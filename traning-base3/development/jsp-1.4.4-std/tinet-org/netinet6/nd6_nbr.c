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
 *  @(#) $Id: nd6_nbr.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6_nbr.c,v 1.13 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: nd6_nbr.c,v 1.86 2002/01/21 02:33:04 jinmei Exp $	*/

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

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

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
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>

#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <netinet6/ip6_var.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �ɽ�ؿ�
 */

static void nd6_dad_timer (T_IN6_IFADDR *ifa);
static void nd6_dad_duplicated (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_ns_output (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_ns_input (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_na_input (T_IFNET *ifp, T_IN6_IFADDR *ifa);

/*
 *  nd6_dad_duplicated -- ��ʣ���ɥ쥹�򸡽Ф������ν���
 */

static void
nd6_dad_duplicated (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	if ((ifa->flags & IN6_IFF_TENTATIVE) == 0)
		syslog(LOG_ERROR, "[ND6 DAD DUP] no pending.");
	else {
		syslog(LOG_ERROR, "[ND6 DAD DUP] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		ifa->flags |=  IN6_IFF_DUPLICATED;

		/* �����ޡ�����ߤ��롣*/
		untimeout((callout_func)nd6_dad_timer, ifa);

		/*
		 *  �⤷ IPv6 ���ɥ쥹������ˡ����˳�����Ƥ餿
		 * �ʥ������ͥå��Ѥ� EUI-64�˥ϡ��ɥ��������ɥ쥹��١����Ȥ���
		 *  ���󥿥ե����� ID ���������줿�ΤǤ���С�
		 *  ���Υ��󥿥ե������Ǥ� IPv6 ��ư���̵���ˤ��٤��Ǥ���
		 * ��RFC2462bis-03 ��������� 5.4.5�ˡ�
		 */
		if (IN6_IS_ADDR_LINKLOCAL(&ifa->addr))
			ifp->flags |= ND6_IFF_IFDISABLED;
		}
	}

/*
 *  nd6_dad_ns_output -- ��ʣ���ɥ쥹���� (DAD) ��������Ϥ��롣
 */

static void
nd6_dad_ns_output (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_DAD_OUT_PACKETS], 1);

	ifa->ns_ocount ++;
	nd6_ns_output(ifp, &in6_addr_unspecified, &ifa->addr, NULL, true);
	}

/*
 *  nd6_dad_ns_input -- ��ʣ���ɥ쥹���� (DAD) ��������
 */

static void
nd6_dad_ns_input (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	/*
	 *  �ޤ�����ʣ���ɥ쥹������������Ϥ��Ƥ��ʤ����
	 */
	if (ifa->ns_ocount == 0)
		nd6_dad_duplicated(ifp, ifa);
	else
		ifa->ns_icount ++;
	}

/*
 *  nd6_dad_na_input -- ��ʣ���ɥ쥹���� (DAD) ��������
 */

static void
nd6_dad_na_input (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NA_IN_PACKETS], 1);
	ifa->na_icount ++;
	nd6_dad_duplicated(ifp, ifa);
	}

/*
 *  nd6_dad_timer -- ��ʣ���ɥ쥹���� (DAD) �����ޡ�
 */

static void
nd6_dad_timer (T_IN6_IFADDR *ifa)
{
	T_IFNET *ifp = IF_GET_IFNET();

	if (ifa->flags & IN6_IFF_DUPLICATED) {
		syslog(LOG_ERROR, "[ND6 DAD] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		return;
		}

	if ((ifa->flags & IN6_IFF_TENTATIVE) == 0) {
		syslog(LOG_ERROR, "[ND6 DAD] no tentative IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		return;
		}

	if (ifa->ns_ocount < NUM_IP6_DAD_COUNT) {
		nd6_dad_ns_output(ifp, ifa);

		/* �����ॢ���Ȥ����õ���������ֳ֤����ꤹ�롣*/
		timeout((callout_func)nd6_dad_timer, ifa, ND6_RETRANS_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		}
	else if (ifa->na_icount || ifa->ns_icount)
		nd6_dad_duplicated(ifp, ifa);
	else {
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		syslog(LOG_NOTICE, "[ND6 DAD] no dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		}
	}

/*
 *  nd6_ns_input -- �������������Ͻ�����
 */

void
nd6_ns_input (T_NET_BUF *input, uint_t off)
{
	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_NEIGHBOR_SOLICIT_HDR	*nsh;
	T_ND_OPT_HDR		*opth;
	T_IN6_IFADDR		*ifa;
	bool_t			tlladdr;
	uint_t			lladdr_len = 0;
	uint32_t		flags;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �إå��Υ����å����ʲ��ξ����˴����롣
	 *    ���ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �ʳ�
	 *    ���إå�Ĺ��û��
	 */
	if (ip6h->hlim != IPV6_MAXHLIM || input->len - off < NEIGHBOR_SOLICIT_HDR_SIZE)
		goto err_ret;

	nsh  = (T_NEIGHBOR_SOLICIT_HDR *)(input->buf + off);

	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src)) {
		/*
		 *  �������ɥ쥹��̵����ʤ顢��ʣ���ɥ쥹����
		 *  �����襢�ɥ쥹�ϡ������ޥ�����㥹�ȤǤʤ���Фʤ�ʤ���
		 */
		if (!IN6_IS_ADDR_NS_MULTICAST(&ip6h->dst))
			goto err_ret;
		}

	/* ��Ū���ɥ쥹���ޥ�����㥹�Ȥʤ饨�顼 */
	if (IN6_IS_ADDR_MULTICAST(&nsh->target))
		goto err_ret;

	/* ����õ�����ץ����Υ��ե��åȤ�Ͽ���롣*/
	if (nd6_options(nd_opt_off, input->buf + (off + NEIGHBOR_SOLICIT_HDR_SIZE),
	                            input->len - (off + NEIGHBOR_SOLICIT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* ����õ�����ץ���� (������󥯥��ɥ쥹) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + NEIGHBOR_SOLICIT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)] - 8);
	 	/* ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src) && lladdr != NULL)
		goto err_ret;

	/* ���襢�ɥ쥹���ޥ�����㥹�Ȥʤ�������Τ˥ǡ�������ؤΥ��ɥ쥹���դ��롣*/
	if (IN6_IS_ADDR_MULTICAST(&ip6h->dst))
		tlladdr = true;
	else
		tlladdr = false;

	/*
	 *  ��Ū���ɥ쥹������ʬ�Υͥåȥ�����󥿥ե�������
	 *  ������Ƥ��Ƥ��륢�ɥ쥹��Ĵ�٤롣
	 *  �ʤ������������ӥ��ϼ������Ƥ��ʤ���
	 */
	ifa = in6_lookup_ifaddr(ifp, &nsh->target);

	if (ifa == NULL)
		goto free_ret;

	/* õ����̥��ɥ쥹����ʣ���Ƥ���б������ʤ��ǽ�λ���롣*/
	if (ifa->flags & IN6_IFF_DUPLICATED)
		goto err_ret;

	/*
	 *  �ͥåȥ�����󥿥ե������Υ��ɥ쥹Ĺ�����פ��ʤ���Х��顼
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/*
	 *  �������ɥ쥹����ʬ�Υ��ɥ쥹�Ȱ��פ���н�ʣ���Ƥ��롣
	 */
	if (IN6_ARE_ADDR_EQUAL(&ifa->addr, &ip6h->src))
		goto free_ret;

	/* ��ʣ������ˡ�������������������Ȥ��ν��� */
	if (ifa->flags & IN6_IFF_TENTATIVE) {
		if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src))
			nd6_dad_ns_input(ifp, ifa);
		goto free_ret;
		}

	if ((ifa->flags & IN6_IFF_ANYCAST) || !tlladdr)
		flags = 0;
	else
		flags = ND_NA_FLG_OVERRIDE;

	/*
	 *  �������ɥ쥹��̵����ʤ顢�������Ͻ�ʣ���ɥ쥹������ǡ�
	 *  ľ���������뤳�ȤϤǤ��ʤ��Τǡ����Ρ��ɥޥ�����㥹��
	 *  ���ɥ쥹���������롣
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src)) {
		nd6_na_output(ifp, &in6_addr_linklocal_allnodes, &nsh->target, flags, tlladdr);
		goto free_ret;
		}

	/* ���٥���å������Ͽ���롣*/
	nd6_cache_lladdr(ifp, &ip6h->src, (T_IF_ADDR *)lladdr, ND_NEIGHBOR_SOLICIT, 0);

	nd6_na_output(ifp, &ip6h->src, &nsh->target, flags | ND_NA_FLG_SOLICITED, tlladdr);

free_ret:
	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

/*
 *  nd6_ns_output -- ������������Ϥ��롣
 */

void
nd6_ns_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
               T_IN6_ADDR *taddr, T_LLINFO_ND6 *ln, bool_t dad)
{
	T_NEIGHBOR_SOLICIT_HDR	*nsh;
	T_NET_BUF		*output;
	T_IP6_HDR		*ip6h;
	T_IF_ADDR		*mac = NULL;
	uint_t			len;
	uint16_t		ipflags = 0;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_OUT_PACKETS], 1);

	if (IN6_IS_ADDR_MULTICAST(taddr))
		return;

	/* ���������ڥ�����Ĺ��׻����롣*/
	if (!dad && IF_SOFTC_TO_IFADDR(ifp->ic))
		len = (NEIGHBOR_SOLICIT_HDR_SIZE + ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
	else
		len = (NEIGHBOR_SOLICIT_HDR_SIZE + 7) >> 3 << 3;

	/*
	 *  �����ޥ�����㥹�ȡ����ɥ쥹���ζ���õ���Ǥϡ�
	 *  ¾�Υ�󥯤���ε�¤���줿�ǡ���������
	 *  �ӽ����뤿�ᡢ�ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �����ꤹ�롣
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(daddr) || IN6_IS_ADDR_MULTICAST(daddr))
		ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM);

	/* �ͥåȥ���Хåե����������IPv6 �إå������ꤹ�롣*/
	if (in6_get_datagram(&output, len, 0, daddr, NULL,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ND6_NS_OUTPUT) != E_OK)
		return;

	ip6h = GET_IP6_HDR(output);

	if (IN6_IS_ADDR_UNSPECIFIED(daddr)) {

		/* ���襢�ɥ쥹��̵����ξ��ϡ������ޥ�����㥹�ȥ��ɥ쥹�����ꤹ�롣*/
		ip6h->dst.s6_addr32[0] = IPV6_ADDR_INT32_MLL;
		ip6h->dst.s6_addr32[2] = IPV6_ADDR_INT32_ONE;
		ip6h->dst.s6_addr32[3] = taddr->s6_addr32[3];
		ip6h->dst.s6_addr8[12] = 0xff;
		}

	/* ���������ɥ쥹������ */
	if (!dad) {

		/* ��ʣ���ɥ쥹���ФǤϤʤ��������������ɥ쥹���������*/
		T_IN6_ADDR *saddr;

		if (ln && ln->hold) {
			/*
			 * �������ڥ�ǥ��󥰤���Ƥ���ǡ���������
			 * ���������ɥ쥹�����Ѥ��롣
			 */
			if (ln->hold->len > IF_IP6_HDR_SIZE)
				saddr = &GET_IP6_HDR(ln->hold)->src;
			else
				saddr = NULL;
			}
		else
			saddr = NULL;

		if (saddr && in6_lookup_ifaddr(ifp, saddr))
			ip6h->src = *saddr;
		else {
			/*
			 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
			 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
			 */
			T_IN6_IFADDR *ifa;

			if ((ifa = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
				syscall(rel_net_buf(output));
				return;
				}
			ip6h->src = ifa->addr;
			}
		}
	else {

		/* ��ʣ���ɥ쥹���л������������ɥ쥹��̵���ꡣ*/
		memset(&ip6h->src, 0, sizeof(T_IN6_ADDR));
		}

 	/* ���������إå������ꤹ�롣*/
 	nsh = GET_NEIGHBOR_SOLICIT_HDR(output, IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET);
 	nsh->hdr.type        = ND_NEIGHBOR_SOLICIT;
 	nsh->hdr.code        = 0;
 	nsh->hdr.data.data32 = 0;
 	nsh->target          = *taddr;

	if (!dad && (mac = IF_SOFTC_TO_IFADDR(ifp->ic)) != NULL) {

		/* ����õ�����ץ����Ȥ��ơ�õ����ɸ�� MAC ���ɥ쥹�����ꤹ�롣*/
		T_ND_OPT_HDR	*opth;
		uint_t		optlen;

		opth   = (T_ND_OPT_HDR *)GET_NEIGHBOR_SOLICIT_SDU(output, IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET);
		optlen = (ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
		memset(opth, 0, optlen);
		opth->type = ND_OPT_SOURCE_LINKADDR;
		opth->len  = optlen >> 3;
		memcpy((uint8_t *)opth + sizeof(T_ND_OPT_HDR), mac, sizeof(T_IF_ADDR));
		}

	/* �����å������׻����롣*/
	nsh->hdr.sum = 0;
	nsh->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)nsh - output->buf, len);

	/* �������롣*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutNeighborSolicits, 1);
	ip6_output(output, ipflags | IPV6_OUT_FLG_DAD, TMO_ND6_NS_OUTPUT);
	}

/*
 *  nd6_na_input -- �������Τ����Ͻ�����
 */

void
nd6_na_input (T_NET_BUF *input, uint_t off)
{
	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_NEIGHBOR_ADVERT_HDR	*nah;
	T_ND_OPT_HDR		*opth;
	T_IN6_IFADDR		*ifa;
	T_LLINFO_ND6		*ln;
	SYSTIM			now;
	bool_t			llchange;
	uint_t			lladdr_len = 0;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �إå��Υ����å����ʲ��ξ����˴����롣
	 *    ���ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �ʳ�
	 *    ���إå�Ĺ��û��
	 */
	if (ip6h->hlim != IPV6_MAXHLIM || input->len - off < NEIGHBOR_ADVERT_HDR_SIZE)
		goto err_ret;

	nah  = (T_NEIGHBOR_ADVERT_HDR *)(input->buf + off);

	/* ��Ū���ɥ쥹���ޥ�����㥹�Ȥʤ饨�顼 */
	if (IN6_IS_ADDR_MULTICAST(&nah->target))
		goto err_ret;

	/* ���������ؤα����ǡ����襢�ɥ쥹���ޥ�����㥹�Ȥʤ饨�顼 */
	if ((nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) &&
	    IN6_IS_ADDR_MULTICAST(&ip6h->dst))
		goto err_ret;

	/* ����õ�����ץ����Υ��ե��åȤ�Ͽ���롣*/
	if (nd6_options(nd_opt_off, input->buf + (off + NEIGHBOR_ADVERT_HDR_SIZE), 
	                            input->len - (off + NEIGHBOR_ADVERT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* ����õ�����ץ���� (��Ū��󥯥��ɥ쥹) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + NEIGHBOR_ADVERT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)] - 8);
	 	/* ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	ifa = in6_lookup_ifaddr(ifp, &nah->target);

	/*
	 *  ��Ū���ɥ쥹����ʬ�Υͥåȥ�����󥿥ե������˳�����Ƥ��Ƥ��륢�ɥ쥹��
	 *  �����줫�˰��פ����Ȥ��ϡ���ʣ���Ƥ��뤳�Ȥ��̣���Ƥ��롣
	 */
	if (ifa) {
		if (ifa->flags & IN6_IFF_TENTATIVE)
			nd6_dad_na_input(ifp, ifa);
		else
			syslog(LOG_ERROR, "[ND6 NA INPUT] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		goto err_ret;
		}

	/*
	 *  �ͥåȥ�����󥿥ե������Υ��ɥ쥹Ĺ�����פ��ʤ���Х��顼
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* ���٥���å����õ�����롣*/
	syscall(wai_sem(SEM_ND6_CACHE));
	if ((ln = nd6_lookup(&nah->target, false)) == NULL)
		goto free_ret;

	/* ���٥���å���ξ��֤����ǡ�������ؤΥ��ɥ쥹̤���ξ�� */
	if (ln->state == ND6_LLINFO_INCOMPLETE) {
		/* ���Τ��줿�ǡ�������ؤΥ��ɥ쥹��Ĺ���� 0 �ξ�� */
		if (lladdr == NULL)
			goto free_ret;

		ln->ifaddr = *(T_IF_ADDR *)lladdr;
		if (nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) {
			ln->state = ND6_LLINFO_REACHABLE;
			/*ln->byhint = 0*/;
			if (ln->expire) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_REACHABLE_TIME;
				}
			}
		else {
			syscall(get_tim(&now));
			ln->expire = now + ND6_GCOLLECTION_TIME;
			ln->state  = ND6_LLINFO_STALE;
			}

		if ((nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) != 0)
			ln->flags |=  ND6_LLIF_ROUTER;
		else
			ln->flags &= ~ND6_LLIF_ROUTER;
		if ((ln->flags & ND6_LLIF_ROUTER) != 0)
			/*pfxlist_onlink_check()*/;
		}
	else {
		if (lladdr == NULL)
			llchange = false;
		else if (memcmp(lladdr, &ln->ifaddr, sizeof(T_IF_ADDR)))
			llchange = true;
		else
			llchange = false;

		/*
		 *  ��������ɽ
		 *
		 *  nd_na_flags_reserved
		 *  OVERRIDE    SOLICTED lladdr llchange ���� (L: lladdr ����Ͽ����)
		 *
		 *      F           F       N      -    (2c)
		 *      F           F       Y      F    (2b) L
		 *      F           F       Y      T    (1)    REACHABLE -> STALE
		 *      F           T       N      -    (2c)           * -> REACHABLE
		 *      F           T       Y      F    (2b) L         * -> REACHABLE
		 *      F           T       Y      T    (1)    REACHABLE -> STALE
		 *      T           F       N      -    (2a)
		 *      T           F       Y      F    (2a) L
		 *      T           F       Y      T    (2a) L         *-> STALE
		 *      T           T       N      -    (2a)           * -> REACHABLE
		 *      T           T       Y      F    (2a) L         * -> REACHABLE
		 *      T           T       Y      T    (2a) L         * -> REACHABLE
		 */
		if ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) == 0 && (lladdr != NULL && llchange)) {	/* (1) */
			/* ���֤� REACHABLE �ʤ� STALE �����ܤ��롣*/
			if (ln->state == ND6_LLINFO_REACHABLE) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_GCOLLECTION_TIME;
				ln->state  = ND6_LLINFO_STALE;
				}
			goto free_ret;
			}
		else if ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) ||						/* (2a) */
		         ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) == 0 && (lladdr != NULL && !llchange)) ||	/* (2b) */
		         lladdr == NULL) {										/* (2c) */

			/* �ǡ�������ؤΥ��ɥ쥹�����Τ���Ƥ���й������롣*/
			if (lladdr != NULL)
				ln->ifaddr = *(T_IF_ADDR *)lladdr;

			/* ���������ؤα����ʤ� REACHABLE �����ܤ��롣*/
			if (nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) {
				ln->state = ND6_LLINFO_REACHABLE;
				/*ln->byhint = 0*/;
				if (ln->expire) {
					syscall(get_tim(&now));
					ln->expire = now + ND6_REACHABLE_TIME;
					}
				}
			/*
			 *  �ǡ�������ؤΥ��ɥ쥹�����Τ��졢
			 *  �ۤʤ륢�ɥ쥹�ʤ鹹�����롣
			 */
			else if (lladdr != NULL && llchange) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_GCOLLECTION_TIME;
				ln->state  = ND6_LLINFO_STALE;
				}
			}

		/* �롼�����Υե饰�ν��� */
		if ((ln->flags        & ND6_LLIF_ROUTER ) != 0 &&
		    (nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) == 0) {
			/*
			 *  ������꤬�롼�����Υե饰��̵���ˤ�����硣
			 *  �ǥ��ե���ȡ��롼���ꥹ�Ȥ����оݤΥ롼����������
			 *  ����õ������å���򹹿����롣
			 */
			T_DEF_ROUTER	*dr = NULL;

			syscall(wai_sem(SEM_ND6_DEFRTRLIST));
			if ((dr = nd6_defrtrlist_lookup(&ln->addr)) != NULL) {
				nd6_defrtrlist_del(dr);
				}
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			}
		if ((nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) != 0)
			ln->flags |=  ND6_LLIF_ROUTER;
		else
			ln->flags &= ~ND6_LLIF_ROUTER;
		}

	ln->asked = 0;

	/* ���ɥ쥹����Ԥ��Υǡ�������ब������������롣*/
	nd6_output_hold(ifp, ln);

free_ret:
	syscall(sig_sem(SEM_ND6_CACHE));
	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

/*
 *  nd6_na_output -- �������Τ���Ϥ��롣
 */

void
nd6_na_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
               T_IN6_ADDR *taddr, uint32_t flags, bool_t tlladdr)
{
	T_NEIGHBOR_ADVERT_HDR	*nah;
	T_NET_BUF		*output;
	T_IP6_HDR		*ip6h;
	T_IN6_IFADDR		*ifa;
	T_IF_ADDR		*mac = NULL;
	uint_t			len;
	uint16_t		ipflags = 0;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NA_OUT_PACKETS], 1);

	/*
	 *  �������Υڥ�����Ĺ��׻����롣
	 *  tlladdr �����ʤ�ͥåȥ�����󥿥ե������Υ��ɥ쥹���ɲä��롣
	 */
	if (tlladdr && IF_SOFTC_TO_IFADDR(ifp->ic))
		len = (NEIGHBOR_ADVERT_HDR_SIZE + ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
	else
		len = (NEIGHBOR_ADVERT_HDR_SIZE + 7) >> 3 << 3;

	/*
	 *  ¾�Υ�󥯤���ε�¤���줿�ǡ���������
	 *  �ӽ����뤿�ᡢ�ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �����ꤹ�롣
	 */
	ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM);

	/* �ͥåȥ���Хåե����������IPv6 �إå������ꤹ�롣*/
	if (in6_get_datagram(&output, len, 0, daddr, NULL,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ND6_NA_OUTPUT) != E_OK)
		return;

	ip6h = GET_IP6_HDR(output);

	if (IN6_IS_ADDR_UNSPECIFIED(daddr)) {
		/*
		 *  ���襢�ɥ쥹��̵����ξ��ϡ�
		 *  ��󥯥��������Ρ��ɡ��ޥ�����㥹�ȥ��ɥ쥹�����ꤹ�롣
		 */
		ip6h->dst.s6_addr32[0] = IPV6_ADDR_INT32_MLL;
		ip6h->dst.s6_addr32[1] = 0;
		ip6h->dst.s6_addr32[2] = 0;
		ip6h->dst.s6_addr32[3] = IPV6_ADDR_INT32_ONE;
		flags &= ~ND_NA_FLG_SOLICITED;
		}
	else
		ip6h->dst = *daddr;

	/*
	 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
	 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
	 */
	if ((ifa = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
		syscall(rel_net_buf(output));
		return;
		}
	ip6h->src = ifa->addr;

 	/* �������Υإå������ꤹ�롣*/
 	nah = GET_NEIGHBOR_ADVERT_HDR(output, IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET);
 	nah->hdr.type        = ND_NEIGHBOR_ADVERT;
 	nah->hdr.code        = 0;
 	nah->target          = *taddr;

	/* tlladdr �����ʤ�ͥåȥ�����󥿥ե������Υ��ɥ쥹���ɲä��롣*/
	if (tlladdr && (mac = IF_SOFTC_TO_IFADDR(ifp->ic)) != NULL) {

		T_ND_OPT_HDR	*opth;
		uint_t		optlen;

		opth   = (T_ND_OPT_HDR *)GET_NEIGHBOR_ADVERT_SDU(output, IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET);
		optlen = (ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
		memset(opth, 0, optlen);
		opth->type = ND_OPT_TARGET_LINKADDR;
		opth->len  = optlen >> 3;
		memcpy((uint8_t *)opth + sizeof(T_ND_OPT_HDR), mac, sizeof(T_IF_ADDR));
		}
	else
		flags &= ~ND_NA_FLG_OVERRIDE;

	nah->nd_na_flags_reserved = flags;

	/* �����å������׻����롣*/
	nah->hdr.sum = 0;
	nah->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)nah - output->buf, len);

	/* �������롣*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutNeighborAdvertisements, 1);
	ip6_output(output, ipflags, TMO_ND6_NS_OUTPUT);
	}

/*
 *  nd6_dad_start -- ��ʣ���ɥ쥹���� (DAD) �򳫻Ϥ��롣
 *
 *    ��3������tick �ϡ����󥿥ե���������ư����Ƥ��顢��ʣ���Ф�
 *    ��������ޤǤκǾ��ٱ��ͤǤ��롣
 */

void
nd6_dad_start (T_IFNET *ifp, T_IN6_IFADDR *ifa, int_t *tick)
{
	/* �ե饰������å����롣*/
	if (!(ifa->flags & IN6_IFF_TENTATIVE))
		return;

#if NUM_IP6_DAD_COUNT == 0

	ifa->flags &= ~IN6_IFF_TENTATIVE;

#else	/* of #if NUM_IP6_DAD_COUNT == 0 */

	if (ifa->flags & IN6_IFF_ANYCAST) {
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		return;
		}
	else if ((ifa->flags & IN6_IFF_TENTATIVE) == 0)
		return;

	/* ��ʣ���ɥ쥹���Х����󥿤�ꥻ�åȤ��롣*/
	ifa->ns_icount = ifa->na_icount = ifa->ns_ocount = 0;

	/*
	 *  ��ʣ���ɥ쥹�����������������롣�����������󥿥ե�������
	 *  ���������ľ��ˡ��ǽ������������ϡ���������ٱ��Ԥ���
	 */
	if (tick == NULL) {
		nd6_dad_ns_output(ifp, ifa);

		/* �����ॢ���Ȥ����õ���������ֳ֤����ꤹ�롣*/
		timeout((callout_func)nd6_dad_timer, ifa, ND6_RETRANS_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		}
	else {
		int_t ntick;

		if (*tick == 0)	/* �ǽ������ */
			ntick = net_rand() % (ND6_FIRST_DAD_DELAY_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		else
			ntick = *tick + net_rand() % (ND6_DAD_DELAY_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		*tick = ntick;
		timeout((callout_func)nd6_dad_timer, ifa, ntick);
		}

#endif	/* of #if NUM_IP6_DAD_COUNT == 0 */

	}

#endif /* of #ifdef SUPPORT_INET6 */
