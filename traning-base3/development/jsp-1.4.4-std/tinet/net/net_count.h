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
 *  @(#) $Id: net_count.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
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

#ifndef _NET_COUNT_H_
#define _NET_COUNT_H_

/*
 *  �ͥåȥ�����׾���η�¬
 */

#if NET_COUNT_ENABLE != 0

#ifndef _MACRO_ONLY

#ifdef _int64_
typedef uint64_t T_NET_COUNT_VAL;
#else
typedef uint32_t T_NET_COUNT_VAL;
#endif

typedef struct t_net_count {
	T_NET_COUNT_VAL	in_octets;		/* ���������ƥåȿ�	*/
	T_NET_COUNT_VAL	out_octets;		/* ���������ƥåȿ�	*/
	T_NET_COUNT_VAL	in_packets;		/* �����Х��åȿ�	*/
	T_NET_COUNT_VAL	out_packets;		/* �����Х��åȿ�	*/
	T_NET_COUNT_VAL	in_err_packets;		/* �������顼�Х��åȿ�	*/
	T_NET_COUNT_VAL	out_err_packets;	/* �������顼�Х��åȿ�	*/
	} T_NET_COUNT;

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #if NET_COUNT_ENABLE != 0 */

#ifdef SUPPORT_PPP

/* PPP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP

#define NET_COUNT_PPP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_ppp;
extern T_NET_COUNT_VAL	net_count_ppp_no_bufs;	/* net_buf ������Ƽ��Կ�	*/

#endif	/* of #ifndef _MACRO_ONLY */

#define NC_PPP_SIZE	7			/* �����󥿿� */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

#define NET_COUNT_PPP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

/* PPP HDLC */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC

#define NET_COUNT_PPP_HDLC(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_hdlc;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

#define NET_COUNT_PPP_HDLC(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

/* PPP LCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP

#define NET_COUNT_PPP_LCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_lcp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_lcp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

#define NET_COUNT_PPP_LCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

/* PPP IPCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP

#define NET_COUNT_PPP_IPCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_ipcp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_ipcp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

#define NET_COUNT_PPP_IPCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

/* PPP CCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP

#define NET_COUNT_PPP_CCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_ccp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_ccp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP */

#define NET_COUNT_PPP_CCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP */

/* PPP PAP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP

#define NET_COUNT_PPP_PAP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_upap_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_upap_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#define NET_COUNT_PPP_PAP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

/* �롼�ץХå� */

#if NET_COUNT_ENABLE & PROTO_FLG_LOOP

#define NET_COUNT_LOOP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_loop;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#define NET_COUNT_LOOP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_ETHER

/* Ethernet */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER

#define NET_COUNT_ETHER(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_ether;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

#define NET_COUNT_ETHER(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

/* NIC (if_ed) */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC

#define NC_ETHER_NIC_RESETS		0	/* �ꥻ�åȿ�			*/
#define NC_ETHER_NIC_TXB_QOVRS		1	/* �������ޥե����ֵѾ�¥����С���*/
#define NC_ETHER_NIC_TIMEOUTS		2	/* ���������ॢ���ȿ�		*/
#define NC_ETHER_NIC_COLS		3	/* ���ꥸ����			*/
#define NC_ETHER_NIC_OUT_ERR_PACKETS	4	/* �������顼�Х��åȿ�		*/
#define NC_ETHER_NIC_OUT_PACKETS	5	/* �����Х��åȿ�		*/
#define NC_ETHER_NIC_OUT_OCTETS		6	/* ���������ƥåȿ�		*/
#define NC_ETHER_NIC_RXB_QOVRS		7	/* �������ޥե����ֵѾ�¥����С���*/
#define NC_ETHER_NIC_NO_BUFS		8	/* net_buf ������Ƽ��Կ�	*/
#define NC_ETHER_NIC_IN_ERR_PACKETS	9	/* �������顼�Х��åȿ�		*/
#define NC_ETHER_NIC_IN_PACKETS		10	/* �����Х��åȿ�		*/
#define NC_ETHER_NIC_IN_OCTETS		11	/* ���������ƥåȿ�		*/
#define NC_ETHER_NIC_SIZE		12	/* �����󥿿�			*/

#define NET_COUNT_ETHER_NIC(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ether_nic[NC_ETHER_NIC_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#define NET_COUNT_ETHER_NIC(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#endif	/* of #ifdef SUPPORT_ETHER */

/* �ͥåȥ���Хåե� */

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

#define NET_COUNT_NET_BUF(v,c)		((v)+=(c))

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

#define NET_COUNT_NET_BUF(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

#if defined(SUPPORT_INET4)

/* ARP */

#if NET_COUNT_ENABLE & PROTO_FLG_ARP

#define NET_COUNT_ARP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_arp;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

#define NET_COUNT_ARP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

/* IPv4 */

#if NET_COUNT_ENABLE & PROTO_FLG_IP4

#define NC_IP4_FRAG_OUT_FRAGS		0	/* ʬ���������ե饰���ȿ�	*/
#define NC_IP4_FRAG_OUT			1	/* ʬ��������			*/
#define NC_IP4_OUT_ERR_PACKETS		2	/* �������顼�ǡ���������	*/
#define NC_IP4_OUT_PACKETS		3	/* �����ǡ���������		*/
#define NC_IP4_OUT_OCTETS		4	/* ���������ƥåȿ�		*/
#define NC_IP4_FRAG_IN_TMOUT		5	/* ʬ����������ॢ���ȿ�		*/
#define NC_IP4_FRAG_IN_NO_BUF		6	/* ʬ������Хåե������Ƽ��Կ�	*/
#define NC_IP4_FRAG_IN_DROP		7	/* ʬ������˴���		*/
#define NC_IP4_FRAG_IN_OK		8	/* ʬ������ƹ���������		*/
#define NC_IP4_FRAG_IN_FRAGS		9	/* ʬ������ե饰���ȿ�		*/
#define NC_IP4_FRAG_IN			10	/* ʬ�������			*/
#define NC_IP4_OPTS			11	/* ���ץ�������Ͽ�		*/
#define NC_IP4_IN_ERR_PROTO		12	/* �ץ�ȥ��륨�顼��		*/
#define NC_IP4_IN_ERR_ADDR		13	/* ���ɥ쥹���顼��		*/
#define NC_IP4_IN_ERR_VER		14	/* �С�����󥨥顼��		*/
#define NC_IP4_IN_ERR_SHORT		15	/* Ĺ�����顼��			*/
#define NC_IP4_IN_ERR_CKSUM		16	/* �����å����२�顼��		*/
#define NC_IP4_IN_ERR_PACKETS		17	/* �������顼�ǡ���������	*/
#define NC_IP4_IN_PACKETS		18	/* �����ǡ���������		*/
#define NC_IP4_IN_OCTETS		19	/* ���������ƥåȿ�		*/
#define NC_IP4_SIZE			20	/* �����󥿿�			*/

#define NET_COUNT_IP4(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ip4[NC_IP4_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

#define NET_COUNT_IP4(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

/* ICMP4 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP4

#define NET_COUNT_ICMP4(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_icmp4;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#define NET_COUNT_ICMP4(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

/* IPv6 */

#if NET_COUNT_ENABLE & PROTO_FLG_IP6

#define NC_IP6_FRAG_OUT_FRAGS		0	/* ʬ���������ե饰���ȿ�	*/
#define NC_IP6_FRAG_OUT			1	/* ʬ��������			*/
#define NC_IP6_OUT_ERR_PACKETS		2	/* �������顼�ǡ���������	*/
#define NC_IP6_OUT_PACKETS		3	/* �����ǡ���������		*/
#define NC_IP6_OUT_OCTETS		4	/* ���������ƥåȿ�		*/
#define NC_IP6_FRAG_IN_TMOUT		5	/* ʬ����������ॢ���ȿ�		*/
#define NC_IP6_FRAG_IN_NO_BUF		6	/* ʬ������Хåե������Ƽ��Կ�	*/
#define NC_IP6_FRAG_IN_DROP		7	/* ʬ������˴���		*/
#define NC_IP6_FRAG_IN_OK		8	/* ʬ������ƹ���������		*/
#define NC_IP6_FRAG_IN_FRAGS		9	/* ʬ������ե饰���ȿ�		*/
#define NC_IP6_FRAG_IN			10	/* ʬ�������			*/
#define NC_IP6_IN_ERR_PROTO		11	/* �ץ�ȥ��륨�顼��		*/
#define NC_IP6_IN_ERR_ADDR		12	/* ���ɥ쥹���顼��		*/
#define NC_IP6_IN_ERR_VER		13	/* �С�����󥨥顼��		*/
#define NC_IP6_IN_ERR_SHORT		14	/* Ĺ�����顼��			*/
#define NC_IP6_IN_ERR_PACKETS		15	/* �������顼�ǡ���������	*/
#define NC_IP6_IN_PACKETS		16	/* �����ǡ���������		*/
#define NC_IP6_IN_OCTETS		17	/* ���������ƥåȿ�		*/
#define NC_IP6_SIZE			18	/* �����󥿿�			*/

#define NET_COUNT_IP6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ip6[NC_IP6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#define NET_COUNT_IP6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP6

#define NC_ICMP6_OUT_ERR_PACKETS	0	/* �������顼 ICMP �ǡ�����	*/
#define NC_ICMP6_OUT_PACKETS		1	/* ���� ICMP �ǡ�����		*/
#define NC_ICMP6_OUT_OCTETS		2	/* ���� ICMP �����ƥåȿ�		*/
#define NC_ICMP6_IN_ERR_CKSUM		3	/* Ĺ�����顼��			*/
#define NC_ICMP6_IN_ERR_PACKETS		4	/* �������顼 ICMP �ǡ�����	*/
#define NC_ICMP6_IN_PACKETS		5	/* ���� ICMP �ǡ�����		*/
#define NC_ICMP6_IN_OCTETS		6	/* ���� ICMP �����ƥåȿ�		*/
#define NC_ICMP6_SIZE			7	/* �����󥿿�			*/

#define NET_COUNT_ICMP6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL	net_count_icmp6[NC_ICMP6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#define NET_COUNT_ICMP6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ND6

#define NC_ND6_DAD_OUT_PACKETS		0	/* ��ʣ���ɥ쥹����������		*/
#define NC_ND6_NS_OUT_PACKETS		1	/* ��������������		*/
#define NC_ND6_NS_IN_PACKETS		2	/* ��������������		*/
#define NC_ND6_NA_OUT_PACKETS		3	/* ��������������		*/
#define NC_ND6_NA_IN_PACKETS		4	/* �������μ�����		*/
#define NC_ND6_RS_OUT_PACKETS		5	/* �롼���������Ͽ�		*/
#define NC_ND6_RA_IN_PACKETS		6	/* �롼�����μ�����		*/
#define NC_ND6_SIZE			7	/* �����󥿿�			*/

#define NET_COUNT_ND6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL	net_count_nd6[NC_ND6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#define NET_COUNT_ND6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_TCP

/* TCP */

#if NET_COUNT_ENABLE & PROTO_FLG_TCP

#define NC_TCP_CONNECTS			0	/* ǽư�����ץ��		*/
#define NC_TCP_ACCEPTS			1	/* ��ư�����ץ��		*/
#define NC_TCP_RTT_UPDATES		2	/* RTT ������			*/
#define NC_TCP_SEND_RSTS		3	/* ������RST ��			*/
#define NC_TCP_SEND_ACKS		4	/* ������ACK ��			*/
#define NC_TCP_SEND_URG_SEGS		5	/* �������۵ޥ������ȿ�	*/
#define NC_TCP_SEND_DATA_SEGS		6	/* �����ǡ����������ȿ�	*/
#define NC_TCP_SEND_REXMIT_SEGS		7	/* �������������ȿ�		*/
#define NC_TCP_SEND_SEGS		8	/* �����������ȿ�		*/
#define NC_TCP_SEND_CNTL_SEGS		9	/* �������楻�����ȿ�		*/
#define NC_TCP_SEND_DATA_OCTETS		10	/* �����ǡ��������ƥåȿ�	*/
#define NC_TCP_FREE_RCV_QUEUE		11	/* �������塼������		*/
#define NC_TCP_RECV_DUP_SEGS		12	/* ������¿�ſ�			*/
#define NC_TCP_RECV_DROP_SEGS		13	/* �������˴���			*/
#define NC_TCP_RECV_RSTS		14	/* ������RST ��			*/
#define NC_TCP_RECV_DUP_ACKS		15	/* ������¿�� ACK ��		*/
#define NC_TCP_RECV_ACKS		16	/* ������ACK ��			*/
#define NC_TCP_RECV_BAD_CKSUMS		17	/* �����������å�����������	*/
#define NC_TCP_RECV_BAD_HEADERS		18	/* �������إå�������		*/
#define NC_TCP_RECV_URG_SEGS		19	/* �������۵ޥ������ȿ�	*/
#define NC_TCP_RECV_DATA_SEGS		20	/* �����ǡ����������ȿ�	*/
#define NC_TCP_RECV_SEGS		21	/* �����������ȿ�		*/
#define NC_TCP_RECV_DATA_OCTETS		22	/* �����ǡ��������ƥåȿ�	*/
#define NC_TCP_RECV_OCTETS		23	/* ���������ƥåȿ�		*/
#define NC_TCP_SIZE			24	/* �����󥿿�			*/

#define NET_COUNT_TCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_tcp[NC_TCP_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#define NET_COUNT_TCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#endif	/* of #ifdef SUPPORT_TCP */

#ifdef SUPPORT_UDP

/* UDP */

#if NET_COUNT_ENABLE & PROTO_FLG_UDP

#define NET_COUNT_UDP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_udp;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#define NET_COUNT_UDP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#endif	/* of #ifdef SUPPORT_UDP */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

#define NET_COUNT_MIB(v, c)		((v)+=(c))

#else	/* of #ifdef SUPPORT_MIB */

#define NET_COUNT_MIB(v, c)

#endif	/* of #ifdef SUPPORT_MIB */

#endif	/* of #ifndef _NET_COUNT_H_ */
