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
 *  @(#) $Id: ppp_fsm.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * fsm.h - {Link, IP} Control Protocol Finite State Machine definitions.
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
 * $FreeBSD: src/usr.sbin/pppd/fsm.h,v 1.6.2.1 1999/08/29 15:47:00 peter Exp $
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
 * $FreeBSD: src/usr.sbin/ppp/fsm.h,v 1.23 1999/12/27 11:54:53 brian Exp $
 *
 *	TODO:
 */

#ifndef _PPP_FSM_H_
#define _PPP_FSM_H_

#ifdef SUPPORT_PPP

/*
 *  ���ִ�����¤��
 */

struct t_ppp_fsm_callbacks;

typedef struct t_fsm {
	struct t_ppp_fsm_callbacks	*callbacks;	/* ������Хå��ؿ�*/
	uint16_t	proto;		/* �ץ�ȥ���				*/
	uint8_t		state;		/* FSM �ξ���				*/
	uint8_t		id;		/* ���ߤ� ID				*/
	uint8_t		reqid;		/* �׵� ID				*/
	uint8_t		seen_ack;	/* �׵���Ф������ ACK/NAK/REJ �����	*/
	int8_t		failures;	/* ��ǧ���� NAK ��			*/
	int8_t		retrans;	/* Configure-Request �ޤ��ϡ�		*/
					/* Terminate-Request �κ������		*/
	} T_PPP_FSM;

#define T_PPP_FSM_DEFINED

/*
 *  ������Хå��ؿ���¤��
 */

typedef struct t_ppp_fsm_callbacks {
	void (*resetci)	(T_PPP_FSM *);	/* �����������ꥻ�åȤ��롣	*/
	int_t  (*cilen)	(T_PPP_FSM *);	/* ���������Ĺ�����֤���		*/
	void (*addci)	(T_PPP_FSM *, T_NET_BUF *);
					/* ������������ɲä��롣		*/
	bool_t (*ackci)	(T_PPP_FSM *, T_NET_BUF *);
					/* ACK ����������Ȥ��ν���	*/
	int_t  (*nakci)	(T_PPP_FSM *, T_NET_BUF *);
					/* NAK ����������Ȥ��ν���	*/
	int_t  (*rejci)	(T_PPP_FSM *, T_NET_BUF *);
					/* REJ ����������Ȥ��ν���	*/
	int_t  (*reqci)	(T_PPP_FSM *, T_NET_BUF *, T_NET_BUF *);
					/* ���ι���������ǧ���롣	*/
	void (*up)	(T_PPP_FSM *);	/* ��󥯤���³���Ω���롣	*/
	void (*down)	(T_PPP_FSM *);	/* ��󥯤���³��������롣	*/
	void (*starting)(T_PPP_FSM *);	/* �����ؤ򳫻Ϥ��롣		*/
	void (*finished)(T_PPP_FSM *);	/* �����ؤ�λ���롣		*/
	void (*retrans)	(T_PPP_FSM *);	/* �������롣			*/
					/* ������ CP ����������Ȥ��ν���	*/
	bool_t  (*extcode)(T_PPP_FSM *, uint8_t, uint8_t, T_NET_BUF *);
	} T_PPP_FSM_CALLBACKS;

/*
 *  FSM �ξ���
 */

#define PPP_FSM_INITIAL		0	/* ̤��³��̤�����ץ�	*/
#define PPP_FSM_STARTING	1	/* ̤��³�������ץ�	*/
#define PPP_FSM_CLOSED		2	/* ��³��  ̤�����ץ�	*/
#define PPP_FSM_STOPPED		3	/* �����ץ������Ԥ�	*/
#define PPP_FSM_CLOSING		4	/* �����桢̤�����ץ�	*/
#define PPP_FSM_STOPPING	5	/* �����桢�����ץ�	*/
#define PPP_FSM_REQSENT		6	/* Config REQ �����Ѥ�	*/
#define PPP_FSM_ACKRCVD		7	/* Config ACK �����Ѥ�	*/
#define PPP_FSM_ACKSENT		8	/* Config ACK �����Ѥ�	*/
#define PPP_FSM_OPENED		9	/* ��³���̿���ǽ	*/

/*
 *  �����ץ����ư��⡼��
 */

#define PPP_OPEN_PASSIVE	false	/* ��ư�����ץ�		*/
#define PPP_OPEN_ACTIVE		true	/* ǽư�����ץ�		*/

/*
 *  �����������ॢ���Ȥδ�����
 */

#define DEF_PPP_TIMEOUT		(3*NET_TIMER_HZ)
					/* RFC1661 �Ǥ�  3 ��			*/
#define MAX_PPP_TERMINATES	2	/* Terminate-Requests �κ���������	*/
					/* RFC1661 �Ǥ�  2 ��			*/
#define MAX_PPP_CONFIGURES	10	/* Configure-Requests �κ���������	*/
					/* RFC1661 �Ǥ� 10 ��			*/
#define MAX_PPP_FAILURES	5	/* Configure-NAK �κ�����ǧ���		*/
					/* RFC1661 �Ǥ�  5 ��			*/

/*
 *  �ؿ�
 */

extern void fsm_init    (T_PPP_FSM *fsm);
extern void fsm_lowerup (T_PPP_FSM *fsm);
extern void fsm_lowerdown(T_PPP_FSM *fsm);
extern void fsm_open    (T_PPP_FSM *fsm);
extern void fsm_close	(T_PPP_FSM *fsm);
extern void fsm_input	(T_PPP_FSM *fsm, T_NET_BUF *data);
extern void fsm_protreject(T_PPP_FSM *fsm);

/*
 *  �ѿ�
 */

extern uint8_t ppp_open_mode;

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_FSM_H_ */
