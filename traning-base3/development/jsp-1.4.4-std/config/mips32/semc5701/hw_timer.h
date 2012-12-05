/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 */

/*
 *	�����ޥɥ饤��
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>

/*
 *  �����޳���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_TIMER	INTNO_TIMER0

#ifndef _MACRO_ONLY
/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW		CLOCK;

#endif /* _MACRO_ONLY */

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *  TIMER_CLOCK�ϡ��ܡ��ɴط��Υإå��ե�����˵��ܤ��Ƥ��롣
 */
/* 1�ߥ��ü���(isig_tim ��ƤӽФ�����;1kHz)��ȯ�������뤿��Υ�����ȿ� */
#define	TO_CLOCK(nume, deno)	(TIMER_CLOCK * (nume) / (deno))
/* clock �� usec ñ�̤��Ѵ�����ޥ��� */
#define	TO_USEC(clock)		((clock) * 1000u / TIMER_CLOCK)

/*
 *  �����ޤθ����ͤ�����ȯ�������ͤȤߤʤ�����Ƚ��
 */
#define	GET_TOLERANCE		((1 << COUNT_TICK_SHIFT) / 100)	/* �����٤�θ��Ѥ���(ñ�̤�����ɽ��) */
#define	BEFORE_IREQ(clock) \
		((clock) >= (1 << COUNT_TICK_SHIFT) - GET_TOLERANCE)

#ifndef _MACRO_ONLY

/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void hw_timer_int_clear() {
	Asm(
			"mfc0 $2, $9; li $3, %0; addu $2, $2, $3; li $3, %1; and $2, $2, $3; mtc0 $2, $11"
			:
			: "i"((1 << COUNT_TICK_SHIFT) + COUNT_TICK_MARGIN), "i"(-1 << COUNT_TICK_SHIFT)
			: "$2", "$3"
	);
}


/*
 *  �����ޤε�ư����
 *  �������ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
Inline void hw_timer_initialize() {
	/*
	 *  �����޳���ߤγ���ߥ�٥�����ꤷ���׵�򥯥ꥢ�����塤
	 *  �ޥ����������롥
	 */
	all_set_ilv( INTNO_TIMER0, &((IPM) IPM_TIMER0) );/* ����ߥ�٥������ */

	hw_timer_int_clear();				/* ������׵�򥯥ꥢ */

	x_enable_int(INTNO_TIMER0);		/* ����ߥޥ������ */
}

/*
 *  �����ޤ���߽���
 *  �����ޤ�ư�����ߤ����롥
 */
Inline void hw_timer_terminate() {
	/*
	 *  �����޳���ߤ�ޥ��������׵�򥯥ꥢ���롥
	 */
	x_disable_int(INTNO_TIMER0);		/* ����ߤ�ޥ��� */

	hw_timer_int_clear();				/* ������׵�򥯥ꥢ */
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK hw_timer_get_current() {
	UW count;
	Asm(
			"mfc0 %0, $9"
			: "=r"(count)
	);
	return count & ((1 << COUNT_TICK_SHIFT) - 1);
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline BOOL hw_timer_fetch_interrupt() {
	return x_probe_int(INTNO_TIMER0);
}

#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */
