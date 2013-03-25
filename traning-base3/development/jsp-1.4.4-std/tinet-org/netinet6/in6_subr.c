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
 *  @(#) $Id: in6_subr.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

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
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_var.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/ah.h>
#include <netinet6/nd6.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  �ۥ��ȥ���å���
 */

static T_IN6_HOSTCACHE_ENTRY in6_hostcache[NUM_IN6_HOSTCACHE_ENTRY];

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

/*
 *  in6_lookup_ifaddr -- �ͥåȥ�����󥿥ե������˳�����Ƥ��Ƥ��륢�ɥ쥹��õ�����롣
 */

T_IN6_IFADDR *
in6_lookup_ifaddr (T_IFNET *ifp, T_IN6_ADDR *addr)
{
	int_t ix;

	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		if ((ifp->in_ifaddrs[ix].flags & IN6_IFF_DEFINED) &&
		    IN6_ARE_ADDR_EQUAL(addr, &ifp->in_ifaddrs[ix].addr))
			return &ifp->in_ifaddrs[ix];
		}
	return NULL;
	}

/*
 *  in6_lookup_multi -- �ͥåȥ�����󥿥ե������Υޥ�����㥹�ȥ��ɥ쥹�򸡺����롣
 */

bool_t
in6_lookup_multi (T_IFNET *ifp, T_IN6_ADDR *maddr)
{
	int_t ix;

	for (ix = MAX_IN6_MADDR_CNT; ix -- > 0; )
		if (IN6_ARE_ADDR_EQUAL(maddr, &ifp->in_maddrs[ix]))
			return true;
	return false;
	}

/*
 *  in6_set_header -- IPv6 �إå������ꤹ�롣
 */

ER
in6_set_header (T_NET_BUF *nbuf, uint_t len,
                T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                uint8_t next, uint8_t hlim)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IP6_HDR	*ip6h;
	T_IN6_IFADDR	*ia;

	/*
	 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
	 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
	 */
	if (srcaddr == NULL || !IN6_IS_ADDR_UNSPECIFIED(srcaddr))
		;
	else if ((ia = in6_ifawithifp(ifp, dstaddr)) == NULL)
		return E_SYS;
	else
		srcaddr = &ia->addr;

	/* IPv6 �إå������ꤹ�롣*/
	ip6h		= GET_IP6_HDR(nbuf);
	ip6h->vcf	= htonl(IP6_MAKE_VCF(IPV6_VERSION, 0));
	ip6h->plen	= htons(len);
	ip6h->next	= next;
	ip6h->hlim	= hlim;

	if (dstaddr == NULL)
		memset(&ip6h->dst, 0, sizeof(T_IN6_ADDR));
	else
		ip6h->dst = *dstaddr;

	if (srcaddr == NULL)
		memset(&ip6h->src, 0, sizeof(T_IN6_ADDR));
	else
		ip6h->src = *srcaddr;

	return E_OK;
	}

/*
 *  in6_get_datagram -- IPv6 �ǡ�����������������إå������ꤹ�롣
 */

ER
in6_get_datagram (T_NET_BUF **nbuf, uint_t len, uint_t maxlen,
                  T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                  uint8_t next, uint8_t hlim, ATR nbatr, TMO tmout)
{
	ER		error;
	uint_t		align;

	/* �ǡ���Ĺ�� 4 �����ƥåȶ�����Ĵ�����롣	*/
	align = (len + 3) >> 2 << 2;

	/* �ͥåȥ���Хåե���������롣	*/
	if ((error = tget_net_buf_ex(nbuf, IF_IP6_HDR_SIZE + align,
	                                   IF_IP6_HDR_SIZE + maxlen, nbatr, tmout)) != E_OK)
		return error;

	/*
	 *  ����礭�ʥ������Υͥåȥ���Хåե������������Τ�Ĺ����Ĵ�����롣
	 *  ��꾮���ʥ������Υͥåȥ���Хåե��γ����ϡ�����������ɥХåե���
	 *  �ʥ��ԡ���ǽ�ǻ��Ѥ��졢�ºݤ���������ޤǡ��ǡ����������Ϸ���Ǥ��ʤ���
	 */
	if ((nbatr & NBA_SEARCH_ASCENT) != 0)
		(*nbuf)->len = IF_IP6_HDR_SIZE + len;

	/* IPv6 �إå������ꤹ�롣*/
	if ((error = in6_set_header(*nbuf, len, dstaddr, srcaddr, next, hlim)) != E_OK)
		return error;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset(GET_IP6_SDU(*nbuf) + len, 0, align - len);

	return E_OK;
	}

/*
 *  in6_get_maxnum_ifaddr -- ���󥿥ե������������ǽ�ʺ��祢�ɥ쥹�����֤���
 */

ER_UINT
in6_get_maxnum_ifaddr (void)
{
	return NUM_IN6_IFADDR_ENTRY;
	}

/*
 *  in6_get_ifaddr -- ���󥿥ե����������ꤵ��Ƥ��륢�ɥ쥹���֤���
 */

const T_IN6_ADDR *
in6_get_ifaddr (int_t index)
{
	T_IFNET		*ifp = IF_GET_IFNET();

	if (index < NUM_IN6_IFADDR_ENTRY &&
	    (ifp->in_ifaddrs[index].flags & IN6_IFF_DEFINED))
		return &ifp->in_ifaddrs[index].addr;
	else
		return NULL;
	}

/*
 *  ipv62str -- IPv6 ���ɥ쥹��ʸ������Ѵ����롣
 */

char *
ipv62str (char *buf, const T_IN6_ADDR *p_ip6addr)
{
	static char	addr_sbuf[NUM_IPV6ADDR_STR_BUFF][sizeof("0123:4567:89ab:cdef:0123:4567:89ab:cdef")];
	static int_t	bix = NUM_IPV6ADDR_STR_BUFF;

	bool_t	omit = false, zero = false;
	char	*start;
	int_t	ix;

	if (buf == NULL) {
		syscall(wai_sem(SEM_IP2STR_BUFF_LOCK));
		buf = addr_sbuf[-- bix];
		if (bix <= 0)
			bix = NUM_IPV6ADDR_STR_BUFF;
		syscall(sig_sem(SEM_IP2STR_BUFF_LOCK));
		}

	start = buf;
	if (p_ip6addr == NULL) {
		*buf ++ = ':';
		*buf ++ = ':';
		}
	else {
		for (ix = 0; ix < sizeof(T_IN6_ADDR) / 2; ix ++) {
			if (omit) {
				buf += convert_hexdigit(buf, ntohs(p_ip6addr->s6_addr16[ix]), 16, 0, ' '); 
				if (ix < 7)
					*buf ++ = ':';
				}
			else if (ix > 0 && ix < 7 && p_ip6addr->s6_addr16[ix] == 0)
				zero = true;
			else {
				if (zero) {
					omit = true;
					*buf ++ = ':';
					}
				buf += convert_hexdigit(buf, ntohs(p_ip6addr->s6_addr16[ix]), 16, 0, ' '); 
				if (ix < 7)
					*buf ++ = ':';
				}
			}
		}
	*buf = '\0';
	return start;
	}

/*
 *  in6_cksum -- IPv6 �Υȥ�󥹥ݡ����إإå��Υ����å������׻����롣
 *
 *  ���: ����ͤϥͥåȥ���Х��ȥ�����
 */

uint16_t
in6_cksum (T_NET_BUF *nbuf, uint8_t proto, uint_t off, uint_t len)
{
	uint32_t	sum;
	uint_t		align;

	/* 4 �����ƥåȶ����Υǡ���Ĺ */
	align = (len + 3) >> 2 << 2;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset((uint8_t*)nbuf->buf + off + len, 0, align - len);

	sum = in_cksum_sum(nbuf->buf + off, align)
	    + in_cksum_sum(&GET_IP6_HDR(nbuf)->src, sizeof(T_IN6_ADDR) * 2)
	    + len + proto;
	sum = in_cksum_carry(sum);

	return ~htons((uint16_t)sum);
	}

/*
 *  in6_is_dstaddr_accept -- ���襢�ɥ쥹�Ȥ����������������å����롣
 */

bool_t
in6_is_dstaddr_accept (T_IN6_ADDR *myaddr, T_IN6_ADDR *dstaddr)
{
	if (IN6_IS_ADDR_UNSPECIFIED(myaddr))
		return in6_lookup_ifaddr(IF_GET_IFNET(), dstaddr) != NULL;
	else
		return IN6_ARE_ADDR_EQUAL(dstaddr, myaddr);
	}

/*
 *  get_ip6_hdr_size -- ��ĥ�إå���ޤ᤿ IPv6 �إå�Ĺ���֤���
 */

uint_t
get_ip6_hdr_size (T_IP6_HDR *iph)
{
	uint_t	size = IP6_HDR_SIZE, hsize;
	uint8_t	curr = iph->next, next;
	uint8_t	*hdr = ((uint8_t *)iph) + IP6_HDR_SIZE;

	while (1) {
		next = *hdr;
		if (curr ==IPPROTO_NONE)		/* ���إå�̵��			*/
			break;
		else if (curr == IPPROTO_FRAGMENT)	/* ���Ҳ�			*/
			hsize = sizeof(T_IP6_FRAG_HDR);
		else if (curr == IPPROTO_AH)		/* IPv6 ǧ��			*/
			hsize = (((T_IP6_AH_HDR *)hdr)->len + 2) * 4;
		else if (curr == IPPROTO_HOPOPTS ||	/* ����� (Hop-by-Hop) ���ץ����	*/
		         curr == IPPROTO_DSTOPTS ||	/* IPv6 �������ץ����		*/
		         curr == IPPROTO_ROUTING)	/* ��ϩ����			*/
			hsize = (((T_IP6_EXT_HDR *)hdr)->len + 1) * 8;
		else
			break;
		size += hsize;
		hdr  += hsize;
		curr = next;
		}
	return size;
	}

/*
 *  in6_plen2pmask -- �ץ�ե��å���Ĺ����ޥ������������롣
 */

void
in6_plen2pmask (T_IN6_ADDR *mask, uint_t prefix_len)
{
	uint8_t	*ptr, bit;

	memset(mask->s6_addr + prefix_len / 8, 0, (128 - prefix_len + 7) / 8);
	for (ptr = mask->s6_addr; prefix_len > 0; ptr ++) {
		for (bit = 0x80; bit && (prefix_len > 0); prefix_len --) {
			*ptr |= bit;
			bit >>= 1;
			}
		}
	}

/*
 *  in6_rtalloc -- �롼�ƥ���ɽ��õ�����롣
 */

T_IN6_ADDR *
in6_rtalloc (T_IFNET *ifp, T_IN6_ADDR *dst)
{
	if (IN6_IS_ADDR_LINKLOCAL(dst) || IN6_IS_ADDR_MULTICAST(dst))
		return dst;
	else {
		T_IN6_IFADDR	*ia;
		SYSTIM		now;
		int_t		ix;

		/*
		 *  �����ȥ����륢�ɥ쥹�������ǽ�ʥ����Х�˥��ɥ쥹�ξ��ϡ�
		 *  Ʊ������ΥΡ��ɤǤ��뤫������å����롣
		 */

		syscall(get_tim(&now));
		now /= SYSTIM_HZ;

		/* �侩ͭ��������Υ��ɥ쥹��õ�����롣*/
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if (IFA6_IS_READY(ia) &&
			    in6_are_prefix_equal(dst, &ia->addr, ia->prefix_len) &&
			    (int32_t)(ia->lifetime.preferred - now) > 0) {
		                   /* ia->lifetime.preferred > now */
				return dst;
				}
			}

		/* ͭ��������Υ��ɥ쥹��õ�����롣*/
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if (IFA6_IS_READY(ia) &&
			    in6_are_prefix_equal(dst, &ia->addr, ia->prefix_len) &&
			    (int32_t)(ia->lifetime.expire - now) > 0)
		                   /* ia->lifetime.expire > now */
				return dst;
			}

		/*
		 *  �ץ�ե��å�����õ�����롣
		 */
		if (nd6_onlink_prefix_lookup (dst) != NULL)
			return dst;

		/*
		 *  ��Ū��ϩɽ��õ�����롣
		 */

#if NUM_ROUTE_ENTRY > 0

		syscall(wai_sem(SEM_IN_ROUTING_TBL));
		for (ix = NUM_ROUTE_ENTRY; ix --; ) {
			if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
			    in6_are_prefix_equal(dst, &routing_tbl[ix].target,
			                               routing_tbl[ix].prefix_len)) {

				/*
				 *  ����ľ���ˤ�륨��ȥ�ϡ�ͭ�����֤��ڤ�������Ĺ���롣
				 *  expire ��ñ�̤� [s]��
				 *  TMO_IN_REDIRECT ��ñ�̤� [ms]��
				 */
				if (ix > NUM_STATIC_ROUTE_ENTRY) {
					SYSTIM	now;

					syscall(get_tim(&now));
					routing_tbl[ix].expire = now / SYSTIM_HZ + TMO_IN_REDIRECT / 1000;
					}

				syscall(sig_sem(SEM_IN_ROUTING_TBL));
				return &routing_tbl[ix].gateway;
				}
			}
		syscall(sig_sem(SEM_IN_ROUTING_TBL));

#endif	/* of #if NUM_ROUTE_ENTRY > 0 */

		/*
		 *  �ǥ��ե���ȥ롼�����ꥹ�Ȥ�õ�����롣
		 */
		return nd6_router_lookup();
		}
	}

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  in6_gateway_lookup -- �롼�ƥ���ɽ�Υ롼����õ�����롣
 */

T_IN_RTENTRY *
in6_gateway_lookup (T_IN6_ADDR *gw)
{
	int_t	ix;

	for (ix = NUM_ROUTE_ENTRY; ix --; )
		if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
		    IN6_ARE_ADDR_EQUAL(&routing_tbl[ix].gateway, gw))
			return &routing_tbl[ix];
	return NULL;
	}

/*
 *  in6_rtredirect -- �롼�ƥ���ɽ�˥���ȥ����Ͽ���롣
 *
 *    ���: ���� tmo ��ñ�̤� [ms]��
 */

void
in6_rtredirect (T_IN6_ADDR *gateway, T_IN6_ADDR *target, uint_t prefix_len, uint8_t flags, uint32_t tmo)
{
	T_IN_RTENTRY	*frt;

	frt = in_rtnewentry(flags, tmo);
	frt->gateway    = *gateway;
	frt->target     = *target;
	frt->prefix_len = prefix_len;
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  in6_hostcache_lookup -- IPv6 �ۥ��ȥ���å����õ�����롣
 */

static T_IN6_HOSTCACHE_ENTRY*
in6_hostcache_lookup (T_IN6_ADDR *dst)
{
	int_t ix;

	for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
		if (IN6_ARE_ADDR_EQUAL(dst, &in6_hostcache[ix].dst))
			return &in6_hostcache[ix];
		}
	return NULL;
	}

/*
 *  in6_hostcache_update -- IPv6 �ۥ��ȥ���å���򹹿����롣
 */

void
in6_hostcache_update (T_IN6_ADDR *dst, uint32_t mtu)
{
	T_IN6_HOSTCACHE_ENTRY	*hc;
	SYSTIM	now, old;
	int_t	ix, oix;

	syscall(get_tim(&now));

	/* ������Ͽ����Ƥ��뤫õ�����롣*/
	if ((hc = in6_hostcache_lookup (dst)) == NULL) {

		/* �����Υۥ��ȥ���å����õ����*/
		for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
			if (IN6_IS_HOSTCACHE_FREE(&in6_hostcache[ix]))
				break;
			}

		if (ix < 0) {
			/*
			 *  ������̵�����ϡ�ͭ�����֤��ڤ����֤���
			 *  �Ǥ�û���ۥ��ȥ���å�����ִ����롣
			 */
			old = now - 1;
			oix = 0;
			for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
				hc = &in6_hostcache[ix];
				if (IN6_IS_HOSTCACHE_BUSY(hc) && (int32_t)(hc->expire - old) < 0) {
				                                        /* hc->expire < old */
					oix = ix;
					old = hc->expire;
					}
				}
			ix = oix;
			}
		hc = &in6_hostcache[ix];
		}
	else if (mtu > hc->mtu &&
	         (int32_t)(hc->expire - now) >= (IN6_HOSTCACHE_EXPIRE - IN6_HOSTCACHE_INCREASE)) {

		/*
		 *  ������Ͽ����Ƥ��ơ������� MTU ������Ͽ����Ƥ��� MTU ����礭���Ȥ���
		 *  IN6_HOSTCACHE_INCREASE�ʿ侩 10 ʬ�˴֤Ϲ������ʤ���
		 */
		return;
		}
	hc->dst    = *dst;
	hc->expire = now + IN6_HOSTCACHE_EXPIRE;
	hc->mtu    = mtu;
	}

/*
 *  in6_hostcache_getmtu -- IPv6 �ۥ��ȥ���å���򤫤� MTU ��������롣
 *
 *    ����ͤ� 0 �Ǥ���С��ۥ��ȥ���å������Ͽ����Ƥ��ʤ���
 */

uint32_t
in6_hostcache_getmtu (T_IN6_ADDR *dst)
{
	T_IN6_HOSTCACHE_ENTRY	*hc;

	/* ������Ͽ����Ƥ��뤫õ�����롣*/
	if ((hc = in6_hostcache_lookup(dst)) == NULL)
		return 0;
	else
		return hc->mtu;
	}

/*
 *  in6_hostcache_timer -- IPv6 �ۥ��ȥ���å��幹�������ޡ�
 *
 *    1�ü����ǵ�ư����롣
 */

static void
in6_hostcache_timer (void)
{
	static int_t interval = IN6_HOSTCACHE_PRUNE / SYSTIM_HZ;

	SYSTIM	now;

	interval --;
	if (interval <= 0) {
		syscall(get_tim(&now));
		interval = IN6_HOSTCACHE_PRUNE / SYSTIM_HZ;
		}
	}

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

/*
 *  in6_timer -- IPv6 ���̥����ޡ�
 *
 *    1�ü����ǵ�ư����롣
 */

static void
in6_timer (void)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rttimer();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

#ifdef IP6_CFG_FRAGMENT

	frag6_timer();

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

#if NUM_IN6_HOSTCACHE_ENTRY > 0

	in6_hostcache_timer();

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

	timeout((callout_func)in6_timer, NULL, IN_TIMER_TMO);
	}

/*
 *  in6_init -- IPv6 ���̵�ǽ���������롣
 */

void
in6_init (void)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rtinit();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

	timeout((callout_func)nd6_timer, NULL, ND6_TIMER_TMO);
	timeout((callout_func)in6_timer, NULL, IN_TIMER_TMO);
	}

#endif /* of #ifdef SUPPORT_INET6 */
