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
 *  @(#) $Id: lpc23xx_rtc.h,v 1.1 2010/08/13 17:38:40 roi Exp $
 */


/*
 *  LPC23XX用RTCデバイスドライバインクルード
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
 *  日時設定用の構造体を定義
 */
struct tm2 {
  int	tm_sec;			/* 秒 */
  int	tm_min;			/* 分 */
  int	tm_hour;		/* 時 */
  int	tm_mday;		/* 月中の日 */
  int	tm_mon;			/* 月 */
  int	tm_year;		/* 年 */
  int	tm_wday;		/* 曜日 */
  int	tm_yday;		/* 年中の日 */
  int	tm_isdst;
};

/*
 *  RTCデバイスドライバプロトタイプ宣言
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
