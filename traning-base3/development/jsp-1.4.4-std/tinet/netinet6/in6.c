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
 *  @(#) $Id: in6.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/in6.c,v 1.21 2002/04/19 04:46:22 suz Exp $	*/
/*	$KAME: in6.c,v 1.259 2002/01/21 11:37:50 keiichi Exp $	*/

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
 * Copyright (c) 1982, 1986, 1991, 1993
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
 *	@(#)in.c	8.2 (Berkeley) 11/15/93
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_types.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet6/in6_ifattach.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �����ѿ�
 */

T_IN6_ADDR in6_addr_unspecified =
	IPV6_ADDR_UNSPECIFIED_INIT;

T_IN6_ADDR in6_addr_linklocal_allnodes =
	IPV6_ADDR_LINKLOCAL_ALLNODES_INIT;

T_IN6_ADDR in6_addr_linklocal_allrouters =
	IPV6_ADDR_LINKLOCAL_ALLROUTERS_INIT;

/*
 *  in6_addmulti -- �ޥ�����㥹�ȥ��ɥ쥹����Ͽ���롣
 */

static ER
in6_addmulti (T_IFNET *ifp, T_IN6_ADDR *maddr)
{
	ER	error = E_OK;

	if ((error = if_addmulti(ifp, maddr, AT_INET6)) != E_OK)
		return error;

	return error;
	}

/*
 *  in6_ifinit -- ���󥿥ե������˥��ɥ쥹��������ꤷ����������롣
 */

static ER
in6_ifinit (T_IFNET *ifp, T_IN6_IFADDR *ia, T_IN6_ADDR *addr, uint_t prefix_len)
{
	/* ���ɥ쥹�ȥץ�ե��å���Ĺ�����ꤹ�롣*/
	ia->addr       = *addr;
	ia->prefix_len = prefix_len;

	/* �ե饰���������롣*/
	ia->flags = 0;

	/*
	 *  ���ƥ��ɥ쥹�����ꤵ�줿�Ȥ������󥿥ե������ȼ��ν������Ԥ���
	 */

	return E_OK;
	}

/*
 *  in6_ifainit -- ���󥿥ե��������ɥ쥹��¤�Τν����
 */

void
in6_ifainit (void)
{
	T_IN6_IFADDR	*ia = NULL;
	T_IFNET		*ifp = IF_GET_IFNET();
	int_t 		ix;

	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		ia = &ifp->in_ifaddrs[ix];
		memset(ia, sizeof(T_IN6_IFADDR), 0);
		ia->router_index = IN6_RTR_IX_UNREACH;
		ia->prefix_index = ND6_PREFIX_IX_INVALID;
		}
	}

/*
 *  in6_if2idlen -- ���󥿥ե����� ID Ĺ���֤���
 */

int_t
in6_if2idlen (T_IFNET *ifp)
{
#if IF_TYPE == IFT_ETHER
	return 64;
#else
	return 64;
#endif
	}

/*
 *  in6_addr2ifaix -- ���ɥ쥹���饤�󥿥ե��������ɥ쥹����Υ���ǥå������Ѵ����롣
 */

int_t
in6_addr2ifaix (T_IN6_ADDR *addr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia;
	int_t 		ix;

	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		ia = &ifp->in_ifaddrs[ix];
		if ((ia->flags & IN6_IFF_DEFINED) != 0 &&
		    in6_are_prefix_equal(addr, &ia->addr, ia->prefix_len))
			return ix;
		}

	return IPV6_IFADDR_IX_INVALID;
	}

/*
 *  in6_addr2maix -- ���ɥ쥹����ޥ�����㥹�ȥ��ɥ쥹�Υ���ǥå������Ѵ����롣
 */

int_t
in6_addr2maix (T_IN6_ADDR *addr)
{
	if (addr->s6_addr8[0] == 0xff) {
		if (addr->s6_addr8[1] == 0x02) {
			if (addr->s6_addr8[11] == 0x01 && addr->s6_addr8[12] == 0xff)
				return IPV6_MADDR_IX_SOL_NODE;
			else
				return IPV6_MADDR_IX_LL_ALL_NODE;
			}
		else
			return IPV6_MADDR_IX_EXTRA;
		}
	else
		return IPV6_MADDR_IX_EXTRA;
	}

/*
 *  in6_update_ifa -- ���󥿥ե������Υ��ɥ쥹����򹹿����롣
 */

ER
in6_update_ifa (T_IFNET *ifp, T_IN6_IFADDR *ia, T_IN6_ADDR *addr,
                uint_t prefix_len, uint32_t vltime, uint32_t pltime,
                int_t router_index, int_t prefix_index, uint_t flags)
{
	T_IN6_ADDR	llsol;
	ER		error = E_OK;
	SYSTIM		now;

	/* ����������å����롣*/
	if (addr == NULL)
		return E_PAR;

	/*
	 *  ͭ�����֤�����å����롣
	 *  vltime (ͭ������) �� pltime (�侩ͭ������) ��ñ�̤� [s]��
	 */
	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	if (((vltime != ND6_INFINITE_LIFETIME) && (vltime + now < now)) || vltime == 0)
		return E_PAR;

	if ((pltime != ND6_INFINITE_LIFETIME) && (pltime + now < now))
		return E_PAR;

	/* ���󥿥ե��������������롣*/
	if ((error = in6_ifinit(ifp, ia, addr, prefix_len)) != E_OK)
		return error;

	if (IN6_IS_ADDR_LINKLOCAL(addr)) {

		/* �����ޥ�����㥹�ȥ��ɥ쥹����Ͽ���롣*/
		llsol.s6_addr32[0] = IPV6_ADDR_INT32_MLL;
		llsol.s6_addr32[1] = 0x00000000;
		llsol.s6_addr32[2] = IPV6_ADDR_INT32_ONE;
		llsol.s6_addr32[3] = addr->s6_addr32[3];
		llsol.s6_addr8[12] = 0xff;
		if ((error = in6_addmulti(ifp, &llsol)) != E_OK)
			return error;

		/* ���Ρ��ɡ���󥯥����롦�ޥ�����㥹�ȥ��ɥ쥹����Ͽ���롣*/
		llsol.s6_addr32[2] = 0x00000000;
		llsol.s6_addr32[3] = IPV6_ADDR_INT32_ONE;
		if ((error = in6_addmulti(ifp, &llsol)) != E_OK)
			return error;

		}

	/* �롼������ǥå��������ꤹ�롣*/
	ia->router_index = router_index;

	/* �ץ�ե��å�������ǥå��������ꤹ�롣*/
	ia->prefix_index = prefix_index;

	/* �ե饰�����ꤹ�롣*/
	ia->flags  = flags & ~(IN6_IFF_DUPLICATED | IN6_IFF_NODAD);
	ia->flags |= IN6_IFF_DEFINED;

 	/*
 	 *  ���ɥ쥹ͭ�����֤����ꤹ�롣
	 *  vltime (ͭ������) �� pltime (�侩ͭ������) ��ñ�̤� [s]��
 	 */
	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

 	ia->lifetime.vltime = vltime;
 	if (vltime != ND6_INFINITE_LIFETIME)
 		ia->lifetime.expire = now + vltime;
 	else
 		ia->lifetime.expire = 0;

 	ia->lifetime.pltime = pltime;
 	if (pltime != ND6_INFINITE_LIFETIME)
 		ia->lifetime.preferred = now + pltime;
 	else
 		ia->lifetime.preferred = 0;

	/* ����õ���ν�������Ԥ���*/
	nd6_ifattach(ifp);

	/* ��ʣ���ɥ쥹���Ф�Ԥ���*/
	if ((flags & IN6_IFF_NODAD) == 0) {
		ia->flags |= IN6_IFF_TENTATIVE;
		nd6_dad_start(ifp, ia, NULL);
		}

	return error;
	}

/*
 * in6ifa_ifpwithix -- ����ǥå����ֹ椫�顢�ͥåȥ�����󥿥ե�������
 *                     ������Ƥ��Ƥ��륢�ɥ쥹��õ�����롣
 */

T_IN6_IFADDR *
in6ifa_ifpwithix (T_IFNET *ifp, int_t ix)
{
	return ix < NUM_IN6_IFADDR_ENTRY? &ifp->in_ifaddrs[ix] : NULL;
	}

/*
 * in6ifa_ifpwithrtrix -- �롼���Υ���ǥå����ֹ椫�顢�ͥåȥ�����󥿥ե�������
 *                        ������Ƥ��Ƥ��륢�ɥ쥹��õ�����롣
 */

T_IN6_IFADDR *
in6ifa_ifpwithrtrix (T_IFNET *ifp, int_t router_index)
{
	int_t ix;

	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; )
		if (ifp->in_ifaddrs[ix].router_index == router_index)
			return &ifp->in_ifaddrs[ix];
	return NULL;
	}

/*
 * in6_ifawithifp -- ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
 *                   �ͥåȥ�����󥿥ե���������õ�����롣
 */

T_IN6_IFADDR *
in6_ifawithifp (T_IFNET *ifp, T_IN6_ADDR *dst)
{
	uint_t	scope;
	int_t	ix;

	/* ���襢�ɥ쥹��Ʊ���������פΥ��ɥ쥹���֤���*/
	if ((ix = in6_addr2ifaix(dst)) != IPV6_IFADDR_IX_INVALID)
		return &ifp->in_ifaddrs[ix];
	else if ((ix = in6_addr2maix(dst)) == IPV6_MADDR_IX_SOL_NODE ||
	          ix                       == IPV6_MADDR_IX_LL_ALL_NODE)
		return &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];
	else {
		scope = in6_addrscope(dst);
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			if ((ifp->in_ifaddrs[ix].flags & IN6_IFF_DEFINED) &&
			    (ifp->in_ifaddrs[ix].flags & IN6_IFF_DETACHED) == 0 &&
			    in6_addrscope(&ifp->in_ifaddrs[ix].addr) == scope) {
				return &ifp->in_ifaddrs[ix];
				}
			}
		return NULL;
		}
	}

/*
 * in6_if_up -- ���󥿥ե�������ư��ν�ʣ���ɥ쥹���Ф�Ԥ���
 */

void
in6_if_up (T_IFNET *ifp)
{
#if 0						/* ��α */
	int_t dad_delay, ix;
#endif	/* of #if 0 */

	in6_ifattach(ifp);

#if 0						/* ��α */
	/* ��ʣ���ɥ쥹���Ф�Ԥ���*/
	dad_delay = 0;
	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; )
		if ((ifp->in_ifaddrs[ix].flags & IN6_IFF_DEFINED) &&
		    (ifp->in_ifaddrs[ix].flags & IN6_IFF_TENTATIVE))
			nd6_dad_start(ifp, &ifp->in_ifaddrs[ix], &dad_delay);
#endif	/* of #if 0 */

#if NUM_ND6_RTR_SOL_RETRY > 0

	/* �롼����������Ϥ��롣*/
	nd6_rtrsol_ctl();

#endif	/* of #if NUM_ND6_RTR_SOL_RETRY > 0 */
	}

/*
 *  in6_are_prefix_equal -- �ץ�ե��å�����Ʊ�줫Ĵ�٤롣
 */

bool_t
in6_are_prefix_equal (T_IN6_ADDR *addr, T_IN6_ADDR *prefix, uint_t prefix_len)
{
	uint_t bitlen, bytelen;

	bytelen = prefix_len / 8;
	if (memcmp(&addr->s6_addr, &prefix->s6_addr, bytelen))
		return false;

	bitlen = prefix_len % 8;
	if (  addr->s6_addr[bytelen] >> (8 - bitlen) !=
	    prefix->s6_addr[bytelen] >> (8 - bitlen))
		return false;

	return true;
	}

/*
 *  in6_ifaddr_timer -- �ͥåȥ�����󥿥ե������Υ��ɥ쥹�δ��������ޡ�
 */

void
in6_ifaddr_timer (T_IFNET *ifp)
{
	T_IN6_IFADDR	*ia;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));
	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		ia = &ifp->in_ifaddrs[ix];

		if ((ia->flags & IN6_IFF_DEFINED) == 0)
			;
		else if (IFA6_IS_INVALID(ia, now)) {

			/*
			 *  ͭ�����֤�᤮���ΤǺ�����롣
			 */
			ia->flags &= ~IN6_IFF_DEFINED;
			}

		else if (IFA6_IS_DEPRECATED(ia, now)) {

			/*
			 *  �侩ͭ�����֤�᤮���Τ���侩�ˤ��롣
			 */
			ia->flags |= IN6_IFF_DEPRECATED;
			}
		}
	}

#endif /* of #ifdef SUPPORT_INET6 */
