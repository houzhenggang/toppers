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
 *  @(#) $Id: nd6.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6.c,v 1.20 2002/08/02 20:49:14 rwatson Exp $	*/
/*	$KAME: nd6.c,v 1.144 2001/05/24 07:44:00 itojun Exp $	*/

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
 * XXX
 * KAME 970409 note:
 * BSD/OS version heavily modifies this code, related to llinfo.
 * Since we don't have BSD/OS version of net/route.c in our hand,
 * I left the code mostly as it was in 970310.  -- itojun
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
 *  ���٥���å���
 */

static T_LLINFO_ND6 nd6_cache[NUM_ND6_CACHE_ENTRY];

/*
 *  nd6_free -- �롼���������롣
 */

static void
nd6_free (T_LLINFO_ND6	*ln)
{
	T_DEF_ROUTER	*dr;

	dr = nd6_defrtrlist_lookup(&ln->addr);
	if (dr != NULL) {
		ln->state = ND6_LLINFO_INCOMPLETE;

		/* �ץ�ե��å������ꥹ�Ȥ���롼���������롣*/
		nd6_defrtrlist_del(dr);
		}
	}

/*
 *  nd6_timer -- ����õ�����������ޡ�
 */

void
nd6_timer (void)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_LLINFO_ND6	*ln;
	SYSTIM		now;
	int_t		ix;

	/* ���٥���å���ν��� */
	syscall(wai_sem(SEM_ND6_CACHE));
	syscall(get_tim(&now));
	for (ix = NUM_ND6_CACHE_ENTRY; ix -- > 0; ) {
		ln = &nd6_cache[ix];
		if (ln->state >= ND6_LLINFO_NO_STATE && (int32_t)(ln->expire - now) < 0) {
		                                               /* ln->expire < now */

			switch (ln->state) {

			case ND6_LLINFO_INCOMPLETE:	/* ̤���		*/
				if (ln->asked < ND6_MAX_MCAST_QUERY) {
					/*
					 *  �ޥ�����㥹�ȥ��ɥ쥹�����κ�������ʲ��ξ��ν���
					 */
					ln->asked ++;
					ln->expire = now + ND6_RETRANS_TIME;	/* ����õ�������ֳ� */
					nd6_ns_output(ifp, &in6_addr_unspecified, &ln->addr, ln, false);
					}
				else  {
					if (ln->hold != NULL) {
						/*
						 *  �ǽ�Ū�ˤϡ���α����Ƥ���ͥåȥ���Хåե���
						 *  ����С�ICMP6 ERROR ��ʬ���Ȥ��֤������ȡ�
						 *  �ͥåȥ���Хåե��������롣
						 *  �����������ߡ�icmp6_error �μ������Դ����Τ��ᡢ
						 *  �ͥåȥ���Хåե��γ����Τ߹Ԥ���
						 */
#if 0	/* ��α */
						icmp6_error(ln->hold, ICMP6_DST_UNREACH,
						                      ICMP6_DST_UNREACH_ADDR, 0);
#endif	/* #if 0 */
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

			case ND6_LLINFO_REACHABLE:	/* ��ã��ǽ		*/
				if (ln->expire) {
					ln->expire = now + ND6_GCOLLECTION_TIME;
					ln->state = ND6_LLINFO_STALE;
					}
				break;

			case ND6_LLINFO_STALE:		/* ��ã��ǽ����̤��ǧ	*/
				if (ln->expire) {
					if (ln->hold != NULL) {
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

			case ND6_LLINFO_DELAY:		/* ��ã��ǽ���γ�ǧ�Ե�	*/
				ln->asked = 1;
				ln->expire = now + ND6_RETRANS_TIME;		/* ����õ�������ֳ� */
				ln->state = ND6_LLINFO_PROBE;
				nd6_ns_output(ifp, &ln->addr, &ln->addr, ln, false);
				break;

			case ND6_LLINFO_PROBE:		/* ��ã��ǽ�����ǧ��	*/
				if (ln->asked < ND6_MAX_UCAST_QUERY) {
					/*
					 *  ��˥��㥹�ȥ��ɥ쥹�����κ�������ʲ��ξ��ν���
					 */
					ln->asked ++;
					ln->expire += ND6_RETRANS_TIME;	/* ����õ�������ֳ� */
					nd6_ns_output(ifp, &ln->addr, &ln->addr, ln, false);
					}
				else {
					if (ln->hold != NULL) {
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

				}
			}
		}
	syscall(sig_sem(SEM_ND6_CACHE));

	/* �ǥ��ե���ȥ롼�����ꥹ�Ȥν��� */
	nd6_defrtrlist_timer();

	/* �ץ�ե��å������ꥹ�Ȥν��� */
	nd6_prelist_timer();

	/* �ͥåȥ�����󥿥ե������Υ��ɥ쥹�ν��� */
	in6_ifaddr_timer(ifp);

	/*
	 *  ��ã��ǽ���֤�ͭ�����֤ι���
	 */
	if ((int32_t)(nd6_recalc_reachtm_interval - now) < 0) {
	           /* nd6_recalc_reachtm_interval < now */
		nd6_recalc_reachtm_interval	= now + ND6_RECALC_REACHTM_INTERVAL;
		nd6_reachable_time		= ND6_CALC_REACH_TIME(nd6_base_reachable_time);
		}
	timeout((callout_func)nd6_timer, NULL, ND6_TIMER_TMO);
	}

/*
 *  nd6_get_cache -- ���٥���å����������롣
 */

const T_LLINFO_ND6 *
nd6_get_cache (void)
{
	return nd6_cache;
	}

/*
 *  nd6_ifattach -- ����õ���ν�������Ԥ���
 */

void
nd6_ifattach (T_IFNET *ifp)
{
	}

/*
 *  nd6_output_hold -- ����õ������å������α����Ƥ���
 *                     ���ɥ쥹����Ԥ��Υǡ�������ब������������롣
 *
 *    ���: ���ޥե� SEM_ND6_CACHE �ˤ���å����֤ǸƽФ����ȡ�
 */

ER
nd6_output_hold (T_IFNET *ifp, T_LLINFO_ND6 *ln)
{
	SYSTIM now;

	/* ���ɥ쥹����Ԥ��Υǡ�������ब������������롣*/
	if (ln->hold) {

		/* �����ॢ���Ȥν��� */
		if (ln->tmout != TMO_FEVR) {

			/*
			 *  �����ॢ���Ȥλ��꤬�ʵפǤʤ������֤�᤮�Ƥ���С�
			 *  ���Ϥ��ʤ��ǽ�λ���롣
			 */
			syscall(get_tim(&now));
			if ((int32_t)(ln->tmout - now) < 0) {
			           /* ln->tmout < now */
				syscall(rel_net_buf(ln->hold));
				ln->hold = NULL;
				return E_TMOUT;
				}
			}
				
		nd6_output(ifp, ln->hold, &ln->addr, ln, TMO_FEVR);
		ln->hold = NULL;
		}
	return E_OK;
	}

/*
 *  nd6_lookup -- ����õ������å����õ�����롣
 *
 *    ���: ���ޥե� SEM_ND6_CACHE �ˤ���å����֤ǸƽФ����ȡ�
 *
 */

T_LLINFO_ND6 *
nd6_lookup (T_IN6_ADDR *addr, bool_t create)
{
	SYSTIM	min = 0xffffffff;
	int_t	ix, fix = -1, mix = -1;

	for (ix = NUM_ND6_CACHE_ENTRY; ix -- > 0; ) {
		if (nd6_cache[ix].state == 0) {
			/* ̤���ѥ���ȥ�Υ���ǥå�����Ͽ���롣*/
			if (fix == -1)
				fix = ix;
			}
		else if (IN6_ARE_ADDR_EQUAL(addr, &nd6_cache[ix].addr)) {
			return &nd6_cache[ix];
			}
		else if ((int32_t)(nd6_cache[ix].expire - min) < 0) {	/* nd6_cache[ix].expire < min */
			/* ͭ�����¤���û����ȥ�Υ���ǥå�����Ͽ���롣*/
			min = nd6_cache[ix].expire;
			mix = ix;
			}
		}

	if (create) {
		if (fix == -1)  {
			if (nd6_cache[mix].hold != NULL) {
				syscall(rel_net_buf(nd6_cache[mix].hold));
				}
			fix = mix;
			}
		syscall(get_tim(&nd6_cache[fix].expire));
		nd6_cache[fix].addr   = *addr;
		nd6_cache[fix].state  = ND6_LLINFO_NO_STATE;
		return &nd6_cache[fix];
		}
	else
		return NULL;
	}

/*
 *  nd6_cache_lladdr -- ����õ������å������Ͽ���롣
 */

T_LLINFO_ND6 *
nd6_cache_lladdr (T_IFNET *ifp, T_IN6_ADDR *from,
                  T_IF_ADDR *lladdr, uint8_t type, uint8_t code)
{
	T_LLINFO_ND6	*ln;
	SYSTIM		now;
	bool_t		newentry, olladdr, llchange, doupdate;
	int_t		newstate = ND6_LLINFO_INCOMPLETE;

	/* ���ɥ쥹��̵����ʤ鲿�⤷�ʤ���*/
	if (IN6_IS_ADDR_UNSPECIFIED(from))
		return NULL;

	/* ���٥���å������Ͽ���롣*/
	syscall(wai_sem(SEM_ND6_CACHE));
	if ((ln = nd6_lookup(from, false)) == NULL) {
		ln = nd6_lookup(from, true);
		newentry = true;
		}
	else
		newentry = false;

	olladdr = ln->state > ND6_LLINFO_INCOMPLETE;
	if (!olladdr || lladdr == NULL)
		llchange = false;
	else if (memcmp(lladdr, &ln->ifaddr, sizeof(T_IF_ADDR)))
		llchange = true;
	else
		llchange = false;

	/*
	 *  ��������ɽ
	 *
	 *  nd_na_flags
	 *  newnetry olladdr lladdr llchange ���� (L: lladdr ����Ͽ����)
	 *
	 *      F       F       N       -    (1)
	 *      F       T       N       -    (2)
	 *      F       F       Y       -    (3) L * -> STALE
	 *      F       T       Y       F    (4) L
	 *      F       T       Y       T    (5) L * -> STALE
	 *      T       -       N       -    (6)   * -> NO_STATE
	 *      T       -       Y       -    (7) L * -> STALE
	 */

	/* �ǡ�������ؤΥ��ɥ쥹�����Τ���Ƥ���й������롣*/
	if (lladdr != NULL) {
		ln->ifaddr = *(T_IF_ADDR *)lladdr;
		}

	if (newentry) {
		if (lladdr != NULL)					/* (7) */
			newstate = ND6_LLINFO_STALE;
		else							/* (6) */
			newstate = ND6_LLINFO_NO_STATE;
		doupdate = true;
		}
	else {
		if ((!olladdr && lladdr != NULL) ||			/* (3) */
		    ( olladdr && lladdr != NULL && llchange)) {		/* (5) */
			newstate = ND6_LLINFO_STALE;
			doupdate = true;
			}
		else							/* (1),(2),(4) */
			doupdate = false;
		}

	/* ���٥���å��奨��ȥ�򹹿����롣*/
	if (doupdate) {
		ln->state = newstate;

		syscall(get_tim(&now));
		if (ln->state == ND6_LLINFO_STALE) {
			ln->expire = now + ND6_GCOLLECTION_TIME;

			/* ���ɥ쥹����Ԥ��Υǡ�������ब������������롣*/
			nd6_output_hold(ifp, ln);
			}
		else if (ln->state == ND6_LLINFO_INCOMPLETE)
			ln->expire = now;
		}
	syscall(sig_sem(SEM_ND6_CACHE));


	/* �롼�����Τν��� */
	switch (type) {

	case ND_NEIGHBOR_SOLICIT:
		if (newentry)
			ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_REDIRECT:
		if (code == ND_REDIRECT_ROUTER)
			ln->flags |=  ND6_LLIF_ROUTER;
		else if (newentry)
			ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_ROUTER_SOLICIT:
		ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_ROUTER_ADVERT:
		if ((!newentry && (olladdr || lladdr != NULL)) ||
		    ( newentry && lladdr))
			ln->flags |=  ND6_LLIF_ROUTER;
		break;
		}

	return ln;
	}

/*
 *  nd6_is_addr_neighbor -- ���ꤵ�줿���ɥ쥹�ΥΡ��ɤ�Ʊ���󥯤ˤ��뤫�����å����롣
 */

bool_t
nd6_is_addr_neighbor (T_IFNET *ifp, T_IN6_ADDR *addr)
{
	if (IN6_IS_ADDR_LINKLOCAL(addr))
		return true;

	if (nd6_onlink_prefix_lookup(addr) != NULL)
		return true;

	if (nd6_lookup(addr, false) != NULL)
		return true;

	return false;
	}

/*
 *  nd6_output -- ����õ���ν��ϴؿ�
 *
 *    ���: ���ޥե� SEM_ND6_CACHE �ˤ���å����֤ǸƽФ����ȡ�
 */

ER
nd6_output (T_IFNET *ifp, T_NET_BUF *output, T_IN6_ADDR *dst, T_LLINFO_ND6 *ln, TMO tmout)
{
	ER	error = E_OK;
	SYSTIM	now;

	/*
	 *  �����襢�ɥ쥹���ޥ�����㥹�Ȥ������٥���å��夬
	 *  ���פξ���ľ�����������롣
	 */
	if (!(IN6_IS_ADDR_MULTICAST(dst) || !IF_IN6_NEED_CACHE(ifp))) {
		if (ln == NULL) {
			/* ���٥���å��夬̤����ξ�� */
			if (nd6_is_addr_neighbor(ifp, dst)) {
				/*
				 *  ���ꤵ�줿���ɥ쥹�ΥΡ��ɤ�Ʊ���󥯤ˤ�����ϡ�
				 *  ���٥���å����õ������̤����ξ�����Ͽ���롣
				 */
				ln = nd6_lookup(dst, true);
				}
			else {
				error = E_CLS;
				goto err_ret;
				}
			}

		/*
		 *  ���٥���å���ξ��֤����ǡ�������ؤΥ��ɥ쥹��ʬ���äƤ��Ƥ⡢
		 *  ��ã��ǽ������ǧ����Ƥ��ʤ��Ȥ��ϡ���ã��ǽ���Τ򳫻Ϥ��롣
		 */
		if (ln->state == ND6_LLINFO_STALE) {
			syscall(get_tim(&now));
			ln->expire = now + ND6_DELAY_TIME;
			ln->asked = 0;
			ln->state = ND6_LLINFO_DELAY;
			}

		/*
		 *  ���٥���å���ξ��֤����ǡ�������ؤΥ��ɥ쥹̤���ξ���
		 *  ����õ����Ԥ���
		 */
		if (ln->state <= ND6_LLINFO_INCOMPLETE) {

			/* �����ॢ���Ȥλ��꤬�ݡ���󥰤ʤ饿���ॢ���Ȥǽ�λ���롣*/
			if (tmout == TMO_POL) {
				error = E_TMOUT;
				goto err_ret;
				}

			if (ln->state == ND6_LLINFO_NO_STATE)
				ln->state = ND6_LLINFO_INCOMPLETE;

			/* ���Ǥˡ�̤���Υͥåȥ���Хåե�������С��������롣*/
			if (ln->hold != NULL) {
				syscall(rel_net_buf(ln->hold));
				}

			/*
			 *  ������ڥ�ǥ��󥰤��롣
			 *  IF �ǥͥåȥ���Хåե��������ʤ��ե饰�����ꤵ��Ƥ���Ȥ��ϡ�
			 *  ������ڥ�ǥ��󥰤��ʤ���
			 */
			if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
				ln->hold = output;

				/* �����ॢ���Ȥ����� */
				if (tmout == TMO_FEVR)
					ln->tmout = tmout;
				else {
					syscall(get_tim(&now));
					ln->tmout = now + tmout;
					}
				}
			else {
				output->flags &= ~NB_FLG_NOREL_IFOUT;
				syscall(get_tim(&now));
				ln->tmout = now + tmout;
				}

			if (ln->expire) {
				if (ln->asked < ND6_MAX_MCAST_QUERY) {
					syscall(get_tim(&now));
					if ((int32_t)(ln->expire - now) < 0) {
					           /* ln->expire < now */
						ln->expire += ND6_RETRANS_TIME;	/* ����õ�������ֳ� */
						ln->asked ++;
						nd6_ns_output(ifp, &in6_addr_unspecified, dst, ln, false);
						}
					}
				}
			return error;
			}
		}

	/*
	 *  ��ʣ�����Ф��줿���󥿥ե������ˤϽ��Ϥ��ʤ���
	 */
	if ((ifp->flags & ND6_IFF_IFDISABLED) != 0) {
		return E_OK;
		}

	IF_SET_PROTO(output, IF_PROTO_IPV6);
	error = IF_OUTPUT(output, dst, ln ? & ln->ifaddr : NULL, tmout);
	return error;

err_ret:
	syscall(rel_net_buf(output));
	return error;
	}

/*
 *  nd6_storelladdr -- ���Ϥ���ͥåȥ�����󥿥ե������Υ��ɥ쥹���֤���
 */

ER
nd6_storelladdr (T_IF_ADDR *out, T_IN6_ADDR *dst, T_IF_ADDR *ifa)
{
	if (IN6_IS_ADDR_MULTICAST(dst)) {
		IF_IN6_RESOLVE_MULTICAST(out, dst);
		}
	else {
		*out = *ifa;
		}

	return E_OK;
	}

/*
 *  nd6_option -- ����õ�����ץ����ν���
 *
 *    ���: ���ץ���󥪥ե��å�����ˤϡ����ե��å� + 8 �����ꤵ��Ƥ��롣
 */

ER
nd6_options (uint8_t *opt, void *nh, uint_t len)
{
	T_ND_OPT_HDR	*opth;
	ER		error = E_OK;
	int_t		pi_count = 0;	/* �ץ�ե��å�������θĿ� */

	opth = (T_ND_OPT_HDR *)nh;
	memset(opt, 0, ND_OPT_OFF_ARRAY_SIZE);

	while (error == E_OK && ((uint8_t *)opth - (uint8_t *)nh) < (256 - 8) && len > 0) {

		/* ���ץ����Ĺ�� 0 �λ��ϡ������ʥ��ץ����Ȥ��ƽ������롣*/
		if (opth->len == 0) {
			error = E_PAR;
			break;
			}

		/* ���ץ����Υ����פˤ��ʬ�����롣*/
		switch (opth->type) {
		case ND_OPT_SOURCE_LINKADDR:		/* ������ͥåȥ�����󥿥ե������Υ��ɥ쥹	*/
		case ND_OPT_TARGET_LINKADDR:		/* �оݥͥåȥ�����󥿥ե������Υ��ɥ쥹	*/
		case ND_OPT_REDIRECTED_HEADER:		/* ������쥯�ȡ��إå�				*/
		case ND_OPT_MTU:			/* MTU						*/
			if (opt[ND_OPT_OFF_ARRAY_IX(opth->type)]) {
				/* �ץ�ե��å�������ʳ���Ʊ�����ץ����ʣ�����ꤵ��Ƥ��롣*/
				error = E_PAR;
				}
			else {
				opt[ND_OPT_OFF_ARRAY_IX(opth->type)] = (uint8_t *)opth - (uint8_t *)nh + 8;
				}
			break;
		case ND_OPT_PREFIX_INFORMATION:		/* �ץ�ե��å�������				*/
			if (!opt[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFORMATION)]) {
				/*
				 *  �ץ�ե��å�������Ϻǽ�˸��줿���ե��åȤΤߵ�Ͽ���롣
				 */
				opt[ND_OPT_OFF_ARRAY_IX(opth->type)] = (uint8_t *)opth - (uint8_t *)nh + 8;
				}
			pi_count ++;
			break;
		default:
			/*
			 *  ������������ץ�ȥ���ؤγ�ĥ���б����뤿�ᡢ
			 *  ǧ���Ǥ��ʤ����ץ�����ñ��̵�뤷��������³�Ԥ��롣
			 */
			break;
			}
		len -= opth->len << 3;		/* ���ץ����Ĺ��ñ�̤� 8 �Х��� */
		opth = (T_ND_OPT_HDR *)((uint8_t *)opth + (opth->len << 3));
		}

	opt[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)] = pi_count;
	return error;
	}

#endif /* of #ifdef SUPPORT_INET6 */
