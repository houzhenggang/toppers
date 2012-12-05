/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: lpc23xx_rtc.c,v 1.1 2011/07/24 19:18:56 roi Exp $
 */

/*
 *  LPC23XX用RTCデバイスドライバ
 */

#include <t_services.h>
#include <s_services.h>
#include "kernel_id.h"
#include "lpc23xx_rtc.h"

static void (*alarm_func)(int event);

/*
 *  RTC用割込みハンドラ
 */
void rtc_isr0 (void)
{ 
	UW status = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR));

	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR), status);
	if(alarm_func != NULL)
		alarm_func(status);
}

/*
 *  RTC用初期化
 */
void rtc_init(VP_INT exinf)
{
	alarm_func = NULL;
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_AMR), 0x000000FF);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CIIR), 0x00000000);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR), 0x00000000);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_PREINT), PREINT_RTC);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_PREFRAC), PREFRAC_RTC);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR), ILR_RTCCIF|ILR_RTCALF);
}

/*
 *  RTC起動関数
 *
 *  引数として割込み発生時のコールバック関数を渡す。
 *  不要な場合は、NULLを渡せばよい。
 */
ER lpc23xx_rtc_start(VP_INT func)
{
	UW ccr = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR));

	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR), ccr | CCR_CLKEN);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR), ILR_RTCCIF|ILR_RTCALF);
	alarm_func = func;
	return E_OK;
}

/*
 *  RTCの停止関数
 */
ER lpc23xx_rtc_terminate(void)
{
	alarm_func = NULL;
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR), sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR)) & ~CCR_CLKEN);
	return E_OK;
}

/*
 *  RTCの時刻設定関数
 *
 *  時刻の設定はPONIXのtm構造体を使用する
 *  PONIXのインクルードがない場合を考慮し、同一項目のtm2をドライバとして定義する。
 */
ER lpc23xx_rtc_set_time(struct tm2 *pt)
{
	if(pt == NULL)
		return E_PAR;
	_syscall(wai_sem(RTCSEM));
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_SEC), pt->tm_sec);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_MIN), pt->tm_min);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_HOUR), pt->tm_hour);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOM), pt->tm_mday);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOW), pt->tm_wday);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOY), pt->tm_yday);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_MONTH), pt->tm_mon);
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_YEAR), pt->tm_year+BASE_YEAR);
	_syscall(sig_sem(RTCSEM));
	return E_OK;
}

/*
 *  RTCのアラーム時刻設定関数
 *
 *  時刻の設定はPONIXのtm構造体を使用する
 *  比較対象外の項目はマイナス値を設定することにより、比較しないように設定。
 */
ER lpc23xx_rtc_set_alarm(struct tm2 *pt)
{
	UW alarm_mask = 0;

	if(pt == NULL)
		return E_PAR;
	_syscall(wai_sem(RTCSEM));
	if(pt->tm_sec >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALSEC), pt->tm_sec);
	else
		alarm_mask |= AMRSEC;
	if(pt->tm_min >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALMIN), pt->tm_min);
	else
		alarm_mask |= AMRMIN;
	if(pt->tm_hour >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALHOUR), pt->tm_hour);
	else
		alarm_mask |= AMRHOUR;
	if(pt->tm_mday > 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALDOM), pt->tm_mday);
	else
		alarm_mask |= AMRDOM;
	if(pt->tm_wday >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALDOW), pt->tm_wday);
	else
		alarm_mask |= AMRDOW;
	if(pt->tm_yday >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALDOY), pt->tm_yday);
	else
		alarm_mask |= AMRDOY;
	if(pt->tm_mon > 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALMON), pt->tm_mon);
	else
		alarm_mask |= AMRMON;
	if(pt->tm_year >= 0)
		sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ALYEAR), pt->tm_year+BASE_YEAR);
	else
		alarm_mask |= AMRYEAR;
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_AMR), alarm_mask);
	_syscall(sig_sem(RTCSEM));
	return E_OK;
}

/*
 *  RTCの時刻取り出し関数
 *
 *  時刻の設定はPONIXのtm構造体を使用する
 *  PONIXのインクルードがない場合を考慮し、同一項目のtm2をドライバとして定義する。
 */
ER lpc23xx_rtc_get_time(struct tm2 *pt)
{
	if(pt == NULL)
		return E_PAR;
	_syscall(wai_sem(RTCSEM));
	pt->tm_sec  = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_SEC));
	pt->tm_min  = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_MIN));
	pt->tm_hour = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_HOUR));
	pt->tm_mday = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOM));
	pt->tm_wday = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOW));
	pt->tm_yday = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_DOY));
	pt->tm_mon  = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_MONTH));
	pt->tm_year = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_YEAR)) - BASE_YEAR;
	_syscall(sig_sem(RTCSEM));
	return E_OK;
}

/*
 *  インクリメント割込み設定項目設定
 *
 *  時刻の設定はPONIXのtm構造体を使用する
 *  比較対象外の項目はマイナス値を設定することにより、比較しないように設定。
 */
ER lpc23xx_rtc_set_event(struct tm2 *pt)
{
	UW sint = 0;

	if(pt == NULL)
		return E_PAR;
	_syscall(wai_sem(RTCSEM));
	if(pt->tm_sec >= 0)
		sint |= IMSEC;
	if(pt->tm_min >= 0)
		sint |= IMMIN;
	if(pt->tm_hour >= 0)
		sint |= IMHOUR;
	if(pt->tm_mday >= 0)
		sint |= IMDOM;
	if(pt->tm_wday >= 0)
		sint |= IMDOW;
	if(pt->tm_yday >= 0)
		sint |= IMDOY;
	if(pt->tm_mon >= 0)
		sint |= IMMON;
	if(pt->tm_year >= 0)
		sint |= IMYEAR;

	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CIIR), sint);
	_syscall(sig_sem(RTCSEM));
	return E_OK;
}

