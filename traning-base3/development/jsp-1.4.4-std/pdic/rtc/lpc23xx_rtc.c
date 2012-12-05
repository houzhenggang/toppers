/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: lpc23xx_rtc.c,v 1.1 2011/07/24 19:18:56 roi Exp $
 */

/*
 *  LPC23XX��RTC�ǥХ����ɥ饤��
 */

#include <t_services.h>
#include <s_services.h>
#include "kernel_id.h"
#include "lpc23xx_rtc.h"

static void (*alarm_func)(int event);

/*
 *  RTC�ѳ���ߥϥ�ɥ�
 */
void rtc_isr0 (void)
{ 
	UW status = sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR));

	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_ILR), status);
	if(alarm_func != NULL)
		alarm_func(status);
}

/*
 *  RTC�ѽ����
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
 *  RTC��ư�ؿ�
 *
 *  �����Ȥ��Ƴ����ȯ�����Υ�����Хå��ؿ����Ϥ���
 *  ���פʾ��ϡ�NULL���Ϥ��Ф褤��
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
 *  RTC����ߴؿ�
 */
ER lpc23xx_rtc_terminate(void)
{
	alarm_func = NULL;
	sil_wrw_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR), sil_rew_mem((VP)(TADR_RTC_BASE+TOFF_RTC_CCR)) & ~CCR_CLKEN);
	return E_OK;
}

/*
 *  RTC�λ�������ؿ�
 *
 *  ����������PONIX��tm��¤�Τ���Ѥ���
 *  PONIX�Υ��󥯥롼�ɤ��ʤ������θ����Ʊ����ܤ�tm2��ɥ饤�ФȤ���������롣
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
 *  RTC�Υ��顼���������ؿ�
 *
 *  ����������PONIX��tm��¤�Τ���Ѥ���
 *  ����оݳ��ι��ܤϥޥ��ʥ��ͤ����ꤹ�뤳�Ȥˤ�ꡢ��Ӥ��ʤ��褦�����ꡣ
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
 *  RTC�λ�����Ф��ؿ�
 *
 *  ����������PONIX��tm��¤�Τ���Ѥ���
 *  PONIX�Υ��󥯥롼�ɤ��ʤ������θ����Ʊ����ܤ�tm2��ɥ饤�ФȤ���������롣
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
 *  ���󥯥���ȳ���������������
 *
 *  ����������PONIX��tm��¤�Τ���Ѥ���
 *  ����оݳ��ι��ܤϥޥ��ʥ��ͤ����ꤹ�뤳�Ȥˤ�ꡢ��Ӥ��ʤ��褦�����ꡣ
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

