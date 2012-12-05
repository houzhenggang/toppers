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
 *  @(#) $Id: ip6_output.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/ip6_output.c,v 1.43 2002/10/31 19:45:48 ume Exp $	*/
/*	$KAME: ip6_output.c,v 1.279 2002/01/26 06:12:30 jinmei Exp $	*/

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
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
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
 *	@(#)ip_output.c	8.3 (Berkeley) 1/21/94
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
#include <net/if_arp.h>
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

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �����ѿ�
 */

/* ��� MTU */

uint32_t	linkmtu = IF_MTU;

/*
 *  �ɽ��ѿ�
 */

#ifdef IP6_CFG_FRAGMENT

static uint32_t	ip6_id;

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

/*
 *  ip6_output -- IPv6 �ν��ϴؿ�
 */

ER
ip6_output (T_NET_BUF *output, uint16_t flags, TMO tmout)
{
	T_IP6_HDR	*ip6h;
	T_IN6_ADDR	*gw;
	T_IFNET		*ifp = IF_GET_IFNET();
	ER		error = E_OK;

#ifdef IP6_CFG_FRAGMENT

	T_IP6_HDR	*fip6h;
	T_IP6_FRAG_HDR	*fip6f;
	T_NET_BUF	*frag;
	uint32_t	mtu, id;
	uint16_t	plen, foff, flen;
	uint8_t		nextproto;
	bool_t		alwaysfrag = false;

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

	ip6h = GET_IP6_HDR(output);

	NET_COUNT_IP6(net_count_ip6[NC_IP6_OUT_OCTETS],
	              GET_IP_HDR_SIZE(ip6h) + GET_IP_SDU_SIZE(ip6h));
	NET_COUNT_IP6(net_count_ip6[NC_IP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutRequests, 1);

	/*
	 *  ��ʣ���ɥ쥹���������ʳ��ˤϡ����������ɥ쥹��
	 *  ̵��������Ǥ��ʤ���
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src) && (flags & IPV6_OUT_FLG_DAD) == 0) {
		error = E_PAR;
		goto drop;
		}

	/* ���������ɥ쥹�ˤϥޥ�����㥹�ȥ��ɥ쥹�����Ǥ��ʤ���*/
	if (IN6_IS_ADDR_MULTICAST(&ip6h->src)) {
		error = E_PAR;
		goto drop;
		}

	/*
	 *  ��ϩ�����Ԥ���
	 */
	if ((gw = in6_rtalloc(ifp, &ip6h->dst)) == NULL) {
		error = E_PAR;
		goto drop;
		}

	if (!IN6_IS_ADDR_MULTICAST(&ip6h->dst)) {
		/* ��˥��㥹�ȥ��ɥ쥹�ν��� */
		}
	else {
		/* �ޥ�����㥹�ȥ��ɥ쥹�ν��� */
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutMcastPkts, 1);
		if (flags & IPV6_OUT_FLG_HOP_LIMIT)
			ip6h->hlim = IPV6_OUT_GET_HOP_LIMIT(flags);
		else
			ip6h->hlim = IPV6_DEFAULT_MULTICAST_HOPS;
		}

	/* Traffic Class �� Flow Label �򥵥ݡ��Ȥ��ʤ��Τ� 0 �����ꤹ�롣*/
	ip6h->vcf = htonl(IP6_MAKE_VCF(IPV6_VERSION, 0));

#ifdef IP6_CFG_FRAGMENT


#if NUM_IN6_HOSTCACHE_ENTRY > 0

	mtu = in6_hostcache_getmtu(&ip6h->dst);

	if (0 < mtu && mtu <= IPV6_MMTU) {

		/*
		 *  Path MTU ����Ͽ����Ƥ����硢
		 *  MTU �� IPv6 MMTU��1280 �����ƥåȡ˰ʲ��ξ��ϡ�
		 *  MTU �� IPv6 MMTU �����ꤷʬ�䤷���������롣
		 */
		mtu = IPV6_MMTU;
		alwaysfrag = true;
		}
	else if (mtu == 0)
		mtu  = linkmtu;

#else	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

	mtu  = linkmtu;

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

	plen = ntohs(ip6h->plen);
	if (plen + IP6_HDR_SIZE <= mtu && !alwaysfrag) {

		/* ʬ�䤹��ɬ�פ��ʤ��Ȥ��ν��� */
		if ((error = nd6_output(ifp, output, gw, NULL, tmout)) != E_OK) {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_OUT_ERR_PACKETS], 1);
			NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutDiscards, 1);
			}
		}
	else {

		/* ���� ID �����ꤹ�롣*/
		id = ip6_id ++;

		/* MTU �� IPv6 �κ���ѥ��åȥ�������Ķ���ʤ��褦�ˤ��롣*/
		if (mtu > IPV6_MAXPACKET)
			mtu = IPV6_MAXPACKET;

		/*
		 *  MTU ���顢ʬ����ǽ��ʬ��TINET-1.4 �Ǥϡ�ʬ��إå��ʳ���
		 *  ��ĥ�إå��ν��Ϥ�̤�����Τ��� 0 �����ƥåȡ�
		 *  �����ҥإå��Υ�������������Ȥ���8 �����ƥåȰʾ�ʤ����
		 *  ʬ�䤷�������Ǥ��ʤ����ᥨ�顼�ˤ��롣
		 */
		if (((mtu - sizeof(T_IP6_FRAG_HDR)) & ~7) < 8) {
			error = E_PAR;
			goto drop;
			}

		/*
		 *  IPv6 �إå��� next �ե�����ɤ����ꤹ���ͤϡ����ҥإå���
		 *  ���ҥإå���  next �ե�����ɤ����ꤹ���ͤϡ�
		 *  ���Υǡ��������� next �ե�����ɤ��͡�
		 */
		nextproto  = ip6h->next;
		ip6h->next = IPPROTO_FRAGMENT;

		/* ʬ�䤷���������롣*/
		NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_OUT], 1);
		for (foff = 0; foff < plen; foff += flen) {

			/* ���Ҥ�Ĺ����׻�����8 �����ƥåȶ�����Ĵ�����롣*/
			if (foff + (mtu - (IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR))) < plen)
				flen = (mtu - (IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR))) >> 3 << 3;
			else
				flen = plen - foff;

			/* �ͥåȥ���Хåե���������롣*/
			if (tget_net_buf(&frag, flen + IF_IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR), TMO_IP6_FRAG_GET_NET_BUF) == E_OK) {

				/* IPv6 �إå��򥳥ԡ����롣*/
				fip6h = GET_IP6_HDR(frag);
				*fip6h = *ip6h;

				/* IPv6 �إå������롣*/
				fip6h->plen	= htons(flen + sizeof(T_IP6_FRAG_HDR));

				/* ���ҥإå������롣*/
				fip6f = (T_IP6_FRAG_HDR *)GET_IP6_NEXT_HDR(frag);
				fip6f->off_flag	= htons((uint16_t)(foff & ~7));
				if (foff + (mtu - (IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR))) < plen)
					fip6f->off_flag	|= IP6F_MORE_FRAG;
				fip6f->reserved	= 0;
				fip6f->ident	= htonl(id);
				fip6f->next	= nextproto;

				/* SDU �򥳥ԡ����롣*/
				memcpy((uint8_t*)(fip6f + 1), GET_IP6_NEXT_HDR(output) + foff, flen);
				NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_OUT_FRAGS], 1);
				NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutFragCreates, 1);

				/* �������롣*/
				if ((error = nd6_output(ifp, frag, gw, NULL, tmout)) != E_OK) {
					NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutFragFails, 1);
					goto drop;
					}
				}
			else {
				/* �ͥåȥ���Хåե��������Ǥ��ʤ���С������򤢤����롣*/
				error = E_NOMEM;
				goto drop;
				}
			}

		/* IF �ǥͥåȥ���Хåե��������ʤ��ե饰������å����롣*/
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;

		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutFragOKs, 1);
		}

#else	/* #ifdef IP6_CFG_FRAGMENT */

	if ((error = nd6_output(ifp, output, gw, NULL, tmout)) != E_OK) {
		NET_COUNT_IP6(net_count_ip6[NC_IP6_OUT_ERR_PACKETS], 1);
		NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutDiscards, 1);
		}

#endif	/* #ifdef IP6_CFG_FRAGMENT */

	return error;

drop:
	/* IF �ǥͥåȥ���Хåե��������ʤ��ե饰������å����롣*/
	if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
		syscall(rel_net_buf(output));
		}
	else
		output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;

	NET_COUNT_IP6(net_count_ip6[NC_IP6_OUT_ERR_PACKETS], 1);
	NET_COUNT_MIB(in6_ifstat.ipv6IfStatsOutDiscards, 1);
	return error;
	}

#endif /* of #ifdef SUPPORT_INET6 */
