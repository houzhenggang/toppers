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
 *  @(#) $Id: in.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
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
 *	@(#)in.h	8.3 (Berkeley) 1/3/94
 * $FreeBSD: src/sys/netinet/in.h,v 1.38.2.3 1999/08/29 16:29:34 peter Exp $
 */
 
#ifndef _IN_H_
#define _IN_H_

#include <tinet_kernel_defs.h>

#include <netinet6/in6.h>

/*
 *  TINET �ΥС���������
 */

#define TINET_PRVER		UINT_C(0x1052)	/* TINET �ΥС�������ֹ� */

/*
 *  ���󥿡��ͥåȥ����ƥ�������RFC790 ����
 */

/*
 *  �ץ�ȥ��� (RFC1700)
 */

#define IPPROTO_IP		UINT_C(0)	/* IP �Υ��ߡ�				*/
#define IPPROTO_HOPOPTS		UINT_C(0)	/* IPv6 ����� (Hop-by-Hop) ���ץ����	*/
#define IPPROTO_ICMP		UINT_C(1)	/* ICMP					*/
#define IPPROTO_TCP		UINT_C(6)	/* TCP					*/
#define IPPROTO_UDP		UINT_C(17)	/* UDP					*/
#define IPPROTO_IPV6		UINT_C(41)	/* IPv6					*/
#define IPPROTO_ROUTING		UINT_C(43)	/* ��ϩ���楪�ץ����			*/
#define IPPROTO_FRAGMENT	UINT_C(44)	/* ���Ҳ����ץ����			*/
#define IPPROTO_RSVP		UINT_C(46)	/* RSVP					*/
#define IPPROTO_ESP		UINT_C(50)	/* IPv6 �Ź沽���ץ����		*/
#define IPPROTO_AH		UINT_C(51)	/* IPv6 ǧ�ڥ��ץ����			*/
#define IPPROTO_ICMPV6		UINT_C(58)	/* ICMPv6				*/
#define IPPROTO_NONE		UINT_C(59)	/* IPv6 ���إå�̵��			*/
#define IPPROTO_DSTOPTS		UINT_C(60)	/* IPv6 �������ץ����			*/
#define IPPROTO_IPCOMP		UINT_C(108)	/* �ڥ����ɰ���			*/
#define IPPROTO_DONE		UINT_C(257)	/* IPv6 �Ǿ�̥ץ�ȥ������Ͻ�λ	*/

/*
 *  IPv4 ���ɥ쥹
 */

/* �������� */

#ifndef T_IN4_ADDR_DEFINED

typedef uint32_t T_IN4_ADDR;

#define T_IN4_ADDR_DEFINED

#endif	/* of #ifndef T_IN4_ADDR_DEFINED */

/*
 *  ITRON TCP/IPv4 ���ɥ쥹/�ݡ����ֹ�����
 */

typedef struct t_ipv4ep {
	uint32_t	ipaddr;		/* IPv4 ���ɥ쥹	*/
	uint16_t	portno;		/* �ݡ����ֹ�		*/
	} T_IPV4EP;

/*
 *  ���ɥ쥹/�ݡ��Ȥ�Ĺ��
 */

#define IPV4_ADDR_LEN		4
#define PORT_NUM_LEN		2

/*
 *  �ݡ����ֹ�����
 */

#define TCP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP ɸ��	*/
#define UDP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP ɸ��	*/

#define TCP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known ��λ�ֹ�	*/
#define TCP_PORT_FIRST_AUTO		UINT_C(1024)	/* ��ư������Ƴ����ֹ�	*/
#define TCP_PORT_LAST_AUTO		UINT_C(4999)	/* ��ư������ƽ�λ�ֹ�	*/

#define UDP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known ��λ�ֹ�	*/
#define UDP_PORT_FIRST_AUTO		UINT_C(1024)	/* ��ư������Ƴ����ֹ�	*/
#define UDP_PORT_LAST_AUTO		UINT_C(4999)	/* ��ư������ƽ�λ�ֹ�	*/

/*
 *  IP ���ɥ쥹�����
 */

#define IPV4_ADDRANY		ULONG_C(0x00000000)	/* ITRON TCP/IP ɸ��	*/

#define IPV4_ADDR_LOOPBACK	ULONG_C(0x7f000001)
#define IPV4_ADDR_LOOPBACK_MASK	IPV4_CLASS_A_MASK
#define IPV4_ADDR_BROADCAST	ULONG_C(0xffffffff)

#define IPV4_CLASS_A(i)		(((i) & ULONG_C(0x80000000)) == 0)
#define IPV4_CLASS_A_NET	ULONG_C(0xff000000)
#define IPV4_CLASS_A_MASK	ULONG_C(0xff000000)
#define IPV4_CLASS_A_HOST	ULONG_C(0x00ffffff)

#define IPV4_CLASS_B(i)		(((i) & ULONG_C(0xc0000000)) == ULONG_C(0x80000000))
#define IPV4_CLASS_B_NET	ULONG_C(0xffff0000)
#define IPV4_CLASS_B_MASK	ULONG_C(0xffff0000)
#define IPV4_CLASS_B_HOST	ULONG_C(0x0000ffff)

#define IPV4_CLASS_C(i)		(((i) & ULONG_C(0xe0000000)) == ULONG_C(0xc0000000))
#define IPV4_CLASS_C_NET	ULONG_C(0xffffff00)
#define IPV4_CLASS_C_MASK	ULONG_C(0xffffff00)
#define IPV4_CLASS_C_HOST	ULONG_C(0x000000ff)

#define IPV4_CLASS_D(i)		(((i) & ULONG_C(0xf0000000)) == ULONG_C(0xe0000000))

#define IN4_IS_ADDR_MULTICAST(i)	IPV4_CLASS_D(i)

#define MAKE_IPV4_LOCAL_BROADCAST(i)	(IPV4_CLASS_A(i)?((i)|IPV4_CLASS_A_HOST):\
					 IPV4_CLASS_B(i)?((i)|IPV4_CLASS_B_HOST):\
					 IPV4_CLASS_C(i)?((i)|IPV4_CLASS_C_HOST):\
					 IPV4_ADDR_BROADCAST)

#define MAKE_IPV4_LOCAL_MASK(i)		(IPV4_CLASS_A(i)?IPV4_CLASS_A_MASK:\
					 IPV4_CLASS_B(i)?IPV4_CLASS_B_MASK:\
					 IPV4_CLASS_C(i)?IPV4_CLASS_C_MASK:\
					 IPV4_ADDRANY)

#define MAKE_IPV4_ADDR(a,b,c,d)		((T_IN4_ADDR)(((uint32_t)(a)<<24)|((uint32_t)(b)<<16)|((uint32_t)(c)<<8)|(d)))

/*
 *  ưŪ������ TCP �̿�ü��
 */

typedef struct t_tcp_ccep {
	/* ɸ�� */
	ATR		cepatr;		/* �̿�ü��°��			*/
	void		*sbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		sbufsz;		/* �����ѥ�����ɥХåե�������	*/
	void		*rbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		rbufsz;		/* �����ѥ�����ɥХåե�������	*/
	FP		callback;	/* ������Хå�			*/
	/* ������¸ */
	} T_TCP_CCEP;

/*
 *  ưŪ������ TCP ���ո�
 */

#if defined(SUPPORT_INET4)

typedef struct t_tcp_crep {
	/* ɸ�� */
	ATR		repatr;		/* ���ո�°��		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹	*/
	/* ������¸ */
	} T_TCP_CREP;

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  ưŪ������ UDP �̿�ü��
 */

#if defined(SUPPORT_INET4)

typedef struct t_udp_ccep {
	/* ɸ�� */
	ATR		cepatr;		/* UDP �̿�ü��°��		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	FP		callback;	/* ������Хå��ؿ�		*/
	/* ������¸ */
	} T_UDP_CCEP;

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ���
 */

#if defined(SUPPORT_INET4)

#define T_IN_ADDR			T_IN4_ADDR
#define T_IPEP				T_IPV4EP
#define IP_ADDRANY			IPV4_ADDRANY

#define IN_ARE_ADDR_EQUAL(n,h)		(*(n)==*(h))
#define IN_ARE_NET_ADDR_EQUAL(n,h)	(ntohl(*(n))==*(h))
#define IN_COPY_TO_NET(d,s)		(*(d)=htonl(*(s)))
#define IN_COPY_TO_HOST(d,s)		(*(d)=ntohl(*(s)))
#define IN_IS_ADDR_MULTICAST(a)		IN4_IS_ADDR_MULTICAST(*(a))
#define IN_IS_NET_ADDR_MULTICAST(a)	IN4_IS_ADDR_MULTICAST(ntohl(*(a)))
#define IN_IS_ADDR_ANY(a)		(*(a)==IPV4_ADDRANY)

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  TINET �ȼ� API
 */

extern const char *in_strtfn (FN fncd);

#if defined(SUPPORT_INET4)

extern ER in4_add_ifaddr (T_IN4_ADDR addr, T_IN4_ADDR mask);
extern ER in4_add_route (int_t index, T_IN4_ADDR target,
                                      T_IN4_ADDR mask, T_IN4_ADDR gateway);
extern char *ip2str (char *buf, const T_IN4_ADDR *p_ipaddr);
extern const T_IN4_ADDR *in4_get_ifaddr (int_t index);

#endif	/* of #if defined(SUPPORT_INET4) */

#endif	/* of #ifndef _IN_H_ */
