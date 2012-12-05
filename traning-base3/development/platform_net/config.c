/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010-2011 by GJ Business Division RICOH COMPANY,LTD.
 *                   JAPAN
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
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
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
 *  MAC���ɥ쥹������
 */
void
macaddr_init(VP_INT exinf)
{
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE1};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}

/*
 *  �ᥤ�󥿥���
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
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
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
