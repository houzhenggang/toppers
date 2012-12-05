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
 *  @(#) $Id: in6.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/in6.h,v 1.7.2.4 2001/07/04 09:45:23 ume Exp $	*/
/*	$KAME: in6.h,v 1.89 2001/05/27 13:28:35 itojun Exp $	*/

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
 */
 
#ifndef _IN6_H_
#define _IN6_H_

/*
 *  IPv6 ���ɥ쥹
 */

struct t_in6_addr {
	union {
		uint8_t		__u6_addr8[16];
		uint16_t	__u6_addr16[8];
		uint32_t	__u6_addr32[4];
		} __u6_addr;
	};

#define s6_addr		__u6_addr.__u6_addr8
#define s6_addr8	__u6_addr.__u6_addr8
#define s6_addr16	__u6_addr.__u6_addr16
#define s6_addr32	__u6_addr.__u6_addr32

#ifndef T_IN6_ADDR_DEFINED

typedef struct t_in6_addr T_IN6_ADDR;

#define T_IN6_ADDR_DEFINED

#endif	/* of #ifndef T_IN6_ADDR_DEFINED */

/*
 *  IPv6 ���ɥ쥹�ν�����ǡ���
 */

#define IPV6_ADDR_UNSPECIFIED_INIT	\
	{{{ UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00) }}}

#define IPV6_ADDR_LINKLOCAL_ALLNODES_INIT	\
	{{{ UINT_C(0xff), UINT_C(0x02), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x01) }}}

#define IPV6_ADDR_LINKLOCAL_ALLROUTERS_INIT	\
	{{{ UINT_C(0xff), UINT_C(0x02), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), \
	    UINT_C(0x00), UINT_C(0x00), UINT_C(0x00), UINT_C(0x02) }}}

/*
 *  ���ɥ쥹�����
 */

#ifdef SIL_ENDIAN

#if SIL_ENDIAN == SIL_ENDIAN_BIG

#define IPV6_ADDR_INT32_ONE		ULONG_C(0x00000001)
#define IPV6_ADDR_INT32_TWO		ULONG_C(0x00000002)
#define IPV6_ADDR_INT32_0000FFFF	ULONG_C(0x0000ffff)
#define IPV6_ADDR_INT32_MNL		ULONG_C(0xff010000)
#define IPV6_ADDR_INT32_MLL		ULONG_C(0xff020000)
#define IPV6_ADDR_INT32_ULL		ULONG_C(0xfe800000)
#define IPV6_ADDR_INT16_ULL		UINT_C(0xfe80)
#define IPV6_ADDR_INT16_USL		UINT_C(0xfec0)
#define IPV6_ADDR_INT16_MLL		UINT_C(0xff02)

#elif SIL_ENDIAN == SIL_ENDIAN_LITTLE

#define IPV6_ADDR_INT32_ONE		ULONG_C(0x01000000)
#define IPV6_ADDR_INT32_TWO		ULONG_C(0x02000000)
#define IPV6_ADDR_INT32_0000FFFF	ULONG_C(0xffff0000)
#define IPV6_ADDR_INT32_MNL		ULONG_C(0x000001ff)
#define IPV6_ADDR_INT32_MLL		ULONG_C(0x000002ff)
#define IPV6_ADDR_INT32_ULL		ULONG_C(0x000080fe)
#define IPV6_ADDR_INT16_ULL		UINT_C(0x80fe)
#define IPV6_ADDR_INT16_USL		UINT_C(0xc0fe)
#define IPV6_ADDR_INT16_MLL		UINT_C(0x02ff)

#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

#endif	/* of #ifdef SIL_ENDIAN */

/*
 *  ���̤ʥ��ɥ쥹�Υ����å�
 */

/* ̵���� */

#define IN6_IS_ADDR_UNSPECIFIED(a)	\
	(memcmp((void *)(a), (void *)&in6_addr_unspecified, sizeof(T_IN6_ADDR)) == 0)

/* �롼�ץХå� */

#define IN6_IS_ADDR_LOOPBACK(a)		\
	(memcmp((void *)(a), (void *)&in6_addr_unspecified, sizeof(T_IN6_ADDR) - 1) == 0 && \
	 (a)->s6_addr8[15] == 0x01)

/* IPv4 �ߴ� */

#define IN6_IS_ADDR_V4COMPAT(a)		\
	(memcmp((void *)(a), (void *)&in6_addr_unspecified, sizeof(T_IN6_ADDR) - 4) == 0 && \
	 (a)->s6_addr32[3] > IPV6_ADDR_INT32_ONE)

/* IPv4 �ޥå� */

#define IN6_IS_ADDR_V4MAPPED(a)		\
	(((a)->s6_addr32[0] == ULONG_C(0x00000000)) && \
	 ((a)->s6_addr32[1] == ULONG_C(0x00000000)) && \
	 ((a)->s6_addr32[2] == IPV6_ADDR_INT32_0000FFFF))

/*
 *  �������� ID
 */

#define IPV6_ADDR_SCOPE_NODELOCAL	UINT_C(0x01)
#define IPV6_ADDR_SCOPE_LINKLOCAL	UINT_C(0x02)
#define IPV6_ADDR_SCOPE_SITELOCAL	UINT_C(0x05)
#define IPV6_ADDR_SCOPE_ORGLOCAL	UINT_C(0x08)
#define IPV6_ADDR_SCOPE_GLOBAL		UINT_C(0x0e)

/*
 *  ��˥��㥹�ȡ���������
 *
 *  ���: ��� 10 �ӥåȤΤߥ����å����ʤ���Фʤ�ʤ���RFC2373 ����
 */

/* ��󥯥����� */

#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr8[0] == UINT_C(0xfe)) && (((a)->s6_addr8[1] & UINT_C(0xc0)) == UINT_C(0x80)))

/* �����ȥ����� */

#define IN6_IS_ADDR_SITELOCAL(a)	\
	(((a)->s6_addr8[0] == UINT_C(0xfe)) && (((a)->s6_addr8[1] & UINT_C(0xc0)) == UINT_C(0xc0)))

/* �����ǽ��˥��㥹�� (�����Х�) */

#define IN6_IS_ADDR_AGGREGATE_UNICAST(a)	\
	(((a)->s6_addr8[0] & UINT_C(0xe0)) == UINT_C(0x20))

/*
 *  �ޥ�����㥹��
 */

#define IN6_IS_ADDR_MULTICAST(a)	((a)->s6_addr8[0] == UINT_C(0xff))

/* �����ޥ�����㥹�� */

#define IN6_IS_ADDR_NS_MULTICAST(a)	\
	(((a)->s6_addr32[0] == IPV6_ADDR_INT32_MLL) && \
	 ((a)->s6_addr32[1] == ULONG_C(0x00000000)) && \
	 ((a)->s6_addr32[2] == IPV6_ADDR_INT32_ONE) && \
	 ((a)->s6_addr8[12] == UINT_C(0xff)))

/*
 *  Ʊ��Υ����å�
 */

#define IN6_ARE_ADDR_EQUAL(a,b)		(memcmp((a), (b), sizeof(T_IN6_ADDR)) == 0)

/*
 *  ��ϩ���������
 */

#define IPV6_RTHDR_TYPE_0		UINT_C(0)	/* IPv6 ��ϩ����إå������� 0	*/

/*
 *  �����ͤ�������
 */

#define IPV6_DEFAULT_MULTICAST_HOPS	1	/* �ޥ�����㥹�Ȼ��Υۥåץ�ߥåȤε����� */

/*
 *  ITRON TCP/IPv6 ���ɥ쥹/�ݡ����ֹ�����
 */

typedef struct t_ipv6ep {
	T_IN6_ADDR	ipaddr;		/* IPv6 ���ɥ쥹	*/
	uint16_t	portno;		/* �ݡ����ֹ�	*/
	} T_IPV6EP;

/*
 *  ITRON/TCP/IP �� IP ���ɥ쥹�����
 */

#define IPV6_ADDRANY		IPV6_ADDR_UNSPECIFIED_INIT

/*
 *  ưŪ������ IPv6 TCP ���ո�
 */

typedef struct t_tcp6_crep {
	/* ɸ�� */
	ATR		repatr;		/* ���ո�°��		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹	*/
	/* ������¸ */
	} T_TCP6_CREP;

#if defined(SUPPORT_INET6)
#define T_TCP_CREP	T_TCP6_CREP
#endif

/*
 *  ưŪ������ IPv6 UDP �̿�ü��
 */

typedef struct t_udp6_ccep {
	/* ɸ�� */
	ATR		cepatr;		/* UDP �̿�ü��°��		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	FP		callback;	/* ������Хå��ؿ�		*/
	/* ������¸ */
	} T_UDP6_CCEP;

#if defined(SUPPORT_INET6)
#define T_UDP_CCEP	T_UDP6_CCEP
#endif

/*
 *  IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ���
 */

#if defined(SUPPORT_INET6)

#define T_IN_ADDR			T_IN6_ADDR
#define T_IPEP				T_IPV6EP
#define IP_ADDRANY			IPV6_ADDRANY

#define IN_ARE_ADDR_EQUAL(n,h)		IN6_ARE_ADDR_EQUAL(n,h)
#define IN_ARE_NET_ADDR_EQUAL(n,h)	IN6_ARE_ADDR_EQUAL(n,h)
#define IN_COPY_TO_NET(d,s)		memcpy(d,s,sizeof(T_IN6_ADDR))
#define IN_COPY_TO_HOST(d,s)		memcpy(d,s,sizeof(T_IN6_ADDR))
#define IN_IS_ADDR_MULTICAST(a)		IN6_IS_ADDR_MULTICAST(a)
#define IN_IS_NET_ADDR_MULTICAST(a)	IN6_IS_ADDR_MULTICAST(a)
#define IN_IS_ADDR_ANY(a)		IN6_IS_ADDR_UNSPECIFIED(a)

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  ��������
 */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

/*
 *  �����ѿ�
 */

extern T_IN6_ADDR in6_addr_unspecified;
extern T_IN6_ADDR in6_addr_linklocal_allnodes;
extern T_IN6_ADDR in6_addr_linklocal_allrouters;

#define ipv6_addrany	in6_addr_unspecified

/*
 *  TINET �ȼ� API
 */

extern char *ipv62str (char *buf, const T_IN6_ADDR *p_ip6addr);
extern ER_UINT in6_get_maxnum_ifaddr (void);
extern const T_IN6_ADDR *in6_get_ifaddr (int_t index);

#endif	/* of #ifndef _IN6_H_ */
