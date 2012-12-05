/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
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
 *
 */

/*
 *	�����ޥɥ饤�С�ADSP-BF537�ѡ�
 *
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>


#ifndef _MACRO_ONLY

#ifdef __GNUC__			// gcc
#include "../cdefbf537.h"
#elif defined(__ECC__)	// visualdsp
#include <cdefbf53x.h>
#else
#error "Compiler is not supported"
#endif

//#include <ccblkfn.h>




/**************************************************************
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 *
 **************************************************************/
Inline void
hw_timer_initialize()
{
#ifndef USE_TIC_CORE
	UW	reg;
#endif

#ifdef USE_TIC_CORE
	// Core timer
	*pTCNTL = TMPWR;					// power up timer;
	*pTPERIOD = CORECLOCK/1000;			// CORE CLOCK is defined in sys_config.h
	*pTCNTL = TMPWR | TMREN | TAUTORLD;
#else
	// GPT7(General-purpose timer7)

	*pTIMER7_CONFIG = PERIOD_CNT | OUT_DIS |IRQ_ENA | PWM_OUT;	// PWM_OUT, Output Pad disable
	*pTIMER7_PERIOD = SYSCLOCK/1000;	// SYS CLOCK is defined in sys_config.h
	*pTIMER7_WIDTH = 1;					// 0 < width < period
	*pTIMER_ENABLE = TIMEN7;			// timer7 start
	ena_int( INHNO_TIMER );				// enable Timer Interrupt

#endif
	asm("ssync;");

}

/**************************************************************
 *  �����޳�����׵�Υ��ꥢ
 **************************************************************/
Inline void
hw_timer_int_clear()
{
#ifdef USE_TIC_CORE
	// Core timer
	*pTCNTL = TMPWR | TMREN | TAUTORLD | TINT;
#else
	// GPT7(General-purpose timer7)
	*pTIMER_STATUS = TIMIL7;
#endif
	asm("ssync;");
}

/**************************************************************
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 **************************************************************/
Inline void
hw_timer_terminate()
{
	/*
	 *  �����ޤ�ư�����ߤ��롥
	 */
#ifdef USE_TIC_CORE
	// Core timer
	*pTCNTL = TMPWR | TAUTORLD | TINT;		// ���
	*pTCNTL = 0;							// �ѥ������⡼��
#else
	// GPT2(General-purpose timer7)
	*pTIMER_DISABLE = TIMEN7;			// timer7 disable
#endif
	asm("ssync;");
}


#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */
