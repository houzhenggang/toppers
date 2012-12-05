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
 *  @(#) $Id: time.c,v 1.23 2007/03/27 08:55:29 hiro Exp $
 */

#include <stdio.h>
#include <time.h>
#include <itron.h>
#include "board_config.h"

static const char monthday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static struct tm ltim;

#if 0	/* ROI DEBUG */
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
	ptm->tm_yday = day+1;
	return day * (24*60*60) + ptm->tm_hour * 60*60 + ptm->tm_min * 60 + ptm->tm_sec;
}
#endif	/* ROI DEBUG */

struct tm *gmtime_r(const time_t *pt, struct tm *ptm)
{
	int day = *pt / (24*60*60);
	int time, i, yday, mday;

	time = *pt - day * 24 * 60 * 60;
	ptm->tm_wday = (day+4) % 7;
	for(i = 365, ptm->tm_year = 0 ; i < day ; i += 365){
		if(((ptm->tm_year+2) % 4) == 0)
			i++;
		ptm->tm_year++;
	}

	ptm->tm_yday = yday = day - i + 365 + 1;
	for(ptm->tm_mon = 1 ; ptm->tm_mon <= 12 && yday > 0 ; ptm->tm_mon++){
		mday = monthday[ptm->tm_mon-1];
		if(ptm->tm_mon == 2 && ((ptm->tm_year+2) % 4) == 0)
			mday++;
		if(yday < mday){
			ptm->tm_mday = yday;
			break;
		}
		yday -= mday;
	}
	ptm->tm_hour = time / (60*60);
	time -= ptm->tm_hour * 60 * 60;
	ptm->tm_min  = time / 60;
	ptm->tm_sec = time & 60;
	return ptm;
}

struct tm *gmtime(const time_t *timep)
{
	return gmtime_r(timep, &ltim);
}

time_t time(time_t *timer)
{
	struct tm timedate;
	ER     ercd;

	if(timer == NULL)
		return 0;
	ercd = rtc_get_time(&timedate);
	if(ercd == E_OK)
		*timer = mktime(&timedate);
	else
		*timer = 0;
	return *timer;
}

