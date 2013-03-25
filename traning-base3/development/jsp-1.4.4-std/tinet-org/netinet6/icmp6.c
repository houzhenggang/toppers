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
 *  @(#) $Id: icmp6.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/icmp66.c,v 1.6.2.6 2001/07/10 09:44:16 ume Exp $	*/
/*	$KAME: icmp66.c,v 1.211 2001/04/04 05:56:20 itojun Exp $	*/

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
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)ip_icmp6.c	8.2 (Berkeley) 1/4/94
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>
#include <netinet6/nd6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

#ifdef SUPPORT_INET6

/*
 *  �ѿ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

T_ICMP6_IFSTAT icmp6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  icmp6_output -- ICMP6 �ѥ��åȤ��������롣
 */

static void
icmp6_output (T_NET_BUF *output, uint_t off)
{
	T_IN6_IFADDR	*ia;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;

	/*
	 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
	 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
	 */
	ip6h = GET_IP6_HDR(output);
	if ((ia = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutErrors, 1);
		syscall(rel_net_buf(output));
		return;
		}
	ip6h->src = ia->addr;

	icmp6h = GET_ICMP6_HDR(output, off);

	/* �����å������׻����롣*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)icmp6h - output->buf, 
	                        ntohs(ip6h->plen) - (off - IF_IP6_HDR_SIZE));

	/* �������롣*/
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	ip6_output(output, 0, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp6_echo_request -- �������׵����������Ȥ��ν���
 */

static void
icmp6_echo_request (T_NET_BUF *input, uint_t off)
{
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia;
	T_IN6_ADDR	dst;
	uint_t		diff;

	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInEchos, 1);

	ip6h       = GET_IP6_HDR(input);

	/*
	 *  IPv6 �إå��� ICMPv6 �إå��֤γ�ĥ�إå������롣
	 */
	diff = off - IF_IP6_HDR_SIZE;
	if (diff > 0) {
		/* ICMPv6 �إå������˵ͤ�롣*/
		memmove(input->buf + IF_IP6_HDR_SIZE, input->buf + off, input->len - off);
		off = IF_IP6_HDR_SIZE;

		/* �ڥ�����Ĺ��Ĵ�����롣*/
		ip6h->plen  = htons(ntohs(ip6h->plen) - diff);
		input->len -= diff;
		}

	icmp6h = GET_ICMP6_HDR(input, off);
	if (icmp6h->code != 0) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		syscall(rel_net_buf(input));
		return;
		}

	/*
	 *  ��å������η��򥨥����׵� (128) ����
	 *  ���������� (129) ���ѹ����������֤���
	 */
	icmp6h->type = ICMP6_ECHO_REPLY;

	/* IPv6 �إå���ȯ�������ɥ쥹�Ȱ��襢�ɥ쥹�����ؤ��롣*/
	dst 	  = ip6h->dst;
	ip6h->dst = ip6h->src;
	ip6h->src = dst;

	/*
	 *  ���ΰ��襢�ɥ쥹���ޥ�����㥹�Ȥξ��ϡ�
	 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
	 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
	 */
	if (IN6_IS_ADDR_MULTICAST(&dst)) {
		if ((ia = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
			syscall(rel_net_buf(input));
			return;
			}
		else
			ip6h->src = ia->addr;
		}

	/* ���إå��ȥۥåץ�ߥåȤ����ꤹ�롣*/
	ip6h->next = IPPROTO_ICMPV6;
	ip6h->hlim = IP_DEFTTL;

	/* �����å������׻����롣*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(input, IPPROTO_ICMPV6, (uint8_t*)icmp6h - input->buf, 
	                        ntohs(ip6h->plen) - (off - IF_IP6_HDR_SIZE));

	/* �������롣*/
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_OCTETS],
	               input->len - GET_IF_IP6_HDR_SIZE(input));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutEchoReplies, 1);
	ip6_output(input, 0, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp6_notify_error -- ���顼�����Τ��롣
 */

static void
icmp6_notify_error(T_NET_BUF *input, uint_t poff)
{
	T_ICMP6_HDR	*icmp6h;
	ER_UINT		loff;
	uint_t		len, next;

	len  = input->len - poff;

	/* �ǡ��������Ĺ�� ICMP6 �إå�Ĺ + IP6 �إå�Ĺ�ʲ��ʤ鲿�⤷�ʤ���*/
	if (len < ICMP6_HDR_SIZE + IP6_HDR_SIZE)
		return;

	icmp6h = GET_ICMP6_HDR(input, poff);

	/* �ǽ��إå���õ�����롣*/
	loff = ip6_lasthdr(input, poff + ICMP6_HDR_SIZE, IPPROTO_IPV6, &next);

	/* �ǽ��إå��� TCP �Τ��б����롣*/
	if (loff >= 0 && next == IPPROTO_TCP) {

#ifdef SUPPORT_TCP

		memcpy(GET_IP6_HDR(input), input->buf + (loff + ICMP6_HDR_SIZE),
		                           input->len - (loff + ICMP6_HDR_SIZE));
		input->len -= loff + ICMP6_HDR_SIZE;
		tcp_notify(input, icmp6h->code == ICMP6_DST_UNREACH_NOPORT ? EV_CNNRF : EV_HURCH);

#endif	/* of #ifdef SUPPORT_TCP */

		}
	else
		syslog(LOG_NOTICE, "[ICMP6] error code: %d.", icmp6h->code);
	}

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  icmp6_mtudisc_update -- Path MTU �򹹿����롣
 */

static void
icmp6_mtudisc_update(T_NET_BUF *input, uint_t off, uint32_t mtu)
{
	T_IP6_HDR	*pip6h;

	pip6h = (T_IP6_HDR*)GET_ICMP6_SDU(input, off);

	if (mtu < IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR) + 8)
		return;

	if (mtu > IF_MTU)
		return;

	in6_hostcache_update(&pip6h->dst, mtu);
	}

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  icmp6_redirect_input -- ����ľ����å������ν���
 */

static void
icmp6_redirect_input (T_NET_BUF *input, uint_t off)
{
	T_IP6_HDR		*ip6h;
	T_IN6_ADDR		*gw;
	T_ND_REDIRECT_HDR	*rdh;
	T_ND_OPT_HDR		*opth;
	T_IFNET			*ifp = IF_GET_IFNET();
	bool_t			router, onlink;
	uint_t			lladdr_len = 0;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	ip6h = GET_IP6_HDR(input);

	/*
	 *  IP �إå��Υ����å����ʲ��ξ����˴����롣
	 *    ����󥯥�����ʳ����������Ƥ�����å�����
	 *    ���ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �ʳ�
	 */
	if (!IN6_IS_ADDR_LINKLOCAL(&ip6h->src) || ip6h->hlim != IPV6_MAXHLIM)
		goto err_ret;

	rdh  = (T_ND_REDIRECT_HDR *)(input->buf + off);

	/* ����ľ���ν������ɥ쥹���ޥ�����㥹�ȥ��ɥ쥹�ξ����˴����롣*/
	if (IN6_IS_ADDR_MULTICAST(&rdh->dst))
		goto err_ret;

	/* �������åȥ��ɥ쥹����ϩɽ����Ͽ����Ƥ��뤫�����å����롣*/
	if ((gw = in6_rtalloc(ifp, &rdh->dst)) != NULL) {
		/* GW ���ɥ쥹�����������ɥ쥹���ۤʤäƤ�����˴����롣*/
		if (!IN6_ARE_ADDR_EQUAL(gw, &ip6h->src))
			goto err_ret;
		}
	else	/* ��ϩɽ�ˤʤ�����˴����롣*/
		goto err_ret;

	router = onlink = false;

	/*
	 *  �������åȥ��ɥ쥹����󥯥����륢�ɥ쥹�Ǥ���С�
	 *  �������åȤϥ롼��
	 */
	if (IN6_IS_ADDR_LINKLOCAL(&rdh->target))
		router = true;

	/*
	 *  �������åȥ��ɥ쥹�Ƚ������ɥ쥹��Ʊ��Ǥ���С�������
	 */
	if (IN6_ARE_ADDR_EQUAL(&rdh->target, &rdh->dst))
		onlink = true;
		
	/*
	 *  �롼���Ǥ⡢�����󥯤Ǥ�ʤ���Х��顼
	 */
	if (!router && !onlink)
		goto err_ret;

	/* ����õ�����ץ����Υ��ե��åȤ�Ͽ���롣*/
	if (nd6_options(nd_opt_off, input->buf +  off + ND_REDIRECT_HDR_SIZE,
	                            input->len - (off + ND_REDIRECT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* ����õ�����ץ���� (����ľ���Υ롼���Υ�󥯥��ɥ쥹) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + ND_REDIRECT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)] - 8);
	 	/* ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	/*
	 *  �ͥåȥ�����󥿥ե������Υ��ɥ쥹Ĺ�����פ��ʤ���Х��顼
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* ����ľ���Υ롼���Υ�󥯥��ɥ쥹����٥���å������Ͽ���롣*/
	nd6_cache_lladdr(ifp, &rdh->target, (T_IF_ADDR *)lladdr, ND_REDIRECT, 
	                 onlink ? ND_REDIRECT_ONLINK : ND_REDIRECT_ROUTER);

	/* �롼�ƥ���ɽ����Ͽ���롣*/
	in6_rtredirect(&rdh->target, &rdh->dst, 128, IN_RTF_REDIRECT, TMO_IN_REDIRECT);

	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp6_input -- ICMP6 �����ϴؿ�
 */

uint_t
icmp6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	uint_t		len, off = *offp;
	uint8_t		code;

	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_OCTETS],
	               input->len - GET_IF_IP6_HDR_SIZE(input));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInMsgs, 1);

	/* ICMP6 �إå���Ĺ��������å����롣*/
	len  = input->len - off;
	if (len < ICMP6_HDR_SIZE) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		goto buf_rel;
		}

	ip6h   = GET_IP6_HDR(input);
	icmp6h = GET_ICMP6_HDR(input, off);

	/* �����å������׻����롣*/
	if ((in6_cksum(input, IPPROTO_ICMPV6, off, ntohs(ip6h->plen) - (off - IF_IP_HDR_SIZE)) & 0xffff) != 0) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		goto buf_rel;
		}

	code = icmp6h->code;

	/* ��å������η��ˤ��ʬ�����롣*/
	switch (icmp6h->type) {

	case ICMP6_DST_UNREACH:			/* ������ã�Բ�ǽ		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInDestUnreachs, 1);
		icmp6_notify_error(input, off);
		break;

	case ICMP6_ECHO_REQUEST:		/* �������׵�			*/
		icmp6_echo_request(input, off);
		return IPPROTO_DONE;
		break;

	case ICMP6_ECHO_REPLY:			/* ����������			*/

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

		icmp6_echo_reply(input, off);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

		break;

	case ND_ROUTER_ADVERT:			/* �롼������			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInRouterAdvertisements, 1);
		if (code != 0 || len < ROUTER_ADVERT_HDR_SIZE)
			goto buf_rel;
		nd6_ra_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_NEIGHBOR_SOLICIT:		/* ��������			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInNeighborSolicits, 1);
		if (code != 0 || len < NEIGHBOR_SOLICIT_HDR_SIZE)
			goto buf_rel;
		nd6_ns_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_NEIGHBOR_ADVERT:		/* ��������			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInNeighborAdvertisements, 1);
		if (code != 0 || len < NEIGHBOR_ADVERT_HDR_SIZE)
			goto buf_rel;
		nd6_na_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_REDIRECT:			/* ����ľ��			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInRedirects, 1);

#if NUM_REDIRECT_ROUTE_ENTRY > 0

		if (code != 0 || len < ND_REDIRECT_HDR_SIZE)
			goto buf_rel;
		icmp6_redirect_input(input, off);
		return IPPROTO_DONE;

#else	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		syslog(LOG_WARNING, "[ICMP6] redirect ignored.");

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		break;

	case ICMP6_PACKET_TOO_BIG:		/* �ѥ��åȤ��礭�����롣	*/

#if NUM_IN6_HOSTCACHE_ENTRY > 0

		icmp6_mtudisc_update(input, off, ntohl(icmp6h->icmp6_mtu));

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInPktTooBigs, 1);
		break;

	case ICMP6_TIME_EXCEEDED:		/* TTL ��Ķ�ᤷ����		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInTimeExcds, 1);
		break;

	case ICMP6_PARAM_PROB:			/* IPv6 �إå���������		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInParmProblems, 1);
		break;

	case MLD_LISTENER_QUERY:		/* �ޥ�����㥹�ȼ����ԾȲ�	*/
	case MLD_LISTENER_REPORT:		/* �ޥ�����㥹�ȼ��������	*/
	case MLD_LISTENER_DONE:			/* �ޥ�����㥹�ȼ����Խ�λ	*/
	case ND_ROUTER_SOLICIT:			/* �롼������			*/
	case ICMP6_ROUTER_RENUMBERING:		/* �롼���ֹ������		*/
	case ICMP6_FQDN_QUERY:			/* FQDN �Ȳ�			*/
	case ICMP6_FQDN_REPLY:			/* FQDN ����			*/
		syslog(LOG_WARNING, "[ICMP6] unsupported type: %d.", icmp6h->type);
		break;

	default:
		syslog(LOG_WARNING, "[ICMP6] unknown type: %d.", icmp6h->type);
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		break;
		}

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

/*
 *  icmp6_error -- ICMP6 ���顼�����ؿ�
 */

void
icmp6_error (T_NET_BUF *input, uint8_t type, uint8_t code, uint32_t param)
{
	T_NET_BUF	*output;
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	ER_UINT		off;
	uint_t		next, len;

	ip6h = GET_IP6_HDR(input);

	/*
	 *  ���襢�ɥ쥹�����ޥ�����㥹�Ȥξ��ϡ�
	 *  �ʲ��ξ��ʳ��ΤȤ��Ͻ�����Ԥ�ʤ���
	 *
	 *    ���ǡ�������ब�礭�����롣
	 *    ��IPv6 �إå��������ǡ����ץ����ǧ���Ǥ��ʤ���
	 */
	if (IN6_IS_ADDR_MULTICAST(&ip6h->dst) &&
	    !((type == ICMP6_PACKET_TOO_BIG) ||
	      (type == ICMP6_PARAM_PROB && code == ICMP6_PARAMPROB_OPTION)))
		goto buf_rel;

	/*
	 *  �������ɥ쥹�����ʲ��ξ��Ͻ�����Ԥ�ʤ���
	 *
	 *    ��̵����
	 *    ���ޥ�����㥹��
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src) ||
	    IN6_IS_ADDR_MULTICAST  (&ip6h->src))
		goto buf_rel;

	/* �Ǹ�Υإå���õ�����롣*/
	off = ip6_lasthdr(input, 0, IPPROTO_IPV6, &next);

	/*
	 *  �����פ������顼������ľ���� ICMP6 �ѥ��åȤΥ��顼�ˤ��������ʤ���
	 */
	if (off >= 0 && next == IPPROTO_ICMPV6) {
		T_ICMP6_HDR	*icmp6h;

		if (input->len - off < ICMP6_HDR_SIZE)
			goto buf_rel;

		icmp6h = GET_ICMP6_HDR(input, off);
		if (icmp6h->type <  ICMP6_ECHO_REQUEST ||
		    icmp6h->type == ND_REDIRECT)
			goto buf_rel;
		}

	/* DoS ������Ф����ɸ��̤���� */

	/*
	 *  �����֤���å�����Ĺ��ICMPv6 �κ���ڥ�����Ĺ��Ĵ�����롣
	 *  IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE)
	 */
	if (input->len - IF_HDR_SIZE > IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE))
		len = IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE);
	else
		len = input->len - IF_HDR_SIZE;

	/* �����ѤΥͥåȥ���Хåե���������롣*/
	if (in6_get_datagram(&output, len + ICMP6_HDR_SIZE, 0,
	                     &ip6h->src, &in6_addr_unspecified,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ICMP_OUTPUT) != E_OK)
		goto buf_rel;

	/* ICMP6 �إå������ꤹ�롣*/
 	icmp6h = GET_ICMP6_HDR(output, IF_IP6_ICMP6_HDR_OFFSET);
 	icmp6h->type       = type;
 	icmp6h->code       = code;
 	icmp6h->icmp6_pptr = htonl(param);
 
 	/* ���顼�ǡ��������ꤹ�롣*/
 	memcpy(GET_ICMP6_SDU(output, IF_IP6_ICMP6_HDR_OFFSET), (uint8_t *)ip6h, len);

#ifdef SUPPORT_MIB

	switch (type) {
	case ICMP6_DST_UNREACH:
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutDestUnreachs, 1);
		break;

	case ICMP6_PARAM_PROB:
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutParmProblems, 1);
		break;

	default:
		break;

		}

#endif	/* of #ifdef SUPPORT_MIB */

	/* �������롣*/
	icmp6_output(output, IF_IP6_HDR_SIZE);

buf_rel:
	syscall(rel_net_buf(input));
	}

#endif /* of #ifdef SUPPORT_INET6 */
