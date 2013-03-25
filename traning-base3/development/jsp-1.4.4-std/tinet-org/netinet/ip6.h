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
 *  @(#) $Id: ip6.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet/ip6.h,v 1.2.2.2 2001/07/03 11:01:46 ume Exp $	*/
/*	$KAME: ip6.h,v 1.18 2001/03/29 05:34:30 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
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
 *	@(#)ip.h	8.1 (Berkeley) 6/10/93
 */
 
#ifndef _IP6_H_
#define _IP6_H_

#ifdef SUPPORT_INET6

/*
 *  IPv6 �������RFC2460 ����
 */

#define IPV6_VERSION	6

/*
 *  IPv6 �إå������
 */

typedef struct t_ip6_hdr {
	uint32_t	vcf;		/* Version:        4 bit		*/
					/* Traffic Class:  8 bit		*/
					/* Flow Label:    20 bit		*/
	uint16_t	plen;		/* Payload Length			*/
	uint8_t		next;		/* Next Header				*/
	uint8_t		hlim;		/* Hop Limit				*/
	T_IN6_ADDR 	src;		/* Source Address			*/
	T_IN6_ADDR 	dst;		/* Destination Address			*/
	} T_IP6_HDR;

#define IP6_HDR_SIZE		(sizeof(T_IP6_HDR))

/*
 *  IPv6 �إå���¤�Υ��Х��������ޥ���
 */

#define IP6_MAKE_VCF(v,cf)	(((uint32_t)(v)<<28)|(cf))
#define IP6_VCF_V(vcf)		((uint32_t)(vcf)>>28)
#define IP6_VCF_C(vcf)		(((uint32_t)(vcf)>>20)&ULONG_C(0xff))
#define IP6_VCF_F(vcf)		((uint32_t)(vcf)&ULONG_C(0x000fffff))
#define IP6_VCF_CF(vcf)		((uint32_t)(vcf)&ULONG_C(0x0fffffff))

/*
 *  ��ĥ�إå�
 */

typedef struct t_ip6_ext_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �����ƥå�ñ�̤�Ĺ��	*/
	} T_IP6_EXT_HDR;

/*
 *  ����� (Hop-by-Hop) ���ץ����إå�
 */

typedef struct t_ip6_hbh_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �����ƥå�ñ�̤�Ĺ������������
					 * ���Υ��ץ����إå����ΤΥ����ƥåȿ���
					 * 8 �ǳ�ä��ͤ� - 1 �����롣
					 */
	} T_IP6_HBH_HDR;

/*
 *  ���� (Destination) ���ץ����إå�
 */

typedef struct t_ip6_dest_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �����ƥå�ñ�̤�Ĺ������������
					 * ���Υ��ץ����إå����ΤΥ����ƥåȿ���
					 * 8 �ǳ�ä��ͤ� - 1 �����롣
					 */
	} T_IP6_DEST_HDR;

/* ����� (Hop-by-Hop) ���ץ���� */

#define IP6OPT_PAD1		UINT_C(0x00)	/* 00 0 00000 */
#define IP6OPT_PADN		UINT_C(0x01)	/* 00 0 00001 */
#define IP6OPT_JUMBO		UINT_C(0xc2)	/* 11 0 00010 */
#define IP6OPT_NSAP_ADDR	UINT_C(0xc3)	/* 11 0 00011 */
#define IP6OPT_TUNNEL_LIMIT	UINT_C(0x04)	/* 00 0 00100 */
#define IP6OPT_RTR_ALERT	UINT_C(0x05)	/* 00 0 00101 */

#define IP6OPT_MINLEN		2	/* ���ץ����κ�ûĹ		*/

/* ̤�ΤΥ��ץ����ν����λ��� */

#define IP6OPT_TYPE_SKIP	UINT_C(0x00)	/* ̵�뤹�롣			*/
#define IP6OPT_TYPE_DISCARD	UINT_C(0x40)	/* �ǡ����������˴����롣	*/
#define IP6OPT_TYPE_FORCEICMP	UINT_C(0x80)	/* �˴����ơ�ICMP ���������롣	*/
#define IP6OPT_TYPE_ICMP	UINT_C(0xc0)
		/* �˴����ơ��ޥ�����㥹�ȤǤʤ���� ICMP ���������롣	*/

#define IP6OPT_TYPE(o)		((o)&UINT_C(0xc0))

/*
 *  ��ϩ����إå�
 */

typedef struct t_ip6_rt_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �����ƥå�ñ�̤�Ĺ������������
					 * ���Υ��ץ����إå����ΤΥ����ƥåȿ���
					 * 8 �ǳ�ä��ͤ� - 1 �����롣
					 */
	uint8_t		type;		/* ��ϩ���楿����		*/
	uint8_t		segleft;	/* �������ȤλĤ�		*/
	} T_IP6_RT_HDR;

/*
 *  ������ 0 ��ϩ����إå�
 */

typedef struct t_ip6_rt0_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �����ƥå�ñ�̤�Ĺ������������
					 * ���Υ��ץ����إå����ΤΥ����ƥåȿ���
					 * 8 �ǳ�ä��ͤ� - 1 �����롣
					 */
	uint8_t		type;		/* ��ϩ���楿����		*/
	uint8_t		segleft;	/* �������ȤλĤ�		*/
	uint32_t	reserved;	/* ͽ��				*/
	} T_IP6_RT0_HDR;

/*
 *  ���ҥإå�
 */

typedef struct t_ip6_frag_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		reserved;
	uint16_t	off_flag;	/* ���ե��åȤȥե饰		*/
	uint32_t	ident;		/* ʬ�伱�̻�			*/
	} T_IP6_FRAG_HDR;

/* ���ҥإå��Υ��ե��åȤȥե饰 */

#ifdef SIL_ENDIAN

#if SIL_ENDIAN == SIL_ENDIAN_BIG

#define IP6F_OFF_MASK		UINT_C(0xfff8)		/* ���ե��åȤ��Ф��ޥ���	*/
#define IP6F_RESERVED_MASK	UINT_C(0x0006)		/* ͽ����Ф��ޥ���		*/
#define IP6F_MORE_FRAG		UINT_C(0x0001)		/* ��֥ե饰����		*/

#elif SIL_ENDIAN == SIL_ENDIAN_LITTLE

#define IP6F_OFF_MASK		UINT_C(0xf8ff)		/* ���ե��åȤ��Ф��ޥ���	*/
#define IP6F_RESERVED_MASK	UINT_C(0x0600)		/* ͽ����Ф��ޥ���		*/
#define IP6F_MORE_FRAG		UINT_C(0x0100)		/* ��֥ե饰����		*/

#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

#endif	/* of #ifdef SIL_ENDIAN */

/*
 *  ������
 */

#define IPV6_MAXHLIM	UINT_C(255)	/* �ۥåץ�ߥåȤκ�����				*/
#define IPV6_DEFHLIM	UINT_C(64)	/* �ۥåץ�ߥåȤε�����				*/
#define IPV6_FRAGTTL	UINT_C(60)	/* ʬ�䤵�줿�ǡ�����������¸���֡��á�	*/
#define IPV6_MMTU	UINT_C(1280)	/* �Ǿ� MTU���ڥ����� (1024) + �إå� (256)	*/
#define IPV6_MAXPACKET	UINT_C(65535)	/* �����ܥڥ����ɤ��������ѥ��åȥ�����	*/

/*
 *  IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ���
 */

/*
 *  �ۥåץ�ߥåȤε����ͤϡ��롼�����Τˤ���ѹ�����뤳�Ȥ�����
 */

#if NUM_ND6_DEF_RTR_ENTRY > 0

/* �롼�����Τ����������ϡ����Τ��줿�� */

#define IP_DEFTTL	ip6_defhlim

#else	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/* �롼�����Τ�������ʤ������ͤϴ����� */

#define IP_DEFTTL	IPV6_DEFHLIM

#endif	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

#define IP_HDR_SIZE	IP6_HDR_SIZE
#define T_IP_HDR	T_IP6_HDR

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP6_H_ */
