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
 *  @(#) $Id: if_loop.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)if_loop.c	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_loop.c,v 1.37.2.1 1999/08/29 16:28:19 peter Exp $
 */

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <net/if_var.h>
#include <net/if6_var.h>

#ifdef SUPPORT_LOOP

/*
 *  ������롼�ץХå����󥿥ե�����
 */

/*
 *  �����ؿ������
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ѿ�
 */

/* �ͥåȥ�����󥿥ե�������¤�� */

#if defined(SUPPORT_INET4)

static T_IFNET loop_ifnet = {
	NULL,			/* �ͥåȥ�����󥿥ե������Υ��եȥ���������	*/
	{
		IPV4_ADDR_LOOPBACK,		/* IPv4 ���ɥ쥹			*/
		IPV4_ADDR_LOOPBACK_MASK,	/* ���֥ͥåȥޥ���			*/
		},
	};

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

static T_IFNET loop_ifnet = {
	NULL,			/* �ͥåȥ�����󥿥ե������Υ��եȥ���������	*/
	{},			/* IPv6 ���ɥ쥹����				*/
	{},			/* �ޥ�����㥹�� IPv6 ���ɥ쥹			*/
	};

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  loop_get_ifnet -- �ͥåȥ�����󥿥ե�������¤�Τ��֤���
 */

T_IFNET *
loop_get_ifnet (void)
{
	return &loop_ifnet;
	}

/*
 *  looutput -- ������롼�ץХå����󥿥ե������ν��ϴؿ�
 */

ER
looutput (T_NET_BUF *output, TMO tmout)
{
	ER error;

	NET_COUNT_LOOP(net_count_loop.out_octets,  output->len);
	NET_COUNT_LOOP(net_count_loop.out_packets, 1);

	if ((error = tsnd_dtq(DTQ_LOOP_OUTPUT, output, tmout)) != E_OK)
		syslog(LOG_NOTICE, "[LOOP] drop error: %s", itron_strerror(error));
	return error;
	}

/*
 *  ������롼�ץХå����󥿥ե����������ϥ�����
 */

void
if_loop_output_task (intptr_t exinf)
{
	T_NET_BUF	*output;
	ER		error;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[LOOP OUTPUT:%d] started.", tskid);
	while (true) {
		if (rcv_dtq(DTQ_LOOP_OUTPUT, (intptr_t*)&output) == E_OK) {
			NET_COUNT_LOOP(net_count_loop.in_octets,  output->len);
			NET_COUNT_LOOP(net_count_loop.in_packets, 1);
			if ((error = snd_dtq(DTQ_LOOP_INPUT, output)) != E_OK)
				syslog(LOG_NOTICE, "[LOOP OUTPUT] drop error: %s", itron_strerror(error));
			}
		}
	}

/*
 *  ������롼�ץХå����󥿥ե����������ϥ�����
 */

void
if_loop_input_task (intptr_t exinf)
{
	T_NET_BUF	*input;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[LOOP INPUT:%d] started.", tskid);
	while (true) {
		if (rcv_dtq(DTQ_LOOP_INPUT, (intptr_t)&input) == E_OK) {
			NET_COUNT_LOOP(net_count_loop.in_octets,  input->len);
			NET_COUNT_LOOP(net_count_loop.in_packets, 1);

#if defined(SUPPORT_INET4)

			/* IPv4 ���ϴؿ���ƤӽФ� */
			if (IP4_VHL_V(GET_IP4_HDR(input)->vhl) == IPV4_VERSION)
				ip_input(input);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

			/* IPv6 ���ϴؿ���ƤӽФ� */
			if (IP6_VCF_V(ntohl(GET_IP6_HDR(input)->vcf)) == IPV6_VERSION)
				ip6_input(input);

#endif	/* of #if defined(SUPPORT_INET6) */

			}
		}
	}

#endif	/* of #ifdef SUPPORT_LOOP */
