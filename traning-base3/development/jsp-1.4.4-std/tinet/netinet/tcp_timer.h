/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: tcp_timer.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)tcp_timer.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/tcp_timer.h,v 1.13.2.1 1999/08/29 16:29:56 peter Exp $
 */
 
#ifndef _TCP_TIMER_H_
#define _TCP_TIMER_H_

/* TCP �������ѿ� */

#define NUM_TCP_TIMERS		4	/* TCP �Υ����޿�	*/

#define TCP_TIM_REXMT		0	/* ����������		*/
#define TCP_TIM_PERSIST		1	/* ��³������		*/
#define TCP_TIM_KEEP		2	/* ��α (keep alive) ������*/
#define TCP_TIM_2MSL		3	/* 2MSL ������		*/

/* MSL: Maximum Segment Lifetime, ���祻��������¸���� 		*/

/*
 *  TCP/IP �Υ����ޤ����
 */

#define TCP_SLOW_TMO		(ULONG_C(500)/NET_TIMER_CYCLE)	/* 500 [ms]	*/
#define TCP_FAST_TMO		(ULONG_C(200)/NET_TIMER_CYCLE)	/* 200 [ms]	*/

#define TCP_SLOW_HZ		(ULONG_C(1000)/TCP_SLOW_TMO/NET_TIMER_CYCLE)	/* Hz	*/

/* TCP �������� */

#define TCP_TVAL_MSL		(TCP_SLOW_HZ * 30)
					/* ���祻��������¸����	*/

#define TCP_TVAL_SRTT_BASE	0	/* ��餫�ʱ������֤δ����*/

#define TCP_TVAL_RTO_BASE	(TCP_SLOW_HZ * 3)
		/* ���������ʤ����κ��������ॢ���Ȥδ����	*/

#define TCP_TVAL_MIN_PERSIST	(TCP_SLOW_HZ * 5)
				/* ��³�����ॢ���ȤκǾ���	*/
#define TCP_TVAL_MAX_PERSIST	(TCP_SLOW_HZ * 60)
				/* ��³�����ॢ���Ȥκ�����	*/

#define TCP_TVAL_KEEP_INIT	(TCP_SLOW_HZ * 75)
					/* ��α�����ޤν����	*/
#define TCP_TVAL_KEEP_IDLE	(TCP_SLOW_HZ * 2 * 60 * 60)
					/* ��α�����޵�ư�ޤǤ�ɸ����*/
#define TCP_TVAL_KEEP_INTERVAL	(TCP_SLOW_HZ * 75)
					/* ��α�����ޥ��󥿡��Х��ɸ����*/
#define TCP_TVAL_KEEP_COUNT	8	/* ��α�����ॢ���Ȥκ�����*/

#define TCP_TVAL_MIN		(TCP_SLOW_HZ * 3)
					/* ���֤κǾ�ñ��	*/
#define TCP_TVAL_MAX_REXMT	(TCP_SLOW_HZ * 64)
					/* �����������		*/

/*
 *  �ʲ����ѿ����ͤϥޥ�������ꤹ�롣
 *
 *  tcp_maixidle   = tcp_keepcnt * tcp_keepintvl
 *                 = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL
 *  tcp_keepcnt    = TCP_TVAL_KEEP_COUNT
 *  tcp_keepintval = TCP_TVAL_KEEP_INTERVAL
 *
 */

/*
 *  ����¾�����
 */

#define TCP_MAX_REXMT_SHIFT	12	/* ����������		*/

/* TCP �������ͤη� */

typedef int16_t T_TCP_TIME;

/*
 *  �ؿ�
 */

extern void tcp_slow_timo (void *ignore);
extern void tcp_fast_timo (void *ignore);

extern T_TCP_TIME tcp_range_set (T_TCP_TIME value, T_TCP_TIME tvmin, T_TCP_TIME tvmax);

#endif	/* of #ifndef _TCP_TIMER_H_ */
