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
 *  @(#) $Id: icmp6.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet/icmp6.h,v 1.2.2.3 2001/07/06 05:36:35 sumikawa Exp $	*/
/*	$KAME: icmp6.h,v 1.46 2001/04/27 15:09:48 itojun Exp $	*/

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
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _IP_ICMP6_H_
#define _IP_ICMP6_H_

#ifdef SUPPORT_INET6

/*
 *  ICMPv6 �إå�
 */

typedef struct t_icmp6_hdr {
	uint8_t		type;		/* ��å������η�	*/
	uint8_t		code;		/* ���ַ�		*/
	uint16_t	sum;		/* �����å�����		*/
	union {
		uint32_t	data32;
		uint16_t	data16[2];
		uint8_t		data8[4];
		} data;
	} T_ICMP6_HDR;

#define icmp6_data32			data.data32
#define icmp6_data16			data.data16
#define icmp6_data8			data.data8
#define icmp6_pptr			data.data32		/* �ѥ�᡼���۾�	*/
#define icmp6_mtu			data.data32		/* �ѥ�᡼���۾�	*/
#define icmp6_id			data.data16[0]		/* �������׵�ȱ���	*/
#define icmp6_seq			data.data16[1]		/* �������׵�ȱ���	*/

#define ICMP6_HDR_SIZE			(sizeof(T_ICMP6_HDR))
#define IF_IP6_ICMP6_HDR_OFFSET		(IF_IP6_HDR_SIZE)

#define GET_ICMP6_HDR(nbuf,ihoff)	((T_ICMP6_HDR*)((uint8_t*)((nbuf)->buf) + ihoff))
#define GET_ICMP6_SDU(nbuf,ihoff)	((uint8_t*)((nbuf)->buf) + ihoff + ICMP6_HDR_SIZE)

#define GET_IP6_ICMP6_HDR_SIZE(nbuf)	(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ICMP6_HDR_SIZE)
#define GET_IF_IP6_ICMP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP6_ICMP6_HDR_SIZE(nbuf))

/*
 *  ICMP6 ������
 */

#define ICMP6_DST_UNREACH		UINT_C(1)	/* ������ã�Բ�ǽ		*/
#define ICMP6_PACKET_TOO_BIG		UINT_C(2)	/* �ѥ��åȤ��礭�����롣	*/
#define ICMP6_TIME_EXCEEDED		UINT_C(3)	/* TTL ��Ķ�ᤷ����		*/
#define ICMP6_PARAM_PROB		UINT_C(4)	/* IPv6 �إå���������		*/

#define ICMP6_ECHO_REQUEST		UINT_C(128)	/* �������׵�			*/
#define ICMP6_ECHO_REPLY		UINT_C(129)	/* ����������			*/

#define ICMP6_MEMBERSHIP_QUERY		UINT_C(130)	/* ���롼�ץ��оȲ�		*/
#define ICMP6_MEMBERSHIP_REPORT		UINT_C(131)	/* ���롼�ץ������		*/
#define ICMP6_MEMBERSHIP_REDUCTION	UINT_C(132)	/* ���롼�ץ��н�λ		*/

#define MLD_LISTENER_QUERY		UINT_C(130)	/* �ޥ�����㥹�ȼ����ԾȲ�	*/
#define MLD_LISTENER_REPORT		UINT_C(131)	/* �ޥ�����㥹�ȼ��������	*/
#define MLD_LISTENER_DONE		UINT_C(132)	/* �ޥ�����㥹�ȼ����Խ�λ	*/

#define ND_ROUTER_SOLICIT		UINT_C(133)	/* �롼������			*/
#define ND_ROUTER_ADVERT		UINT_C(134)	/* �롼������			*/
#define ND_NEIGHBOR_SOLICIT		UINT_C(135)	/* ��������			*/
#define ND_NEIGHBOR_ADVERT		UINT_C(136)	/* ��������			*/
#define ND_REDIRECT			UINT_C(137)	/* ����ľ��			*/

#define ICMP6_ROUTER_RENUMBERING	UINT_C(138)	/* �롼���ֹ������		*/

#define ICMP6_WRU_REQUEST		UINT_C(139)	/* �׵�Ρ���õ��		*/
#define ICMP6_WRU_REPLY			UINT_C(140)	/* �����Ρ���õ��		*/

#define ICMP6_FQDN_QUERY		UINT_C(139)	/* FQDN �Ȳ�			*/
#define ICMP6_FQDN_REPLY		UINT_C(140)	/* FQDN ����			*/

#define ICMP6_NI_QUERY			UINT_C(139)	/* �Ρ��ɾ���Ȳ�		*/
#define ICMP6_NI_REPLY			UINT_C(140)	/* �Ρ��ɾ������		*/

#define ICMP6_MAX_TYPE			UINT_C(203)	/* ICMP6 �����פκ�����		*/

/*
 *  ICMP6 ������
 */

/* ������ã�Բ�ǽ */

#define ICMP6_DST_UNREACH_NOROUTE	UINT_C(0)	/* ��ã�롼�Ȥʤ���		*/
#define ICMP6_DST_UNREACH_ADMIN		UINT_C(1)	/* �����Ԥˤ��̵�����档	*/
#define ICMP6_DST_UNREACH_NOTEIGHBOR	UINT_C(2)	/* ���ټԤǤϤʤ��ʤä���	*/
#define ICMP6_DST_UNREACH_BEYOND_SCOPE	UINT_C(2)	/* �������פ�Ķ���Ƥ��롣	*/
#define ICMP6_DST_UNREACH_ADDR		UINT_C(3)	/* ���襢�ɥ쥹����ã�Բ�ǽ��	*/
#define ICMP6_DST_UNREACH_NOPORT	UINT_C(4)	/* ����ݡ��Ȥ���ã�Բ�ǽ��	*/

/* TTL Ķ�� */

#define ICMP6_TIME_EXCEED_TRANSIT	UINT_C(0)	/* ž������ TTL==0 �ˤʤä���	*/
#define ICMP6_TIME_EXCEED_REASSEMBLY	UINT_C(1)	/* IP �ƹ����ǥ����ॢ���Ȥ�����*/

/* �إå����� */

#define ICMP6_PARAMPROB_HEADER		UINT_C(0)	/* �إå������������ä���	*/
#define ICMP6_PARAMPROB_NEXT_HEADER	UINT_C(1)	/* ���إå���ǧ���Ǥ��ʤ���	*/
#define ICMP6_PARAMPROB_OPTION		UINT_C(2)	/* ���ץ����ǧ���Ǥ��ʤ���	*/

/* �������� */
#define ND_REDIRECT_ONLINK		UINT_C(0)	/* �����󥯤ؤθ���ľ��	*/
#define ND_REDIRECT_ROUTER		UINT_C(1)	/* �롼���ؤθ���ľ��		*/

/*
 *  ������
 */

							/* ICMPv6 �κ���ڥ�����Ĺ	*/
#define ICMPV6_PAYLOAD_MAXLEN		(IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE))

/*
 *  ��������
 */

typedef struct t_neighbor_solicit_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	/* ���θ�˥��ץ����³�� */
	} T_NEIGHBOR_SOLICIT_HDR;

#define NEIGHBOR_SOLICIT_HDR_SIZE	(sizeof(T_NEIGHBOR_SOLICIT_HDR))
#define IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_NEIGHBOR_SOLICIT_HDR(nbuf,nhoff)	\
					((T_NEIGHBOR_SOLICIT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_NEIGHBOR_SOLICIT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + NEIGHBOR_SOLICIT_HDR_SIZE)

#define GET_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + NEIGHBOR_SOLICIT_HDR_SIZE)
#define GET_IF_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf)	\
					(GET_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  ��������
 */

typedef struct t_neighbor_advert_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	/* ���θ�˥��ץ����³�� */
	} T_NEIGHBOR_ADVERT_HDR;

/* ICMP6 �إå��Υǡ���������� */

#define nd_na_flags_reserved		hdr.data.data32

#define NEIGHBOR_ADVERT_HDR_SIZE	(sizeof(T_NEIGHBOR_ADVERT_HDR))
#define IP6_NEIGHBOR_ADVERT_HDR_SIZE	(IP6_HDR_SIZE + NEIGHBOR_ADVERT_HDR_SIZE)
#define IF_IP6_NEIGHBOR_ADVERT_HDR_SIZE	\
					(IF_IP6_HDR_SIZE + NEIGHBOR_ADVERT_HDR_SIZE)
#define IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_NEIGHBOR_ADVERT_HDR(nbuf,nhoff)	\
					((T_NEIGHBOR_ADVERT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_NEIGHBOR_ADVERT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + NEIGHBOR_ADVERT_HDR_SIZE)

#define GET_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + NEIGHBOR_ADVERT_HDR_SIZE)
#define GET_IF_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  �������Υե饰��nd_na_flags_reserved (hdr.data32) �����ꤹ�롣
 */

#if SIL_ENDIAN == SIL_ENDIAN_BIG

#define ND_NA_FLG_OVERRIDE		ULONG_C(0x20000000)	/* ���٥���å�����	*/
#define ND_NA_FLG_SOLICITED		ULONG_C(0x40000000)	/* ���������ؤα���	*/
#define ND_NA_FLG_ROUTER		ULONG_C(0x80000000)	/* �롼������		*/

#elif SIL_ENDIAN == SIL_ENDIAN_LITTLE

#define ND_NA_FLG_OVERRIDE		ULONG_C(0x00000020)	/* ���٥���å�����	*/
#define ND_NA_FLG_SOLICITED		ULONG_C(0x00000040)	/* ���������ؤα���	*/
#define ND_NA_FLG_ROUTER		ULONG_C(0x00000080)	/* �롼������		*/

#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

/*
 *  �롼������
 */

typedef struct t_router_advert_hdr {
	T_ICMP6_HDR	hdr;
	uint32_t	reachable;		/* [ms] ��ã��ǽ����	*/
	uint32_t	retransmit;		/* [ms] �������������ֳ�	*/
	/* ���θ�˥��ץ����³�� */
	} T_ROUTER_ADVERT_HDR;

/* ICMP6 �إå��Υǡ���������� */

#define nd_ra_current_hoplimit		hdr.data.data8[0]
#define nd_ra_flags			hdr.data.data8[1]
#define nd_ra_router_lifetime		hdr.data.data16[1]	/* [s] �롼��ͭ������	*/

#define ROUTER_ADVERT_HDR_SIZE		(sizeof(T_ROUTER_ADVERT_HDR))
#define IP6_ROUTER_ADVERT_HDR_SIZE	(IP6_HDR_SIZE + ROUTER_ADVERT_HDR_SIZE)
#define IF_IP6_ROUTER_ADVERT_HDR_SIZE	(IF_IP6_HDR_SIZE + ROUTER_ADVERT_HDR_SIZE)
#define IF_IP6_ROUTER_ADVERT_HDR_OFFSET	(IF_IP6_HDR_SIZE)

#define GET_ROUTER_ADVERT_HDR(nbuf,nhoff)	\
					((T_ROUTER_ADVERT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_ROUTER_ADVERT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + ROUTER_ADVERT_HDR_SIZE)

#define GET_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ROUTER_ADVERT_HDR_SIZE)
#define GET_IF_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  �롼�����Υإå��Υե饰
 */

#define ND_RA_FLAG_MANAGED		UINT_C(0x80)
#define ND_RA_FLAG_OTHER		UINT_C(0x40)
#define ND_RA_FLAG_HA			UINT_C(0x20)

/*
 *  �롼������
 */

typedef struct t_router_solicit_hdr {
	T_ICMP6_HDR	hdr;
	} T_ROUTER_SOLICIT_HDR;

/* ICMP6 �إå��Υǡ���������� */

#define nd_rs_reserved			hdr.data.data32

#define ROUTER_SOLICIT_HDR_SIZE		(sizeof(T_ROUTER_SOLICIT_HDR))
#define IP6_ROUTER_SOLICIT_HDR_SIZE	(IP6_HDR_SIZE + ROUTER_SOLICIT_HDR_SIZE)
#define IF_IP6_ROUTER_SOLICIT_HDR_SIZE	(IF_IP6_HDR_SIZE + ROUTER_SOLICIT_HDR_SIZE)
#define IF_IP6_ROUTER_SOLICIT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_ROUTER_SOLICIT_HDR(nbuf,nhoff)	\
					((T_ROUTER_SOLICIT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_ROUTER_SOLICIT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + ROUTER_SOLICIT_HDR_SIZE)

#define GET_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ROUTER_SOLICIT_HDR_SIZE)
#define GET_IF_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf)	\
					(GET_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  ����õ�����ץ����
 */

/* ����õ���إå� */

typedef struct t_neighbor_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	} T_NEIGHBOR_HDR;

/* ����õ�����ץ����إå� */

typedef struct t_nd_opt_hdr {
	uint8_t		type;			/* ���ץ���󥿥���			*/
	uint8_t		len;			/* ���ץ����Ĺ��ñ�̤� 8 �Х���	*/
	} T_ND_OPT_HDR;

#define ND_OPT_HDR_SIZE			(sizeof(T_ND_OPT_HDR))

#define ND_OPT_SOURCE_LINKADDR		UINT_C(1)	/* ������ͥåȥ�����󥿥ե������Υ��ɥ쥹	*/
#define ND_OPT_TARGET_LINKADDR		UINT_C(2)	/* �оݥͥåȥ�����󥿥ե������Υ��ɥ쥹	*/
#define ND_OPT_PREFIX_INFORMATION	UINT_C(3)	/* �ץ�ե��å�������				*/
#define ND_OPT_REDIRECTED_HEADER	UINT_C(4)	/* ������쥯�ȡ��إå�				*/
#define ND_OPT_MTU			UINT_C(5)	/* MTU						*/

#define ND_OPT_PREFIX_INFO_COUNT	UINT_C(6)	/* �ץ�ե��å�������θĿ�			*/
#define ND_OPT_OFF_ARRAY_SIZE		UINT_C(7)	/* ND ���ץ����Υ��ե��åȤ�Ͽ�������󥵥���*/

#define ND_OPT_OFF_ARRAY_IX(t)		((t)-1)		/* ���ե��å�����Υ���ǥå���			*/

/* �ץ�ե��å������ץ���� */

typedef struct t_nd_opt_prefix_info {
	uint8_t		type;		/* ����õ�����ץ���󥿥��� = 3	*/
	uint8_t		len;		/* ���ץ����Ĺ = 8��4=32	*/
	uint8_t		prefix_len;	/* �ץ�ե��å���Ĺ		*/
	uint8_t		flags;		/* �ե饰			*/
	uint32_t	valid;		/* [s] ͭ������			*/
	uint32_t	preferred;	/* [s] �侩ͭ������		*/
	uint32_t	reserved;
	T_IN6_ADDR	prefix;		/* �ץ�ե��å���		*/
	} T_ND_OPT_PREFIX_INFO;

#define ND_OPT_PI_FLAG_ONLINK	UINT_C(0x80)		/* �����󥯥ץ�ե��å���	*/
#define ND_OPT_PI_FLAG_AUTO	UINT_C(0x40)		/* ���ơ��ȥ쥹�����ɥ쥹��ư����*/

/* MTU ���ץ����إå� */

typedef struct t_nd_opt_mtu_hdr {
	uint8_t		type;		/* ���ץ���󥿥���		*/
	uint8_t		len;		/* ���ץ����Ĺ��ñ�̤� 8 �Х���*/
	uint16_t	reserved;
	uint32_t	mtu;		/* MTU				*/
	} T_ND_OPT_MTU_HDR;

/*
 *  ����ľ��
 */

typedef struct t_nd_redirect_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;		/* �롼���Υ��ɥ쥹		*/
	T_IN6_ADDR	dst;		/* ����ľ���ν������ɥ쥹		*/
	/* ���θ�˥��ץ����³�� */
	} T_ND_REDIRECT_HDR;

#define ND_REDIRECT_HDR_SIZE		(sizeof(T_ND_REDIRECT_HDR))

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

typedef struct t_icmp6_ifstat {
	uint32_t	ipv6IfIcmpInMsgs;
	uint32_t	ipv6IfIcmpInErrors;
	uint32_t	ipv6IfIcmpInDestUnreachs;
/*	uint32_t	ipv6IfIcmpInAdminProhibs;*/
	uint32_t	ipv6IfIcmpInTimeExcds;
	uint32_t	ipv6IfIcmpInParmProblems;
	uint32_t	ipv6IfIcmpInPktTooBigs;
	uint32_t	ipv6IfIcmpInEchos;
	uint32_t	ipv6IfIcmpInEchoReplies;
/*	uint32_t	ipv6IfIcmpInRouterSolicits;*/
	uint32_t	ipv6IfIcmpInRouterAdvertisements;
	uint32_t	ipv6IfIcmpInNeighborSolicits;
	uint32_t	ipv6IfIcmpInNeighborAdvertisements;
	uint32_t	ipv6IfIcmpInRedirects;
/*	uint32_t	ipv6IfIcmpInGroupMembQueries;*/
/*	uint32_t	ipv6IfIcmpInGroupMembResponses;*/
/*	uint32_t	ipv6IfIcmpInGroupMembReductions;*/
	uint32_t	ipv6IfIcmpOutMsgs;
	uint32_t	ipv6IfIcmpOutErrors;
	uint32_t	ipv6IfIcmpOutDestUnreachs;
/*	uint32_t	ipv6IfIcmpOutAdminProhibs;*/
/*	uint32_t	ipv6IfIcmpOutTimeExcds;*/
	uint32_t	ipv6IfIcmpOutParmProblems;
	uint32_t	ipv6IfIcmpOutPktTooBigs;
	uint32_t	ipv6IfIcmpOutEchos;
	uint32_t	ipv6IfIcmpOutEchoReplies;
	uint32_t	ipv6IfIcmpOutRouterSolicits;
/*	uint32_t	ipv6IfIcmpOutRouterAdvertisements;*/
	uint32_t	ipv6IfIcmpOutNeighborSolicits;
	uint32_t	ipv6IfIcmpOutNeighborAdvertisements;
/*	uint32_t	ipv6IfIcmpOutRedirects;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembQueries;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembResponses;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembReductions;*/
} T_ICMP6_IFSTAT;

extern T_ICMP6_IFSTAT icmp6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ؿ�
 */

extern uint_t icmp6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void icmp6_error (T_NET_BUF *input, uint8_t type, uint8_t code, uint32_t param);

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

extern void icmp6_echo_reply (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP_ICMP6_H_ */
