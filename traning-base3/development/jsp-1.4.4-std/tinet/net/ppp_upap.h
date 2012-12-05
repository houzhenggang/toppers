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
 *  @(#) $Id: ppp_upap.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * upap.h - User/Password Authentication Protocol definitions.
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
 * $FreeBSD: src/usr.sbin/pppd/upap.h,v 1.6.2.1 1999/08/29 15:47:10 peter Exp $
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
 * $FreeBSD: src/usr.sbin/ppp/pap.h,v 1.11 1999/08/28 01:18:37 peter Exp $
 *
 *	TODO:
 */

#ifndef _PPP_UPAP_H_
#define _PPP_UPAP_H_

#ifdef SUPPORT_PPP

/*
 *  PAP �����楳����
 */

#define PAP_AUTHREQ		UINT_C(1)	/* ǧ���׵�	*/
#define PAP_AUTHACK		UINT_C(2)	/* ǧ�� ACK	*/
#define PAP_AUTHNAK		UINT_C(3)	/* ǧ�� NAK	*/

/*
 *  ���饤����Ȥξ���
 */

#define PAP_CS_INIT		UINT_C(0)	/* ̤��³		*/
#define PAP_CS_CLOSED		UINT_C(1)	/* ��³��̤ǧ��		*/
#define PAP_CS_PENDING		UINT_C(2)	/* ̤��³��ǧ��		*/
#define PAP_CS_AUTHREQ		UINT_C(3)	/* ǧ���׵������Ѥ�	*/
#define PAP_CS_OPEN		UINT_C(4)	/* ACK ����		*/
#define PAP_CS_BADAUTH		UINT_C(5)	/* NAK ����		*/

/*
 *  �����Фξ���
 */

#define PAP_SS_INIT		UINT_C(0)	/* ̤��³		*/
#define PAP_SS_CLOSED		UINT_C(1)	/* ��³��̤ǧ��		*/
#define PAP_SS_PENDING		UINT_C(2)	/* ̤��³��ǧ��		*/
#define PAP_SS_LISTEN		UINT_C(3)	/* ǧ���׵�����Ԥ�	*/
#define PAP_SS_OPEN		UINT_C(4)	/* ACK ����		*/
#define PAP_SS_BADAUTH		UINT_C(5)	/* NAK ����		*/

/*
 *  �ѿ�
 */

extern T_PPP_PROTENT	pap_protent;

/*
 *  �ؿ�
 */

extern void upap_auth_client (void);
extern void upap_auth_server (void);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_UPAP_H_ */
