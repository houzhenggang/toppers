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
 *  @(#) $Id: ip_icmp.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/ip_icmp.h,v 1.12.2.2 1999/11/18 08:51:44 peter Exp $
 */
 
#ifndef _IP_ICMP_H_
#define _IP_ICMP_H_

/*
 *  ICMP �إå��������RFC 792
 */

typedef struct t_icmp_hdr {
	uint8_t		type;		/* ��å������η�	*/
	uint8_t		code;		/* ���ַ�		*/
	uint16_t	sum;		/* �����å�����		*/
	union {
		struct id_seq {
			uint16_t	id;
			uint16_t	seq;
			} id_seq;
		T_IN4_ADDR	addr;
		} data;
	} T_ICMP4_HDR;

#define ICMP4_HDR_SIZE			(sizeof(T_ICMP4_HDR))
#define IP4_ICMP4_HDR_SIZE		(IP4_HDR_SIZE + ICMP4_HDR_SIZE)
#define IF_IP4_ICMP4_HDR_SIZE		(IF_IP4_HDR_SIZE + ICMP4_HDR_SIZE)
#define IF_IP4_ICMP4_HDR_OFFSET		(IF_IP4_HDR_SIZE)

#define GET_ICMP4_HDR(nbuf,ihoff)	((T_ICMP4_HDR*)((uint8_t*)((nbuf)->buf) + ihoff))
#define GET_ICMP4_SDU(nbuf,ihoff)	((uint8_t*)((nbuf)->buf) + ihoff + ICMP4_HDR_SIZE)

#define GET_ICMP4_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_IP4_ICMP4_HDR_SIZE(nbuf)	(GET_IP4_HDR_SIZE(GET_IP4_HDR(nbuf)) + ICMP4_HDR_SIZE)
#define GET_IF_IP4_ICMP4_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP4_ICMP4_HDR_SIZE(nbuf))

/*
 *  ��å������η�
 */

#define ICMP4_ECHO_REPLY	UINT_C(0)	/* ����������		*/
#define ICMP4_UNREACH		UINT_C(3)	/* ���顼		*/
#define ICMP4_SOURCE_QUENCH	UINT_C(4)	/* ȯ������		*/
#define ICMP4_REDIRECT		UINT_C(5)	/* �����ѹ�		*/
#define ICMP4_ECHO_REQUEST	UINT_C(8)	/* �������׵�		*/
#define ICMP4_TIME_EXCEEDED	UINT_C(11)	/* ȯ������		*/
#define ICMP4_PARAMETER		UINT_C(12)	/* �ѥ�᡼���۾�	*/
#define ICMP4_TIME_REQUEST	UINT_C(13)	/* �����ॹ������׵�	*/
#define ICMP4_TIME_REPLY	UINT_C(14)	/* �����ॹ����ױ���	*/
#define ICMP4_MASK_REQUEST	UINT_C(17)	/* ���ɥ쥹�ޥ����׵�	*/
#define ICMP4_MASK_REPLY	UINT_C(18)	/* ���ɥ쥹�ޥ�������	*/

/*
 *  ���ַ�
 */

/* ICMP4_UNREACH (3)	*/

#define ICMP4_UNREACH_NET		UINT_C(0)	/* �ͥåȥ��		*/
#define ICMP4_UNREACH_HOST		UINT_C(1)	/* �ۥ���		*/
#define ICMP4_UNREACH_PROTOCOL		UINT_C(2)	/* �ץ�ȥ���		*/
#define ICMP4_UNREACH_PORT		UINT_C(3)	/* �ݡ���		*/
#define ICMP4_UNREACH_FLAG		UINT_C(4)	/* ʬ��			*/
#define ICMP4_UNREACH_SRC_FAIL		UINT_C(5)	/* ��������ϩ		*/
#define ICMP4_UNREACH_NET_UNKNOWN	UINT_C(6)	/* �ͥåȥ������	*/
#define ICMP4_UNREACH_HOST_UNKNOWN	UINT_C(7)	/* �ۥ�������		*/
#define ICMP4_UNREACH_ISOLATED		UINT_C(8)	/* ʬΥ			*/
#define ICMP4_UNREACH_NET_PROHIB	UINT_C(9)	/* 			*/
#define ICMP4_UNREACH_HOST_PROHIB	UINT_C(10)	/* 			*/
#define ICMP4_UNREACH_TOS_NET		UINT_C(11)	/* �ͥåȥ���ؤ�����TOS*/
#define ICMP4_UNREACH_TOS_HOST		UINT_C(12)	/* �ۥ��Ȥؤ�����TOS	*/
#define ICMP4_UNREACH_FILTER_PROHIB	UINT_C(13)	/* 			*/
#define ICMP4_UNREACH_HOST_PRECEDENCE	UINT_C(14)	/* 			*/
#define ICMP4_UNREACH_PRECEDENCE_CUTOFF	UINT_C(15)	/* 			*/

/* ICMP4_REDIRECT (5)	*/

#define ICMP4_REDIRECT_NET		UINT_C(0)	/* �ͥåȥ��		*/
#define ICMP4_REDIRECT_HOST		UINT_C(1)	/* �ۥ���		*/
#define ICMP4_REDIRECT_PORT_AND_NET	UINT_C(2)	/* �ݡ����ֹ�ȥͥå�	*/
#define ICMP4_REDIRECT_PORT_AND_HOST	UINT_C(3)	/* �ݡ����ֹ�ȥۥ���	*/

/*
 *  �����ѿ�
 */

/*
 *  �ؿ����ߥ�졼�����ޥ���
 */

#ifndef ICMP_REPLY_ERROR

#define _tinet_icmp_error(code,data)

#endif	/* of #ifdef ICMP_REPLY_ERROR */

/*
 *  �ؿ�
 */

extern uint_t icmp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);

#ifdef ICMP_REPLY_ERROR

extern void icmp_error (uint8_t code, T_NET_BUF *data);

#endif	/* of #ifdef ICMP_REPLY_ERROR */

/*
 *  TINET �ȼ� API
 */

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

extern void icmp_echo_reply (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

#endif	/* of #ifndef _IP_ICMP_H_ */
