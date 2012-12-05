/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: lpc23xx_gpdma.c,v 1.1 2010/08/12 21:18:56 roi Exp $
 */

/*
 *  LP23XX GPDMAデバイスドライバ
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
 *  GPDMA割込みハンドラ
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
 *  GPDMAの初期化
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
 *  GPDMA転送設定
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
 *  GPDMAコンフィギュレーション設定
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

