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
 *  @(#) $Id: tcp_input.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1994, 1995
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
 *	@(#)tcp_input.c	8.12 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_input.c,v 1.82.2.3 1999/10/14 11:49:38 des Exp $
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
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#ifdef SUPPORT_TCP

/*
 *  �����
 *
 *      RET_OK		����
 *	RET_DROP	���顼���������Ȥ��˴����롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 */

#define RET_OK		(0)
#define RET_NEED_OUTPUT	(1)
#define RET_RETURN	(2)
#define RET_DROP	(-1)
#define RET_RST_DROP	(-2)

/*
 *  �ؿ�
 */

static void close_connection	(T_TCP_CEP *cep, bool_t *needoutput);
static void set_rexmt_timer	(T_TCP_CEP *cep,  T_TCP_TIME rtt);
static uint8_t reassemble		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags);
static ER drop_after_ack	(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff);
static ER listening		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, T_TCP_SEQ iss);
static ER proc_ack1		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput);
static ER proc_ack2		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput);
static ER syn_sent		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void trim_length		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void parse_option	(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static bool_t update_wnd		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void proc_urg		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

/*
 *  ����������� Time Wait ���� CEP ʬΥ��ǽ
 */

/*
 *  �ؿ�
 */

static T_TCP_TWCEP*tcp_find_twcep (T_IN_ADDR *dstaddr,  uint16_t dstport,
                                   T_IN_ADDR *peeraddr, uint16_t peerport);

/*
 *  �ѿ�
 */

T_TCP_TWCEP tcp_twcep[NUM_TCP_TW_CEP_ENTRY];

/*
 *  tcp_find_twcep -- �ݡ����ֹ椫�� Time Wait �� TCP �̿�ü�������롣
 *
 *    ���: dstaddr �ϡ��ͥåȥ���Х��ȥ�����
 */

static T_TCP_TWCEP*
tcp_find_twcep (T_IN_ADDR *dstaddr, uint16_t dstport, T_IN_ADDR *peeraddr, uint16_t peerport)
{
	T_TCP_TWCEP*	twcep;
	
	/*
	 *  ���֤� TIME WAIT �ǡ�
	 *  IP ���ɥ쥹�ȥݡ����ֹ椬���פ����̿�ü����õ�����롣
	 */
	for (twcep = &tcp_twcep[NUM_TCP_TW_CEP_ENTRY]; twcep -- != tcp_twcep; ) {
		if (twcep->fsm_state == TCP_FSM_TIME_WAIT                   &&
		    IN_IS_DSTADDR_ACCEPT (&twcep->myaddr.ipaddr,  dstaddr)  &&
		    IN_ARE_NET_ADDR_EQUAL(&twcep->dstaddr.ipaddr, peeraddr) &&
		    dstport  == twcep->myaddr.portno                        &&
		    peerport == twcep->dstaddr.portno)
			return twcep;
		}

	return NULL;
	}

/*
 *  ɬ�פʾ���� Time Wait �� TCP �̿�ü���˰ܤ��ơ�
 *  ɸ��� TCP �̿�ü���������롣
 */

void
tcp_move_twcep (T_TCP_CEP *cep)
{
	T_TCP_TWCEP*	twcep;

	/* ������ Time Wait �� TCP �̿�ü����õ�����롣*/
	for (twcep = &tcp_twcep[NUM_TCP_TW_CEP_ENTRY]; twcep -- != tcp_twcep; ) {
		if (twcep->fsm_state != TCP_FSM_TIME_WAIT) {

			/*
			 *  �̿�ü�����å�����
			 *  ɬ�פʾ���� Time Wait �� TCP �̿�ü���˰ܤ���
			 */
			syscall(wai_sem(cep->semid_lock));
			twcep->rbufsz		= cep->rbufsz;
			twcep->dstaddr		= cep->dstaddr;
			twcep->myaddr		= cep->myaddr;
			twcep->snd_una		= cep->snd_una;
			twcep->rcv_nxt		= cep->rcv_nxt;
			twcep->rwbuf_count	= cep->rwbuf_count;
			twcep->fsm_state	= cep->fsm_state;
			twcep->timer_2msl	= cep->timer[TCP_TIM_2MSL];

			/* �̿�ü�����å��������롣*/
			syscall(sig_sem(cep->semid_lock));

			/* ɸ�� TCP �̿�ü���������롣*/
			tcp_close(cep);

			break;
			}
		}
	}

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

/*
 *  parse_option -- TCP �إå��Υ��ץ�������Ϥ��롣
 */

static void
parse_option (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	uint8_t	*opt, type = 0;
	uint_t	len, ol, ssize;

	opt = (uint8_t*)tcph + TCP_HDR_SIZE;
	len = (uint_t)(TCP_HDR_LEN(tcph->doff) - TCP_HDR_SIZE);
	while (len > 0 && (type = *opt) != TCP_OPT_EOL) {
		if (type == TCP_OPT_NOP)
			ol = 1u;
		else {
			if (len < 2)
				break;
			ol = *(opt + 1);
			if (ol < 2 || ol > len)
				break;
			}
		switch (type) {
		case TCP_OPT_NOP:
			break;
		case TCP_OPT_MAXSEG:
			if ((ol == TCP_OPT_LEN_MAXSEG) && (tcph->flags & TCP_FLG_SYN)) {
				ssize = ntohs(*(uint16_t*)(opt + 2));
				if (ssize > MAX_TCP_SND_SEG)
					cep->maxseg = MAX_TCP_SND_SEG;
				else if (ssize < TCP_MINMSS)
					cep->maxseg = TCP_MINMSS;
				else
					cep->maxseg = ssize;
				}
			break;

		case TCP_OPT_WINDOW:
		case TCP_OPT_SACK_PERM:
		case TCP_OPT_TIMESTAMP:
		case TCP_OPT_CC:
		case TCP_OPT_CCNEW:
		case TCP_OPT_CCECHO:
			syslog(LOG_INFO, "[TCP] unsup opt: %d.", type);
			break;

		default:
			syslog(LOG_NOTICE, "[TCP] unexp opt: %d.", type);
			break;
			}
		opt += ol;
		len -= ol;
		}
	}

/*
 *  set_rexmt_timer -- �������������֤�����������������ޤ򹹿����롣
 */

static void
set_rexmt_timer (T_TCP_CEP *cep, T_TCP_TIME rtt)
{
	T_TCP_TIME delta;

	NET_COUNT_TCP(net_count_tcp[NC_TCP_RTT_UPDATES], 1);
	if (cep->srtt != 0) {
		/*
		 *  srtt: ʿ�경���줿 RTT
		 *
		 *  ��¬���줿 RTT (rtt) �ȸ��ߤ�ʿ�경���줿 RTT (srtt) �κ� (delta) ����롣
		 *
		 *  delta �� 2 �ӥåȺ����ե� ( 4 ��) �����ͤ��ݻ����롣
		 *  srtt  �� 5 �ӥåȺ����ե� (32 ��) �����ͤ��ݻ�����Ƥ��롣
		 *
		 *    delta = rtt / 8 - srtt / 8
		 *
		 *  ������ srtt ��
		 *
		 *    srtt = rtt / 8 + srtt * 7 / 8
		 *         = srtt + (rtt / 8 - srtt / 8)
		 *
		 *  �Ƿ׻����롣
		 *  ���Τ��ᡢrtt �� 2 �ӥåȺ����եȤ���srtt �� (5 - 2) �ӥåȱ����եȤ��� delta ����롣
		 */
		delta = ((rtt - 1) << TCP_DELTA_SHIFT) - (cep->srtt >> (TCP_SRTT_SHIFT - TCP_DELTA_SHIFT));
		cep->srtt += delta;
		if (cep->srtt <= 0)
			cep->srtt = 1;

		/*
		 *  delta �������� | delta | ����롣
		 */
		if (delta < 0)
			delta = - delta;

		/*
		 *  rttvar: ʿ�경���줿ʬ��
		 *
		 *  rttvar �� 4 �ӥåȺ����ե� (16 ��) �����ͤ��ݻ�����Ƥ��롣
		 *
		 *    delta = |delta| / 4 - rttvar / 4
		 *
		 *  ������ rttvar ��
		 *
		 *    rttvar = |delta|/ 4 + rttvar * 3 /4
		 *           = rttvar + (|delta| / 4 - rttvar / 4)
		 *
		 *  �Ƿ׻����롣
		 */
		delta -= cep->rttvar >> (TCP_RTTVAR_SHIFT - TCP_DELTA_SHIFT);
		cep->rttvar += delta;
		if (cep->rttvar <= 0)
			cep->rttvar = 1;
		}
	else {
		/*
		 *  �ޤ� srtt �����꤬�Ԥ��Ƥ��ʤ��Ȥ��ϡ������¬���줿 RTT ����Ѥ��롣
		 *  ʿ�경���줿 RTT (srtt) �ˤϡ�RTT �� 5 �ӥåȺ����ե� (32��) �����͡�
		 *  ʿ�경���줿ʬ�� (rttvar) �ˤϡ�RTT �� 1/2 �� 4 �ӥåȺ����ե� (16��) �����͡�
		 */
		cep->srtt   = rtt <<  TCP_SRTT_SHIFT;
		cep->rttvar = rtt << (TCP_RTTVAR_SHIFT - 1);
		}

	/*
	 *  rtt ��¬���λ�������������ꥻ�åȤ��롣
	 */
	cep->rtt = cep->rxtshift = 0;

	/*
	 *  RTT �˵������Ǿ��� �� rtt + 2 ���礭���ͤ�������������ॢ���ȤκǾ��ͤˤ��롣
	 */
	if (rtt + 2 < TCP_TVAL_MIN)
		cep->rxtcur = tcp_range_set(tcp_rexmt_val(cep),
		                            (T_TCP_TIME)TCP_TVAL_MIN,
		                            (T_TCP_TIME)TCP_TVAL_MAX_REXMT);
	else
		cep->rxtcur = tcp_range_set(tcp_rexmt_val(cep),
		                            (T_TCP_TIME)(rtt + 2),
		                            (T_TCP_TIME)TCP_TVAL_MAX_REXMT);
	}

/*
 *  reassemble -- �����������Ȥ�ƹ������롣�����̤�˼��������Ȥ��ν���
 */

static uint8_t
reassemble (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags)
{
	T_TCP_Q_HDR 	*qhdr;
	T_TCP_HDR	*tcph;

	tcph = GET_TCP_HDR(input, thoff);
	if (tcph->sum > cep->rbufsz - cep->rwbuf_count) {
		/*
		 *  ����������ɥХåե��˶������ʤ��Ȥ����˴����롣
		 */
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DROP_SEGS], 1);
		syscall(rel_net_buf(input));
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		flags &= ~TCP_FLG_FIN;
		}
	else if (tcph->seq == cep->rcv_nxt &&
	         cep->reassq == NULL &&
	         cep->fsm_state == TCP_FSM_ESTABLISHED) {
		/*
		 *  �����̤�˥������Ȥ�����������ν���
		 *  �����������Ȥ��¤��ؤ������פʤΤ�
		 *  ���Τޤ޼���������ɥХåե��˽񤭹��ࡣ
		 */

#ifdef TCP_CFG_DELAY_ACK

		cep->flags |= TCP_CEP_FLG_DEL_ACK;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		qhdr = GET_TCP_Q_HDR(input, thoff);

		/*  TCP �إå��ΰ��֤���¸���롣*/
		GET_TCP_IP_Q_HDR(input)->thoff = thoff;

		/* SDU �Υ��ե��åȡʸ��ϥ�����ɥ������ˤ�ꥻ�åȤ��롣*/
		qhdr->soff = 0;

		/* �ǡ��������������ɥХåե��˽񤭹��ࡣ*/
		TCP_WRITE_RWBUF(cep, input, thoff);
		}
	else {
		flags = tcp_write_raque(input, cep, thoff, flags);
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		}
	return flags;
	}

/*
 *  listening -- ��ư�����ץ󤷤ơ����֤� LISTEN �ν���
 *
 *    �����:
 *      RET_OK		����
 *	RET_DROP	���顼���������Ȥ��˴����롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 */

static ER
listening (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, T_TCP_SEQ iss)
{
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;

	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, thoff);

	/* 
	 *  �ե饰�� RST �����åȤ���Ƥ�����˴����롣
	 */
	if (tcph->flags & TCP_FLG_RST)
		return RET_DROP;

	/*  
	 *  �ե饰�� ACK �����åȤ��Ƥ줤��С�
	 *  �ꥻ�åȤ����ä��˴����롣
	 */
	if (tcph->flags & TCP_FLG_ACK)
		return RET_RST_DROP;

	/* 
	 *  �ե饰�� SYN �����åȤ���Ƥ��ʤ���Ф���˴����롣
	 */
	if ((tcph->flags & TCP_FLG_SYN) == 0)
		return RET_DROP;

#if defined(SUPPORT_INET4)

#ifdef SUPPORT_LOOP

	/*
	 *  ���ΤȤ����˴����롣
	 *    ���ݡ����ֹ椬Ʊ��ǡ������� IP ���ɥ쥹 ��Ʊ�졣
	 *      ��������������롼�ץХå� (127.0.0.1) �ʤ��ɤ���
	 *    ���ޥ�����㥹�ȥ��ɥ쥹
	 */

	if (tcph->dport == tcph->sport &&
	    (iph->dst == iph->src && ntohl(iph->src) != IPV4_ADDR_LOOPBACK))
		return RET_DROP;

#else	/* of #ifdef SUPPORT_LOOP */

	/*
	 *  ���ΤȤ����˴����롣
	 *    ���ݡ����ֹ椬Ʊ��ǡ������� IP ���ɥ쥹 ��Ʊ�졣
	 *    ���ޥ�����㥹�ȥ��ɥ쥹
	 */

	if (tcph->dport == tcph->sport && iph->dst == iph->src)
		return RET_DROP;

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

	/*
	 *  ���ΤȤ����˴����롣
	 *    ���ݡ����ֹ椬Ʊ��ǡ������� IP ���ɥ쥹 ��Ʊ�졣
	 *    ���ޥ�����㥹�ȥ��ɥ쥹
	 */

	if (tcph->dport == tcph->sport && IN_ARE_ADDR_EQUAL(&iph->dst, &iph->src))
		return RET_DROP;

#endif	/* of #if defined(SUPPORT_INET6) */

	if (IN_IS_NET_ADDR_MULTICAST(&iph->dst))
		return RET_DROP;

	/* ���Υ��ɥ쥹��Ͽ���롣*/
	IN_COPY_TO_HOST(&cep->dstaddr.ipaddr, &iph->src);
	cep->dstaddr.portno = tcph->sport;

	/* ���ץ�����������롣*/
	parse_option(tcph, cep);

	/* ���������ֹ���������롣*/
	if (tcp_iss == 0)
		tcp_init_iss();

	/* ��ʬ�Υ��������ֹ�ν���ͤ�Ͽ���롣*/
	if (iss != 0)
		cep->iss = iss;
	else
		cep->iss = tcp_iss;

	tcp_iss += TCP_ISS_INCR() / 4;

	/* ���Υ��������ֹ�ν���ͤ�Ͽ���롣*/
	cep->irs = tcph->seq;

	/* ���������������ֹ���������롣*/
	init_send_seq(cep);
	init_receive_seq(cep);

	/* ����������ɥ����������ꤹ�롣*/
	cep->snd_wnd = tcph->win;

	/* �ǽ����� */
	cep->flags    |= TCP_CEP_FLG_ACK_NOW;
	cep->fsm_state = TCP_FSM_SYN_RECVD;
	cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_INIT;

	return RET_OK;
	}

/*
 *  syn_sent -- ǽư�����ץ󤷤ơ����֤� SYN �����Ѥν���
 *
 *    �����:
 *      RET_OK		����
 *	RET_DROP	���顼���������Ȥ��˴����롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 */

static ER
syn_sent (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	ER error = RET_OK;

	/*
	 *  ��꤫�������ǧ����������Ƥ⡢
	 *
	 *    ACK <= iss && ������������ SEQ (snd_max) < ACK
	 *
	 *  �ʤ顢�ꥻ�åȤ����äƥ������Ȥ��˴����롣
	 */
	if ((tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_LE(tcph->ack, cep->iss) || SEQ_GT(tcph->ack, cep->snd_max)))
		return RET_RST_DROP;

	/*
	 *  RST/ACK �ե饰�α���������С��ݡ��Ȥ������Ƥ��ʤ�
	 *  ���Ȥ��̣���Ƥ��롣
	 */
	if (tcph->flags & TCP_FLG_RST) {
		if (tcph->flags & TCP_FLG_ACK) {
			cep->net_error = EV_CNNRF;
			cep = tcp_drop(cep, E_CLS);
			}
		return RET_DROP;
		}

	/*
	 *  SYN �ե饰���ʤ���Х������Ȥ��˴����롣
	 */
	if ((tcph->flags & TCP_FLG_SYN) == 0)
		return RET_DROP;

	cep->snd_wnd = tcph->win;	/* snd_wnd: ���μ�����ǽ������ɥ�����	*/
	cep->irs     = tcph->seq;	/* irs:     ���Υ��������ֹ�ν����	*/
	init_receive_seq(cep);		/* ���������������ֹ���������롣		*/

	if (tcph->flags & TCP_FLG_ACK) {
		/*
		 *  ACK �ե饰������Ȥ��ν���
		 *
		 *  ��������Ԥ��Ƥ������� SEQ (rcv_adv) ��
		 *  ������ǽ�ʥ�����ɥ����� (rcv_wnd) ʬ�ʤ�롣
		 */
		cep->rcv_adv += cep->rcv_wnd;	/* rcv_adv: ��������Ԥ��Ƥ������� SEQ	*/
						/* rcv_wnd: ������ǽ�ʥ�����ɥ�����		*/

		/* ̤��ǧ�κǾ����� SEQ (snd_una) �� SYN ʬ (1 �����ƥå�) �ʤ�롣*/
		cep->snd_una ++;

#ifdef TCP_CFG_DELAY_ACK

		if (tcph->sum != 0)		/* tcph->sum �� SDU Ĺ */
			cep->flags |= TCP_CEP_FLG_DEL_ACK;
		else
			cep->flags |= TCP_CEP_FLG_ACK_NOW;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		if (cep->flags & TCP_CEP_FLG_NEED_FIN) {
			/*
			 *  CEP �� FIN �������׵ᤵ��Ƥ���С�
			 *  ���ǽ����򳫻Ϥ���
			 *  CEP �ξ��֤� FIN Wait 1 �ˤ��롣
			 */
			cep->fsm_state = TCP_FSM_FIN_WAIT_1;
			cep->flags  &= ~TCP_CEP_FLG_NEED_FIN;
			tcph->flags &= ~TCP_FLG_SYN;
			}
		else {
			/*
			 *  ��꤫�� ACK ���������줿�Τǡ�
			 *  CEP �ξ��֤� ���ͥ�������ߴ�λ���֤ˤ��롣
			 */
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
			cep->fsm_state  = TCP_FSM_ESTABLISHED;
			NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_ESTABLISHED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP) {

				/* ���Υ��ɥ쥹�򥳥ԡ����롣*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					error = RET_RST_DROP;
					}
				cep->p_dstaddr = NULL;
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}
			else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
			}
		}
	else {
		/* ACK �ե饰���ʤ��Ȥ��ϡ�ACK �����äơ�CEP �ξ��֤� SYN �����Ѥߤˤ��롣*/
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		cep->timer[TCP_TIM_REXMT] = 0;
		cep->fsm_state  = TCP_FSM_SYN_RECVD;
		}

	return error;
	}

/*
 *  trim_length -- �������� SDU Ĺ��Ĵ�����롣
 */

static void
trim_length (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	tcph->seq ++;
	if (tcph->sum > cep->rcv_wnd) {		/* ���: tcph->sum �� SDU Ĺ */
		/*
		 *  SDU Ĺ������������ɥ���������礭���Ȥ��ϡ�����������ɥ������ʹߤ�
		 *  �˴�����FIN �˱������ʤ����Ȥǡ��˴������ǡ�������������롣
		 */
		tcph->sum    = (uint16_t)cep->rcv_wnd;
		tcph->flags &= ~TCP_FLG_FIN;
		}
	cep->snd_wl1 = tcph->seq - 1;		/* cep->snd_wl1: ������ɹ��� SEQ �ֹ�	*/

#ifdef TCP_CFG_EXTENTIONS
	cep->rcv_up  = tcph->seq;		/* cep->rcv_up : ���������۵ޥݥ���	*/
#endif
	}

/*
 *  proc_ack2 -- ACK �ν��� (2)
 *
 *    �����
 *
 *      RET_OK		����
 *      RET_RETURN	����꥿���󤹤롣
 *	RET_DROP	���顼���������Ȥ��˴����롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 */

static ER
proc_ack2 (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput)
{
	T_TCP_HDR	*tcph;
	ER		ret = RET_OK;
	uint32_t	acked;
	bool_t		ourfinisacked = false;

	tcph = GET_TCP_HDR(input, thoff);

	/*
	 *  ���˼�����ǧ���줿 ACK ���顢�ޤ���ǧ����Ƥ��ʤ�
	 *  �Ǿ����� SEQ (snd_una) ������ȡ�����������ɥХåե�����
	 *  ������Ƥ褤�����ƥåȿ� (acked) �ˤʤ롣
	 */
	acked = tcph->ack - cep->snd_una;
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_ACKS], 1);

	/*
	 *  �������ַ�¬ (rtt) �����ꤵ��Ƥ��ơ���¬���� SEQ ���
	 *  ��� ACK ����������顢�����ޥХå����դ򥭥�󥻥뤷��
	 *  ���������ޤ�����ꤹ�롣
	 */
	if (cep->rtt && SEQ_GT(tcph->ack, cep->rtseq)) {
		set_rexmt_timer(cep, cep->rtt);
		}

	/*
	 *  ���Ƥ�̤��ǧ�ǡ����� ACK ���줿�顢���������ޤ���ߤ���
	 *  �Ƴ��򵭲����� (����˽��Ϥ���³)��
	 *  �⤷��ACK ���٤��������¿���Υǡ���������ʤ顢���������ޤ�
	 *  ���ߤκ��������ॢ���Ȥ����ꤹ�롣
	 */
	if (tcph->ack == cep->snd_max) {	/* cep->snd_max: ������������ SEQ */

#ifdef TCP_CFG_SWBUF_CSAVE

		/*
		 * ����������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ξ��ϡ�
		 * �����Ѥߤǡ�ACK����λ����ޤǺ��������ޤ��ѹ����ʤ���
		 */
		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_ACKED)
			cep->timer[TCP_TIM_REXMT] = 0;

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		cep->timer[TCP_TIM_REXMT] = 0;

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		*needoutput = true;
		}
	else if (cep->timer[TCP_TIM_PERSIST] == 0) {
	 	cep->timer[TCP_TIM_REXMT] = cep->rxtcur;	/* cep->rxtcur: ���ߤκ��������ॢ���� */
		}

	/* ��꤬������ǧ�����ǡ���������Ȥ��ν��� */
	if (acked) {
		uint32_t cw   = cep->snd_cwnd;	/* cep->snd_cwnd: ���ԥ�����ɥ�����	*/
		uint32_t incr = cep->maxseg;		/* cep->maxseg:   ���祻�����ȥ�����	*/

		/*
		 *  ��������꤬������ǧ�����ǡ��������ä��Ȥ��ϡ�
		 *  ���ԥ�����ɥ��������礭�����롣
		 *  ���ԥ�����ɥ����� (snd_cwnd) ��
		 *  ���ԥ�����ɥ������Τ������� (snd_ssthresh) ����礭���Ȥ���
		 *  ���Բ��������Ԥ���
		 *
		 *    snd_cwnd = snd_cwnd + maxseg * maxseg / snd_cwnd;
		 *
		 *  ���������������Ȥ��ϡ������������������Ԥ���
		 *
		 *    snd_cwnd = snd_cwnd + maxseg
		 *
		 */
		if (cw > cep->snd_ssthresh)
			/* ���Բ������� */
			incr = incr * incr / cw;

		if (cw + incr < MAX_TCP_WIN_SIZE)
			cep->snd_cwnd = (uint16_t)(cw + incr);
		else
			cep->snd_cwnd = MAX_TCP_WIN_SIZE;

		/*
		 *  ����������ɥХåե����顢��꤬������ǧ�����ǡ����� (acked) �Υǡ����������롣
		 */
		if (acked > cep->swbuf_count) {
			cep->snd_wnd -= cep->swbuf_count;
			TCP_DROP_SWBUF(cep, (uint_t)cep->swbuf_count);
			ourfinisacked = true;
			}
		else {
			cep->snd_wnd -= (uint16_t)acked;
			TCP_DROP_SWBUF(cep, (uint_t)acked);
			ourfinisacked = false;
			}

		/* ����������ɥХåե��˶������Ǥ������Ȥ��Τ餻�롣*/
		syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

		/*
		 *  ��ã��ǧ����Ƥ��ʤ��Ǿ����� SEQ (snd_una) ��
		 *  ������ã��ǧ���줿 ACK �ޤǿʤᡢ
		 *  ���������ǡ����� SEQ (snd_nxt) �⡢������
		 *  ��ã��ǧ����Ƥ��ʤ��Ǿ����� SEQ (snd_una)
		 *  �ޤǿʤ�롣
		 */
		cep->snd_una += acked;
		if (SEQ_LT(cep->snd_nxt, cep->snd_una))
			cep->snd_nxt = cep->snd_una;

		/*
		 *  ���֤ˤ��ʬ��
		 */
		switch (cep->fsm_state) {
		case TCP_FSM_FIN_WAIT_1:	/* APP ����λ��FIN �����Ѥߡ�ACK �Ԥ� */
			if (ourfinisacked) {
				cep->fsm_state = TCP_FSM_FIN_WAIT_2;
				cep->timer[TCP_TIM_2MSL] = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL;
				}
			break;
		case TCP_FSM_CLOSING:		/* Ʊ����������FIN �򴹺Ѥߡ�ACK �Ԥ� */
			if (ourfinisacked) {
				/*
				 *  �������� FIN ����ǧ����Ƥ���о��֤��ѹ�����
				 *  ���٤ƤΥ����ޤ�ꥻ�åȤ����塢2MSL �����ޤ����ꤹ�롣
				 */
				cep->fsm_state = TCP_FSM_TIME_WAIT;
				tcp_cancel_timers(cep);
				cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
				}
			break;
		case TCP_FSM_LAST_ACK:		/* APP ����λ��ACK �Ԥ� */
			if (ourfinisacked) {
				/*
				 *  �������� FIN ����ǧ����Ƥ���С�cep �򥯥�������
				 *  �������Ȥ��˴����롣
				 */
				cep = tcp_close(cep);
				ret = RET_DROP;
				}
			break;
		case TCP_FSM_TIME_WAIT:		/* ��꤫��� FIN �����Ѥߡ������Ԥ� */
			/*
			 *  ��꤫�� FIN ���������줿���⤦����2MSL �����ޤ����ꤷ��
			 *  ACK �����塢�������Ȥ��˴����롣
			 */
			cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
			return drop_after_ack(input, cep, thoff);
			}
		}

	return ret;
	}

/*
 *  proc_ack1 -- ACK �ν��� (1)
 *
 *    �����:
 *      RET_OK		����
 *      RET_RETURN	����꥿���󤹤롣
 *	RET_DROP	���顼���������Ȥ��˴����롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 *
 */

static ER
proc_ack1 (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput)
{
	T_TCP_HDR *tcph = GET_TCP_HDR(input, thoff);

	switch (cep->fsm_state) {
	case TCP_FSM_SYN_RECVD:		/* SYN ���������SYN �����Ѥ�	*/

		/* ���֤��ѹ����롣*/
		if (cep->flags & TCP_CEP_FLG_NEED_FIN) {
			cep->fsm_state  = TCP_FSM_FIN_WAIT_1;
			cep->flags &= ~TCP_CEP_FLG_NEED_FIN;
			}
		else {
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
			cep->fsm_state  = TCP_FSM_ESTABLISHED;

			/* TCP �̿�ü������TCP ���ո���������롣*/
			cep->rep = NULL;

			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_ESTABLISHED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->rcv_nblk_tfn == TFN_TCP_ACP_CEP) {

				/* ���Υ��ɥ쥹�򥳥ԡ����롣*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					cep->p_dstaddr = NULL;
					cep->rcv_tskid = TA_NULL;
					cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					cep->p_dstaddr = NULL;
					cep->rcv_tskid = TA_NULL;
					cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
					return RET_RST_DROP;
					}
				}

			if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP) {

				/* ���Υ��ɥ쥹�򥳥ԡ����롣*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					cep->p_dstaddr = NULL;
					cep->snd_tskid = TA_NULL;
					cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					cep->p_dstaddr = NULL;
					cep->snd_tskid = TA_NULL;
					cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
					return RET_RST_DROP;
					}
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			if (cep->rcv_tfn == TFN_TCP_ACP_CEP) {
				NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
				NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
				}

			if (cep->snd_tfn == TFN_TCP_CON_CEP) {
				NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
				NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
				}
			}

		/*
		 *  SDU ���ʤ� FIN ���Ĥ��Ƥ��ʤ���С�tcp_move_ra2rw() ��ƽФ���
		 */
		if (tcph->sum == 0 && (tcph->flags & TCP_FLG_FIN) == 0)		/* tcph->sum �� SDU Ĺ */
			tcph->flags = tcp_move_ra2rw(cep, tcph->flags);
		
		cep->snd_wl1 = tcph->seq - 1;	/* snd_wl1: ������ɹ��� SEQ */

		/* break; ��������롣*/
	
	case TCP_FSM_ESTABLISHED:	/* ���ͥ�������ߴ�λ		*/
	case TCP_FSM_FIN_WAIT_1:	/* ��λ���ơ�FIN �����Ѥ�		*/
	case TCP_FSM_FIN_WAIT_2:	/* ��λ��FIN ��ã��ǧ������FIN�Ԥ�*/
	case TCP_FSM_CLOSE_WAIT:	/* FIN �������������Ԥ�		*/
	case TCP_FSM_CLOSING:		/* ��λ��FIN �򴹺Ѥߡ�ACK �Ԥ�	*/
	case TCP_FSM_LAST_ACK:		/* FIN ��������λ��ACK �Ԥ�	*/
	case TCP_FSM_TIME_WAIT:		/* ��λ�������Ԥ�		*/

		if (SEQ_LE(tcph->ack, cep->snd_una)) {

			/*
			 *  ������ǧ ACK �� ̤��ǧ�κǾ����� SEQ (snd_una) ��Ʊ���������ΤȤ��ν���
			 *  �Ĥޤꡢ¿�Ť� ACK ������������Ȥ��̣���Ƥ��롣
			 */

			if (tcph->sum == 0 && tcph->win == cep->snd_wnd) {	/* tcph->sum �� SDU Ĺ */

				/*
				 *  SDU ���ʤ������Υ�����ɥ��������ѹ�����Ƥ��ʤ���С�
				 *  ���Ǥ����������������Ȥ���ǡ�ACK (tcph->ack) ��
				 *  Ʊ�� SEQ ����Ϥޤ륻�����Ȥ�������Ǿü�������ǽ�������롣
				 *  ���ξ��ϡ���®��ž���ȹ�®�ꥫ�Х��Ԥ���
				 */
				NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DUP_ACKS], 1);

				if (cep->timer[TCP_TIM_REXMT] == 0 || tcph->ack != cep->snd_una) {

					/*
					 *  ���������ޤ����åȤ���Ƥ��ʤ��Ȥ���
					 *  �ޤ��ϡ�ACK (tcph->ack) ��̤��ǧ�κǾ����� SEQ��
					 *  ���פ��ʤ��Ȥ��ϡ�¿�� ACK ���� 0 �ˤ��롣
					 */
					cep->dupacks = 0;
					}

				else if (++ cep->dupacks == MAX_TCP_REXMT_THRESH) {

					/*
					 *  ¿�� ACK ������������ (ɸ�� 3) �ˤʤä���
					 *  ��®��ž�������򳫻Ϥ��롣
					 */
					uint_t		win;

					/*
					 *  ���ԥ�����ɥ�����(snd_cwnd)�Τ������ͤ����ꤹ�롣
					 *
					 *    ���μ�����ǽ������ɥ����� (snd_wnd) ��
					 *    ���ԥ�����ɥ����� (snd_cwnd) �� 1/2��
					 *    ��������2 * maxseg �ʾ塣
					 *
					 */
					if (cep->snd_wnd < cep->snd_cwnd)
						win = cep->snd_wnd / 2 / cep->maxseg;
					else
						win = cep->snd_cwnd / 2 / cep->maxseg;
					if (win < 2)
						win = 2;
					cep->snd_ssthresh = win * cep->maxseg;

					/* ���������ޤȱ������֤�ꥻ�åȤ��롣*/
					cep->timer[TCP_TIM_REXMT] = 0;
					cep->rtt = 0;

					/* �ü������������Ȥ��������롣*/
					cep->snd_old_nxt = cep->snd_nxt;
					cep->snd_nxt     = tcph->ack;
					cep->snd_cwnd    = cep->maxseg;

					/*
					 *  snd_nxt �򸵤��᤹�褦�����ꤷ��
					 *  ������ؼ����롣
					 */
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT |
					               TCP_CEP_FLG_FORCE       |
					               TCP_CEP_FLG_FORCE_CLEAR |
					               TCP_CEP_FLG_RESTORE_NEXT_OUTPUT;
					sig_sem(SEM_TCP_POST_OUTPUT);

					/* ���ԥ�����ɥ������򹹿����롣*/
					cep->snd_cwnd = (uint16_t)(cep->snd_ssthresh
					                   + cep->maxseg * cep->dupacks);
					
					return RET_DROP;
					}

				else if (cep->dupacks > MAX_TCP_REXMT_THRESH) {

					/*
					 *  ¿�� ACK ������������ (ɸ�� 3) ��Ķ������
					 *  ���ԥ�����ɥ����������ä��ʤ���������롣
					 */
					cep->snd_cwnd += cep->maxseg;

					/* ������ؼ����롣*/
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
					sig_sem(SEM_TCP_POST_OUTPUT);

					return RET_DROP;
					}
				} 
			else
				cep->dupacks = 0;
			break;
			}

		/*
		 *  ������ǧ ACK �� ̤��ǧ�κǾ����� SEQ (snd_una) �ʹߤΤȤ��ν���
		 */
		if (cep->dupacks >= MAX_TCP_REXMT_THRESH && cep->snd_cwnd > cep->snd_ssthresh)
		 	/*
			 *  ��®��ž����ԤäƤ����Ȥ��ϡ����ԥ�����ɥ������򤷤����ͤޤ��᤹��
			 */
			cep->snd_cwnd = (uint16_t)cep->snd_ssthresh;
	
		cep->dupacks = 0;

		if (SEQ_GT(tcph->ack, cep->snd_max))
			/*
			 *  �������� ACK �������������� SEQ ��Ķ���Ƥ����Ȥ��ν���
			 */
			return drop_after_ack(input, cep, thoff);

		if (cep->flags & TCP_CEP_FLG_NEED_SYN) {
			/*
			 *  SYN �����׵����ä��ơ�̤��ǧ�κǾ����� SEQ ��ʤ�롣
			 */
			cep->flags &= ~TCP_CEP_FLG_NEED_SYN;
			cep->snd_una ++;
			}
		
		return proc_ack2(input, cep, thoff, needoutput);
		break;
		}
	return RET_OK;
	}

/*
 *  update_wnd -- ������ɥ������򹹿����롣
 *
 *    �����: ������ɬ�פʤ� true ���֤���
 */

static bool_t
update_wnd (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{

	/*
	 *  �������
	 *
	 *    ACK �ե饰�����åȤ���Ƥ��� &&
	 *    (���󥦥���ɤ򹹿����� SEQ (snd_wl1) �� SEQ ����� ||
	 *     ���󥦥���ɤ򹹿����� SEQ (snd_wl1) �� SEQ ��Ʊ�� &&
	 *     (���󥦥���ɤ򹹿����� ACK (snd_wl2) �� ACK ����� ||
	 *      (���󥦥���ɤ򹹿����� ACK (snd_wl2) �� ACK ��Ʊ�� &&
	 *       WIN �����μ�����ǽ������ɥ����� (snd_wnd) ����礭��
	 *       )
	 *      )
	 *     )
	 */
	if ((tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_LT(cep->snd_wl1, tcph->seq) ||
	     (cep->snd_wl1 == tcph->seq &&
	      (SEQ_LT(cep->snd_wl2, tcph->ack) ||
	       (cep->snd_wl2 == tcph->ack && tcph->win > cep->snd_wnd))))) {

		cep->snd_wnd = tcph->win;
		cep->snd_wl1 = tcph->seq;
		cep->snd_wl2 = tcph->ack;

		if (cep->snd_wnd > cep->max_sndwnd)
			/* ���ޤǤκ�������������ɥ������򹹿����롣*/
			cep->max_sndwnd = cep->snd_wnd;

#ifdef TCP_CFG_SWBUF_CSAVE

		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_WOPEN_PEND) {

			/*
			 *  ����������ɥХåե��ѤΥͥåȥ���Хåե����������ǡ�
			 *  ���μ���������ɤ������Τ��ԤäƤ���Ȥ��ν���
			 */
			if (cep->snd_wnd > 0) {

				/*
				 *  ���μ���������ɤ��������Ȥ��ϡ�
				 *  ����������ɥХåե��ѤΥͥåȥ���Хåե�������Ƥ�Ƴ����롣
				 */
				cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK)
				                         |  TCP_CEP_FLG_WBCS_FREE |  TCP_CEP_FLG_POST_OUTPUT;
				sig_sem(SEM_TCP_POST_OUTPUT);
				}
			}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		return true;
		}
	else
		return false;
	}

/*
 *  proc_urg -- �۵ޥǡ����Ĥ��Υ������Ȥν���
 */

#ifdef TCP_CFG_EXTENTIONS

static void
proc_urg (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	if ((tcph->flags & TCP_FLG_URG) && VALID_URG_POINTER(tcph->urp) &&
	    TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {

		/* �۵ޥǡ����Ĥ��Υ������Ȥν��� */

		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_URG_SEGS], 1);
		if (tcph->urp + cep->rwbuf_count > cep->rbufsz) {

			/*
			 *  �۵ޥݥ��󥿤ΰ��֤�����������ɥХåե���
			 *  �ϰϤ�Ķ����Ȥ��ϲ��⤷�ʤ���
			 */
			tcph->urp    = 0;
			tcph->flags &= ~TCP_FLG_URG;
			}

		if (SEQ_GT(tcph->seq + tcph->urp, cep->rcv_up))
			/* �۵ޥݥ��󥿤��������줿�Ȥ��ν��� */
			cep->rcv_up = tcph->seq + tcph->urp;

		if ((tcph->flags & TCP_FLG_URG) && (tcph->urp + TCP_CFG_URG_OFFSET) < tcph->sum) {	/* tcph->sum �� TCP �� SDU Ĺ */

			/*
			 *  �۵ޥݥ��󥿤ΰ��֤������������������������ξ��ϡ�
			 *  ������Хå��ؿ���ƤӽФ���
			 */
			cep->urg_tcph = tcph;
			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), TEV_TCP_RCV_OOB, (void*)(uint32_t)1);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				uint32_t	len = 1;

				(*cep->callback)(GET_TCP_CEPID(cep), TEV_TCP_RCV_OOB, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else {
				syslog(LOG_WARNING, "[TCP] no call back for OOB, CEP: %d.", GET_TCP_CEPID(cep));
				}

			if (cep->urg_tcph != NULL) {
				/* ������Хå��ؿ���� tcp_rcv_oob() ��ƽФ��ʤ��ä���*/
				cep->urg_tcph = NULL;
				tcph->urp = 0;
				}
			else {
				/* 
				 *  ������Хå��ؿ���� tcp_rcv_oob() ��ƽФ������ϡ�
				 *  SDU Ĺ�������ͤ����ꤹ�롣
				 */
				tcph->urp = 1;
				}
			}
		else if (tcph->urp > 0) {
			tcph->urp = 0;
			}

		}
	else if (SEQ_GT(cep->rcv_nxt, cep->rcv_up)) {
		cep->rcv_up = cep->rcv_nxt;
		tcph->urp = 0;
		}
	}

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

static void
proc_urg (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	tcph->urp = 0;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

/*
 *  drop_after_ack -- �����������Ȥ��˴������塢ACK ���֤� (���: ̾���ȤϹ�äƤ��ʤ�)��
 *
 *    �����:
 *      RET_RETURN	����꥿���󤹤롣
 *	RET_RST_DROP	���顼��RST �����������������Ȥ��˴����롣
 */

static ER
drop_after_ack (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff)
{
	T_TCP_HDR *tcph = GET_TCP_HDR(input, thoff);

	/*
	 *    SYN �������֤ǡ�ACK ����ã��ǧ����Ƥ��ʤ��Ǿ����� SEQ (snd_una) ���
	 *    �����ͤ����������줿���� SEQ (snd_max) ������ͤξ��ϡ����� RST ��
	 *    ���äƽ�λ���롣����ϡ�"LAND" DoS ����ؤ��ɸ�Ǥ��ꡢ��¤���줿 SYN
	 *    �������Ȥ��������ĤŤ���ݡ��ȴ֤Ǥ� ACK ���ȡ�����ɤ���
	 */
	if (cep->fsm_state == TCP_FSM_SYN_RECVD && (tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_GT(cep->snd_una, tcph->ack) ||
	     SEQ_GT(tcph->ack, cep->snd_max)))
		return RET_RST_DROP;

	syscall(rel_net_buf(input));

	/* ������ؼ����롣*/
	cep->flags |=  TCP_CEP_FLG_ACK_NOW | TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);
	return RET_RETURN;
	}

/*
 *  close_connection -- ���ͥ����������������꤫�� FIN �����������
 */

static void
close_connection (T_TCP_CEP *cep, bool_t *needoutput)
{
	if (TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {

#ifdef TCP_CFG_DELAY_ACK

		if (cep->flags & TCP_CEP_FLG_NEED_SYN)
			cep->flags |= TCP_CEP_FLG_DEL_ACK;
		else
			cep->flags |= TCP_CEP_FLG_ACK_NOW;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->rcv_nxt ++;
		}

	switch (cep->fsm_state) {
	case TCP_FSM_SYN_RECVD:		/* SYN ���������SYN �����Ѥ�	*/
	case TCP_FSM_ESTABLISHED:	/* ���ͥ�������ߴ�λ		*/
		cep->fsm_state = TCP_FSM_CLOSE_WAIT;
		break;

	case TCP_FSM_FIN_WAIT_1:	/* APP ����λ��FIN �����Ѥߡ�ACK �Ԥ� */
		cep->fsm_state = TCP_FSM_CLOSING;
		break;

	case TCP_FSM_FIN_WAIT_2:	/* ��꤫��� FIN �Ԥ� */
		cep->fsm_state = TCP_FSM_TIME_WAIT;
		tcp_cancel_timers(cep);
		cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;

		/*
		 *  FIN WAIT 2 ���֤Ǥϡ�
		 *  �����ϲ�ǽ�Ǥ��뤬�����Ǥ������Ͻ�λ���Ƥ��롣
		 *  ���������⽪λ�����Τǡ����ϥ������Τߵ������롣
		 */
		syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

		/* ��꤫��� FIN ���Ф��Ʊ������֤���*/
		tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una,
		            cep->rbufsz - cep->rwbuf_count, TCP_FLG_ACK);
		cep->flags &= ~TCP_CEP_FLG_ACK_NOW;
		*needoutput = false;

		/*
		 *  ɬ�פʾ���� Time Wait �� TCP �̿�ü���˰ܤ��ơ�
		 *  ɸ��� TCP �̿�ü���������롣
		 */
		tcp_move_twcep(cep);

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

		break;

	case TCP_FSM_TIME_WAIT:		/* ��꤫��� FIN �����Ѥߡ������Ԥ� */
		cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
		break;
		}
	}

/*
 *  tcp_input -- TCP �����ϴؿ�
 *
 *	���: input �ˤ� IF �إå��� IP �إå�����Ƭ�ˤ��롣
 */

uint_t
tcp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	T_TCP_CEP	*cep = NULL;
	T_TCP_SEQ	iss = 0;
	ER		ret;
	bool_t		needoutput = false;
	int_t		rbfree;
	int32_t		todrop, win;
	uint16_t	seglen;
	uint8_t		flags;

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0
	T_TCP_TWCEP	*twcep;
#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_OCTETS],
	              input->len - GET_IF_IP_HDR_SIZE(input));
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpInSegs, 1);

	/* �إå�Ĺ������å����롣*/
	if (input->len < IF_IP_TCP_HDR_SIZE) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_HEADERS], 1);
		goto drop;
		}

	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, *offp);

	seglen  = input->len - *offp;				/* TCP �Υ�������Ĺ */

	if (IN_CKSUM(input, IPPROTO_TCP, *offp, (uint_t)seglen) != 0) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_CKSUMS], 1);
		goto drop;
		}

	/* TCP �إå�Ĺ������å����롣*/
	if (TCP_HDR_LEN(tcph->doff) < TCP_HDR_SIZE || TCP_HDR_LEN(tcph->doff) > seglen) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_HEADERS], 1);
		goto drop;
		}
	tcph->sum = seglen - TCP_HDR_LEN(tcph->doff);		/* �������� tcph->sum �� TCP �� SDU Ĺ */

	/*
	 *  SYN �� FIN ��ξ�ӥåȤ����åȤ���Ƥ�����˴����롣nmap �����к�
	 *  ��������RFC1644 T/TCP ��ĥ��ǽ�ȶ��礹�롣
	 */
	if ((tcph->flags & (TCP_FLG_SYN | TCP_FLG_FIN)) == (TCP_FLG_SYN | TCP_FLG_FIN))
		goto drop;

	/* �ͥåȥ��������������ۥ��ȥ����������Ѵ����롣*/

	NTOHL(tcph->seq);
	NTOHL(tcph->ack);
	NTOHS(tcph->win);
	NTOHS(tcph->urp);
	NTOHS(tcph->sport);
	NTOHS(tcph->dport);

find_cep:

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

	/*
	 *  ���֤� Time Wait ��� CEP ��õ�����롣
	 */
	twcep = tcp_find_twcep(&iph->dst, tcph->dport, &iph->src, tcph->sport);
	if (twcep != NULL) {

		if (tcph->flags & TCP_FLG_RST)		/* RST �ե饰����������Ȥ���̵�뤹�롣*/
			goto drop;
		else {

			/*
			 *    TCP �̿�ü���� Time Wait �λ������ۥ��Ȥ��饻�����Ȥ��褿�Ȥ��ϡ�
			 *    ���ۥ��Ȥ� FIN ���Ф��뼫�ۥ��Ȥ� ACK �������Ȥ������
			 *    »���������Ȥ��̣���Ƥ���Τǡ�ACK �������Ȥ�������롣
			 */

			/* �ۥ��ȥ�����������ͥåȥ�������������᤹��*/
			HTONS(tcph->sport);
			HTONS(tcph->dport);

			tcp_respond(input, NULL, twcep->rcv_nxt, twcep->snd_una, twcep->rbufsz - twcep->rwbuf_count, TCP_FLG_ACK);
			}
		return IPPROTO_DONE;
		}
	else
		/* ɸ��� TCP �̿�ü�������롣*/
		cep = tcp_find_cep(&iph->dst, tcph->dport, &iph->src, tcph->sport);

#else	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	/* TCP �̿�ü�������롣*/
	cep = tcp_find_cep(&iph->dst, tcph->dport, &iph->src, tcph->sport);

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	/*
	 *  TCP �̿�ü�����ʤ����� CEP �ξ��֤��������ʤ��˴����롣
	 */
	if (cep == NULL) {
		syslog(LOG_INFO, "[TCP] unexp port: %d.", tcph->dport);
		goto reset_drop;
		}

#ifdef TCP_CFG_TRACE

	tcp_input_trace(input, cep);

#endif	/* of #ifdef TCP_CFG_TRACE */


	if (cep->fsm_state == TCP_FSM_CLOSED)
		goto drop;

	/*
	 *  ���ͥ�������ߺѤߤǥ������Ȥ���������Ȥ��ϡ�
	 *  �����ɥ���֤���¸��ǧ�����ޤ�ꥻ�åȤ��롣
	 */
	cep->idle = 0;
	if (TCP_FSM_HAVE_ESTABLISHED(cep->fsm_state)) {
		cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
		}

	/* CEP �ξ��֤� LISTEN �ʳ��λ��ϡ����ץ�����������롣*/
	if (cep->fsm_state != TCP_FSM_LISTEN)
		parse_option(tcph, cep);

	/*
	 *  ������ǽ������ɥ�������׻����롣
	 *
	 *  rcv_nxt:     ��������Ԥ��Ƥ���Ǿ��� SEQ�ʤ�������ϼ����Ѥߡ�
	 *  rcv_adv:     ��������Ԥ��Ƥ������� SEQ
	 *  rbufsz:      ����������ɥХåե�������
	 *  rwbuf_count:  ����������ɥХåե��ˤ���ǡ�����
	 *  tcph->sum:   ����������� SDU ������
	 *
	 *  ������������������Ȥ������󥭥塼��Ϣ�뤹��
	 *  ��ǽ��������Τ� tcph->sum ���θ���롣
	 *
	 */
	win = cep->rbufsz - (cep->rwbuf_count + tcph->sum);
	if (win < 0)
		win = 0;
	if (win > (int32_t)(cep->rcv_adv - cep->rcv_nxt))
		cep->rcv_wnd = win;
	else
		cep->rcv_wnd = cep->rcv_adv - cep->rcv_nxt;

	/* CEP �ξ��֤ˤ�������Ԥ���*/

	if (cep->fsm_state == TCP_FSM_LISTEN) {		/* ��ư�����ץ� (LISTEN) �ν�����*/
		if ((ret = listening(input, cep, *offp, iss)) == RET_RST_DROP)
			goto reset_drop;
		else if (ret == RET_DROP)
			goto drop;
		trim_length(tcph, cep);			/* �������� SDU Ĺ��Ĵ�����롣*/

		if (tcph->flags & TCP_FLG_ACK) {	/* ACK �ե饰�ν��� */
			if ((ret = proc_ack2(input, cep, *offp, &needoutput)) == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}
	else if (cep->fsm_state == TCP_FSM_SYN_SENT) {	/* ǽư�����ץ�SYN �����Ѥ�	*/
		if ((ret = syn_sent(tcph, cep)) == RET_RST_DROP)
			goto reset_drop;
		else if (ret == RET_DROP)
			goto drop;
		trim_length(tcph, cep);			/* �������� SDU Ĺ��Ĵ�����롣*/

		if (tcph->flags & TCP_FLG_ACK) {	/* ACK �ե饰�ν��� */
			if ((ret = proc_ack2(input, cep, *offp, &needoutput)) == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}
	else {
		if (cep->fsm_state == TCP_FSM_SYN_RECVD) {	/* SYN �������SYN �����Ѥ�	*/
			/*
			 *  ��꤫�������ǧ����������Ƥ⡢
			 *
			 *    ACK <= ̤��ǧ�κǾ����� SEQ (snd_una) &&
			 *           ������������     SEQ (snd_max) < ACK
			 *
			 *  �ʤ顢�ꥻ�åȤ����äƥ������Ȥ��˴����롣
			 */
			if ((tcph->flags & TCP_FLG_ACK) &&
			    (SEQ_LE(tcph->ack, cep->snd_una) ||
			     SEQ_GT(tcph->ack, cep->snd_max)))
			     	goto reset_drop;
			}

		/* 
		 *  RST �ե饰����������Ȥ��ν��� (�۾�����)
		 */
		if (tcph->flags & TCP_FLG_RST) {
			if (SEQ_GE(tcph->seq, cep->last_ack_sent) &&
			    SEQ_LT(tcph->seq, cep->last_ack_sent + cep->rcv_wnd)) {
				/*
				 *  ���������������Ȥ� SEQ �����Ǹ���������� ACK (last_ack_sent)
				 *  ���顢����������ɥ��������ޤǤδ֤ν���
				 */
				switch (cep->fsm_state) {
				case TCP_FSM_SYN_RECVD:		/* SYN ���������SYN �����Ѥ�		*/

					cep->net_error = EV_CNNRF;	/* ��³��ǽ */
					cep->error     = E_CLS;
					NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_RSTS], 1);
					NET_COUNT_MIB(tcp_stats.tcpAttemptFails, 1);
					cep = tcp_close(cep);
					break;

				case TCP_FSM_ESTABLISHED:	/* ���ͥ�������ߴ�λ			*/
				case TCP_FSM_CLOSE_WAIT:	/* FIN �������������Ԥ�		*/
					NET_COUNT_MIB(tcp_stats.tcpEstabResets, 1);
					/* fallthrough */

				case TCP_FSM_FIN_WAIT_1:	/* ��λ���ơ�FIN �����Ѥ�		*/
				case TCP_FSM_FIN_WAIT_2:	/* ��λ��FIN ��ã��ǧ������FIN�Ԥ�	*/

					cep->net_error = EV_CNRST;	/* ��³�ꥻ�å� */
					cep->error     = E_CLS;
					NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_RSTS], 1);
					/* no break; */

				case TCP_FSM_CLOSING:		/* ��λ��FIN �򴹺Ѥߡ�ACK �Ԥ�	*/
				case TCP_FSM_LAST_ACK:		/* FIN ��������λ��ACK �Ԥ�	*/

					cep = tcp_close(cep);
					break;
					}
				}
			goto drop;
			}

		/*
		 *  CEP �ξ��֤� SYN ���������SYN �����Ѥߤξ��ϡ�
		 *  ����������ɤ˼��ޤ�褦�˥ǡ�����
		 *  Ĵ���������ˡ�������³�ˤ��ѥ��åȤ��ɤ����򸡾ڤ��롣
		 *
		 *    ������������ SEQ < ���� SEQ �ν���� (irs)
		 *
		 *  ����ϡ�"LAND" DoS ������ɸ�Ǥ��롣
		 */
		if (cep->fsm_state == TCP_FSM_SYN_RECVD && SEQ_LT(tcph->seq, cep->irs)) {
			goto reset_drop;
			}

		/*
		 *  ��������Ԥ��Ƥ���Ǿ��� SEQ (rcv_nxt) - ������������ SEQ ��
		 *  ���ʤ顢rcv_nxt �����Υǡ����Ϥ��Ǥ˼������Ƥ���Τǡ�������ʬ��
		 *  ������롣
		 *                           <---------- rcv_wnd --------->
		 *                           rcv_nxt                      rcv_nxt + rcv_wnd
		 *                           v                            v
		 *                      -----+----------------------------+-----
		 *                           |                            |
		 *                      -----+----------------------------+-----
		 *           +----------------------+
		 *           |***************|      |
		 *           +----------------------+
		 *           ^                      ^
		 *           seq                    seq + len
		 *           <---------------> ������롣
		 */
		todrop = cep->rcv_nxt - tcph->seq;
		if (todrop > 0) {

			/*
			 *  SYN �ե饰���Ĥ��Ƥ���Ȥ��ϡ�����ʬ (1 �����ƥå�)
			 *  SEQ ��ʤᡢ�۵ޥݥ��󥿤Ⱥ������Ĺ����Ĵ�����롣
			 */
			if (tcph->flags & TCP_FLG_SYN) {
				tcph->flags &= ~TCP_FLG_SYN;
				tcph->seq ++;
				if (tcph->urp > 1)
					tcph->urp --;
				else
					tcph->flags &= ~TCP_FLG_URG;
				todrop --;
				}

			/*
			 *  �������Ĺ���� SDU ���Ĺ�����Ĥޤꡢ��������Ԥ��Ƥ���
			 *  �Ǿ��� SEQ (rcv_nxt) ��ã���Ƥ��ʤ�����
			 *  �������Ĺ���� SDU ��Ʊ���ǡ�FIN �ե饰���Ĥ��Ƥʤ����
			 *  ���ƺ�����롣
			 */
			if ( todrop >  tcph->sum ||		/* tcph->sum �� TCP �� SDU Ĺ */
			    (todrop == tcph->sum && (tcph->flags & TCP_FLG_FIN) == 0)) {
				tcph->flags &= ~TCP_FLG_FIN;
				cep->flags |= TCP_CEP_FLG_ACK_NOW;
				todrop = tcph->sum;		/* tcph->sum �� TCP �� SDU Ĺ */
				}

			/*
			 *  SDU �����˵ͤ�롣
			 */
			if (todrop < tcph->sum) {		/* tcph->sum �� TCP �� SDU Ĺ */
				memcpy(GET_TCP_SDU(input, *offp),
				       GET_TCP_SDU(input, *offp) + todrop, (size_t)(tcph->sum - todrop));
				}

			/*
			 *  SEQ �� SDU Ĺ��Ĵ�����롣
			 */
			tcph->seq +=     todrop;
			tcph->sum -= (uint16_t)todrop;	/* tcph->sum �� TCP �� SDU Ĺ */

			/*
			 *  �۵ޥݥ��󥿤�Ĵ�����롣
			 */
			if (tcph->urp > todrop)
				tcph->urp -= (uint16_t)todrop;
			else {
				tcph->flags &= ~TCP_FLG_URG;
				tcph->urp = 0;
				}

			NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DUP_SEGS], 1);
			}

		/*  
		 *  �⤷�桼������������λ������ˡ��ǡ������������
		 *  ���ϡ�RST �����롣
		 */
		if (cep->fsm_state == TCP_FSM_LAST_ACK && tcph->sum > 0) {	/* tcph->sum �� TCP �� SDU Ĺ */
			cep = tcp_close(cep);
			goto reset_drop;
			}

		/*
		 *  �����������Ȥ�����������ɤ�Ķ������ϡ�
		 *  Ķ����ʬ���롣
		 *
		 *       <---------- rcv_wnd --------->
		 *       rcv_nxt                      (rcv_nxt + rcv_wnd)
		 *       v                            v
		 *  -----+----------------------------+-----
		 *       |                            |
		 *  -----+----------------------------+-----
		 *                    +----------------------+
		 *                    |               |******|
		 *                    +----------------------+
		 *                    ^                      ^
		 *                    seq                    seq + len
		 *                                     <-----> ������롣
		 */
		todrop = (tcph->seq + tcph->sum) - (cep->rcv_nxt + cep->rcv_wnd);	/* tcph->sum �� TCP �� SDU Ĺ */
		if (todrop > 0) {
			if (todrop > tcph->sum) {					/* tcph->sum �� TCP �� SDU Ĺ */
				/*
				 *  �������� SDU �����Ƥ�����������ɤ�Ķ�����硣
				 *
				 *  TIME_WAIT ��ˡ���������³�׵�����������
				 *  �Ť���³���˴�������������³�򳫻Ϥ��롣
				 *  ��������SEQ �������ʤ�Ǥ��ʤ���Фʤ�ʤ���
				 */
				if ((tcph->flags & TCP_FLG_SYN) &&
				    cep->fsm_state == TCP_FSM_TIME_WAIT &&
				    SEQ_GT(tcph->seq, cep->rcv_nxt)) {
					iss = cep->snd_nxt + TCP_ISS_INCR();
					tcp_close(cep);
					syscall(dly_tsk(0));
					goto find_cep;
				    	}

				/*
				 *  ����������ɤ� 0 �ǡ��������� SEQ ��
				 *  ��������Ԥ��Ƥ���Ǿ��� SEQ �����פ����Ȥ���
				 *  ACK ���֤�������ʳ��ϥǡ������˴�����ACK ���֤���
				 */
				if (cep->rcv_wnd == 0 && (tcph->seq == cep->rcv_nxt || tcph->sum == 0)) {
					cep->flags |= TCP_CEP_FLG_ACK_NOW;
					}
				else if (drop_after_ack(input, cep, *offp) == RET_RST_DROP)
					goto reset_drop;
				else {
					return IPPROTO_DONE;
					}
				}
			tcph->sum -= (uint16_t)todrop;	/* tcph->sum �� TCP �� SDU Ĺ */
			tcph->flags &= ~(TCP_FLG_PUSH | TCP_FLG_FIN);
			}

		/*
		 *  �⤷��SYN �����åȤ���Ƥ���С�
		 *  ���顼�ʤΤ� RST �����ꡢ��³���˴����롣
		 */
		if (tcph->flags & TCP_FLG_SYN) {
			cep->net_error = EV_CNRST;
			cep = tcp_drop(cep, E_CLS);
			goto reset_drop;
			}

		/*
		 *  �⤷��ACK �����åȤ���Ƥ��ʤ����ϡ�
		 *  ���֤� SYN �����Ѥߤ�
		 *  SYN ���������褦�Ȥ��Ƥ���С�������³���뤬��
		 *  ����ʳ��ϥ������Ȥ��˴����ƽ�λ���롣
		 */
		if ((tcph->flags & TCP_FLG_ACK) == 0) {
			if (!(cep->fsm_state == TCP_FSM_SYN_RECVD || (cep->flags & TCP_CEP_FLG_NEED_SYN)))
				goto drop;
			}
		else {
			/*
			 * ACK �ν���
			 */
			ret = proc_ack1(input, cep, *offp, &needoutput);
			if (ret == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}

/* step 6 */

	/* ����������ɤ򹹿����롣*/
	if (update_wnd(tcph, cep) == true)
		needoutput = true;

	/* �۵ޥǡ�����������롣*/
	proc_urg(tcph, cep);

/* do data */

	/*
	 *  SDU �����뤫��FIN ��̤�����ξ��֤ǡ��ǽ�� FIN ����������Ȥ���
	 *  �����������ȥ��塼�� net_buf ���ɲä��롣
	 *  ����ʳ��ξ��ϡ��������Ȥ��˴����롣
	 */
	flags = tcph->flags;
	if ((tcph->sum > 0 || (flags & TCP_FLG_FIN)) &&		/* tcph->sum �� TCP �� SDU Ĺ */
	    TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {
		flags = reassemble(input, cep, *offp, flags);
		}
	else {
		syscall(rel_net_buf(input));
		flags &= ~TCP_FLG_FIN;
		}

	/*
	 *  FIN ����������饳�ͥ������򥯥������롣
	 */
	if (flags & TCP_FLG_FIN)
		close_connection(cep, &needoutput);

	/* ���Ϥ�Ԥä��彪λ���롣*/
	if (needoutput == true || (cep->flags & TCP_CEP_FLG_ACK_NOW)) {
		/* ������ؼ����롣*/
		cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}

	return IPPROTO_DONE;

reset_drop:
	/*
	 *  RST ��������
	 */

	if ((tcph->flags & TCP_FLG_RST) || IN_IS_NET_ADDR_MULTICAST(&iph->dst))
		goto drop;

	/* �ۥ��ȥ�����������ͥåȥ�������������᤹��*/

	HTONS(tcph->sport);
	HTONS(tcph->dport);

	if (cep == NULL)
		rbfree = 0;
	else
		rbfree = cep->rbufsz - cep->rwbuf_count;

	if (tcph->flags & TCP_FLG_ACK) {
		tcp_respond(input, cep, 0, tcph->ack, rbfree, TCP_FLG_RST);
		}
	else {
		if (tcph->flags & TCP_FLG_SYN)
			tcph->sum ++;		/* tcph->sum �� SDU Ĺ */
		tcp_respond(input, cep, tcph->seq + tcph->sum, 0, rbfree, TCP_FLG_RST | TCP_FLG_ACK);
		}

	/* input �� tcp_respoond ���ֵѤ���롣*/
	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_RSTS], 1);
	NET_COUNT_MIB(tcp_stats.tcpOutRsts, 1);
	return IPPROTO_DONE;

drop:
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DROP_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpInErrs, 1);
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif	/* of #ifdef SUPPORT_TCP */
