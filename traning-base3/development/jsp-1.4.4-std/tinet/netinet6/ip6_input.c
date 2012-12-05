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
 *  @(#) $Id: ip6_input.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/ip6_input.c,v 1.11.2.10 2001/07/24 19:10:18 brooks Exp $	*/
/*	$KAME: ip6_input.c,v 1.194 2001/05/27 13:28:35 itojun Exp $	*/

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
 *	@(#)ip_input.c	8.2 (Berkeley) 1/4/94
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

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
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>
#include <netinet6/ah6.h>
#include <netinet6/esp6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �ؿ�
 */

static uint_t ip6_no_header_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);

/*
 *  ��̥ץ�ȥ�������¤��
 */

typedef struct t_proto_switch {
	uint_t (*func)(T_NET_BUF **, uint_t *, uint_t *);	/* ���ϴؿ�		*/
	uint_t proto;						/* �ץ�ȥ����ֹ�	*/
	} T_PROTO_SWITCH;

static const T_PROTO_SWITCH proto_switch[] = {
	{ esp6_input,	IPPROTO_ESP		},	/* IPv6 �Ź沽�إå�	*/
	{ ah6_input,	IPPROTO_AH		},	/* IPv6 ǧ�ڥإå�	*/
	{ frag6_input,	IPPROTO_FRAGMENT	},	/* ���ҥإå�		*/
	{ route6_input,	IPPROTO_ROUTING		},	/* ��ϩ����إå�	*/
	{ dest6_input,	IPPROTO_DSTOPTS		},	/* IPv6 �������ץ����	*/
	{ ip6_no_header_input,
			IPPROTO_NONE		},	/* ���إå�̵��		*/
	{ icmp6_input,	IPPROTO_ICMPV6		},

#ifdef SUPPORT_UDP

	{ udp_input,	IPPROTO_UDP		},

#endif	/* of #ifdef SUPPORT_UDP */

#ifdef SUPPORT_TCP

	{ tcp_input,	IPPROTO_TCP		},

#endif	/* of #ifdef SUPPORT_TCP */

	};

#ifdef SUPPORT_MIB

T_IN6_IFSTAT in6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  get_upper_proto -- ��̥ץ�ȥ�������ؿ����֤���
 */

static uint_t (*
get_upper_proto(uint_t proto))(T_NET_BUF **, uint_t *, uint_t *)
{
	int_t ix;

	for (ix = sizeof(proto_switch) / sizeof(T_PROTO_SWITCH); ix -- > 0; )
		if (proto_switch[ix].proto == proto)
			return proto_switch[ix].func;
	return NULL;
	}

/*
 *  ip6_no_header_input -- ���إå���̵���ξ������Ͻ���
 */

static uint_t
ip6_no_header_input (T_NET_BUF **input, uint_t *offp, uint_t *nextp)
{
	syscall(rel_net_buf(*input));
	return IPPROTO_DONE;
	}

/*
 *  ip6_hopopts_input -- ��������ץ�������Ͻ���
 *
 *    �ܼ����Ǥϡ��ѥǥ��󥰰ʳ��Υ��ץ���������̤�Υ��ץ����Ȥ��ƽ������롣
 *
 *    �����:
 *
 *      0 �ʾ� 		����
 *      IP6_OPT_RET_ERR (-1)	���顼���ƽ�¦�ǥͥåȥ���Хåե��������롣
 *      IP6_OPT_RET_REL (-2)	���顼���ͥåȥ���Хåե��ϳ�������Ƥ��롣
 */

static ER_UINT
ip6_hopopts_input (T_NET_BUF *input, uint_t *offp, uint_t *nextp)
{
	T_IP6_HBH_HDR	*hbh;
	ER_UINT		optlen;
	uint_t		len;
	uint8_t		*opt;

	hbh    = (T_IP6_HBH_HDR *)(input->buf + *offp);
	len    = (hbh->len + 1) << 3;
	*nextp = *offp - IF_HDR_SIZE + offsetof(T_IP6_HBH_HDR, next);
	*offp += len;
	opt    = (uint8_t *)hbh + sizeof(T_IP6_HBH_HDR);

	for (len -= sizeof(T_IP6_HBH_HDR); len > 0; len -= optlen) {
		switch (*opt) {
		case IP6OPT_PAD1:
			optlen = 1;
			break;
		case IP6OPT_PADN:
			if (len < IP6OPT_MINLEN)
				return IP6_OPT_RET_ERR;
			optlen = *(opt + 1) + 2;
			break;
		case IP6OPT_JUMBO:
		case IP6OPT_NSAP_ADDR:
		case IP6OPT_TUNNEL_LIMIT:
		case IP6OPT_RTR_ALERT:
		default:
			if (len < IP6OPT_MINLEN)
				return IP6_OPT_RET_ERR;
			optlen = ip6_unknown_opt(input, opt);
			if (optlen < 0)
				return optlen;
			optlen += 2;
			break;
			}

		opt += optlen;
		}

	return *offp;
	}

/*
 *  ip6_get_prev_hdr -- ľ���γ�ĥ�إå��� next �ե�����ɤΥ��ɥ쥹���֤���
 *
 *    ���: off �ˤ� IF_HDR_SIZE ��ޤޤ�Ƥ��롣
 */

uint8_t *
ip6_get_prev_hdr (T_NET_BUF *nbuf, uint_t off)
{
	T_IP6_HDR	*ip6h;
	T_IP6_EXT_HDR	*ip6eh;
	uint_t		len;
	uint8_t		next;

	ip6h = GET_IP6_HDR(nbuf);
	if (off == IF_HDR_SIZE + sizeof(T_IP6_HDR))
		return &ip6h->next;
	else {
		next  = ip6h->next;
		len   = IF_HDR_SIZE + sizeof(T_IP6_HDR);
		ip6eh = NULL;

		while (len < off) {
			ip6eh = (T_IP6_EXT_HDR *)(nbuf->buf + len);

			switch (next) {
			case IPPROTO_FRAGMENT:
				len += sizeof(T_IP6_FRAG_HDR);
				break;
			case IPPROTO_AH:
				len += (ip6eh->len + 2) << 2;
				break;
			default:
				len += (ip6eh->len + 2) << 3;
				break;
				}
			next  = ip6eh->next;
			}

		if (ip6eh == NULL)
			return NULL;
		else
			return &ip6eh->next;
		}
	}

/*
 *  ip6_init -- IPv6 �ν�����ؿ�
 */

void
ip6_init (void)
{
	in6_init();
	in6_ifainit();
	}

/*
 *  ip6_input -- IPv6 �����ϴؿ�
 */

void
ip6_input (T_NET_BUF *input)
{
	T_IP6_HDR	*ip6h;
	T_IN6_IFADDR	*ia6;
	T_IFNET		*ifp;
	ER_UINT		noff;
	uint_t		next, nest, plen, offp, nextp;
	uint_t		(*func)(T_NET_BUF **, uint_t *, uint_t *);

	NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_OCTETS], input->len - IF_HDR_SIZE);
	NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_PACKETS], 1);
	NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInReceives, 1);

	/* IP �إå���Ĺ��������å����롣*/
	if (input->len < IF_IP6_HDR_SIZE) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInHdrErrors, 1);
		goto buf_rel;
		}

	ip6h = GET_IP6_HDR(input);

	/* �С�����������å����롣*/
	if (IP6_VCF_V(ntohl(ip6h->vcf)) != IPV6_VERSION) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_VER], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInHdrErrors, 1);
		goto buf_rel;
		}

	/*
	 *  ���Υǡ����������˴����롣
	 *
	 *    ���������ɥ쥹���ޥ�����㥹��
	 *    ���������ɥ쥹��̤���
	 *
	 *  �ͥåȥ�����󥿥ե��������롼�ץХå��Ǥʤ��Ȥ���
	 *  ���Υǡ����������˴����롣
	 *
	 *    ���������ɥ쥹���롼�ץХå�
	 *    ���������ɥ쥹���롼�ץХå�
	 *
	 *  ���դΤ���桼���� TCP/UDP �����å��κ����
	 *  �������ƥ������å���Х��ѥ����뤿�ᡢIPv4
	 *  �ޥåץ��ɥ쥹���Ѥ��뤳�Ȥ��ɤ�����
	 *  �ʲ��Υǡ����������˴����롣  
	 *
	 *    ���������ɥ쥹�� ::ffff:127.0.0.1
	 *    ���������ɥ쥹�� ::ffff:127.0.0.1
	 */

	if (IN6_IS_ADDR_MULTICAST(&ip6h->src) ||
	    IN6_IS_ADDR_UNSPECIFIED(&ip6h->dst)) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
		goto buf_rel;
		}

	if (IN6_IS_ADDR_V4MAPPED(&ip6h->src) ||
	    IN6_IS_ADDR_V4MAPPED(&ip6h->dst)) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
		goto buf_rel;
		}

#ifdef SUPPORT_LOOP

#else	/* of #ifdef SUPPORT_LOOP */

	if (IN6_IS_ADDR_LOOPBACK(&ip6h->src) ||
	    IN6_IS_ADDR_LOOPBACK(&ip6h->dst)) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
		goto buf_rel;
		}

#endif	/* of #ifdef SUPPORT_LOOP */

	ifp = IF_GET_IFNET();

	if (IN6_IS_ADDR_MULTICAST(&ip6h->dst)) {
		/* ���褬�ޥ�����㥹�Ȥξ��ν��� */
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInMcastPkts, 1);
		if (!in6_lookup_multi(ifp, &ip6h->dst)) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
			goto buf_rel;
			}
		}
	else {
		if ((ia6 = in6_lookup_ifaddr(ifp, &ip6h->dst)) == NULL) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
			goto buf_rel;
			}

		/*  ���ɥ쥹��̤���ξ��ϥǡ����������˴����롣*/
		if (IFA6_IS_NOTREADY(ia6)) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_ADDR], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInAddrErrors, 1);
			goto buf_rel;
			}
		}

	/* ���ե��åȤ����ꤹ�롣*/
	offp  = GET_IP6_NEXT_HDR(input) - input->buf;

	/* �ڥ�����Ĺ����Ф���*/
	plen = ntohs(ip6h->plen);


	/* ���إå��ΰ��֤��������롣*/
	nextp = offsetof(T_IP6_HDR, next);

	/*
	 *  ����� (Hop-by-Hop) ���ץ����إå��Υ����å�
	 */
	if (ip6h->next == IPPROTO_HOPOPTS) {

		/* ������إå���Ĺ��������å����롣*/
		if (plen < sizeof(T_IP6_HBH_HDR)) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_SHORT], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInHdrErrors, 1);
			goto buf_rel;
			}

		if ((noff = ip6_hopopts_input(input, &offp, &nextp)) < 0) {
			if (noff == IP6_OPT_RET_ERR) {
				NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PACKETS], 1);
				NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInHdrErrors, 1);
				goto buf_rel;
				}
			else if (noff == IP6_OPT_RET_REL) {
				NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PACKETS], 1);
				NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInHdrErrors, 1);
				return;
				}
			}

		/*
		 *  �ڥ�����Ĺ�� 0 �ǡ���������ץ���󤬤���Ȥ��ϡ�
		 *  ����ڥ����ɡ����ץ���󤬴ޤޤ�ʤ���Фʤ�ʤ���
		 *  ���ΤȤ�������ڥ����ɡ����ץ����ˤ���
		 *  �ڥ�����Ĺ������å�����ɬ�פ����뤬���ܼ����Ǥϡ�
		 *  ����ڥ����ɡ����ץ�����̤�ΤΥ��ץ����Ȥ���
		 *  �����Τǡ����⤷�ʤ���
		 */
		next = ((T_IP6_HBH_HDR *)(ip6h + 1))->next;
		}
	else
		next = ip6h->next;

	/* IPv6 �ǡ��������Ĺ������å����롣*/
	if (input->len - IF_IP6_HDR_SIZE < plen) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInTruncatedPkts, 1);
		goto buf_rel;
		}
	else if (input->len > IF_IP6_HDR_SIZE + plen)
		input->len = IF_IP6_HDR_SIZE + plen;

	/* ��̥ץ�ȥ�������ؿ���ƤӽФ���*/
	nest = 0;
	while (next != IPPROTO_DONE) {
		if (++ nest > IP6_HDR_NEST_LIMIT) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PROTO], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInUnknownProtos, 1);
			goto buf_rel;
			}
		else if ((func = get_upper_proto(next)) == NULL) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PROTO], 1);
			NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PACKETS], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsInUnknownProtos, 1);

			/* icmp6_error �ǥͥåȥ���Хåե��������롣*/
			icmp6_error(input, ICMP6_PARAM_PROB,
			                   ICMP6_PARAMPROB_NEXT_HEADER, nextp);
			return;
			}
		else {
			next = (*func)(&input, &offp, &nextp);
			}
		}
	return;

buf_rel:
	NET_COUNT_IP6(net_count_ip6[NC_IP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

/*
 *  ip6_nexthdr -- ���Υإå��Υ��ե��åȤ��֤���
 *
 *    ����� == -1 : �Ǹ�Υإå����ޤ��ϥ��顼��
 *    ����� >   0 : ����˥إå���³����
 */

ER_UINT
ip6_nexthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp)
{
	T_IP6_FRAG_HDR	*ip6fh;
	T_IP6_EXT_HDR	*ip6eh;

	switch (proto) {

	case IPPROTO_IPV6:				/* IPv6 */
		if (nbuf->len < off + IP6_HDR_SIZE)
			return (ER_UINT)-1;
		*nextp = ((T_IP6_HDR *)(nbuf->buf + off))->next;
		return off + IP6_HDR_SIZE;
		break;

	case IPPROTO_FRAGMENT:			/* ���ҥإå� */
		if (nbuf->len < off + sizeof(T_IP6_FRAG_HDR))
			return (ER_UINT)-1;

		/* ��֤Υե饰���Ȥξ��Ͻ�������롣*/
		ip6fh = (T_IP6_FRAG_HDR *)(nbuf->buf + off);
		if (ntohs(ip6fh->off_flag) & IP6F_MORE_FRAG)
			return (ER_UINT)-1;

		*nextp = ip6fh->next;
		return off + sizeof(T_IP6_FRAG_HDR);
		break;

	case IPPROTO_AH:		/* IPv6 ǧ�ڥإå�			*/
	case IPPROTO_HOPOPTS:		/* IPv6 ����� (Hop-by-Hop) ���ץ����	*/
	case IPPROTO_ROUTING:		/* ��ϩ����إå�			*/
	case IPPROTO_DSTOPTS:		/* IPv6 �������ץ����			*/
		if (nbuf->len < off + sizeof(T_IP6_EXT_HDR))
			return (ER_UINT)-1;

		ip6eh = (T_IP6_EXT_HDR *)(nbuf->buf + off);
		*nextp =  ip6eh->next;
		if (proto == IPPROTO_AH)
			return off + ((ip6eh->len + 2) << 2);
		else
			return off + ((ip6eh->len + 1) << 3);
		break;
		}

	return (ER_UINT)-1;
	}

/*
 *  ip6_lasthdr -- �Ǹ�Υإå��Υ��ե��åȤ��֤���
 */

ER_UINT
ip6_lasthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp)
{
	ER_UINT	newoff;

	while (1) {
		newoff = ip6_nexthdr(nbuf, off, proto, nextp);
		if (newoff < 0)
			return (ER_UINT)off;
		off   = newoff;
		proto = *nextp;
		}
	return (ER_UINT)0u;
	}

/*
 *  ip6_unknown_opt -- ̤�ΤΥ��ץ����ν���
 *
 *    �����:
 *
 *      0 �ʾ� 			������ץ����Ĺ��
 *      IP6_OPT_RET_ERR (-1)	���顼���ƽ�¦�ǥͥåȥ���Хåե��������롣
 *      IP6_OPT_RET_REL (-2)	���顼���ͥåȥ���Хåե��ϳ�������Ƥ��롣
 */

ER_UINT
ip6_unknown_opt (T_NET_BUF *input, uint8_t *opt)
{
	switch (IP6OPT_TYPE(*opt)) {
	case IP6OPT_TYPE_SKIP:		/* ̵�뤹�롣			*/
		return *(opt + 1);
		break;
	case IP6OPT_TYPE_ICMP:		/* �˴����ơ��ޥ�����㥹�ȤǤʤ���� ICMP ���������롣	*/
		if (IN6_IS_ADDR_MULTICAST(&GET_IP6_HDR(input)->dst))
			return IP6_OPT_RET_ERR;
		/* no break; */
	case IP6OPT_TYPE_FORCEICMP:	/* �˴����ơ�ICMP ���������롣	*/
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_OPTION,
		                   (opt - input->buf) - IF_HDR_SIZE);
		return IP6_OPT_RET_REL;
		break;
	/*case IP6OPT_TYPE_DISCARD:	�ǡ����������˴����롣	*/
		}

	return IP6_OPT_RET_ERR;
	}

/*
 *  ip6_remove_exthdrs -- IPv6 ��ĥ�إå����������ʹߤ����˵ͤ�롣
 */

ER
ip6_remove_exthdrs (T_NET_BUF *nbuf)
{
	ER_UINT	off;
	uint_t	next;

	/* ���ϥ��ե��åȤ� IP �إå������ꤹ�롣*/
	off = ((uint8_t *)GET_IP_HDR(nbuf)) - nbuf->buf;

	/* �ǽ��إå���õ�����롣*/
	off = ip6_lasthdr(nbuf, off, IPPROTO_IPV6, &next);

	if (off <= 0)
		return E_OBJ;
	else {
		uint_t sdu;

		sdu = GET_IP_SDU(nbuf) - nbuf->buf;
		if (off > sdu) {
			memmove(nbuf->buf + sdu, nbuf->buf + off, off - sdu);
			GET_IP_HDR(nbuf)->plen -= off - sdu;
			nbuf->len              -= off - sdu;
			}
		}
	return E_OK;
	}

#endif /* of #ifdef SUPPORT_INET6 */
