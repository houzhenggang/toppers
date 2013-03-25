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
 *  @(#) $Id: if_arp.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * Copyright (c) 1986, 1993
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
 *	@(#)if_arp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_arp.h,v 1.10.2.3 1999/11/19 09:30:31 julian Exp $
 */

#ifndef _IF_ARP_H_
#define _IF_ARP_H_

#ifdef SUPPORT_ETHER

/*
 *  Address Resolution Protocol.
 *
 *  RFC 826 ����
 */

/*
 *  ��¤��
 */

/* ARP �إå� */

typedef struct t_arp_hdr {
	uint16_t	hrd_addr;	/* ʪ�����ɥ쥹�ե����ޥå�	*/
	uint16_t	proto;		/* �ץ�ȥ���			*/
	uint8_t		hdr_len;	/* ʪ�����ɥ쥹Ĺ		*/
	uint8_t		proto_len;	/* �ץ�ȥ���Ĺ			*/
	uint16_t	opcode;		/* ̿�ᥳ����			*/
	} T_ARP_HDR;

#define ARP_HDR_SIZE			(sizeof(T_ARP_HDR))
#define IF_ARP_HDR_SIZE			(IF_HDR_SIZE + ARP_HDR_SIZE)

#define GET_ARP_HDR(nbuf)		((T_ARP_HDR*)((nbuf)->buf + IF_HDR_SIZE))

#define GET_IF_ARP_HDR_SIZE(nbuf)	(IF_HDR_SIZE + ARP_HDR_SIZE)

/* hrd_addr��ʪ�����ɥ쥹�ե����ޥåȤ��� */

#define ARPHRD_ETHER	1	/* Ethernet	*/

/* opcode, ̿�ᥳ���ɤ��� */

#define ARPOP_REQUEST		UINT_C(1)	/* ���ɥ쥹����׵�		*/
#define ARPOP_REPLY		UINT_C(2)	/* ���ɥ쥹������		*/
#define ARPOP_REV_REQUEST	UINT_C(3)	/* �ץ�ȥ��롦���ɥ쥹����׵�	*/
#define ARPOP_REV_REPLY		UINT_C(4)	/* �ץ�ȥ��롦���ɥ쥹����׵�	*/
#define ARPOP_INV_REQUEST	UINT_C(8)	/* ��ü�����׵�			*/
#define ARPOP_INV_REPLY		UINT_C(9)	/* ��ü�����׵�			*/

/*
 *  �������ͥåȥɥ饤�Х⥸�塼��ǻ��Ѥ���� ARP ����
 */

typedef struct arpcom {
	uint8_t		mac_addr[ETHER_ADDR_LEN];
	} T_ARPCOM;

/*
 *  ARP ����å��幹�������ޤ����
 */

#define ARP_TIMER_TMO		(60*NET_TIMER_HZ)	/* �����ॢ���ȡ�60 [s]	*/

/*
 *  �ѿ�
 */

extern const uint8_t	ether_broad_cast_addr[ETHER_ADDR_LEN];

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifndef _IF_ARP_H_ */
