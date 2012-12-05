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
 *  @(#) $Id: ppp.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
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

#ifndef _PPP_H_
#define _PPP_H_

/*
 *  PPP �إå��Υץ�ȥ���ե�����ɤ���
 */

#define PPP_IP		UINT_C(0x0021)		/* IP   */

#define PPP_IPCP	UINT_C(0x8021)		/* IPCP */
#define PPP_CCP		UINT_C(0x80fd)		/* CCP */

#define PPP_LCP		UINT_C(0xc021)		/* LCP  */
#define PPP_PAP		UINT_C(0xc023)		/* PAP  */
#define PPP_LQR		UINT_C(0xc025)		/* LQR  */
#define PPP_CHAP	UINT_C(0xc223)		/* CHAP */

#define GET_PPP_HDR(nbuf)	((T_PPP_HDR*)((nbuf)->buf))

/*
 *  ��󥯤ξ���
 */

#define PPP_PHASE_DEAD		0
#define PPP_PHASE_INITIALIZE	1
#define PPP_PHASE_DORMANT	2
#define PPP_PHASE_ESTABLISH	3
#define PPP_PHASE_AUTHENTICATE	4
#define PPP_PHASE_CALLBACK	5
#define PPP_PHASE_NETWORK	6
#define PPP_PHASE_TERMINATE	7
#define PPP_PHASE_HOLDOFF	8

/*
 *  PPP ������� (CP) �إå���¤��
 */

typedef struct t_ppp_cp_hdr {
	uint8_t		code;		/* ���楳����	*/
	uint8_t		id;		/* ���̻�	*/
	uint16_t	len;		/* Ĺ��		*/
	} T_PPP_CP_HDR;

#define GET_PPP_CP_HDR(nbuf)	((T_PPP_CP_HDR*)((nbuf)->buf + sizeof(T_PPP_HDR)))

/*
 *  PPP ������� (CP) �����楳����
 */

#define PPP_VENDER		UINT_C(0)	/* Vender Specific		*/
#define PPP_CONFREQ		UINT_C(1)	/* Configuration Request	*/
#define PPP_CONFACK		UINT_C(2)	/* Configuration ACK		*/
#define PPP_CONFNAK		UINT_C(3)	/* Configuration NAK		*/
#define PPP_CONFREJ		UINT_C(4)	/* Configuration Reject		*/
#define PPP_TERMREQ		UINT_C(5)	/* Termination Request		*/
#define PPP_TERMACK		UINT_C(6)	/* Termination ACK		*/
#define PPP_CODEREJ		UINT_C(7)	/* Code Reject			*/

/*
 * �������� (CI) �إå�
 */

typedef struct t_ppp_ci_hdr {
	uint8_t		type;		/* CI �η�	*/
	uint8_t		len;		/* Ĺ��		*/
	} T_PPP_CI_HDR;

#endif	/* of #ifndef _PPP_H_ */
