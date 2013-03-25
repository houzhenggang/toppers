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
 *  @(#) $Id: in6_var.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/in6_var.h,v 1.3.2.2 2001/07/03 11:01:52 ume Exp $	*/
/*	$KAME: in6_var.h,v 1.56 2001/03/29 05:34:31 itojun Exp $	*/

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
 * Copyright (c) 1985, 1986, 1993
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
 *	@(#)in_var.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _IN6_VAR_H_
#define _IN6_VAR_H_

#ifdef SUPPORT_INET6

/*
 *  ���ɥ쥹ͭ�����ֹ�¤��
 */

typedef struct in6_addr_lifetime {

	/*
	 * expire �� perferred �ϡ������ƥब��ư���Ƥ���ηв����
	 */
	uint32_t	expire;		/* ͭ�����֤��ڤ����� [s]	*/
	uint32_t	preferred;	/* �侩ͭ�����֤��ڤ����� [s]	*/

	/*
	 * vltime �� pltime �ϡ��ɲ�/�ѹ����Ƥ�������л���
	 */
	uint32_t	vltime;		/* ͭ������ [ms]			*/
	uint32_t	pltime;		/* �侩ͭ������ [ms]		*/
	} T_IN6_ADDR_LIFETIME;

/*
 *  ���󥿥ե��������ɥ쥹��¤��
 */

typedef struct t_in6_ifaddr {
	T_IN6_ADDR		addr;		/* IPv6 ���ɥ쥹		*/
	T_IN6_ADDR_LIFETIME	lifetime;	/* ͭ������		*/
	uint8_t			flags;		/* �ե饰		*/
	uint8_t			prefix_len;	/* �ץ�ե��å���Ĺ	*/
	uint8_t			router_index;	/* �롼������ǥå���	*/
	uint8_t			prefix_index;	/* �ץ�ե��å�������ǥå���	*/
	uint8_t			na_icount;	/* ��ʣ���ɥ쥹���� (DAD) ���Τ����ϲ��	*/
	uint8_t			ns_icount;	/* ��ʣ���ɥ쥹���� (DAD) ���������ϲ��	*/
	uint8_t			ns_ocount;	/* ��ʣ���ɥ쥹���� (DAD) �����ν��ϲ��	*/
	} T_IN6_IFADDR;

/*
 *  ���ɥ쥹���֥ե饰
 */

#define IN6_IFF_ANYCAST		UINT_C(0x01)	/* ���ˡ����㥹��	*/
#define IN6_IFF_DEFINED		UINT_C(0x02)	/* ����Ѥ�		*/
#define IN6_IFF_TENTATIVE	UINT_C(0x04)	/* ��ʣ������		*/
#define IN6_IFF_DUPLICATED	UINT_C(0x08)	/* ��ʣ�򸡽Ф���	*/
#define IN6_IFF_DEPRECATED	UINT_C(0x10)	/* ��侩		*/
#define IN6_IFF_NODAD		UINT_C(0x20)	/* ��ʣ��������		*/
#define IN6_IFF_AUTOCONF	UINT_C(0x40)	/* ��ư���ꤵ�줿	*/
#define IN6_IFF_DETACHED	UINT_C(0x80)	/* �����		*/

/*
 *  ���ɥ쥹��ͭ���������å�
 */

#define IFA6_IS_READY(a)	(((a)->flags & IN6_IFF_DEFINED) != 0 && \
				 ((a)->flags & (IN6_IFF_TENTATIVE|IN6_IFF_DUPLICATED|IN6_IFF_DETACHED)) == 0)
#define IFA6_IS_NOTREADY(a)	(((a)->flags & IN6_IFF_DEFINED) == 0 ||	\
				 ((a)->flags & (IN6_IFF_TENTATIVE|IN6_IFF_DUPLICATED|IN6_IFF_DETACHED)) != 0)

#define IFA6_IS_DEPRECATED(a,n)	\
	((a)->lifetime.preferred != 0 && (int32_t)((a)->lifetime.preferred - ((n / SYSTIM_HZ))) < 0)

#define IFA6_IS_INVALID(a,n)	\
	((a)->lifetime.expire != 0 && (int32_t)((a)->lifetime.expire - ((n / SYSTIM_HZ))) < 0)

/*
 *  �롼���Υ���ǥå���
 */

#define IN6_RTR_IX_UNREACH	0xff

/*
 *  ������
 */

#define IP6_HDR_NEST_LIMIT	50	/* IPv6 �إå��Υͥ���������	*/

/*
 *  ���ɥ쥹��������Υ���ǥå���
 */

#define IPV6_IFADDR_IX_LINKLOCAL	0
#define IPV6_IFADDR_IX_INVALID		0xff

/*
 *  IPv6 �ޥ�����㥹�ȥ��ɥ쥹����Υ���ǥå���
 */

#define IPV6_MADDR_IX_SOL_NODE		0	/* �����ޥ�����㥹�ȡ����ɥ쥹			*/
#define IPV6_MADDR_IX_LL_ALL_NODE	1	/* ���Ρ��ɡ���󥯥����롦�ޥ�����㥹�ȥ��ɥ쥹	*/
#define IPV6_MADDR_IX_EXTRA		2

#define MAX_IN6_MADDR_CNT		MAX_IF_MADDR_CNT
						/* IPv6 �ޥ�����㥹�ȥ��ɥ쥹����κ��祵����	*/

/*
 *  �롼�ƥ��󥰤�����
 */

/* �롼�ƥ���ɽ����ȥ깽¤�� */

typedef struct t_in6_rtentry {
	T_IN6_ADDR	target;		/* ��ɸ�ͥåȥ�����ɥ쥹	*/
	T_IN6_ADDR	gateway;	/* �����ȥ������� IP ���ɥ쥹	*/
	uint32_t	expire;		/* ͭ�����֤��ڤ����� [s]	*/
	uint8_t		flags;		/* �ե饰			*/
	uint8_t		prefix_len;	/* �ץ�ե��å���Ĺ		*/
	} T_IN6_RTENTRY;

/*
 *  �ۥ��ȥ���å���
 */

/* �ۥ��ȥ���å��幽¤�� */

typedef struct t_in6_hostcache_entry {
	T_IN6_ADDR	dst;		/* ��ɸ�ͥåȥ�����ɥ쥹	*/
	uint32_t	expire;		/* ͭ�����֤��ڤ����� [s]	*/
	uint32_t	mtu;		/* Path MTU			*/
	} T_IN6_HOSTCACHE_ENTRY;

#define IN6_HOSTCACHE_EXPIRE	(60*60*SYSTIM_HZ)	/* ͭ������	*/
#define IN6_HOSTCACHE_PRUNE	(5*60*SYSTIM_HZ)	/* �����ֳ�	*/
#define IN6_HOSTCACHE_INCREASE	(10*60*SYSTIM_HZ)	/* ���ä�������ݸ����	*/

#define IN6_IS_HOSTCACHE_FREE(e)	IN6_IS_ADDR_UNSPECIFIED(&((e)->dst))
#define IN6_IS_HOSTCACHE_BUSY(e)	(!IN6_IS_HOSTCACHE_FREE(e))

/*
 *  IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ���
 */

#define IN_SET_HEADER(nbuf,len,dst,src,next,hlim)	\
					in6_set_header(nbuf,len,dst,src,next,hlim)
#define IN_GET_DATAGRAM(nbuf,len,maxlen,dst,src,next,hlim,nbatr,tmout)	\
					in6_get_datagram(nbuf,len,maxlen,dst,src,next,hlim,nbatr,tmout)
#define IN_CKSUM(nbuf,proto,off,len)	in6_cksum(nbuf,proto,off,len)
#define IN_IS_DSTADDR_ACCEPT(myaddr,dstaddr)			\
					in6_is_dstaddr_accept(myaddr,dstaddr)
#define IN_IFAWITHIFP(ifp,dst)		in6_ifawithifp(ifp,dst)
#define T_IN_IFADDR			T_IN6_IFADDR
#define T_IN_RTENTRY			T_IN6_RTENTRY

/*
 *  ��������
 */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

/*
 *  �ѿ�
 */

extern uint32_t linkmtu;

/*
 *  �ؿ�
 */

extern void in6_ifainit (void);
extern int_t in6_addr2maix (T_IN6_ADDR *addr);
extern ER in6_update_ifa (T_IFNET *ifp, T_IN6_IFADDR *ia, T_IN6_ADDR *addr,
                          uint_t prefix_len, uint32_t vltime, uint32_t pltime,
                          int_t router_index, int_t prefix_index, uint_t flags);
extern ER in6_set_header (T_NET_BUF *nbuf, uint_t len,
                          T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                          uint8_t next, uint8_t hlim);
extern ER in6_get_datagram (T_NET_BUF **nbuf, uint_t len, uint_t maxlen,
                            T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                            uint8_t next, uint8_t hlim, ATR nbatr, TMO tmout);
extern uint16_t in6_cksum (T_NET_BUF *nbuf, uint8_t proto, uint_t off, uint_t len);
extern T_IN6_IFADDR *in6ifa_ifpwithix (T_IFNET *ifp, int_t ix);
extern T_IN6_IFADDR *in6ifa_ifpwithrtrix (T_IFNET *ifp, int_t rtr_ix);
extern T_IN6_IFADDR *in6_ifawithifp (T_IFNET *ifp, T_IN6_ADDR *dst);
extern void ip6_input (T_NET_BUF *input);
extern T_IN6_IFADDR *in6_lookup_ifaddr (T_IFNET *ifp, T_IN6_ADDR *addr);
extern bool_t in6_lookup_multi (T_IFNET *ifp, T_IN6_ADDR *maddr);
extern bool_t in6_is_dstaddr_accept (T_IN6_ADDR *myaddr, T_IN6_ADDR *dstaddr);
extern T_IN6_ADDR *in6_rtalloc (T_IFNET *ifp, T_IN6_ADDR *dst);
extern int_t in6_if2idlen (T_IFNET *ifp);
extern int_t in6_addr2ifaix (T_IN6_ADDR *addr);
extern void in6_plen2pmask (T_IN6_ADDR *mask, uint_t prefix_len);
extern bool_t in6_are_prefix_equal (T_IN6_ADDR *addr, T_IN6_ADDR *prefix,
                                  uint_t prefix_len);
extern void in6_ifaddr_timer (T_IFNET *ifp);
extern T_IN6_RTENTRY *in6_gateway_lookup (T_IN6_ADDR *src);
extern void in6_rtredirect (T_IN6_ADDR *gateway, T_IN6_ADDR *target,
                            uint_t prefix_len, uint8_t flags, uint32_t tmo);
extern void in6_init (void);
extern void in6_if_up (T_IFNET *ifp);
extern void in6_hostcache_update (T_IN6_ADDR *dst, uint32_t mtu);
extern uint32_t in6_hostcache_getmtu (T_IN6_ADDR *dst);
extern uint_t in6_addrscope (T_IN6_ADDR *addr);
extern const T_NET_BUF**ip6_get_frag_queue (void);

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IN6_VAR_H_ */
