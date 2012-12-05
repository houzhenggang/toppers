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
 *  @(#) $Id: if_ppp.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * if_ppp.h - Point-to-Point Protocol definitions.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/sys/net/if_ppp.h,v 1.13.2.1 1999/08/29 16:28:21 peter Exp $
 */

#ifndef _IF_PPP_H_
#define _IF_PPP_H_

#ifdef SUPPORT_PPP

/*
 *  ���󥿥ե�����������ޥ���
 */

#define T_IF_HDR		T_PPP_HDR	/* ���󥿥ե������Υإå�			*/
#define IF_HDR_ALIGN		2		/* �إå��Υ��饤��ñ��			*/
#define IF_MTU			DEF_PPP_MTU	/* ���󥿥ե������� MTU			*/
						/* ���󥿥ե������� IPv4 ���ɥ쥹		*/
#define IF_PROTO_IP		PPP_IP		/* ���󥿥ե������� IP �ץ�ȥ������	*/

#define IF_OUTPUT(o,d,g,t)	ppp_output(o,t)		/* ���󥿥ե������ν��ϴؿ�		*/
#define IF_RAW_OUTPUT(o,t)	ppp_output(o,t)		/* ���󥿥ե������ν��ϴؿ������ɥ쥹���̵��*/
							/* ���󥿥ե������Υץ�ȥ�������ؿ�	*/
#define IF_SET_PROTO(b,p)	(*GET_PPP_HDR(b) = htons(p))
#define IF_GET_IFNET()		ppp_get_ifnet()		/* �ͥåȥ�����󥿥ե�������¤�Τ��֤���		*/

/*
 *  MTU (MRU) �˴ؤ������
 */

#define DEF_PPP_MTU		1500	/* PPP �� ɸ�� MTU	*/
#define MAX_PPP_MTU		16384	/* PPP �� ���� MTU	*/
#define MIN_PPP_MTU		128	/* PPP �� �Ǿ� MTU	*/

/*
 *  PPP �إå�
 */

typedef uint16_t T_PPP_HDR;				/* ��̥ץ�ȥ���		*/

/*
 *  ��������
 */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  �ͥåȥ�����󥿥ե������˰�¸���ʤ����եȥ���������
 */

struct t_if_softc { };

/*
 *  �ؿ�
 */

extern T_IFNET *ppp_get_ifnet (void);
ER ppp_output (T_NET_BUF *data, TMO tmout);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _IF_PPP_H_ */
