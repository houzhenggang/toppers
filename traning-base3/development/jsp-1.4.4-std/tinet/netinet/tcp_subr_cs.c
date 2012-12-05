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
 *  @(#) $Id: tcp_subr_cs.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)tcp_subr.c	8.2 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_subr.c,v 1.49.2.4 1999/08/29 16:29:55 peter Exp $
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
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/in_itron.h>

#ifdef SUPPORT_TCP

#ifdef TCP_CFG_SWBUF_CSAVE

#ifndef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ʾ��
 *  ���������̿�ü��������������ɥХåե���cep->sbuf�ˤ��ͤˤ�ꡢ
 *  TCP �̿�ü���������������ɥХåե��ξʥ��ԡ���ǽ����Ѥ��뤫��
 *  ���Ѥ��ʤ������ڤ��ؤ��롣
 */

/*
 *  tcp_drop_swbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ������������ˡ�
 */

void
tcp_drop_swbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_drop_swbuf_ncs(cep, len);
	else
		tcp_drop_swbuf_cs(cep, len);
	}

/*
 *  tcp_write_swbuf -- ����������ɥХåե��˥ǡ�����񤭹��������ˡ�
 */

ER_UINT
tcp_write_swbuf (T_TCP_CEP *cep, void *data, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_write_swbuf_ncs(cep, data, len);
	else
		return tcp_write_swbuf_cs(cep, data, len);
	}

/*
 *  tcp_read_swbuf -- ����������ɥХåե�����ǡ������ɤ߽Ф�������ˡ�
 */

void
tcp_read_swbuf (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_read_swbuf_ncs(cep, output, len, doff);
	}

/*
 *  tcp_wait_swbuf -- ����������ɥХåե������μ���������ɤ������Τ��Ԥġ�����ˡ�
 */

ER
tcp_wait_swbuf (T_TCP_CEP *cep, TMO tmout)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_wait_swbuf_ncs(cep, tmout);
	else
		return tcp_wait_swbuf_cs(cep, tmout);
	}

/*
 *  tcp_get_swbuf_addr -- ����������ɥХåե��ζ������ɥ쥹��������������ˡ�
 */

ER_UINT
tcp_get_swbuf_addr (T_TCP_CEP *cep, void **p_buf)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_get_swbuf_addr_ncs(cep, p_buf);
	else
		return tcp_get_swbuf_addr_cs(cep, p_buf);
	}

/*
 *  tcp_send_swbuf -- ����������ɥХåե��Υǡ�����������ǽ�ˤ��������ˡ�
 */

void
tcp_send_swbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_send_swbuf_ncs(cep, len);
	else
		tcp_send_swbuf_cs(cep, len);
	}

/*
 *  tcp_free_swbufq -- ����������ɥХåե����塼�β�����ؼ����������ˡ�
 */

void
tcp_free_swbufq (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->sbuf))
		tcp_free_swbufq_cs(cep);
	}

/*
 *  tcp_alloc_swbuf -- ����������ɥХåե��ѤΥͥåȥ���Хåե��γ�����Ƥ�ؼ����������ˡ�
 */

void
tcp_alloc_swbuf (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->sbuf))
		tcp_alloc_swbuf_cs(cep);
	}

/*
 *  tcp_is_swbuf_full -- ����������ɥХåե������դ������å����������ˡ�
 */

bool_t
tcp_is_swbuf_full (T_TCP_CEP *cep)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_is_swbuf_full_ncs(cep);
	else
		return tcp_is_swbuf_full_cs(cep);
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE_ONLY */

/*
 *  tcp_drop_swbuf_cs -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ�����������ѡˡ�
 */

void
tcp_drop_swbuf_cs (T_TCP_CEP *cep, uint_t len)
{

	/*����������ɥХåե�������ꤵ�줿�����ƥå�ʬ������롣*/
	cep->swbuf_count -= (uint16_t)len;

	/* �����Ѥߤǡ�ACK�Ԥ��λ��ϡ�ACK��λ���ѹ����롣*/
	if (len > 0 && (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT) {
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_ACKED;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_write_swbuf_cs -- ����������ɥХåե��˥ǡ�����񤭹�������ѡˡ�
 */

ER_UINT
tcp_write_swbuf_cs (T_TCP_CEP *cep, void *data, uint_t len)
{
	ER_UINT	error;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if ((error = net_buf_siz(cep->swbufq)) > 0 && error >= IF_IP_TCP_HDR_SIZE) {


		/*
		 *  +-----------+--------+---------+---------+
		 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
		 *  +-----------+--------+---------+---------+
		 *        14        20        20        n
		 *   <---------------- error --------------->
		 *              ^
		 *              net_buf �� 4 �����ƥåȶ����˥��饤�󤵤�Ƥ��롣
		 *
		 *  tcp_output �� ip_output �ǡ������å������׻�����Ȥ���
		 *  n �� 4 �����ƥåȶ����ˤʤ�褦�� SDU �θ��� 0 ��
		 *  �ѥåǥ��󥰤��롣����ʬ���θ��������������ɥХåե���
		 *  ������������ 4 �����ƥåȶ�����Ĵ�����롣
		 */
		error = (uint_t)(((error - IF_IP_TCP_HDR_SIZE) >> 2 << 2) + IF_IP_TCP_HDR_SIZE);

		if (len > cep->sbufsz - cep->swbuf_count)
			len = (uint_t)(cep->sbufsz - cep->swbuf_count);
		if (len > (error - IF_IP_TCP_HDR_SIZE))
			len = (uint_t)(error - IF_IP_TCP_HDR_SIZE);

		/* ����������ɥ������ˤ�ꥵ������Ĵ�����롣*/
		if (len > cep->snd_wnd) 
			len = cep->snd_wnd;
		if (len > cep->snd_cwnd)
			len = cep->snd_cwnd;

		/* ���κ�������������ȥ����� (maxseg) ��Ķ���ʤ��褦�ˤ��롣*/
		if (len > cep->maxseg) 
			len = cep->maxseg;

		/* �ǡ�����ܤ���*/
		memcpy(cep->sbuf_wptr, (void*)((uint8_t*)data), (size_t)len);
		cep->sbuf_wptr   += len;
		cep->swbuf_count += len;
		error             = len;

		/* �ͥåȥ���Хåե�Ĺ�� IP �ǡ��������Ĺ�����ꤹ�롣*/
		cep->swbufq->len = (uint16_t)(cep->swbuf_count + IF_IP_TCP_HDR_SIZE);
		SET_IP_SDU_SIZE(GET_IP_HDR(cep->swbufq), cep->swbuf_count + TCP_HDR_SIZE);

		/* �ե饰��������ǽ�����ꤹ�롣*/
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SEND_READY;
		}

	else {	/* ����������ɥХåե������� */
		syslog(LOG_WARNING, "[TCP] illegal window buff for send, CEP: %d, %4d < %4d.",
		                    GET_TCP_CEPID(cep), error, IF_IP_TCP_HDR_SIZE);

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		tcp_free_swbufq_cs(cep);
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_wait_swbuf_cs -- ����������ɥХåե������μ���������ɤ������Τ��Ԥġ����ѡˡ�
 */

ER
tcp_wait_swbuf_cs (T_TCP_CEP *cep, TMO tmout)
{
	FLGPTN	flag;
	SYSTIM	before, after;
	ER	error;
	int_t	win;


	/* ����������ɥХåե��������ƺѤߤǡ�����������н�λ���롣*/
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_READY &&
	    (cep->swbuf_count + IF_IP_TCP_HDR_SIZE) < net_buf_siz(cep->swbufq))
		return E_OK;

	/* ������Ǥ���С���λ����ޤ��Ե����롣*/
	while ((cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_FREE) {

		/* �����Ԥ��λ��֤� tmout ���鸺���롣*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR))
			syscall(get_tim(&before));

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY,
		                      TWF_ORW, &flag, tmout)) != E_OK)
			return error;
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/* �����Ԥ��λ��֤� tmout ���鸺���롣*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR)) {
			syscall(get_tim(&after));
			if (after - before > tmout)
				return E_TMOUT;
			tmout -= (TMO)(after - before);
			}

		/*
		 *  �����Ǥ��뤫��CEP �� FSM ���֤򸫤롣
		 *  ����������ɥХåե��������ޤ��ԤĴ֤ˡ�������ǽ�ˤʤä����ϡ�
		 *  ���ͥ���������Ǥ��줿���Ȥ��̣���Ƥ��롣
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state))
			return E_CLS;
		}

	/* ���μ���������ɤ��Ĥ��Ƥ�����ϡ������ޤ��Ե����롣*/
	while (true) {

		/*
		 *  snd_wnd:  ���μ�����ǽ������ɥ�����
		 *  snd_cwnd: ���ԥ�����ɥ�����
		 *
		 *  win: �ɤ��餫������������ɥ����������ꤹ�롣
		 */
		win = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;
		if (win > 0)
			break;

		/* �����Ԥ��λ��֤� tmout ���鸺���롣*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR))
			syscall(get_tim(&before));

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY,
		                      TWF_ORW, &flag, tmout)) != E_OK)
			return error;
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/* �����Ԥ��λ��֤� tmout ���鸺���롣*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR)) {
			syscall(get_tim(&after));
			if (after - before > tmout)
				return E_TMOUT;
			tmout -= (TMO)(after - before);
			}

		/*
		 *  �����Ǥ��뤫��CEP �� FSM ���֤򸫤롣
		 *  ����������ɥХåե��������ޤ��ԤĴ֤ˡ�������ǽ�ˤʤä����ϡ�
		 *  ���ͥ���������Ǥ��줿���Ȥ��̣���Ƥ��롣
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state))
			return E_CLS;
		}

	/* �ͥåȥ���Хåե���������롣*/
	if ((error = tcp_get_segment(&cep->swbufq, cep, 0,
	                             TCP_CFG_SWBUF_CSAVE_MIN_SIZE,
	                             TCP_CFG_SWBUF_CSAVE_MAX_SIZE - IF_IP_TCP_HDR_SIZE,
	                             NBA_SEARCH_DESCENT, tmout)) != E_OK)
		return error;

	/* ����������ɥХåե����������롣*/
	tcp_init_swbuf(cep);

	return E_OK;
	}

/*
 *  tcp_get_swbuf_addr_cs -- ����������ɥХåե��ζ������ɥ쥹�������������ѡˡ�
 */

ER_UINT
tcp_get_swbuf_addr_cs (T_TCP_CEP *cep, void **p_buf)
{
	ER_UINT	error;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if ((error = net_buf_siz(cep->swbufq)) > 0) {

		/*
		 *  +-----------+--------+---------+---------+
		 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
		 *  +-----------+--------+---------+---------+
		 *        14        20        20        n
		 *   <---------------- error --------------->
		 *              ^
		 *              net_buf �� 4 �����ƥåȶ����˥��饤�󤵤�Ƥ��롣
		 *
		 *  tcp_output �� ip_output �ǡ������å������׻�����Ȥ���
		 *  n �� 4 �����ƥåȶ����ˤʤ�褦�� SDU �θ��� 0 ��
		 *  �ѥåǥ��󥰤��롣����ʬ���θ��������������ɥХåե���
		 *  ������������ 4 �����ƥåȶ�����Ĵ�����롣
		 */
		error = (uint_t)(((error - IF_IP_TCP_HDR_SIZE) >> 2 << 2) - cep->swbuf_count);

		/* ����������ɥ������ˤ�ꥵ������Ĵ�����롣*/
		if (error > cep->snd_wnd) 
			error = cep->snd_wnd;
		if (error > cep->snd_cwnd)
			error = cep->snd_cwnd;

		/* ���κ�������������ȥ����� (maxseg) ��Ķ���ʤ��褦�ˤ��롣*/
		if (error > cep->maxseg) 
			error = cep->maxseg;

		/* ����������ɥХåե��ζ����ǡ���Ĺ�����ꤷ�������ͤ��֤���*/
		cep->get_buf_len = error;

		/* ����������ɥХåե��ζ������ɥ쥹����Ƭ�����ꤹ�롣*/
		*p_buf = cep->sbuf_wptr;
		}

	else {	/* �ͥåȥ���Хåե������� */

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		tcp_free_swbufq_cs(cep);
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_send_swbuf_cs -- ����������ɥХåե��Υǡ�����������ǽ�ˤ�������ѡˡ�
 */

void
tcp_send_swbuf_cs (T_TCP_CEP *cep, uint_t len)
{
	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	cep->sbuf_wptr  += len;
	cep->swbuf_count += len;

	/* �ͥåȥ���Хåե�Ĺ�� IP �ǡ��������Ĺ�����ꤹ�롣*/
	cep->swbufq->len = (uint16_t)(cep->swbuf_count + IF_IP_TCP_HDR_SIZE);
	SET_IP_SDU_SIZE(GET_IP_HDR(cep->swbufq), len + TCP_HDR_SIZE);

	/* tcp_get_buf �γ�����Ĺ��ꥻ�åȤ��롣*/
	cep->get_buf_len = 0;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* �ե饰��������ǽ�����ꤷ������Ū���������롣*/
	cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SEND_READY
	                                               | TCP_CEP_FLG_FORCE
	                                               | TCP_CEP_FLG_FORCE_CLEAR
	                                               | TCP_CEP_FLG_POST_OUTPUT;
	}

/*
 *  tcp_free_swbufq_cs -- ����������ɥХåե����塼�β�����ؼ���������ѡˡ�
 *
 *    ���:
 *      ɬ�פǤ���С����δؿ���ƤӽФ����ˡ��̿�ü�����å�����
 *      ��ä��塢�������ɬ�פ����롣
 */

void
tcp_free_swbufq_cs (T_TCP_CEP *cep)
{
	/* ����������ɥХåե��ζ����Ԥ�����ä���*/
	cep->flags &= ~TCP_CEP_FLG_WBCS_NBUF_REQ;

	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_FREE) {
		/*
		 *  ����������ɥХåե��������뤿��ˡ��ե饰�� ACK ��λ�����ꤷ��
		 *  TCP ���ϥ�������ư���롣
		 */
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_ACKED;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_alloc_swbuf_cs -- ����������ɥХåե��ѤΥͥåȥ���Хåե��γ�����Ƥ�ؼ���������ѡˡ�
 */

void
tcp_alloc_swbuf_cs (T_TCP_CEP *cep)
{
	cep->flags |= TCP_CEP_FLG_WBCS_NBUF_REQ;

	/*
	 *  ����������ɥХåե���̤���Ѥξ��Τߡ�
	 *  ����������ɥХåե��ѤΥͥåȥ���Хåե��γ�����Ƥ�ؼ����롣
	 */
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_FREE)
		sig_sem(SEM_TCP_POST_OUTPUT);
	}

/*
 *  tcp_is_swbuf_full_cs -- ����������ɥХåե������դ������å���������ѡˡ�
 */

bool_t
tcp_is_swbuf_full_cs (T_TCP_CEP *cep)
{
	return (cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_NBUF_READY ||
	        cep->swbuf_count >= cep->swbufq->len - IF_IP_TCP_HDR_SIZE;
	}

/*
 *  tcp_init_swbuf -- ����������ɥХåե���������������ѡˡ�
 *
 *    ���: tcp_get_segment �ǥͥåȥ���Хåե����������
 *          ľ��˸ƤӽФ����ȡ�
 */

void
tcp_init_swbuf (T_TCP_CEP *cep)
{
	/* ����������ɥХåե��λ����極������ꥻ�åȤ��롣*/
	cep->swbuf_count = 0;

	/* ����������ɥХåե��Υ��ɥ쥹�����ꤹ�롣*/
	cep->sbuf_wptr = cep->sbuf_rptr = GET_TCP_SDU(cep->swbufq, IF_IP_TCP_HDR_OFFSET);

	/* �ե饰�򡢥ͥåȥ���Хåե������ƺѤߤ����ꤹ�롣*/
	cep->flags = (cep->flags & ~(TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK))
	                         |   TCP_CEP_FLG_WBCS_NBUF_READY;
	}

/*
 *  tcp_push_res_nbuf -- �ͥåȥ���Хåե���ͽ�󤹤�����ѡˡ�
 */

T_NET_BUF *
tcp_push_res_nbuf (T_NET_BUF *nbuf)
{
	static int_t last_ix = 0;

	T_TCP_CEP	*cep;
 	int_t		ix, sel_ix;

	if (++ last_ix == tmax_tcp_cepid)
		last_ix = 0;
	sel_ix = ix = last_ix;
	do {
		cep = &tcp_cep[ix];
		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_PEND) {

			/* �ͥåȥ���Хåե���ͽ�󤹤롣*/
			cep->swbufq = nbuf;
			nbuf = NULL;

			/* �ե饰��ͽ������ꤹ�롣*/
			cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_NBUF_RSVD;
			sel_ix = ix;
			break;
			}
		if (++ ix == tmax_tcp_cepid)
			ix = 0;
		} while (ix != last_ix);

	last_ix = sel_ix;

	return nbuf;
	}

/*
 *  tcp_pull_res_nbuf -- ͽ�󤷤Ƥ���ͥåȥ���Хåե��֤������ѡˡ�
 */

T_NET_BUF *
tcp_pull_res_nbuf (ATR nbatr)
{
	T_NET_BUF	*nbuf;
	T_TCP_CEP	*cep;

	cep = GET_TCP_CEP(nbatr & NBA_ID_MASK);
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_RSVD) {

		/* ͽ�󤷤Ƥ���ͥåȥ���Хåե����֤���*/
		nbuf = cep->swbufq;
		cep->swbufq = NULL;

		/* TCP ���ϥ�������ư���롣*/
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	else
		nbuf = NULL;

	return nbuf;
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#ifdef TCP_CFG_RWBUF_CSAVE 

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ʾ��
 *  ���������̿�ü���μ���������ɥХåե���cep->rbuf�ˤ��ͤˤ�ꡢ
 *  TCP �̿�ü����˼���������ɥХåե��ξʥ��ԡ���ǽ����Ѥ��뤫��
 *  ���Ѥ��ʤ������ڤ��ؤ��롣
 */

/*
 *  tcp_drop_rwbuf -- ����������ɥХåե����塼�κǽ�Υͥåȥ���Хåե���������롣
 */

void
tcp_drop_rwbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		tcp_drop_rwbuf_ncs(cep, len);
	else
		tcp_drop_rwbuf_cs(cep, len);
	}

/*
 *  tcp_read_rwbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ�ɤ߽Ф���
 */

uint_t
tcp_read_rwbuf (T_TCP_CEP *cep, void *data, uint_t len)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		return tcp_read_rwbuf_ncs(cep, data, len);
	else
		return tcp_read_rwbuf_cs(cep, data, len);
	}

/*
 *  tcp_get_rwbuf_addr -- ����������ɥХåե��ζ������ɥ쥹��������롣
 */

uint_t
tcp_get_rwbuf_addr (T_TCP_CEP *cep, void **p_buf)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		return tcp_get_rwbuf_addr_ncs(cep, p_buf);
	else
		return tcp_get_rwbuf_addr_cs(cep, p_buf);
	}

/*
 *  tcp_free_rwbufq -- ����������ɥХåե����塼��������롣
 */

void
tcp_free_rwbufq (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->rbuf))
		tcp_free_rwbufq_cs(cep);
	}

/*
 *  tcp_write_rwbuf -- ����������ɥХåե��˥ǡ�����񤭹��ࡣ
 */

void
tcp_write_rwbuf (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		tcp_write_rwbuf_ncs(cep, input, thoff);
	else
		tcp_write_rwbuf_cs(cep, input, thoff);
	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE_ONLY */

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��ͭ��
 */

/*
 *  tcp_drop_rwbuf -- ����������ɥХåե����塼�κǽ�Υͥåȥ���Хåե���������롣
 */

void
tcp_drop_rwbuf_cs (T_TCP_CEP *cep, uint_t len)
{
	T_TCP_Q_HDR	*qhdr;

	if (cep->rwbufq != NULL) {

		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		cep->rwbuf_count -= len;

		/* �ͥåȥ���Хåե��˥ǡ�����̵���ʤä���������롣*/
		if (len == qhdr->slen) {
			T_NET_BUF *next;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

			cep->rwbufq_entries --;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

			next = qhdr->next;
			syscall(rel_net_buf(cep->rwbufq));
			cep->rwbufq = next;
			}
		else {
			qhdr->slen -= len;
			qhdr->soff += len;
			}
		}
	}

/*
 *  tcp_read_rwbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ�ɤ߽Ф���
 */

uint_t
tcp_read_rwbuf_cs (T_TCP_CEP *cep, void *data, uint_t len)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		blen, rlen = 0;
	uint8_t		*buf = (uint8_t*)data;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  ����������ɥХåե����塼�˥ͥåȥ���Хåե���̵���ʤ뤫
	 *  len �� 0 �ˤʤ�ޤ�³���롣
	 */
	while (cep->rwbufq != NULL && len > 0) {
		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);

		/*
		 *  len �ȼ���������ɥХåե����塼����Ƭ�ͥåȥ���Хåե���
		 *  �ǡ������ξ���������ܤ��ǡ������ˤ��롣
		 */
		if (len > qhdr->slen)
			blen = qhdr->slen;
		else
			blen = len;

		memcpy(buf,
		       GET_TCP_SDU(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff,
		       (size_t)blen);

		/*
		 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���
		 *  �ǡ�����̵���ʤä���������롣
		 */
		tcp_drop_rwbuf_cs(cep, blen);

		buf  += blen;
		rlen += blen;
		len  -= blen;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return rlen;
	}

/*
 *  tcp_get_rwbuf_addr -- ����������ɥХåե��ζ������ɥ쥹��������롣
 */

uint_t
tcp_get_rwbuf_addr_cs (T_TCP_CEP *cep, void **p_buf)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		len;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if (cep->rwbufq == NULL) {

		/* ����������ɥХåե������Ƴ�������Ƥ���Ȥ���*/
		*p_buf = NULL;
		len = 0;
		}
	else {

		/* ����������ɥХåե��Υǡ����Υ��ɥ쥹����Ƭ�����ꤹ�롣*/
		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		*p_buf = GET_TCP_SDU(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff;

		/* ����������ɥХåե��Υǡ���Ĺ��׻����롣*/
		len = qhdr->slen;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* ����������ɥХåե��Υǡ���Ĺ�����ꤷ�������ͤ��֤���*/
	cep->rcv_buf_len = len;
	return len;
	}

/*
 *  tcp_free_rwbufq -- ����������ɥХåե����塼��������롣
 *
 *    ���:
 *      ɬ�פǤ���С����δؿ���ƤӽФ����ˡ��̿�ü�����å�����
 *      ��ä��塢�������ɬ�פ����롣
 */

void
tcp_free_rwbufq_cs (T_TCP_CEP *cep)
{
	T_NET_BUF *next;

	if (cep->rwbuf_count == 0 && cep->reassq == NULL) {
		while (cep->rwbufq != NULL) {
			next = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff)->next;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

			cep->rwbufq_entries --;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

			syscall(rel_net_buf(cep->rwbufq));
			cep->rwbufq = next;
			}

		/* ����������ɥХåե��λ����極������ꥻ�åȤ��롣*/
		cep->rwbuf_count = 0;
		}
	}

/*
 *  tcp_write_rwbuf -- ����������ɥХåե��˥ǡ�����񤭹��ࡣ
 *
 *    ���:
 *	���� input �ϡ�T_TCP_Q_HDR �ˤ���󥯤��졢
 *	�¤��ؤ�����λ���Ƥ��ʤ���Фʤ�ʤ����ޤ���
 *	�ɲä���ǡ����ϡ�����������ɥХåե��˼��ޤ뤳�ȡ�
 */

void
tcp_write_rwbuf_cs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	T_TCP_Q_HDR	*qhdr;
	T_NET_BUF	**nextp;
	uint_t		inlen, last;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	inlen = qhdr->slen;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

	if (cep->rwbufq_entries >= TCP_CFG_RWBUF_CSAVE_MAX_QUEUES &&
	    inlen > 0 && (qhdr->flags & TCP_FLG_FIN) == 0) {

		/*
		 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ�Ρ�
		 *  ����������ɥХåե����塼�κ��票��ȥ����Ķ����Ȥ��ϡ�
		 *  ���������������Ȥ��˴����롣
		 *  ��������SDU Ĺ�� 0 �Υ������Ȥ� FIN �������Ȥ��˴����ʤ���
		 *  �ʤ�������˼��������������Ȥ��˴����뤿�ᡢ������������ä��롣
		 */
		syscall(rel_net_buf(input));

		/* �̿�ü���Υ�å��������롣*/
		syscall(sig_sem(cep->semid_lock));
		return;
		}

	cep->rwbufq_entries ++;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	/* �����Ѥߥ��������ֹ�򹹿����롣*/
	cep->rcv_nxt += inlen;

	/* �۵ޥǡ����� SDU ������Ԥ���*/
	if (qhdr->urp > 0 && inlen > 0) {
		inlen      -= qhdr->urp;
		qhdr->slen -= qhdr->urp;
		qhdr->urp   = 0;
		}

	last  = cep->rwbuf_count;

	/* �ͥåȥ���Хåե������������ɥХåե����塼�κǸ��Ϣ�뤹�롣*/
	qhdr->next = NULL;
	nextp = &cep->rwbufq;
	while (*nextp)
		nextp = &GET_TCP_Q_HDR(*nextp, GET_TCP_IP_Q_HDR(*nextp)->thoff)->next;
	*nextp = input;

	/*
	 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
	 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
	 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
	 */
	if (inlen > 0) {
		cep->rwbuf_count += inlen;
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_SEGS],   1);
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_OCTETS], inlen);
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->rcv_nblk_tfn == TFN_TCP_RCV_BUF) {	/* �Υ�֥�å��󥰥����� */

		int_t	len;

		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		len = qhdr->slen;

		/*
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if (len > 0 || inlen == 0) {

			/* tcp_rcv_buf �γ�����Ĺ�����ꤹ�롣*/
			cep->rcv_buf_len = len;

			/* ����������ɥХåե��Υ��ɥ쥹���֤���*/
			*cep->rcv_p_buf = GET_TCP_SDU(cep->rwbufq,
			                  GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff;

			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			if (len == 0) {

				/*
				 *  �̿�ü�����å����ơ�
				 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
				 */
				syscall(wai_sem(cep->semid_lock));
				tcp_free_rwbufq_cs(cep);
				syscall(sig_sem(cep->semid_lock));
				}
			}

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}

	else if (cep->rcv_nblk_tfn == TFN_TCP_RCV_DAT) {	/* �Υ�֥�å��󥰥����� */
		int_t	len;

		/* ����������ɥХåե�����ǡ�������Ф���*/
		if ((len = tcp_read_rwbuf_cs(cep, cep->rcv_data, (uint_t)cep->rcv_len)) > 0) {
			/* ���˥�����ɥ����������Ѥ�ä����Ȥ��Τ餻�뤿����Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

		/*
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if (len > 0 || inlen == 0) {

			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
			}

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if (inlen == 0 && cep->rwbuf_count == 0) {
			/*
			 *  ����������ɥХåե���Υǡ������� 0 �ǡ�
			 *  ��꤫�� FIN �ե饰���դ����������Ȥ���������Ȥ��ϡ�
			 *  �̿�ü�����å����ơ�
			 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
			 */
			syscall(wai_sem(cep->semid_lock));
			tcp_free_rwbufq_cs(cep);
			syscall(sig_sem(cep->semid_lock));
			}

		/*
		 *  ����������ɥХåե��˥ǡ��������뤫�� inlen == 0 �λ������ϥ������򵯾����롣
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if ((last == 0 && cep->rwbuf_count > 0) || inlen == 0) {
			syscall(set_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	}

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#endif	/* of #ifdef SUPPORT_TCP */
