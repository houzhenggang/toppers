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
 *  @(#) $Id: ppp_lcp.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * lcp.h - Link Control Protocol definitions.
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
 *
 * $FreeBSD: src/usr.sbin/pppd/lcp.h,v 1.6.2.1 1999/08/29 15:47:03 peter Exp $
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
 *
 * $FreeBSD: src/usr.sbin/ppp/lcp.h,v 1.23.2.1 2000/08/19 09:30:04 brian Exp $
 *
 *	TODO:
 */

#ifndef _PPP_LCP_H_
#define _PPP_LCP_H_

#ifdef SUPPORT_PPP

/*
 *  LCP ��ͭ�� PPP ������� (CP) �����楳����
 */

#define PPP_PROTREJ		UINT_C(8)	/* Protocol Reject	*/
#define PPP_ECHOREQ		UINT_C(9)	/* Echo Request		*/
#define PPP_ECHOREP		UINT_C(10)	/* Echo Reply		*/
#define PPP_DISCREQ		UINT_C(11)	/* Discard Request	*/

/*
 *  LCP �ι������� (CI)
 */

/*
 *  CI �η�
 */

#define LCP_CIT_MRU		UINT_C(1)	/* ��������� (Maximum Receive Unit)	*/
#define LCP_CIT_ACCM		UINT_C(2)	/* Async Control Character Map		*/
#define LCP_CIT_AUTH		UINT_C(3)	/* ǧ�ڥץ�ȥ���			*/
#define LCP_CIT_QUALITY		UINT_C(4)	/* �ʼ��ץ�ȥ����̤����			*/
#define LCP_CIT_MAGIC		UINT_C(5)	/* �ޥ��å��ֹ�				*/
#define LCP_CIT_PCOMP		UINT_C(7)	/* �ץ�ȥ��������̤ϼ���ͽ��		*/
#define LCP_CIT_ACCOMP		UINT_C(8)	/* ���ɥ쥹�����������̤ϼ���ͽ��		*/
#define LCP_CIT_FCS_ALTER	UINT_C(9)	/* FCS-Alternatives ��̤����		*/
#define LCP_CIT_SELF_PAD	UINT_C(10)	/* Self-Describing-Padding ��̤����	*/
#define LCP_CIT_CALLBACK	UINT_C(13)	/* Callback ��̤����			*/
#define LCP_CIT_CFRAMES		UINT_C(15)	/* Compound-Frames ��̤����		*/

/*
 *  LCP �ι������󥪥ץ����
 */

typedef struct t_lcp_configs {
	uint32_t	ACCM;		/* ACCM			*/

#ifdef LCP_CFG_MAGIC

	uint32_t	magic;		/* �ޥ��å��ֹ�		*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	uint16_t	MRU;		/* MRU			*/
	uint16_t	options;	/* ���ץ����ե饰	*/
	} T_LCP_CONFIGS;

/*
 *  �ѿ�
 */

extern T_PPP_FSM	lcp_fsm;
extern T_PPP_PROTENT	lcp_protent;
extern T_LCP_CONFIGS	lcp_local_ack_cfg;	/* ���˵��Ĥ��줿�μ���������	*/
extern T_LCP_CONFIGS	lcp_remote_ack_cfg;	/* ���˵��Ĥ�����������		*/

/*
 *  �ؿ�
 */

extern void lcp_lowerup (void);
extern void lcp_lowerdown (void);
extern void lcp_down (T_PPP_FSM *fsm);
extern void lcp_finished (T_PPP_FSM *fsm);
extern void lcp_open (uint8_t open_mode);
extern void lcp_close (void);
extern void lcp_sprotrej (T_NET_BUF *data);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_LCP_H_ */
