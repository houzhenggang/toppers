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
 *  @(#) $Id: tcp_output.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *
 *	@(#)tcp_output.c	8.4 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_output.c,v 1.32.2.2 1999/08/29 16:29:55 peter Exp $
 */

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
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#ifdef SUPPORT_TCP

/*
 *  �ؿ�
 */

static ER send_segment (bool_t *sendalot, T_TCP_CEP *cep, uint_t doff, uint_t win, uint_t len, uint8_t flags);
static void tcp_output (T_TCP_CEP *cep);

/*
 *  �ѿ�
 */

/* ���ϻ��Υե饰�� FSM ���֤ˤ�����򤹤뤿���ɽ */

const static uint8_t tcp_outflags[] = {
	TCP_FLG_RST | TCP_FLG_ACK,	/*  0, ������				*/
	0,				/*  1, ��ư�����ץ�			*/
	TCP_FLG_SYN,			/*  2, ǽư�����ץ�SYN �����Ѥ�	*/
	TCP_FLG_SYN | TCP_FLG_ACK,	/*  3, SYM ���������SYN �����Ѥ�	*/
	TCP_FLG_ACK,			/*  4, ���ͥ�������ߴ�λ		*/
	TCP_FLG_ACK,			/*  5, FIN �������������Ԥ�		*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  6, ��λ���ơ�FIN �����Ѥ�		*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  7, ��λ��FIN �򴹺Ѥߡ�ACK �Ԥ�	*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  8, FIN ��������λ��ACK �Ԥ�		*/
	TCP_FLG_ACK,			/*  9, ��λ��FIN ��ã��ǧ������FIN�Ԥ�	*/
	TCP_FLG_ACK,			/* 10, ��λ�������Ԥ�			*/
	};

/*
 *  send_segment -- TCP ���Ͻ���
 */

static ER
send_segment (bool_t *sendalot, T_TCP_CEP *cep, uint_t doff, uint_t win, uint_t len, uint8_t flags)
{
	T_NET_BUF	*output;
	T_TCP_HDR	*tcph;
	uint_t		optlen;
	ER		error;

#ifdef TCP_CFG_OPT_MSS

	uint8_t		*optp;

	if (flags & TCP_FLG_SYN)
		optlen = TCP_OPT_LEN_MAXSEG;
	else
		optlen = 0;

#else/* of #ifdef TCP_CFG_OPT_MSS */

	optlen = 0;

#endif/* of #ifdef TCP_CFG_OPT_MSS */

	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpOutSegs, 1);

	/*
	 *  ��������Ĺ�����κ��������������Ĺ��Ĵ�����롣
	 *  �⤷��Ķ���Ƥ�����ϡ�Ķ����ʬ�����������롣
	 *  ���Τ��ᡢFIN �ӥåȤ򥯥ꥢ���롣
	 *
	 *  ���ꥸ�ʥ�Ǥϡ�t_maxopd ������Ĺ�ˤ��Ƥ��뤬��
	 *  �ܼ����Ǥϡ����κ�������������Ȥˤ��롣
	 */
	if (len + optlen > cep->maxseg) {
		flags &= ~TCP_FLG_FIN;
		len = cep->maxseg - optlen;
		*sendalot = true;
		}

	/*
	 *  �����Хåե������ˤʤ�Ȥ��� PUSH �ե饰�����ꤹ�롣
	 */
	if (len && doff + len >= cep->swbuf_count)
		flags |= TCP_FLG_PUSH;

#if defined(TCP_CFG_SWBUF_CSAVE_ONLY)
		
	if (len > 0 && ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY ||
	                (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT)) {

		/*
		 *  ����������ɥХåե�����������ʤ��褦�ˤ��ơ�
		 *  �ͥåȥ���Хåե�����Ϥ˰ܤ���
		 */
		cep->swbufq->flags |= NB_FLG_NOREL_IFOUT;
		output = cep->swbufq; 
		}
	else {

		/*
		 *  ACK ��λ���֤ǡ����δؿ����ƤӽФ���뤳�Ȥ⤢�롣
		 *  ���λ��ϡ�len �� 0 �ˤ��ơ��������³���롣
		 */
		len = 0;
		if ((error = tcp_get_segment(&output, cep, optlen,
	                                    len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                                    NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}

#elif defined(TCP_CFG_SWBUF_CSAVE)	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	if (IS_PTR_DEFINED(cep->sbuf)) {
		if ((error = tcp_get_segment(&output, cep, optlen,
		                             len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
		                             NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}
	else if (len > 0 && ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY ||
	                     (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT)) {

		/*
		 *  ����������ɥХåե�����������ʤ��褦�ˤ��ơ�
		 *  �ͥåȥ���Хåե�����Ϥ˰ܤ���
		 */
		cep->swbufq->flags |= NB_FLG_NOREL_IFOUT;
		output = cep->swbufq; 
		}
	else {

		/*
		 *  ACK ��λ���֤ǡ����δؿ����ƤӽФ���뤳�Ȥ⤢�롣
		 *  ���λ��ϡ�len �� 0 �ˤ��ơ��������³���롣
		 */
		len = 0;
		if ((error = tcp_get_segment(&output, cep, optlen,
	                                    len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                                    NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}

#else	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	if ((error = tcp_get_segment(&output, cep, optlen,
	                             len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                             NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
		if (cep->timer[TCP_TIM_REXMT] == 0)
			cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
		goto err_ret;
		}

#endif	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	/*
	 *  TCP ���ץ����������Ԥ���
	 *  �ܼ����Ǥϡ����祻�����ȥ������Τ����ꤹ�롣
	 */
	if (flags & TCP_FLG_SYN) {
		cep->snd_nxt = cep->iss;

#ifdef TCP_CFG_OPT_MSS

		optp = GET_TCP_OPT(output, IF_IP_TCP_HDR_OFFSET);
		*optp ++ = TCP_OPT_MAXSEG;
		*optp ++ = TCP_OPT_LEN_MAXSEG;
		*(uint16_t*)optp = htons(DEF_TCP_RCV_SEG);

#endif/* of #ifdef TCP_CFG_OPT_MSS */

		}

	/* TCP SDU �������ǡ����򥳥ԡ����롣*/

	if (len > 0) {
		if (SEQ_LT(cep->snd_nxt, cep->snd_max)) {
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_REXMIT_SEGS], 1);
			NET_COUNT_MIB(tcp_stats.tcpRetransSegs, 1);
			}
		TCP_READ_SWBUF(cep, output, len, doff);
		}
	else {
		if (cep->flags & TCP_CEP_FLG_ACK_NOW)
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_ACKS], 1);
		if (flags & (TCP_FLG_FIN | TCP_FLG_SYN | TCP_FLG_RST))
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_CNTL_SEGS],  1);


#ifdef TCP_CFG_EXTENTIONS

		if (SEQ_LT(cep->snd_up, cep->snd_una))
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_URG_SEGS], 1);

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		}

	/*
	 * snd_max: ������������ SEQ
	 * snd_nxt: ������������ SEQ
	 *
	 *  ��꤫�� FIN ����������ޤ� FIN ���������Ƥ��ʤ�����
	 *  ����ǡ������ʤ��Ȥ��ϡ�FIN �������Ϥ��뤿�ᡢ
	 *  �������Ȥ��������뤬��SEQ �Ͽʤ�ʤ���
	 */
	if ((flags & TCP_FLG_FIN) && (cep->flags & TCP_CEP_FLG_SENT_FIN) &&
	    cep->snd_nxt == cep->snd_max) {
		cep->snd_nxt --;
		}

	tcph = GET_TCP_HDR(output, IF_IP_TCP_HDR_OFFSET);

	/*
	 *  SEQ��ACK���ե饰�����ꡣ
	 */
	if (len > 0 || (flags & (TCP_FLG_SYN | TCP_FLG_FIN)) || cep->timer[TCP_TIM_PERSIST] != 0)
		tcph->seq = htonl(cep->snd_nxt);
	else
		tcph->seq = htonl(cep->snd_max);

	/*
	 *  rcv_nxt: ��������Ԥ��Ƥ���Ǿ��� SEQ
	 */
	tcph->ack   = htonl(cep->rcv_nxt);
	tcph->flags = flags;

	/*
	 *  ����������ɤη׻�
	 *
	 *  rbufsz: �����ѥХåե�������
	 *  maxseg: ���κ�������������ȥ�����	
	 */
	if (win < (cep->rbufsz / 4) && win < cep->maxseg)
		win = 0;

	/*
	 *  rcv_nxt: ��������Ԥ��Ƥ���Ǿ��� SEQ
	 *  rcv_adv: ��������Ԥ��Ƥ������� SEQ
	 */
	if ((int32_t)win < (int32_t)(cep->rcv_adv - cep->rcv_nxt))
		win = (uint_t)(cep->rcv_adv - cep->rcv_nxt);

	tcph->win = htons(win);

#ifdef TCP_CFG_EXTENTIONS

	/*
	 *  �۵ޥݥ��󥿤�����
	 */
	if (SEQ_GT(cep->snd_up, cep->snd_nxt)) {
		if (TCP_CFG_URG_OFFSET)
			tcph->urp    = htons((uint16_t)(cep->snd_up - cep->snd_nxt));
		else
			tcph->urp    = htons((uint16_t)(cep->snd_up - cep->snd_nxt - 1));
		tcph->flags |= TCP_FLG_URG;
		}
	else
		cep->snd_up  = cep->snd_una;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/*
	 *  �����å���������ꤹ�롣
	 */
	tcph->sum = 0;
	tcph->sum = IN_CKSUM(output, IPPROTO_TCP, (uint_t)GET_TCP_HDR_OFFSET(output),
		             GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len);

	/* �ͥåȥ���Хåե�Ĺ��Ĵ�����롣*/
	output->len = (uint16_t)(GET_IF_IP_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len);

	/*
	 *  �����ޤ�Ĵ��
	 */
	if ((cep->flags & TCP_CEP_FLG_FORCE) == 0 || cep->timer[TCP_TIM_PERSIST] == 0) {
		T_TCP_SEQ startseq = cep->snd_nxt;

		/*
		 *  ������������ SEQ (snd_nxt) �򺣲���������ǡ�����ʬ�ʤ�롣
		 */
		if (flags & TCP_FLG_SYN)
			cep->snd_nxt ++;
		if (flags & TCP_FLG_FIN) {
			cep->flags |= TCP_CEP_FLG_SENT_FIN;
			cep->snd_nxt ++;
			}

		cep->snd_nxt += len;

		/*
		 *  ������������ SEQ (snd_nxt) ��
		 *  ������������ SEQ (snd_max) ���ʤ�Ǥ���С�
		 *  ������������ SEQ (snd_max) �򹹿����롣
		 */
		if (SEQ_GT(cep->snd_nxt, cep->snd_max)) {
			cep->snd_max = cep->snd_nxt;
			/*
			 *  �⤷���������ַ�¬��ԤäƤ��ʤ���С�
			 *  ���������˻��֤��碌�롣
			 */
			if (cep->rtt == 0) {
				cep->rtt   = 1;
				cep->rtseq = startseq;	/* �������� cep->snd_nxt */
				}
			}

		/*
		 *  �⤷���ꤵ��Ƥ��ʤ�����ACK �ޤ�����α��ȯ�����Ƥ��ʤ���С�
		 *  ���������ޤ����ꤹ�롣���ꤹ�����ͤϡ�
		 * �ֳ�餫�ʱ������� + 2 �� ����������ư�פǤ��롣
		 *  �������֤ΥХå����դ˻Ȥ��륷�եȥ�����Ȥ��������롣
		 */
		if (cep->timer[TCP_TIM_REXMT] == 0 && cep->snd_nxt != cep->snd_una) {
			cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			if (cep->timer[TCP_TIM_PERSIST] != 0) {
				cep->timer[TCP_TIM_PERSIST] = 0;
				cep->rxtshift = 0;
				}
			}
		}

	/*
	 *  ������������ SEQ (snd_nxt) + ������������ǡ����� (len) ��
	 *  ������������ SEQ (snd_max) ���ʤ�Ǥ���С�
	 *  ������������ SEQ (snd_max) �򹹿����롣
	 */
	else if (SEQ_GT(cep->snd_nxt + len, cep->snd_max))
		cep->snd_max = cep->snd_nxt + len;

#ifdef TCP_CFG_SWBUF_CSAVE

	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY)
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SENT;

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#ifdef TCP_CFG_TRACE

	tcp_output_trace(output, cep);

#endif	/* of #ifdef TCP_CFG_TRACE */

	/* �ͥåȥ���� (IP) �ν��ϴؿ���ƤӽФ���*/
	if ((error = IP_OUTPUT(output, TMO_TCP_OUTPUT)) != E_OK)
		goto err_ret;

	/*
	 *  ����������������ɥ������� (win) �� 0 �ʾ�ǡ�
	 *  ��������Ԥ��Ƥ���Ǿ��� SEQ (rcv_nxt) + win ��
	 *  ��������Ԥ��Ƥ������� SEQ (rcv_adv) ���ʤ�Ǥ����
	 *  ��������Ԥ��Ƥ������� SEQ �򹹿����롣
	 */
	if (win > 0 && SEQ_GT(cep->rcv_nxt + win, cep->rcv_adv)) {
		cep->rcv_adv = cep->rcv_nxt + win;
		}

	/*
	 *  �Ǹ���������� ACK (last_ack_sent) �򹹿����롣
	 */
	cep->last_ack_sent = cep->rcv_nxt;

	/*
	 *  �ե饰�������Ԥ���
	 */
	cep->flags &= ~(TCP_CEP_FLG_ACK_NOW | TCP_CEP_FLG_DEL_ACK);
	if (cep->flags & TCP_CEP_FLG_FORCE_CLEAR)
		cep->flags &= ~(TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR);

	return E_OK;

err_ret:
	/*
	 * �ʲ��˴ط����ʤ��ե饰�򥯥ꥢ�����롣
	 * ��������������ɥХåե��ξʥ��ԡ���ǽ
	 * ��ưŪ���̿�ü���������������ǽ
	 */
	cep->flags &= (TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK | 
	               TCP_CEP_FLG_DYNAMIC       | TCP_CEP_FLG_VALID);

	return error;
	}

/*
 *  tcp_output -- TCP ���Ͻ���
 */

void
tcp_output (T_TCP_CEP *cep)
{
	bool_t	sendalot = true, idle;
	ER	error = E_OK;
	int32_t	len;
	uint_t	doff, win;
	uint8_t	flags;

	/*
	 *  snd_una: ̤��ǧ�κǾ����� SEQ	 �ޤ��ϡ���ǧ���줿�������� SEQ
	 *  snd_max: ������������ SEQ
	 */
	idle = (cep->snd_max == cep->snd_una);

	/*
	 *  idle:   �����ɥ����
	 *  rxtcur: ���ߤκ��������ॢ����
	 */
	if (idle && cep->idle >= cep->rxtcur)

		/*
		 *  snd_cwnd: ���ԥ�����ɥ�����
		 *  maxseg  : ���κ�������������ȥ�����
		 *
		 *  Ĺ���֥����ɥ���ä��Τǥ�������������������ꤹ�롣
		 */
		cep->snd_cwnd = cep->maxseg;

	while (error == E_OK && sendalot) {
		sendalot = false;

		/*
		 *  snd_nxt: ������������ SEQ�����λ����Ǥϡ������������� SEQ
		 *  snd_una: ̤��ǧ�κǾ����� SEQ���ޤ��ϳ�ǧ���줿�������� SEQ
		 *
		 *  doff: �����򳫻Ϥ��륪�ե��åȡ�
		 *                                    swbuf_count (�����Хåե��ˤ��륪���ƥåȿ�)
		 *    0                               V
		 *    +-------------------------------------------+
		 *    |                    sbuf                   |
		 *    +-------------------------------------------+
		 *    ^               ^
		 *    |<------------->snd_nxt (������������ SEQ)
		 *    |       doff
		 *    snd_una (�ޤ���ǧ����Ƥ��ʤ�)
		 */
		doff = (uint_t)(cep->snd_nxt - cep->snd_una);

		/*
		 *  snd_wnd:  ���μ�����ǽ������ɥ�����
		 *  snd_cwnd: ���ԥ�����ɥ�����
		 *
		 *  win: �ɤ��餫������������ɥ����������ꤹ�롣
		 */
		win   = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;
	
		/* ���ϥե饰������ */
		flags = tcp_outflags[cep->fsm_state];
		if (cep->flags & TCP_CEP_FLG_NEED_FIN)
			flags |= TCP_FLG_FIN;
		if (cep->flags & TCP_CEP_FLG_NEED_SYN)
			flags |= TCP_FLG_SYN;
		if (cep->flags & TCP_CEP_FLG_FORCE) {

			/*
			 *  �⤷������������ɥ����� (win) �� 0 �ʤ� 1 �����ƥå��������롣
			 *  �����Ǥʤ���С���³�����ॢ���Ȥ򥭥�󥻥뤷��
			 *  ��������� (rxtshift) �� 0 �ˤ��롣
			 */
			if (win == 0) {

				/*
				 *  doff:        �������륪���ƥåȿ���
				 *  swbuf_count: �����Хåե��λ����極����
				 *
				 *  �����Хåե��˻ĤäƤ��륪���ƥåȤ������줫��
				 *  �������褦�Ȥ��Ƥ��륪���ƥåȿ����¿�����
				 *  FIN �ե饰�򥯥ꥢ���롣
				 */
				if (doff < cep->swbuf_count)
					flags &=~TCP_FLG_FIN;
				win = 1;
				}
			else {
				/*
				 *  TCP_TIM_PERSIST: ��³������
				 *  rxtshift:        ����������� log(2)
				 */
				cep->timer[TCP_TIM_PERSIST] = 0;
				cep->rxtshift = 0;
				}
		 	}

		/*
		 *  len: �����������륪���ƥåȿ�
		 *        swbuf_count (�����Хåե��ˤ��륪���ƥåȿ�)
		 *                                    |
		 *    0                               V
		 *    +-------------------------------------------+
		 *    |                    sbuf       |           |
		 *    +-------------------------------------------+
		 *    ^               ^<------------->
		 *    |               |      len
		 *    |<------------->snd_nxt (������������ SEQ)
		 *    |       doff
		 *    snd_una (�ޤ���ǧ����Ƥ��ʤ�)
		 */
		if (cep->swbuf_count < win)
			len = (int32_t)cep->swbuf_count - doff;
		else
			len = (int32_t)win - doff;

		/*
		 *  ���Ǥ���������Ƥ���С�SYN �ӥåȤ򥪥դ��롣
		 *  ���������ʲ��ξ��Ǥ������򹵤��롣
		 *
		 *    �����֤� SYN ������
		 *    ���������Ȥ��ǡ�����ޤ�Ǥ��롣
		 */
		if ((flags & TCP_FLG_SYN) && SEQ_GT(cep->snd_nxt, cep->snd_una)) {
			flags &= ~TCP_FLG_SYN;
			doff --;		/* -1 �� SYN �ե饰ʬ */
			len ++;			/* +1 �� SYN �ե饰ʬ */
			if (len > 0 && cep->fsm_state == TCP_FSM_SYN_SENT)
				break;
			}

		if (flags & TCP_FLG_SYN) {
			len = 0;
			flags &= ~TCP_FLG_FIN;
			}

		if (len < 0) {

			/*
			 *  len �� 0 �ʲ��ʤ顢0 �����ꤹ�롣
			 *  �⤷������������ɥ��������� 0 �ʤ顢
			 *  �����������ޤ򥭥�󥻥뤷��
			 *  ������������ SEQ (snd_nxt) ��
			 *  ��ǧ���줿�������� SEQ (snd_una) ���᤹��
			 *  �����ơ���³�����ޡ����ߤޤäƤ���С������ꤹ�롣
			 */
			len = 0;
			if (win == 0) {
				cep->timer[TCP_TIM_REXMT] = 0;
				cep->rxtshift = 0;
				cep->snd_nxt  = cep->snd_una;
				if (cep->timer[TCP_TIM_PERSIST] == 0)
					tcp_set_persist_timer(cep);
				}
			}


		/*
		 *  �����������륪���ƥåȿ� (len) �ϡ�
		 *  ���κ�������������ȥ����� (maxseg) ��Ķ���ʤ��褦�ˤ��롣
		 */
		if (len > cep->maxseg) {
			len = cep->maxseg;
			sendalot = true;
			}

		/*
                 *        swbuf_count (�����Хåե��ˤ��륪���ƥåȿ�)
                 *                                           |
		 *    0                                      V
		 *    +-------------------------------------------+
		 *    |                    sbuf       |           |
		 *    +-------------------------------------------+
		 *    ^               ^<------------->
		 *    |               |      len
		 *    |<------------->snd_nxt (������������ SEQ)
		 *    |       doff
		 *    snd_una (�ޤ���ǧ����Ƥ��ʤ�)
		 *
		 *  ����������⡢�����Хåե��˥ǡ������ĤäƤ����
		 *  FIN �ե饰�򥯥ꥢ���롣
		 */
		if (SEQ_LT(cep->snd_nxt + len, cep->snd_una + cep->swbuf_count))
			flags &= ~TCP_FLG_FIN;

		/*
		 *  �������� win �ϡ�����������ɥ���������
		 *  �����Хåե��ζ�������
		 */
		win = cep->rbufsz - cep->rwbuf_count;

		/*
		 *  �򤫤ʥ�����ɥ�������ɥ���β������ (����¦)
		 *
		 *  �ʲ��ξ��ǡ�������Ԥ���
		 *
		 *    ���ե륵���� (maxseg) �Υ������Ȥ����뤳�Ȥ��Ǥ��롣
		 *    �����κ���μ���������ɥ��������� 1/2 �Υǡ�����
		 *      ���뤳�Ȥ��Ǥ��롣
		 *    �������Хåե�����ˤǤ��������ɥ뤫���ٱ䥪�ץ����ͭ���ʤȤ���
		 */
		if (len) {

			/*
			 *  �����������륪���ƥåȿ� (len) ��
			 *  ���κ�������������ȥ����� (maxseg) ��
			 *  ���פ���Ȥ����������롣
			 */
			if (len == cep->maxseg) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}

			/*
			 *  ����������ǡ������Хåե�����ˤǤ���
			 *  �����ɥ뤫�� PUSH ���ץ����ͭ���ʤȤ���
			 */
			if ((idle || (cep->flags & TCP_CEP_FLG_NO_DELAY)) &&
			    (cep->flags & TCP_CEP_FLG_NO_PUSH) == 0 &&
			    len + doff >= cep->swbuf_count) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}

			/*
			 *  max_sndwnd: ���ޤǤκ�������������ɥ�����
			 *  snd_nxt:    ������������ SEQ
			 *  snd_max:    ������������ SEQ
			 *
			 *  ���ξ��Ǥ�������Ԥ���
			 *
			 *    �����������ե饰�����åȤ���Ƥ��롣
			 *    ���ǡ���Ĺ�����κ���μ���������ɥ��������� 1/2 �ʾ�ǡ�
			 *      ���κ���μ���������ɥ��������� 0 ����礭����
			 *    �������������� SEQ �������������� SEQ ��꾮������
			 *      �Ĥޤꡢ��������Ȥ���
			 */
			if ((cep->flags & TCP_CEP_FLG_FORCE) ||
			    (len >= cep->max_sndwnd / 2 && cep->max_sndwnd > 0) ||
			    SEQ_LT(cep->snd_nxt, cep->snd_max)) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}
			}


		/*
		 *  �򤫤ʥ�����ɥ�������ɥ���β������ (����¦)
		 *
		 *  ������ɥ����������ե륵������ 2 �ܤΥ������ȡ����뤤��
		 *  �����Хåե����̤� 1/2 �Ρ������줫�������ۤ���
		 *  �����������ä������ϡ�������ɥ��������ι�����Ԥ���
		 */
		if (win > 0) {
			long adv;

			/*
			 *  win:              �����Хåե��ζ�������
			 *  MAX_TCP_WIN_SIZE: TCP �إå��� win �ե�����ɤ�����Ǥ��������
			 *  rcv_adv:          ��������Ԥ��Ƥ������� SEQ
			 *  rcv_nxt:          ��������Ԥ��Ƥ���Ǿ��� SEQ
			 */
			if (win < MAX_TCP_WIN_SIZE)
				adv = win - (cep->rcv_adv - cep->rcv_nxt);
			else
				adv = MAX_TCP_WIN_SIZE - (cep->rcv_adv - cep->rcv_nxt);

			if (adv     >= (long)(cep->maxseg * 2) ||
			    adv * 2 >= (long) cep->rbufsz) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}
			}
	
		/*
		 *  ACK ���������롣
		 */
		if (cep->flags & TCP_CEP_FLG_ACK_NOW) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

		if ( (flags & TCP_FLG_RST) ||
		    ((flags & TCP_FLG_SYN) && (cep->flags & TCP_CEP_FLG_NEED_SYN) == 0)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

#ifdef TCP_CFG_EXTENTIONS

		if (SEQ_GT(cep->snd_up, cep->snd_una)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		/*
		 *  snd_nxt: ������������ SEQ
		 *  snd_una: ̤��ǧ�κǾ����� SEQ���ޤ��ϳ�ǧ���줿�������� SEQ
		 *
		 *  ��꤫�� FIN ����������ޤ� FIN ���������Ƥ��ʤ�����
		 *  ����ǡ������ʤ��Ȥ��ϡ�FIN �������Ϥ��뤿�ᡢ
		 *  �������Ȥ��������롣
		 */
		if ((flags & TCP_FLG_FIN) &&
		    ((cep->flags & TCP_CEP_FLG_SENT_FIN) == 0 || cep->snd_nxt == cep->snd_una)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

		/*
		 *  �������٤��ǡ��������ꡢ���������ޤȻ�³�����ޤ��ڤ�Ƥ���Ȥ���
		 *  ��³�����ޤ����ꤹ�롣
		 */
		if (cep->swbuf_count && cep->timer[TCP_TIM_REXMT  ] == 0 &&
		                        cep->timer[TCP_TIM_PERSIST] == 0) {
			cep->rxtshift = 0;
			tcp_set_persist_timer(cep);
			break;
			}
		
		}
	}

#ifdef TCP_CFG_SWBUF_CSAVE

/*
 *  tcptsk_alloc_swbufq -- ����������ɥХåե��������
 */

static void
tcptsk_alloc_swbufq (T_TCP_CEP *cep)
{
 	ER	error;
	uint_t	win;

	/*
	 *  snd_wnd:  ���μ�����ǽ������ɥ�����
	 *  snd_cwnd: ���ԥ�����ɥ�����
	 *
	 *  win: �ɤ��餫������������ɥ����������ꤹ�롣
	 */
	win = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;

	/*
	 *  ���μ���������ɤ��Ĥ��Ƥ�����ϡ������ޤ��Ե����롣
	 */
	if (win == 0) {
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_WOPEN_PEND;
		}
	else {

#ifdef TCP_CFG_NON_BLOCKING

		/* �Υ�֥�å��󥰥����� */
		if (!IS_PTR_DEFINED(cep->callback)) {
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
			cep->snd_tskid = TA_NULL;
			cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			return;
			}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if ((error = tcp_get_segment(&cep->swbufq, cep, 0,
		                             (uint_t) TCP_CFG_SWBUF_CSAVE_MIN_SIZE,
		                             (uint_t)(TCP_CFG_SWBUF_CSAVE_MAX_SIZE - IF_IP_TCP_HDR_SIZE),
		                             (ATR)(NBA_SEARCH_DESCENT |
		                                   NBA_RESERVE_TCP    |
		                                   (GET_TCP_CEPID(cep) & NBA_ID_MASK)), TMO_POL)) != E_OK) {

			/* �ͥåȥ���Хåե���ͽ�󤹤롣*/
			cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_NBUF_PEND;
			}
		else {

			/* ����������ɥХåե����������롣*/
			tcp_init_swbuf(cep);

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->snd_nblk_tfn == TFN_TCP_GET_BUF) {

				uint_t len;

				/* ����������ɥХåե��ν񤭹��ߥ��ɥ쥹�����ꤹ�롣*/
				len = TCP_GET_SWBUF_ADDR(cep, cep->snd_p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */


				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

			else {	/* cep->snd_nblk_tfn == TFN_TCP_SND_DAT || */
				/* cep->snd_nblk_tfn == TFN_TCP_SND_OOB    */

				uint_t len;

				/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
				len = TCP_WRITE_SWBUF(cep, cep->snd_data, (uint_t)cep->snd_len);

#ifdef TCP_CFG_EXTENTIONS

				/* �����۵ޥݥ��󥿤����ꤹ�롣*/
			        if (cep->snd_nblk_tfn == TFN_TCP_SND_OOB)
					cep->snd_up = cep->snd_una + len;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

				/* �ե饰��������ǽ�����ꤷ������Ū���������롣*/
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR | TCP_CEP_FLG_POST_OUTPUT;
#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */


				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			}
		}
	}

/*
 *  tcptsk_free_swbufq -- ����������ɥХåե�����
 */

static void
tcptsk_free_swbufq (T_TCP_CEP *cep)
{
	/*
	 *  ������ǧ����λ�����ͥåȥ�����󥿥ե����������
	 *  ���Ϥⴰλ�����Ȥ��ϡ�����������ɥХåե����塼��������롣
	 */

	/* ����������ɥХåե��λ����極������ꥻ�åȤ��롣*/
	cep->swbuf_count = 0;

	/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
	syscall(rel_net_buf(cep->swbufq));
	cep->swbufq = NULL;

	/* �ե饰����������ꤹ�롣*/
	cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_FREE;

	/* ����������ɥХåե��˶������Ǥ������Ȥ��Τ餻�롣*/
	syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

	/* ����������ɥХåե��ζ����Ԥ��ΤȤ��ϡ�TCP ���ϥ�������ư���롣*/
	if ((cep->flags & TCP_CEP_FLG_WBCS_NBUF_REQ) != 0) {
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

/*
 *  TCP ���ϥ�����
 */

void
tcp_output_task (intptr_t exinf)
{
	static int_t last_ix = 0;

	T_TCP_CEP	*cep;
	ID		tskid;
 	int_t		ix, sel_ix;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP OUTPUT:%d] started.", tskid);

	tcp_init();

#ifdef SUPPORT_INET6

	/* IPv6 �Υ��ơ��ȥ쥹�����ɥ쥹��ư�����¹Ԥ��롣*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #ifdef SUPPORT_INET6 */

	while (true) {

		/* ���Ϥ��ݥ��Ȥ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_POST_OUTPUT));

		if (++ last_ix == tmax_tcp_cepid)
			last_ix = 0;
		sel_ix = ix = last_ix;
		do {
			cep = &tcp_cep[ix];

#ifdef TCP_CFG_SWBUF_CSAVE

			if ((cep->flags & TCP_CEP_FLG_WBCS_NBUF_REQ) != 0 &&
			    ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_FREE ||
			     (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_RSVD)) {
				tcptsk_alloc_swbufq(cep);
				sel_ix = ix;
				}

			if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_ACKED &&
			    (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) == 0) {
				tcptsk_free_swbufq(cep);
				sel_ix = ix;
				}

			/*
			 *  �ͥåȥ�����󥿥ե�������������������äƤ��ʤ��Ȥ��ϡ�
			 *  ������ͽ�󤹤롣
			 */
			if (cep->flags & TCP_CEP_FLG_POST_OUTPUT &&
			   (cep->flags & TCP_CEP_FLG_WBCS_MASK) >= TCP_CEP_FLG_WBCS_SENT) {
				syscall(wai_sem(cep->semid_lock));
				if (cep->swbufq == NULL)
					cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;
				else if (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) {
					cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;
					cep->flags |=  TCP_CEP_FLG_RESERVE_OUTPUT;
					}
				syscall(sig_sem(cep->semid_lock));
				}

			/*
			 *  ����ͽ����ˡ��ͥåȥ�����󥿥ե�����������������λ�����顢
			 *  �����򳫻Ϥ��롣����������������������λ�����Ȥ��ϲ��⤷�ʤ���
			 */
			if (cep->flags & TCP_CEP_FLG_RESERVE_OUTPUT) {
				syscall(wai_sem(cep->semid_lock));
				if (cep->swbufq != NULL && (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) == 0) {
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
					}
				syscall(sig_sem(cep->semid_lock));
				cep->flags &= ~TCP_CEP_FLG_RESERVE_OUTPUT;
				}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

			if (cep->flags & TCP_CEP_FLG_POST_OUTPUT) {

				cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;

#ifdef TCP_CFG_NON_BLOCKING

				if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP && cep->myaddr.portno == TCP_PORTANY) {
				 	ER	error;

					/*
					 *  tcp_con_cep �ΥΥ�֥�å��󥰥�����ǡ�
					 *  ̤�����Τξ��ϡ��ݡ����ֹ�������Ƥ롣
					 *  p_myaddr �� NADR (-1) ����
					 *  ���ݡ����ֹ椬 TCP_PORTANY �ʤ顢��ư�ǳ�����Ƥ롣
					 */
					if (cep->p_myaddr == NADR || cep->p_myaddr->portno == TCP_PORTANY)
						tcp_alloc_auto_port(cep);
					else if ((error = tcp_alloc_port(cep, cep->p_myaddr->portno)) != E_OK) {

						if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

							(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

							(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

						else
							syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

						/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
						cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
						cep->snd_tskid = TA_NULL;
						continue;
						}
					}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				tcp_output(cep);

				if (cep->flags & TCP_CEP_FLG_CLOSE_AFTER_OUTPUT) {
					/* ���ͥ��������Ĥ��롣*/
					tcp_close(cep);
					cep->flags &= ~TCP_CEP_FLG_CLOSE_AFTER_OUTPUT;
					}

				if (cep->flags & TCP_CEP_FLG_RESTORE_NEXT_OUTPUT) {
					/* snd_nxt �򸵤��᤹��*/
					if (SEQ_GT(cep->snd_old_nxt, cep->snd_nxt))
						cep->snd_nxt = cep->snd_old_nxt;
					cep->flags &= ~TCP_CEP_FLG_RESTORE_NEXT_OUTPUT;
					}

				sel_ix = ix;
				}

			if (++ ix == tmax_tcp_cepid)
				ix = 0;
			} while (ix != last_ix);

		/* ����ϡ����������̿�ü�����󤷤ˤ��롣*/
		last_ix = sel_ix;
		}
	}

#endif	/* of #ifdef SUPPORT_TCP */
