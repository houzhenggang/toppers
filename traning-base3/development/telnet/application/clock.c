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
 *  @(#) $Id: clock.c,v 1.2 2012/07/08 12:55:29 roi Exp $
 */

#include "config.h"
#include <stdio.h>
#include <time.h>

/*
 *  パイプコマンド番号
 */
#define PIPE_DATE        0
#define PIPE_TIME        1
#define PIPE_CLOCK       2
#define PIPE_TEST        3
#define PIPE_HELP        4

/*
 *  パイプコマンドテーブル
 */
static const struct SUBCOMMAND_TABLE const mon_pipe[] = {
	{"DATE",	PIPE_DATE    },	/* 日にち設定 */
	{"TIME",	PIPE_TIME    },	/* 時間設定 */
	{"CLOCK",	PIPE_CLOCK   },	/* 時計 */
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
 *  PIPEコマンドのディスパッチ
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
	case PIPE_DATE:	/* 日時設定 */
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
	case PIPE_TIME:/* SECTOR WRITE制御 */
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

