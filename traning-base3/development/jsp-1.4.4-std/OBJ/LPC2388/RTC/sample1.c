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
 *  @(#) $Id: sample1.c,v 1.23 2007/03/27 08:55:29 hiro Exp $
 */

/* 
 *  サンプルプログラム(1)の本体
 *
 *  RTCをテストプログラム．
 *
 *  プログラムの概要:
 *
 *  1.RTCに日時設定する．
 *  2.2分後にアラーム設定する．
 *  3.年と秒のインクリメント割込みを設定する.
 *  4.割込み発生時、または２秒ごとに日時を表示する.
 *    これを202秒間繰り返す
 *  5.終了日時を表示する．
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
 *  メインタスク
 */
void main_task(VP_INT exinf)
{
	SYSTIM stime;
	int i;
	time_t time;
	struct tm timedate;
	struct tm2 timedate2;

	if(first_time == FALSE){
		syscall(rtc_get_time((struct tm2 *)&timedate));	/* 時間の取得 */
		goto start_test;
	}

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	/* POSIX互換関数のテスト */
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

	/* RTCのテスト */
	syscall(rtc_set_time((struct tm2 *)&timedate));	/* 時間の設定 */
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
	syscall(rtc_set_alarm((struct tm2 *)&timedate));	/* アラームの設定 */
	syslog_0(LOG_NOTICE, "set alarm date/time");

	timedate.tm_sec = -1;
	timedate.tm_min = 0;
	timedate.tm_year = 0;
	syscall(rtc_set_event((struct tm2 *)&timedate));	/* 秒と年のインクリメント割込みを設定 */

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
	syscall(rtc_get_time((struct tm2 *)&timedate));	/* 終了時刻の取り出し */
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);

	syslog(LOG_NOTICE, "Sample program ends.");
	dly_tsk(1000);
}
