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
 *  @(#) $Id: ip.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)ip.h	8.2 (Berkeley) 6/1/94
 * $FreeBSD: src/sys/netinet/ip.h,v 1.15.2.1 1999/08/29 16:29:38 peter Exp $
 */
 
#ifndef _IP4_H_
#define _IP4_H_

/*
 *  IPv4 �������RFC791 ����
 */

#define IPV4_VERSION		4

/*
 *  IPv4 �إå������
 */

typedef struct t_ip4_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length �� 4 octets ñ��		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	sum;		/* checksum				*/

	T_IN4_ADDR	src;		/* source address			*/
	T_IN4_ADDR	dst;		/* destination address			*/
	} T_IP4_HDR;

#define IP4_HDR_SIZE		(sizeof(T_IP4_HDR))

/*
 *  IPv4 �إå���¤�Υ��Х��������ޥ���
 */

#define IP4_MAKE_VHL(v,hl)	((uint8_t)(((uint8_t)(v)<<4)|(hl)))
#define IP4_VHL_V(vhl)		((uint8_t)((uint8_t)(vhl)>>4))
#define IP4_VHL_HL(vhl)		((uint8_t)((vhl)&0x0f))

#define IP4_MAKE_FLGOFF(f,o)	((uint16_t)((f)|(o)))
#define IP4_FLGOFF_FLG(f)	((uint16_t)((f)&~IP4_OFFMASK))
#define IP4_FLGOFF_OFF(o)	((uint16_t)((o)&IP4_OFFMASK))

/*
 *  IPv4 �إå��Υե�����ɤ��ͤ����
 */

#define IP4_VHL_BORING	UINT_C(0x45)	/* ���ץ���󤬤ʤ� VHL ��	*/
#define IP4_RF		UINT_C(0x8000)	/* off: ͽ��			*/
#define IP4_DF		UINT_C(0x4000)	/* off: ʬ��ػ�			*/
#define IP4_MF		UINT_C(0x2000)	/* off: ʬ�䤢��			*/
#define IP4_OFFMASK	UINT_C(0x1fff)	/* ���ե��å����Υޥ�����		*/

/*
 *  ������
 */

#define IP4_MAXPACKET	UINT_C(65535)	/* ����ѥ��åȥ�����		*/
#define IP4_MAXTTL	UINT_C(255)	/* TTL ������			*/
#define IP4_DEFTTL	UINT_C(64)	/* TTL ������ (RFC1340)		*/
#define IP4_FRAGTTL	UINT_C(60)	/* ʬ�䤵�줿�ǡ�����������¸���֡��á�*/
#define IP4_MSS		UINT_C(576)	/* ���祻�����ȥ������ε�����	*/

/* IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ��� */

#if defined(SUPPORT_INET4)

#define IP_HDR_SIZE	IP4_HDR_SIZE
#define T_IP_HDR	T_IP4_HDR
#define IP_DEFTTL	IP4_DEFTTL

#endif	/* of #if defined(SUPPORT_INET4) */

#endif	/* of #ifndef _IP4_H_ */
