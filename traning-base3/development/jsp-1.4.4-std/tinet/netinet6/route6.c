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
 *  @(#) $Id: route6.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/route6.c,v 1.6 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: route6.c,v 1.24 2001/03/14 03:07:05 itojun Exp $	*/

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

#include <net/net.h>
#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#ifdef SUPPORT_INET6

#if 0
	/*
	 *  �̿��Ӱ�򿩤��Ĥ֤�����ؤ��б��Τ��ᡢ
	 *  ������ 0 ��ϩ����إå��ν�����Ԥ�ʤ���
	 */

/*
 *  ip6_rthdr0 -- ������ 0 ��ϩ����إå������ϴؿ�
 */

static ER
ip6_rthdr0 (T_NET_BUF *input, T_IP6_RT0_HDR *rt0h)
{
	if (rt0h->segleft == 0) {
		/* ��ѥΡ��ɿ��� 0 �ʤΤǡ������Ρ��� */
		return E_OK;
		}

	/* len �� segleft �������������å� */
#ifdef IP6_CFG_COMPAT_RFC1883
	if ((rt0h->len % 2) || (rt0h->len > 46)) {
#else
	if (rt0h->len % 2) {
#endif
		/*
		 *  len �϶����ǡ�(23 * 2) �ޤǡ�
		 *  ��������(23 * 2) �����¤� RFC 2462 �Ǻ������Ƥ��롣
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rt0h->len - input->buf) - IF_HDR_SIZE);
		return E_PAR;
		}

	/* len ����ѥΡ��ɿ���̷�⤷�Ƥ��ʤ��������å����롣*/
	if ((rt0h->len / 2) < rt0h->segleft) {
		/*
		 *  len �� 8�����ƥå�ñ�̡�segleft �� 16�����ƥå�ñ�̤ʤΤǡ�
		 *  len / 2 == segleft �Ȥʤ�Ϥ���
		 *  len / 2 <  segleft �ϥ��顼��
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rt0h->segleft - input->buf) - IF_HDR_SIZE);
		return E_PAR;
		}

	/*
	 *  �Ĥ����ѥΡ��ɿ��� 1 �ʾ�Ǥ���С����ΥΡ��ɤϺǽ�Ū��
	 *  �����Ρ��ɤǤϤʤ����ܼ����Ǥϡ���Ѥ򤷤ʤ��Τǡ�
	 *  ���ϥǡ��������ν�����λ���롣
	 */
	syscall(rel_net_buf(input));
	return E_PAR;
	}

#endif

/*
 *  route6_input -- ��ϩ����إå������ϴؿ�
 */

uint_t
route6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP6_RT_HDR	*rth;
	uint_t		len, off = *offp;

	/* �ͥåȥ���Хåե��λĤ��Ĺ��������å����롣*/
	if (input->len - off < sizeof(T_IP6_RT_HDR))
		goto buf_rel;

	rth = (T_IP6_RT_HDR *)(input->buf + off);
	len = (rth->len + 1) << 3;

	/* ��ϩ����إå���Ĺ��������å����롣*/
	if (input->len < off + len)
		goto buf_rel;

#if 0
	/*
	 *  �̿��Ӱ�򿩤��Ĥ֤�����ؤ��б��Τ��ᡢ
	 *  ������ 0 ��ϩ����إå��ν�����Ԥ�ʤ���
	 */
	if (rth->type == IPV6_RTHDR_TYPE_0) {
		if (ip6_rthdr0(input, (T_IP6_RT0_HDR*)rth) != E_OK) {

			/* ���顼�ξ��ϡ�ip6_rthdr0 �ǥХåե��������Ƥ��롣*/
			return IPPROTO_DONE;
			}
		}
	else if (rth->segleft != 0) {

		/*
		 *  �Ĥ����ѥΡ��ɿ��� 1 �ʾ�Ǥ���С����ΥΡ��ɤϺǽ�Ū��
		 *  �����Ρ��ɤǤϤʤ����ܼ����Ǥϡ���Ѥ򤷤ʤ��Τǡ�
		 *  ICMP6 ���顼���������ƽ�����λ���롣
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rth->type - input->buf) - IF_HDR_SIZE);
		return IPPROTO_DONE;
		}
#else
	if (rth->segleft != 0) {

		/*
		 *  �Ĥ����ѥΡ��ɿ��� 1 �ʾ�Ǥ���С����ΥΡ��ɤϺǽ�Ū��
		 *  �����Ρ��ɤǤϤʤ����ܼ����Ǥϡ���Ѥ򤷤ʤ��Τǡ�
		 *  ICMP6 ���顼���������ƽ�����λ���롣
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rth->type - input->buf) - IF_HDR_SIZE);
		return IPPROTO_DONE;
		}
#endif

	*nextp = *offp - IF_HDR_SIZE + offsetof(T_IP6_RT_HDR, next);
	*offp += len;
	return rth->next;

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif /* of #ifdef SUPPORT_INET6 */
