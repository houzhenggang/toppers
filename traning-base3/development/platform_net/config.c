/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010-2011 by GJ Business Division RICOH COMPANY,LTD.
 *                   JAPAN
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
 *  @(#) $Id: sample1.c,v 1.23 2007/03/27 08:55:29 hiro Exp $
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include <t_services.h>
#include <s_services.h>
#include "kernel_id.h"
#include <tinet_config.h>
#include <tinet_defs.h>
#include "tinet_id.h"
#include "config.h"

#include "dhcp.h"

/*
 *  周期ハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
void cyclic_handler(VP_INT exinf)
{
	static unsigned int sw = 1;

	sil_wrw_mem((VP)(TADR_FIO_BASE+TOFF_FIO2_CLR), sw);		/* led on */
	sil_wrw_mem((VP)(TADR_FIO_BASE+TOFF_FIO2_SET), ~sw);	/* led off */
	sw <<= 1;
	if((sw & 0x00000100) != 0)
		sw = 1;
}

/*
 *  MACアドレスの設定
 */
void
macaddr_init(VP_INT exinf)
{
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE1};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}

/*
 *  メインタスク
 */
void main_task(VP_INT exinf)
{
	int  result;
    T_IF_SOFTC  *ic;
	ER	error = E_OK;
	INT connect = FALSE;
	int ch = 0;

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	sta_cyc(CYCHDR1);

	dly_tsk(1000);	/* wait tinet */
	/*
	 * 自分のMACアドレス読み込み
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}

	syslog_0(LOG_NOTICE, "start telnet !");
	act_tsk(TCP_TELNET_SRV_TASK);
	while(ch != EOF){
		if(tcp_telnet_connect()){	/* connect */
			if(!connect){
				syslog_0(LOG_NOTICE, "TELNET CONNECT !");
				connect = TRUE;
			}
			dly_tsk(100);
		}
		else{				/* disconnect */
			if(connect){
				syslog_0(LOG_NOTICE, "TELNET DISCONNECT !");
				connect = FALSE;
			}
			dly_tsk(100);
		}
	}

	syslog(LOG_NOTICE, "Sample program ends.");
	kernel_exit();
}
