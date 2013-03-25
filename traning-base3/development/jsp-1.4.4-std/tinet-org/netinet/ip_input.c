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
 *  @(#) $Id: ip_input.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)input.c	8.2 (Berkeley) 1/4/94
 * $FreeBSD: src/sys/netinet/input.c,v 1.111.2.4 1999/11/01 22:23:53 des Exp $
 *	$ANA: input.c,v 1.5 1996/09/18 14:34:59 wollman Exp $
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
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#if defined(SUPPORT_IPSEC)
//#include <stdio.h>
#include <sys/types.h>
#include <netinet6/ipsec.h>
#include <netinet6/esp.h>
#include <netkey/key.h>
#include <netkey/key_debug.h>
#endif /* of defined(SUPPORT_IPSEC) */

#include <net/if_var.h>

/*
 *  �ѿ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

T_IP_STATS ip_stats;

#endif	/* of #ifdef SUPPORT_MIB */

#ifdef IP4_CFG_FRAGMENT

/*
 *  �ǡ��������ƹ������塼
 */

static T_NET_BUF	*ip_frag_queue[NUM_IP4_FRAG_QUEUE];
static T_IN4_ADDR	    frag_dst  [NUM_IP4_FRAG_QUEUE];

/*
 *  �ؿ�
 */

static void ip_freef (int_t ix);
static T_NET_BUF *ip_reass (T_IP4_HDR *ip4h, T_NET_BUF *input);

/*
 *  ip_get_frag_queue -- �ǡ��������ƹ������塼��������롣
 */

const T_NET_BUF **
ip_get_frag_queue (void)
{
	return (const T_NET_BUF **)ip_frag_queue;
	}

/*
 *  ip_freef -- �ǡ��������ƹ������塼��������롣
 */

static void
ip_freef (int_t ix)
{
	T_NET_BUF	*frag, *next;

	frag = ip_frag_queue[ix];
	while (frag != NULL) {
		next = GET_QIP4_HDR(frag)->next;
		syscall(rel_net_buf(frag));
		frag = next;
		}
	ip_frag_queue[ix] = NULL;
	}

/*
 *  ip_frag_timer -- �ǡ��������ƹ�������������
 */

void
ip_frag_timer (void)
{
	T_NET_BUF	*frag;
	int_t		ix;

	syscall(wai_sem(SEM_IP4_FRAG_QUEUE));
	for (ix = NUM_IP4_FRAG_QUEUE; ix -- > 0; ) {
		frag = ip_frag_queue[ix];
		if (frag != NULL && GET_QIP4_HDR(frag)->ttl > 0 &&
		    -- GET_QIP4_HDR(frag)->ttl == 0) {
			NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_TMOUT], 1);
			NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
			ip_freef(ix);
			}
		}
	syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
	}

/*
 *  ip_reass -- �ǡ���������ƹ������롣
 */

static T_NET_BUF *
ip_reass (T_IP4_HDR *ip4h, T_NET_BUF *input)
{
	T_NET_BUF	*frag, *prev;
	T_IN4_ADDR	dst, src;
	int_t		ix;
	uint_t		id, off, len;

	NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_FRAGS], 1);
	NET_COUNT_MIB(ip_stats.ipReasmReqds, 1);

	src = ntohl(ip4h->src);
	dst = ntohl(ip4h->dst);
	NTOHS(ip4h->id);
	NTOHS(ip4h->flg_off);
	id = ip4h->id;
	ix = id % NUM_IP4_FRAG_QUEUE;

	syscall(wai_sem(SEM_IP4_FRAG_QUEUE));

	/*
	 *  ID��IP���ɥ쥹����̥ץ�ȥ��뤬�ۤʤ�ե饰���Ȥ����塼��ͭ����˴����롣
	 */
	frag = ip_frag_queue[ix];
	if (frag != NULL &&
	    (id  != GET_IP4_HDR(frag)->id  ||
	     dst != frag_dst[ix] ||
	     src != ntohl(GET_IP4_HDR(frag)->src) ||
	     ip4h->proto != GET_IP4_HDR(frag)->proto)) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
		NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
		ip_freef(ix);
		}

	frag = ip_frag_queue[ix];
	if (frag == NULL) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN], 1);

		/* ������ ID �ʤ顢���襢�ɥ쥹����¸���ơ����塼�ˤĤʤ���*/
		frag_dst  [ix] = dst;
		ip_frag_queue[ix] = input;
		((T_QIP4_HDR *)ip4h)->next = NULL;
		input = NULL;

		/* �ƹ��������ॢ���Ȥ����ꤹ�롣*/
		ip4h->ttl = IP4_FRAGTTL;
		}
	else {

		/* ���������֤��������롣*/
		prev = NULL;
		while (frag != NULL &&
		       IP4_FLGOFF_OFF(ip4h->flg_off) >
		       IP4_FLGOFF_OFF(GET_QIP4_HDR(frag)->flg_off)) {
			prev = frag;
			frag = GET_QIP4_HDR(frag)->next;
			}
		((T_QIP4_HDR *)ip4h)->next = frag;
		if (prev == NULL) {
			ip4h->ttl      = GET_QIP4_HDR(frag)->ttl;
			ip_frag_queue[ix] = input;
			}
		else
			GET_QIP4_HDR(prev)->next = input;
		input = NULL;

		/* ���ƤΥե饰���Ȥ�·�äƤ��뤫Ĵ�٤롣*/
		off = 0;
		for (frag = ip_frag_queue[ix]; frag != NULL; frag = GET_QIP4_HDR(frag)->next) {
			if ((IP4_FLGOFF_OFF(GET_QIP4_HDR(frag)->flg_off) << 3) != off) {
				/* ���椬ȴ���Ƥ����齪λ���롣*/
				syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
				return NULL;
				}
			off += ntohs(GET_QIP4_HDR(frag)->len) - (IP4_VHL_HL(GET_QIP4_HDR(frag)->vhl) << 2);
			prev = frag;				
			}

		/* ���ƤΥե饰���Ȥ�·�ä���ƹ������롣*/
		if ((GET_QIP4_HDR(prev)->flg_off & IP4_MF) == 0) {

			/* �ͥåȥ���Хåե���������롣*/
			if (tget_net_buf(&input, IF_IP4_HDR_SIZE + off, TMO_IP4_FRAG_GET_NET_BUF) == E_OK) {
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_OK], 1);
				NET_COUNT_MIB(ip_stats.ipReasmOKs, 1);

				/* IPv4 �إå������ꤹ�롣*/
				frag  = ip_frag_queue[ix];
				ip4h  = GET_IP4_HDR(input);
				*ip4h = *GET_IP4_HDR(frag);
				ip4h->dst     = htonl(frag_dst[ix]);
				ip4h->len     = htons(IP4_HDR_SIZE + off);
				ip4h->vhl     = IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
				ip4h->ttl     = GET_QIP4_HDR(prev)->ttl;
				ip4h->flg_off = ip4h->id = 0;

				/* �ǡ���������ƹ������롣*/
				off = IP4_HDR_SIZE;
				while (frag != NULL) {
					len = ntohs(GET_QIP4_HDR(frag)->len) - (IP4_VHL_HL(GET_QIP4_HDR(frag)->vhl) << 2);
					memcpy((uint8_t *)ip4h + off, GET_QIP4_SDU(frag), len);
					off += len;
					frag = GET_QIP4_HDR(frag)->next;
					}
				}
			else {
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_NO_BUF], 1);
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
				NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
				}
			/* ���塼����ˤ��롣*/
			ip_freef(ix);
			}
		}
	syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
	return input;
	}

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

/*
 *  ip_init -- IP �ν����
 */

void
ip_init (void)
{
	in4_init();
	}

/*
 *  ip_remove_options -- IPv4 �إå��Υ��ץ������������ʹߤ����˵ͤ�롣
 */

ER
ip_remove_options (T_NET_BUF *nbuf)
{
	T_IP_HDR	*iph;

	iph  = GET_IP_HDR(nbuf);

	if (GET_IP_HDR_SIZE(iph) > IP4_HDR_SIZE) {
		memmove((char *)iph + IP4_HDR_SIZE, GET_IP_SDU(nbuf),
		        (size_t)(iph->len - GET_IP_HDR_SIZE(iph)));
		iph->vhl   = IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
		iph->len  -= (uint16_t)(GET_IP_HDR_SIZE(iph) - IP4_HDR_SIZE);
		nbuf->len -= (uint16_t)(GET_IP_HDR_SIZE(iph) - IP4_HDR_SIZE);
		}

	return E_OK;
	}

/*
 *  ip_input -- IP �����ϴؿ�
 */

#if defined(SUPPORT_IPSEC)
/*
 * TODO: IPsec SP�򸡺������ѥ��åȤ�ꥸ�����Ȥ��뤫�ɤ���Ƚ�ꤹ��������������
 */
#endif /* of defined(SUPPORT_IPSEC) */

void
ip_input (T_NET_BUF *input)
{
	T_IP4_HDR	*ip4h;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN4_ADDR	dst, src, bc;
	uint_t		hlen, off;

	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_OCTETS], input->len - IF_HDR_SIZE);
	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_PACKETS], 1);
	NET_COUNT_MIB(ip_stats.ipInReceives, 1);

	/* IP �إå���Ĺ��������å����롣*/
	if (input->len < IF_IP4_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	ip4h  = GET_IP4_HDR(input);
	hlen = GET_IP4_HDR_SIZE(ip4h);

	/* �С�����������å����롣*/
	if (IP4_VHL_V(ip4h->vhl) != IPV4_VERSION) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_VER], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* IP �إå���Ĺ��������å��������ץ�������Ϥ��롣*/
	if (hlen > IP4_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OPTS], 1);
		/* %%% ���ץ����β��� %%% */
		}

	/* �ǡ��������Ĺ������å����롣*/
	if (ntohs(ip4h->len) > input->len - IF_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* �ͥåȥ���Хåե���Ĺ����ǡ��������Ĺ��Ĵ�����롣*/
	input->len = (uint16_t)(ntohs(ip4h->len) + IF_HDR_SIZE);

	/* �����å����������å����롣*/
	if (in_cksum(ip4h, hlen) != 0) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_CKSUM], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* IP �إå���Ĺ��������å�������̤� ICMP �ʳ��ϥ��ץ�����õ�롣*/
	if (hlen > IP4_HDR_SIZE && ip4h->proto != IPPROTO_ICMP) {
		memset((uint8_t*)ip4h + IP4_HDR_SIZE, 0, hlen - IP4_HDR_SIZE);
		}

	/* ���������ɥ쥹������å����롣*/
	src = ntohl(ip4h->src);
	bc  = (ifp->in_ifaddr.addr & ifp->in_ifaddr.mask) | ~ifp->in_ifaddr.mask;

#ifdef SUPPORT_LOOP

	if (src == bc || src == IPV4_ADDR_BROADCAST || src == IPV4_ADDRANY) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#else	/* of #ifdef SUPPORT_LOOP */

	if (src == ifp->in_ifaddr.addr || src == bc || src == IPV4_ADDR_BROADCAST || src == IPV4_ADDRANY) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#endif	/* of #ifdef SUPPORT_LOOP */

	/* �����襢�ɥ쥹������å����롣*/
	dst = ntohl(ip4h->dst);

#ifdef DHCP_CFG

	/*
	 *  DHCP_CFG ���������Ƥ���Ȥ��ϡ������륢�ɥ쥹��̤�����
	 *  ����ǡ���������������롣
	 */

	if ((ifp->in_ifaddr.addr != IPV4_ADDRANY) &&
	    (!(dst == ifp->in_ifaddr.addr || dst == bc ||
	       dst == IPV4_ADDR_BROADCAST || dst == IPV4_ADDRANY))) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#else	/* of #ifdef DHCP_CFG */

	if (!(dst == ifp->in_ifaddr.addr || dst == bc ||
	      dst == IPV4_ADDR_BROADCAST || dst == IPV4_ADDRANY)) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#endif	/* of #ifdef DHCP_CFG */

#ifdef IP4_CFG_FRAGMENT

	/* ʬ�䤵��Ƥ��뤫�����å����롣*/
	if (ntohs(ip4h->flg_off) & (IP4_MF | IP4_OFFMASK)) {
		if ((input = ip_reass(ip4h, input)) == NULL)
			return;
		}

#else	/* of #ifdef IP4_CFG_FRAGMENT */

	/* ʬ�䤵��Ƥ��뤫�����å����롣*/
	if (ntohs(ip4h->flg_off) & (IP4_MF | IP4_OFFMASK)) {
		T_IN4_ADDR	src;

		NET_COUNT_MIB(ip_stats.ipReasmReqds, 1);
		if ((ntohs(ip4h->flg_off) & IP4_OFFMASK) == 0) {
			NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
			}
		src = ntohl(ip4h->src);
		syslog(LOG_WARNING, "[IP] flaged src: %s.", ip2str(NULL, &src));
		goto buf_rel;
		}

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

	off  = (uint_t)(GET_IP4_SDU(input) - input->buf);

#if defined(SUPPORT_IPSEC)
	/* ������ipsec4_in_reject��¹Ԥ��� */
	if ((ip4h->proto != IPPROTO_ESP) && ipsec4_in_reject (input)) {
		goto buf_rel;
	}
#endif /* of #if defined(SUPPORT_IPSEC) */

	/* �ץ�ȥ�������򤹤� */
	switch (ip4h->proto) {

#ifdef SUPPORT_UDP
	case IPPROTO_UDP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		udp_input(&input, &off, NULL);
		return;
		break;
#endif	/* of #ifdef SUPPORT_UDP */

#ifdef SUPPORT_TCP
	case IPPROTO_TCP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		tcp_input(&input, &off, NULL);
		return;
		break;
#endif	/* of #ifdef SUPPORT_UDP */

	case IPPROTO_ICMP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		icmp_input(&input, &off, NULL);
		return;
		break;

#if defined(SUPPORT_IPSEC)
	case IPPROTO_ESP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		esp4_input(input, &off);
		return;
		break;
#endif /* of #if defined(SUPPORT_IPSEC) */

	default:
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_PROTO], 1);
		NET_COUNT_MIB(ip_stats.ipInUnknownProtos, 1);

		/* ������ IP ���ɥ쥹���Ϥ����ǡ��������Τ� ICMP ���顼�����Τ��롣*/
		if (dst == ifp->in_ifaddr.addr) {
			T_IN4_ADDR	src;

			src = ntohl(ip4h->src);
			syslog(LOG_INFO, "[IP] unexp proto: %d, src=%s.", ip4h->proto, ip2str(NULL, &src));
			icmp_error(ICMP4_UNREACH_PROTOCOL, input);
			}
		/*
		 *  icmp_error �Ǥϡ��ͥåȥ���Хåե� input ���ֵѤ��ʤ��Τ�
		 *  �������Ƥ��齪λ���롣
		 */
		break;
		}

buf_rel:
	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}
