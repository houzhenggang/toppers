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
 *  @(#) $Id: ppp.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
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
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* 
 *  PPP ����������������
 */

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_ipcp.h>
#include <net/ppp_ccp.h>
#include <net/ppp_upap.h>
#include <net/ppp_modem.h>

#ifdef SUPPORT_PPP

/*
 *  �����ѿ�
 */

uint8_t	ppp_phase = PPP_PHASE_INITIALIZE;	/* ��󥯤ξ���		*/

/*
 *  �ץ�ȥ���ɽ
 */

T_PPP_PROTENT *protocols[] = {
	&lcp_protent,
	&ipcp_protent,

#ifdef SUPPORT_CCP
	&ccp_protent,
#endif	/* #ifdef SUPPORT_CCP */

#ifdef LCP_CFG_PAP
	&pap_protent,
#endif	/* #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_CHAP
	&chap_protent,
#endif	/* #ifdef LCP_CFG_CHAP */

	NULL
	};

/*
 *  �ѿ�
 */

#ifdef PPP_IDLE_TIMEOUT

static bool_t idle = false;

#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

/*
 *  �ؿ�
 */

static void parse_input (T_NET_BUF *input);

#ifdef PPP_IDLE_TIMEOUT

static void idle_timeout (void *arg);

#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

/*
 *  PPP ���Ϥβ���
 */

static void
parse_input(T_NET_BUF *input)
{
	T_PPP_PROTENT	*entry;
	int_t		ix;
	uint16_t	proto;

	NET_COUNT_PPP(net_count_ppp.in_octets,  input->len);
	NET_COUNT_PPP(net_count_ppp.in_packets, 1);

	/* �ե졼��Ĺ������å����� */
	if (input->len < sizeof(T_PPP_HDR)) {	/* FreeBSD �Ǥ� PPP_HDRLEN �� 4 */
		syslog(LOG_NOTICE, "[PPP] recv short frame.");
		goto buf_rel;
		}

	proto = ntohs(*GET_PPP_HDR(input));

	/* �ץ�ȥ��뤬 LCP �ʳ��ǡ�LCP �������ץ󤵤�Ƥ��ʤ���Х��顼 */
	if (proto != PPP_LCP && lcp_fsm.state != PPP_FSM_OPENED) {
		syslog(LOG_NOTICE, "[PPP] LCP not open.");
		goto buf_rel;
		}

	/* ��󥯤�ǧ�ھ��ְ����ϡ�LCP��LQR��PAP��CHAP �Τ߼����դ��� */
	if (ppp_phase <= PPP_PHASE_AUTHENTICATE &&
	    !(proto == PPP_LCP || proto == PPP_LQR ||
	      proto == PPP_PAP || proto == PPP_CHAP)) {
		syslog(LOG_NOTICE, "[PPP] disc proto: 0x%04x, phase: %d.", proto, ppp_phase);
		goto buf_rel;
		}

	/* ��̥ץ�ȥ�������ϴؿ���ƽФ� */
	for (ix = 0; (entry = protocols[ix]) != NULL; ix ++) {
		if (entry->proto == proto && entry->input != NULL) {
			(*entry->input)(input);
			syscall(rel_net_buf(input));
			return;
			}
		if ((entry->proto & ~0x8000) == proto && entry->datainput != NULL) {
			(*entry->datainput)(input);
			return;
			}
		}

	syslog(LOG_INFO, "[PPP] unexp proto: 0x%04x.", proto);
	lcp_sprotrej(input);

buf_rel:
	NET_COUNT_PPP(net_count_ppp.in_err_packets, 1);
	syscall(rel_net_buf(input));
	}

/*
 *  ppp_output -- PPP ���󥿥ե������ν��ϴؿ�
 */

ER
ppp_output (T_NET_BUF *output, TMO tmout)
{
	ER error = E_OK;

#ifdef PPP_CFG_MODEM

#if 0	/* ��α */
	/* ��ǥ����³��λ�ޤ��Ԥġ�*/
	if ((error = wait_modem()) != E_OK)
		goto buf_ret;
#endif

#endif	/* of #ifdef PPP_CFG_MODEM */

	/* IPCP ����³��λ�ޤ��Ԥġ�*/
	if ((error = wait_ipcp()) != E_OK)
		goto buf_ret;

#ifdef PPP_IDLE_TIMEOUT
	wai_sem(SEM_IDLE_TIMEOUT);
	if (idle) {
		untimeout((FP)idle_timeout, NULL);
		idle = false;
		}
	sig_sem(SEM_IDLE_TIMEOUT);
#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

	/* PPP ���ϥ��塼���������롣*/
	if ((error = tsnd_dtq(DTQ_PPP_OUTPUT, output, tmout)) != E_OK)
		goto buf_ret;

#ifdef PPP_IDLE_TIMEOUT
	wai_sem(SEM_IDLE_TIMEOUT);
	if (!idle && ppp_phase == PPP_PHASE_NETWORK) {
		timeout((FP)idle_timeout, NULL, PPP_IDLE_TIMEOUT);
		idle = true;
		}
	sig_sem(SEM_IDLE_TIMEOUT);
#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

	return error;

buf_ret:
	syscall(rel_net_buf(output));
	NET_COUNT_PPP(net_count_ppp.out_err_packets, 1);
	return error;
	}

/*
 *  ppp_cp_output -- CP �ե졼�������
 */

void
ppp_cp_output (uint8_t code, uint8_t id, T_NET_BUF *output)
{
	T_PPP_CP_HDR	*cph;

	/* CP �إå������ꤹ�� */
	cph = GET_PPP_CP_HDR(output);
	cph->code = code;
	cph->id   = id;
	cph->len  = htons(output->len - sizeof(T_PPP_HDR));

	/* PPP ���ϥ��塼���������롣*/
	if (snd_dtq(DTQ_PPP_OUTPUT, output) != E_OK) {
		syscall(rel_net_buf(output));
		NET_COUNT_PPP(net_count_ppp.out_err_packets, 1);
		}
	}

/*
 *  PPP ���ϥ�����
 */

void
ppp_input_task(intptr_t exinf)
{
	T_NET_BUF	*input;
	T_PPP_PROTENT	*proto;
	ID		tskid;
	int_t		ix;

	/* �ݡ��Ȥ������ꤹ�� */
	syscall(serial_opn_por(HDLC_PORTID));
	syscall(serial_ctl_por(HDLC_PORTID, IOCTL_FCSND | IOCTL_FCRCV));

	get_tid(&tskid);

#ifdef PPP_CFG_MODEM

	init_modem();
	syslog(LOG_NOTICE, "[PPP INPUT:%d] started with modem on port %d.", tskid, HDLC_PORTID);

#else	/* of #ifdef PPP_CFG_MODEM */

	syslog(LOG_NOTICE, "[PPP INPUT:%d] started on port %d.", tskid, HDLC_PORTID);

#endif	/* of #ifdef PPP_CFG_MODEM */

	/* �ͥåȥ�������ޥ�������ư���� */
	syscall(act_tsk(NET_TIMER_TASK));

	/* ��̥ץ�ȥ������������ */
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++)
		if (proto->init != NULL)
			(*proto->init)();

	lcp_lowerup();
	lcp_open(PPP_OPEN_PASSIVE);

	/* PPP ���ϥ�������ư���� */
	syscall(act_tsk(PPP_OUTPUT_TASK));

	while (true) {
		if (tget_net_buf(&input, IF_PDU_SIZE, TMO_PPP_GET_NET_BUF) == E_OK) {
			while (HDLC_read(input, IF_PDU_SIZE) != E_OK)
				;
			if (input->len > 0) {

	#ifdef PPP_IDLE_TIMEOUT
				wai_sem(SEM_IDLE_TIMEOUT);
				if (idle && ntohs(*GET_PPP_HDR(input)) != PPP_LCP) {
					untimeout((FP)idle_timeout, NULL);
					idle = false;
					}
				sig_sem(SEM_IDLE_TIMEOUT);
	#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

				parse_input(input);
				}
			else
				syscall(rel_net_buf(input));

	#ifdef PPP_IDLE_TIMEOUT
			wai_sem(SEM_IDLE_TIMEOUT);
			if (!idle && ppp_phase == PPP_PHASE_NETWORK) {
				timeout((FP)idle_timeout, NULL, PPP_IDLE_TIMEOUT);
				idle = true;
				}
			else if (idle && ppp_phase != PPP_PHASE_NETWORK) {
				untimeout((FP)idle_timeout, NULL);
				idle = false;
				}
			sig_sem(SEM_IDLE_TIMEOUT);
	#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

			}
		else {
			HDLC_dummy_read();
			NET_COUNT_PPP(net_count_ppp.in_err_packets, 1);
			NET_COUNT_PPP(net_count_ppp_no_bufs, 1);
			}
		}
	}

/*
 *  PPP ���ϥ�����
 */

void
ppp_output_task(intptr_t exinf)
{
	T_NET_BUF	*output;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[PPP OUTPUT:%d] started.", tskid);

	while (true) {
		while (rcv_dtq(DTQ_PPP_OUTPUT, (intptr_t*)&output) == E_OK) {
			NET_COUNT_PPP(net_count_ppp.out_octets,  output->len);
			NET_COUNT_PPP(net_count_ppp.out_packets, 1);
			syscall(HDLC_write(output));
			syscall(rel_net_buf(output));
			}
		}
	}

#ifdef PPP_IDLE_TIMEOUT

/*
 *  �����ɥ륿���ॢ���Ƚ���
 */

static void
idle_timeout (void *arg)
{
	syslog(LOG_NOTICE, "[PPP] idel %d [s], disconnecting.", (uint16_t)(PPP_IDLE_TIMEOUT / NET_TIMER_HZ));
	lcp_close();
	}

#endif	/* of #ifdef PPP_IDLE_TIMEOUT */

#endif	/* fo #ifdef SUPPORT_PPP */
