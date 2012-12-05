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
 *  @(#) $Id: ip_icmp.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)ip_icmp.c	8.2 (Berkeley) 1/4/94
 * $FreeBSD: src/sys/netinet/ip_icmp.c,v 1.33.2.3 1999/10/14 11:49:38 des Exp $
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
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

/*
 *  �ѿ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

T_ICMP_STATS icmp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ؿ�
 */

static void icmp_echo (T_NET_BUF *input, uint_t ihoff);
static void icmp_unreach (T_NET_BUF *input, uint_t ihoff);

#if NUM_REDIRECT_ROUTE_ENTRY > 0

static void icmp_redirect (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp_echo -- �������׵����������Ȥ��ν���
 *
 *    input �ˤ� IF �إå��� IP �إå���ޤޤ�Ƥ��롣
 */

static void
icmp_echo (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h;
	T_ICMP4_HDR	*icmp4h;
	T_IN4_ADDR	addr;

	NET_COUNT_MIB(icmp_stats.icmpInEchos, 1);

	/* ��å������η��򥨥����׵� (8) ���� ���������� (0) ��	*/
	/* �ѹ����������֤���					*/

	icmp4h = GET_ICMP4_HDR(input, ihoff);
	icmp4h->type = ICMP4_ECHO_REPLY;

	/* IP �إå��ΰ����ȯ������򴹤��롣*/
	ip4h      = GET_IP4_HDR(input);
	addr      = ip4h->src;
	ip4h->src = ip4h->dst;
	ip4h->dst = addr;

	/* �����å������׻����롣*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h,
	                       (uint_t)(((input->len - GET_IF_IP4_HDR_SIZE(input)) + 3) >> 2 << 2));

	/* �������롣*/
	NET_COUNT_ICMP4(net_count_icmp4.out_octets,
	               input->len - GET_IF_IP4_HDR_SIZE(input));
	NET_COUNT_ICMP4(net_count_icmp4.out_packets, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutEchoReps, 1);
	ip_output(input, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp_unreach -- ICMP4_UNREACH ����������Ȥ��ν���
 */

static const int8_t code2error[] = {
	EV_HURCH,	/* ICMP4_UNREACH_NET			 0 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST			 1 */
	EV_CNNRF,	/* ICMP4_UNREACH_PROTOCOL		 2 */
	EV_CNNRF,	/* ICMP4_UNREACH_PORT			 3 */
	EV_MSIZE,	/* ICMP4_UNREACH_FLAG			 4 */
	EV_HURCH,	/* ICMP4_UNREACH_SRC_FAIL		 5 */
	EV_HURCH,	/* ICMP4_UNREACH_NET_UNKNOWN		 6 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_UNKNOWN		 7 */
	EV_HURCH,	/* ICMP4_UNREACH_ISOLATED		 8 */
	EV_HURCH,	/* ICMP4_UNREACH_NET_PROHIB		 9 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_PROHIB		10 */
	EV_HURCH,	/* ICMP4_UNREACH_TOS_NET		11 */
	EV_HURCH,	/* ICMP4_UNREACH_TOS_HOST		12 */
	EV_HURCH,	/* ICMP4_UNREACH_FILTER_PROHIB		13 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_PRECEDENCE	14 */
	EV_HURCH,	/* ICMP4_UNREACH_PRECEDENCE_CUTOFF	15 */
	};

static void
icmp_unreach (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h;
	uint8_t		code;
	ER		error;

	NET_COUNT_MIB(icmp_stats.icmpInDestUnreachs, 1);

	ip4h   = (T_IP4_HDR*)GET_ICMP4_SDU(input, ihoff);
	code  = GET_ICMP4_HDR(input, ihoff)->code;
	error = code2error[code];
	if (ip4h->proto == IPPROTO_TCP) {

#ifdef SUPPORT_TCP

		memcpy(GET_IP4_HDR(input), ip4h, input->len - (IP4_HDR_SIZE + ICMP4_HDR_SIZE));
		input->len -= IP4_HDR_SIZE + ICMP4_HDR_SIZE;
		tcp_notify(input, error);

#endif	/* of #ifdef SUPPORT_TCP */

		}
	else
		syslog(LOG_NOTICE, "[ICMP] error, code: %d.", code);
	}

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  icmp_redirect -- ����ľ����å���������������Ȥ��ν���
 *
 *    input �ˤ� IF �إå��� IP �إå���ޤޤ�Ƥ��롣
 */

static void
icmp_redirect (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h, *sip4h;
	T_ICMP4_HDR	*icmp4h;

	ip4h   = GET_IP4_HDR(input);
	icmp4h = GET_ICMP4_HDR(input, ihoff);
	sip4h  = (T_IP4_HDR *)GET_ICMP4_SDU(input, ihoff);

	/*
	 *  ���ƥ����å����ʲ��ξ��ϥ��顼
	 *
	 *    ��ICMP �����ɤ���ICMP4_REDIRECT_PORT_AND_HOST (3) �ʾ�
	 *    ���ǡ��������Ĺ����ICMP �κǾ�Ĺ���û�� (IP �إå� + ICMP �إå� + IP �إå� + 8)
	 *    ���ǡ��������Ĺ����ICMP �κ���Ĺ���û��
	 *    ��
	 */
	if (icmp4h->code > ICMP4_REDIRECT_PORT_AND_HOST ||
	    ip4h->len < GET_IP4_ICMP4_HDR_SIZE(input) + 8 + IP4_HDR_SIZE ||
	    ip4h->len < GET_IP4_ICMP4_HDR_SIZE(input) + 8 + (IP4_VHL_HL(sip4h->vhl) << 2)) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		return;
		}

	in4_rtredirect(icmp4h->data.addr, sip4h->dst, IN_RTF_REDIRECT, TMO_IN_REDIRECT);
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp_input -- ICMP �����ϴؿ�
 *
 *    input �ˤ� IF �إå��� IP �إå���ޤޤ�Ƥ��롣
 */

uint_t
icmp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_ICMP4_HDR	*icmp4h;
	T_IN4_ADDR	addr;
	uint_t		len, align;

	NET_COUNT_ICMP4(net_count_icmp4.in_octets,
	               input->len - GET_IF_IP4_HDR_SIZE(input));
	NET_COUNT_ICMP4(net_count_icmp4.in_packets, 1);

	/* ICMP �إå���Ĺ��������å����롣*/
	if (input->len < IF_IP4_ICMP4_HDR_SIZE) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		NET_COUNT_MIB(icmp_stats.icmpInErrors, 1);
		goto buf_rel;
		}

	icmp4h = (T_ICMP4_HDR *)(input->buf + *offp);

	/* 4 �����ƥåȶ����Υǡ���Ĺ */
	len   = input->len - *offp;
	align = (len + 3) >> 2 << 2;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset((uint8_t*)input->buf + input->len, 0, (size_t)(align - len));

	/* �����å������׻����롣*/
	if (in_cksum(icmp4h, align) != 0) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		goto buf_rel;
		}

	/* ��å������η��ˤ��ʬ�����롣*/
	switch (icmp4h->type) {
	case ICMP4_ECHO_REQUEST:
		icmp_echo(input, *offp);
		return IPPROTO_DONE;
		break;
	case ICMP4_ECHO_REPLY:

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

		icmp_echo_reply(input, *offp);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

		break;
	case ICMP4_UNREACH:
		icmp_unreach(input, *offp);
		break;
	case ICMP4_REDIRECT:

#if NUM_REDIRECT_ROUTE_ENTRY > 0

		addr = ntohl(icmp4h->data.addr);
		syslog(LOG_INFO, "[ICMP] redirect, addr: %s.", ip2str(NULL, &addr));
		icmp_redirect(input, *offp);

#else	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		addr = ntohl(icmp4h->data.addr);
		syslog(LOG_INFO, "[ICMP] redirect ignored, addr: %s.", ip2str(NULL, &addr));

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		break;
	default:
		syslog(LOG_INFO, "[ICMP] unknown type: %d.", icmp4h->type);
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		break;
		}

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#ifdef ICMP_REPLY_ERROR

/*
 *  icmp_error -- ICMP ���顼�����ؿ���
 *
 *    input �ˤ� IF �إå��� IP �إå���ޤޤ�Ƥ��롣
 *    icmp_error �Ǥϡ��ͥåȥ���Хåե� input ���ֵѤ��ʤ��Τǡ�
 *    �ƽФ�¦�ǡ��������Ƥ��齪λ���롣	
 */

void
icmp_error (uint8_t code, T_NET_BUF *input)
{
	T_IP4_HDR	*ip4h;
	T_ICMP4_HDR	*icmp4h;
	T_NET_BUF	*output;
	uint_t		len, ip4hl, align;

	ip4h  = GET_IP4_HDR(input);
	ip4hl = GET_IP4_HDR_SIZE(ip4h);

	/* �����Ѥ� IP �ǡ���������������롣*/
	if (input->len - ip4hl < 8)
		len = input->len - ip4hl;
	else
		len = 8;
	
	if (in4_get_datagram(&output, (uint_t)(ICMP4_HDR_SIZE + ip4hl + len), 0,
	                     &ip4h->src, NULL, IPPROTO_ICMP, IP4_DEFTTL, 
	                     NBA_SEARCH_ASCENT, TMO_ICMP_OUTPUT) != E_OK)
		return;

	/* ICMP �إå������ꤹ�롣*/
	icmp4h		= GET_ICMP4_HDR(output, IF_IP4_ICMP4_HDR_OFFSET);
	icmp4h->type	= ICMP4_UNREACH;
	icmp4h->code	= code;
	icmp4h->data.addr= 0;

	/* ���顼��ȯ������ IP �إå��� �ǡ��� 8 �����ƥåȤ򥳥ԡ����롣*/
	memcpy(GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET),
	       GET_IP4_HDR(input), (size_t)(ip4hl + len));

	/* 4 �����ƥåȶ����Υǡ���Ĺ */
	align = (len + 3) >> 2 << 2;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset((uint8_t*)GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET) + ip4hl + len,
		       0, (size_t)(align - len));

	/* �����å������׻����롣*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h, (uint_t)(ICMP4_HDR_SIZE + ip4hl + align));

	/* �������롣*/
	NET_COUNT_ICMP4(net_count_icmp4.out_octets,
	               output->len - GET_IF_IP4_HDR_SIZE(output));
	NET_COUNT_ICMP4(net_count_icmp4.out_packets, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutDestUnreachs, 1);
	ip_output(output, TMO_ICMP_OUTPUT);
	}

#endif	/* of #ifdef ICMP_REPLY_ERROR */
