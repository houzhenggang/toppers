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
 *  @(#) $Id: if_ether.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 *	@(#)if_ether.h	8.3 (Berkeley) 5/2/95
 * $FreeBSD: src/sys/netinet/if_ether.h,v 1.21.2.1 1999/08/29 16:29:31 peter Exp $
 */

#ifndef _IF_ETHER_H_
#define _IF_ETHER_H_

#ifdef SUPPORT_ETHER

/*
 *  Ethernet Address Resolution Protocol.
 *
 *  RFC 826 ����
 */

typedef struct t_ether_arp_hdr {
	uint8_t		shost[ETHER_ADDR_LEN];	/* �����ۥ��Ȥ�ʪ�����ɥ쥹	*/
	uint8_t		sproto[IPV4_ADDR_LEN];	/* �����ۥ��Ȥ� IP ���ɥ쥹	*/
	uint8_t		thost[ETHER_ADDR_LEN];	/* ����о�ʪ�����ɥ쥹		*/
	uint8_t		tproto[IPV4_ADDR_LEN];	/* ����о� IP ���ɥ쥹		*/
	} T_ETHER_ARP_HDR;

#define ETHER_ARP_HDR_SIZE		(sizeof(T_ETHER_ARP_HDR))
#define IF_ARP_ETHER_HDR_SIZE		(IF_HDR_SIZE + ARP_HDR_SIZE + ETHER_ARP_HDR_SIZE)

#define GET_ETHER_ARP_HDR(nbuf)		((T_ETHER_ARP_HDR*)((nbuf)->buf + GET_IF_ARP_HDR_SIZE(nbuf)))

/*
 *  ARP ����å��奨��ȥ�
 */

typedef struct arp_entry {
	T_NET_BUF	*hold;		/* ARP �β���Ԥ����ϥե졼��	*/
	T_IN4_ADDR	ip_addr;	/* IP ���ɥ쥹			*/
	uint16_t	expire;		/* �˴��ޤǤλ��֡�0 �ʤ�̤����	*/
	uint8_t		mac_addr[ETHER_ADDR_LEN];	/* MAC ���ɥ쥹	*/
	} T_ARP_ENTRY;

/*
 *  �ؿ�
 */

extern ER arp_request (T_IF_ADDR *ifaddr, T_IN4_ADDR dst);
extern void arp_input (T_IF_ADDR *ifaddr, T_NET_BUF *input);
extern bool_t arp_resolve (T_IF_ADDR *ifaddr, T_NET_BUF *output, T_IN4_ADDR gw);
extern void arp_init (void);
extern const T_ARP_ENTRY *arp_get_cache (void);

/*
 *  TINET �ȼ� API
 */

#ifdef ARP_CFG_CALLBACK_DUPLICATED

extern bool_t arp_callback_duplicated(uint8_t *shost);

#endif	/* of #ifdef ARP_CFG_CALLBACK_DUPLICATED */

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifndef _IF_ETHER_H_ */
