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
 *  @(#) $Id: tcp.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)tcp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/tcp.h,v 1.10.2.1 1999/08/29 16:29:52 peter Exp $
 */
 
#ifndef _TCP_H_
#define _TCP_H_

/*
 *  TCP �إå���RFC 793 ����
 */

typedef struct t_tcp_hdr {
	uint16_t	sport;		/* �������ݡ����ֹ�			*/
	uint16_t	dport;		/* ����ݡ����ֹ�			*/

	uint32_t	seq;		/* SEQ �ֹ�				*/

	uint32_t	ack;		/* ACK �ֹ�				*/

	uint8_t		doff;		/* �ǡ������ե��å�(���4�ӥå�)	*/
	uint8_t		flags;		/* �ե饰(����6�ӥå�)			*/
	uint16_t	win;		/* ������ɥ�����			*/

	uint16_t	sum;		/* �����å�����				*/
	uint16_t	urp;		/* �۵ޥݥ���				*/
	} T_TCP_HDR;

#define TCP_HDR_SIZE			(sizeof(T_TCP_HDR))

/*
 *  TCP �إå���¤�Υ��Х��������ޥ���
 */

#define TCP_MAKE_DATA_OFF(o)	((uint8_t)(((uint8_t)(o) << 2) & 0xf0))
#define TCP_DATA_OFF(o)		(((uint8_t)(o) & UINT_C(0xf0)) >> 2)
#define TCP_HDR_LEN(o)		(TCP_DATA_OFF(o))

/*
 *  TCP �إå��Υե饰�ե�����ɤ��ͤ����
 */

#define TCP_FLG_FIN		UINT_C(0x01)	/* FIN:	�ǽ�			*/
#define TCP_FLG_SYN		UINT_C(0x02)	/* SYN:	Ʊ��			*/
#define TCP_FLG_RST		UINT_C(0x04)	/* RST:	���ͥ������Υꥻ�å�	*/
#define TCP_FLG_PUSH		UINT_C(0x08)	/* PUSH:�ץå��嵡ǽ		*/
#define TCP_FLG_ACK		UINT_C(0x10)	/* ACK:	�������		*/
#define TCP_FLG_URG		UINT_C(0x20)	/* URG:	�۵޾���		*/

/*
 *  TCP ���ץ��������
 */

/* ���ץ����η� */

#define TCP_OPT_EOL		UINT_C(0)	/* �ǽ�				*/
#define TCP_OPT_NOP		UINT_C(1)	/* ���⤷�ʤ�			*/
#define TCP_OPT_MAXSEG		UINT_C(2)	/* ���祻������Ĺ		*/
#define TCP_OPT_WINDOW		UINT_C(3)	/* ������ɥ��������		*/
#define TCP_OPT_SACK_PERM	UINT_C(4)	/* ���� ACK ����		*/
#define TCP_OPT_SACK		UINT_C(5)	/* ���� ACK			*/
#define TCP_OPT_TIMESTAMP	UINT_C(8)	/* �����ॹ�����		*/
#define TCP_OPT_CC		UINT_C(11)	/* ��³�������			*/
#define TCP_OPT_CCNEW		UINT_C(12)	/* ��³�������			*/
#define TCP_OPT_CCECHO		UINT_C(13)	/* ��³�������			*/

/* ���ץ�����Ĺ�� */

#define TCP_OPT_LEN_MAXSEG	4		/* ���祻������Ĺ		*/
#define TCP_OPT_LEN_WINDOW	3		/* ������ɥ��������		*/
#define TCP_OPT_LEN_SACK_PERM	4		/* ���� ACK ����		*/
#define TCP_OPT_LEN_SACK	5		/* ���� ACK			*/
#define TCP_OPT_LEN_TIMESTAMP	10		/* �����ॹ�����		*/
#define TCP_OPT_LEN_CC		6		/* ��³�������			*/
#define TCP_OPT_LEN_CCNEW	6		/* ��³�������			*/
#define TCP_OPT_LEN_CCECHO	6		/* ��³�������			*/

/*
 *  TCP ���祻�����ȥ�����
 */

/*
 *  IPv4 �� TCP ���祻�����ȥ�����
 *  IP4_MSS �� 576 �ǡ�ɸ��� IPv4 �إå�Ĺ (20) ��
 *  TCP �إå�Ĺ (20) ��������� 536 �Ǥ��뤬��512 ��ɸ��Ȥ��롣
 */

#define TCP_MSS			UINT_C(512)

/*
 *  IPv6 �� TCP ���祻�����ȥ�����
 *  IPV6_MMTU �� 1280 �ǡ�ɸ��� IPv6 �إå�Ĺ (40) ��
 *  TCP �إå�Ĺ (20) ��������� 1220 �Ǥ��뤬��1024 ��ɸ��Ȥ��롣
 */

#define TCP6_MSS		UINT_C(1024)

/*
 *  TCP �Ǿ��������ȥ�����
 *
 *  256�ʺǾ���� MTU��- 40 = 216
 */

#define TCP_MINMSS		UINT_C(216)

/*
 *  TCP ���祦����ɥ�������
 */

#define MAX_TCP_WIN_SIZE	UINT_C(65535)

#endif	/* of #ifndef _TCP_H_ */
