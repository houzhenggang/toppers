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
 *  @(#) $Id: tcp_discard_srv.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  DISCARD ������
 *
 *    ���ʥ��ԡ� API
 *    ��IPv4
 *    ��IPv6
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/discard.h>

#ifdef USE_TCP_DISCARD_SRV

/*
 *  ɽ��
 */

//#define SHOW_RCV_RANGE
//#define SHOW_RCV_DATA

/*
 *  �����ѿ�
 */

/* TCP ������������ɥХåե� */

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY
uint8_t tcp_discard_srv_rwbuf[TCP_DISCARD_SRV_RWBUF_SIZE];
#endif

/*
 *  TCP DISCARD �����Х�����
 */

#define BUF_SIZE	TCP_DISCARD_SRV_RWBUF_SIZE

#ifdef USE_COPYSAVE_API

static ER
tcp_discard_srv (ID cepid, ID repid)
{
	T_IPEP		dst;
	ER_UINT		rlen;
	ER		error;
	SYSTIM		time;
	uint32_t	total;
	uint16_t	count;
	uint8_t		*buf;

#ifdef SHOW_RCV_DATA
	uint_t	ix;
#endif	/* of #ifdef SHOW_RCV_DATA */

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d ACP] accept error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	count = total = 0;
	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] connected:  %6ld, from: %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while ((rlen = tcp_rcv_buf(cepid, (void*)&buf, TMO_FEVR)) > 0) {
		count ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TDS:%02d RCV] count: %4d, len: %4d, data: %02x -> %02x",
		       cepid, count, (uint16_t)rlen, *buf, *(buf + rlen - 1));
#endif	/* of #ifdef SHOW_RCV_RANGE */

#ifdef SHOW_RCV_DATA
		for (ix = 0; ix < rlen; ix ++)
			cons_putchar(CONSOLE_PORTID,  *(buf + ix));
#endif	/* of #ifdef SHOW_RCV_DATA */

		if ((error = tcp_rel_buf(cepid, rlen)) != E_OK) {
			syslog(LOG_NOTICE, "[TDS:%02d RCV] rel buf error: %s",
			                    cepid, itron_strerror(error));
			rlen = 0;
			break;
			}
		total += rlen;
		}

	if (rlen != 0)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] recv buf error: %s", cepid, itron_strerror(rlen));

	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] shutdown error: %s", cepid, itron_strerror(error));

	if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] close error: %s", cepid, itron_strerror(error));

	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] finished:   %6ld,            rcv: %4d, len: %ld",
	                   cepid, time / SYSTIM_HZ, count, total);

	return error;
	}

#else	/* of #ifdef USE_COPYSAVE_API */

static ER
tcp_discard_srv (ID cepid, ID repid)
{
	static char buffer[BUF_SIZE];

	T_IPEP		dst;
	ER_UINT		rlen;
	ER		error;
	SYSTIM		time;
	uint32_t	total;
	uint16_t	count;
	uint8_t		*buf = buffer;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d RCV] accept error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	count = total = 0;
	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] connected:  %6ld, from: %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while ((rlen = tcp_rcv_dat(cepid, buf, BUF_SIZE - 1, TMO_FEVR)) > 0) {
		count ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TDS:%02d RCV] count: %4d, len: %4d, data: %02x -> %02x",
		       cepid, count, (uint16_t)rlen, *buf, *(buf + rlen - 1));
#endif	/* of #ifdef SHOW_RCV_RANGE */

		total += rlen;
		}
	if (rlen != 0)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] recv error: %s", cepid, itron_strerror(rlen));

	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] shutdown error: %s", cepid, itron_strerror(error));

	if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] close error: %s", cepid, itron_strerror(error));

	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] finished:   %6ld,            rcv: %4d, len: %ld",
	                   cepid, time / SYSTIM_HZ, count, total);

	return error;
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#ifdef USE_TCP_EXTENTIONS

/*
 *  get_tcp_rep -- TCP ���ո���������롣
 */

static ER
get_tcp_rep (ID *repid)
{
	ID		tskid;
	T_TCP_CREP	crep;

	get_tid(&tskid);

	crep.repatr = UINT_C(0);
	crep.myaddr.portno = UINT_C(9);

#if defined(SUPPORT_INET4)
	crep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
	memcpy(&crep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

	return alloc_tcp_rep(repid, tskid, &crep);
	}

/*
 *  get_tcp_cep -- TCP �̿�ü���Ȥ�������롣
 */

static ER
get_tcp_cep (ID *cepid)
{
	ID		tskid;
	T_TCP_CCEP	ccep;

	get_tid(&tskid);

	ccep.cepatr = UINT_C(0);
	ccep.sbuf = NADR;
	ccep.sbufsz = 0;
	ccep.rbufsz = TCP_DISCARD_SRV_RWBUF_SIZE;
	ccep.callback = NULL;

#ifdef TCP_CFG_RWBUF_CSAVE
	ccep.rbuf = NADR;
#else
	ccep.rbuf = tcp_discard_srv_rwbuf;
#endif

	return alloc_tcp_cep(cepid, tskid, &ccep);
	}

/*
 *  tcp_discard_srv_task -- TCP �����������Х�����
 */

void
tcp_discard_srv_task (intptr_t exinf)
{
	ID	tskid, cepid, repid;
	ER	error = E_OK;

	syscall(get_tid(&tskid));
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d] started.", tskid);
	while (true) {

		syscall(slp_tsk());
		if ((error = get_tcp_cep (&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TDS:00 EXT] CEP create error: %s", itron_strerror(error));
			continue;
			}

		while (true) {

			if ((error = get_tcp_rep (&repid)) != E_OK) {
				syslog(LOG_NOTICE, "[TDS:00 EXT] REP create error: %s", itron_strerror(error));
				break;
				}
			else if ((error = tcp_discard_srv(cepid, repid)) != E_OK) {
				error = free_tcp_rep(repid, error != E_DLT);
				break;
				}
			}

		if ((error = free_tcp_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TDS:%02d EXT] CEP delete error: %s", cepid, itron_strerror(error));

		}
	}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

void
tcp_discard_srv_task(intptr_t exinf)
{
	ID	tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP DISCARD SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		while (tcp_discard_srv((ID)exinf, TCP_DISCARD_SRV_REPID) == E_OK)
			;
		}
	}

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

#endif	/* of #ifdef USE_TCP_DISCARD_SRV */
