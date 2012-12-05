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
 *  @(#) $Id: clock.c,v 1.2 2012/07/08 12:55:29 roi Exp $
 */

#include "config.h"
#include <stdio.h>
#include <time.h>

/*
 *  �ѥ��ץ��ޥ���ֹ�
 */
#define PIPE_DATE        0
#define PIPE_TIME        1
#define PIPE_CLOCK       2
#define PIPE_TEST        3
#define PIPE_HELP        4

/*
 *  �ѥ��ץ��ޥ�ɥơ��֥�
 */
static const struct SUBCOMMAND_TABLE const mon_pipe[] = {
	{"DATE",	PIPE_DATE    },	/* ���ˤ����� */
	{"TIME",	PIPE_TIME    },	/* �������� */
	{"CLOCK",	PIPE_CLOCK   },	/* ���� */
    {"TEST",    PIPE_TEST    },
	{"HELP",	PIPE_HELP    }
};

static const char monthday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

time_t mktime(struct tm *ptm)
{
	int day = ptm->tm_year *365;
	int yday, i;

	day += (ptm->tm_year+2) / 4;
	for(i = 1, yday = 0 ; i < ptm->tm_mon ; i++)
		yday += monthday[i-1];
	if(ptm->tm_mon > 2 && ((ptm->tm_year+2) % 4) == 0)
		yday++;
	yday += ptm->tm_mday - 1;
	day  += yday;
	ptm->tm_wday = (day+4) % 7;
	ptm->tm_yday = yday+1;
	syslog_3(LOG_INFO, "yday[%d] wday[%d] day[%d]", yday+1, ptm->tm_wday, ptm->tm_yday);
	return day * (24*60*60) + ptm->tm_hour * 60*60 + ptm->tm_min * 60 + ptm->tm_sec;
}

/*
 *  PIPE���ޥ�ɤΥǥ����ѥå�
 */
INT pipe_command(B *command)
{
	int   point=0;
	char  cmd=1;
	int   no, count, arg1, arg2, arg3;
	char  reg;
	struct tm timedate;
	count = sizeof(mon_pipe) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_pipe[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_pipe[no].type;
				break;
			}
		}
	}
	arg1 = 1970;
	switch(cmd){
	case PIPE_DATE:	/* �������� */
		sscanf((char *)&command[point], "%d %d %d", &arg1, &arg2, &arg3);
		printf("%04d/%02d/%02d\n", arg1, arg2, arg3);
		rtc_get_time(&timedate);
		timedate.tm_mday = arg3;
		timedate.tm_mon = arg2;
		timedate.tm_year = arg1-1970;
		timedate.tm_isdst = 0;
		mktime((struct tm *)&timedate);
		rtc_set_time(&timedate);
		break;
	case PIPE_TIME:/* SECTOR WRITE���� */
		sscanf((char *)&command[point], "%d %d %d", &arg1, &arg2, &arg3);
		printf("%02d:%02d:%02d\n", arg1, arg2, arg3);
		rtc_get_time(&timedate);
		timedate.tm_sec = arg3;
		timedate.tm_min = arg2;
		timedate.tm_hour = arg1;
		timedate.tm_isdst = 0;
		mktime((struct tm *)&timedate);
		rtc_set_time(&timedate);
		break;
	case PIPE_CLOCK:
		rtc_get_time(&timedate);
		syslog_3(LOG_NOTICE, "        %04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
		syslog_5(LOG_NOTICE, "y[%d][%d] %02d:%02d:%02d", timedate.tm_yday, timedate.tm_wday, timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
		break;
	case PIPE_TEST:
		sscanf((char *)&command[point], "%d", &arg1);
		printf("test no[%02d]\n", arg1);
		if(arg1 == 1)
			rtc_test(0);
		else if(arg1 == 2)
			file_test(0);
		break;
	default:
		printf("  DATE  (year #) (month #) (day #)\n");
		printf("  TIME  (hour #) (min   #) (sec #)\n");
		printf("  CLOCK DATE:TIME\n");
		printf("  TEST  (no)\n");
		break;
	}
	return 0;
}

