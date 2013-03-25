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
 *  @(#) $Id: ppp_fsm.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * fsm->c - {Link, IP} Control Protocol Finite State Machine.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 *		PPP Finite State Machine for LCP/IPCP
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan, Inc.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/fsm->c,v 1.52.2.3 2000/08/19 09:30:03 brian Exp $
 *
 *  TODO:
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_timer.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_fsm.h>

#include <netinet/in.h>

#ifdef SUPPORT_PPP

/*
 *  �����ѿ�
 */

uint8_t	ppp_open_mode = PPP_OPEN_PASSIVE;	/* �����ץ����ư��⡼��	*/

/*
 *  �ؿ�
 */

static void fsm_sconfreq	(T_PPP_FSM *fsm, int_t retansmit);
static void fsm_rconfreq	(T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input);
static void fsm_rconfack	(T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input);
static void fsm_rconfnakrej	(T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input);
static void fsm_rtermreq	(T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input);
static void fsm_rtermack	(T_PPP_FSM *fsm, T_NET_BUF *input);
static void fsm_rcoderej	(T_PPP_FSM *fsm, T_NET_BUF *input);
static void fsm_stermreq	(T_PPP_FSM *fsm, uint8_t id);
static void fsm_timeout		(void *arg);

/*
 *  fsm_sconfreq -- Configure-Request ���������롣
 */

static void
fsm_sconfreq (T_PPP_FSM *fsm, int_t retransmit)
{
	T_NET_BUF	*output;
	uint16_t	len;

	if (!(fsm->state == PPP_FSM_REQSENT ||
	      fsm->state == PPP_FSM_ACKRCVD ||
	      fsm->state == PPP_FSM_ACKSENT)) {
		/* �ޤ��ͥ��򤷤Ƥ��ʤ������ץ�����ꥻ�åȤ��롣 */
		if (fsm->callbacks->resetci)
			(*fsm->callbacks->resetci)(fsm);
		fsm->failures = 0;
		}
	if (retransmit == 0) {
		/* �������ꥯ�����ȡ����������󥿤�ꥻ�åȤ��������� ID �����ꤹ�롣 */
		fsm->retrans = MAX_PPP_CONFIGURES;
		fsm->reqid   = ++ fsm->id;
		}

	fsm->seen_ack = 0;

	if (fsm->callbacks->cilen && fsm->callbacks->addci) {
		/* ��������ѥ��åȤ��롣 */
		len = (*fsm->callbacks->cilen)(fsm);

		syscall(get_net_buf(&output, len + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
		(*fsm->callbacks->addci)(fsm, output);

		/* ��������ѥ��åȤ��������롣 */
		IF_SET_PROTO(output, fsm->proto);
		ppp_cp_output(PPP_CONFREQ, fsm->reqid, output);

		-- fsm->retrans;
		timeout((FP)fsm_timeout, fsm, DEF_PPP_TIMEOUT);
		}
	}

/*
 *  fsm_rconfreq -- Configure-Request ����������Ȥ��ν���
 */

static void
fsm_rconfreq (T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input)
{
	T_NET_BUF	*output;
	uint16_t	code;

	switch (fsm->state) {
	case PPP_FSM_CLOSED:
		syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		ppp_cp_output(PPP_TERMACK, id, output);
		return;
		break;

	case PPP_FSM_CLOSING:
	case PPP_FSM_STOPPING:
		return;
		break;

	case PPP_FSM_OPENED:
		/* ����ؤ���ߤ��ơ��ͥ��˰ܤ롣 */
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm_sconfreq(fsm, 0);		/* �ǽ�� Configure-Request �����롣 */
		break;

	case PPP_FSM_STOPPED:
		/* ��꤫��ͥ������Ϥ��줿 */
		fsm_sconfreq(fsm, 0);		/* �ǽ�� Configure-Request �����롣 */
		fsm->state = PPP_FSM_REQSENT;
		break;

		}

	syscall(get_net_buf(&output, input->len));

	/* ��̥ץ�ȥ�����׵ᤵ�줿 Configure-Request �����롣 */
	if (fsm->callbacks->reqci != NULL)	/* �������������å����롣 */
		code = (*fsm->callbacks->reqci)(fsm, input, output);
	else if (output->len > sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR))
		code = PPP_CONFREJ;
	else
		code = PPP_CONFACK;

	/* ���� ACK, NAK �ޤ��� REJ ���������롣 */
	ppp_cp_output(code, id, output);

	if (code == PPP_CONFACK) {
		if (fsm->state == PPP_FSM_ACKRCVD) {
			untimeout((FP)fsm_timeout, fsm);
			fsm->state = PPP_FSM_OPENED;
			if (fsm->callbacks->up != NULL)
				(*fsm->callbacks->up)(fsm);
			}
		else
			fsm->state = PPP_FSM_ACKSENT;
		fsm->failures = 0;
		}
	else {
		/* ACK �� REJ ������ */
		if (fsm->state != PPP_FSM_ACKRCVD)
			fsm->state = PPP_FSM_REQSENT;
		if (code == PPP_CONFNAK)
			fsm->failures ++;
		}
	}

/*
 *  fsm_rconfnakrej -- Configure-NAK/REJ ����������Ȥ��ν���
 */

static void
fsm_rconfnakrej (T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input)
{
	int_t		ret = 0;
	T_NET_BUF	*output;

	/* ͽ������ ID �Ǥʤ�����NAK/REJ ��ͽ�����Ƥ��ʤ��Ȥ��Ͻ�λ���롣*/
	if (id != fsm->reqid || fsm->seen_ack) {
		syslog(LOG_WARNING, "[PPP/FSM] bad ID or unexp NAK/REJ.");
		return;
		}

	if (code == PPP_CONFNAK) {
		if (fsm->callbacks->nakci != NULL && (ret = (*fsm->callbacks->nakci)(fsm, input)) == 0) {
			syslog(LOG_WARNING, "[PPP/FSM] bad NAK.");
			return;
			}
		}
	else {
		if (fsm->callbacks->rejci != NULL && (ret = (*fsm->callbacks->rejci)(fsm, input)) == 0) {
			syslog(LOG_WARNING, "[PPP/FSM] bad REJ.");
			return;
			}
		}

	fsm->seen_ack = 1;

	switch (fsm->state) {
	case PPP_FSM_CLOSED:
	case PPP_FSM_STOPPED:
		syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		ppp_cp_output(PPP_TERMACK, id, output);
		return;
		break;

	case PPP_FSM_REQSENT:
	case PPP_FSM_ACKSENT:
		untimeout((FP)fsm_timeout, fsm);
		if (ret < 0)		/* �������� Conf-Req ����»������ NAK/REJ ���Ϥ�����*/
			fsm->state = PPP_FSM_STOPPED;
		else
			fsm_sconfreq(fsm, 0);
		break;

	case PPP_FSM_ACKRCVD:
		untimeout((FP)fsm_timeout, fsm);
		fsm_sconfreq(fsm, 0);
		fsm->state = PPP_FSM_REQSENT;
		break;

	case PPP_FSM_OPENED:
		/* �Ƶ�ư�����ͥ�����ľ����*/
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm_sconfreq(fsm, 0);
		fsm->state = PPP_FSM_REQSENT;
		break;
		}
	}

/*
 *  fsm_rconfack -- Configure-ACK ����������Ȥ��ν���
 */

static void
fsm_rconfack (T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input)
{
	T_NET_BUF	*output;

	/* ͽ������ ID �Ǥʤ�����ACK ��ͽ�����Ƥ��ʤ��Ȥ��Ͻ�λ���롣*/
	if (id != fsm->reqid || fsm->seen_ack) {
		syslog(LOG_WARNING, "[PPP/FSM] bad ID or unexp ACK.");
		return;
		}

	if (fsm->callbacks->ackci != NULL) {
		if ((*fsm->callbacks->ackci)(fsm, input) != true) {
			syslog(LOG_WARNING, "[PPP/FSM] bad ACK.");
			return;
			}
		}
	else if (input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)) != 0) {
		syslog(LOG_WARNING, "[PPP/FSM] bad ACK.");
		return;
		}

	fsm->seen_ack = 1;

	switch (fsm->state) {
	case PPP_FSM_CLOSED:
	case PPP_FSM_STOPPED:
		syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		ppp_cp_output(PPP_TERMACK, id, output);
		break;

	case PPP_FSM_REQSENT:
		fsm->state = PPP_FSM_ACKRCVD;
		fsm->retrans = MAX_PPP_CONFIGURES;
		break;

	case PPP_FSM_ACKRCVD:
		untimeout((FP)fsm_timeout, fsm);
		fsm_sconfreq(fsm, 0);
		fsm->state = PPP_FSM_REQSENT;
		break;

	case PPP_FSM_ACKSENT:
		untimeout((FP)fsm_timeout, fsm);
		fsm->state = PPP_FSM_OPENED;
		fsm->retrans = MAX_PPP_CONFIGURES;
		if (fsm->callbacks->up != NULL)
			(*fsm->callbacks->up)(fsm);
		break;

	case PPP_FSM_OPENED:
		/* �Ƶ�ư�����ͥ�����ľ����*/
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm_sconfreq(fsm, 0);
		fsm->state = PPP_FSM_REQSENT;
		break;

	default	:
		syslog(LOG_WARNING, "[PPP/FSM] unexp state: %d in recv Conf-ACK.", fsm->state);
		break;
		}

	}

/*
 *  fsm_rtermreq -- Terminate-Request ����������Ȥ��ν���
 */

static void
fsm_rtermreq (T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input)
{
	T_NET_BUF	*output;

	switch (fsm->state) {
	case PPP_FSM_ACKRCVD:
	case PPP_FSM_ACKSENT:
		fsm->state = PPP_FSM_REQSENT;
		break;

	case PPP_FSM_OPENED:
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm->retrans = 0;
		fsm->state = PPP_FSM_STOPPING;
		timeout((FP)fsm_timeout, fsm, DEF_PPP_TIMEOUT);
		break;
		}
	syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
	memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	ppp_cp_output(PPP_TERMACK, id, output);
	}

/*
 *  fsm_rtermack -- Terminate-ACK ����������Ȥ��ν���
 */

static void
fsm_rtermack (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	switch (fsm->state) {
	case PPP_FSM_CLOSING:
		untimeout((FP)fsm_timeout, fsm);
#if 0	/* �����ư��� CLOSED �����ܤ��롣*/
		fsm->state = PPP_FSM_CLOSED;
#else	/* of #if 0 */
		fsm->state = PPP_FSM_STOPPED;
#endif	/* of #if 0 */
		if (fsm->callbacks->finished != NULL)
			(*fsm->callbacks->finished)(fsm);
		break;

	case PPP_FSM_STOPPING:
		untimeout((FP)fsm_timeout, fsm);
		fsm->state = PPP_FSM_STOPPED;
		if (fsm->callbacks->finished != NULL)
			(*fsm->callbacks->finished)(fsm);
		break;

	case PPP_FSM_ACKRCVD:
		fsm->state = PPP_FSM_REQSENT;
		break;

	case PPP_FSM_OPENED:
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm_sconfreq(fsm, 0);
		break;
		}
	}

/*
 *  fsm_rcoderej -- Code-REJ ����������Ȥ��ν���
 */

static void
fsm_rcoderej (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_PPP_CP_HDR	*hdr;

 	/* PPP ������� (CP) �إå����û����Х��顼 */
 	if (input->len < sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)) {
 		syslog(LOG_WARNING, "[PPP/FSM] bad len: %d in recv Code-REJ.", input->len);
 		return;
 		}

 	hdr = GET_PPP_CP_HDR(input);

	syslog(LOG_WARNING, "[PPP/FSM] recv Code-REJ, code=%d, id=%d.", hdr->code, hdr->id);

	if (fsm->state == PPP_FSM_ACKRCVD)
		fsm->state = PPP_FSM_REQSENT;
	}

/*
 *  fsm_timeout -- �����ॢ���Ƚ���
 */

static void
fsm_timeout (void *arg)
{
	T_PPP_FSM *fsm = (T_PPP_FSM*)arg;

	switch (fsm->state) {
	case PPP_FSM_CLOSING:
	case PPP_FSM_STOPPING:
		if (fsm->retrans <= 0) {
			/* ������������Ķ�����Ȥ��ν��� */
#if 0	/* �����ư��� CLOSED �����ܤ��롣*/
			fsm->state = (fsm->state == PPP_FSM_CLOSING) ? PPP_FSM_CLOSED : PPP_FSM_STOPPED;
#else	/* of #if 0 */
			fsm->state = PPP_FSM_STOPPED;
#endif	/* of #if 0 */
			if (fsm->callbacks->finished != NULL)
				(*fsm->callbacks->finished)(fsm);
			}
		else {
			/* Terminate-Request ���������롣*/
			fsm_stermreq(fsm, ++ fsm->id);
			}
		break;
	case PPP_FSM_REQSENT:
	case PPP_FSM_ACKRCVD:
	case PPP_FSM_ACKSENT:
		if (fsm->retrans <= 0) {
			/* ������������Ķ�����Ȥ��ν��� */
			syslog(LOG_WARNING, "[PPP/FSM] retrans Conf-Req.");
			fsm->state = PPP_FSM_STOPPED;
			if (ppp_open_mode != PPP_OPEN_PASSIVE && fsm->callbacks->finished)
				(*fsm->callbacks->finished)(fsm);
			}
		else {
			/* Configure-Request ��������롣*/
			if (fsm->callbacks->retrans != NULL)
				(*fsm->callbacks->retrans)(fsm);
			fsm_sconfreq(fsm, 1);
			if (fsm->state == PPP_FSM_ACKRCVD)
				fsm->state = PPP_FSM_REQSENT;
			}

		break;

	default	:
		syslog(LOG_WARNING, "[PPP/FSM] unexp state: %d in timeout.", fsm->state);
		break;
		}
	}

/*
 *  fsm_stermreq -- Terminate-Request ���������롣
 */

static void
fsm_stermreq (T_PPP_FSM *fsm, uint8_t id)
{
	T_NET_BUF	*input;

	syscall(get_net_buf(&input, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
	IF_SET_PROTO(input, fsm->proto);
	ppp_cp_output(PPP_TERMREQ, id, input);

	timeout((FP)fsm_timeout, fsm, DEF_PPP_TIMEOUT);
	fsm->retrans --;
	}

/*
 *  fsm_init -- FSM �⥸�塼��ν����
 */

void
fsm_init (T_PPP_FSM *fsm)
{
	fsm->state = PPP_FSM_INITIAL;
	fsm->id	   = 0;
	}

/*
 *  fsm_lowerup -- FSM �����ؤ�ư���롣
 */

void
fsm_lowerup (T_PPP_FSM *fsm)
{
	switch (fsm->state) {
	case PPP_FSM_INITIAL:
		fsm->state = PPP_FSM_CLOSED;
		break;

	case PPP_FSM_STARTING:
		if (ppp_open_mode == PPP_OPEN_PASSIVE)
			fsm->state = PPP_FSM_STOPPED;
        	else {
			fsm_sconfreq(fsm, 0);
			fsm->state = PPP_FSM_REQSENT;
			}
		break;

	default	:
		syslog(LOG_WARNING, "[PPP/FSM] unexp state: %d in lowerup", fsm->state);
		break;
		}
	}

/*
 *  fsm_lowerdown -- FSM �����ؤ���ߤ��롣
 */

void
fsm_lowerdown (T_PPP_FSM *fsm)
{
	switch (fsm->state) {
	case PPP_FSM_CLOSED:
		fsm->state = PPP_FSM_INITIAL;
		break;

	case PPP_FSM_STOPPED:
		fsm->state = PPP_FSM_STARTING;
		if (fsm->callbacks->starting != NULL)
			(*fsm->callbacks->starting)(fsm);
		break;

	case PPP_FSM_CLOSING:
		fsm->state = PPP_FSM_INITIAL;
		untimeout((FP)fsm_timeout, fsm);
		break;

	case PPP_FSM_STOPPING:
	case PPP_FSM_REQSENT:
	case PPP_FSM_ACKRCVD:
	case PPP_FSM_ACKSENT:
		fsm->state = PPP_FSM_STARTING;
		untimeout((FP)fsm_timeout, fsm);
		break;

	case PPP_FSM_OPENED:
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);
		fsm->state = PPP_FSM_STARTING;
		break;

	default	:
		syslog(LOG_WARNING, "[PPP/FSM] unexp state: %d in lowerdown", fsm->state);
		break;
		}
	}

/*
 *  fsm_open -- FSM �Υ����ץ�
 */

void
fsm_open (T_PPP_FSM *fsm)
{
	switch (fsm->state) {
	case PPP_FSM_INITIAL:
		fsm->state = PPP_FSM_STARTING;
		if (fsm->callbacks->starting != NULL)
			(*fsm->callbacks->starting)(fsm);
		break;

	case PPP_FSM_CLOSED:
		if (ppp_open_mode == PPP_OPEN_PASSIVE)
			fsm->state = PPP_FSM_STOPPED;
		else {
			fsm_sconfreq(fsm, 0);
			fsm->state = PPP_FSM_REQSENT;
			}
		break;

	case PPP_FSM_CLOSING:
		fsm->state = PPP_FSM_STOPPING;
		/* nobreak;	��������� */

	case PPP_FSM_STOPPED:
	case PPP_FSM_OPENED:
		fsm_lowerdown(fsm);
		fsm_lowerup(fsm);
		break;
		}
	}

/*
 *  fsm_close -- ��󥯤����Ǥ򳫻Ϥ��롣
 */

void
fsm_close (T_PPP_FSM *fsm)
{
	switch (fsm->state) {
	case PPP_FSM_STARTING:
		fsm->state = PPP_FSM_INITIAL;
		break;

#if 0	/* �����ư��� CLOSED �����ܤ��롣*/
	case PPP_FSM_STOPPED:
		fsm->state = PPP_FSM_CLOSED;
		break;
#endif	/* of #if 0 */

	case PPP_FSM_STOPPING:
		fsm->state = PPP_FSM_CLOSING;
		break;

	case PPP_FSM_REQSENT:
	case PPP_FSM_ACKRCVD:
	case PPP_FSM_ACKSENT:
	case PPP_FSM_OPENED:
		if (fsm->state != PPP_FSM_OPENED)
			untimeout((FP)fsm_timeout, fsm);
		else if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);

		/* �����ॢ���Ȥ����ꤷ��Terminate-Request ���������롣*/
		fsm->retrans = MAX_PPP_TERMINATES;
		fsm_stermreq(fsm, fsm->reqid = ++ fsm->id);
		fsm->state = PPP_FSM_CLOSING;
		break;
		}
	}

/*
 *  fsm_input -- ���ϡ�PPP ������� (CP) �����楳���ɤˤ��Ŭ���ʴؿ���ƽФ�
 */

void
fsm_input (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_PPP_CP_HDR	*hdr;
	T_NET_BUF	*output;

 	/* PPP ������� (CP) �إå����û����Х��顼 */
 	if (input->len < (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR))) {
 		syslog(LOG_WARNING, "[PPP/FSM] short hdr: %d.", input->len);
 		return;
 		}

 	hdr = GET_PPP_CP_HDR(input);

 	/* �إå���Ĺ�������ϥǡ��������������פ��ʤ���Х��顼 */
 	if (hdr->len != input->len - sizeof(T_PPP_HDR)) {
 		syslog(LOG_WARNING, "[PPP/FSM] bad len: %d.", hdr->len);
 		return;
 		}
 
 	/* ���֤� INITIAL �� STARTING �ʤ饨�顼 */
 	if (fsm->state == PPP_FSM_INITIAL || fsm->state == PPP_FSM_STARTING) {
 		syslog(LOG_WARNING, "[PPP/FSM] unexp state: %d in input.", fsm->state);
 		return;
 		}
 
 	/*
 	 *  ���楳���ɤˤ��Ŭ���ʴؿ���ƽФ�
 	 */

	switch (hdr->code) {
	case PPP_CONFREQ:
		fsm_rconfreq(fsm, hdr->id, input);
		break;

	case PPP_CONFACK:
		fsm_rconfack(fsm, hdr->id, input);
		break;

	case PPP_CONFNAK:
	case PPP_CONFREJ:
		fsm_rconfnakrej(fsm, hdr->code, hdr->id, input);
		break;

	case PPP_TERMREQ:
		fsm_rtermreq(fsm, hdr->id, input);
		break;

	case PPP_TERMACK:
		fsm_rtermack(fsm, input);
		break;

	case PPP_CODEREJ:
		fsm_rcoderej(fsm, input);
		break;

	default:
		if (fsm->callbacks->extcode == NULL ||
		    (*fsm->callbacks->extcode)(fsm, hdr->code, hdr->id, input) != true) {
			syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
			memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
			ppp_cp_output(PPP_CODEREJ, ++ fsm->id, output);
			}
		break;
		}
	}

/*
 *  fsm_protoreject -- Proto-REJ ����������Ȥ��ν���
 */

void
fsm_protreject (T_PPP_FSM *fsm)
{
	switch (fsm->state) {
	case PPP_FSM_CLOSING:
		untimeout((FP)fsm_timeout, fsm);

#if 0	/* �����ư��� CLOSED �����ܤ��롣*/
		/* ��������� */
#else	/* of #if 0 */
		fsm->state = PPP_FSM_STOPPED;
		if (fsm->callbacks->finished != NULL)
			(*fsm->callbacks->finished)(fsm);
		break;
#endif	/* of #if 0 */

	case PPP_FSM_CLOSED:
		fsm->state = PPP_FSM_CLOSED;
		if (fsm->callbacks->finished != NULL)
			(*fsm->callbacks->finished)(fsm);
		break;

	case PPP_FSM_STOPPING:
	case PPP_FSM_REQSENT:
	case PPP_FSM_ACKRCVD:
	case PPP_FSM_ACKSENT:
		untimeout((FP)fsm_timeout, fsm);
		/* ��������� */

	case PPP_FSM_STOPPED:
		fsm->state = PPP_FSM_STOPPED;
		if (fsm->callbacks->finished != NULL)
			(*fsm->callbacks->finished)(fsm);
		break;

	case PPP_FSM_OPENED:
		if (fsm->callbacks->down != NULL)
			(*fsm->callbacks->down)(fsm);

		/* �����ॢ���Ȥ����ꤷ��Terminate-Request ���������롣*/
		fsm->retrans = MAX_PPP_TERMINATES;
		fsm_stermreq(fsm, fsm->reqid = ++ fsm->id);
		fsm->state = PPP_FSM_STOPPING;
		break;

		}
	}

#endif	/* fo #ifdef SUPPORT_PPP */
