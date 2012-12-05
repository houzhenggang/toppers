/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2006-2011 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: $
 */

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#if defined(SUPPORT_ETHER)

/*
 *  �ǡ���
 */
UB lp23xx_macaddr[LPC_ETHER_ADDR_LEN];

/*
 *  ETHERNET�ѤΥ����ƥ�����
 */
void
tinet_sys_initialize(void)
{
	unsigned long tmp;

	/* turn on the ethernet MAC clock in PCONP, bit 30 */
	tmp  = sil_rew_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP));
	tmp |= PCONP_EMAC_CLOCK;
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP), tmp);

	sil_dly_nse(20000);
  /*------------------------------------------------------------------------------      
   * write to PINSEL2/3 to select the PHY functions on P1[17:0]
   *-----------------------------------------------------------------------------*/
  /* documentation needs to be updated */
#ifdef USE_RMII
	/* P1.6, ENET-TX_CLK, has to be set for EMAC to address a BUG in the engineering 
	version, even if this pin is not used for RMII interface. This bug has been fixed,
	and this port pin can be used as GPIO pin in the future release. */ 
	/* Unfortunately, this MCB2300 board still has the old eng. version LPC23xx chip
 	on it. On the new rev.(xxAY, released on 06/22/2007), P1.6 should NOT be set.
	See errata for more details. */
	tmp = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MODULEID));

	if ( tmp == PHILIPS_EMAC_MODULE_ID ){
		/* This is the rev."-" ID for the existing MCB2300 board,
		on rev. A, regVal should NOT equal to PHILIPS_EMAC_MODULE_ID,
		P1.6 should NOT be set. */
		sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL2), 0x50151105);	/* selects P1[0,1,4,6,8,9,10,14,15] */
	}
	else{
		sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL2), 0x50150105);	/* selects P1[0,1,4,8,9,10,14,15] */
	}
#else					/* else RMII, then it's MII mode */      
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL2), 0x55555555);	/* selects P1[15:0] */
#endif
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL3), 0x00000005);	/* selects P1[17:16] */
}

#endif	/* of #if defined(SUPPORT_ETHER) */
