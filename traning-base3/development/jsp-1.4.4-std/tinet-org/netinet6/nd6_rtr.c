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
 *  @(#) $Id: nd6_rtr.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6_rtr.c,v 1.11 2002/04/19 04:46:23 suz Exp $	*/
/*	$KAME: nd6_rtr.c,v 1.111 2001/04/27 01:37:15 jinmei Exp $	*/

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
#include <netinet6/in6_ifattach.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <netinet6/ip6_var.h>

#include <net/if6_var.h>

/*
 *  �����ؿ������
 */

extern const char *itron_strerror (ER ercd);

#ifdef SUPPORT_INET6

#if NUM_ND6_DEF_RTR_ENTRY > 0

/*
 *  �����ѿ�
 */

SYSTIM	nd6_base_reachable_time		= ND6_DEF_REACHABLE_TIME;	/* �롼���������Τ��줿��		*/
SYSTIM	nd6_reachable_time		= ND6_DEF_REACHABLE_TIME;	/* �롼���������Τ��줿�ͤ�������	*/
SYSTIM	nd6_recalc_reachtm_interval	= ND6_RECALC_REACHTM_INTERVAL;	/* ��ã��ǽ���֤�ͭ�����ֺƷ׻��ֳ�	*/
SYSTIM	nd6_retrans_time		= ND6_DEF_RETRANS_TIME;		/* ����õ���������ֳ�			*/
uint8_t	ip6_defhlim			= IPV6_DEFHLIM;			/* �ۥåץ�ߥåȤε�����		*/

/*
 *  �ɽ��ѿ�
 */

/*
 *  �ץ�ե��å������ꥹ��
 */

static T_ND6_PREFIX nd6_prefix[NUM_ND6_PREFIX_ENTRY];

/*
 *  �ǥ��ե���ȥ롼�����ꥹ��
 */

static T_DEF_ROUTER	nd6_def_router[NUM_ND6_DEF_RTR_ENTRY];
static uint_t		def_router_count = 0;				/* �ꥹ�Ȥˤ���롼���� */

/*
 *  make_mask -- �ޥå��ѤΥޥ������������롣
 */

static uint_t
make_mask (int_t index)
{
	uint_t	mask;
	int_t	ix;

	/* �ޥ������������롣*/
	mask = 1;
	for (ix = index; ix -- > 0; )
		mask <<= 1;

	return mask;
	}

/*
 *  find_pfxlist_reachable_router --
 *      ���ꤷ���ץ�ե��å��������Τ����롼������󥯾��¸�ߤ��뤫�����å����롣
 */

static T_DEF_ROUTER *
find_pfxlist_reachable_router (T_ND6_PREFIX *pr)
{
	T_DEF_ROUTER	*dr = NULL;
	T_LLINFO_ND6	*ln;
	uint_t		mask;
	int_t		ix;

	mask = 1;
	for (ix = 0; ix < def_router_count; ix ++) {
		if ((pr->routermap & mask) != 0) {
			if ((ln = nd6_lookup(&nd6_def_router[ix].addr, false)) != NULL &&
			    ND6_IS_LLINFO_PROBREACH(ln))
				return dr;
			}
		mask <<= 1;
		}
	return NULL;
	}

/*
 *  pfxlist_onlink_check -- �ץ�ե��å������ꥹ�ȤΥ����󥯾��֤�����å����롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

static void
pfxlist_onlink_check (void)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ND6_PREFIX	*pr = NULL;
	T_IN6_IFADDR	*ia;
	ER		error;
	int_t		ix;

	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) != 0 &&
		    find_pfxlist_reachable_router(pr))
			break;
		}

	if (ix >= 0) {
		/*
		 *  �����󥯾��֤Υץ�ե��å�����������¸�ߤ���Ȥ��ν�����
		 *  �ƥץ�ե��å����Υ����󥯾��֤򡢤��������Τ��Ƥ����롼����
		 *  ���֤˽��ä����ꤹ�롣
		 */

		
		for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
			pr = &nd6_prefix[ix];

			if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
				continue;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) == 0 &&
			    find_pfxlist_reachable_router(pr) == NULL)
				pr->flags |= ND6_PREFIX_STATE_DETACHED;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0 &&
			    find_pfxlist_reachable_router(pr) != NULL)
				pr->flags &= ~ND6_PREFIX_STATE_DETACHED;
			}
		}
	else {
		/*
		 *  �ɤΥץ�ե��å����⥪���󥯤ǤϤʤ���
		 *  �ǥ��ե���ȥ롼����¸�ߤ��ʤ��Ȥ��ν�����
		 *  ���٤ƤΥץ�ե��å�������Ѳ�ǽ���֤����ꤹ�롣
		 */

		
		for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
			pr = &nd6_prefix[ix];

			if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
				continue;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0)
				pr->flags &= ~ND6_PREFIX_STATE_DETACHED;
			}
		}

	/*
	 *  �ƥץ�ե��å�����ˡ����Τ��Ƥ����롼���ξ��֤�
	 *  �����󥯤ξ��֤����פ��ʤ���С������󥯾��֤򹹿����롣
	 */
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];

		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
			continue;

		if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK  ) != 0) {
			if ((error = nd6_prefix_offlink(pr)) != E_OK)
				syslog(LOG_ERROR, "[ND6 RTR] prefix offlink failed: %s", itron_strerror(error));
			}

		if ((pr->flags & ND6_PREFIX_STATE_DETACHED) == 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK  ) == 0 &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK   ) == 0) {
			if ((error = nd6_prefix_onlink(pr)) != E_OK)
				syslog(LOG_ERROR, "[ND6 RTR] prefix onlink failed: %s", itron_strerror(error));
			}
		}

	/*
	 *  ��󥯾�˥ץ�ե��å��������Τ��Ƥ���롼����
	 *  ���ʤ��Ȥ� 1 ��¸�ߤ��뤫��ǧ���롣
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		ia = &ifp->in_ifaddrs[ix];
		if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0 &&
		     ia->prefix_index != ND6_PREFIX_IX_INVALID) {
			pr = &nd6_prefix[ia->prefix_index];
			if (find_pfxlist_reachable_router(pr) != NULL)
				break;
			}
		}

	if (ix >= 0) {
		/*
		 *  ��󥯾�˥ץ�ե��å��������Τ��Ƥ���롼����
		 *  ���ʤ��Ȥ� 1 ��¸�ߤ�����ν�����
		 */
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0 &&
			     ia->prefix_index != ND6_PREFIX_IX_INVALID) {
				pr = &nd6_prefix[ia->prefix_index];
				if (find_pfxlist_reachable_router(pr) != NULL)
					ia->flags &= ~IN6_IFF_DETACHED;
				else
					ia->flags |= IN6_IFF_DETACHED;
				}
			}
		}
	else {
		/*
		 *  ��󥯾�˥ץ�ե��å��������Τ��Ƥ���롼����
		 *  1 ��¸�ߤ��ʤ��������ƤΥ��ɥ쥹�����ѤǤ���褦�ˤ��롣
		 */
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0)
				ia->flags &= ~IN6_IFF_DETACHED;
			}
		}
	}

/*
 *  pfxrtr_add -- �ץ�ե��å�������ȥ�ȥǥ��ե���ȥ롼��������ȥ���󥯤��롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

static void
pfxrtr_add (int_t prefix_index, int_t rtr_index)
{
	/*  �ץ�ե��å�������ȥ�ȥǥ��ե���ȥ롼��������ȥ���󥯤��롣*/
	nd6_prefix[prefix_index].routermap |= make_mask(rtr_index);
	nd6_def_router[rtr_index].plistmap |= make_mask(prefix_index);

	pfxlist_onlink_check();
	}

/*
 *  nd6_pfxrtr_lookup -- �ץ�ե��å�������ȥ꤫��롼����õ�����롣
 */

static uint_t
pfxrtr_lookup (const T_ND6_PREFIX *pr, int_t rtr_index)
{
	return (pr->routermap & make_mask(rtr_index)) == 0 ? IN6_RTR_IX_UNREACH : rtr_index;
	}

/*
 *  defrouter_select -- ͥ��ǥ��ե���ȡ��롼�������򤷤ʤ�����
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

static void
defrouter_select (void)
{
	T_DEF_ROUTER	*dr = NULL, router;
	T_LLINFO_ND6	*ln;
	int_t		ix, tix;

	for (ix = 0; ix < def_router_count; ix ++) {
		dr = &nd6_def_router[ix];
		if ((ln = nd6_lookup(&dr->addr, false)) != NULL && ND6_IS_LLINFO_PROBREACH(ln)) {
		
			/* ���򤷤��롼������Ƭ�˰ܤ���*/
			router = *dr;
			for (tix = ix; tix > 0; tix --)
				nd6_def_router[tix] = nd6_def_router[tix - 1];
			nd6_def_router[0] = router;
			break;
			}
		}
	}

/*
 *  defrtrlist_update -- �ǥ��ե���ȥ롼�����ꥹ�Ȥ򹹿����롣
 *
 *  	����ͤϡ��롼���Υ���ǥå�����
 *      ���������ͤ� -1 �ʤ顢�ץ�ե��å������ꥹ�ȤϹ������ʤ���
 */

static int_t
defrtrlist_update (T_IN6_ADDR *src, uint32_t lifetime, uint8_t flags)
{
	T_DEF_ROUTER	*dr, *fdr = NULL;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));
	syscall(wai_sem(SEM_ND6_DEFRTRLIST));

	/* ��Ͽ�Ѥ�Ĵ�٤롣*/
	if ((fdr = nd6_defrtrlist_lookup(src)) != NULL) {
		/* ��Ͽ�Ѥߤξ��ν��� */
		if (lifetime == 0) {
			nd6_defrtrlist_del(fdr);
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return -1;
			}
		else {
			fdr->lifetime = lifetime * SYSTIM_HZ;		/* lifetime ��ñ�̤��� */
			fdr->flags    = flags;
			fdr->expire   = now + fdr->lifetime;
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return fdr - nd6_def_router;
			}
		}
	else if (lifetime == 0) {
		syscall(sig_sem(SEM_ND6_DEFRTRLIST));
		return -1;
		}

	if (fdr == NULL && def_router_count < NUM_ND6_DEF_RTR_ENTRY) {
		/*
		 *  def_router_count < NUM_ND6_DEF_RTR_ENTRY �Ǥ���С�
		 *  nd6_def_router[def_router_count]; ����������ȥ�
		 */
		fdr = &nd6_def_router[def_router_count];
		}

	/* ��������ȥ꤬�ʤ���С�ͭ�����֤�û������ȥ�������롣*/
	if (fdr == NULL) {
		T_DEF_ROUTER	*sdr = NULL;
		int32_t		diff, sdiff = 0xffffffff;

		for (ix = def_router_count; ix -- > 0; ) {
			dr = &nd6_def_router[ix];
			diff = (int32_t)(dr->expire - now);
			if (diff <= 0) {	/* dr->expire <= now */
				/* ���ˡ�ͭ�����֤��᤮�Ƥ��롣*/
				sdr = dr;
				break;
				}
			else if (diff < sdiff)
				sdr = dr;
			}
		if (sdr != NULL) {
			fdr = sdr;
			nd6_defrtrlist_del(fdr);
			}
		}

	/* �ƥ��Ф��ͤ����ꤹ�롣*/
	fdr->plistmap = 0;
	fdr->addr     = *src;
	fdr->lifetime = lifetime * SYSTIM_HZ;		/* lifetime ��ñ�̤��� */
	fdr->flags    = flags;
	fdr->expire   = now + fdr->lifetime;
	fdr->state    = ND6_DEF_RTR_BUSY;
	def_router_count ++;

	/*
	 *  �ǥ��ե���ȥ롼���Ȥ�����Ͽ���뤬��
	 *  ���˥ǥ��ե���ȥ롼������������򤷤ʤ����ʤ���
	 */
	if (fdr - nd6_def_router != 0)
		defrouter_select();

	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	return fdr - nd6_def_router;
	}

/*
 *  in6_ifadd -- ���󥿥ե������˥��ɥ쥹���ɲä��롣
 */

static ER
in6_ifadd (T_ND6_PREFIX *pr, T_IN6_IFADDR *ia, int_t router_index)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_ADDR	mask, addr;
	T_IN6_IFADDR	*lla;
	int_t		ix;

	lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];

	/*
	 *  ��󥯥����륢�ɥ쥹��̤��Ͽ�Ǥ���в��⤷�ʤ���
	 */
	if ((lla->flags & IN6_IFF_DEFINED) == 0)
		return E_OBJ;

	/*
	 *  �롼���������Τ��줿�ץ�ե��å���Ĺ����
	 *  ��󥯥����륢�ɥ쥹�Υץ�ե��å���Ĺ��
	 *  �ۤʤäƤ���Х��顼
	 */
	if (lla->prefix_len != pr->prefix_len)
		return E_PAR;

	/* �ץ�ե��å����ޥ������������롣*/
	in6_plen2pmask(&mask, pr->prefix_len);

	/* ���ɥ쥹���������롣*/
	for (ix = 0; ix < 4; ix ++)
		addr.s6_addr32[ix] = (pr->prefix.s6_addr32[ix] &  mask.s6_addr32[ix])
		                   | ( lla->addr.s6_addr32[ix] & ~mask.s6_addr32[ix]);

	/* �ե饰���������롣*/
	ia->flags = 0;

	return in6_update_ifa(ifp, ia, &addr,
	                      pr->prefix_len, pr->vltime, pr->pltime,
	                      router_index, pr - nd6_prefix, IN6_IFF_AUTOCONF);
	}

/*
 *  nd6_prefix_lookup -- �ץ�ե��å�����õ�����롣
 */

static T_ND6_PREFIX *
nd6_prefix_lookup (const T_IN6_ADDR *prefix, uint_t plen)
{
	T_ND6_PREFIX	*pr;
	int_t		ix;

	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) &&
		     pr->prefix_len == plen && IN6_ARE_ADDR_EQUAL(&pr->prefix, prefix))
			return pr;
		}

	return NULL;
	}

/*
 *  prelist_remove -- �ץ�ե��å����ꥹ�Ȥ���ץ�ե��å����������롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

static void
prelist_remove (T_ND6_PREFIX *pr)
{
	ER	error = E_OK;
	uint_t	mask;
	int_t	rix;

	/* ͭ�������ڤ�ˤ��롣*/
	pr->vltime = 0;
	pr->pltime = 0;

	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) != 0 &&
	    (error = nd6_prefix_offlink(pr)) != E_OK) {
		syslog(LOG_ERROR, "[ND6 RTR] prefix remove failed: %s", itron_strerror(error));
		return;
		}

	/*  �ץ�ե��å�������ȥ�ȥǥ��ե���ȥ롼��������ȥ�Υ�󥯤������롣*/
	pr->routermap = 0;
	mask = make_mask(pr - nd6_prefix);
	for (rix = def_router_count; rix --; )
		nd6_def_router[rix].plistmap &= ~mask;

	/* �ץ�ե��å�����̵���ˤ��롣*/
	pr->flags &= ~ND6_PREFIX_STATE_BUSY;

	pfxlist_onlink_check();
	}

/*
 *  nd6_prefix_onlink -- �ץ�ե��å����򥪥��󥯤����ꤷ�����ɥ쥹����Ѳ�ǽ�ˤ��롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

ER
nd6_prefix_onlink (T_ND6_PREFIX *pr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*lla, *ia = NULL;
	int_t		ix;

	/* ���˥����󥯾��֤ˤʤäƤ�����ϥ��顼��*/
	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) != 0)
		return E_OBJ;

	/* ��󥯥����륢�ɥ쥹��̤��Ͽ�Ǥ���в��⤷�ʤ���*/
	lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];
	if ((lla->flags & IN6_IFF_DEFINED) == 0)
		return E_OK;

	/*
	 *  ���ꤵ�줿�ץ�ե��å�����������Ƥ��Ƥ��륤�󥿥ե�������
	 *  ���ɥ쥹�����õ����
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if (ia->prefix_index == (pr - nd6_prefix))
			break;
		}

	if (ix >= 0) {

		/* ���ɥ쥹�������Ѳ�ǽ�ˤ��롣*/
		ia->flags &= ~IN6_IFF_DETACHED;

		/* �ץ�ե��å����򥪥��󥯤����ꤹ�롣*/
		pr->flags |= ND6_PREFIX_STATE_ONLINK;
		}

	return E_OK;
	}

/*
 *  nd6_prefix_offlink -- �ץ�ե��å����򥪥ե�󥯤����ꤷ�����ɥ쥹������ԲĤˤ��롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

ER
nd6_prefix_offlink (T_ND6_PREFIX *pr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia = NULL;
	int_t		ix;

	/* ���˥��ե�󥯾��֤ˤʤäƤ�����ϥ��顼��*/
	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) == 0)
		return E_OBJ;

	/*
	 *  ���ꤵ�줿�ץ�ե��å�����������Ƥ��Ƥ��륤�󥿥ե�������
	 *  ���ɥ쥹�����õ����
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if (ia->prefix_index == (pr - nd6_prefix))
			break;
		}

	if (ix >= 0) {

		/* ���ɥ쥹���������ԲĤˤ��롣*/
		ia->flags |= IN6_IFF_DETACHED;

		/* �ץ�ե��å����򥪥ե�󥯤����ꤹ�롣*/
		pr->flags &= ~ND6_PREFIX_STATE_ONLINK;
		}

	return E_OK;
	}

/*
 *  in6_init_prefix_ltimes -- �ץ�ե��å�����ͭ�����֤����ꤹ�롣
 */

static ER
in6_init_prefix_ltimes (T_ND6_PREFIX *pr)
{
	SYSTIM		now;

	/* �侩ͭ�����֤�ͭ�����֤��Ĺ���Ȥ��ϥ��顼 */
	if (pr->pltime > pr->vltime)
		return E_PAR;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	if (pr->pltime == ND6_INFINITE_LIFETIME)
		pr->preferred = 0;
	else
		pr->preferred = pr->pltime + now;

	if (pr->vltime == ND6_INFINITE_LIFETIME)
		pr->expire = 0;
	else
		pr->expire = pr->vltime + now;

	return E_OK;
	}

/*
 *  nd6_prelist_add -- �ץ�ե��å����ꥹ�Ȥ˥ץ�ե��å������ɲä��롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

static T_ND6_PREFIX *
nd6_prelist_add (T_ND_OPT_PREFIX_INFO *pi, int_t rtr_index)
{
	T_ND6_PREFIX	*pr = NULL;
	int_t		ix;
	ER		error;

	/* �ץ�ե��å����ꥹ�Ȥ�������Υץ�ե��å�������ȥ��õ�����롣*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix --; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) == 0)
			break;
		}

	/* �ץ�ե��å����ꥹ�Ȥ˶������ʤ���Х��顼 */
	if (ix < 0)
		return NULL;

	pr->flags |= ND6_PREFIX_STATE_BUSY;

	/* �ץ�ե��å������ɲä��롣*/
	pr->prefix     = pi->prefix;
	pr->prefix_len = pi->prefix_len;

	/* �ե饰�����ꤹ�롣*/
	if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0)
		pr->flags |= ND6_PREFIX_FLAG_ONLINK;
	if ((pi->flags & ND_OPT_PI_FLAG_AUTO) != 0)
		pr->flags |= ND6_PREFIX_FLAG_AUTO;

	/* �ץ�ե��å�����ͭ�����֤����ꤹ�롣*/
	pr->vltime = ntohl(pi->valid);
	pr->pltime = ntohl(pi->preferred);
	in6_init_prefix_ltimes(pr);

	if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) != 0) {
		if ((error = nd6_prefix_onlink(pr)) != E_OK)
			return NULL;
		}

	/* �롼���ޥåפ��������롣*/
	pr->routermap = 0;

	/* �롼�����ɲä��롣*/
	pfxrtr_add(pr - nd6_prefix, rtr_index);

	return pr;
	}

/*
 *  prelist_update -- �ץ�ե��å������ꥹ�Ȥ򹹿����롣
 */

static void
prelist_update (T_ND_OPT_PREFIX_INFO *pi, uint_t router_index)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ND6_PREFIX	*pr;
	T_IN6_IFADDR	*ia = NULL;
	int_t		ix, ifidlen;

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	if ((pr = nd6_prefix_lookup(&pi->prefix, pi->prefix_len)) != NULL) {
		/*
		 *  ��Ͽ�Ѥߤξ��ϡ��ץ�ե��å����ꥹ�Ȥ򹹿����롣
		 */

		/*
		 *  �ե饰�ι��������:
		 *    on-link �ӥåȤ� autonomous �ӥåȤ�
		 *    1 ���� 0 ���ѹ����ƤϤʤ�ʤ���
		 */

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0)
			pr->flags |= ND6_PREFIX_FLAG_ONLINK;
		if ((pi->flags & ND_OPT_PI_FLAG_AUTO) != 0)
			pr->flags |= ND6_PREFIX_FLAG_AUTO;

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0) {
			/*
			 *  ���Τ��줿�ץ�ե��å����������󥯤λ��ϡ�
			 *  ͭ�����֤򹹿����롣
			 */
			pr->vltime = ntohl(pi->valid);
			pr->pltime = ntohl(pi->preferred);
			in6_init_prefix_ltimes(pr);
			}

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK  ) != 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK) == 0) {
			/*
			 *  ���ե�󥯤Υץ�ե��å����������󥯤ˤʤä����ν�����¹Ԥ��롣
			 */
			if (nd6_prefix_onlink(pr) != E_OK) {
				syscall(sig_sem(SEM_ND6_DEFRTRLIST));
				syslog(LOG_ERROR, "[ND6 RTR] prefix update failed.");
				return;
				}
			}

		if (router_index != IN6_RTR_IX_UNREACH && pfxrtr_lookup(pr, router_index) == IN6_RTR_IX_UNREACH)
			pfxrtr_add(pr - nd6_prefix, router_index);
		}
	else {	/* ̤��Ͽ�ξ�� */

		/* ͭ������ 0 �Υץ�ե��å������ɲä��ʤ���*/
		if (pi->valid == 0) {
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		/* ���ե�󥯤ǥ��ɥ쥹��ư����˻��Ѥ��ʤ�����ɲä��ʤ���*/
		if ((pi->flags & (ND_OPT_PI_FLAG_ONLINK | ND_OPT_PI_FLAG_AUTO)) !=
		                 (ND_OPT_PI_FLAG_ONLINK | ND_OPT_PI_FLAG_AUTO)) {
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		/* �ץ�ե��å������ɲä��롣*/
		if ((pr = nd6_prelist_add(pi, router_index)) == NULL) {
			syslog(LOG_ERROR, "[ND6 RTR] prefix add failed.");
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0) {
			/*
			 *  ���ե�󥯡��ץ�ե��å����ξ��ϡ�ͭ�����֤� 0 �����ꤹ�롣
			 *  ���Ȥ�ͭ�������ڤ�Ȥʤꡢ�ꥹ�Ȥ���������롣
			 */
			pr->vltime = 0;
			pr->pltime = 0;
			in6_init_prefix_ltimes(pr);
			}
		}

	/*
	 *  ���ơ��ȥ쥹�����ɥ쥹��ư�����Ԥ���
	 */
	if ((pr->flags & ND6_PREFIX_FLAG_AUTO) == 0) {
		syscall(sig_sem(SEM_ND6_DEFRTRLIST));
		return;
		}

	/*
	 *  ���Τ��줿�ץ�ե��å�����������Ƥ��Ƥ��륤�󥿥ե�������
	 *  ���ɥ쥹�����õ����
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if ((ia->flags & IN6_IFF_DEFINED) != 0 &&
		    ia->prefix_len == pr->prefix_len &&
		    in6_are_prefix_equal(&ia->addr, &pr->prefix, pr->prefix_len))
			break;
		}

	if (ix >= 0) {	/* ��Ͽ�ѤߤΤȤ� */
		if ((ia->flags & IN6_IFF_AUTOCONF) == 0) {
			/*
			 *  ���ơ��ȥ쥹�����ɥ쥹��ư����ˤ��
			 *  ���ꤵ��Ƥ��ʤ���й������ʤ���
			 */
			;
			}
		else if (ia->flags & IN6_IFF_TENTATIVE) {
			/*
			 *  ��ʣ������ʤ鹹�����ʤ���
			 */
			;
			}
		else {
			T_IN6_ADDR	mask, addr;
			T_IN6_IFADDR	*lla;
			uint32_t		vltime;
			SYSTIM		now;
			int_t		ix;

			/* ͭ�����֤����ꤹ�롣*/
			syscall(get_tim(&now));

			if (ia->lifetime.vltime == ND6_INFINITE_LIFETIME)
				vltime = ND6_INFINITE_LIFETIME;
			else if (IFA6_IS_INVALID(ia, now))
				vltime = 0;
			else
				vltime = ia->lifetime.expire - now / SYSTIM_HZ;

			if (pr->vltime > (2 * 60 * 60) || pr->vltime > vltime) {
				/*
				 *  lifetime.expire��pi->valid (ͭ������) ��
				 *  pi->preferred (�侩ͭ������) ��ñ�̤� [s]��
				 *  ���Τ��줿ͭ�����֤� 2 ���ְʾ夫�����ߤλĤ���֤��
				 *  Ĺ����С�������ͭ�����֤ˤϡ����Τ��줿ͭ�����֤����ꤹ�롣
				 */
				vltime = pr->vltime;
				}
			else if (vltime <= (2 * 60 * 60))
				;
			else {
				/*
				 *  IPsec ��̤�����Τ��ᡢ2 ���֤����ꤹ�롣
				 */
				vltime = 2 * 60 * 60;
				}

			lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];

			/* �ץ�ե��å����ޥ������������롣*/
			in6_plen2pmask(&mask, pr->prefix_len);

			/* ���ɥ쥹���������롣*/
			for (ix = 0; ix < 4; ix ++)
				addr.s6_addr32[ix] = (pr->prefix.s6_addr32[ix] &  mask.s6_addr32[ix])
				                   | ( lla->addr.s6_addr32[ix] & ~mask.s6_addr32[ix]);

			in6_update_ifa(ifp, ia, &addr, pr->prefix_len, vltime,
			               pr->pltime, router_index, pr - nd6_prefix,
			               IN6_IFF_AUTOCONF | IN6_IFF_NODAD);
			}
		}

	else { /* ̤��Ͽ�ΤȤ� */

		/*
		 *  �ץ�ե��å���Ĺ������å����롣
		 *  �⤷���ץ�ե��å���Ĺ�ȥ��󥿥ե����� ID �ι�פ�
		 *  128 �ӥåȤ˰��פ��ʤ����ϡ��ץ�ե��å��������̵�뤹�롣
		 */
		if ((ifidlen = in6_if2idlen(ifp)) < 0)
			syslog(LOG_ERROR, "[ND6 RTR] IFID undefined.");
		else if (ifidlen + pr->prefix_len != 128)
			syslog(LOG_NOTICE, "[ND6 RTR] invalid prefix len: %d.", pr->prefix_len);
		else {

			for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
				ia = &ifp->in_ifaddrs[ix];
				if ((ia->flags & IN6_IFF_DEFINED) == 0) {
					in6_ifadd(pr, ia, router_index);
					pfxlist_onlink_check();
					break;
					}
				}

			if (ix < 0)
				syslog(LOG_ERROR, "[ND6 RTR] prefix update failed.");
			}
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_prelist_timer -- �ץ�ե��å������ꥹ�Ȥδ��������ޡ�
 */

void
nd6_prelist_timer (void)
{
	T_ND6_PREFIX	*pr;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;		/* ͭ�����֤�ñ�̤� [s] */

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) != 0 && (int32_t)(pr->expire - now) <= 0)
		                                                       /* pr->expire <= now */
			prelist_remove(pr);
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_rs_output -- �롼����������Ϥ��롣
 */

static void
nd6_rs_output (void)
{
	T_ROUTER_SOLICIT_HDR	*rsh;
	T_NET_BUF		*output;
	T_IN6_IFADDR		*ifa;
	T_IN6_ADDR		*saddr;
	uint16_t		len;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RS_OUT_PACKETS], 1);

	/*
	 *  ���������ɥ쥹�ˤϡ���󥯥����륢�ɥ쥹�����ꤹ�뤬��
	 *  �ޤ����ꤵ�줤�ʤ���С�̵��������ꤹ�롣
	 */
	if ((ifa = in6ifa_ifpwithix(IF_GET_IFNET(), IPV6_IFADDR_IX_LINKLOCAL)) != NULL && !IFA6_IS_NOTREADY(ifa))
		saddr = &ifa->addr;
	else
		saddr = &in6_addr_unspecified;

	len = (ROUTER_SOLICIT_HDR_SIZE + 7) >> 3 << 3;

	/* �ͥåȥ���Хåե����������IPv6 �إå������ꤹ�롣*/
	if (in6_get_datagram(&output, len, 0, &in6_addr_linklocal_allrouters,
	                     saddr, IPPROTO_ICMPV6,
	                     IPV6_MAXHLIM, NBA_SEARCH_ASCENT, TMO_ND6_RS_OUTPUT) != E_OK)
		return;

 	/* �롼�������إå������ꤹ�롣*/
 	rsh = GET_ROUTER_SOLICIT_HDR(output, IF_IP6_ROUTER_SOLICIT_HDR_OFFSET);
 	rsh->hdr.type       = ND_ROUTER_SOLICIT;
 	rsh->hdr.code       = 0;
 	rsh->nd_rs_reserved = 0;

	/* �����å������׻����롣*/
	rsh->hdr.sum = 0;
	rsh->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)rsh - output->buf, len);

	/* �������롣*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutRouterSolicits, 1);
	ip6_output(output, IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM), TMO_ND6_RS_OUTPUT);
	}

/*
 *  nd6_defrtrlist_lookup -- �ǥ��ե���ȥ롼�����ꥹ�Ȥ�õ�����롣
 */

T_DEF_ROUTER *
nd6_defrtrlist_lookup (T_IN6_ADDR *src)
{
	T_DEF_ROUTER	*dr = NULL;
	int_t		ix;

	for (ix = def_router_count; ix -- > 0; ) {
		dr = &nd6_def_router[ix];
		if (IN6_ARE_ADDR_EQUAL(&dr->addr, src)) {
			return dr;
			}
		}
	return NULL;
	}

/*
 *  nd6_router_lookup -- �롼���Υ��ɥ쥹���֤���
 *
 */

T_IN6_ADDR *
nd6_router_lookup (void)
{
	if (def_router_count > 0)
		return &nd6_def_router[0].addr;
	else
		return NULL;
	}

/*
 *  nd6_defrtrlist_del -- �ǥ��ե���ȥ롼�����ꥹ�Ȥ���롼���������롣
 *
 *    ���: ���δؿ���ƤӽФ��Ȥ��ϡ�SEM_ND6_DEFRTRLIST �ǡ�
 *          ��å����Ƥ���ƤӽФ����ȡ�
 */

void
nd6_defrtrlist_del (T_DEF_ROUTER *dr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia;
	T_ND6_PREFIX	*pr;
	uint_t		mask;
	int_t		ix, rix, pix, rtrix = dr - nd6_def_router;

	if ((ia = in6ifa_ifpwithrtrix(ifp, rtrix)) != NULL) {
		/*
		 *  �ͥåȥ�����󥿥ե������Υץ�ե��å��������Τ���
		 *  �롼������ã��ǽ�ˤ��롣
		 */
		ia->router_index = IN6_RTR_IX_UNREACH;
		}

	/* �ץ�ե��å����ꥹ�Ȥ���롼���������롣*/
	mask = make_mask(rtrix);
	for (pix = NUM_ND6_PREFIX_ENTRY; pix --; )
		nd6_prefix[pix].routermap &= ~mask;

	/* ��������롼���ʹߤ����˵ͤ�롣*/
	for (rix = rtrix + 1; rix < def_router_count; rix ++)
		nd6_def_router[rix - 1] = nd6_def_router[rix];

	/* �ץ�ե��å����ꥹ�ȤΥ롼���⹹�����롣*/
	if (dr != nd6_def_router) {

		/* �ޥ������������롣*/
		mask = 1;
		for (ix = rtrix - 1; ix -- > 0; )
			mask = (mask << 1) | 1;

		for (pix = NUM_ND6_PREFIX_ENTRY; pix --; ) {
			pr = &nd6_prefix[pix];
			pr->routermap = (pr->routermap & mask) | (((pr->routermap & ~mask) >> 1) & ~mask);
			}
		}
	def_router_count --;

	/* �ץ�ե��å����Υ����󥯾��֤��ǧ���롣*/
	pfxlist_onlink_check();

	/*
	 *  �������롼����ͥ��ǥ��ե���ȥ롼���ξ��ϡ�
	 *  ͥ��ǥ��ե���ȥ롼�������򤷤ʤ�����
	 */
	if (rtrix == 0)
		defrouter_select();
	}

/*
 *  nd6_defrtrlist_timer -- �ǥ��ե���ȥ롼�����ꥹ�Ȥδ��������ޡ�
 */

void
nd6_defrtrlist_timer (void)
{
	T_DEF_ROUTER	*dr;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	for (ix = def_router_count; ix -- > 0; ) {
		dr = &nd6_def_router[ix];
		if ((int32_t)(dr->expire - now) <= 0) {
		           /* dr->expire <= now */
			nd6_defrtrlist_del(dr);
			}
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_get_drl -- �ǥ��ե���ȥ롼�����ꥹ�Ȥ�������롣
 */

const T_DEF_ROUTER *
nd6_get_drl (uint_t *count)
{
	*count = def_router_count;
	return nd6_def_router;
	}

/*
 *  nd6_get_prl -- �ץ�ե��å������ꥹ�Ȥ�������롣
 */

const T_ND6_PREFIX *
nd6_get_prl (void)
{
	return nd6_prefix;
	}

#endif	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/*
 *  nd6_ra_input -- �롼�����Τ����Ͻ�����
 */

void
nd6_ra_input (T_NET_BUF *input, uint_t off)
{
#if NUM_ND6_DEF_RTR_ENTRY > 0

	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_ROUTER_ADVERT_HDR	*rah;
	T_ND_OPT_HDR		*opth;
	SYSTIM			now;
	int_t			rix;
	uint_t			lladdr_len = 0;
	uint32_t		advrea;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RA_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �إå��Υ����å����ʲ��ξ����˴����롣
	 *    ���ۥåץ�ߥåȤ� IPV6_MAXHLIM (255) �ʳ�
	 *    ���إå�Ĺ��û��
	 *    ���������ɥ쥹������󥯥�����ǤϤʤ� (RFC2461)
	 */
	if (ip6h->hlim != IPV6_MAXHLIM                ||
	    input->len - off < ROUTER_ADVERT_HDR_SIZE ||
	    !IN6_IS_ADDR_LINKLOCAL(&ip6h->src))
		goto err_ret;

	rah  = GET_ROUTER_ADVERT_HDR(input, off);

	/* ����õ�����ץ����Υ��ե��åȤ�Ͽ���롣*/
	if (nd6_options(nd_opt_off, input->buf + (off + ROUTER_ADVERT_HDR_SIZE),
	                            input->len - (off + ROUTER_ADVERT_HDR_SIZE)) != E_OK)
		goto err_ret;
	/*
	 *  ��ã��ǽ���֤�ͭ�����֤ι���

	 */
	if (rah->reachable) {
		advrea = ntohl(rah->reachable) * SYSTIM_HZ / 1000;	/* rah->reachable ��ñ�̤� ms */
		if (advrea <= ND6_MAX_REACHABLE_TIME &&
		    advrea != nd6_base_reachable_time) {
			syscall(get_tim(&now));
			nd6_recalc_reachtm_interval
				= now + ND6_RECALC_REACHTM_INTERVAL;
			nd6_base_reachable_time	= advrea;
			nd6_reachable_time
				= ND6_CALC_REACH_TIME(nd6_base_reachable_time);
			}
		}

	/* ����õ���������ֳ֤ι��� */
	if (rah->retransmit) {
		nd6_retrans_time = ntohl(rah->retransmit) * SYSTIM_HZ / 1000;
									/* rah->retransmit ��ñ�̤� ms */
		}

	/* �ۥåץ�ߥåȤε����ͤι��� */
	if (rah->nd_ra_current_hoplimit) {
		ip6_defhlim = rah->nd_ra_current_hoplimit;
		}

	/* �ǥ��ե���ȥ롼���ꥹ�Ȥι��� */
	rix = defrtrlist_update(&ip6h->src,
	                       ntohs(rah->nd_ra_router_lifetime),
	                       rah->nd_ra_flags);		/* rah->nd_ra_router_lifetime ��ñ�̤��� */

	/* �ץ�ե��å����ꥹ�Ȥι��� */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)]) {
		T_ND_OPT_PREFIX_INFO	*pi;
		uint_t			pi_off, pi_count;

		pi_count = nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)];
		pi_off   = off + ROUTER_ADVERT_HDR_SIZE
		               + nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFORMATION)] - 8;
	 	/* ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣*/
		while (pi_count -- > 0) {
			pi = (T_ND_OPT_PREFIX_INFO*)(input->buf + pi_off);
			if (pi->type != ND_OPT_PREFIX_INFORMATION)
				/* ���ץ���󥿥��פ��ץ�ե��å�������Ǥʤ���в��⤷�ʤ���*/
				;
			else if (pi->len != 4)
			    	/* �ץ�ե��å��������Ĺ���� 32 (8��4) �Ǥʤ�������� */
				syslog(LOG_NOTICE, "[ND6 RTR] prefix opt len: %d.", pi->len);
			else if (pi->prefix_len > 128)
				/* �ץ�ե��å���Ĺ�� 128 �ӥåȰʲ� */
				syslog(LOG_NOTICE, "[ND6 RTR] prefix len: %d.", pi->prefix_len);
			else if (IN6_IS_ADDR_MULTICAST(&pi->prefix) ||
			         IN6_IS_ADDR_LINKLOCAL(&pi->prefix))
				/* �ޥ�����㥹�Ȥȥ�󥯥���������� */
				syslog(LOG_NOTICE, "[ND6 RTR] invalid addr: %s from %s.",
				                   ipv62str(NULL, &pi->prefix), ipv62str(NULL, &ip6h->src));
#if 0	/* FreeBSD 6.3 �Ǻ������Ƥ��롣*/
			else if (IN6_IS_ADDR_AGGREGATE_UNICAST(&pi->prefix) &&		
			         (pi->prefix_len != 64)                       )
				/* �����ǽ��˥��㥹�Ȥǡ��ץ�ե��å���Ĺ�� 64 �ӥåȰʳ������� */
				syslog(LOG_NOTICE, "[ND6 RTR] invalid prefix len for global: %d.", pi->prefix_len);
#endif
			else if (ntohl(pi->preferred) > ntohl(pi->valid))
				/* �侩ͭ�����֤�ͭ�����֤��Ĺ��������� */
				syslog(LOG_NOTICE, "[ND6 RTR] preferred(%d) > valid time(%d).", ntohl(pi->preferred), ntohl(pi->valid));
			else {
				syslog(LOG_NOTICE, "[ND6 RTR] update prefix: %s from %s.",
				                   ipv62str(NULL, &pi->prefix), ipv62str(NULL, &ip6h->src));
				if (rix >= 0) {
					/*
					 *  defrtrlist_update ������ͤϡ��롼���Υ���ǥå�����
					 *  ���������ͤ� -1 �ʤ顢�ץ�ե��å������ꥹ�ȤϹ������ʤ���
					 */
					prelist_update(pi, rix);	/* �ץ�ե��å������ꥹ�Ȥ򹹿����롣*/
					}
				}
			pi_off += pi->len << 3;		/* ���ץ����Ĺ��ñ�̤� 8 �Х��� */
			}
		}

	/* MTU �ι��� */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_MTU)]) {
		T_ND_OPT_MTU_HDR	*optmtuh;
		uint32_t			mtu;

		optmtuh = (T_ND_OPT_MTU_HDR *)((uint8_t *)(input->buf + off + ROUTER_ADVERT_HDR_SIZE) +
		                               nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_MTU)] - 8);

		/*
		 *  �ͤΥ����å�
		 *
		 *    ���ץ����Ĺ: 1
		 *    ͽ��:         0
		 */
		if (optmtuh->len != 1 || optmtuh->reserved != 0)
			goto err_ret;

		/* MTU �� IPv6 MMTU��1280 �����ƥåȡ˰ʲ��ʤ�̵�뤹�롣*/
		mtu = ntohl(optmtuh->mtu);
		if (mtu >= IPV6_MMTU) {
			if (mtu <= (linkmtu > IF_MTU ? linkmtu : IF_MTU))
				linkmtu = mtu;
			}
		}

	/*
	 *  �롼���λ�����󥯥��ɥ쥹����٥���å������Ͽ���롣
	 */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + ROUTER_ADVERT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)] - 8);
	 	/* ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	/*
	 *  �ͥåȥ�����󥿥ե������Υ��ɥ쥹Ĺ�����פ��ʤ���Х��顼
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* ���٥���å������Ͽ���롣*/
	nd6_cache_lladdr(ifp, &ip6h->src, (T_IF_ADDR *)lladdr, ND_ROUTER_ADVERT, 0);

	/*
	 *  �롼���λ�����󥯥��ɥ쥹����٥���å������Ͽ�����Τǡ�
	 *  �����󥯾��֤��Ѳ������ǽ�������뤿�ᡢ���������å����롣
	 */
	pfxlist_onlink_check();

	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));

#else	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */

	/*
	 *  �롼�����Τ�������ʤ����ϡ��˴����ƽ�λ���롣
	 */
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RA_IN_PACKETS], 1);
	syscall(rel_net_buf(input));

#endif	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */
	}

#if NUM_ND6_RTR_SOL_RETRY > 0

/*
 *  nd6_rtrsol_ctl -- �롼���������Ϥ�����
 */

void
nd6_rtrsol_ctl (void)
{
	T_IN6_IFADDR	*ifa;
	int_t		try;

	/* ��󥯥����륢�ɥ쥹�Υ��ɥ쥹��������롣*/
	if ((ifa = in6ifa_ifpwithix(IF_GET_IFNET(), IPV6_IFADDR_IX_LINKLOCAL)) == NULL)
		return;

	/* ��󥯥����륢�ɥ쥹�ν�ʣ���н�λ���Ԥġ�*/
	do {
		/* ��󥯥����륢�ɥ쥹�ν�ʣ���н�λ�Ԥ����֤����ꤹ�롣*/
		syscall(dly_tsk(net_rand() % TMO_ND6_RTR_SOL_DELAY));

		/* �ԤäƤ���֤˽�ʣ�����Ф��줿�齪λ���롣*/
		if (ifa->flags & IN6_IFF_DUPLICATED)
			return;

		} while (!((ifa->flags & IN6_IFF_DEFINED) && (ifa->flags & IN6_IFF_TENTATIVE) == 0));

	for (try = 0; try < NUM_ND6_RTR_SOL_RETRY; try ++) {

		/* �ǥ��ե���ȥ롼�����ꥹ�Ȥ˥���ȥ꤬����н�λ */
		if (def_router_count > 0)
			return;

		/* �롼����������Ϥ��롣*/
		nd6_rs_output();

		/* ���Ϥ� 2 ���ܰʹߤ��ٱ���֤����ꤹ�롣*/
		syscall(dly_tsk(TMO_ND6_RTR_SOL_INTERVAL));
		}
	}

#endif	/* of #if NUM_ND6_RTR_SOL_RETRY > 0 */

/*
 *  nd6_onlink_prefix_lookup -- �ץ�ե��å�����õ�����롣
 */

T_ND6_PREFIX *
nd6_onlink_prefix_lookup (T_IN6_ADDR *dst)
{
	SYSTIM		now;
	T_ND6_PREFIX	*pr;
	int_t		ix;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	/* �侩ͭ��������Υץ�ե��å�����õ�����롣*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY)  &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK) &&
		    in6_are_prefix_equal(dst, &pr->prefix, pr->prefix_len) &&
		    (int32_t)(pr->preferred - now) > 0) {
		           /* pr->preferred > now */
			return pr;
			}
		}

	/* ͭ��������Υץ�ե��å�����õ�����롣*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY)  &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK) &&
		    in6_are_prefix_equal(dst, &pr->prefix, pr->prefix_len) &&
		    (int32_t)(pr->expire - now) > 0) {
		           /* pr->expire > now */
			return pr;
			}
		}

	return NULL;
	}

#endif /* of #ifdef SUPPORT_INET6 */
