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
 *  @(#) $Id: if_loop.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _IF_LOOP_H_
#define _IF_LOOP_H_

#ifdef SUPPORT_LOOP

/*
 *  ������롼�ץХå����󥿥ե��������إå��ȥ��ɥ쥹
 */

typedef struct t_loop_hdr  { } T_LOOP_HDR;
typedef struct t_loop_addr { } T_LOOP_ADDR;

/*
 *  ���󥿥ե�����������ޥ���
 */

#define T_IF_HDR		T_LOOP_HDR		/* ���󥿥ե������Υإå�	*/
#define T_IF_ADDR		T_LOOP_ADDR		/* ���󥿥ե������Υ��ɥ쥹	*/
#define IF_HDR_ALIGN		4			/* �إå��Υ��饤��ñ��		*/
#define IF_MTU			LOMTU			/* ���󥿥ե������� MTU		*/

#define IF_OUTPUT(o,d,g,t)	looutput(o,t)		/* ���󥿥ե������ν��ϴؿ�	*/
#define IF_RAW_OUTPUT(o,t)	looutput(o,t)		/* ���󥿥ե������ν��ϴؿ������ɥ쥹���̵��*/
#define IF_SET_PROTO(b,p)				/* ���󥿥ե������Υץ�ȥ�������ؿ�	*/
#define IF_GET_IFNET()		loop_get_ifnet()	/* �ͥåȥ�����󥿥ե�������¤�Τ��֤���		*/

/* IPv4 �ط� */

#define IF_PROTO_IP		0			/* ���󥿥ե������� IP �ץ�ȥ������		*/

/* IPv6 �ط� */

#define MAX_IF_MADDR_CNT	0			/* ���󥿥ե������Υޥ�����㥹�ȥ��ɥ쥹����κ��祵����	*/
#define IF_IN6_NEED_CACHE(i)	(false)			/* ����õ������å������Ѥ��롣				*/

/*
 *  ��������
 */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

/*
 *  �ͥåȥ�����󥿥ե������˰�¸���ʤ����եȥ���������
 */

struct t_if_softc { };

/*
 *  �ؿ�
 */

extern T_IFNET *loop_get_ifnet (void);
ER looutput (T_NET_BUF *output, TMO tmout);

/*
 *  ������롼�ץХå����󥿥ե�����������������
 */

extern void	if_loop_output_task(intptr_t exinf);
extern void	if_loop_input_task(intptr_t exinf);

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #ifndef _IF_LOOP_H_ */
