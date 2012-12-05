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
 *  @(#) $Id: lpc23xx_rtc.h,v 1.1 2010/08/13 17:38:40 roi Exp $
 */


/*
 *  LPC23XX��RTC�ǥХ����ɥ饤�Х��󥯥롼��
 */


#ifndef _LPC23XX_RTC_H_
#define _LPC23XX_RTC_H_

#define INHNO_RTC   INTNO_RTC

#define BASE_YEAR   1970

#define IMSEC       (1<<0)		/* Interrupt for Seconds */
#define IMMIN       (1<<1)		/* Interrupt for Minutes */
#define IMHOUR      (1<<2)		/* Interrupt for Hours */
#define IMDOM       (1<<3)		/* Interrupt for Day of Manth */
#define IMDOW       (1<<4)		/* Interrupt for Day of Week */
#define IMDOY       (1<<5)		/* Interrupt for Day of Year */
#define IMMON       (1<<6)		/* Interrupt for Month */
#define IMYEAR      (1<<7)		/* Interrupt for Year */

#define AMRSEC      IMSEC		/* Alarm mask for Seconds */
#define AMRMIN      IMMIN		/* Alarm mask for Minutes */
#define AMRHOUR     IMHOUR		/* Alarm mask for Hours */
#define AMRDOM      IMDOM		/* Alarm mask for Day of Month */
#define AMRDOW      IMDOW		/* Alarm mask for Day of Week */
#define AMRDOY      IMDOY		/* Alarm mask for Day of Year */
#define AMRMON      IMMON		/* Alarm mask for Month */
#define AMRYEAR     IMYEAR		/* Alarm mask for Year */

#define PREINT_RTC	0x0000016D  /* Prescaler value, integer portion, 
				    PCLK = 15Mhz */
#define PREFRAC_RTC	0x000061C0  /* Prescaler value, fraction portion, 
				    PCLK = 15Mhz */
#define ILR_RTCCIF	0x01
#define ILR_RTCALF	0x02
#define ILR_RTSSF   0x04

#define CCR_CLKEN	0x01
#define CCR_CTCRST	0x02
#define CCR_CLKSRC	0x10

#ifndef _MACRO_ONLY

/*
 *  ���������Ѥι�¤�Τ����
 */
struct tm2 {
  int	tm_sec;			/* �� */
  int	tm_min;			/* ʬ */
  int	tm_hour;		/* �� */
  int	tm_mday;		/* ������� */
  int	tm_mon;			/* �� */
  int	tm_year;		/* ǯ */
  int	tm_wday;		/* ���� */
  int	tm_yday;		/* ǯ����� */
  int	tm_isdst;
};

/*
 *  RTC�ǥХ����ɥ饤�Хץ�ȥ��������
 */
extern void rtc_isr0 (void);
extern void rtc_init(VP_INT exinf );
extern ER   lpc23xx_rtc_start(VP_INT func);
extern ER   lpc23xx_rtc_terminate(void);
extern void RTC_CTCReset( void );
extern ER   lpc23xx_rtc_set_time(struct tm2 *pt);
extern ER   lpc23xx_rtc_get_time(struct tm2 *pt);
extern ER   lpc23xx_rtc_set_alarm(struct tm2 *pt);
extern ER   lpc23xx_rtc_set_event(struct tm2 *pt);

#endif	/* _MACRO_ONLY */
#endif /* _LPC23XX_RTC_H_ */
