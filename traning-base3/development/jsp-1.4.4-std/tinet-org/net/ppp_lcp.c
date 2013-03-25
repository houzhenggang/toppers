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
 *  @(#) $Id: ppp_lcp.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * lcp.c - PPP Link Control Protocol.
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
 *	      PPP Link Control Protocol (LCP) Module
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
 * $FreeBSD: src/usr.sbin/ppp/lcp.c,v 1.81.2.3 2000/08/19 09:30:04 brian Exp $
 *
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
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_auth.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>

#ifdef SUPPORT_PPP

/*
 *  �ؿ�
 */

static void lcp_init    (void);
static void lcp_protrej (void);
static void lcp_input   (T_NET_BUF *input);

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

static void send_echo_req  (T_PPP_FSM *fsm);
static void recv_echo_rep  (T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input);
static void echo_timeout   (void *arg);
static void echo_lowerup   (void);
static void echo_lowerdown (void);

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

/*
 * FSM ����ƽФ���륳����Хå��ؿ�
 */

static void  lcp_resetci(T_PPP_FSM *fsm);	/* �����������ꥻ�åȤ��롣	*/
static int_t lcp_cilen	(T_PPP_FSM *fsm);	/* ���������Ĺ�����֤���		*/
static void  lcp_addci	(T_PPP_FSM *fsm, T_NET_BUF *output);
						/* ������������ɲä��롣		*/
static bool_t lcp_ackci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* ACK ����������Ȥ��ν���	*/
static bool_t lcp_nakci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* NAK ����������Ȥ��ν���	*/
static bool_t lcp_rejci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* REJ ����������Ȥ��ν���	*/
static int_t lcp_reqci	(T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output);
						/* ���ι���������ǧ���롣	*/
static void lcp_up	(T_PPP_FSM *fsm);	/* �����³���Ω���롣		*/
static void lcp_starting(T_PPP_FSM *fsm);	/* �����ؤ򳫻Ϥ��롣		*/
static bool_t lcp_extcode	(T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input);
						/* ������ CP ����������Ȥ��ν���	*/
static void lcp_rprotrej(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* Proto-REJ ����������Ȥ��ν���	*/
/*
 *  �ѿ�
 */

static T_LCP_CONFIGS lcp_def_cfg = {		/* ��������ν��������		*/
	DEF_REMOTE_ACCM,			/* ACCM				*/

#ifdef LCP_CFG_MAGIC

	ULONG_C(0),				/* �ޥ��å��ֹ�			*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	DEF_PPP_MTU,				/* MRU				*/
	UINT_C(0),				/* ���ץ����ե饰		*/
	};

static T_LCP_CONFIGS lcp_local_def_cfg = {	/* ����������ε�����		*/
	DEF_LOCAL_ACCM,				/* ACCM				*/

#ifdef LCP_CFG_MAGIC

	ULONG_C(0),				/* �ޥ��å��ֹ�			*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	DEF_PPP_MTU,				/* MRU				*/
	DEF_LCP_LOCAL_CFGS,			/* ���ץ����ե饰		*/
	};

static T_LCP_CONFIGS lcp_local_neg_cfg;		/* �ͥ���μ���������		*/

static T_LCP_CONFIGS lcp_remote_neg_cfg;	/* �ͥ�������ι�������		*/

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

static uint8_t echo_pending  = UINT_C(0);
static uint8_t echo_number   = UINT_C(0);
static uint8_t timer_running = false;

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

/*
 *  �����ѿ�
 */

T_PPP_FSM_CALLBACKS lcp_callbacks = {
	lcp_resetci,			/* �����������ꥻ�åȤ��롣	*/
	lcp_cilen,			/* ���������Ĺ�����֤���		*/
	lcp_addci,			/* ������������ɲä��롣		*/
	lcp_ackci,			/* ACK ����������Ȥ��ν���	*/
	lcp_nakci,			/* NAK ����������Ȥ��ν���	*/
	lcp_rejci,			/* REJ ����������Ȥ��ν���	*/
	lcp_reqci,			/* ���ι���������ǧ���롣	*/
	lcp_up,				/* �����³���Ω���롣		*/
	lcp_down,			/* �����³��������롣		*/
	lcp_starting,			/* �����ؤ򳫻Ϥ��롣		*/
	lcp_finished,			/* �����ؤ�λ���롣		*/
	NULL,				/* �������롣			*/
	lcp_extcode,			/* ������ CP ����������Ȥ��ν���	*/
	};

T_PPP_FSM lcp_fsm = {
	&lcp_callbacks,			/* ������Хå��ؿ�		*/
	PPP_LCP,			/* �ץ�ȥ���			*/
	};

T_PPP_PROTENT lcp_protent = {
	PPP_LCP,
	lcp_init,			/* �����			*/
	lcp_input,			/* ����				*/
	lcp_protrej,			/* Proto-REJ ��������		*/
	NULL,				/* �����ؤ�ư����		*/
	lcp_lowerdown,			/* �����ؤ���ߤ���		*/
	NULL,				/* �����ץ󤹤�			*/
	lcp_close,			/* ����������			*/
	NULL,				/* �ǡ�������			*/
	};

T_LCP_CONFIGS lcp_local_ack_cfg;	/* ���˵��Ĥ��줿�μ���������	*/
T_LCP_CONFIGS lcp_remote_ack_cfg;	/* ���˵��Ĥ�����������		*/

/*
 *  lcp_init -- LCP �⥸�塼��ν����
 */

static void
lcp_init (void)
{
	fsm_init(&lcp_fsm);
	}

/*
 *  lcp_input -- LCP ����
 */

static void
lcp_input (T_NET_BUF *input)
{
	NET_COUNT_PPP_LCP(net_count_ppp_lcp_in_octets,  input->len);
	NET_COUNT_PPP_LCP(net_count_ppp_lcp_in_packets, 1);
	fsm_input(&lcp_fsm, input);
	}

/*
 *  lcp_resetci -- LCP�ι��������ꥻ�åȤ��롣
 */

static void
lcp_resetci (T_PPP_FSM *fsm)
{
#ifdef LCP_CFG_MAGIC

	SYSTIM	time;

#endif	/* of #ifdef LCP_CFG_MAGIC */

	/* ����������ν������ */
	lcp_local_neg_cfg	= lcp_local_def_cfg;
	lcp_local_ack_cfg	= lcp_def_cfg;

	/* ���ι�������ν������ */
	lcp_remote_neg_cfg	= lcp_def_cfg;
	lcp_remote_ack_cfg	= lcp_def_cfg;

#ifdef LCP_CFG_MAGIC

	syscall(get_tim(&time));
	net_srand((unsigned int)time);
	lcp_local_neg_cfg.magic = net_rand();

#endif	/* of #ifdef LCP_CFG_MAGIC */

	auth_reset();
	}

/*
 *  lcp_cilen -- ���������Ĺ�����֤���
 */

static int_t
lcp_cilen (T_PPP_FSM *fsm)
{
	int_t cilen = 0;

	if (lcp_local_neg_cfg.options & LCP_CFG_MRU)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);	/* MRU   */

	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* ACCM  */

#ifdef LCP_CFG_MAGIC

	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* Magic */

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	if (lcp_local_neg_cfg.options & LCP_CFG_PAP)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);	/* PAP   */

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)
		cilen += sizeof(T_PPP_CI_HDR);			/* �ץ�ȥ��밵�� */

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)
		cilen += sizeof(T_PPP_CI_HDR);			/* ���ɥ쥹�����氵�� */

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	return cilen;
	}

/*
 *  lcp_addci -- LCP�ι���������ɲä��롣
 */

static void
lcp_addci (T_PPP_FSM *fsm, T_NET_BUF *output)
{
	uint8_t *buf;

	buf = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/* MRU ���ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_MRU) {
		*buf ++ = LCP_CIT_MRU;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		*((uint16_t*)buf) = htons(lcp_local_neg_cfg.MRU);
		buf += sizeof(uint16_t);
		}

	/* ACCM ���ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM) {
		*buf ++ = LCP_CIT_ACCM;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		ahtonl(buf, lcp_local_neg_cfg.ACCM);
		buf += sizeof(uint32_t);
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number ���ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC) {
		*buf ++ = LCP_CIT_MAGIC;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		ahtonl(buf, lcp_local_neg_cfg.magic);
		buf += sizeof(uint32_t);
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* ǧ�ڥץ�ȥ��륪�ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_PAP) {
		*buf ++ = LCP_CIT_AUTH;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		*((uint16_t*)buf) = htons(PPP_PAP);
		buf += sizeof(uint16_t);
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �ץ�ȥ��밵�̥��ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP) {
		*buf ++ = LCP_CIT_PCOMP;
		*buf ++ = sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* ���ɥ쥹�����氵�̥��ץ������ɲä��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP) {
		*buf ++ = LCP_CIT_ACCOMP;
		*buf ++ = sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */
	}

/*
 *  lcp_ackci -- ACK ����������Ȥ��ν���
 *
 *	�����:	TURE  ACK ������
 *		false ACK �ϰ۾�
 */

static bool_t
lcp_ackci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	/*
	 *  �������������������˴����˰��פ��ʤ���Фʤ�ʤ���
	 *  ���äơ�lcp_addci �Ǻ���������˲��Ϥ��롣
	 */

	/* MRU ���ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_MRU) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	||
		    *buf ++ != LCP_CIT_MRU			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)||
		    *((uint16_t*)buf) != htons(lcp_local_neg_cfg.MRU)	)
			return false;
		buf += sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		}

	/* ACCM ���ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
		    *buf ++ != LCP_CIT_ACCM			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
		    nahcmpl(buf, lcp_local_neg_cfg.ACCM)        )
			return false;
		buf += sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number ���ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
		    *buf ++ != LCP_CIT_MAGIC			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
		    nahcmpl(buf, lcp_local_neg_cfg.magic)       )
			return false;
		buf += sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* ǧ�ڥץ�ȥ��륪�ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_PAP) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	||
		    *buf ++ != LCP_CIT_AUTH			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)||
		    *((uint16_t*)buf) != htons(PPP_PAP)		)
			return false;
		buf += sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �ץ�ȥ��밵�̥��ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP) {
		if (len < sizeof(T_PPP_CI_HDR)			||
		    *buf ++ != LCP_CIT_PCOMP			||
		    *buf ++ != sizeof(T_PPP_CI_HDR))
			return false;
		len -= sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* ���ɥ쥹�����氵�̥��ץ�������Ϥ��롣 */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP) {
		if (len < sizeof(T_PPP_CI_HDR)			||
		    *buf ++ != LCP_CIT_ACCOMP			||
		    *buf ++ != sizeof(T_PPP_CI_HDR))
			return false;
		len -= sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */
	return true;
	}

/*
 *  lcp_nakci -- NAK ����������Ȥ��ν���
 *
 *	�����:	1  NAK ������
 *		0  NAK �ϰ۾�
 */

static int_t
lcp_nakci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_LCP_CONFIGS	new_cfg;
	bool_t		loop = false;	/* �롼�ץХå�������å� */
	uint32_t	cilong;
	uint16_t	cishort, len;
	uint8_t		*buf, cilen;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = lcp_local_neg_cfg;

	/* MRU ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_MRU				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MRU)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort <= lcp_local_neg_cfg.MRU || cishort <= DEF_PPP_MTU)
			new_cfg.MRU = cishort;
		}

	/* ACCM ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_ACCM				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCM)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.ACCM |= cilong;
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_MAGIC				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.magic = cilong;
		loop = true;
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* ǧ�ڥץ�ȥ��륪�ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_AUTH				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PAP)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort == PPP_PAP)
			new_cfg.options &= ~LCP_CFG_PAP;
		else
			return 0;
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �ץ�ȥ��밵�̥��ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_PCOMP				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_PCOMP;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* ���ɥ쥹�����氵�̥��ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_ACCOMP			&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_ACCOMP;
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */

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
	if (fsm->state != PPP_FSM_OPENED) {
		if (loop) {
			syslog(LOG_WARNING, "[PPP/LCP] line looped.");
			lcp_close();
			}
		lcp_local_neg_cfg = new_cfg;
		}
	return 1;
	}

/*
 *  lcp_rejci -- REJ ����������Ȥ��ν���
 *
 *	�����:	1  REJ ������
 *		0  REJ �ϰ۾�
 */

static int_t
lcp_rejci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_LCP_CONFIGS	new_cfg;
	uint32_t	cilong;
	uint16_t	cishort, len;
	uint8_t		*buf;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = lcp_local_neg_cfg;

	/* MRU ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_MRU					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MRU)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort != lcp_local_neg_cfg.MRU)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_MRU;
		}
		
	/* ACCM ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_ACCM					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCM)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		if (cilong != lcp_local_neg_cfg.ACCM)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_ACCM;
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number ���ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_MAGIC					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		if (cilong != lcp_local_neg_cfg.magic)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_MAGIC;
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* ǧ�ڥץ�ȥ��륪�ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_AUTH					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PAP)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort != PPP_PAP)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_PAP;
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �ץ�ȥ��밵�̥��ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_PCOMP				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_PCOMP;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* ���ɥ쥹�����氵�̥��ץ�������Ϥ��롣 */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_ACCOMP			&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_ACCOMP;
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	/* Ĺ���� 0 �Ǥʤ���Х��顼 */
	if (len != 0)
		return 0;

	/* ���������ץ��������ꤹ�롣*/
	if (fsm->state != PPP_FSM_OPENED)
		lcp_local_neg_cfg = new_cfg;

	return 1;
	}

/*
 *  lcp_reqci -- ���ι����������Ϥ��롣
 */

static int_t
lcp_reqci (T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output)
{
#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

	uint32_t	cilong;

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

	uint16_t	code, final, len, cilen, cishort;
	uint8_t		*np, *rp, *ap, *cp, type = 0;

	rp = ap = input->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
				/* rp: REJ��ap: ACK ���� CI �Υݥ���		*/
				/* ���ݤ�����ϡ����� input �˾�񤭤��롣	*/
	len   = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	np    = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	final = PPP_CONFACK;	/* �ǽ�Ū���������륳���� */
	while (len > 0) {
		code = PPP_CONFACK;
		cp   = ap;	/* cp: ���߽������ CI	*/

		if (len < sizeof(T_PPP_CI_HDR)) {

			/* �Ĥ꤬ CI �إå����û�� */
			syslog(LOG_WARNING, "[PPP/LCP] bad CI len: %d.", len);
			cilen = len;	/* �ǡ���Ĺ���۾�ξ��ν���	*/
			len   = 0;	/* �롼�פ���ȴ���롣		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}

		type  = *ap ++;	/* CI �η�		*/
		cilen = *ap ++;	/* CI ��Ĺ��		*/
		if (len < cilen) {

			/* �Ĥ꤬ CI Ĺ���û�� */
			syslog(LOG_WARNING, "[PPP/LCP] bad CI len: %d.", cilen);
			cilen = len;	/* �ǡ���Ĺ���۾�ξ��ν���	*/
			len   = 0;	/* �롼�פ���ȴ���롣		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}
		len -= sizeof(T_PPP_CI_HDR);

		/* CI �η��ˤ��ʬ�����롣*/
		switch (type) {

		case LCP_CIT_MRU:	/* ��������� (Maximum Receive Unit) */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0 */

		 	/* CI Ĺ�����إå� + 2 �����ƥåȤǤʤ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t))
				code = PPP_CONFREJ;
			{
				cishort = ntohs(*(uint16_t*)ap);

				/* �Ǿ������̤�꾮������� NAK */
				if (cishort < MIN_PPP_MTU) {
					*np ++ = LCP_CIT_MRU;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
					*((uint16_t*)np) = htons(MIN_PPP_MTU);
					np  += sizeof(uint16_t);
					code = PPP_CONFNAK;
					}
				else {
					lcp_remote_neg_cfg.MRU = cishort;
					lcp_remote_neg_cfg.options |= LCP_CFG_MRU;
					}
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0 */

			break;

		case LCP_CIT_ACCM:	/* Async Control Character Map */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0 */

		 	/* CI Ĺ�����إå� + 4 �����ƥåȤǤʤ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(lcp_remote_neg_cfg.ACCM, ap);
				lcp_remote_neg_cfg.options |= LCP_CFG_ACCM;
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0 */

			break;

		case LCP_CIT_MAGIC:	/* �ޥ��å��ֹ� */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0 */

		 	/* CI Ĺ�����إå� + 4 �����ƥåȤǤʤ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(cilong, ap);

				/* �ֹ椬��ʬ��Ʊ���ʤ� NAK */
				if (cilong == lcp_local_neg_cfg.magic) {
					cilong = net_rand();
					*np ++ = LCP_CIT_MAGIC;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
					ahtonl(np, cilong);
					np  += sizeof(uint32_t);
					code = PPP_CONFNAK;
					}
				else {
					lcp_remote_neg_cfg.magic = cilong;
					lcp_remote_neg_cfg.options |= LCP_CFG_MAGIC;
					}
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0 */

			break;

#ifdef LCP_CFG_PAP
		/* CHAP �ϼ���ͽ��	*/

		case LCP_CIT_AUTH:	/* ǧ�ڥץ�ȥ��� */

		 	/* CI Ĺ�����إå� + 2 �����ƥåȤ��û���Ȥ��ϥ��顼 */
		 	if (cilen < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t))
				code = PPP_CONFREJ;
			else {
				cishort = ntohs(*(uint16_t*)ap);

				/* ǧ�ڥץ�ȥ���ˤ��ʬ������	*/
				if (cishort == PPP_PAP &&
				    cilen   == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t) &&
			 	    (DEF_LCP_REMOTE_CFGS & LCP_CFG_PAP) != 0)
					lcp_remote_neg_cfg.options |= LCP_CFG_PAP;
				else
					code = PPP_CONFREJ;
				}
			break;

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

		case LCP_CIT_PCOMP:	/* �ץ�ȥ��������̤ϼ���ͽ�� */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0 */

		 	/* CI Ĺ�����إå�Ĺ�����Ǥʤ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR))
				code = PPP_CONFREJ;
			else
				lcp_remote_neg_cfg.options |= LCP_CFG_PCOMP;

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0 */

			break;

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

		case LCP_CIT_ACCOMP:	/* ���ɥ쥹������������ */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0 */

		 	/* CI Ĺ�����إå�Ĺ�����Ǥʤ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR))
				code = PPP_CONFREJ;
			else
				lcp_remote_neg_cfg.options |= LCP_CFG_ACCOMP;

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0 */

			break;

#endif	/* of #ifdef LCP_CFG_ACCOMP */

		default:
			syslog(LOG_WARNING, "[PPP/LCP] unexp opt: %d.", type);
			code  = PPP_CONFREJ;
			break;
			}
endswitch:
		if (code == PPP_CONFNAK) {
			/* CI �η��� Magic Number �ξ�������ơ�NAK �β����	*/
			/* ������ MAX_PPP_FAILURES  ��Ķ��������ݤ��롣	*/
			if (fsm->failures >= MAX_PPP_FAILURES && type != LCP_CIT_MAGIC)
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
 *  lcp_up -- �����³���Ω���� (Phase: Establish �˰ܹԤ���)��
 */

static void
lcp_up (T_PPP_FSM *fsm)
{
	/* ��������������� */
	lcp_local_ack_cfg = lcp_local_neg_cfg;

	/* ���ι������������ */
	lcp_remote_ack_cfg = lcp_remote_neg_cfg;

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

	echo_lowerup();

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

	link_established();
	}

/*
 *  lcp_starting -- �����ؤ򳫻Ϥ��롣
 */

static void
lcp_starting (T_PPP_FSM *fsm)
{
	link_required();
	}

/*
 *  lcp_extcode -- LCP ��ͭ�� CP ����������Ȥ��ν���
 */

static bool_t
lcp_extcode (T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input)
{
#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

	T_NET_BUF *output;

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

	switch (code) {
	case PPP_PROTREJ:
		lcp_rprotrej(fsm, input);
		break;

	case PPP_ECHOREQ:

#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

		if (fsm->state == PPP_FSM_OPENED) {
			syscall(get_net_buf(&output, sizeof(T_PPP_HDR)
			                           + sizeof(T_PPP_CP_HDR)
			                           + sizeof(uint32_t)));
			*(uint32_t*)(output->buf + sizeof(T_PPP_HDR)
			                   + sizeof(T_PPP_CP_HDR)) = lcp_local_ack_cfg.magic;
			IF_SET_PROTO(output, PPP_LCP);
			ppp_cp_output(PPP_ECHOREP, id, output);
			}

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

		break;

	case PPP_ECHOREP:

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

		recv_echo_rep(fsm, id, input);

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

		break;

	case PPP_DISCREQ:
		break;

	default:
		return false;
		break;

		}
	return true;
	}

/*
 *  lcp_rprotrej -- Proto-REJ ����������Ȥ��ν���
 */

static void
lcp_rprotrej (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_PPP_PROTENT	*entry;
	int_t		ix;
	uint16_t	proto;

	if (input->len < sizeof(uint16_t)) {
		syslog(LOG_WARNING, "[PPP/LCP] bad len: %d in recv Proto-REJ.");
		return;
		}

	proto = ntohs(*GET_PPP_HDR(input));

	if (fsm->state != PPP_FSM_OPENED) {
		return;
		}

	/* ��̥ץ�ȥ������������ */
	for (ix = 0; (entry = protocols[ix]) != NULL; ix ++)
		if (entry->proto == proto) {
			(*entry->protrej)();
			return;
			}

	syslog(LOG_WARNING, "[PPP/LCP] unexp proto: %d in recv Proto-REJ.", proto);
	}

/*
 *  lcp_protrej -- Proto-REJ ����������Ȥ��ν���
 */

static void
lcp_protrej (void)
{
	fsm_protreject(&lcp_fsm);
	}

/*
 *  lcp_lowerup -- LCP �����ؤ�ư���롣
 */

void
lcp_lowerup (void)
{
	fsm_lowerup(&lcp_fsm);
	}

/*
 *  lcp_lowerdown -- LCP �����ؤ���ߤ��롣
 */

void
lcp_lowerdown (void)
{
	fsm_lowerdown(&lcp_fsm);
	}

/*
 *  lcp_open -- LCP �Υ�����
 */

void
lcp_open (uint8_t open_mode)
{
	ppp_open_mode = open_mode;	/* �����ץ����ư��⡼��	*/
	fsm_open(&lcp_fsm);
	}

/*
 *  lcp_close -- LCP �Υ�����
 */

void
lcp_close (void)
{
	if (ppp_phase != PPP_PHASE_DEAD)
		ppp_phase = PPP_PHASE_TERMINATE;

	if (ppp_open_mode == PPP_OPEN_PASSIVE && lcp_fsm.state == PPP_FSM_STOPPED) {
		lcp_fsm.state = PPP_FSM_CLOSED;
		lcp_finished(&lcp_fsm);
		}
	else
		fsm_close(&lcp_fsm);
	}

/*
 *  lcp_sprotrej -- ǧ���Ǥ��ʤ��ץ�ȥ��뤬�����Ƥ����Ȥ��ν���
 */

void
lcp_sprotrej (T_NET_BUF *input)
{
	T_NET_BUF	*output;
	/*
	 *  Protocol-Reject �������֤���
	 */

	syscall(get_net_buf(&output, input->len + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));

	memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	memcpy(output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR), input->buf, input->len);

	IF_SET_PROTO(output, PPP_LCP);
	ppp_cp_output(PPP_PROTREJ, ++ lcp_fsm.id, output);
	}

/*
 *  lcp_down -- �����³��������� (Phase: Dead �˰ܹԤ���)��
 */

void
lcp_down (T_PPP_FSM *fsm)
{

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

	echo_lowerdown();

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

	link_down();
	}

/*
 *  lcp_finished -- �����ؤ�λ���롣
 */

void
lcp_finished (T_PPP_FSM *fsm)
{
	link_terminated();
	}

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

/*
 *  recv_echo_rep -- ECHOREP ����������Ȥ��ν���
 */

static void
recv_echo_rep(T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input)
{
	T_PPP_CP_HDR	*hdr;
	uint32_t	magic;

 	hdr = GET_PPP_CP_HDR(input);

 	/* Magic Number ��Ĺ���ʲ��ʤ饨�顼 */
 	if (hdr->len < sizeof(T_PPP_CP_HDR) + sizeof(uint32_t)) {
		syslog(LOG_WARNING, "[PPP/LCP] bad ECHOREP len: %d.", hdr->len);
		return;
		}

	ntoahl(magic, input->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

 	/* �������� Magic Number ����ʬ��Ʊ���ʤ�롼�פ��Ƥ��롣*/
	if ((lcp_local_ack_cfg.options & LCP_CFG_MAGIC) && magic == lcp_local_ack_cfg.magic) {
		syslog(LOG_WARNING, "[PPP/LCP] ECHOREP looped.");
		return;
		}

	echo_pending = 0;
	}

/*
 *  echo_timeout -- ECHO REQ/REP �Υ����ॢ���Ƚ���
 */

static void
echo_timeout (void *arg)
{
	if (timer_running) {
		timer_running = false;
		send_echo_req((T_PPP_FSM *)arg);
		}
	}

/*
 *  send_echo_req -- ECHO REQ ���������롣
 */

static void
send_echo_req (T_PPP_FSM *fsm)
{
	T_NET_BUF	*input;

#if LCP_ECHO_FAILS > 0

	if (echo_pending >= LCP_ECHO_FAILS) {
		syslog(LOG_WARNING, "[PPP/LCP] no reply to ECHOREQ.");
		lcp_close();
		echo_pending = 0;
		}

#endif	/* of #if LCP_ECHO_FAILS > 0 */

	if (fsm->state == PPP_FSM_OPENED) {

		/* ECHOREQ ���������롣*/
		syscall(get_net_buf(&input, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR) + sizeof(uint32_t)));
		*(uint32_t*)(input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)) = lcp_local_ack_cfg.magic;
		IF_SET_PROTO(input, PPP_LCP);
		ppp_cp_output(PPP_ECHOREQ, echo_number ++, input);
		echo_pending ++;

		/* �����ޡ��򥹥����Ȥ��롣*/
		timeout((FP)echo_timeout, fsm, LCP_ECHO_INTERVAL);
		timer_running = true;
		}
	}

/*
 *  echo_lowerup -- ECHO REQ/REP �ε�ư
 */

static void
echo_lowerup (void)
{
	echo_pending  = 0;
	echo_number   = 0;
	timer_running = false;

	send_echo_req(&lcp_fsm);
	}

/*
 *  echo_lowerdown -- ECHO REQ/REP �����
 */

static void
echo_lowerdown (void)
{
	if (timer_running) {
		untimeout((FP)echo_timeout, &lcp_fsm);
		timer_running = false;
		}
	}

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

#endif	/* fo #ifdef SUPPORT_PPP */
