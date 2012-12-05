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
 *  @(#) $Id: ping6.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  ping6 -- ICMPv6 ECHO ��å��������������롣
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/ppp_var.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>

#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#include <net/if6_var.h>

#ifdef USE_PING

/*
 *  �ѿ�
 */

static uint16_t	send_icmp6_id = 0;
static uint16_t	curr_icmp6_id;
static uint16_t	curr_icmp6_size;
static uint16_t	reply_count;
static SYSTIM	icmp6_start_time;

/*
 *  icmp6_reply_timeout -- ICMP6 REPLY �����ॢ���Ƚ���
 */

static void
icmp6_reply_timeout (void *arg)
{
	if (reply_count == 0)
		syslog(LOG_NOTICE, "[PING6] request timeout.");
	}

/*
 *  icmp6_echo_reply -- ICMP6 ECHO REPLY ��å�������������롣
 */

void
icmp6_echo_reply (T_NET_BUF *input, uint_t ihoff)
{
	T_IP6_HDR	*ip6h;
	SYSTIM		time;

	syscall(get_tim(&time));
	ip6h  = GET_IP6_HDR(input);

	syslog(LOG_NOTICE, "[PING6] reply: %5d [ms] from: %s",
	                   (time - icmp6_start_time) * 1000 / SYSTIM_HZ,
	                   ipv62str(NULL, &ip6h->src));
	reply_count ++;
	}

/*
 *  ping6 -- ICMP ECHO ��å��������������롣
 */

void
ping6 (T_IN6_ADDR *addr, uint_t tmo, uint_t size)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ICMP6_HDR	*icmp6h;
	T_NET_BUF	*output;
	T_IN6_IFADDR	*ia;
	int_t		ix;
	uint16_t	ipflags = 0;
	uint8_t		*sdu;

	/*
	 *  ���襢�ɥ쥹�ˤդ��路�����������ɥ쥹��
	 *  �ͥåȥ�����󥿥ե���������õ���������Ѥ��롣
	 */
	if ((ia = in6_ifawithifp(ifp, addr)) == NULL)
		return;

	if (IN6_IS_ADDR_MULTICAST(addr))
		ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_DEFHLIM);

	/* �����Ѥ� IP �ǡ���������������롣*/
	if (in6_get_datagram(&output, ICMP6_HDR_SIZE + size, 0,
	                     addr, &ia->addr, IPPROTO_ICMPV6,
	                     IPV6_DEFHLIM, NBA_SEARCH_ASCENT, TMO_FEVR) != E_OK)
		return;

	/* ICMP �إå������ꤹ�롣*/
	icmp6h           = GET_ICMP6_HDR(output, IF_IP6_ICMP6_HDR_OFFSET);
	icmp6h->type     = ICMP6_ECHO_REQUEST;
	icmp6h->code     = 0;
	icmp6h->icmp6_id = htons(send_icmp6_id);
	icmp6h->icmp6_seq= 0;

	/* �ǡ��������ꤹ�롣*/
	sdu = GET_ICMP6_SDU(output, IF_IP6_ICMP6_HDR_OFFSET) + size;
	for (ix = size; ix -- > 0; )
		*-- sdu = ('0' + send_icmp6_id + ix) & 0xff;

	/* �����å������׻����롣*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(output, IPPROTO_ICMPV6,
	                        (uint8_t*)icmp6h - output->buf, ICMP6_HDR_SIZE + size);

	/* ���������å��Ѥ��ѿ������ꤹ�롣*/
	curr_icmp6_id   = send_icmp6_id ++;
	curr_icmp6_size = size;

	reply_count = 0;

	syslog(LOG_NOTICE, "[PING6] send: TMO:%d, SIZE:%d, to: %s, from %s",
	                   tmo, size,
	                   ipv62str(NULL, addr), ipv62str(NULL, &ia->addr));

	/* �����塢���ߤλ��֤򵭲����������ॢ���Ȥ����ꤹ�롣*/
	ip6_output(output, ipflags, TMO_FEVR);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutEchos, 1);

	syscall(get_tim(&icmp6_start_time));
	timeout(icmp6_reply_timeout, NULL, tmo * NET_TIMER_HZ);

	}

#endif	/* of #ifdef USE_PING */
