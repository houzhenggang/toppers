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
 *  @(#) $Id: udp_output.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1995
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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/icmp6.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#ifdef SUPPORT_UDP

#ifdef UDP_CFG_NON_BLOCKING

/*
 *  �ؿ�
 */

static void udp_output (T_UDP_CEP *cep);

/*
 *  UDP ���ϥ�����
 *  �Υ�֥�å��󥰥�������Ȥ߹�����Ȥ����Ѥ��롣
 */

static void
udp_output (T_UDP_CEP *cep)
{
	T_NET_BUF	*output;
	T_UDP_HDR	*udph;
	ER_UINT		error;

#ifdef UDP_CFG_OUT_CHECKSUM
	uint16_t	sum;
#endif	/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* IP �ǡ��������������Ƥ롣*/
	if ((error = IN_GET_DATAGRAM(&output, (uint_t)(UDP_HDR_SIZE + cep->snd_len), 0,
	                             &cep->snd_p_dstaddr->ipaddr,
	                             &cep->myaddr.ipaddr,
	                             IPPROTO_UDP, IP_DEFTTL, 
	                             NBA_SEARCH_ASCENT, TMO_UDP_OUTPUT)) != E_OK) {
		goto err_ret;
		}

	/* UDP �إå��˾�������ꤹ�롣*/
	udph		= GET_UDP_HDR(output, IF_IP_UDP_HDR_OFFSET);
	udph->sport	= htons(cep->myaddr.portno);
	udph->dport	= htons(cep->snd_p_dstaddr->portno);
	udph->ulen	= htons(UDP_HDR_SIZE + cep->snd_len);
	udph->sum	= 0;

	/* �ǡ����򥳥ԡ����롣*/
	memcpy((void*)GET_UDP_SDU(output, IF_IP_UDP_HDR_OFFSET),
	       cep->snd_data, (size_t)cep->snd_len);

#ifdef UDP_CFG_OUT_CHECKSUM

	sum = IN_CKSUM(output, IPPROTO_UDP, IF_IP_UDP_HDR_OFFSET,
	               (uint_t)(UDP_HDR_SIZE + cep->snd_len));

	/* �׻����������å�������ͤ� 0 �ʤ� 0xffff ������롣*/
	if (sum == 0)
		sum = UINT_C(0xffff);
	udph->sum = sum;

#endif/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* �ͥåȥ���Хåե�Ĺ��Ĵ�����롣*/
	output->len = (uint16_t)(IF_IP_UDP_HDR_SIZE + cep->snd_len);

	/* �ͥåȥ���� (IP) �ν��ϴؿ���ƤӽФ���*/
	if ((error = IP_OUTPUT(output, TMO_UDP_OUTPUT)) != E_OK)
		goto err_ret;


	NET_COUNT_MIB(udp_stats.udpOutDatagrams, 1);

	if (IS_PTR_DEFINED(cep->callback)) {

		if (error == E_OK)
			error = cep->snd_len;

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;

err_ret:
	NET_COUNT_UDP(net_count_udp.out_err_packets, 1);
	if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)E_NOMEM);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		error = E_NOMEM;
		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;
	}

/*
 *  UDP ���ϥ�����
 *  �Υ�֥�å��󥰥�������Ȥ߹�����Ȥ����Ѥ��롣
 */

void
udp_output_task (intptr_t exinf)
{
	ID	tskid;
	int_t	ix;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP OUTPUT:%d] started.", tskid);


#if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP)

	/* IPv6 �Υ��ơ��ȥ쥹�����ɥ쥹��ư�����¹Ԥ��롣*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP) */

	while (true) {

		/* ���Ϥ��ݥ��Ȥ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_UDP_POST_OUTPUT));

		for (ix = tmax_udp_ccepid; ix -- > 0; ) {

			if (udp_cep[ix].flags & UDP_CEP_FLG_POST_OUTPUT) {
				udp_cep[ix].flags &= ~UDP_CEP_FLG_POST_OUTPUT;
				udp_output(&udp_cep[ix]);
				}
			}
		}
	}

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
