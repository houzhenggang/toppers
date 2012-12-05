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
 *  @(#) $Id: net.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
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
 */

#ifndef _NET_H_
#define _NET_H_

/*
 *  �Х��ȥ������Ѵ������
 */

#ifdef TARGET_KERNEL_ASP

#if defined(SIL_ENDIAN_BIG)

#undef  SIL_ENDIAN_BIG
#define SIL_ENDIAN_LITTLE	0
#define SIL_ENDIAN_BIG		1
#define SIL_ENDIAN		SIL_ENDIAN_BIG

#elif defined(SIL_ENDIAN_LITTLE)

#undef  SIL_ENDIAN_LITTLE
#define SIL_ENDIAN_LITTLE	0
#define SIL_ENDIAN_BIG		1
#define SIL_ENDIAN		SIL_ENDIAN_LITTLE

#endif	/* of #if defined(SIL_ENDIAN_BIG) */

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#if !defined(SIL_ENDIAN)

#error "SIL_ENDIAN expected."

#else	/* of #if !defined(SIL_ENDIAN) */

#if SIL_ENDIAN == SIL_ENDIAN_BIG

#define ntohs(n)		((uint16_t)n)
#define htons(h)		((uint16_t)h)
#define ntohl(n)		((uint32_t)n)
#define htonl(h)		((uint32_t)h)

#define NTOHS(n)
#define HTONS(h)
#define NTOHL(n)
#define HTONL(h)

/*
 *  ���: IP�إå��ʹߤϡ�4 �Х��ȶ����˥��饤�󤵤�Ƥ������
 *        ����Ȥ��Ƥ��뤬��4 �Х��ȶ����ǥ�����������
 *        �ץ��å��ǡ��ͥåȥ��¦�Υǡ�������4 �Х��ȶ����˥��饤��
 *        ����Ƥ��ʤ����ϡ�ntoahl��ahtonl��nahcmpl ����Ѥ��뤳�ȡ�
 */

#define ntoahl(h,n)		memcpy((uint8_t*)&(h),(n),4)
#define ahtonl(n,h)		memcpy((n),(uint8_t*)&(h),4)

#define nahcmpl(n,h)		memcmp((n),(uint8_t*)&(h),4)

#elif SIL_ENDIAN == SIL_ENDIAN_LITTLE

#ifndef NET_REV_ENDIAN_HWORD

#define NET_REV_ENDIAN_HWORD(d)	((uint16_t)((((uint16_t)(d)&0xff)<<8)|(((uint16_t)(d)>>8)&0xff)))

#endif	/* of #ifndef NET_REV_ENDIAN_HWORD */

#ifndef NET_REV_ENDIAN_WORD

#define NET_REV_ENDIAN_WORD(d)	((uint32_t)((((uint32_t)(d)&0xff)<<24)|(((uint32_t)(d)&0xff00)<<8)| \
				            (((uint32_t)(d)>>8)&0xff00)|(((uint32_t)(d)>>24)&0xff)))

#endif	/* of #ifndef NET_REV_ENDIAN_WORD */

#define ntohs(n)		NET_REV_ENDIAN_HWORD(n)
#define htons(h)		NET_REV_ENDIAN_HWORD(h)
#define ntohl(n)		NET_REV_ENDIAN_WORD(n)
#define htonl(h)		NET_REV_ENDIAN_WORD(h)

#define NTOHS(n)		((n)=NET_REV_ENDIAN_HWORD(n))
#define HTONS(h)		((h)=NET_REV_ENDIAN_HWORD(h))
#define NTOHL(n)		((n)=NET_REV_ENDIAN_WORD(n))
#define HTONL(h)		((h)=NET_REV_ENDIAN_WORD(h))

/*
 *  ���: IP�إå��ʹߤϡ�4 �Х��ȶ����˥��饤�󤵤�Ƥ������
 *        ����Ȥ��Ƥ��뤬��4 �Х��ȶ����ǥ�����������
 *        �ץ��å��ǡ��ͥåȥ��¦�Υǡ�������4 �Х��ȶ����˥��饤��
 *        ����Ƥ��ʤ����ϡ�ntoahl��ahtonl��nahcmpl ����Ѥ��뤳�ȡ�
 */

#ifndef _MACRO_ONLY

extern void rev_memcpy_word (uint8_t *dst, uint8_t *src);
extern int  rev_memcmp_word (uint8_t *data1, uint8_t *data2);

#endif	/* of #ifndef _MACRO_ONLY */

#define ntoahl(h,n)		rev_memcpy_word((uint8_t*)&(h),(n))
#define ahtonl(n,h)		rev_memcpy_word((n),(uint8_t*)&(h))
#define nahcmpl(n,h)		rev_memcmp_word((n),(uint8_t*)&(h))

#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

#endif	/* of #if !defined(SIL_ENDIAN) */

/*
 *  �ץ�ȥ�����̤���ե饰�˴ؤ������
 *
 *    �����׾���
 */

#define PROTO_FLG_PPP_HDLC	ULONG_C(0x00000001)	/* ppp_hdlc.c	*/
#define PROTO_FLG_PPP_FSM	ULONG_C(0x00000002)	/* ppp_fsm.c	*/
#define PROTO_FLG_PPP_AUTH	ULONG_C(0x00000004)	/* ppp_auth.c	*/
#define PROTO_FLG_PPP_LCP	ULONG_C(0x00000008)	/* ppp_lcp.c	*/
#define PROTO_FLG_PPP_IPCP	ULONG_C(0x00000010)	/* ppp_ipcp.c	*/
#define PROTO_FLG_PPP_CCP	ULONG_C(0x00000020)	/* ppp_ccp.c	*/
#define PROTO_FLG_PPP_PAP	ULONG_C(0x00000040)	/* ppp_upap.c	*/
#define PROTO_FLG_PPP_MODEM	ULONG_C(0x00000080)	/* ppp_modem.c	*/
#define PROTO_FLG_PPP		ULONG_C(0x00000100)	/* ppp.c	*/

#define PROTO_FLG_ETHER_NIC	ULONG_C(0x00000001)	/* if_??.c	*/

#define PROTO_FLG_LOOP		ULONG_C(0x00000100)	/* if_loop.c	*/

#define PROTO_FLG_ETHER		ULONG_C(0x00000100)	/* ethernet.c	*/

#define PROTO_FLG_IF		ULONG_C(0x00000800)	/* if.c		*/

#define PROTO_FLG_ARP		ULONG_C(0x00008000)	/* if_ether.c	*/

#define PROTO_FLG_IP4		ULONG_C(0x00010000)	/* ip_*.c	*/
#define PROTO_FLG_ICMP4		ULONG_C(0x00040000)	/* ip_icmp.c	*/

#define PROTO_FLG_IP6		ULONG_C(0x00100000)	/* ip6_*.c	*/
#define PROTO_FLG_ICMP6		ULONG_C(0x00400000)	/* icmp6.c	*/
#define PROTO_FLG_ND6		ULONG_C(0x00800000)	/* nd6_*.c	*/

#define PROTO_FLG_UDP		ULONG_C(0x08000000)	/* udp_*.c	*/

#define PROTO_FLG_TCP		ULONG_C(0x01000000)	/* tcp_*.c	*/

#define PROTO_FLG_NET_BUF	ULONG_C(0x10000000)	/* net_buf.c	*/
#define PROTO_FLG_NET		ULONG_C(0x80000000)	/* route.c, net*.c	*/

/*
 *  ���ɥ쥹���������
 */

#define AT_ETHER		UINT_C(0x01)		/* �������ͥå�		*/
#define AT_INET4		UINT_C(0x10)		/* IPv4 ���ɥ쥹	*/
#define AT_INET6		UINT_C(0x20)		/* IPv6 ���ɥ쥹	*/

#if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY)

/*
 *  TINET �ȼ��ؿ�
 */

extern char *mac2str (char *buf, uint8_t *macaddr);

#endif /* #if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY) */

#endif	/* of #ifndef _NET_H_ */
