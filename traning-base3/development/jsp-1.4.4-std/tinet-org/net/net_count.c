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
 *  @(#) $Id: net_count.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1994, 1995
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
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1994, 1995
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
 */

/* 
 *  �ͥåȥ�����׾���η�¬
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>
#include <net/net_count.h>

/*
 *  ��¬���ѿ�
 */

#ifdef SUPPORT_PPP

#if NET_COUNT_ENABLE & PROTO_FLG_PPP

T_NET_COUNT	net_count_ppp;
T_NET_COUNT_VAL	net_count_ppp_no_bufs;		/* net_buf ������Ƽ��Կ�	*/

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP

T_NET_COUNT_VAL	net_count_ppp_lcp_in_octets;
T_NET_COUNT_VAL	net_count_ppp_lcp_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP

T_NET_COUNT_VAL	net_count_ppp_ipcp_in_octets;
T_NET_COUNT_VAL	net_count_ppp_ipcp_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP

T_NET_COUNT_VAL	net_count_ppp_upap_in_octets;
T_NET_COUNT_VAL	net_count_ppp_upap_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC

T_NET_COUNT	net_count_hdlc;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

#if NET_COUNT_ENABLE & PROTO_FLG_LOOP

T_NET_COUNT	net_count_loop;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_ETHER

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER

T_NET_COUNT	net_count_ether;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC

T_NET_COUNT_VAL net_count_ether_nic[NC_ETHER_NIC_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#endif	/* of #ifdef SUPPORT_ETHER */

#if defined(SUPPORT_INET4)

#if NET_COUNT_ENABLE & PROTO_FLG_ARP

T_NET_COUNT	net_count_arp;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

#if NET_COUNT_ENABLE & PROTO_FLG_IP4

T_NET_COUNT_VAL net_count_ip4[NC_IP4_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP4

T_NET_COUNT	net_count_icmp4;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#if NET_COUNT_ENABLE & PROTO_FLG_IP6

T_NET_COUNT_VAL net_count_ip6[NC_IP6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP6

T_NET_COUNT_VAL	net_count_icmp6[NC_ICMP6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ND6

T_NET_COUNT_VAL	net_count_nd6[NC_ND6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_TCP

#if NET_COUNT_ENABLE & PROTO_FLG_TCP

T_NET_COUNT_VAL net_count_tcp[NC_TCP_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#endif	/* of #ifdef SUPPORT_TCP */

#ifdef SUPPORT_UDP

#if NET_COUNT_ENABLE & PROTO_FLG_UDP

T_NET_COUNT	net_count_udp;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#endif	/* of #ifdef SUPPORT_PPP */
