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
 *  @(#) $Id: tcp_subr.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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

#include <stdarg.h>
#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <syssvc/serial.h>
#include <syssvc/logtask.h>
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

/*
 *  �����ѿ�
 */

/*
 *  TCP �� SEQ �ν���͡��ץ���ब��ư���ơ��ǽ�� TCP �������Ȥ�
 *  ����������Ȥ��ˡ�get_tim() �ˤ���������롣
 */
T_TCP_SEQ tcp_iss = 0;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

T_TCP_STATS tcp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ɽ��ѿ�
 */

static uint16_t tcp_port_auto = TCP_PORT_FIRST_AUTO;	/* ��ư��������ֹ�	*/

/*
 *  tcp_free_reassq -- �����ƹ������塼�Υͥåȥ���Хåե���������롣
 *
 *    ���:
 *      ɬ�פǤ���С����δؿ���ƤӽФ����ˡ��̿�ü�����å�����
 *      ��ä��塢�������ɬ�פ����롣
 */

void
tcp_free_reassq (T_TCP_CEP *cep)
{
	T_NET_BUF	*q, *nq;

	for (q = cep->reassq; q != NULL; q = nq) {
		nq = GET_TCP_Q_HDR(q, GET_TCP_IP_Q_HDR(q)->thoff)->next;
		syscall(rel_net_buf(q));
		}
	cep->reassq  = NULL;
	NET_COUNT_TCP(net_count_tcp[NC_TCP_FREE_RCV_QUEUE],   1);
	}

/*
 *  tcp_alloc_auto_port -- ��ư������ƥݡ����ֹ�����ꤹ�롣
 */

void
tcp_alloc_auto_port (T_TCP_CEP *cep)
{
	int_t		ix;
	uint16_t	portno;

	while (true) {
		portno = tcp_port_auto ++;
		if (tcp_port_auto > TCP_PORT_LAST_AUTO)
			tcp_port_auto = TCP_PORT_FIRST_AUTO;

#ifdef TCP_CFG_PASSIVE_OPEN

		for (ix = tmax_tcp_repid; ix -- > 0; ) {

#ifdef TCP_CFG_EXTENTIONS

			if (VALID_TCP_REP(&tcp_rep[ix]) && tcp_rep[ix].myaddr.portno == portno) {
				portno = TCP_PORTANY;
				break;
				}

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

			if (tcp_rep[ix].myaddr.portno == portno) {
				portno = TCP_PORTANY;
				break;
				}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

			}

#endif	/* of #ifdef TCP_CFG_PASSIVE_OPEN */

		if (portno != TCP_PORTANY) {

			syscall(wai_sem(SEM_TCP_CEP));
			for (ix = tmax_tcp_cepid; ix -- > 0; ) {
				if (VALID_TCP_CEP(&tcp_cep[ix]) && tcp_cep[ix].myaddr.portno == portno) {
					portno = TCP_PORTANY;
					break;
					}
				}

			if (portno != TCP_PORTANY) {
				cep->myaddr.portno = portno;
				syscall(sig_sem(SEM_TCP_CEP));
				return;
				}
			syscall(sig_sem(SEM_TCP_CEP));
			}
		}
	}

/*
 *  tcp_alloc_port -- ���ꤵ�줿�ݡ����ֹ�����ꤹ�롣
 */

ER
tcp_alloc_port (T_TCP_CEP *cep, uint16_t portno)
{
	int_t	ix;

	syscall(wai_sem(SEM_TCP_CEP));
	for (ix = tmax_tcp_cepid; ix -- > 0; )
		if (VALID_TCP_CEP(cep) && tcp_cep[ix].myaddr.portno == portno) {
			syscall(sig_sem(SEM_TCP_CEP));
			return E_PAR;
			}
	cep->myaddr.portno = portno;
	syscall(sig_sem(SEM_TCP_CEP));
	return E_OK;
	}

/*
 *  tcp_init -- TCP �⥸�塼��ν����
 */

void
tcp_init (void)
{
	timeout(tcp_slow_timo, NULL, TCP_SLOW_TMO);

#ifdef TCP_CFG_DELAY_ACK

	timeout(tcp_fast_timo, NULL, TCP_FAST_TMO);

#endif/* of #ifdef TCP_CFG_DELAY_ACK */
	}

/*
 * tcp_init_iss ���������ֹ���������롣
 */

void
tcp_init_iss (void)
{
	SYSTIM now;

#ifdef SUPPORT_ETHER

	T_IF_SOFTC	*ic;

	ic = IF_ETHER_NIC_GET_SOFTC();
	syscall(get_tim(&now));
	net_srand(now + (ic->ifaddr.lladdr[2] << 24)
	              + (ic->ifaddr.lladdr[3] << 16)
	              + (ic->ifaddr.lladdr[4] <<  8)
	              + (ic->ifaddr.lladdr[5]      ));

#else	/* of #ifdef SUPPORT_ETHER */

	syscall(get_tim(&now));
	net_srand(now);

#endif	/* of #ifdef SUPPORT_ETHER */

	tcp_iss = net_rand();
	}

/*
 *  tcp_close -- ���ͥ������������롣
 */

T_TCP_CEP *
tcp_close (T_TCP_CEP *cep)
{
	/* �����ޡ�����ߤ��롣*/
	tcp_cancel_timers(cep);

	/* 
	 *  �̿�ü�����å�����
	 *  �����ƹ������塼�Υͥåȥ���Хåե���������롣
	 */
	syscall(wai_sem(cep->semid_lock));
	tcp_free_reassq(cep);
	syscall(sig_sem(cep->semid_lock));

	/* ���֤�̤���Ѥˤ��롣*/
	cep->fsm_state = TCP_FSM_CLOSED;

	/*
	 * �ʲ��˴ط����ʤ��ե饰�򥯥ꥢ�����롣
	 * ��������������ɥХåե��ξʥ��ԡ���ǽ
	 * ��ưŪ���̿�ü���������������ǽ
	 */
	cep->flags &= (TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK | 
	               TCP_CEP_FLG_DYNAMIC       | TCP_CEP_FLG_VALID);

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->snd_nblk_tfn != TFN_TCP_UNDEF || cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {
		/* �Υ�֥�å��󥰥����� */

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		if (!IS_PTR_DEFINED(cep->callback))
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
		else {
			if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {
				ER_UINT len;

				switch (cep->rcv_nblk_tfn) {

				case TFN_TCP_ACP_CEP:
					/* TCP �̿�ü������TCP ���ո���������롣*/
					cep->rep = NULL;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_CLS);
					break;

				case TFN_TCP_RCV_BUF:

					/* ����������ɥХåե��ζ����ɥ쥹��������롣*/
					len = TCP_GET_RWBUF_ADDR(cep, cep->rcv_p_buf);

					/* �۾��������Υ��顼�����ꤹ�롣*/
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else if (cep->error < 0)
						len = cep->error;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);
					break;

				case TFN_TCP_RCV_DAT:

					/* ����������ɥХåե�����ǡ�������Ф���*/
					len = TCP_READ_RWBUF(cep, cep->rcv_data, (uint_t)cep->rcv_len);

					/* �۾��������Υ��顼�����ꤹ�롣*/
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else if (cep->error != E_OK)
						len = cep->error;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);
					break;

				case TFN_TCP_CLS_CEP:

					if (cep->error == E_TMOUT)
						(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_CLS);
					else
						(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)cep->error);
					break;

				default:
					syslog(LOG_WARNING, "[TCP] unexp TFN: %s.", in_strtfn((FN)cep->rcv_nblk_tfn));
					break;
					}

				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->rcv_tskid = TA_NULL;
				cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
				}

			if (cep->snd_nblk_tfn != TFN_TCP_UNDEF) {

				switch (cep->snd_nblk_tfn) {

				case TFN_TCP_CON_CEP:
					/* TCP �̿�ü������ TCP ���ո���������롣*/
					cep->rep = NULL;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)E_CLS);
					break;

				case TFN_TCP_SND_DAT:
				case TFN_TCP_GET_BUF:
					if (cep->error == E_TMOUT)
						(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)E_CLS);
					else
						(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)cep->error);
					break;

				default:
					syslog(LOG_WARNING, "[TCP] unexp TFN: %s.", in_strtfn((FN)cep->snd_nblk_tfn));
					break;
					}

				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

			}

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		if (!IS_PTR_DEFINED(cep->callback))
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
		else {
			if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {
				ER_UINT len;

				switch (cep->rcv_nblk_tfn) {

				case TFN_TCP_ACP_CEP:
					/* TCP �̿�ü������TCP ���ո���������롣*/
					cep->rep = NULL;
					len      = E_CLS;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);
					break;

				case TFN_TCP_RCV_BUF:

					/* ����������ɥХåե��ζ����ɥ쥹��������롣*/
					len = TCP_GET_RWBUF_ADDR(cep, cep->rcv_p_buf);

					/* �۾��������Υ��顼�����ꤹ�롣*/
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else if (cep->error < 0)
						len = cep->error;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);
					break;

				case TFN_TCP_RCV_DAT:

					/* ����������ɥХåե�����ǡ�������Ф���*/
					len = TCP_READ_RWBUF(cep, cep->rcv_data, (uint_t)cep->rcv_len);

					/* �۾��������Υ��顼�����ꤹ�롣*/
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else if (cep->error != E_OK)
						len = cep->error;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);
					break;

				case TFN_TCP_CLS_CEP:
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else
						len = cep->error;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);
					break;

				default:
					syslog(LOG_WARNING, "[TCP] unexp TFN: %s.", in_strtfn((FN)cep->rcv_nblk_tfn));
					break;
					}

				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->rcv_tskid = TA_NULL;
				cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
				}

			if (cep->snd_nblk_tfn != TFN_TCP_UNDEF) {
				ER_UINT len;

				switch (cep->snd_nblk_tfn) {

				case TFN_TCP_CON_CEP:
					/* TCP �̿�ü������ TCP ���ո���������롣*/
					cep->rep = NULL;
					len      = E_CLS;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);
					break;

				case TFN_TCP_SND_DAT:
				case TFN_TCP_GET_BUF:
					if (cep->error == E_TMOUT)
						len = E_CLS;
					else
						len = cep->error;
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);
					break;

				default:
					syslog(LOG_WARNING, "[TCP] unexp TFN: %s.", in_strtfn((FN)cep->snd_nblk_tfn));
					break;
					}

				/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

			}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		/* 
		 *  �̿�ü�����å�����
		 *  ������������ɥХåե����塼�Υͥåȥ���Хåե���������롣
		 */
		syscall(wai_sem(cep->semid_lock));
		TCP_FREE_RWBUFQ(cep);
		TCP_FREE_SWBUFQ(cep);
		syscall(sig_sem(cep->semid_lock));

		/* ̤���Ѥˤʤä����Ȥ��Τ餻�롣*/
		syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
		}
	else {	/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->snd_tskid = cep->rcv_tskid = TA_NULL;
		cep->snd_tfn   = cep->rcv_tfn   = TFN_TCP_UNDEF;

		/* 
		 *  �̿�ü�����å�����
		 *  ������������ɥХåե����塼�Υͥåȥ���Хåե���������롣
		 */
		syscall(wai_sem(cep->semid_lock));
		TCP_FREE_RWBUFQ(cep);
		TCP_FREE_SWBUFQ(cep);
		syscall(sig_sem(cep->semid_lock));

		/* ̤���Ѥˤʤä����Ȥ��Τ餻�롣*/
		syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));

		/*
		 * �����ϥ������򵯾����ơ�
		 * �������ԲĤˤʤä����Ȥ��Τ餻�롣
		 */
		syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));
		syscall(set_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	return NULL;
	}

/*
 *  tcp_drop -- TCP ��³���˴����롣
 */

T_TCP_CEP *
tcp_drop (T_TCP_CEP *cep, ER errno)
{
#ifdef SUPPORT_MIB

	if ((cep->fsm_state == TCP_FSM_SYN_SENT) || (cep->fsm_state == TCP_FSM_SYN_RECVD)) {
		NET_COUNT_MIB(tcp_stats.tcpAttemptFails, 1);
		}

#endif	/* of #ifdef SUPPORT_MIB */

	cep->error = errno;
	if (TCP_FSM_HAVE_RCVD_SYN(cep->fsm_state)) {
		cep->fsm_state = TCP_FSM_CLOSED;

		/* �����ȡ������女�ͥ����������Ǥ�ؼ����롣*/
		cep->flags |=  TCP_CEP_FLG_POST_OUTPUT | TCP_CEP_FLG_CLOSE_AFTER_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	else
		cep = tcp_close(cep);
	return cep;
	}

/*
 *  tcp_respond -- TCP ��ñ���å��������������롣
 */

void
tcp_respond (T_NET_BUF *output, T_TCP_CEP *cep,
             T_TCP_SEQ ack, T_TCP_SEQ seq, uint_t rbfree, uint8_t flags)
{
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	uint_t		win = 0;

	if ((flags & TCP_FLG_RST) == 0)
		win = rbfree;

	/*
	 *  output �� NULL �Ǥʤ���С���������Ϥ����������Ȥ�
	 *  net_buf �ǡ����Τޤ޺����Ѥ��롣
	 */
	if (output != NULL) {
		T_IN_ADDR	ipaddr;
		uint16_t		portno;

		/*
		 * IPv4 �Ǥϡ�IP �إå��Υ��ץ����������롣
		 * IPv6 �Ǥϡ���ĥ�إå��������롣
		 */
		if (IP_REMOVE_OPTIONS(output) != E_OK) {
			syscall(rel_net_buf(output));
			return;
			}

		iph  = GET_IP_HDR(output);

		/* IP ���ɥ쥹��򴹤��롣*/
		ipaddr = iph->src;
		iph->src = iph->dst;
		iph->dst = ipaddr;

#if defined(SUPPORT_INET6)

		/* �ȥ�ҥå����饹�ȥե���٥�򥯥ꥢ���롣*/
		iph->vcf = htonl(IP6_MAKE_VCF(IP6_VCF_V(ntohl(iph->vcf)), 0));

#endif	/* of #if defined(SUPPORT_INET6) */

		/* TCP SDU Ĺ�� 0 �ˤ��롣*/
		SET_IP_SDU_SIZE(iph, TCP_HDR_SIZE);

		tcph = GET_TCP_HDR(output, IF_IP_TCP_HDR_OFFSET);

		/* �ݡ����ֹ��򴹤��롣*/
		portno = tcph->sport;
		tcph->sport = tcph->dport;
		tcph->dport = portno;

		/* TCP �إå��˾�������ꤹ�롣*/
		tcph->doff = TCP_MAKE_DATA_OFF(TCP_HDR_SIZE);
		}
	
	/* cep �� NULL �Ǥ���С����⤷�ʤ��ǽ�λ���롣*/
	else if (cep == NULL)
		return;
	else {
		if (tcp_get_segment(&output, cep, 0,
		                    0, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
		                    NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF) != E_OK)
			return;
		tcph = GET_TCP_HDR(output, IF_IP_TCP_HDR_OFFSET);
		flags |= TCP_FLG_ACK;
		}

	tcph->seq   = htonl(seq);
	tcph->ack   = htonl(ack);
	tcph->win   = htons(win);
	tcph->flags = flags;
	tcph->urp   = tcph->sum = 0;

	/*
	 *  �����å���������ꤹ�롣
	 */
	tcph->sum = IN_CKSUM(output, IPPROTO_TCP, IF_IP_TCP_HDR_OFFSET, 
	                     (uint_t)GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET));

	/* �ͥåȥ���Хåե�Ĺ��Ĵ�����롣*/
	output->len = (uint16_t)GET_IF_IP_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET);

#ifdef TCP_CFG_TRACE

	tcp_output_trace(output, cep);

#endif	/* of #ifdef TCP_CFG_TRACE */

	/* �ͥåȥ���� (IP) �ν��ϴؿ���ƤӽФ���*/
	IP_OUTPUT(output, TMO_TCP_OUTPUT);
	}

/*
 *  tcp_set_header -- TCP �إå������ꤹ�롣
 */

void
tcp_set_header (T_NET_BUF *nbuf, T_TCP_CEP *cep, uint_t thoff, uint_t optlen)
{
	T_TCP_HDR	*tcph = GET_TCP_HDR(nbuf, thoff);

	/* TCP �إå��˾�������ꤹ�롣*/
	tcph->sport	= htons(cep->myaddr.portno);
	tcph->dport	= htons(cep->dstaddr.portno);
	tcph->doff	= TCP_MAKE_DATA_OFF(TCP_HDR_SIZE + optlen);
	tcph->sum	= tcph->flags = 0;
	}

/*
 *  tcp_get_segment -- TCP �������Ȥ���������إå������ꤹ�롣
 *
 *    �����	���顼������
 *    optlen	���ץ���󥵥�����4 �����ƥå�ñ��
 *    len	TCP SDU ������
 */

ER
tcp_get_segment (T_NET_BUF **nbuf, T_TCP_CEP *cep,
                 uint_t optlen, uint_t len, uint_t maxlen, ATR nbatr, TMO tmout)
{
	ER		error;

	/* IP �ǡ���������������롣*/
	if ((error = IN_GET_DATAGRAM(nbuf,
	                             (uint_t)(TCP_HDR_SIZE + optlen + len),
	                             (uint_t)(TCP_HDR_SIZE + maxlen),
	                             &cep->dstaddr.ipaddr,
	                             &cep->myaddr.ipaddr,
	                             IPPROTO_TCP, IP_DEFTTL, nbatr, tmout)) != E_OK) {
		syslog(LOG_WARNING, "[TCP] NET BUF busy,  len:%4d, CEP: %d.",
		                    (uint16_t)(TCP_HDR_SIZE + optlen + len), GET_TCP_CEPID(cep));
		return error;
		}

	/* TCP �إå��˾�������ꤹ�롣*/
	tcp_set_header(*nbuf, cep, IF_IP_TCP_HDR_OFFSET, optlen);

	return E_OK;
	}

/*
 *  tcp_can_send_more -- �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣
 */

ER
tcp_can_send_more (T_TCP_CEP *cep, FN fncd, TMO tmout)
{
	ER	error;

	/* �����Ǥ��뤫��CEP �� FSM ���֤򸫤롣*/
	if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state)) {
		if ((error = cep->error) == E_OK)
			error = E_OBJ;

#ifdef TCP_CFG_NON_BLOCKING

		/* �����ॢ���Ȥ�����å����롣*/
		if (tmout == TMO_NBLK) {	/* �Υ�֥�å��󥰥����� */

			if (!IS_PTR_DEFINED(cep->callback))
				error = E_OBJ;
			else {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				error = E_WBLK;
				}
			}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		}
	else {

#ifdef TCP_CFG_SWBUF_CSAVE

		error = E_OK;

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		if (!IS_PTR_DEFINED(cep->sbuf)) {

#ifdef TCP_CFG_NON_BLOCKING

			/* �����ॢ���Ȥ�����å����롣*/
			if (tmout == TMO_NBLK) {	/* �Υ�֥�å��󥰥����� */
				if (!IS_PTR_DEFINED(cep->callback))
					error = E_OBJ;
				else {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					/* ������Хå��ؿ���ƤӽФ���*/
					(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)E_OBJ);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					/* ������Хå��ؿ���ƤӽФ���*/
					error = E_OBJ;
					(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					error = E_WBLK;
					}
				}
			else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				error = E_OBJ;
			}
		else
			error = E_OK;

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		}

	return error;
	}

/*
 *  tcp_can_recv_more -- �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣
 *
 *  ���: �����
 *
 *	E_OK	������ǽ
 *	E_OBJ	��꤫�����Ǥ��줿�������顼��ȯ��������
 */

ER
tcp_can_recv_more (ER *error, T_TCP_CEP *cep, FN fncd, TMO tmout)
{
	/*
	 *  �����Ǥ��뤫��fsm_state �򸫤롣�����Ǥ��ʤ�����
	 *  Ĺ�� 0���ޤ��ϥ��顼���֤���
	 */
	if (!TCP_FSM_CAN_RECV_MORE(cep->fsm_state) &&
	    cep->rwbuf_count == 0 && cep->reassq == NULL) {
		*error = cep->error;

#ifdef TCP_CFG_NON_BLOCKING

		/* �����ॢ���Ȥ�����å����롣*/
		if (tmout == TMO_NBLK) {	/* �Υ�֥�å��󥰥����� */

			if (!IS_PTR_DEFINED(cep->callback))
				*error = E_OBJ;
			else {
#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)*error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* ������Хå��ؿ���ƤӽФ���*/
				(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				*error = E_WBLK;
				}
			}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/*
		 *  �̿�ü�����å����ơ�
		 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
		 */
		syscall(wai_sem(cep->semid_lock));
		TCP_FREE_RWBUFQ(cep);
		syscall(sig_sem(cep->semid_lock));

		return E_OBJ;
		}
	else {

#ifndef TCP_CFG_RWBUF_CSAVE

		if (!IS_PTR_DEFINED(cep->rbuf)) {

#ifdef TCP_CFG_NON_BLOCKING

			/* �����ॢ���Ȥ�����å����롣*/
			if (tmout == TMO_NBLK) {	/* �Υ�֥�å��󥰥����� */
				if (!IS_PTR_DEFINED(cep->callback))
					*error = E_OBJ;
				else {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					/* ������Хå��ؿ���ƤӽФ���*/
					(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)E_OBJ);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					/* ������Хå��ؿ���ƤӽФ���*/
					*error = E_OBJ;
					(*cep->callback)(GET_TCP_CEPID(cep), fncd, (void*)error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					*error = E_WBLK;
					}
				}
			else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				*error = E_OBJ;

			return E_OBJ;
			}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE */

		return E_OK;
		}
	}

/*
 *  tcp_wait_rwbuf -- ����������ɥХåե��˥ǡ���������Τ��Ԥġ�
 */

ER
tcp_wait_rwbuf (T_TCP_CEP *cep, TMO tmout)
{
	ER	error;
	FLGPTN	flag;

	if (cep->rwbuf_count == 0) {
		/* ����������ɥХåե��˥ǡ������ʤ���С����Ϥ�����ޤ��Ԥġ�*/
		while (cep->rwbuf_count == 0) {
			if ((error = twai_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY, TWF_ORW, &flag, tmout)) != E_OK) {
				return error;
				}
			syscall(clr_flg(cep->rcv_flgid, (FLGPTN)(~TCP_CEP_EVT_RWBUF_READY)));

			/*
			 *  �����Ǥ��뤫��fsm_state �򸫤롣�����Ǥ��ʤ����֤ǡ�
			 *  ����������ɥХåե���ʸ�����ʤ����Ͻ�λ���롣
			 */
			if (!TCP_FSM_CAN_RECV_MORE(cep->fsm_state) &&
			    cep->rwbuf_count == 0 && cep->reassq == NULL) {

				/*
				 *  �̿�ü�����å����ơ�
				 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
				 */
#ifdef TCP_CFG_RWBUF_CSAVE
#endif
				syscall(wai_sem(cep->semid_lock));
				TCP_FREE_RWBUFQ(cep);
				syscall(sig_sem(cep->semid_lock));

				return cep->error;
				}
			}
		}
	else
		syscall(clr_flg(cep->rcv_flgid, (FLGPTN)(~TCP_CEP_EVT_RWBUF_READY)));

	return E_OK;
	}

/*
 *  tcp_move_ra2rw -- �����ƹ������塼�Ǻƹ��������������Ȥ����������ɥХåե��˽񤭹��ࡣ
 */

uint8_t
tcp_move_ra2rw (T_TCP_CEP *cep, uint8_t flags)
{
	T_NET_BUF	*q;
	T_TCP_Q_HDR	*qhdr;

	/*
	 *  �����ǡ��������������ɥХåե��˽񤭹��ߡ�
	 *  rcv_nxt ��λ���� SEQ �����ʤ�롣
	 */
	if (TCP_FSM_HAVE_ESTABLISHED(cep->fsm_state)) {
		while (cep->reassq != NULL) {
			q = cep->reassq;
			qhdr = GET_TCP_Q_HDR(q, GET_TCP_IP_Q_HDR(q)->thoff);
			if (qhdr->seq != cep->rcv_nxt)
				break;

			/* ���Υ������Ȥ˿ʤࡣ*/
			cep->reassq = qhdr->next;

			/* FIN �ե饰�Τ߻Ĥ���*/
			flags &= TCP_FLG_FIN;

			/* �ǡ��������������ɥХåե��˽񤭹��ࡣ*/
			TCP_WRITE_RWBUF(cep, q, (uint_t)(GET_TCP_IP_Q_HDR(q)->thoff));
			}
		}
	if (cep->reassq != NULL) {
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		flags &= ~TCP_FLG_FIN;
		}
	return flags;
	}

/*
 *  tcp_write_raque -- �����������Ȥ�ƹ������ơ������ƹ������塼�˷Ҥ���
 */

uint8_t
tcp_write_raque (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags)
{
	T_NET_BUF	*new;
	T_NET_BUF	*p, *q, *nq;
	T_TCP_Q_HDR	*qhdr, *inqhdr = GET_TCP_Q_HDR(input, thoff);
	int32_t		len;

	/*  TCP �إå��ΰ��֤���¸���롣*/
	GET_TCP_IP_Q_HDR(input)->thoff = thoff;

	/*
	 *  MAX_TCP_REALLOC_SIZE �ʲ��ξ��ϡ������˥ͥåȥ���Хåե���
	 *  �����Ƥơ��ǡ����򥳥ԡ����롣
	 *  ���ΤȤ���IP �Υ��ץ����ʳ�ĥ�إå��ˤ� TCP �Υ��ץ����Ϻ�����롣
	 */
	len  = IF_IP_TCP_HDR_SIZE + inqhdr->slen;

	if (len <= MAX_TCP_REALLOC_SIZE) {

		/*
		 *  �ͥåȥ���Хåե������ݤǤ��ʤ��Ȥ��ϳ����Ƥʤ���
		 */
		if (tget_net_buf(&new, (uint_t)len, TMO_TCP_GET_NET_BUF) != E_OK)
			new = NULL;
		}
	else
		new = NULL;

	/*
	 *    inqhdr->seq               
	 *    |
	 *    |<------- inqhdr->slen ------->|
	 *    v                              v
	 *    +------------------------------+
	 *    |             input            |
	 *    +------------------------------+
	 *        ^                  ^
	 *        |<----- slen ----->|
	 *        |
	 *        soff
	 *
	 */
	inqhdr->soff = 0;

	/*
	 *  �����ɲä��륻�����Ȥ����(p)�ȸ�(q)�Υ������Ȥ�õ����
	 *
	 *    +-------------------------+
	 *    |            p            |
	 *    +-------------------------+
	 *    ^              +---------------------------+
	 *    p->seq         |            input          |
	 *                   +---------------------------+
	 *                   ^                      +-------------------------+
	 *                   inqhdr->seq            |            q            |
	 *                                          +-------------------------+
	 *                                          ^
	 *                                          q->seq
	 */
	for (q = cep->reassq, p = NULL; q != NULL; ) {
		qhdr = GET_TCP_Q_HDR(q, GET_TCP_IP_Q_HDR(q)->thoff);
		if (SEQ_GT(qhdr->seq, inqhdr->seq))
			break;
		p = q;
		q = qhdr->next;
		}

	/*
	 *  ��(p)�Υ������Ȥ�����С����ˡ������Ʊ���������Ȥ�
	 *  ���뤳�Ȥ⤢�롣���ξ��ϡ�������ʬ�ޤ������Ƥ��˴����롣
	 *
	 *    qhdr->seq
	 *    |
	 *    |<----- qhdr->slen ------>|
	 *    v                         v
	 *    +-------------------------+
	 *    |            p            |
	 *    +-------------------------+
	 *                    <--len -->
	 *                   +---------------------------+
	 *                   |            input          |
	 *                   +---------------------------+
	 *                   ^
	 *                   inqhdr->seq
	 */
	if (p != NULL) {
		qhdr = GET_TCP_Q_HDR(p, GET_TCP_IP_Q_HDR(p)->thoff);
		len = qhdr->seq + qhdr->slen - inqhdr->seq;
		if (len > 0) {

			/*
			 *  len �����Ǥ���С���(p) �Υ������ȤȺ����
			 *  �������Ȥ��ŤʤäƤ��롣
			 */
			if (len >= inqhdr->slen) {

				/*
				 *  len ������Υ������Ȥ�Ʊ���ʤ�
				 *  �ޤä���Ʊ���������ȤʤΤǲ��⤷�ʤ���
				 */
				if (new != NULL) {
					syscall(rel_net_buf(new));
					}

				syscall(rel_net_buf(input));
				return flags;
				}

			/*
			 *  �ɲä��륻�����Ȥ� SDU �� len ʬ���˵ͤ�롣
			 */
			inqhdr->seq  += len;
			inqhdr->soff += (uint16_t)len;
			inqhdr->slen -= (uint16_t)len;
			}
		}

	/*
	 *  ���塼�ˤĤʤ����ˡ��������ͥåȥ���Хåե��˥ǡ�����ܤ���
	 *  TCP �Υ��ץ����Ϻ�����롣
	 */
	if (new != NULL) {
		memcpy(new->buf, input->buf, (size_t)(thoff + TCP_HDR_SIZE));
		memcpy((uint8_t*)GET_TCP_HDR(new, thoff) + TCP_HDR_SIZE,
		                 GET_TCP_SDU(input, thoff), (size_t)(inqhdr->slen));
		syscall(rel_net_buf(input));
		input = new;
		inqhdr = GET_TCP_Q_HDR(input, thoff);
		inqhdr->doff = (uint8_t)TCP_MAKE_DATA_OFF(TCP_HDR_SIZE);
		}

	/*
	 *  �Ťʤ��(q)�Υ������Ȥ�Ĵ�����롣
	 *
	 *    inqhdr->seq
	 *    |
	 *    |<----- inqhdr->slen ---->|
	 *    v                         v
	 *    +-------------------------+
	 *    |          input          |
	 *    +-------------------------+
	 *                    <--len -->
	 *                   +---------------------------+
	 *                   |              q            |
	 *                   +---------------------------+
	 *                   ^
	 *                   qhdr->seq
	 */
	while (q != NULL) {
		qhdr = GET_TCP_Q_HDR(q, GET_TCP_IP_Q_HDR(q)->thoff);
		len = inqhdr->seq + inqhdr->slen - qhdr->seq;
		if (len <= 0)
			/* len ����ʤ�ŤʤäƤ��ʤ���*/
			break;
		else if (len < qhdr->slen) {

			/*
			 *  ���ǽŤʤäƤ��륻�����Ȥ� SDU �� len ʬ���˵ͤ�롣
			 *
			 *    inqhdr->seq
			 *    |
			 *    |<----- inqhdr->slen ---->|
			 *    v                         v
			 *    +-------------------------+
			 *    |          input          |
			 *    +-------------------------+
			 *                    <--len -->
			 *            +------+---------------------------+
			 *            |      |              q            |
			 *            +------+---------------------------+
			 *                   ^--------->
			 *                   qhdr->seq
			 *                   qhdr->soff
			 */
			qhdr->seq  += len;
			qhdr->soff += (uint16_t)len;
			qhdr->slen -= (uint16_t)len;
			break;
			}
		nq = qhdr->next;
		if (p)
			GET_TCP_Q_HDR(p, GET_TCP_IP_Q_HDR(p)->thoff)->next = nq;
		else
			cep->reassq = nq;
		syscall(rel_net_buf(q));
		q = nq;
		}

	if (p == NULL) {
		inqhdr->next = cep->reassq;
		cep->reassq = input;
		}
	else {
		inqhdr->next = GET_TCP_Q_HDR(p, GET_TCP_IP_Q_HDR(p)->thoff)->next;
		GET_TCP_Q_HDR(p, GET_TCP_IP_Q_HDR(p)->thoff)->next = input;
		}

	return tcp_move_ra2rw(cep, flags);
	}

/*
 *  tcp_rexmt_val -- ���������ॢ�����ͤ��֤���
 */

T_TCP_TIME
tcp_rexmt_val (T_TCP_CEP *cep)
{
	T_TCP_TIME val;

	val = ((cep->srtt >> (TCP_SRTT_SHIFT - TCP_DELTA_SHIFT)) + cep->rttvar) >> TCP_DELTA_SHIFT;
	if (val < TCP_TVAL_MIN)
		return TCP_TVAL_MIN;
	else
		return val;
	}

/*
 *  tcp_init_cep -- �̿�ü�����������롣
 */

void
tcp_init_cep (T_TCP_CEP *cep)
{
#ifdef TCP_CFG_RWBUF_CSAVE
	/*
	 * ����������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ˤ�����硢
	 * ����������ɥХåե������Ʋ�������ʤ����Ȥ�����Τǡ�
	 * �����ǲ������롣
	 */
	if (cep->rwbufq != NULL) {
		cep->rwbuf_count = 0;
		TCP_FREE_RWBUFQ(cep);
		}
#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

	memset((uint8_t*)cep + offsetof(T_TCP_CEP, timer), 0,
	       sizeof(T_TCP_CEP) - offsetof(T_TCP_CEP, timer));

	cep->sbuf_rptr	= cep->sbuf_wptr = cep->sbuf;
	cep->rbuf_rptr	= cep->rbuf_wptr = cep->rbuf;

	cep->maxseg	= DEF_TCP_SND_SEG;		/* �������祻�����ȥ�����		*/
	cep->srtt	= TCP_TVAL_SRTT_BASE;		/* ��餫�ʰ�ưʿ��			*/
	cep->rttvar	= ((TCP_TVAL_RTO_BASE - TCP_TVAL_SRTT_BASE) << TCP_RTTVAR_SHIFT) / 4;
							/* ��餫��ʬ��				*/
	cep->rxtcur	= TCP_TVAL_RTO_BASE;		/* ���ߤκ�����				*/
	cep->snd_cwnd	=  MAX_TCP_WIN_SIZE;		/* ���ԥ�����ɥ�����			*/
	cep->snd_ssthresh= MAX_TCP_WIN_SIZE;		/* ���ԥ�����ɥ�����(snd_cwnd)��	������	*/

	/*
	 * �ʲ��˴ط����ʤ��ե饰�򥯥ꥢ�����롣
	 * ��������������ɥХåե��ξʥ��ԡ���ǽ
	 * ��ưŪ���̿�ü���������������ǽ
	 */
	cep->flags &= (TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK | 
	               TCP_CEP_FLG_DYNAMIC       | TCP_CEP_FLG_VALID);

	/* ���ޥե����������롣*/
	sig_sem (cep->semid_lock);

	/* �ե饰���������롣*/
	syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));
	syscall(clr_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));
	}

/*
 *  tcp_notify -- ICMP ���顼�ν���
 */

void
tcp_notify (T_NET_BUF *input, ER error)
{
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	T_TCP_CEP	*cep;

	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, GET_TCP_HDR_OFFSET(input));

	if ((cep = tcp_find_cep(&iph->src, tcph->sport, &iph->dst, tcph->dport)) != NULL) {

		/*
		 *  ���ͥ�������ߺѤǡ��ۥ�����ã��ǽ���顼�ξ��ϡ�
		 *  �����ˤ��������롣
		 */
		if (cep->fsm_state == TCP_FSM_ESTABLISHED &&
		    (error == EV_NURCH || error == EV_HURCH || error == EV_HDOWN))
			return;

		/*
		 *  ���ͥ���������桢Ʊ�����顼���٤������������ϡ�
		 *  �Ԥ����֤��������б�����ؿ��˥��顼���֤����롣
		 */
		if (cep->fsm_state < TCP_FSM_ESTABLISHED && cep->rxtshift > 3 && cep->net_error != E_OK) {
			cep->error = E_CLS;
			tcp_close(cep);
			}
		else {
			cep->net_error = error;

			/* ������ؼ����롣*/
			cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}
		}
	}

/*
 *  tcp_find_cep -- �ݡ����ֹ椫�� TCP �̿�ü�������롣
 *
 *    ���: dstaddr �ϡ�
 *          TINET-1.2 ����ͥåȥ���Х��ȥ�������
 *          TINET-1.1 �ޤǤϡ��ۥ��ȥХ��ȥ�����
 */

T_TCP_CEP*
tcp_find_cep (T_IN_ADDR *dstaddr, uint16_t dstport, T_IN_ADDR *peeraddr, uint16_t peerport)
{
	T_TCP_CEP*	cep;
	
	/*
	 *  ���֤� SYN �����Ѥ߰ʸ�ϡ�
	 *  IP ���ɥ쥹�ȥݡ����ֹ椬���פ����̿�ü����õ�����롣
	 */
	for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; ) {
		if (cep->fsm_state >= TCP_FSM_SYN_SENT                    &&
		    IN_IS_DSTADDR_ACCEPT (&cep->myaddr.ipaddr,  dstaddr)  &&
		    IN_ARE_NET_ADDR_EQUAL(&cep->dstaddr.ipaddr, peeraddr) &&
		    dstport  == cep->myaddr.portno                        &&
		    peerport == cep->dstaddr.portno)
			return cep;
		}

	/* ��ư�����ץ�����̿�ü����õ�����롣*/	
	for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; ) {
		if (cep->fsm_state == TCP_FSM_LISTEN &&
		    IN_IS_DSTADDR_ACCEPT(&cep->myaddr.ipaddr, dstaddr) &&
		    dstport == cep->myaddr.portno)
			return cep;
		}

	return NULL;
	}

/*
 *  tcp_lock_cep -- TCP �̿�ü�����å����롣
 */

ER
tcp_lock_cep (ID cepid, T_TCP_CEP **p_cep, FN tfn)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK;

	*p_cep = NULL;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* TCP �̿�ü��������å����롣*/
	if (!VALID_TCP_CEP(cep)) {
		syscall(sig_sem(cep->semid_lock));
		return E_NOEXS;
		}

	/*
	 *  API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if (IS_TFN_TCP_RCV(tfn)) {
		if (cep->rcv_tfn != TFN_TCP_UNDEF ||
		    (tfn == TFN_TCP_ACP_CEP && cep->snd_tfn == TFN_TCP_CON_CEP)) 
			error = E_OBJ;
		else {
			get_tid(&(cep->rcv_tskid));
			cep->rcv_tfn = tfn;
			}
		}
	else {
		if (cep->snd_tfn != TFN_TCP_UNDEF ||
		    (tfn == TFN_TCP_CON_CEP && cep->rcv_tfn == TFN_TCP_ACP_CEP) ||
		    (tfn == TFN_TCP_CON_CEP && cep->rcv_tfn == TFN_TCP_CLS_CEP))
			error = E_OBJ;
		else {
			get_tid(&(cep->snd_tskid));
			cep->snd_tfn = tfn;
			}
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	*p_cep = cep;
	return error;
	}

#ifdef TCP_CFG_TRACE

#ifndef CONSOLE_PORTID
#define	CONSOLE_PORTID		LOGTASK_PORTID
#endif

/*
 *  ���ͥ������ξ���
 */

static const char tcp_strfsm[][3] = {
	{ 'C', 'D', '\0' },
	{ 'L', 'I', '\0' },
	{ 'S', 'S', '\0' },
	{ 'S', 'R', '\0' },
	{ 'E', 'S', '\0' },
	{ 'C', 'W', '\0' },
	{ 'F', '1', '\0' },
	{ 'C', 'G', '\0' },
	{ 'L', 'A', '\0' },
	{ 'F', '2', '\0' },
	{ 'T', 'W', '\0' },
	};

/*
 *  trace_putchar -- ���ꥢ��ݡ��Ȥؤ�ʸ������
 */

static void
trace_putchar (ID portid, char ch)
{
	serial_wri_dat(portid, &ch, 1);
	/*cpu_putc(ch);*/
	}

/*
 *  ���ꥢ��ݡ��Ȥؤν���ʸ������ϥ饤�֥��
 */

/*
 *  �����Ѵ��Τ�����Ѵ�ɽ
 */

static const char radhex[] = "0123456789abcdef";
static const char radHEX[] = "0123456789ABCDEF";

/*
 *  convert -- trace_printf �ο����Ѵ�
 */

static int_t
convert (ID portid, long_t val, int_t radix,
         const char *radchar, int_t width, bool_t minus, char padchar)
{
	char	digits[24];
	int_t	ix, pad, pchars;

	ix = 0;
	do {
		if (minus)
			digits[ix ++] = radchar[val % radix];
		else
			digits[ix ++] = radchar[(ulong_t)val % radix];
		val /= radix;
		} while (val != 0);

	if (minus)
		digits[ix ++] = '-';

	if (width > ix)
		pchars = width;
	else
		pchars = ix;

	for (pad = ix; pad < width; pad ++)
		trace_putchar(portid, padchar);

	while (ix -- > 0)
		trace_putchar(portid, digits[ix]);

	return pchars;
	}

/*
 *  trace_printf -- ���ꥢ��ݡ��Ȥؤν���ʸ�������
 */

static void
trace_printf (ID portid, const char *fmt, ...)
{
	va_list	ap;
	ulong_t	val;
	char	padchar, *str;
	int_t	ch, width, longflag;

	va_start(ap, fmt);
	while ((ch = *fmt ++) != '\0') {
		if (ch != '%') {		/* �񼰻���ʳ� */
			trace_putchar(portid, (char)ch);
			continue;
			}

		width = longflag = 0;
		padchar = ' ';
		if ((ch = *fmt ++) == '0') {	/* ��̷�� 0 */
			padchar = '0';
			ch = *fmt ++;
			}

		while ('0' <= ch && ch <= '9') {	/* ������ */
			width = width * 10 + ch - '0';
			ch = *fmt ++;
			}

		while (ch == 'l') {		/* long (long) �λ��� */
			longflag ++;
			ch = *fmt ++;
			}

		switch (ch) {
		case 'd':
			val = longflag ? (ulong_t)va_arg(ap, long_t)
			               : (ulong_t)va_arg(ap, int_t);
			if (val >= 0)
				convert(portid,  val, 10, radhex, width, false, padchar);
			else
				convert(portid, -val, 10, radhex, width, true, padchar);
			break;

		case 'u':
			val = longflag ? (ulong_t)va_arg(ap, ulong_t)
			               : (ulong_t)va_arg(ap, uint_t);
			convert(portid, val, 10, radhex, width, false, padchar);
			break;

		case 'x':
			val = longflag ? (ulong_t)va_arg(ap, ulong_t)
			               : (ulong_t)va_arg(ap, uint_t);
			convert(portid, val, 16, radhex, width, false, padchar);
			break;

		case 'X':
			val = longflag ? (ulong_t)va_arg(ap, ulong_t)
			               : (ulong_t)va_arg(ap, uint_t);
			convert(portid, val, 16, radHEX, width, false, padchar);
			break;

		case 'c':
			ch = va_arg(ap, int_t);
			trace_putchar(portid, (char)ch);
			break;

		case 's':
			str = va_arg(ap, char*);
			while ((ch = *str ++) != '\0')
				trace_putchar(portid, (char)ch);
			break;

		case '%':
			trace_putchar(portid, '%');
			break;

		case '0':
			fmt --;
			break;

		default:
			break;
			}

		}
	va_end(ap);
	}

/*
 *  TCP �ե饰ʸ����
 */

static char *
get_tcp_flag_str (char *buf, uint8_t flags)
{
	static char tcp_flag_str[] = "FSRPAU";

	int_t	bit, mask = 1;

	for (bit = 0; bit < sizeof(tcp_flag_str); bit ++) {
		buf[sizeof(tcp_flag_str) - bit - 1] = (char)((flags & mask) ? tcp_flag_str[bit] : '-');
		mask <<= 1;
		}
	buf[sizeof(tcp_flag_str)] = '\0';
	return buf;
	}

/*
 *  ���� TCP �إå��Υȥ졼������
 */

void
tcp_output_trace (T_NET_BUF *output, T_TCP_CEP *cep)
{
	SYSTIM		time;
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	char		buf[9];

	if (!(TCP_CFG_TRACE_LPORTNO == TCP_PORTANY || cep->myaddr.portno  == TCP_CFG_TRACE_LPORTNO) ||
	    !(TCP_CFG_TRACE_RPORTNO == TCP_PORTANY || cep->dstaddr.portno == TCP_CFG_TRACE_RPORTNO))
		return;

#if defined(SUPPORT_INET4)

	if (!(TCP_CFG_TRACE_IPV4_RADDR == IPV4_ADDRANY || cep->dstaddr.ipaddr == TCP_CFG_TRACE_IPV4_RADDR))
		return;

#endif	/* of #if defined(SUPPORT_INET4) */

	syscall(wai_sem(SEM_TCP_TRACE));
	syscall(get_tim(&time));
	iph  = GET_IP_HDR(output);
	tcph = GET_TCP_HDR(output, GET_TCP_HDR_OFFSET(output));
	if (time > 99999999)
		trace_printf(CONSOLE_PORTID, "=O%10d", time / 1000);
	else
		trace_printf(CONSOLE_PORTID, "=O%6d.%03d", time / 1000, time % 1000);
	if (cep == NULL)
		trace_printf(CONSOLE_PORTID, "=c:-- s:-- f:-----");
	else
		trace_printf(CONSOLE_PORTID, "=c:%2d s:%s f:%05x",
		                             GET_TCP_CEPID(cep),
		                             tcp_strfsm[cep->fsm_state], cep->flags);
	trace_printf(CONSOLE_PORTID, ":%s", get_tcp_flag_str(buf, tcph->flags));
	if (cep->fsm_state >= TCP_FSM_ESTABLISHED)
		trace_printf(CONSOLE_PORTID, " s:%10u a:%10u",
		                             ntohl(tcph->seq) - cep->iss,
		                             ntohl(tcph->ack) - cep->irs);
	else
		trace_printf(CONSOLE_PORTID, " s:%10u a:%10u",
		                             ntohl(tcph->seq), ntohl(tcph->ack));
	trace_printf(CONSOLE_PORTID, " w:%5d l:%4d>\n", 
	                             ntohs(tcph->win),
	                             GET_IP_SDU_SIZE(iph) - TCP_HDR_LEN(tcph->doff));
	syscall(sig_sem(SEM_TCP_TRACE));
	}

/*
 *  ���� TCP �إå��Υȥ졼������
 *
 *    ���: TCP �إå���ϡ����Ǥ˥ۥ��ȥХ��ȥ�����
 */

void
tcp_input_trace (T_NET_BUF *input, T_TCP_CEP *cep)
{
	SYSTIM		time;
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	char		buf[9];

	if (!(TCP_CFG_TRACE_LPORTNO == TCP_PORTANY || cep->myaddr.portno  == TCP_CFG_TRACE_LPORTNO) ||
	    !(TCP_CFG_TRACE_RPORTNO == TCP_PORTANY || cep->dstaddr.portno == TCP_CFG_TRACE_RPORTNO))
		return;

#if defined(SUPPORT_INET4)

	if (!(TCP_CFG_TRACE_IPV4_RADDR == IPV4_ADDRANY || cep->dstaddr.ipaddr == TCP_CFG_TRACE_IPV4_RADDR))
		return;

#endif	/* of #if defined(SUPPORT_INET4) */

	syscall(wai_sem(SEM_TCP_TRACE));
	syscall(get_tim(&time));
	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, GET_TCP_HDR_OFFSET(input));
	if (time > 99999999)
		trace_printf(CONSOLE_PORTID, "<I%10d", time / 1000);
	else
		trace_printf(CONSOLE_PORTID, "<I%6d.%03d", time / 1000, time % 1000);
	if (cep == NULL)
		trace_printf(CONSOLE_PORTID, "=c:-- s:-- f:-----");
	else
		trace_printf(CONSOLE_PORTID, "=c:%2d s:%s f:%05x",
		                             GET_TCP_CEPID(cep),
		                             tcp_strfsm[cep->fsm_state], cep->flags);
	trace_printf(CONSOLE_PORTID, ":%s", get_tcp_flag_str(buf, tcph->flags));
	if (cep->fsm_state >= TCP_FSM_SYN_RECVD)
		trace_printf(CONSOLE_PORTID, " a:%10u s:%10u", tcph->ack - cep->iss, tcph->seq - cep->irs);
	else
		trace_printf(CONSOLE_PORTID, " a:%10u s:%10u", tcph->ack, tcph->seq);
	trace_printf(CONSOLE_PORTID, " w:%5d l:%4d=\n", 
	                             tcph->win, GET_IP_SDU_SIZE(iph) - TCP_HDR_LEN(tcph->doff));
	syscall(sig_sem(SEM_TCP_TRACE));
	}

#endif	/* of #ifdef TCP_CFG_TRACE */

#endif	/* of #ifdef SUPPORT_TCP */
