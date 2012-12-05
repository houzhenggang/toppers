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
 *  @(#) $Id: in_subr.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/tcp_timer.h>

#include <net/if_var.h>

#if defined(SUPPORT_INET4)

/*
 *  in4_get_ifaddr -- ���󥿥ե����������ꤵ��Ƥ��륢�ɥ쥹���֤���
 */

const T_IN4_ADDR *
in4_get_ifaddr (int_t index)
{
	T_IFNET		*ifp = IF_GET_IFNET();

	return &ifp->in_ifaddr.addr;
	}

/*
 *  ip2str -- IPv4 ���ɥ쥹��ʸ������Ѵ����롣
 */

char *
ip2str (char *buf, const T_IN4_ADDR *ipaddr)
{
	static char	addr_sbuf[NUM_IPV4ADDR_STR_BUFF][sizeof("123.123.123.123")];
	static int_t	bix = NUM_IPV4ADDR_STR_BUFF;

	char *start;

	if (buf == NULL) {
		syscall(wai_sem(SEM_IP2STR_BUFF_LOCK));
		buf = addr_sbuf[-- bix];
		if (bix <= 0)
			bix = NUM_IPV4ADDR_STR_BUFF;
		syscall(sig_sem(SEM_IP2STR_BUFF_LOCK));
		}

	start = buf;
	buf += convert_hexdigit(buf, (uint_t)((*ipaddr >> 24) & 0xff), 10, 0, ' ');
	*(buf ++) = '.';
	buf += convert_hexdigit(buf, (uint_t)((*ipaddr >> 16) & 0xff), 10, 0, ' ');
	*(buf ++) = '.';
	buf += convert_hexdigit(buf, (uint_t)((*ipaddr >>  8) & 0xff), 10, 0, ' ');
	*(buf ++) = '.';
	buf += convert_hexdigit(buf, (uint_t)((*ipaddr      ) & 0xff), 10, 0, ' ');
	*buf = '\0';
	return start;
	}

/*
 *  in4_set_header -- IPv4 �إå������ꤹ�롣
 */

ER
in4_set_header (T_NET_BUF *nbuf, uint_t len,
                T_IN4_ADDR *dstaddr, T_IN4_ADDR *srcaddr, uint8_t proto, uint8_t ttl)
{
	T_IP4_HDR	*ip4h = GET_IP4_HDR(nbuf);
	T_IFNET		*ifp = IF_GET_IFNET();

	/* IP �إå������ꤹ�롣*/
	ip4h->vhl	= IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
	ip4h->len	= htons(IP4_HDR_SIZE + len);
	ip4h->proto	= proto;
	ip4h->ttl	= ttl;
	ip4h->type	= 0;
	ip4h->id	= ip4h->flg_off = ip4h->sum = 0;

	/* IP ���ɥ쥹�����ꤹ�롣*/
	ip4h->dst	= htonl(*dstaddr);

	if (srcaddr == NULL || *srcaddr == IPV4_ADDRANY)
		ip4h->src = htonl(ifp->in_ifaddr.addr);
	else
		ip4h->src = htonl(*srcaddr);

	return E_OK;
	}

/*
 *  in4_get_datagram -- IPv4 �ǡ�����������������إå������ꤹ�롣
 */

ER
in4_get_datagram (T_NET_BUF **nbuf, uint_t len, uint_t maxlen,
                  T_IN4_ADDR *dstaddr, T_IN4_ADDR *srcaddr,
                  uint8_t proto, uint8_t ttl, ATR nbatr, TMO tmout)
{
	ER	error;
	uint_t	align;

	/* �ǡ���Ĺ�� 4 �����ƥåȶ�����Ĵ�����롣*/
	align = (len + 3) >> 2 << 2;

	/* �ͥåȥ���Хåե���������롣*/
	if ((error = tget_net_buf_ex(nbuf, (uint_t)(IF_IP4_HDR_SIZE + align),
	                                   (uint_t)(IF_IP4_HDR_SIZE + maxlen), nbatr, tmout)) != E_OK)
		return error;

	/*
	 *  ����礭�ʥ������Υͥåȥ���Хåե������������Τ�Ĺ����Ĵ�����롣
	 *  ��꾮���ʥ������Υͥåȥ���Хåե��γ����ϡ�����������ɥХåե���
	 *  �ʥ��ԡ���ǽ�ǻ��Ѥ��졢�ºݤ���������ޤǡ��ǡ����������Ϸ���Ǥ��ʤ���
	 */
	if ((nbatr & NBA_SEARCH_ASCENT) != 0)
		(*nbuf)->len = (uint16_t)(IF_IP4_HDR_SIZE + len);

	/* IP �إå������ꤹ�롣*/
	if ((error = in4_set_header(*nbuf, len, dstaddr, srcaddr, proto, ttl)) != E_OK)
		return error;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset((GET_IP4_SDU(*nbuf) + len), 0, (size_t)(align - len));

	return E_OK;
	}

/*
 *  in4_cksum -- IPv4 �Υȥ�󥹥ݡ����إإå��Υ����å������׻����롣
 *
 *  ���: ����ͤϥͥåȥ���Х��ȥ�����
 */

uint16_t
in4_cksum (T_NET_BUF *nbuf, uint8_t proto, uint_t off, uint_t len)
{
	uint32_t	sum;
	uint_t		align;

	/* 4 �����ƥåȶ����Υǡ���Ĺ */
	align = (len + 3) >> 2 << 2;

	/* 4 �����ƥåȶ����ޤǥѥǥ��󥰤����롣*/
	if (align > len)
		memset((uint8_t*)nbuf->buf + off + len, 0, (size_t)(align - len));

	sum = in_cksum_sum(nbuf->buf + off, align)
	    + in_cksum_sum(&GET_IP4_HDR(nbuf)->src, sizeof(T_IN4_ADDR) * 2)
	    + len + proto;
	sum = in_cksum_carry(sum);

	return (uint16_t)(~htons((uint16_t)sum));
	}

/*
 *  in_cksum -- �����å�����׻��ؿ���IPv4��ICMPv4 ��
 *
 *  ���: data �� 4 �����ƥå�ñ�̤ǥѥǥ��󥰤��뤳�ȡ�
 *        data �� 2 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��ʤ���
 *        �㳰��ȯ�������ǽ�������롣
 *        len  �� 4 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��뤳�ȡ�
 *
 *        ����ͤϥͥåȥ���Х��ȥ�����
 */

uint16_t
in_cksum (void *data, uint_t len /*�����ƥå�ñ��*/)
{
	uint16_t	sum;

	sum = (uint16_t)in_cksum_carry(in_cksum_sum(data, len));
	return (uint16_t)(~htons(sum));
	}

/*
 *  in4_is_dstaddr_accept -- ���襢�ɥ쥹�Ȥ����������������å����롣
 *
 *    ���: dstaddr �ϡ�
 *          TINET-1.2 ����ͥåȥ���Х��ȥ�������
 *          TINET-1.1 �ޤǤϡ��ۥ��ȥХ��ȥ�����
 */

bool_t
in4_is_dstaddr_accept (T_IN4_ADDR *myaddr, T_IN4_ADDR *dstaddr)
{
	if (*myaddr == IPV4_ADDRANY)
		return ntohl(*dstaddr) == IF_GET_IFNET()->in_ifaddr.addr;
	else
		return ntohl(*dstaddr) == *myaddr;
	}

/*
 * in4_ifawithifp -- ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
 *                   �ͥåȥ�����󥿥ե���������õ�����롣
 *                   in6_ifawithifp �򥷥ߥ�졼�Ȥ�������ǡ�
 *                   ���顼���֤����ȤϤʤ���
 */

T_IN4_IFADDR *
in4_ifawithifp (T_IFNET *ifp, T_IN4_ADDR *dst)
{
	return &ifp->in_ifaddr;
	}

/*
 *  in4_add_ifaddr -- ���󥿥ե������� IPv4 ���ɥ쥹�����ꤹ�롣
 */

ER
in4_add_ifaddr (T_IN4_ADDR addr, T_IN4_ADDR mask)
{
	T_IFNET	*ifp = IF_GET_IFNET();

	ifp->in_ifaddr.addr = addr;
	ifp->in_ifaddr.mask = mask;
	return E_OK;
	}

#if NUM_ROUTE_ENTRY > 0

/*
 *  in4_add_route -- ��ϩɽ�˥���ȥ�����ꤹ�롣
 */

ER
in4_add_route (int_t index, T_IN4_ADDR target, T_IN4_ADDR mask, T_IN4_ADDR gateway)
{

	if (0 <= index && index < NUM_STATIC_ROUTE_ENTRY) {
		routing_tbl[index].target  = target;
		routing_tbl[index].mask    = mask;
		routing_tbl[index].gateway = gateway;
		return E_OK;
		}
	else
		return E_PAR;
	}

#endif	/* of #if NUM_ROUTE_ENTRY > 0 */

/*
 *  in4_rtalloc -- �롼�ƥ���ɽ��õ�����롣
 */

T_IN4_ADDR
in4_rtalloc (T_IN4_ADDR dst)
{
	int_t ix;

	for (ix = NUM_ROUTE_ENTRY; ix --; )
		if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
		    (dst & routing_tbl[ix].mask) == routing_tbl[ix].target) {
			if (routing_tbl[ix].gateway == 0)
				return dst;
			else {
				return routing_tbl[ix].gateway;
				}
			}
	return dst;
	}

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  in4_rtredirect -- �롼�ƥ���ɽ�˥���ȥ����Ͽ���롣
 *
 *    ���: ���� tmo ��ñ�̤� [ms]��
 */

void
in4_rtredirect (T_IN4_ADDR gateway, T_IN4_ADDR target, uint8_t flags, uint32_t tmo)
{
	T_IN_RTENTRY	*frt;

	frt = in_rtnewentry(flags, tmo);
	frt->gateway    = gateway;
	frt->target     = target;
	frt->mask       = 0xffffffff;
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  in4_timer -- IPv4 ���̥����ޡ�
 *
 *    1�ü����ǵ�ư����롣
 */

static void
in4_timer (void *ignore)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rttimer();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

#ifdef IP4_CFG_FRAGMENT

	ip_frag_timer();

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

	timeout(in4_timer, NULL, IN_TIMER_TMO);
	}

/*
 *  in4_init -- IPv4 ���̵�ǽ���������롣
 */

void
in4_init (void)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rtinit();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

	timeout(in4_timer, NULL, IN_TIMER_TMO);
	}

#endif	/* of #if defined(SUPPORT_INET4) */

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  in_rtinit -- �롼�ƥ���ɽ���������롣
 */

void
in_rtinit (void)
{
	int_t ix;

	for (ix = 0; ix < NUM_STATIC_ROUTE_ENTRY; ix ++)
		routing_tbl[ix].flags = IN_RTF_DEFINED;

	for ( ; ix < NUM_ROUTE_ENTRY; ix ++)
		routing_tbl[ix].flags = 0;
	}

/*
 *  in_rtnewentry -- ����������ȥ��������롣
 */

T_IN_RTENTRY *
in_rtnewentry (uint8_t flags, uint32_t tmo)
{
	SYSTIM		now;
	T_IN_RTENTRY	*rt, *frt = NULL;
	int_t		ix;

	/* ��������ȥ��õ����*/
	for (ix = NUM_STATIC_ROUTE_ENTRY; ix < NUM_ROUTE_ENTRY; ix ++) {
		rt = &routing_tbl[ix];
		if ((routing_tbl[ix].flags & IN_RTF_DEFINED) == 0) {
			frt = rt;
			break;
			}
		}

	/* expire ��ñ�̤� [s]��*/
	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	if (frt == NULL) {
		/* �������ʤ���С�ͭ�����֤���äȤ�û������ȥ������ˤ��롣*/
		T_IN_RTENTRY	*srt = NULL;
		int_t		diff, sdiff = INT_MAX;

		syscall(wai_sem(SEM_IN_ROUTING_TBL));
		for (ix = NUM_STATIC_ROUTE_ENTRY; ix < NUM_ROUTE_ENTRY; ix ++) {
			rt = &routing_tbl[ix];
			diff = (int_t)(rt->expire - now);
			if (diff <= 0) {	/* rt->expire <= now */
				/* ���ˡ�ͭ�����֤��᤮�Ƥ��롣*/
				frt = rt;
				break;
				}
			else if (diff < sdiff) {
				srt = rt;
				sdiff = diff;
				}
			}
		if (frt == NULL)
			frt = srt;
		frt->flags = 0;
		syscall(sig_sem(SEM_IN_ROUTING_TBL));
		}

	frt->flags  = (uint8_t)(flags | IN_RTF_DEFINED);
	frt->expire = now + tmo / SYSTIM_HZ;
	return frt;
	}

/*
 *  in_rttimer -- �롼�ƥ���ɽ�δ��������ޡ�
 */

void
in_rttimer (void)
{
	SYSTIM	now;
	int_t	ix;

	/* expire ��ñ�̤� [s]��*/
	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	syscall(wai_sem(SEM_IN_ROUTING_TBL));
	for (ix = NUM_STATIC_ROUTE_ENTRY; ix < NUM_ROUTE_ENTRY; ix ++)
		if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
		    (int_t)(routing_tbl[ix].expire - now) <= 0)
			routing_tbl[ix].flags = 0;
	syscall(sig_sem(SEM_IN_ROUTING_TBL));
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  in_cksum_sum -- �����å�����ι�׷׻��ؿ�
 *
 *  ���: data �� 4 �����ƥå�ñ�̤ǥѥǥ��󥰤��뤳�ȡ�
 *        data �� 2 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��ʤ���
 *        �㳰��ȯ�������ǽ�������롣
 *        len  �� 4 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��뤳�ȡ�
 *
 *        ����ͤϥۥ��ȥХ��ȥ�����
 */

uint32_t
in_cksum_sum (void *data, uint_t len /*�����ƥå�ñ��*/)
{
	uint32_t sum = 0;

	for ( ; len > 0; len -= 2) {
		sum += *((uint16_t*)data);
		data = (uint8_t*)data + 2;
		}

#if SIL_ENDIAN == SIL_ENDIAN_BIG
	return sum;
#elif SIL_ENDIAN == SIL_ENDIAN_LITTLE
	return ((sum >> 8) & 0xffff) + ((sum & 0xff) << 8) + ((sum >> 24) & 0xff);
#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

	}

/*
 *  in_cksum_carry -- �����å�����η�夲�׻��ؿ�
 *
 *  ���: data �� 4 �����ƥå�ñ�̤ǥѥǥ��󥰤��뤳�ȡ�
 *        data �� 2 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��ʤ���
 *        �㳰��ȯ�������ǽ�������롣
 *        len  �� 4 �����ƥå�ñ�̤˥��饤�󤵤�Ƥ��뤳�ȡ�
 */

uint32_t
in_cksum_carry (uint32_t sum)
{
	uint32_t	carry;

	while (sum >= 0x00010000) {
		carry = sum >> 16;
		sum   = (sum & 0xffff) + carry;
		}

	return sum;
	}

/*
 *  in_strtfn -- API ��ǽ�����ɤ�ʸ��ɽ�����֤���
 */

const char *
in_strtfn (FN fncd)
{
	switch (fncd) {

	/* TCP �ط� */

	case TFN_TCP_CRE_REP:
		return "TFN_TCP_CRE_REP";
		break;
	case TFN_TCP_DEL_REP:
		return "TFN_TCP_DEL_REP";
		break;
	case TFN_TCP_CRE_CEP:
		return "TFN_TCP_CRE_CEP";
		break;
	case TFN_TCP_DEL_CEP:
		return "TFN_TCP_DEL_CEP";
		break;
	case TFN_TCP_ACP_CEP:
		return "TFN_TCP_ACP_CEP";
		break;
	case TFN_TCP_CON_CEP:
		return "TFN_TCP_CON_CEP";
		break;
	case TFN_TCP_SHT_CEP:
		return "TFN_TCP_SHT_CEP";
		break;
	case TFN_TCP_CLS_CEP:
		return "TFN_TCP_CLS_CEP";
		break;
	case TFN_TCP_SND_DAT:
		return "TFN_TCP_SND_DAT";
		break;
	case TFN_TCP_RCV_DAT:
		return "TFN_TCP_RCV_DAT";
		break;
	case TFN_TCP_GET_BUF:
		return "TFN_TCP_GET_BUF";
		break;
	case TFN_TCP_SND_BUF:
		return "TFN_TCP_SND_BUF";
		break;
	case TFN_TCP_RCV_BUF:
		return "TFN_TCP_RCV_BUF";
		break;
	case TFN_TCP_REL_BUF:
		return "TFN_TCP_REL_BUF";
		break;
	case TFN_TCP_SND_OOB:
		return "TFN_TCP_SND_OOB";
		break;
	case TFN_TCP_RCV_OOB:
		return "TFN_TCP_RCV_OOB";
		break;
	case TFN_TCP_CAN_CEP:
		return "TFN_TCP_CAN_CEP";
		break;
	case TFN_TCP_SET_OPT:
		return "TFN_TCP_SET_OPT";
		break;
	case TFN_TCP_GET_OPT:
		return "TFN_TCP_GET_OPT";
		break;
	case TFN_TCP_ALL:
		return "ALL";
		break;

	/* UDP �ط� */

	case TFN_UDP_CRE_CEP:
		return "TFN_UDP_CRE_CEP";
		break;
	case TFN_UDP_DEL_CEP:
		return "TFN_UDP_DEL_CEP";
		break;
	case TFN_UDP_SND_DAT:
		return "TFN_UDP_SND_DAT";
		break;
	case TFN_UDP_RCV_DAT:
		return "TFN_UDP_RCV_DAT";
		break;
	case TFN_UDP_CAN_CEP:
		return "TFN_UDP_CAN_CEP";
		break;
	case TFN_UDP_SET_OPT:
		return "TFN_UDP_SET_OPT";
		break;
	case TFN_UDP_GET_OPT:
		return "TFN_UDP_GET_OPT";
		break;

	default:
		return "unknown TFN";
		}
	}
