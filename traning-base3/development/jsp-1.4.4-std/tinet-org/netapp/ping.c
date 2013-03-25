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
 *  @(#) $Id: ping.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  ping -- ICMP ECHO ��å��������������롣
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
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>

#ifdef USE_PING

/*
 *  �ѿ�
 */

static uint16_t	icmp_id = 0;
static uint16_t	curr_icmp_id;
static uint16_t	curr_icmp_len;
static SYSTIM	icmp_start_time;

/*
 *  icmp_reply_timeout -- ICMP REPLY �����ॢ���Ƚ���
 */

static void
icmp_reply_timeout (void *arg)
{
	syslog(LOG_NOTICE, "[PING] request timeout.");
	}

/*
 *  icmp_echo_reply -- ICMP ECHO REPLY ��å�������������롣
 */

void
icmp_echo_reply (T_NET_BUF *input, uint_t ihoff)
{
	SYSTIM time;

	syscall(get_tim(&time));
	untimeout(icmp_reply_timeout, NULL);
	syslog(LOG_NOTICE, "[PING] reply, %d [ms].",
	                   (time - icmp_start_time) * 1000 / SYSTIM_HZ);
	}

/*
 *  ping4 -- ICMP ECHO ��å��������������롣
 */

void
ping4 (T_IN4_ADDR *addr, uint_t tmo, uint_t len)
{
	T_ICMP4_HDR	*icmp4h;
	T_NET_BUF	*output;
	uint8_t		*sdu;
	int_t		ix;

	/* �����Ѥ� IP �ǡ���������������롣*/
	if (in4_get_datagram(&output, ICMP4_HDR_SIZE + len, 0,
	                     addr, NULL, IPPROTO_ICMP,
	                     IP4_DEFTTL, NBA_SEARCH_ASCENT, TMO_FEVR) != E_OK)
		return;

	/* ICMP �إå������ꤹ�롣*/
	icmp4h			= GET_ICMP4_HDR(output, IF_IP4_ICMP4_HDR_OFFSET);
	icmp4h->type		= ICMP4_ECHO_REQUEST;
	icmp4h->code		= 0;
	icmp4h->data.id_seq.id	= htons(icmp_id);
	icmp4h->data.id_seq.seq	= 0;

	/* �ǡ��������ꤹ�롣*/
	sdu = GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET) + len;
	for (ix = len; ix -- > 0; )
		*-- sdu = ('0' + icmp_id + ix) & 0xff;

	/* �����å������׻����롣*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h, ICMP4_HDR_SIZE + len);

	/* ���������å��Ѥ��ѿ������ꤹ�롣*/
	curr_icmp_id  = icmp_id ++;
	curr_icmp_len = len;

	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutEchos, 1);

	/* �����塢���ߤλ��֤򵭲����������ॢ���Ȥ����ꤹ�롣*/
	ip_output(output, TMO_FEVR);

	syscall(get_tim(&icmp_start_time));
	timeout(icmp_reply_timeout, NULL, tmo * NET_TIMER_HZ);

	}

#endif	/* of #ifdef USE_PING */
