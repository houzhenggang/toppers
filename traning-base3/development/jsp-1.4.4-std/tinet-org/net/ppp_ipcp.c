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
 *  @(#) $Id: ppp_ipcp.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * ipcp.c - PPP IP Control Protocol.
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
 *	PPP IP Control Protocol (IPCP) Module
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
 * $FreeBSD: src/usr.sbin/ppp/ipcp.c,v 1.90.2.4 2000/08/19 09:30:03 brian Exp $
 *
 *	TODO:
 *		o Support IPADDRS properly
 *		o Validate the length in IpcpDecodeConfig
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_ipcp.h>
#include <net/ppp_modem.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>

#include <net/if_var.h>

#ifdef SUPPORT_PPP

/*
 *  �ؿ�
 */

static void ipcp_init (void);
static void ipcp_input (T_NET_BUF *input);
static void ipcp_protrej (void);
static void ipcp_lowerup (void);
static void ipcp_lowerdown (void);
static void ipcp_open (void);
static void ipcp_close (void);

/*
 * FSM ����ƽФ���륳����Хå���
 */

static void  ipcp_resetci(T_PPP_FSM *fsm);	/* �����������ꥻ�åȤ��롣	*/
static int_t ipcp_cilen	(T_PPP_FSM *fsm);	/* ���������Ĺ�����֤���		*/
static void  ipcp_addci	(T_PPP_FSM *fsm, T_NET_BUF *output);
						/* ������������ɲä��롣		*/
static bool_t  ipcp_ackci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* ACK ����������Ȥ��ν���	*/
static bool_t  ipcp_nakci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* NAK ����������Ȥ��ν���	*/
static bool_t  ipcp_rejci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* REJ ����������Ȥ��ν���	*/
static int_t ipcp_reqci	(T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output);
						/* ���ι���������ǧ���롣	*/
static void ipcp_up	(T_PPP_FSM *fsm);	/* �����³���Ω���롣		*/
static void ipcp_down	(T_PPP_FSM *fsm);	/* �����³��������롣		*/
static void ipcp_finished(T_PPP_FSM *fsm);	/* �����ؤ�λ���롣		*/

/*
 *  �ѿ�
 */

static T_IFNET ipcp_local_def_cfg = {		/* ����������ε�����		*/
	NULL,
	{
		IPV4_ADDR_LOCAL,		/* IP ���ɥ쥹			*/
		UINT_C(0),			/* ���֥ͥåȥޥ���		*/
		},
	};

static T_IFNET ipcp_remote_def_cfg = {		/* ���ι�������ε�����	*/
	NULL,
	{
		IPV4_ADDR_REMOTE,		/* IP ���ɥ쥹			*/
		UINT_C(0),			/* ���֥ͥåȥޥ���		*/
		}
	};

static T_IFNET ipcp_local_neg_cfg;		/* �ͥ���μ���������		*/

static T_IFNET ipcp_remote_neg_cfg;		/* �ͥ�������ι�������		*/

/*
 *  �����ѿ�
 */

T_PPP_FSM_CALLBACKS ipcp_callbacks = {
	ipcp_resetci,			/* �����������ꥻ�åȤ��롣	*/
	ipcp_cilen,			/* ���������Ĺ�����֤���		*/
	ipcp_addci,			/* ������������ɲä��롣		*/
	ipcp_ackci,			/* ACK ����������Ȥ��ν���	*/
	ipcp_nakci,			/* NAK ����������Ȥ��ν���	*/
	ipcp_rejci,			/* REJ ����������Ȥ��ν���	*/
	ipcp_reqci,			/* ���ι���������ǧ���롣	*/
	ipcp_up,			/* �����³���Ω���롣		*/
	ipcp_down,			/* �����³��������롣		*/
	NULL,				/* �����ؤ򳫻Ϥ��롣		*/
	ipcp_finished,			/* �����ؤ�λ���롣		*/
	NULL,				/* �������롣			*/
	NULL,				/* ������ CP ����������Ȥ��ν���	*/
	};

T_PPP_FSM ipcp_fsm = {
	&ipcp_callbacks,		/* ������Хå��ؿ�		*/
	PPP_IPCP,			/* �ץ�ȥ���			*/
	};

T_PPP_PROTENT ipcp_protent = {
	PPP_IPCP,
	ipcp_init,			/* �����			*/
	ipcp_input,			/* ����				*/
	ipcp_protrej,			/* Proto-REJ ��������		*/
	ipcp_lowerup,			/* �����ؤ�ư����		*/
	ipcp_lowerdown,			/* �����ؤ���ߤ���		*/
	ipcp_open,			/* �����ץ󤹤�			*/
	ipcp_close,			/* ����������			*/
	ip_input,			/* �ǡ������ϡ�IP ����		*/
	};

T_IFNET ipcp_local_ack_cfg;		/* ���˵��Ĥ��줿�μ���������	*/
T_IFNET ipcp_remote_ack_cfg;		/* ���˵��Ĥ�����������	*/

/*
 *  ppp_get_ifnet -- �ͥåȥ�����󥿥ե�������¤�Τ��֤���
 */

T_IFNET *
ppp_get_ifnet (void)
{
	return &ipcp_local_ack_cfg;
	}

/*
 *  wait_ipcp -- IP ��³��λ�ޤ��Ԥġ�
 *
 *	�����: ��³�˼��Ԥ����� E_OBJ ���֤���
 */

ER
wait_ipcp (void)
{
#ifdef PPP_CFG_MODEM
	ER error;
#endif	/* of #ifdef PPP_CFG_MODEM */

	if (ipcp_fsm.state <= PPP_FSM_STOPPED) {

#ifdef PPP_CFG_MODEM

		/* ��ǥ����³��λ�ޤ��Ԥġ�*/
		if ((error = wait_modem()) != E_OK)
			return error;

#else	/* of #ifdef PPP_CFG_MODEM */

		/*
		 * ��ư�����ץ󤷡���꤫�����³�Ԥ��ʤ� LCP ����٥���������
		 * ǽư�����ץ���֤ǡ��ƥ����ץ󤹤롣
		 */
		lcp_close();
		lcp_open(PPP_OPEN_ACTIVE);

#endif	/* of #ifdef PPP_CFG_MODEM */

		}

	if (ipcp_fsm.state != PPP_FSM_OPENED) {
		/* IP ��³��λ�ޤ��Ԥġ�*/
		wai_sem(SEM_IPCP_READY);
		if (ipcp_fsm.state != PPP_FSM_OPENED)
			return E_OBJ;
		}

	return E_OK;
	}

/*
 *  ipcp_init -- IPCP �⥸�塼��ν����
 */

static void
ipcp_init (void)
{
	fsm_init(&ipcp_fsm);
	}

/*
 *  ipcp_input -- IPCP ����
 */

static void
ipcp_input (T_NET_BUF *input)
{
	NET_COUNT_PPP_IPCP(net_count_ppp_ipcp_in_octets,  input->len);
	NET_COUNT_PPP_IPCP(net_count_ppp_ipcp_in_packets, 1);
	fsm_input(&ipcp_fsm, input);
	}

/*
 *  ipcp_resetci -- IPCP�ι��������ꥻ�åȤ��롣
 */

static void
ipcp_resetci (T_PPP_FSM *fsm)
{
	/* ����������ν������ */
	ipcp_local_neg_cfg = ipcp_local_def_cfg;
	memset((void*)&ipcp_local_ack_cfg, 0, sizeof(T_IFNET));

	/* ���ι�������ν������ */
	ipcp_remote_neg_cfg = ipcp_remote_def_cfg;
	memset((void*)&ipcp_remote_ack_cfg, 0, sizeof(T_IFNET));
	}

/*
 *  ipcp_cilen -- ���������Ĺ�����֤���
 */

static int_t
ipcp_cilen (T_PPP_FSM *fsm)
{
	int_t cilen = 0;

	cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* IP ���ɥ쥹 */

	return cilen;
	}

/*
 *  ipcp_addci -- IPCP�ι���������ɲä��롣
 */

static void
ipcp_addci (T_PPP_FSM *fsm, T_NET_BUF *output)
{
	uint8_t *buf;

	buf = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/* IP ���ɥ쥹���ץ������ɲä��롣 */
	*buf ++ = IPCP_CIT_ADDR;
	*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
	ahtonl(buf, ipcp_local_neg_cfg.in_ifaddr.addr);
	buf += sizeof(uint32_t);
	}

/*
 *  ipcp_ackci -- ACK ����������Ȥ��ν���
 *
 *	�����:	true  ACK ������
 *		false ACK �ϰ۾�
 */

static bool_t
ipcp_ackci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	/*
	 *  �������������������˴����˰��פ��ʤ���Фʤ�ʤ���
	 *  ���äơ�ipcp_addci �Ǻ���������˲��Ϥ��롣
	 */

	/* ADDR ���ץ�������Ϥ��롣 */
	if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
	    *buf ++ != IPCP_CIT_ADDR			||
	    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
	    nahcmpl(buf, ipcp_local_neg_cfg.in_ifaddr.addr))
		return false;
	buf += sizeof(uint32_t);
	len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);

	return true;
	}

/*
 *  ipcp_nakci -- NAK ����������Ȥ��ν���
 *
 *	�����:	1  NAK ������
 *		0  NAK �ϰ۾�
 */

static int_t
ipcp_nakci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_IFNET		new_cfg;
	uint32_t	cilong;
	uint16_t	len;
	uint8_t		*buf, cilen;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = ipcp_local_neg_cfg;

	/* ADDR ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == IPCP_CIT_ADDR				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.in_ifaddr.addr = cilong;
		}

	/* ���̵�뤹�롣*/
	while (len > sizeof(T_PPP_CI_HDR)) {
		cilen = *(buf + 1);
		if (len < cilen)
			return 0;
		buf += cilen;
		len -= cilen;
		}

	/* Ĺ���� 0 �Ǥʤ���Х��顼 */
	if (len != 0)
		return 0;

	/* ���������ץ��������ꤹ�롣*/
	if (fsm->state != PPP_FSM_OPENED)
		ipcp_local_neg_cfg = new_cfg;
               		
	return 1;
	}

/*
 *  ipcp_rejci -- REJ ����������Ȥ��ν���
 *
 *	�����:	1  REJ ������
 *		0  REJ �ϰ۾�
 */

static int_t
ipcp_rejci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_IFNET		new_cfg;
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = ipcp_local_neg_cfg;

	/* ADDR ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == IPCP_CIT_ADDR				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)) {
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.in_ifaddr.addr = 0;
		}

	/* Ĺ���� 0 �Ǥʤ���Х��顼 */
	if (len != 0)
		return 0;

	/* ���������ץ��������ꤹ�롣*/
	if (fsm->state != PPP_FSM_OPENED)
		ipcp_local_neg_cfg = new_cfg;

	return 1;
	}

/*
 *  ipcp_reqci -- ���ι����������Ϥ��롣
 */

static int_t
ipcp_reqci (T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output)
{
	uint32_t	addr;
	uint16_t	code, final, len, cilen;
	uint8_t		*np, *rp, *ap, *cp, type = 0;

	rp = ap = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
				/* rp: REJ��ap: ACK ���� CI �Υݥ���	*/
				/* ���ݤ�����ϡ����� buf �˾�񤭤��롣	*/
	len   = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	np    = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	final = PPP_CONFACK;	/* �ǽ�Ū���������륳���� */
	while (len > 0) {
		code = PPP_CONFACK;
		cp   = ap;	/* cp: ���߽������ CI	*/

		if (len < sizeof(T_PPP_CI_HDR)) {

			/* �Ĥ꤬ CI �إå����û�� */
			syslog(LOG_NOTICE, "[PPP/IPCP] bad CI len: %d.", len);
			cilen = len;	/* �ǡ���Ĺ���۾�ξ��ν���	*/
			len  = 0;	/* �롼�פ���ȴ���롣		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}

		type  = *ap ++;	/* CI �η�		*/
		cilen = *ap ++;	/* CI ��Ĺ��		*/
		if (len < cilen) {

			/* �Ĥ꤬ CI Ĺ���û�� */
			syslog(LOG_NOTICE, "[PPP/IPCP] bad CI len: %d.", cilen);
			cilen = len;	/* �ǡ���Ĺ���۾�ξ��ν���	*/
			len  = 0;	/* �롼�פ���ȴ���롣		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}
		len -= sizeof(T_PPP_CI_HDR);

		/* CI �η��ˤ��ʬ�����롣*/
		switch (type) {

		case IPCP_CIT_ADDR:	/* IP ���ɥ쥹 */

		 	/* CI Ĺ�����إå� + 4 �����ƥåȤǤʤ���Х��顼 */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(addr, ap);
				if (addr != ipcp_remote_neg_cfg.in_ifaddr.addr &&
				    (addr == 0 || ipcp_remote_neg_cfg.in_ifaddr.addr != 0)) {
					*np ++ = IPCP_CIT_ADDR;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
					ahtonl(np, ipcp_remote_neg_cfg.in_ifaddr.addr);
					np  += sizeof(uint32_t);
					code = PPP_CONFNAK;
					}
#if 1	/* �׳�ǧ */
				else if (addr == 0 && ipcp_remote_neg_cfg.in_ifaddr.addr == 0)
#else
				else if (addr == 0 || ipcp_remote_neg_cfg.in_ifaddr.addr == 0)
#endif
					code = PPP_CONFREJ;
				else
					ipcp_remote_neg_cfg.in_ifaddr.addr = addr;
				}
			break;

		default:
			syslog(LOG_INFO, "[PPP/IPCP] unexp opt: %d.", type);
			code = PPP_CONFREJ;
			break;
			}
endswitch:

		if (code == PPP_CONFNAK) {
			/* CI �η��� Magic Number �ξ�������ơ�NAK �β����	*/
			/* ������ MAX_PPP_FAILURES  ��Ķ��������ݤ��롣	*/
			if (fsm->failures >= MAX_PPP_FAILURES)
				code = PPP_CONFREJ;
			else if (final != PPP_CONFREJ)
				final = PPP_CONFNAK;
			}

		/* ���� CI ����ݤ��� */
		if (code == PPP_CONFREJ) {
			if (rp < cp)		/* ���˵ͤ�롣*/
				memcpy(rp, cp, cilen);
			rp += cilen;
			final = PPP_CONFREJ;
			}

		ap   += cilen - sizeof(T_PPP_CI_HDR);
		len  -= cilen - sizeof(T_PPP_CI_HDR);
		}

	/* �ǽ�Ū��Ĺ����Ĵ�����롣*/
	switch (final) {
	case PPP_CONFNAK:
		output->len = np - output->buf;
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		break;
	case PPP_CONFREJ:
		memcpy(output->buf, input->buf, output->len = rp - input->buf);
		break;
	case PPP_CONFACK:
		memcpy(output->buf, input->buf, input->len);
		break;
		}

	return final;
	}

/*
 *  ipcp_up -- �����³���Ω���롣
 */

static void
ipcp_up (T_PPP_FSM *fsm)
{
	/* ����������ν������ */
	ipcp_local_ack_cfg = ipcp_local_neg_cfg;

	/*
	 *  ���֥ͥåȥޥ�����
	 *  �����롦�֥��ɥ��㥹�� IP ���ɥ쥹�����ꤹ�롣
	 */
	ipcp_local_ack_cfg.in_ifaddr.mask = MAKE_IPV4_LOCAL_MASK(ipcp_local_neg_cfg.in_ifaddr.addr);

	/* ���ι�������ν������ */
	ipcp_remote_ack_cfg = ipcp_remote_neg_cfg;

	/*
	 *  ���֥ͥåȥޥ�����
	 *  �����롦�֥��ɥ��㥹�� IP ���ɥ쥹�����ꤹ�롣
	 */
	ipcp_remote_ack_cfg.in_ifaddr.mask = MAKE_IPV4_LOCAL_MASK(ipcp_remote_neg_cfg.in_ifaddr.addr);

	sig_sem(SEM_IPCP_READY);

	syslog(LOG_NOTICE, "[PPP/IPCP] up, Local IP Addr: %s, Remote IP Addr: %s.",
	                   ip2str(NULL, &ipcp_local_neg_cfg.in_ifaddr.addr),
	                   ip2str(NULL, &ipcp_remote_neg_cfg.in_ifaddr.addr));
	}

/*
 *  ipcp_down -- �����³��������롣
 */

static void
ipcp_down (T_PPP_FSM *fsm)
{
	sig_sem(SEM_IPCP_READY);
	syslog(LOG_NOTICE, "[PPP/IPCP] down.");
	}

/*
 *  ipcp_finished -- �����ؤ�λ���롣
 */

static void
ipcp_finished (T_PPP_FSM *fsm)
{
	}

/*
 *  ipcp_protrej -- Proto-REJ ����������Ȥ��ν���
 */

static void
ipcp_protrej (void)
{
	fsm_lowerdown(&ipcp_fsm);
	}

/*
 *  ipcp_lowerup -- IPCP �����ؤ�ư���롣
 */

static void
ipcp_lowerup (void)
{
	fsm_lowerup(&ipcp_fsm);
	}

/*
 *  ipcp_lowerdown -- IPCP �����ؤ���ߤ��롣
 */

static void
ipcp_lowerdown (void)
{
	fsm_lowerdown(&ipcp_fsm);
	}

/*
 *  ipcp_open -- IPCP �Υ����ץ�
 */

static void
ipcp_open (void)
{
	fsm_open(&ipcp_fsm);
	}

/*
 *  ipcp_close -- IPCP �Υ�����
 */

static void
ipcp_close (void)
{
	fsm_close(&ipcp_fsm);
	}

#endif	/* fo #ifdef SUPPORT_PPP */
