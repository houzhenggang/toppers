/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *                2003      by  Advanced Data Controls, Corp
 *  Copyright (C) 2006 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.3 2006/06/18 09:14:24 roi Exp $
 */

/*
 *  CPU��¸�����ޥ⥸�塼���lpc23xx�ѡ�
 *  TIMER1(12Mhz����)�����
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>
#include <lpc23xx.h>

/*
 *  �����޳���ߤγ�����ֹ�
 */
#define INHNO_TIMER    INTNO_TIMER0

#ifndef _MACRO_ONLY

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *  TIMER_CLOCK �ϥ������åȥܡ����������
 */
#define TO_CLOCK(nume, deno) ((TIMER_CLOCK * (nume) / (deno))-1)
#define TO_USEC(clock)       ((clock) * 1000 / TIMER_CLOCK)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK    ((CLOCK) 0xffffffff)
/*
 *  �����ޤθ����ͤ�����ȯ�������ͤȤߤʤ�����Ƚ��
 */
#define GET_TOLERANCE    100
#define BEFORE_IREQ(clock) \
        ((clock) >= TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
Inline void
hw_timer_initialize()
{
    CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);

    /*
     *  �����޴�Ϣ������
     */
	/* ��������ߤȥꥻ�å� */
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_TCR), 0x00000002);
	/* ����ߥ��ꥢ */
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_IR), 0x00000001);
	/* �ץꥹ������ȳ�������� */
	sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_CTCR), 0x00000000);
	sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_PR), 0x00000000);
    /* �����޾���ͤΥ����å� */
    assert(cyc <= MAX_CLOCK);
    /* ��������ͤ򥻥å� */
	sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_MR0), cyc);
    /* �ޥå������󥿥��å�  */
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_MCR), 0x00000003);
    /* ������ȥ�������   */
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_TCR), 0x00000001);
}

/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_IR), 0x00000001);
}

/*
 *  �����ޤ���߽���
 */
Inline void
hw_timer_terminate()
{
    /* ��������� */
    sil_wrw_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_TCR), 0x00000002);
    /* ������Ե���*/
    sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_INTENCLR), 1<<INHNO_TIMER);
}

/*
 *  �����ޤθ����ͤ��ɤߤ���
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
    return(sil_rew_mem((VP)TADR_TMR0_BASE+TOFF_TMR_TC));
}

Inline BOOL
hw_timer_fetch_interrupt(void)
{
    return((sil_rew_mem((VP)(TADR_TMR0_BASE+TOFF_TMR_IR)) & 1) != 0);
}

#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */



