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
 *  @(#) $Id: config.c,v 1.01 2011/12/10 17:55:29 roi Exp $
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include "config.h"
#include <tinet_config.h>
#include <tinet_defs.h>
#include "ff.h"
#include "fcntl.h"
#include "dhcp.h"

#include "kernel_id.h"
#include "tinet_id.h"

static void  *mon_infile;
int   (*application)(INT mode);

extern FILE *_get_stdio(int no);
extern int   _set_stdio(int no);
extern void *monitor_infile(void *file);
extern INT  dispatcher(INT mode);

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
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE3};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}

/*
 *  FILE�����ƥ��ѻ��ּ����ؿ�
 */
static int get_rtc_time(void)
{
	struct tm2 timedate;
	int    reqtime, ctime;

	rtc_get_time(&timedate);
	reqtime  = ((timedate.tm_year-10)<<25)+(timedate.tm_mon<<21)+(timedate.tm_mday<<16);
	reqtime += (timedate.tm_hour<<11)+(timedate.tm_min<<5)+(timedate.tm_sec/2);
	return reqtime;
}

/*
 *  STORAGE DEVICE������
 */
static void sdcard_notice(StorageDevice_t *psdev, BOOL sw)
{
	if(sw)
		syslog_1(LOG_NOTICE, "found sd-card %d sectors !", psdev->_sdev_maxsec);
	else
		syslog_0(LOG_NOTICE, "remove sd-card !");
}

/*
 *  TELNET���ץꥳ����Хå��ؿ�
 */
static void callback_telnet(INT mode)
{
	FILE *st;

	syslog_1(LOG_NOTICE, "callback telnet(%d) !", mode);
	switch(mode){
	case TCP_TELNET_IN:
		mon_infile = monitor_infile(stderr);
		st = _get_stdio(0);
		tcp_telnet_srv_set_file(st);
		st = _get_stdio(1);
		tcp_telnet_srv_set_file(st);
		st = _get_stdio(2);
		tcp_telnet_srv_set_file(st);
		break;
	case TCP_TELNET_OUT:
		_set_stdio(0);
		_set_stdio(1);
		_set_stdio(2);
		monitor_infile(mon_infile);
		break;
	default:
		break;
	}
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(VP_INT exinf)
{
/*	int  result; */
	StorageDevice_t *psdev;
	FATFS   *fs;
	struct tm2 timedate;
    T_IF_SOFTC  *ic;
	ER	error = E_OK;
	INT  ch = 0;

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	sta_cyc(CYCHDR1);

	/*
	 *  RTC���Хåƥ�Хå����åפǤʤ����ᡢ���������
	 */
	timedate.tm_sec = 0;
	timedate.tm_min = 0;
	timedate.tm_hour = 21;
	timedate.tm_mday = 3;
	timedate.tm_mon = 3;
	timedate.tm_year = 2012-1970;
	timedate.tm_isdst = 0;
	mktime((struct tm *)&timedate);
	rtc_set_time(&timedate);
	rtc_start(NULL);
	SDeviceHead._get_datetime = get_rtc_time;

	/*
	 *  SD�����ɥե����륷���ƥ��MCI�ν����
	 */
	_sd_init();
	psdev = SDMGetStorageDevice(0);
	fs = (FATFS *)psdev->_sdev_local[0];
	psdev->_sdev_notice = sdcard_notice;

	/*
	 *  �������κ�ɽ��
	 */
	rtc_get_time(&timedate);
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
	chg_pri(TSK_SELF, DEFAULT_PRIORITY);

	/*
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}

	/*
	 *  SD�����ɸ����Ԥ�
	 */
	while((psdev->_sdev_attribute & SDEV_EMPLOY) == 0){
		SDMSence_task(0);
	}
	syslog_0(LOG_NOTICE, "start telnet !");
	tcp_telnet_srv_init(callback_telnet);
	while(ch != EOF){
		if(tcp_telnet_connect()){	/* connect */
			if(application != NULL)
				ch = application(0);
			else{
				putchar(ch = getchar());
				if(ch == CHAR_CR)
					putchar(CHAR_LF);
			}
		}
		else				/* disconnect */
			dly_tsk(100);
	}

	syslog(LOG_NOTICE, "Sample program ends.");
	kernel_exit();
}
