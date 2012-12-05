/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: lpc23xx_gpdma.c,v 1.1 2010/08/12 21:18:56 roi Exp $
 */

/*
 *  LP23XX GPDMA�ǥХ����ɥ饤��
 */
#include <s_services.h>
#include "lpc23xx_gpdma.h"


#define SBSIZE_SHIFT    12
#define DBSIZE_SHIFT    15
#define SWIDTH_SHIFT    18
#define DWIDTH_SHIFT    21
#define SI_SHIFT        26
#define DI_SHIFT        27
#define IE_SHIFT        31


static const UW dma_base[NUM_DMA_CHANNEL] = {TADR_DMAC_BASE+TOFF_DMAC_CH0, TADR_DMAC_BASE+TOFF_DMAC_CH1};

/*
 *  GPDMA����ߥϥ�ɥ�
 */
void dma_isr0(void)
{
	UW regVal, tmp;
	static W DMATCCount, DMAErrCount;

	syslog_0(LOG_NOTICE, "## dma int ##");
	regVal = sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTTCSTAT));
	if ( regVal ){
		DMATCCount++;
		tmp  = sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTTCCLR));
		tmp |= regVal;
		sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTTCCLR), tmp);
	}

	regVal = sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTERRSTAT));
	if ( regVal ) {
		DMAErrCount++;
		tmp  = sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTERRCLR));
		tmp |= regVal;
		sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTERRCLR), tmp);
	}
}

/*
 *  GPDMA�ν����
 */
void dma_init(VP_INT exinf)
{
	UW tmp;

	tmp = sil_rew_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP));
	tmp |= 1 << 29;				/* Power on GPDMA block */
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP), tmp);

	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTTCCLR), 0x03);
	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTERRCLR), 0x03);

	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_CONFIG), 0x01);	/* Enable DMA channels */
	while ((sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_CONFIG)) & 0x01) == 0);
}

/*
 *  GPDMAž������
 */
ER lpc23xx_set_trn(UB cnum, UB mode, UW src, UW dst, UW size)
{
	UW base;
	UW ctrl = (size & 0x0FFF) | (1<<IE_SHIFT) | (2<<SWIDTH_SHIFT) | (2<<DWIDTH_SHIFT);

	if(cnum >= NUM_DMA_CHANNEL)
		return E_ID;
	base = dma_base[cnum];
	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTTCCLR), (1<<cnum));
	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_INTERRCLR), (1<<cnum));
	switch(mode){
	case M2MD:
	case M2MP:
		ctrl |= (0x04<<SBSIZE_SHIFT) | (0x04<<DBSIZE_SHIFT) | (1<<SI_SHIFT) | (1<<DI_SHIFT);
		break;
	case M2PD:
	case M2PP:
		ctrl |= (0x04<<SBSIZE_SHIFT) | (0x02<<DBSIZE_SHIFT) | (1<<SI_SHIFT);
		break;
	case P2MD:
	case P2MP:
		ctrl |= (0x02<<SBSIZE_SHIFT) | (0x04<<DBSIZE_SHIFT) | (1<<DI_SHIFT);
		break;
	default:
		ctrl = 0;
		break;
	}
	if(ctrl == 0)
		return FALSE;
	sil_wrw_mem((VP)(base+TOFF_DMAC_CH_SRC), src);
	sil_wrw_mem((VP)(base+TOFF_DMAC_CH_DEST), dst);
	sil_wrw_mem((VP)(base+TOFF_DMAC_CH_CTRL), ctrl);

	sil_wrw_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_CONFIG), 0x01);	/* Enable DMA channels */
	while ((sil_rew_mem((VP)(TADR_DMAC_BASE+TOFF_DMAC_CONFIG)) & 0x01) == 0);
	return E_OK;
}

/*
 *  GPDMA����ե�����졼���������
 */
ER lpc23xx_set_cfg(UB cnum, UB sp, UB dp, UB mode)
{
	UW base, tmp;
	if(cnum >= NUM_DMA_CHANNEL)
		return E_ID;

	base = dma_base[cnum];
	tmp  = sil_rew_mem((VP)(base+TOFF_DMAC_CH_CFG));
	tmp |= (mode<<11) | (sp<<1) | (dp<<6) | 0x10001;
	sil_wrw_mem((VP)(base+TOFF_DMAC_CH_CFG), tmp);
	return E_OK;
}

