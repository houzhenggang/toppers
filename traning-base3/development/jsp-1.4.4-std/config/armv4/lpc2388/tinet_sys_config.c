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
 *  @(#) $Id: $
 */

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#if defined(SUPPORT_ETHER)

/*
 *  データ
 */
UB lp23xx_macaddr[LPC_ETHER_ADDR_LEN];

/*
 *  ETHERNET用のシステム設定
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
