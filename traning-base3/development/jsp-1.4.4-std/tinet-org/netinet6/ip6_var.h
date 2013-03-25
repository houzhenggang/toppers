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
 *  @(#) $Id: ip6_var.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/ip6_var.h,v 1.10 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: ip6_var.h,v 1.62 2001/05/03 14:51:48 itojun Exp $	*/

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
 *	@(#)ip_var.h	8.1 (Berkeley) 6/10/93
 */
 
#ifndef _IP6_VAR_H_
#define _IP6_VAR_H_

#ifdef SUPPORT_INET6

/*
 *  IPv6 �إå����ڥ����ɥ��������ޥ���
 */

#define IF_IP6_HDR_SIZE			(IF_HDR_SIZE + IP6_HDR_SIZE)

#define GET_IP6_HDR(nbuf)		((T_IP6_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_IP6_SDU(nbuf)		((uint8_t*)((nbuf)->buf) + GET_IF_IP6_HDR_SIZE(nbuf))
#define GET_IP6_NEXT_HDR(nbuf)		((uint8_t*)((nbuf)->buf) + IF_IP6_HDR_SIZE)

#define GET_IP6_HDR_SIZE(iph)		(get_ip6_hdr_size(iph))
#define GET_IP6_SDU_SIZE(iph)		(ntohs((iph)->plen))
#define GET_IF_IP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf))))

#define SET_IP6_SDU_SIZE(iph,slen)	((iph)->plen=htons(slen))

/* ip6_output �Υե饰 */

#define IPV6_OUT_FLG_DAD		0x0100	/* ��ʣ���ɥ쥹����	*/
#define IPV6_OUT_FLG_HOP_LIMIT		0x0200	/* �ۥåץ�ߥåȻ���	*/

/* �ۥåץ�ߥåȥե饰���դ������ۥåץ�ߥå��ͤ�����ޥ��� */

#define IPV6_OUT_GET_HOP_LIMIT(f)	((f)&0x00ff)
#define IPV6_OUT_SET_HOP_LIMIT(f,l)	((f)|(l))

/*
 *  ip6_unknown_opt -- ̤�ΤΥ��ץ����ν���
 *
 *    �����:
 *
 *      0 �ʾ� 			������ץ����Ĺ��
 *      IP6_OPT_RET_ERR (-1)	���顼���ƽ�¦�ǥͥåȥ���Хåե��������롣
 *      IP6_OPT_RET_REL (-2)	���顼���ͥåȥ���Хåե��ϳ�������Ƥ��롣
 */

#define IP6_OPT_RET_ERR		(-1)
#define IP6_OPT_RET_REL		(-2)

/*
 *  IPv4 �� IPv6 �򥳥�ѥ���������򤹤뤿��Υޥ���
 */

#define T_TCP_IP_Q_HDR			T_TCP_IP6_Q_HDR

#define IF_IP_HDR_SIZE			IF_IP6_HDR_SIZE

#define GET_IP_HDR(nbuf)		GET_IP6_HDR(nbuf)
#define GET_IP_SDU(nbuf)		GET_IP6_SDU(nbuf)

#define GET_IP_HDR_SIZE(iph)		GET_IP6_HDR_SIZE(iph)
#define GET_IP_SDU_SIZE(iph)		GET_IP6_SDU_SIZE(iph)
#define GET_IF_IP_HDR_SIZE(nbuf)	GET_IF_IP6_HDR_SIZE(nbuf)

#define SET_IP_SDU_SIZE(iph,len)	SET_IP6_SDU_SIZE(iph,len)

#define IP_OUTPUT(nbuf,tmout)		ip6_output(nbuf,0,tmout)
#define IP_INIT()			ip6_init()
#define IP_REMOVE_OPTIONS(nbuf)		ip6_remove_exthdrs(nbuf)

/*
 *  IPv6 �� MMTU �������Υͥåȥ���Хåե�
 */

typedef struct t_net_buf_ipv6_mmtu {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		unit;	/* ���󥿥ե������ֹ�	*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_HDR_SIZE + IPV6_MMTU];
				/* �Хåե�����		*/
	} T_NET_BUF_IPV6_MMTU;

/*
 *  65536 �����ƥåȥ������Υͥåȥ���Хåե�
 */

typedef struct t_net_buf6_65536 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_IP6_HDR_SIZE + 65536];
				/* �Хåե�����		*/
#if defined(IF_PDU_HDR_PADDING)
	uint8_t		padding[IF_PDU_HDR_PADDING];
#endif				/* �إå���;ʬ		*/
	} T_NET_BUF6_65536;

#ifdef IP6_CFG_FRAGMENT

/*
 *  �ƹ������塼�� IPv6 �إå������
 */

typedef struct t_qip6_hdr {
	uint32_t		vcf;		/* Version:        4 bit		*/
					/* Traffic Class:  8 bit		*/
					/* Flow Label:    20 bit		*/
	uint16_t	plen;		/* Payload Length			*/
	uint8_t		next;		/* Next Header				*/
	uint8_t		hlim;		/* Hop Limit				*/
	T_IN6_ADDR	src;		/* Source Address			*/
	T_NET_BUF	*next_frag;	/* ���� IPv6 �ե饰����	*/
	uint16_t	foff;		/* ���ҥإå��Υ��ե��å�		*/
	uint16_t	flen;		/* ����Ĺ				*/
	uint16_t	ftim;		/* �ƹ��������ॢ����			*/
	uint16_t	dummy1;
	uint8_t		dummy2[sizeof(T_IN6_ADDR) - (sizeof(T_NET_BUF*) + sizeof(uint16_t) * 4)];
	} T_QIP6_HDR;

#define QIP6_HDR_SIZE			(sizeof(T_QIP6_HDR))
#define IF_QIP6_HDR_SIZE		(IF_HDR_SIZE + QIP6_HDR_SIZE)

#define GET_QIP6_HDR(nbuf)		((T_QIP6_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_QIP6_SDU(nbuf)		((uint8_t*)(nbuf)->buf + GET_IF_QIP6_HDR_SIZE(nbuf))

#define GET_QIP6_HDR_SIZE(iph)		((uint8_t)IP6_VHL_HL((iph)->vhl) << 2)
#define GET_IF_QIP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_QIP6_HDR_SIZE(GET_QIP6_HDR(nbuf))))

/*
 *  �ǡ��������ƹ����ѥͥåȥ���Хåե�
 */

typedef struct t_net_buf6_reassm {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		align[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IP6_CFG_FRAG_REASSM_SIZE];
				/* �Хåե�����		*/
	} T_NET_BUF6_REASSM;

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

/*
 *  TCP �κƹ������塼�ˤ����� IPv6 �إå������
 */

typedef struct t_tcp_ip6_q_hdr {
	uint8_t vc;		/* Version:        4 bit		*/
	uint8_t cf;		/* Traffic Class:  8 bit		*/
			/* Flow Label:     4 bit (20 bit)	*/
	uint16_t thoff;	/* TCP �إå��Υ��ե��å�		*/
	uint16_t plen;	/* Payload Length			*/
	uint8_t next;	/* Next Header				*/
	uint8_t hlim;	/* Hop Limit				*/
	T_IN6_ADDR src;	/* Source Address			*/
	T_IN6_ADDR dst;	/* Destination Address			*/
	} T_TCP_IP6_Q_HDR;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

typedef struct t_in6_ifstat {
	uint32_t	ipv6IfStatsInReceives;
	uint32_t	ipv6IfStatsInHdrErrors;
/*	uint32_t	ipv6IfStatsInTooBigErrors;*/
/*	uint32_t	ipv6IfStatsInNoRoutes;*/
	uint32_t	ipv6IfStatsInAddrErrors;
	uint32_t	ipv6IfStatsInUnknownProtos;
	uint32_t	ipv6IfStatsInTruncatedPkts;
/*	uint32_t	ipv6IfStatsInDiscards;*/
/*	uint32_t	ipv6IfStatsInDelivers;*/
/*	uint32_t	ipv6IfStatsOutForwDatagrams;*/
	uint32_t	ipv6IfStatsOutRequests;
	uint32_t	ipv6IfStatsOutDiscards;
	uint32_t	ipv6IfStatsOutFragOKs;
	uint32_t	ipv6IfStatsOutFragFails;
	uint32_t	ipv6IfStatsOutFragCreates;
	uint32_t	ipv6IfStatsReasmReqds;
	uint32_t	ipv6IfStatsReasmOKs;
	uint32_t	ipv6IfStatsReasmFails;
	uint32_t	ipv6IfStatsInMcastPkts;
	uint32_t	ipv6IfStatsOutMcastPkts;
} T_IN6_IFSTAT;

extern T_IN6_IFSTAT in6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ؿ�
 */

extern ER ip6_output (T_NET_BUF *output, uint16_t flags, TMO tmout);
extern void ip6_init (void);
extern uint8_t *ip6_get_prev_hdr (T_NET_BUF *nbuf, uint_t off);
extern uint_t get_ip6_hdr_size (T_IP6_HDR *iph);
extern ER_UINT ip6_nexthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp);
extern ER_UINT ip6_lasthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp);
extern ER_UINT ip6_unknown_opt (T_NET_BUF *input, uint8_t *opt);
extern uint_t dest6_input  (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern uint_t route6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern uint_t frag6_input  (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void frag6_timer (void);
extern ER ip6_remove_exthdrs (T_NET_BUF *nbuf);

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP6_VAR_H_ */
