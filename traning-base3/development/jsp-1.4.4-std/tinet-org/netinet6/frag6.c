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
 *  @(#) $Id: frag6.c,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/frag6.c,v 1.9 2002/04/19 04:46:22 suz Exp $	*/
/*	$KAME: frag6.c,v 1.33 2002/01/07 11:34:48 kjc Exp $	*/

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
#include <net/net_buf.h>
#include <net/net_var.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#ifdef SUPPORT_INET6

#ifdef IP6_CFG_FRAGMENT

/*
 *  �ǡ��������ƹ������塼����
 */

static T_NET_BUF	*ip6_frag_queue[NUM_IP6_FRAG_QUEUE];
static T_IN6_ADDR	 ip6_frag_dest [NUM_IP6_FRAG_QUEUE];

/*
 *  ip6_get_frag_queue -- �ǡ��������ƹ������塼��������롣
 */

const T_NET_BUF **
ip6_get_frag_queue (void)
{
	return (const T_NET_BUF **)ip6_frag_queue;
	}

/*
 *  frag6_free_queue -- �ǡ��������ƹ������塼��������롣
 *
 *    ���: �ǡ��������ƹ������塼������å����Ƥ���ƤӽФ����ȡ�
 */

static void
frag6_free_queue (T_NET_BUF **queue)
{
	T_NET_BUF 	*frag, *next;
	T_QIP6_HDR	*qip6h;

	frag = *queue;
	while (frag != NULL) {
		qip6h = GET_QIP6_HDR(frag);
		next  = qip6h->next_frag;
		syscall(rel_net_buf(frag));
		frag = next;
		}
	*queue = NULL;
	}

/*
 *  frag6_timer -- �ǡ��������ƹ�������������
 */

void
frag6_timer (void)
{
	T_NET_BUF	*frag;
	T_QIP6_HDR	*qip6h;
	T_IP6_FRAG_HDR	*qip6fh;
	int_t		ix;

	syscall(wai_sem(SEM_IP6_FRAG_QUEUE));
	for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
		frag = ip6_frag_queue[ix];
		if (frag != NULL) {
			qip6h = GET_QIP6_HDR(frag);
			if (qip6h->ftim > 0 && -- qip6h->ftim == 0) {

				qip6fh = (T_IP6_FRAG_HDR *)(frag->buf + qip6h->foff);
				if (ntohs(qip6fh->off_flag & IP6F_OFF_MASK) == 0) {

					/*
					 *  ��Ƭ�����ҤΥ��ե��åȤ� 0 �λ��Τ�
					 *  ICMPv6 ���顼��å��������������롣
					 */

					/* ��Ƭ�����Ҥ�ǡ��������ƹ������塼���鳰����*/
					ip6_frag_queue[ix] = qip6h->next_frag;

					/* �����襢�ɥ쥹�򸵤��᤹��*/
					GET_IP6_HDR(frag)->dst = ip6_frag_dest[ix];

					/* ICMPv6 ���顼��å��������������롣*/
					icmp6_error(frag, ICMP6_TIME_EXCEEDED,
					                  ICMP6_TIME_EXCEED_REASSEMBLY, 0);
					}

				/* �ǡ��������ƹ������塼��������롣*/
				NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_TMOUT], 1);
				NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_DROP], 1);
				frag6_free_queue(&ip6_frag_queue[ix]);
				}
			}
		}
	syscall(sig_sem(SEM_IP6_FRAG_QUEUE));
	}

#endif	/* #ifdef IP6_CFG_FRAGMENT */

/*
 *  frag6_input -- ���ҥإå������ϴؿ�
 */

uint_t
frag6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_IP6_HDR	*ip6h;
	T_IP6_FRAG_HDR	*ip6fh;
	T_NET_BUF	*input = *inputp;
	uint_t		off = *offp;

#ifdef IP6_CFG_FRAGMENT

	T_QIP6_HDR	*qip6h, *rip6h;
	T_IP6_FRAG_HDR	*qip6fh = NULL;
	T_NET_BUF	**ip6fq = NULL, *prev, *next, *frag;
	int_t		ix;
	int32_t		unfraglen, diff;
	uint16_t	fragpartlen, qfragpartlen, fragoff, qfragoff, plen;
	uint8_t		ftim, *prev_next;
	uint_t		nextproto = IPPROTO_DONE;

#endif	/* #ifdef IP6_CFG_FRAGMENT */

	/* �ͥåȥ���Хåե��λĤ��Ĺ��������å����롣*/
	if (input->len - off < sizeof(T_IP6_FRAG_HDR))
		goto buf_rel;

	/* 
	 *  ����ڥ����ɥ��ץ��������ҥإå���Ʊ���˻��Ѥ��뤳�Ȥ�
	 *  �Ǥ��ʤ����ڥ�����Ĺ���� 0 �ʤ顢����ڥ����ɥ��ץ����
	 *  ���ꤵ��Ƥ��뤳�Ȥˤʤ�Τ� ICMP �ǥ��顼�������Ԥ�
	 *  ���Τ��롣
	 */
	ip6h = GET_IP6_HDR(input);
	if (ip6h->plen == 0) {
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   off - IF_HDR_SIZE);
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return IPPROTO_DONE;
		}

	/*
	 *  ���ե��åȤ� 0 �ǡ��ǽ��ե饰���ȤǤ���С�
	 *  ʬ�����פΥǡ��������ʤΤǡ�
	 *  ���إå���ؤ��ѿ���Ĵ�����ƽ�λ���롣
	 */
	ip6fh = (T_IP6_FRAG_HDR *)(input->buf + off);
	if (ip6fh->off_flag == 0) {
		*nextp = *offp - IF_HDR_SIZE + offsetof(T_IP6_FRAG_HDR, next);
		*offp = off + sizeof(T_IP6_FRAG_HDR);
		return ip6fh->next;
		}

#ifdef IP6_CFG_FRAGMENT

	/*
	 *  �ڥ�����Ĺ������å����롣
	 */
	if ((ip6fh->off_flag & IP6F_MORE_FRAG) && 
	    ((ntohs(ip6h->plen) - (off - IF_HDR_SIZE)) & 0x7) != 0) {
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   offsetof(T_IP6_HDR, plen));
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return nextproto;
		}
	NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmReqds, 1);

	syscall(wai_sem(SEM_IP6_FRAG_QUEUE));

	/*
 	 *  �ǡ��������ƹ������塼���󤫤顢�б����륨��ȥ��õ����
 	 */
	for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
		if (ip6_frag_queue[ix] != NULL) {
			qip6h  = GET_QIP6_HDR(ip6_frag_queue[ix]);
			qip6fh = (T_IP6_FRAG_HDR *)(ip6_frag_queue[ix]->buf + qip6h->foff);
			if (ip6fh->ident == qip6fh->ident               &&
			    IN6_ARE_ADDR_EQUAL(&ip6h->src, &qip6h->src) &&
			    IN6_ARE_ADDR_EQUAL(&ip6h->dst, &ip6_frag_dest[ix])) {
				ip6fq = &ip6_frag_queue[ix];
			    	break;
			    	}
			}
		}

 	if (ip6fq == NULL) {

		/*
	 	 *  ���Ҥ�������������å����롣
		 */
		unfraglen = 0;
		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  ���Ϥ������Ҥ���Ƭ������
			 *  ʬ��Ǥ��ʤ���ʬ��Ĺ�� unfraglen ��׻����롣
			 */
			unfraglen = (off - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		/*
		 *             off
		 *  |<--------------------------->|
		 *  |          off - IF_HDR_SIZE  |
		 *  |        |<------------------>|
		 *  |        | off - IF_HDR_SIZE + IP6_FRAG_HDR_SIZE |
		 *  |        |<------------------------------------->|
		 *  +--------+----------+---------+------------------+-------------+
		 *  | IF HDR | IPv6 HDR | EXT HDR |     FRAG HDR     |   Payload   |
		 *  +--------+----------+---------+------------------+-------------+
		 *                      |<---------------------------------------->|
		 *                      |             Payload Size                 |
		 *           |<--------------------------------------------------->|
		 *           |         IP6_HDR_SIZE + Payload Size                 |
		 *                                                   |<----------->|
		 *                                                   | fragpartlen |
		 */
		fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
		if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {
			icmp6_error(input, ICMP6_PARAM_PROB,
			                   ICMP6_PARAMPROB_HEADER,
			                   (off - IF_HDR_SIZE) +
			                   offsetof(T_IP6_FRAG_HDR, off_flag));
			goto sig_ret;
			}

		/*
	 	 *  ip6fq == NULL �Ǥ���С��б����륨��ȥ��̵���Τǡ�
	 	 *  �ǡ��������ƹ������塼����ˡ�����ȥ���ɲä��롣
	 	 */
		for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {

			/* ��������ȥ��õ����*/
			if (ip6_frag_queue[ix] == NULL) {
				ip6fq = &ip6_frag_queue[ix];
				break;
				}
			}

		/*
		 *  ip6fq == NULL �Ǥ���С���������ȥ̵꤬���Τǡ�
		 *  �����ॢ���ȡ�hlim�ˤ�û������ȥ�������롣
		 */
 		if (ip6fq == NULL) {

		 	ftim = IPV6_MAXHLIM;
			for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
				if (ip6_frag_queue[ix] != NULL) {
					rip6h  = GET_QIP6_HDR(ip6_frag_queue[ix]);
					if (rip6h->ftim < ftim) {
						ftim  = rip6h->ftim;
						ip6fq = &ip6_frag_queue[ix];
						}
					}
				}
			frag6_free_queue(ip6fq);
			}

		/*
		 *  ����ȥ�����ꤹ�롣
		 */
		*ip6fq = input; 
		ip6_frag_dest[ip6fq - ip6_frag_queue] = ip6h->dst;
		qip6h  = GET_QIP6_HDR(*ip6fq);
		qip6h->ftim = IPV6_FRAGTTL;
		qip6h->foff = off;
		qip6h->flen = fragpartlen;
		qip6h->next_frag = NULL;
 		}
 	else {

		/*
	 	 *  ���Ҥ�������������å����롣
		 */
		unfraglen = 0;
		fragoff = ntohs(((T_IP6_FRAG_HDR *)((*ip6fq)->buf + GET_QIP6_HDR(*ip6fq)->foff))->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  �ǡ��������ƹ������塼�κǽ�����Ҥ���Ƭ������
			 *  ʬ��Ǥ��ʤ���ʬ��Ĺ�� unfraglen ��׻����롣
			 */
			unfraglen = (GET_QIP6_HDR(*ip6fq)->foff - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  ���Ϥ������Ҥ���Ƭ������
			 *  ʬ��Ǥ��ʤ���ʬ��Ĺ�� unfraglen ��׻����롣
			 */
			unfraglen = (off - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		/*
		 *             off
		 *  |<--------------------------->|
		 *  |          off - IF_HDR_SIZE  |
		 *  |        |<------------------>|
		 *  |        | off - IF_HDR_SIZE + IP6_FRAG_HDR_SIZE |
		 *  |        |<------------------------------------->|
		 *  +--------+----------+---------+------------------+-------------+
		 *  | IF HDR | IPv6 HDR | EXT HDR |     FRAG HDR     |   Payload   |
		 *  +--------+----------+---------+------------------+-------------+
		 *                      |<---------------------------------------->|
		 *                      |             Payload Size                 |
		 *           |<--------------------------------------------------->|
		 *           |         IP6_HDR_SIZE + Payload Size                 |
		 *                                                   |<----------->|
		 *                                                   | fragpartlen |
		 */
		fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
		if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {
			icmp6_error(input, ICMP6_PARAM_PROB,
			                   ICMP6_PARAMPROB_HEADER,
			                   (off - IF_HDR_SIZE) +
			                   offsetof(T_IP6_FRAG_HDR, off_flag));
			goto sig_ret;
			}
		
		if (ntohs(ip6fh->off_flag & IP6F_OFF_MASK) == 0) {

			/*
		 	 *  ���Ϥ������Ҥ���Ƭ������
		 	 *  �ǡ��������ƹ������塼�κǸ�����Ҥ���
		 	 *  �ǡ��������κ���Ĺ��Ķ���Ƥ��ʤ��������å����롣
			 */

			/* �Ǹ�����Ҥ�õ�����롣*/
			next = *ip6fq;
			while ((qip6h = GET_QIP6_HDR(next))->next_frag != NULL)
				next = qip6h->next_frag;

			/* �Ǹ�����ҤΥ��ե��åȤ����ҥ�������׻����롣*/
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			fragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			fragpartlen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (qip6h->foff - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
			if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {

				/*
				 *  �ǡ��������κ���Ĺ��Ķ���Ƥ�����ϡ�
			 	 *  �ǡ��������ƹ������塼���Τ��˴����롣
			 	 */
				frag6_free_queue(ip6fq);
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		/* ECN �������������å���̤���� */

		/*
		 *  ���Ҥ򥨥�ȥ���������롣
	 	 *  �ǡ��������ƹ������塼���顢���Ϥ������Ҥ���������Ҥ�õ�����롣
		 */
		prev = NULL;
		next = *ip6fq;
		while (next != NULL) {
			qip6h  = GET_QIP6_HDR(next);
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			if (ntohs(ip6fh->off_flag & IP6F_OFF_MASK) <= ntohs(qip6fh->off_flag & IP6F_OFF_MASK))
				break;
			prev = next;
			next = qip6h->next_frag;
			}

		/*
		 *  prev �ϡ����Ϥ������Ҥ���������ҡ������� NULL �ξ��ϡ�
		 *  ���Ϥ������Ҥ��ǡ��������ƹ������塼����ǺǤ��������ҡ�
		 *  next �ϡ����Ϥ������Ҥ�������ҡ������� NULL �ξ��ϡ�
		 *  ���Ϥ������Ҥ��ǡ��������ƹ������塼����ǺǤ������ҡ�
		 */
		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (prev != NULL) {

			/*
			 *  �������Ҥȡ����Ϥ������Ҥ��ŤʤäƤ��ʤ��������å����롣
			 *
			 *    qfragoff
			 *    |   qfragparglen
			 *    |<------------------>|
			 *    +--------------------+
			 *    |        prev        |
			 *    +--------------------+
			 *
			 *                         +--------------------+
			 *                         |        input       |
			 *                         +--------------------+
			 *                         |
			 *                         fragoff
			 */
			qip6h  = GET_QIP6_HDR(prev);
			qip6fh = (T_IP6_FRAG_HDR *)(prev->buf + qip6h->foff);
			qfragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			qfragpartlen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

			diff = ((int32_t)qfragoff + qfragpartlen) - fragoff;
			if (diff > 0) {

				/* �ŤʤäƤ���С����Ϥ������Ҥ��˴����ƽ�λ���롣*/
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		if (next != NULL) {

			/*
			 *  ������Ҥȡ����Ϥ������Ҥ��ŤʤäƤ��ʤ��������å����롣
			 *
			 *    fragoff
			 *    |    fragparglen
			 *    |<------------------>|
			 *    +--------------------+
			 *    |       input        |
			 *    +--------------------+
			 *
			 *                         +--------------------+
			 *                         |         next       |
			 *                         +--------------------+
			 *                         |
			 *                         qfragoff
			 */
			qip6h  = GET_QIP6_HDR(next);
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			qfragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

			diff = ((int32_t)fragoff + fragpartlen) - qfragoff;
			if (diff > 0) {

				/* �ŤʤäƤ���С����Ϥ������Ҥ��˴����ƽ�λ���롣*/
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		/* ���Ϥ������Ҥ����ꤹ�롣*/
		qip6h  = GET_QIP6_HDR(input);
		qip6h->foff = off;
		qip6h->flen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

		if (prev == NULL) {
			*ip6fq = input;
			qip6h->ftim = IPV6_FRAGTTL;
			}
		else
			GET_QIP6_HDR(prev)->next_frag = input;
		qip6h->next_frag = next;

		/*
		 *  ���Ƥ����Ҥ���������������å����롣
		 */
		plen = 0;
		frag = *ip6fq;
		while (frag != NULL) {
			qip6h  = GET_QIP6_HDR(frag);
			qip6fh = (T_IP6_FRAG_HDR *)(frag->buf + qip6h->foff);
			if (ntohs(qip6fh->off_flag & IP6F_OFF_MASK) != plen) {

				/* ���Ҥ�Ϣ³���Ƥ��ʤ���*/
				goto sig_ret;
				}
			plen += qip6h->flen;
			frag = qip6h->next_frag;
			}
		if (ntohs(qip6fh->off_flag & IP6F_MORE_FRAG) != 0) {

			/* �Ǹ�����Ҥ�������Ƥ��ʤ���*/
			goto sig_ret;
			}

		/*
		 *  ���Ƥ����Ҥ���������Τǡ��ƹ������롣
		 */

		/* �ͥåȥ���Хåե���������롣*/
		qip6h  = GET_QIP6_HDR(*ip6fq);
		qip6fh = (T_IP6_FRAG_HDR *)((*ip6fq)->buf + qip6h->foff);
		if (tget_net_buf(inputp, qip6h->foff + plen, TMO_IP6_FRAG_GET_NET_BUF) == E_OK) {

			/*
			 *  ���ҥإå���ľ���Υإå��� NEXT �ե�����ɤΥ��ɥ쥹���������
			 *  �����᤹��
			 */
			if ((prev_next = ip6_get_prev_hdr(*ip6fq, qip6h->foff)) == NULL) {
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			*prev_next = qip6fh->next;
			input = *inputp;

			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_OK], 1);
			NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmOKs, 1);

			/*
			 *  IPv6 �إå���ʬ��Ǥ��ʤ���ʬ��
			 *  �ǡ��������ƹ������塼�������Ƭ�����Ҥ��饳�ԡ����롣
			 */
			memcpy(input->buf, (*ip6fq)->buf, qip6h->foff);

			/* �����襢�ɥ쥹�򸵤��᤹��*/
			ip6h = GET_IP6_HDR(input);
			ip6h->dst = ip6_frag_dest[ip6fq - ip6_frag_queue];

			/* offp �򡢺ƹ����������Ҥ���Ƭ�����ꤹ�롣*/
			*offp = qip6h->foff;

			/* �ͥåȥ���Хåե�Ĺ�����ꤹ�롣*/
			input->len = plen + qip6h->foff;

			/*
			 *  ���Ƥ����Ҥ򥳥ԡ����롣
			 */
			frag = *ip6fq;
			off  = qip6h->foff;
			while (frag != NULL) {
				qip6h  = GET_QIP6_HDR(frag);
				memcpy(input->buf + off,
				       frag->buf + qip6h->foff + sizeof(T_IP6_FRAG_HDR),
				       qip6h->flen);
				off += qip6h->flen;
				frag = qip6h->next_frag;
				}

			/* �ڥ�����Ĺ�����ꤹ�롣*/
			ip6h->plen = htons(plen);

			*nextp = offsetof(T_IP6_HDR, next);
			nextproto = ip6h->next;
			}
		else {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_NO_BUF], 1);
			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_DROP], 1);
			NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
			}

		/* �ǡ��������ƹ������塼��������롣*/
		frag6_free_queue(ip6fq);
 		}

sig_ret:
	syscall(sig_sem(SEM_IP6_FRAG_QUEUE));
	return nextproto;

#else	/* #ifdef IP6_CFG_FRAGMENT */

	/*
	 *  �ǡ���������ʬ�䡦�ƹ����Ԥ�ʤ����ϡ������Ҥ��˴�����
	 *  �Ǹ�����Ҥ���������Ȥ���
	 *  ICMP ���顼�������Ԥ����Τ��롣
	 */
	if ((ip6fh->off_flag & IP6F_MORE_FRAG) == 0) {
		icmp6_error(input, ICMP6_TIME_EXCEEDED,
		                   ICMP6_TIME_EXCEED_REASSEMBLY, 0);
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return IPPROTO_DONE;
		}

#endif	/* #ifdef IP6_CFG_FRAGMENT */

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif /* of #ifdef SUPPORT_INET6 */
