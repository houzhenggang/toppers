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
 *  @(#) $Id: net_buf.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

/*
 *  �ؿ�
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ѿ�
 */

static T_NET_BUF_ENTRY net_buf_table[] = {

#if defined(NUM_MPF_NET_BUF6_65536) && NUM_MPF_NET_BUF6_65536 > 0
	{
		MPF_NET_BUF6_65536,
		IF_IP6_HDR_SIZE + 65536,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF6_65536,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF6_65536) && NUM_MPF_NET_BUF6_65536 > 0 */

#if defined(NUM_MPF_NET_BUF6_REASSM) && NUM_MPF_NET_BUF6_REASSM > 0
	{
		MPF_NET_BUF_REASSM,
		IP6_CFG_FRAG_REASSM_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF6_REASSM,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF6_REASSM) && NUM_MPF_NET_BUF6_REASSM > 0 */

#if defined(NUM_MPF_NET_BUF4_REASSM) && NUM_MPF_NET_BUF4_REASSM > 0
	{
		MPF_NET_BUF_REASSM,
		IP4_CFG_FRAG_REASSM_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF4_REASSM,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF4_REASSM) && NUM_MPF_NET_BUF4_REASSM > 0 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0
	{
		MPF_NET_BUF_IF_PDU,
		IF_PDU_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IF_PDU,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(NUM_MPF_NET_BUF_IPV6_MMTU) && NUM_MPF_NET_BUF_IPV6_MMTU > 0
	{
		MPF_NET_BUF_IPV6_MMTU,
		IF_HDR_SIZE + IPV6_MMTU,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IPV6_MMTU,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IPV6_MMTU) && NUM_MPF_NET_BUF_IPV6_MMTU > 0 */

#if defined(NUM_MPF_NET_BUF_1024) && NUM_MPF_NET_BUF_1024 > 0
	{
		MPF_NET_BUF_1024,
		UINT_C(1024),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_1024,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_1024) && NUM_MPF_NET_BUF_1024 > 0 */

#if defined(NUM_MPF_NET_BUF_IP_MSS) && NUM_MPF_NET_BUF_IP_MSS > 0
	{
		MPF_NET_BUF_IP_MSS,
		IF_HDR_SIZE + IP4_MSS,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IP_MSS,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IP_MSS) && NUM_MPF_NET_BUF_IP_MSS > 0 */

#if defined(NUM_MPF_NET_BUF_512) && NUM_MPF_NET_BUF_512 > 0
	{
		MPF_NET_BUF_512,
		UINT_C(512),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_512,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_512) && NUM_MPF_NET_BUF_512 > 0 */

#if defined(NUM_MPF_NET_BUF_256) && NUM_MPF_NET_BUF_256 > 0
	{
		MPF_NET_BUF_256,
		UINT_C(256),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_256,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_256) && NUM_MPF_NET_BUF_256 > 0 */

#if defined(NUM_MPF_NET_BUF_128) && NUM_MPF_NET_BUF_128 > 0
	{
		MPF_NET_BUF_128,
		UINT_C(128),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_128,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_128) && NUM_MPF_NET_BUF_128 > 0 */

#if defined(SUPPORT_INET4)

#if defined(NUM_MPF_NET_BUF_64) && NUM_MPF_NET_BUF_64 > 0
	{
		MPF_NET_BUF_64,
		UINT_C(64),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_64,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_64) && NUM_MPF_NET_BUF_64 > 0 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(NUM_MPF_NET_BUF_CSEG) && NUM_MPF_NET_BUF_CSEG > 0
	{
		MPF_NET_BUF_CSEG,
		IF_HDR_SIZE + IP_HDR_SIZE + TCP_HDR_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_CSEG,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_CSEG) && NUM_MPF_NET_BUF_CSEG > 0 */

	};

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

/*
 *  nbuf_get_tbl -- �ͥåȥ���Хåե�����ɽ��������롣
 *
 *    ���: �ͥåȥ�����׾���η�¬��
 */

const T_NET_BUF_ENTRY *
nbuf_get_tbl (void)
{
	return net_buf_table;
	}

/*
 *  nbuf_get_tbl_size -- �ͥåȥ���Хåե���������ȥ����������롣
 *
 *    ���: �ͥåȥ�����׾���η�¬��
 */

uint_t
nbuf_get_tbl_size (void)
{
	return sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	}

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

/*
 *  tget_net_buf_up -- �礭�ʥ�������������õ�����ơ��ͥåȥ���Хåե���������롣
 */

static ER
tget_net_buf_up (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, TMO tmout)
{
	int_t	ix, req_ix;
	ER	error = E_OK;

	/* ��Ŭ�ʥ������θ���Ĺ����ס����õ����*/
	ix = sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	while (ix -- > 0 && minlen > net_buf_table[ix].size)
		;
	req_ix = ix;

	NET_COUNT_NET_BUF(net_buf_table[req_ix].requests, 1);

	while (1) {
		if ((error = tget_mpf((ID)net_buf_table[ix].index, (void*)buf, ix == 0 ? tmout : TMO_POL)) == E_OK) {
			(*buf)->idix  = (uint8_t)ix;
			(*buf)->len   = (uint16_t)minlen;
			(*buf)->flags = 0;
			NET_COUNT_NET_BUF(net_buf_table[ix].allocs, 1);
			return error;
			}
		else if (ix == 0 || net_buf_table[ix].size > maxlen)
			break;
		ix --;
		}

	syslog(LOG_WARNING, "[NET BUF] busy, index=%d, len=%4d.", (uint16_t)req_ix, minlen);
	*buf = NULL;
	NET_COUNT_NET_BUF(net_buf_table[req_ix].errors, 1);
	return error;
	}

/*
 *  tget_net_buf_down -- �����ʥ�������������õ�����ơ��ͥåȥ���Хåե���������롣
 */

static ER
tget_net_buf_down (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, TMO tmout)
{
	int_t	ix, req_ix;
	ER	error = E_OK;

	/* ��Ŭ�ʥ������θ���Ĺ����ס����õ����*/
	ix = sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	while (ix -- > 0 && maxlen > net_buf_table[ix].size)
		;
	req_ix = ix;

	NET_COUNT_NET_BUF(net_buf_table[req_ix].requests, 1);

	while (1) {
		if ((error = tget_mpf((ID)net_buf_table[ix].index, (void*)buf,
		                      ix == sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY) - 1 ? tmout : TMO_POL)) == E_OK) {
			(*buf)->idix  = (uint8_t)ix;
			(*buf)->len   = net_buf_table[ix].size;
			(*buf)->flags = 0;
			NET_COUNT_NET_BUF(net_buf_table[ix].allocs, 1);
			return error;
			}
		ix ++;
		if (ix == sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY) || net_buf_table[ix].size < minlen)
			break;
		}

	syslog(LOG_WARNING, "[NET BUF] busy, index=%d, len=%4d.", (uint16_t)req_ix, maxlen);
	*buf = NULL;
	NET_COUNT_NET_BUF(net_buf_table[req_ix].errors, 1);
	return error;
	}

/*
 *  tget_net_buf_ex -- �ͥåȥ���Хåե����������ʳ�ĥ��ǽ�ˡ�
 */

ER
tget_net_buf_ex (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, ATR nbatr, TMO tmout)
{
	/* �Ǿ������������祵������Ķ���Ƥ����饨�顼 */
	if ((nbatr & NBA_SEARCH_DESCENT) != 0 && minlen > maxlen) {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, minlen=%4d > maxlen=%4d.", minlen, maxlen);
		return E_PAR;
		}

	/* �����Ʋ�ǽ�ʺ���Υ�������Ķ���Ƥ����饨�顼 */
	if (minlen > net_buf_table[0].size || maxlen > net_buf_table[0].size) {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, minlen=%4d or maxlen=%4d > %4d",
		                    minlen, maxlen, net_buf_table[0].size);
		return E_PAR;
		}

	/* TCP ��ͽ�󤷤��ͥåȥ���Хåե�����Ф���*/
	if ((nbatr & NBA_RESERVE_TCP) != 0) {
		if ((*buf = TCP_PULL_RES_NBUF(nbatr)) != NULL) {
			return E_OK;
			}
		}

	if ((nbatr & NBA_SEARCH_DESCENT) != 0)
		return tget_net_buf_down(buf, minlen, maxlen, tmout);
	else if ((nbatr & NBA_SEARCH_ASCENT) != 0)
		return tget_net_buf_up(buf, minlen, (uint_t)net_buf_table[0].size, tmout);
	else {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, nbatr=%08x.", nbatr);
		return E_PAR;
		}
	}

/*
 *  tget_net_buf -- �ͥåȥ���Хåե����������ʸߴ��ˡ�
 */

ER
tget_net_buf (T_NET_BUF **buf, uint_t len, TMO tmout)
{
	return tget_net_buf_ex(buf, len, (uint_t)net_buf_table[0].size, NBA_SEARCH_ASCENT, tmout);
	}

/*
 * rel_net_buf -- �ͥåȥ���Хåե����ֵѤ��롣
 */

ER
rel_net_buf (T_NET_BUF *buf)
{
	ER	error = E_OK;

	/* �ͥåȥ���Хåե��� ID ���������򸡾ڤ��롣*/
	if ((int_t)buf->idix >= (int_t)(sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY))) {
		syslog(LOG_WARNING, "[NET BUF] E_ID, ID=%d.", buf->idix);
		error = E_ID;
		}
	else {

		/* TCP �ǡ��ͥåȥ���Хåե���ͽ�󤹤롣*/
		if (TCP_PUSH_RES_NBUF(buf) == NULL)
			return E_OK;

		/* �������ס�����֤���*/
		if ((error = rel_mpf((ID)net_buf_table[buf->idix].index, buf)) != E_OK)
			syslog(LOG_WARNING, "[NET BUF] %s, ID=%d.", itron_strerror(error), buf->idix);
		}
	return error;
	}

/*
 * rus_net_buf -- �ͥåȥ���Хåե�������Ѥ��롣
 */

ER
rus_net_buf (T_NET_BUF *buf)
{
	ER	error = E_OK;

	if (buf->idix >= sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY)) {
		syslog(LOG_WARNING, "[NET BUF] E_ID, ID=%d.", buf->idix);
		error = E_ID;
		}
	else {
		buf->len   = net_buf_table[buf->idix].size;
		buf->flags = 0;
		error = E_OK;
		}
	return error;
	}

/*
 * net_buf_siz -- �ͥåȥ���Хåե��Υ��������֤���
 */

ER_UINT
net_buf_siz (T_NET_BUF *buf)
{
	if (buf->idix >= sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY)) {
		syslog(LOG_WARNING, "[BUF SIZ] E_ID, ID=%d.", buf->idix);
		return E_ID;
		}
	else
		return (ER_UINT)net_buf_table[buf->idix].size;
	}

/*
 * net_buf_max_siz -- �ͥåȥ���Хåե��κ��祵�������֤���
 */

uint_t
net_buf_max_siz (void)
{
	return (uint_t)net_buf_table[0].size;
	}
