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
 *  @(#) $Id: ppp_auth.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * auth.c - PPP authentication and phase control.
 *
 * Copyright (c) 1993 The Australian National University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Australian National University.  The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
 *			PPP Secret Key Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1994, Internet Initiative Japan, Inc. All rights reserverd.
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
 * $FreeBSD: src/usr.sbin/ppp/auth.c,v 1.50 1999/12/27 11:43:30 brian Exp $
 *
 *	TODO:
 *		o Implement check against with registered IP addresses.
 */

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_auth.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_upap.h>

#ifdef SUPPORT_PPP

/*
 *  ���
 */

#define PAP_PEND_SERVER		UINT_C(0x01)
#define PAP_PEND_CLIENT		UINT_C(0x02)
#define CHAP_PEND_SERVER	UINT_C(0x04)
#define CHAP_PEND_CLIENT	UINT_C(0x08)

/*
 *  network_phase -- ���ͥ�������Ω
 */

void
network_phase (void)
{
	int_t		num, ix;
	T_PPP_PROTENT	*proto;

	ppp_phase = PPP_PHASE_NETWORK;

	/* ��̥ץ�ȥ���򥪡��ץ󤹤� */
	num = 0;
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++)
#if 0	/* ��α������ػ� */
		if (proto->proto < 0xc000 && proto->open != NULL) {
#else	/* of #if 0 */
		if (proto->open != NULL) {
#endif	/* of #if 0 */
			(*proto->open)();
			if (proto->proto != PPP_CCP)
				num ++;
			}

	if (num == 0)
		/* ��̥ץ�ȥ��뤬�ʤ� */
		lcp_close();
	else
		syslog(LOG_NOTICE, "[PPP] up.");
	}

/*
 *  link_required -- ��󥯤��ߤ��롣
 */

void
link_required (void)
{
	}

/*
 *  link_terminated -- �������Ȥ��ơ���󥯤����Ǥ��롣
 */

void
link_terminated (void)
{
	ppp_phase     = PPP_PHASE_DEAD;
	ppp_open_mode = PPP_OPEN_PASSIVE;
	syslog(LOG_NOTICE, "[PPP] down.");
	}

/*
 *  link_down -- ��󥯤�������롣
 */

void
link_down (void)
{
	int_t		ix;
	T_PPP_PROTENT	*proto;

	/* ��̥ץ�ȥ����������� */
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++) {
		if (proto->proto != PPP_LCP && proto->lowerdown != NULL)
			(*proto->lowerdown)();
		if (proto->proto < 0xc000 && proto->close != NULL)
			(*proto->close)();
		}

	if (ppp_phase != PPP_PHASE_DEAD)
		ppp_phase = PPP_PHASE_TERMINATE;
	}

/*
 *  link_established -- ��󥯤���³����Ω������
 */

void
link_established (void)
{
	int_t		ix;
	T_PPP_PROTENT	*proto;

#if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP)

	int		auth;

#endif	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	/* ��̥ץ�ȥ����ư���� */
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++)
		if (proto->lowerup != NULL)
			(*proto->lowerup)();

	/* ǧ�ڥ��ץ������ǧ���롣��̤������*/

	ppp_phase = PPP_PHASE_AUTHENTICATE;

#if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP)

	auth = 0;

#ifdef AUTH_CFG_SERVER

#if defined(LCP_CFG_CHAP)

	if (lcp_local_ack_cfg.options & LCP_CFG_CHAP) {
		chap_auth_server();
		auth |= CHAP_PEND_SERVER;
		}

#endif	/* of #if defined(LCP_CFG_CHAP) */

#if defined(LCP_CFG_PAP)
	
	if (lcp_local_ack_cfg.options & LCP_CFG_PAP) {
		upap_auth_server();
		auth |= PAP_PEND_SERVER;
		}

#endif	/* of #if defined(LCP_CFG_PAP) */

#endif	/* of #ifdef AUTH_CFG_SERVER */

#ifdef AUTH_CFG_CLIENT

#if defined(LCP_CFG_PAP)
	
	if (lcp_remote_ack_cfg.options & LCP_CFG_PAP) {
		upap_auth_client();
		auth |= PAP_PEND_CLIENT;
		}

#endif	/* of #if defined(LCP_CFG_PAP) */

#endif	/* of #ifdef AUTH_CFG_CLIENT */

	if (auth == 0)
		network_phase();

#else	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	network_phase();

#endif	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	}

/*
 *  auth_reset -- ǧ�ڥ��ץ�����Ƴ�ǧ���롣
 */

void
auth_reset (void)
{
	}

#endif	/* fo #ifdef SUPPORT_PPP */
