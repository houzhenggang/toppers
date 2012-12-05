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
 *  @(#) $Id: in6_ifattach.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/in6_ifattach.c,v 1.2.2.5 2001/08/13 16:26:17 ume Exp $	*/
/*	$KAME: in6_ifattach.c,v 1.118 2001/05/24 07:44:00 itojun Exp $	*/

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
#include <net/net.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet6/in6_ifattach.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 * EUI64 �����
 */

#define EUI64_UBIT		0x02

#ifdef SUPPORT_ETHER

/*
 * get_mac6_ifid -- MAC (6 �����ƥå�) ���ɥ쥹�ǡ����󥿥ե��������̻Ҥ����ꤹ�롣
 */

static ER
get_mac6_ifid (T_IFNET *ifp, T_IN6_ADDR *ifra_addr)
{
	ifra_addr->s6_addr[ 8] = ifp->ic->ifaddr.lladdr[0] ^ EUI64_UBIT;
	ifra_addr->s6_addr[ 9] = ifp->ic->ifaddr.lladdr[1];
	ifra_addr->s6_addr[10] = ifp->ic->ifaddr.lladdr[2];
	ifra_addr->s6_addr[11] = UINT_C(0xff);
	ifra_addr->s6_addr[12] = UINT_C(0xfe);
	ifra_addr->s6_addr[13] = ifp->ic->ifaddr.lladdr[3];
	ifra_addr->s6_addr[14] = ifp->ic->ifaddr.lladdr[4];
	ifra_addr->s6_addr[15] = ifp->ic->ifaddr.lladdr[5];

	return E_OK;
	}

#endif	/* of #ifdef SUPPORT_ETHER */

#ifdef IP6_CFG_AUTO_LINKLOCAL

/*
 *  in6_ifattach_linklocal -- ���󥿥ե������˥�󥯥����롦���ɥ쥹�������Ƥ롣
 */

static ER
in6_ifattach_linklocal (T_IFNET *ifp)
{
	T_IN6_ADDR	addr;
	ER		error = E_OK;

	/*
	 *  ��󥯥����롦�ץ�ե��å��� fe80::/64 �����ꤹ�롣
	 */
	addr.s6_addr32[0] = IPV6_ADDR_INT32_ULL;
	addr.s6_addr32[1] = ULONG_C(0);

	/* ���󥿥ե��������̻Ҥ����ꤹ�롣*/
	if ((error = IF_IN6_IFID(ifp, &addr)) != E_OK)
		return error;

	/* ���󥿥ե������Υ��ɥ쥹����򹹿����롣*/
	if ((error = in6_update_ifa(ifp, &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL],
	                            &addr, 64, ND6_INFINITE_LIFETIME,
	                                       ND6_INFINITE_LIFETIME, 
	                                       IN6_RTR_IX_UNREACH, ND6_PREFIX_IX_INVALID, 0)) != E_OK)
		return error;

	return error;
	}

#endif	/* of #ifdef IP6_CFG_AUTO_LINKLOCAL */

/*
 *  in6_ifattach -- ���󥿥ե������˥��ɥ쥹�������Ƥ롣
 */

ER
in6_ifattach (T_IFNET *ifp)
{
	ER error = E_OK;

#ifdef IP6_CFG_AUTO_LINKLOCAL

	if ((ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL].flags & IN6_IFF_DEFINED) == 0)
		if ((error = in6_ifattach_linklocal(ifp)) != E_OK)
			return error;

#endif	/* of #ifdef IP6_CFG_AUTO_LINKLOCAL */

	return error;
	}

#endif /* of #ifdef SUPPORT_INET6 */
