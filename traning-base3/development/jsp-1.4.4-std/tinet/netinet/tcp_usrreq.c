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
 *  @(#) $Id: tcp_usrreq.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	From: @(#)tcp_usrreq.c	8.2 (Berkeley) 1/3/94
 * $FreeBSD: src/sys/netinet/tcp_usrreq.c,v 1.40.2.3 1999/08/29 16:29:57 peter Exp $
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
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
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
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#include <net/if_var.h>

#ifdef SUPPORT_TCP

/*
 *  IPv4 �� IPv6 ���ڤ��ؤ��ޥ���
 */

#if defined(SUPPORT_INET4)

#define TCP_CRE_REP	tcp_cre_rep
#define TCP_ACP_CEP	tcp_acp_cep
#define TCP_CON_CEP	tcp_con_cep

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_CRE_REP	tcp6_cre_rep
#define TCP_ACP_CEP	tcp6_acp_cep
#define TCP_CON_CEP	tcp6_con_cep

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  TINET ��饤�֥�경���ʤ����ϡ����Ƥε�ǽ��
 *  ���֥������ȥե�����˽��Ϥ��뤿�ᡢ�ޥ����ͭ���ˤ��롣
 */

#ifndef TCP_CFG_LIBRARY

#define __tcp_cre_rep
#define __tcp_del_rep
#define __tcp_cre_cep
#define __tcp_del_cep
#define __tcp_acp_cep
#define __tcp_con_cep
#define __tcp_sht_cep
#define __tcp_cls_cep
#define __tcp_snd_dat
#define __tcp_rcv_dat
#define __tcp_snd_oob
#define __tcp_rcv_oob
#define __tcp_get_buf
#define __tcp_snd_buf
#define __tcp_rcv_buf
#define __tcp_rel_buf
#define __tcp_can_cep
#define __tcp_set_opt
#define __tcp_get_opt

#endif	/* of #ifndef TCP_CFG_LIBRARY */

/*
 *  tcp_cre_rep -- TCP ���ո��������ڳ�ĥ��ǽ��
 */

#ifdef __tcp_cre_rep

#ifdef TCP_CFG_EXTENTIONS

ER
TCP_CRE_REP (ID repid, T_TCP_CREP *pk_crep)
{
	T_TCP_REP	*rep;
	ER		error;

	/* TCP ���ո� ID ������å����롣*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

	/* pk_crep �� NULL �ʤ饨�顼 */
	if (pk_crep == NULL)
		return E_PAR;

	/* TCP ���ո������롣*/
	rep = GET_TCP_REP(repid);

	/* TCP ���ո�����ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_TCP_REP(rep))
		return E_ID;

	/* ���ո����å����롣*/
	syscall(wai_sem(rep->semid_lock));

	/*
	 * TCP ���ո�������å����롣�����ѤߤǤ���Х��顼
	 */
	if (VALID_TCP_REP(rep))
		error = E_OBJ;
	else {

		/* TCP ���ո���������򥳥ԡ����롣*/
		rep->repatr = pk_crep->repatr;		/* ���ո�°��		*/
		rep->myaddr = pk_crep->myaddr;		/* ��ʬ�Υ��ɥ쥹	*/

		/* TCP ���ո��������Ѥߤˤ��롣*/
		rep->flags |= TCP_REP_FLG_VALID;
		error = E_OK;
		}

	/* ���ո��Υ�å��������롣*/
	syscall(sig_sem(rep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_cre_cep */

#ifdef __tcp_del_rep

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_find_cep_rep -- TCP ���ո����󥯤��Ƥ��� TCP �̿�ü�������롣
 */

static T_TCP_CEP*
tcp_find_cep_rep (T_TCP_REP* rep)
{
	T_TCP_CEP*	cep;

	for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; ) {
		if (cep->rep == rep)
			return cep;
		}

	return NULL;
	}

/*
 *  tcp_del_rep -- TCP ���ո��κ���ڳ�ĥ��ǽ��
 */


ER
tcp_del_rep (ID repid)
{
	T_TCP_CEP	*cep;
	T_TCP_REP	*rep;
	ER		error = E_OK;

	/* TCP ���ո� ID ������å����롣*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

	/* TCP ���ո������롣*/
	rep = GET_TCP_REP(repid);

	/* TCP ���ո�����ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_TCP_REP(rep))
		return E_ID;

	/* ���ո����å����롣*/
	syscall(wai_sem(rep->semid_lock));

	/* TCP ���ո�������å����롣̤�����ξ��ϥ��顼 */
	if (!VALID_TCP_REP(rep))
		error = E_NOEXS;
	else {
		if ((cep = tcp_find_cep_rep(rep)) != NULL) {
			/*
			 * ���Ǥ˼�ư�����ץ󤷤Ƥ���Ȥ�
			 *��tcp_acp_cep ���ƤФ�Ƥ���Ȥ��ˤϡ�
			 * tcp_acp_cep ��λ�����롣
			 */

			/* �̿�ü�����å����롣*/
			syscall(wai_sem(cep->semid_lock));

			/*
			 *  �̿�ü��������ո����������
			 *  ���٥�ȥե饰�򥯥��������ꤹ�롣
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			cep->error = E_DLT;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {
				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_DLT);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_DLT;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					}
				else
					error = E_OBJ;
				cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			cep->rcv_tskid = TA_NULL;
			cep->rcv_tfn   = TFN_TCP_UNDEF;

			/* �̿�ü���Υ�å��������롣*/
			syscall(sig_sem(cep->semid_lock));

			}
		else
			error = E_OK;

		/* TCP ���ո���̤�����ˤ��롣*/
		rep->flags &= ~TCP_REP_FLG_VALID;
		}

	/* ���ո��Υ�å��������롣*/
	syscall(sig_sem(rep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_del_rep */

/*
 *  tcp_cre_cep -- TCP �̿�ü���������ڳ�ĥ��ǽ��
 */

#ifdef __tcp_cre_cep

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_cre_cep (ID cepid, T_TCP_CCEP *pk_ccep)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* pk_ccep �� NULL �ʤ饨�顼 */
	if (pk_ccep == NULL)
		return E_PAR;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü������ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_TCP_CEP(cep))
		return E_ID;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * TCP �̿�ü��������å����롣�����ѤߤǤ���Х��顼
	 */
	if (VALID_TCP_CEP(cep))
		error = E_OBJ;
	else {

		/* TCP �̿�ü����������򥳥ԡ����롣*/
		cep->cepatr   = pk_ccep->cepatr;		/* �̿�ü��°��			*/
		cep->sbuf     = pk_ccep->sbuf;			/* �����ѥ�����ɥХåե�	*/
		cep->sbufsz   = pk_ccep->sbufsz;		/* �����ѥ�����ɥХåե�������	*/
		cep->rbuf     = pk_ccep->rbuf;			/* �����ѥ�����ɥХåե�	*/
		cep->rbufsz   = pk_ccep->rbufsz;		/* �����ѥ�����ɥХåե�������	*/
		cep->callback = (void*)pk_ccep->callback;	/* ������Хå�			*/

		/* TCP �̿�ü���������Ѥߤˤ��롣*/
		cep->flags |= TCP_CEP_FLG_VALID;
		error = E_OK;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_cre_cep */

/*
 *  tcp_del_cep -- TCP �̿�ü���κ���ڳ�ĥ��ǽ��
 */

#ifdef __tcp_del_cep

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_del_cep (ID cepid)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü������ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_TCP_CEP(cep))
		return E_ID;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * TCP �̿�ü��������å����롣�ʲ��ξ��ϥ��顼
	 * ��̤������
	 * �������档
	 */
	if (!VALID_TCP_CEP(cep))
		error = E_NOEXS;
	else if (cep->fsm_state != TCP_FSM_CLOSED)
		error = E_OBJ;
	else {

		/* TCP �̿�ü����̤�����ˤ��롣*/
		cep->flags &= ~TCP_CEP_FLG_VALID;
		error = E_OK;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_del_cep */

#ifdef TCP_CFG_PASSIVE_OPEN

/*
 *  tcp_acp_cep -- ��³�׵��Ԥ� (��ư�����ץ�)��ɸ�ൡǽ��
 */

#ifdef __tcp_acp_cep

ER
TCP_ACP_CEP (ID cepid, ID repid, T_IPEP *p_dstaddr, TMO tmout)
{
	T_TCP_REP	*rep;
	T_TCP_CEP	*cep;
	ER		error;
	FLGPTN		flag;

	/* TCP ���ո�������å����롣*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_dstaddr �� NULL �ʤ饨�顼 */
	if (p_dstaddr == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_dstaddr �� NULL ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (p_dstaddr == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_ACP_CEP)) != E_OK)
		return error;

	/* CEP �� FSM �����������֤Ǥʤ���Х��顼��*/
	if (cep->fsm_state != TCP_FSM_CLOSED) {
		error = E_OBJ;
		goto err_ret;
		}
	syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_CLOSED)));

	/* TCP �̿�ü�����������롣*/
	tcp_init_cep(cep);

	/* TCP ���ո������롣*/
	rep = GET_TCP_REP(repid);

#ifdef TCP_CFG_EXTENTIONS

	/* TCP ���ո����å����롣*/
	syscall(wai_sem(rep->semid_lock));

	/* TCP ���ո�������å����롣*/
	if (!VALID_TCP_REP(rep)) {
		syscall(sig_sem(rep->semid_lock));
		error = E_NOEXS;
		goto err_ret;
		}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/* TCP �̿�ü����TCP���ո���Ͽ���롣*/
	cep->rep = rep;

#ifdef TCP_CFG_EXTENTIONS

	/* TCP ���ո��Υ�å��������롣*/
	syscall(sig_sem(rep->semid_lock));

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/* TCP ���ո��Υ��ɥ쥹�򥳥ԡ����롣*/
	cep->myaddr = rep->myaddr;

	/* �̿�ü�������ꤹ�롣*/
	cep->fsm_state = TCP_FSM_LISTEN;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {
		/* �Υ�֥�å��󥰥����� */
		cep->p_dstaddr    = p_dstaddr;
		cep->rcv_nblk_tfn = TFN_TCP_ACP_CEP;
		return E_WBLK;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/*
		 *  FSM �� ESTABLISHED �ˤʤ�ޤ��Ԥġ�
		 *  FSM �� CLOSED �ˤʤä����ϡ����顼��ȯ���������Ȥ��̣���Ƥ��롣
		 */
		error = twai_flg(cep->est_flgid, (TCP_CEP_EVT_CLOSED |
		                                  TCP_CEP_EVT_ESTABLISHED), TWF_ORW, &flag, tmout);
		if (error == E_OK) {
			if (cep->error != E_OK)
				error = cep->error;
			else if (cep->fsm_state == TCP_FSM_CLOSED)
				error = E_TMOUT;
			}

		syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_ESTABLISHED)));

		if (error == E_OK) {
			/* ���Υ��ɥ쥹�򥳥ԡ����롣*/
			*p_dstaddr = cep->dstaddr;
			}
		else {
			/*
			 *  �̿�ü��������ո����������
			 *  ���٥�ȥե饰�򥯥��������ꤹ�롣
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_acp_cep */

#endif	/* of #ifdef TCP_CFG_PASSIVE_OPEN */

/*
 *  tcp_con_cep -- ��³�׵� (ǽư�����ץ�)��ɸ�ൡǽ��
 */

#ifdef __tcp_con_cep

ER
TCP_CON_CEP (ID cepid, T_IPEP *p_myaddr, T_IPEP *p_dstaddr, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER		error;
	FLGPTN		flag;

#ifdef TCP_CFG_NON_BLOCKING

	/*
	 *  p_dstaddr �ޤ��� p_myaddr �� NULL ����
	 *  �����褬�ޥ�����㥹�ȥ��ɥ쥹�ʤ饨�顼
	 */
	if (p_myaddr == NULL || p_dstaddr == NULL || IN_IS_ADDR_MULTICAST(&p_dstaddr->ipaddr))
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  p_dstaddr �ޤ��� p_myaddr �� NULL ��
	 *  �����褬�ޥ�����㥹�ȥ��ɥ쥹����
	 *  tmout �� TMO_NBLK �ʤ饨�顼
	 */
	if (p_myaddr == NULL || p_dstaddr == NULL ||
	    IN_IS_ADDR_MULTICAST(&p_dstaddr->ipaddr) || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_CON_CEP)) != E_OK)
		return error;

	/* CEP �� FSM �����������֤Ǥʤ���Х��顼��*/
	if (cep->fsm_state != TCP_FSM_CLOSED) {
		error = E_OBJ;
		goto err_ret;
		}
	syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_CLOSED)));

	/* ���������ֹ���������롣*/
	if (tcp_iss == 0)
		tcp_init_iss();

	/* �̿�ü�����������롣*/
	tcp_init_cep(cep);

	/*
	 *  p_myaddr �� NADR (-1) �ǤϤʤ����� IP ���ɥ쥹�� ANY �Ǥʤ���С�
	 *  ���ꤵ�줿 IP ���ɥ쥹�������Ƥ롣
	 */
	if (p_myaddr != NADR && !IN_IS_ADDR_ANY(&p_myaddr->ipaddr))
		cep->myaddr.ipaddr = p_myaddr->ipaddr;
	else {
		T_IN_IFADDR	*ia;

		if ((ia = IN_IFAWITHIFP(IF_GET_IFNET(), &p_dstaddr->ipaddr)) == NULL) {
			error = E_PAR;
			goto err_ret;
			}
		cep->myaddr.ipaddr = ia->addr;
		}

	/* �̿�ü�������ꤹ�롣*/
	cep->fsm_state = TCP_FSM_SYN_SENT;
	cep->dstaddr   = *p_dstaddr;
	cep->iss       = tcp_iss;
	cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_INIT;
	tcp_iss += TCP_ISS_INCR() / 2;
	init_send_seq(cep);

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {
		/* �Υ�֥�å��󥰥����� */
		cep->p_dstaddr    = p_dstaddr;
		cep->p_myaddr     = p_myaddr;
		cep->snd_nblk_tfn = TFN_TCP_CON_CEP;

		/* ���ͥ������γ��ߤ�ݥ��Ȥ��롣*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		return E_WBLK;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/*
		 *  p_myaddr �� NADR (-1) ����
		 *  ���ݡ����ֹ椬 TCP_PORTANY �ʤ顢��ư�ǳ�����Ƥ롣
		 */
		if (p_myaddr == NADR || p_myaddr->portno == TCP_PORTANY)
			tcp_alloc_auto_port(cep);
		else if ((error = tcp_alloc_port(cep, p_myaddr->portno)) != E_OK)
			goto err_ret;

		/* ���ͥ������γ��ߤ�ݥ��Ȥ��롣*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

		/*
		 *  ���٥�Ȥ� ESTABLISHED �ˤʤ�ޤ��Ԥġ�
		 *  ���٥�Ȥ� CLOSED �ˤʤä����ϡ����餫�Υ��顼��ȯ����������
		 *  ��³�׵᤬���ݤ��줿���Ȥ��̣���Ƥ��롣
		 */
		error = twai_flg(cep->est_flgid, (TCP_CEP_EVT_CLOSED |
		                                  TCP_CEP_EVT_ESTABLISHED), TWF_ORW, &flag, tmout);
		if (error == E_OK) {
			if (cep->error != E_OK)
				error = cep->error;
			else if (cep->fsm_state == TCP_FSM_CLOSED)
				error = E_CLS;
			}

		syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_ESTABLISHED)));

		if (error != E_OK) {
			/*
			 *  �̿�ü��������ո����������
			 *  ���٥�ȥե饰�򥯥��������ꤹ�롣
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_con_cep */

#ifdef __tcp_cls_cep

/*
 *  tcp_user_closed -- �桼������Υ��ͥ������γ���
 */

T_TCP_CEP *
tcp_user_closed (T_TCP_CEP *cep)
{
	switch (cep->fsm_state) {

	case TCP_FSM_CLOSED:		/* ������	*/
	case TCP_FSM_LISTEN:		/* ��ư�����ץ�	*/
		cep->fsm_state = TCP_FSM_CLOSED;
		cep = tcp_close(cep);
		break;

	case TCP_FSM_SYN_SENT:		/* ǽư�����ץ�SYN �����Ѥ�	*/
	case TCP_FSM_SYN_RECVD:		/* SYN ���������SYN �����Ѥ�	*/
		cep->flags |= TCP_CEP_FLG_NEED_FIN;
		break;

	case TCP_FSM_ESTABLISHED:	/* ���ͥ�������ߴ�λ	*/
		cep->fsm_state = TCP_FSM_FIN_WAIT_1;
		break;

	case TCP_FSM_CLOSE_WAIT:	/* ��꤫�� FIN ������APP �ν�λ�Ԥ� */
		cep->fsm_state = TCP_FSM_LAST_ACK;
		break;
		}

	if (cep != NULL && cep->fsm_state == TCP_FSM_FIN_WAIT_2)
		cep->timer[TCP_TIM_2MSL] = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL;
	return cep;
	}

/*
 *  tcp_cls_cep -- �̿�ü���Υ�������ɸ�ൡǽ��
 */

ER
tcp_cls_cep (ID cepid, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK;
	FLGPTN		flag;

#ifndef TCP_CFG_NON_BLOCKING

	/* tmout �� TMO_NBLK �ʤ饨�顼 */
	if (tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifndef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_CLS_CEP)) != E_OK)
		return error;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {				/* �Υ�֥�å��󥰥����� */

		if (!IS_PTR_DEFINED(cep->callback))
			error = E_OBJ;
		else if (cep->fsm_state == TCP_FSM_CLOSED) {	/* ���Ǥ˥���������Ƥ���Ȥ� */

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_CLS_CEP, E_OK);
			error = E_WBLK;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			ER	error = E_OK;

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_CLS_CEP, (void*)&error);
			error = E_WBLK;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			}
		else {
			/* NBLK ��API ��ǽ�����ɤ����ꤹ�롣*/
			cep->rcv_nblk_tfn = TFN_TCP_CLS_CEP;

			if ((cep = tcp_user_closed(cep)) != NULL) {	/* ���ͥ����������Ǥ��롣*/
				/* ���ǥ������Ƚ��Ϥ�ݥ��Ȥ��롣*/
				cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
				sig_sem(SEM_TCP_POST_OUTPUT);
				}

			/*  cep �� NULL ����äƤ������ϡ�
			 *  ���˥��ͥ���������Ǥ���Ƥ��뤳�Ȥ��̣���Ƥ��롣
			 *  �ޤ������ξ�祳����Хå��ؿ����ƤӽФ���Ƥ��롣
			 */
			return E_WBLK;
			}
		}
	else {							/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if ((cep = tcp_user_closed(cep)) == NULL) {	/* ���ͥ����������Ǥ��롣*/

			/*  cep �� NULL ����äƤ������ϡ�
			 *  ���˥��ͥ���������Ǥ���Ƥ��뤳�Ȥ��̣���Ƥ��롣
			 */
			return error;
			}
		else {
			/* ���ǥ������Ƚ��Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

			/* ���٥�ȥե饰�� CLOSED �ˤʤ�ޤ��Ԥġ�*/
			error = twai_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED, TWF_ORW, &flag, tmout);
			if (error == E_OK && cep->error != E_OK)
				error = cep->error;

			if (error != E_OK) {
				if (error == E_RLWAI) {
					/* tcp_cls_cep ������󥻥뤵�줿�Ȥ��ϡ�RST ���������롣*/
					tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una - 1, 
					            cep->rbufsz - cep->rwbuf_count, TCP_FLG_RST);
					}

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

				/* 
				 *  �̿�ü�����å�����
				 *  ������������ɥХåե����塼�Υͥåȥ���Хåե���������롣
				 */
				cep->rwbuf_count = 0;
				syscall(wai_sem(cep->semid_lock));
				TCP_FREE_RWBUFQ(cep);
				TCP_FREE_SWBUFQ(cep);
				syscall(sig_sem(cep->semid_lock));

				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				}
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_cls_cep */

#ifdef __tcp_sht_cep

/*
 *  tcp_sht_cep  -- �ǡ��������ν�λ��ɸ�ൡǽ��
 */

ER
tcp_sht_cep (ID cepid)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK;

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SHT_CEP)) != E_OK)
		return error;

	/* TCP �̿�ü���Υ��ͥ�����󤬳�Ω���֤Ǥʤ���Х��顼 */
	if (!TCP_FSM_HAVE_ESTABLISHED(cep->fsm_state)) {
		if ((error = cep->error) == E_OK)
			error = E_OBJ;
		}

	else if ((cep = tcp_user_closed(cep)) != NULL) {		/* ���ͥ����������Ǥ��롣*/

		/* ���ǥ������Ƚ��Ϥ�ݥ��Ȥ��롣*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}

	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_sht_cep */

#ifdef __tcp_snd_dat

/*
 *  tcp_snd_dat -- �ѥ��åȤ�������ɸ�ൡǽ��
 */

ER_UINT
tcp_snd_dat (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ����len < 0 �ʤ饨�顼 */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL��len < 0 ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_DAT)) != E_OK)
		return error;

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_SND_DAT, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {		/* �Υ�֥�å��󥰥����� */

		/* ����������ɥХåե��˶���������Х�����Хå��ؿ���ƤӽФ���*/
		if (!TCP_IS_SWBUF_FULL(cep)) {

		 	/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
			error = TCP_WRITE_SWBUF(cep, data, (uint_t)len);

			/* ���Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_data     = data;
			cep->snd_len      = len;
			cep->snd_nblk_tfn = TFN_TCP_SND_DAT;
			TCP_ALLOC_SWBUF(cep);

			return E_WBLK;
			}
		}
	else {		/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ����������ɥХåե��������Τ��Ԥġ�*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
		if ((error = TCP_WRITE_SWBUF(cep, data, (uint_t)len)) > 0) {

			/* �ǡ������������롣����������ɥХåե����ե�ΤȤ��϶���Ū���������롣*/
			if (TCP_IS_SWBUF_FULL(cep))
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;

			/* ���Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_snd_dat */

#ifdef __tcp_snd_oob

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_snd_oob -- �۵ޥǡ����������ڳ�ĥ��ǽ��
 */

ER_UINT
tcp_snd_oob (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ����len < 0 �ʤ饨�顼 */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL��len < 0 ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_OOB)) != E_OK)
		return error;

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_SND_OOB, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {		/* �Υ�֥�å��󥰥����� */

		/* ����������ɥХåե��˶���������Х�����Хå��ؿ���ƤӽФ���*/
		if (!TCP_IS_SWBUF_FULL(cep)) {

		 	/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
			error = TCP_WRITE_SWBUF(cep, data, (uint_t)len);

			/* �����۵ޥݥ��󥿤����ꤹ�롣*/
			cep->snd_up = cep->snd_una + cep->swbuf_count;

			/* ���Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_OOB, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_OOB, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_data     = data;
			cep->snd_len      = len;
			cep->snd_nblk_tfn = TFN_TCP_SND_OOB;
			TCP_ALLOC_SWBUF(cep);

			return E_WBLK;
			}
		}
	else {		/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ����������ɥХåե��������Τ��Ԥġ�*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
		if ((error = TCP_WRITE_SWBUF(cep, data, (uint_t)len)) > 0) {

			/* �����۵ޥݥ��󥿤����ꤹ�롣*/
			cep->snd_up = cep->snd_una + cep->swbuf_count;

			/* �ǡ������������롣����������ɥХåե����ե�ΤȤ��϶���Ū���������롣*/
			if (TCP_IS_SWBUF_FULL(cep))
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;

			/* ���Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_snd_oob */

#ifdef __tcp_get_buf

/*
 *  tcp_get_buf -- �����ѥХåե��γ�����ɸ�ൡǽ��
 */

ER_UINT
tcp_get_buf (ID cepid, void **p_buf, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_buf �� NULL �ʤ饨�顼 */
	if (p_buf == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_buf �� NULL ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (p_buf == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_GET_BUF)) != E_OK)
		return error;

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_GET_BUF, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {		/* �Υ�֥�å��󥰥����� */

		if (!TCP_IS_SWBUF_FULL(cep)) {

			/* ����������ɥХåե��˶���������Х�����Хå��ؿ���ƤӽФ���*/
			error = TCP_GET_SWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_GET_BUF, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_GET_BUF, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_p_buf    = p_buf;
			cep->snd_nblk_tfn = TFN_TCP_GET_BUF;
			TCP_ALLOC_SWBUF(cep);
			return E_WBLK;
			}
		}

	else {		/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ����������ɥХåե��������Τ��Ԥġ�*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ����������ɥХåե��ζ����ɥ쥹��������롣*/
		error = TCP_GET_SWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_get_buf */

#ifdef __tcp_snd_buf

/*
 *  tcp_snd_buf -- �Хåե���Υǡ�����������ɸ�ൡǽ��
 */

ER
tcp_snd_buf (ID cepid, int_t len)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* ��������Ĺ�� len ������å����롣*/
	if (len < 0)
		return E_PAR;

	/* ��������Ĺ��len �� 0 �Ǥ���С����⤷�ʤ�����롣*/
	if (len == 0)
		return E_OK;

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_BUF)) != E_OK)
		return error;

	/* ��������Ĺ�� len ������å����롣*/
	if (len > cep->get_buf_len) {
		error = E_OBJ;
		goto err_ret;
		}

	/* �����Ǥ��뤫��CEP �� FSM ���֤򸫤롣*/
	if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state)) {
		if ((error = cep->error) == E_OK)
			error = E_OBJ;
		goto err_ret;
		}

	/* ����������ɥХåե��Υǡ�����������ǽ�ˤ��롣*/
	TCP_SEND_SWBUF(cep, (uint_t)len);

	/* ���Ϥ�ݥ��Ȥ��롣*/
	cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_snd_buf */

#ifdef __tcp_rcv_dat

/*
 *  tcp_rcv_dat -- �ѥ��åȤμ�����ɸ�ൡǽ��
 */

ER_UINT
tcp_rcv_dat (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ����len < 0 �ʤ饨�顼 */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL��len < 0 ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_RCV_DAT)) != E_OK)
		return error;

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	if (tcp_can_recv_more(&error, cep, TFN_TCP_RCV_DAT, tmout) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {		/* �Υ�֥�å��󥰥����� */

		/* ����������ɥХåե��˥ǡ���������Х�����Хå��ؿ���ƤӽФ���*/
		if (cep->rwbuf_count > 0) {

			/* ����������ɥХåե�����ǡ�������Ф���*/
			len = TCP_READ_RWBUF(cep, data, (uint_t)len);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_DAT, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_DAT, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->rcv_data     = data;
			cep->rcv_len      = len;
			cep->rcv_nblk_tfn = TFN_TCP_RCV_DAT;
			return E_WBLK;
			}
		}
	else {		/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ����������ɥХåե��˥ǡ������ʤ���С����Ϥ�����ޤ��Ԥġ�*/
		if ((error = tcp_wait_rwbuf(cep, tmout)) != E_OK)
			goto err_ret;

		/* ����������ɥХåե�����ǡ�������Ф���*/
		error = TCP_READ_RWBUF(cep, data, (uint_t)len);

		/* ���˥�����ɥ����������Ѥ�ä����Ȥ��Τ餻�뤿����Ϥ�ݥ��Ȥ��롣*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rcv_dat */

#ifdef __tcp_rcv_oob

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_rcv_oob -- �۵ޥǡ����μ����ڳ�ĥ��ǽ��
 *
 *    ���: ����¦��ʣ�������ƥåȤΥǡ������������Ƥ⡢
 *          �۵ޥݥ��󥿤��ؤ� 1 �����ƥåȤΥǡ����Τ߼������롣
 */

ER_UINT
tcp_rcv_oob (ID cepid, void *data, int_t len)
{
	T_TCP_CEP	*cep;
	uint8_t		*urg;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* data �� NULL ����len < 0 �ʤ饨�顼 */
	if (data == NULL || len < 0)
		return E_PAR;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	/* �����Ǥ��뤫��fsm_state �򸫤롣*/
	if (!TCP_FSM_CAN_RECV_MORE(cep->fsm_state))
		return E_OBJ;

	/*
	 *  �۵ޥǡ�������Υ������Ȥ� TCP �إå���
	 *  ���ꤵ��Ƥ��ʤ���С��۵ޥǡ�����������Ƥ��ʤ���
	 */
	if (cep->urg_tcph == NULL)
		return E_OBJ;

	/* len == 0 �ʤ�Хåե������С��ե� */
	if (len == 0)
		return E_BOVR;

	/* �۵ޥݥ��󥿤��ؤ� 1 �����ƥåȤΥǡ������ɤ߼�롣*/
	urg = (uint8_t*)cep->urg_tcph + TCP_DATA_OFF(cep->urg_tcph->doff) + cep->urg_tcph->urp + TCP_CFG_URG_OFFSET;
	*(uint8_t*)data = *urg;

	/* �ɤ߼�ä��ǡ���������� SDU �����˵ͤ�롣*/
	memcpy(urg, urg + 1, cep->urg_tcph->sum - (cep->urg_tcph->urp + TCP_CFG_URG_OFFSET) - 1);

	/* tcp_rcv_oob() ���ƽФ��줿�����Τ餻�뤿��ˡ�NULL �����ꤹ�롣*/
	cep->urg_tcph = NULL;

	return 1;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_rcv_oob */

#ifdef __tcp_rcv_buf

/*
 *  tcp_rcv_buf -- ���������ǡ��������ä��Хåե��γ�����ɸ�ൡǽ��
 */

ER_UINT
tcp_rcv_buf (ID cepid, void **p_buf, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_buf �� NULL �ʤ饨�顼 */
	if (p_buf == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_buf �� NULL ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (p_buf == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_RCV_BUF)) != E_OK)
		return error;

	/* �����Ǥ��뤫���̿�ü���ξ��֤򸫤롣*/
	if (tcp_can_recv_more(&error, cep, TFN_TCP_RCV_DAT, tmout) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �����ॢ���Ȥ�����å����롣*/
	if (tmout == TMO_NBLK) {		/* �Υ�֥�å��󥰥����� */

		/* ����������ɥХåե��˥ǡ���������Х�����Хå��ؿ���ƤӽФ���*/
		if (cep->rwbuf_count > 0) {

		 	/* ����������ɥХåե��ζ����ɥ쥹��������롣*/
			error = TCP_GET_RWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_BUF, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* ������Хå��ؿ���ƤӽФ���*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_BUF, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->rcv_p_buf    = p_buf;
			cep->rcv_nblk_tfn = TFN_TCP_RCV_BUF;
			return E_WBLK;
			}
		}
	else {		/* ��Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ����������ɥХåե��˥ǡ������ʤ���С����Ϥ�����ޤ��Ԥġ�*/
		if ((error = tcp_wait_rwbuf(cep, tmout)) != E_OK) {
			cep->rwbuf_count = 0;
			goto err_ret;
			}

	 	/* ����������ɥХåե��Υ��ɥ쥹��������롣*/
		error = TCP_GET_RWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rcv_buf */

#ifdef __tcp_rel_buf

/*
 *  tcp_rel_buf -- �����ѥХåե��β�����ɸ�ൡǽ��
 */

ER
tcp_rel_buf (ID cepid, int_t len)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* ��������Ĺ�� len ������å����롣*/
	if (len < 0)
		return E_PAR;

	/*
	 *  CEP ���å�����API ��ǽ�����ɤȥ��������̻Ҥ�Ͽ���롣
	 *  ���Ǥ˵�Ͽ����Ƥ���С��ڥ�ǥ�����ʤΤǥ��顼
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_REL_BUF)) != E_OK)
		return error;

	/* ��������Ĺ�� len ������å����롣*/
	if (len > cep->rcv_buf_len) {
		error = E_OBJ;
		goto err_ret;
		}

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* ����������ɥХåե�����������������ƥåȤ������롣*/
	TCP_DROP_RWBUF(cep, (uint_t)len);

	/* tcp_rcv_buf �γ�����Ĺ��ꥻ�åȤ��롣*/
	cep->rcv_buf_len = 0;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* ���˥�����ɥ����������Ѥ�ä����Ȥ��Τ餻�뤿����Ϥ�ݥ��Ȥ��롣*/
	cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rel_buf */

#ifdef __tcp_can_cep

/*
 *  tcp_can_snd -- �ڥ�ǥ��󥰤��Ƥ��������Υ���󥻥�
 */

static ER
tcp_can_snd (T_TCP_CEP *cep, FN fncd)
{
	ER	error = E_OK;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  snd_tskid �� TA_NULL �ʤ顢
	 *  �ڥ�ǥ��󥰤��Ƥ��ʤ��Τǥ��顼
	 */
	if (cep->snd_tskid == TA_NULL)
		error = EV_NOPND;

	/* �ڥ�ǥ������ API ��ǽ�����ɤȰ��פ��ʤ���Х��顼 */
	else if (fncd != TFN_TCP_ALL && fncd != cep->snd_tfn)
		error = E_OBJ;

	/* �����򥭥�󥻥뤹�롣*/
	else {

		/* �����ƹ������塼�Υͥåȥ���Хåե���������롣*/
		tcp_free_reassq(cep);

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		cep->rwbuf_count = 0;
		TCP_FREE_RWBUFQ(cep);

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		TCP_FREE_SWBUFQ(cep);

#ifdef TCP_CFG_NON_BLOCKING

		if (cep->snd_nblk_tfn != TFN_TCP_UNDEF) {	/* �Υ�֥�å��󥰥����� */

			switch (cep->snd_nblk_tfn) {

			case TFN_TCP_CON_CEP:
				/*  �̿�ü��������ո���������롣*/
				cep->rep = NULL;
				cep->fsm_state = TCP_FSM_CLOSED;
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;

			case TFN_TCP_SND_DAT:
			case TFN_TCP_GET_BUF:
			case TFN_TCP_SND_OOB:
				break;
				}

			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)E_RLWAI);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				ER	error = E_RLWAI;

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else
				error = E_OBJ;
			cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			}
		else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			error = rel_wai(cep->snd_tskid);

		cep->snd_tskid = TA_NULL;
		cep->snd_tfn   = TFN_TCP_UNDEF;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_can_rcv -- �ڥ�ǥ��󥰤��Ƥ�������Υ���󥻥�
 */

static ER
tcp_can_rcv (T_TCP_CEP *cep, FN fncd)
{
	ER	error = E_OK;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  rcv_tskid �� TA_NULL �ʤ顢
	 *  �ڥ�ǥ��󥰤��Ƥ��ʤ��Τǥ��顼
	 */
	if (cep->rcv_tskid == TA_NULL)
		error = EV_NOPND;

	/* �ڥ�ǥ������ API ��ǽ�����ɤȰ��פ��ʤ���Х��顼 */
	else if (fncd != TFN_TCP_ALL && fncd != cep->rcv_tfn)
		error = E_OBJ;

	/* �����򥭥�󥻥뤹�롣*/
	else {

		/* �����ƹ������塼�Υͥåȥ���Хåե���������롣*/
		tcp_free_reassq(cep);

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		cep->rwbuf_count = 0;
		TCP_FREE_RWBUFQ(cep);

		/* ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣*/
		TCP_FREE_SWBUFQ(cep);

#ifdef TCP_CFG_NON_BLOCKING

		if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {	/* �Υ�֥�å��󥰥����� */

			switch (cep->rcv_nblk_tfn) {

			case TFN_TCP_ACP_CEP:
				/*
				 *  �̿�ü��������ո����������
				 *  ���٥�ȥե饰�򥯥��������ꤹ�롣
				 */
				cep->rep = NULL;
				cep->fsm_state = TCP_FSM_CLOSED;
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;

			case TFN_TCP_RCV_DAT:
			case TFN_TCP_RCV_BUF:
				break;

			case TFN_TCP_CLS_CEP:
				cep->fsm_state = TCP_FSM_CLOSED;
				tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una - 1,
				            cep->rbufsz - cep->rwbuf_count, TCP_FLG_RST);
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;
				}

			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_RLWAI);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				ER	error = E_RLWAI;

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else
				error = E_OBJ;
			cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
			}
		else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			error = rel_wai(cep->rcv_tskid);

		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = TFN_TCP_UNDEF;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_can_cep -- �ڥ�ǥ��󥰤��Ƥ�������Υ���󥻥��ɸ�ൡǽ��
 */

ER
tcp_can_cep (ID cepid, FN fncd)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK, snd_err, rcv_err;

	/* API ��ǽ�����ɤ�����å����롣*/
	if (!VALID_TFN_TCP_CAN(fncd))
		return E_PAR;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü��������å����롣*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	if (fncd == TFN_TCP_ALL) {		/* TFN_TCP_ALL �ν��� */
		snd_err = tcp_can_snd(cep, fncd);
		rcv_err = tcp_can_rcv(cep, fncd);

		/*
		 *  snd_err �� rcv_err �Τɤ���� EV_NOPND
		 *  �ʤ顢�ڥ�ǥ��󥰤��Ƥ��ʤ��Τǥ��顼
		 */
		if (snd_err == EV_NOPND && rcv_err == EV_NOPND)
			error = E_OBJ;
		else {
			if (snd_err == EV_NOPND)
				snd_err = E_OK;
			if (rcv_err == EV_NOPND)
				rcv_err = E_OK;

			if (snd_err != E_OK)
				error = snd_err;
			else if (rcv_err != E_OK)
				error = rcv_err;
			}
		}

	else if (IS_TFN_TCP_RCV(fncd)) {	/* ���������Υ���󥻥� */
		if ((error = tcp_can_rcv(cep, fncd)) == EV_NOPND)
			error = E_OBJ;
		}

	else {					/* ���������Υ���󥻥� */
		if ((error = tcp_can_snd(cep, fncd)) == EV_NOPND)
			error = E_OBJ;
		}

	return error;
	}

#endif	/* of #ifdef __tcp_can_cep */

/*
 *  tcp_set_opt -- TCP �̿�ü�����ץ���������ڳ�ĥ��ǽ��
 *
 *  ���: �����ǽ�� TCP �̿�ü�����ץ�����̵�����ᡢE_PAR ���֤���롣
 */

#ifdef __tcp_set_opt

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_TCP_CEP	*cep;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü��������å����롣*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_set_opt */

/*
 *  tcp_get_opt -- TCP �̿�ü�����ץ���������ڳ�ĥ��ǽ��
 *
 *  ���: �����ǽ�� TCP �̿�ü�����ץ�����̵�����ᡢE_PAR ���֤���롣
 */

#ifdef __tcp_get_opt

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_TCP_CEP	*cep;

	/* TCP �̿�ü�� ID ������å����롣*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �̿�ü�������롣*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �̿�ü��������å����롣*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_get_opt */

#endif	/* of #ifdef SUPPORT_TCP */
