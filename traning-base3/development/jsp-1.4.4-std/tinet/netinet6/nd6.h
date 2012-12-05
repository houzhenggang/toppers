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
 *  @(#) $Id: nd6.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6.h,v 1.10 2002/04/19 04:46:23 suz Exp $	*/
/*	$KAME: nd6.h,v 1.76 2001/12/18 02:10:31 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef _ND6_H_
#define _ND6_H_

#ifdef SUPPORT_INET6

/*
 *  �ͥåȥ�����󥿥ե�������¤�Ρ�T_IFNET�ˤΥե饰
 */

#define ND6_IFF_IFDISABLED	UINT_C(0x01)	/* ���󥿥ե�������̵���ˤ��롣*/

/*
 *  ���٥���å��� 
 */

typedef struct t_llinfo_nd6 {
	T_IN6_ADDR	addr;
	T_NET_BUF	*hold;
	TMO		tmout;
	SYSTIM		expire;		/* [ms] ͭ�����֤��ڤ�����	*/
	T_IF_ADDR	ifaddr;
	uint8_t		state;
	uint8_t		asked;
	uint8_t		flags;
	} T_LLINFO_ND6;

/* ���٥���å���ξ��� */

#define ND6_LLINFO_FREE			0	/* ̤����		*/
#define ND6_LLINFO_NO_STATE		1	/* ����̤���		*/
#define ND6_LLINFO_INCOMPLETE		2	/* ̤���		*/
#define ND6_LLINFO_REACHABLE		3	/* ��ã��ǽ		*/
#define ND6_LLINFO_STALE		4	/* ��ã��ǽ����̤��ǧ	*/
#define ND6_LLINFO_DELAY		5	/* ��ã��ǽ���γ�ǧ�Ե�	*/
#define ND6_LLINFO_PROBE		6	/* ��ã��ǽ�����ǧ��	*/

#define ND6_IS_LLINFO_PROBREACH(n)	((n)->state > ND6_LLINFO_INCOMPLETE)

/* ���٥���å��������ӥå� */

#define ND6_LLIF_ROUTER			UINT_C(0x80)	/* �롼��		*/
#define ND6_LLIF_ASKED			UINT_C(0x40)	/* ���κѤ�		*/
#define ND6_LLIF_STATE_MASK		UINT_C(0x07)	/* ���֥ޥ���		*/

/* ����õ������å��塢ͭ�����֤���� */

#define ND6_SLOW_TMO			((60*60)/NET_TIMER_HZ)
							/* 1 [����]				*/
							/* ����õ������å��幹�������ॢ����	*/

#define ND6_MAX_DAD_TRY			15		/* ��ʣ���ɥ쥹���Фκ������		*/
#define ND6_MAX_MCAST_QUERY		3		/* �ޥ�����㥹�ȥ��ɥ쥹�����κ������	*/
#define ND6_MAX_UCAST_QUERY		3		/* ��˥��㥹�ȥ��ɥ쥹�����κ������	*/

#define ND6_INFINITE_LIFETIME		0xffffffff

#define ND6_GCOLLECTION_TIME		(60*60*24*SYSTIM_HZ)
							/* ���߽���������1 ��			*/
#define	ND6_DELAY_TIME			(5*SYSTIM_HZ)	/* ��ǧ�Ե��ٱ�				*/
#define ND6_FIRST_DAD_DELAY_TIME	(1*SYSTIM_HZ)	/* �ǽ�ν�ʣ���ɥ쥹���������ٱ�	*/
#define ND6_DAD_DELAY_TIME		(5*SYSTIM_HZ/10)
							/* ��ʣ���ɥ쥹���������ٱ�		*/

/* ����õ���ѥ����ޤ����� */

#define ND6_TIMER_TMO			((SYSTIM_HZ/NET_TIMER_CYCLE)/5)	/* 0.2[s] �ֳ�		*/

/*
 *  ��ã��ǽ���֤�ͭ������
 */

#define	ND6_DEF_REACHABLE_TIME		(30*SYSTIM_HZ)	/* ��ã��ǽ���֤�ͭ�����֤δ�����		*/
#define	ND6_MAX_REACHABLE_TIME		(60*60*SYSTIM_HZ)
							/* ��ã��ǽ���֤�ͭ�����֤δ�����		*/
#define	ND6_RECALC_REACHTM_INTERVAL	(60*60*2*SYSTIM_HZ)
							/* ��ã��ǽ���֤�ͭ�����ֺƷ׻��ֳ�	*/

#define	ND6_MIN_REACHTM_RAND_FACTOR	512		/* �Ǿ���������͡�1,024 * 0.5		*/

#if 1							/* �����ޡ��ε�ư�ֳ֤��θ����������û������	*/
#define	ND6_MAX_REACHTM_RAND_FACTOR	1484		/* �Ǿ���������͡�1,024 * 1.45			*/
#else
#define	ND6_MAX_REACHTM_RAND_FACTOR	1536		/* �Ǿ���������͡�1,024 * 1.5			*/
#endif

/* ��ã��ǽ���֤�ͭ�����֤η׻��ޥ��� */

#define ND6_CALC_REACH_TIME(b)		\
	 ((ND6_MIN_REACHTM_RAND_FACTOR * ((uint32_t)(b) >> 10)) + \
	  (net_rand() & ((ND6_MAX_REACHTM_RAND_FACTOR - ND6_MIN_REACHTM_RAND_FACTOR) * ((uint32_t)(b) >> 10))))

/*
 *  ����õ���������ֳ�
 */

#define ND6_DEF_RETRANS_TIME		(1*SYSTIM_HZ)

/*
 *  �롼�����Τˤ���ѹ�����뤳�Ȥ�������
 */

#if NUM_ND6_DEF_RTR_ENTRY > 0

/* �롼�����Τ����������ϡ����Τ��줿�� */

#define	ND6_REACHABLE_TIME		nd6_reachable_time
#define ND6_RETRANS_TIME		nd6_retrans_time

#else	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/* �롼�����Τ�������ʤ������ͤϴ����� */

#define	ND6_REACHABLE_TIME		ND6_DEF_REACHABLE_TIME
#define ND6_RETRANS_TIME		ND6_DEF_RETRANS_TIME

#endif	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/*
 *  �ǥ��ե���ȥ롼�����ꥹ��
 */

typedef struct t_def_router {
	T_IN6_ADDR	addr;
	SYSTIM		expire;		/* [ms] ͭ�����֤��ڤ�����	*/
	uint32_t	lifetime;	/* [ms] ͭ������			*/
	uint16_t	plistmap;	/* �ץ�ե��å����ޥå�		*/
	uint8_t		flags;		/* �롼�����ΤΥե饰		*/
	uint8_t		state;
	} T_DEF_ROUTER;

/* �ǥ��ե���ȥ롼�����ꥹ�Ȥξ��� */

#define ND6_DEF_RTR_BUSY		0xff	/* ������		*/

/* �ץ�ե��å����Υ���ǥå��� */

#define ND6_PREFIX_IX_INVALID		0xff

/*
 *  �ץ�ե��å������ꥹ��
 */

typedef struct t_nd6_prefix {
	T_IN6_ADDR	prefix;		/* �ץ�ե��å���		*/
	uint32_t	expire;		/* [s] ͭ�����֤��ڤ�����	*/
	uint32_t	preferred;	/* [s] �侩ͭ�����֤��ڤ�����	*/
	uint32_t	vltime;		/* [s] ͭ������			*/
	uint32_t	pltime;		/* [s] �侩ͭ������		*/
	uint16_t	routermap;	/* �롼���ޥå�			*/
	uint8_t		flags;		/* �ե饰			*/
	uint8_t		prefix_len;	/* �ץ�ե��å���Ĺ		*/
	} T_ND6_PREFIX;

/* �ե饰 */

#define ND6_PREFIX_FLAG_ONLINK		UINT_C(0x80)	/* �����󥯥ץ�ե��å���	*/
#define ND6_PREFIX_FLAG_AUTO		UINT_C(0x40)	/* ���ơ��ȥ쥹�����ɥ쥹��ư����*/

#define ND6_PREFIX_STATE_BUSY		UINT_C(0x01)	/* ������		*/
#define ND6_PREFIX_STATE_ONLINK		UINT_C(0x02)	/* �����󥯾���	*/
#define ND6_PREFIX_STATE_DETACHED	UINT_C(0x04)	/* ����Ѿ���	*/

/*
 *  �ѿ�
 */

extern SYSTIM	nd6_base_reachable_time;
extern SYSTIM	nd6_reachable_time;
extern SYSTIM	nd6_recalc_reachtm_interval;
extern SYSTIM	nd6_retrans_time;
extern uint8_t	ip6_defhlim;

/*
 *  �ؿ�
 */

extern void nd6_ifattach (T_IFNET *ifp);
extern void nd6_ns_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
                           T_IN6_ADDR *taddr, T_LLINFO_ND6 *ln, bool_t dad);
extern void nd6_na_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
                           T_IN6_ADDR *taddr, uint32_t flags, bool_t tlladdr);
extern void nd6_dad_start (T_IFNET *ifp, T_IN6_IFADDR *ia, int_t *tick);
extern ER nd6_output (T_IFNET *ifp, T_NET_BUF *output,
                      T_IN6_ADDR *dst, T_LLINFO_ND6 *ln, TMO tmout);
extern void nd6_na_input (T_NET_BUF *input, uint_t off);
extern void nd6_ns_input (T_NET_BUF *input, uint_t off);
extern void nd6_ra_input (T_NET_BUF *input, uint_t off);
extern ER nd6_storelladdr (T_IF_ADDR *out, T_IN6_ADDR *dst, T_IF_ADDR *ifa);
extern ER nd6_options (uint8_t *opt, void *nh, uint_t len);
extern T_LLINFO_ND6 *nd6_lookup (T_IN6_ADDR *addr, bool_t create);
extern ER nd6_output_hold (T_IFNET *ifp, T_LLINFO_ND6 *ln);
extern T_LLINFO_ND6 *nd6_cache_lladdr (T_IFNET *ifp, T_IN6_ADDR *from, 
                                       T_IF_ADDR *lladdr, uint8_t type, uint8_t code);
extern void nd6_defrtrlist_timer (void);
extern void nd6_prelist_timer (void);
extern void nd6_rtrsol_ctl (void);
extern T_IN6_ADDR *nd6_router_lookup (void);
extern T_DEF_ROUTER *nd6_defrtrlist_lookup (T_IN6_ADDR *src);
extern void nd6_defrtrlist_del (T_DEF_ROUTER *dr);
extern void nd6_timer (void);
extern const T_DEF_ROUTER *nd6_get_drl (uint_t *count);
extern const T_ND6_PREFIX *nd6_get_prl (void);
extern const T_LLINFO_ND6 *nd6_get_cache (void);
extern ER nd6_prefix_onlink (T_ND6_PREFIX *pr);
extern ER nd6_prefix_offlink (T_ND6_PREFIX *pr);
extern T_ND6_PREFIX *nd6_onlink_prefix_lookup (T_IN6_ADDR *dst);

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _ND6_H_ */
