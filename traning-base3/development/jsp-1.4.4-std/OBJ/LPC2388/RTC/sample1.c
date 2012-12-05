/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

/* 
 *  ����ץ�ץ����(1)������
 *
 *  RTC��ƥ��ȥץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  1.RTC���������ꤹ�롥
 *  2.2ʬ��˥��顼�����ꤹ�롥
 *  3.ǯ���äΥ��󥯥���ȳ���ߤ����ꤹ��.
 *  4.�����ȯ�������ޤ��ϣ��ä��Ȥ�������ɽ������.
 *    �����202�ôַ����֤�
 *  5.��λ������ɽ�����롥
 *
 */

#include <t_services.h>
#include <board_config.h>
#include <stdio.h>
#include <time.h>
#include "kernel_id.h"
#include "sample1.h"

static BOOL alarm_on;
static BOOL first_time = TRUE;

struct tm *gmtime_r(const time_t *pt, struct tm *ptm)
{
	int day = *pt / (24*60*60);
	int time, i;

	time = *pt - day * 24 * 60 * 60;
	ptm->tm_wday = (day+4) % 7;
	for(i = 365, ptm->tm_year = 0 ; i < day ; i += 365){
		if(((ptm->tm_year+2) % 4) == 0)
			i++;
		ptm->tm_year++;
	}
	ptm->tm_yday = day - i + 365 + 1;
	ptm->tm_hour = time / (60*60);
	time -= ptm->tm_hour * 60 * 60;
	ptm->tm_min  = time / 60;
	ptm->tm_sec = time & 60;
	return ptm;
}

static void alarm_event(int event)
{
	alarm_on = TRUE;
	iwup_tsk(MAIN_TASK);
	syslog_1(LOG_NOTICE, "alarmevent[%08x] !", event);
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(VP_INT exinf)
{
	SYSTIM stime;
	int i;
	time_t time;
	struct tm timedate;
	struct tm2 timedate2;

	if(first_time == FALSE){
		syscall(rtc_get_time((struct tm2 *)&timedate));	/* ���֤μ��� */
		goto start_test;
	}

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	/* POSIX�ߴ��ؿ��Υƥ��� */
	time = 0;
	timedate.tm_sec = 0;
	timedate.tm_min = 0;
	timedate.tm_hour = 0;
	timedate.tm_mday = 23;
	timedate.tm_mon = 7;
	timedate.tm_year = 2011-1970;
	timedate.tm_isdst = 0;
	time = mktime(&timedate);
	gmtime_r(&time, &timedate);
	syslog_4(LOG_NOTICE, "time_t[%d] %04d/%02d/%02d", time, timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_5(LOG_NOTICE, "y[%d][%d] %02d:%02d:%02d", timedate.tm_yday, timedate.tm_wday, timedate.tm_hour, timedate.tm_min, timedate.tm_sec);

	/* RTC�Υƥ��� */
	syscall(rtc_set_time((struct tm2 *)&timedate));	/* ���֤����� */
	syslog_0(LOG_NOTICE, "set current date/time");
	first_time = FALSE;

start_test:
	timedate.tm_min += 2;
	timedate.tm_hour = -1;
	timedate.tm_mday = -1;
	timedate.tm_mon = -1;
	timedate.tm_year = -1;
	timedate.tm_wday = -1;
	timedate.tm_yday = -1;
	timedate.tm_isdst = -1;
	syscall(rtc_set_alarm((struct tm2 *)&timedate));	/* ���顼������� */
	syslog_0(LOG_NOTICE, "set alarm date/time");

	timedate.tm_sec = -1;
	timedate.tm_min = 0;
	timedate.tm_year = 0;
	syscall(rtc_set_event((struct tm2 *)&timedate));	/* �ä�ǯ�Υ��󥯥���ȳ���ߤ����� */

	alarm_on = FALSE;
	syscall(rtc_start(alarm_event));
	syslog_0(LOG_NOTICE, "RTC start");

	for(i = 0 ; i < 101 ; i++) {
		syscall(rtc_get_time((struct tm2 *)&timedate));
		get_tim(&stime);
		syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
		syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
		syslog_3(LOG_NOTICE, "count[%d] alarm[%d] systime[%d]", i, alarm_on, stime);
		tslp_tsk(2000);
		alarm_on = FALSE;
	}
	syscall(rtc_get_time((struct tm2 *)&timedate));	/* ��λ����μ��Ф� */
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);

	syslog(LOG_NOTICE, "Sample program ends.");
	dly_tsk(1000);
}
