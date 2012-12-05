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
 *  @(#) $Id: tcp_discard_cli.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  TCP DISCARD ���饤�����
 *
 *    ���Υ�֥�å��󥰥�����
 *    ��IPv4
 *    ��IPv6
 */

#include <stdlib.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/discard.h>

#ifdef USE_TCP_DISCARD_CLI

/* discard �����ФΥݡ����ֹ� */

#define DISCARD_SRV_PORTNO	UINT_C(9)

/* ɽ�� */

/*#define SHOW_RCV_RANGE*/

/*
 *  �Хåե������������
 */

#define NUM_DISCARD		5
#define NUM_REP_PAT		40
#define PAT_BEGIN		' '
#define PAT_END			'~'
#define SND_BUF_SIZE		((PAT_END - PAT_BEGIN + 1) * NUM_REP_PAT)

/*
 *  �����ѿ�
 */

bool_t tcp_discard_cli_valid;

/* TCP ������������ɥХåե� */

#ifndef TCP_CFG_SWBUF_CSAVE_ONLY
uint8_t tcp_discard_cli_swbuf[TCP_DISCARD_CLI_SWBUF_SIZE];
#endif

#ifdef USE_TCP_NON_BLOCKING

/*
 *  �ѿ�
 */

static T_IPEP		nblk_src = {
				IP_ADDRANY,
				TCP_PORTANY,
				};
static T_IPEP		nblk_dst;
static ER_UINT		nblk_error;

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp_discard_cli (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;

	nblk_error = *(ER*)p_parblk;

	switch (fncd) {

	case TFN_TCP_CON_CEP:
		syscall(sig_sem(SEM_TCP_DISCARD_CLI_NBLK_READY));
		break;

	case TFN_TCP_CLS_CEP:
		if (nblk_error < 0)
			syslog(LOG_NOTICE, "[TDC:%02d CBN] close error: %s", cepid, itron_strerror(nblk_error));
		syscall(sig_sem(SEM_TCP_DISCARD_CLI_NBLK_READY));
		break;

	case TFN_TCP_ACP_CEP:
	case TFN_TCP_SND_DAT:
	case TFN_TCP_GET_BUF:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

/*
 *  send_tcp_discard -- DISCARD/TCP �����Ф˥�å��������������롣
 */

static void
send_tcp_discard (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno)
{
	static char smsg[SND_BUF_SIZE];

	ER_UINT		slen;
	ER		error;
	SYSTIM		time;
	uint32_t	total;
	uint16_t	soff, discard, rep, scount;
	uint8_t		pat, *p;

	nblk_dst.ipaddr = *ipaddr;
	nblk_dst.portno = portno;

	p = smsg;
	for (rep = NUM_REP_PAT; rep -- > 0; )
		for (pat = PAT_BEGIN; pat <= PAT_END; pat ++)
			*p ++ = pat;

	if ((error = TCP_CON_CEP(cepid, &nblk_src, &nblk_dst, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[TDC:%02d SND] connect error: %s", cepid, itron_strerror(error));
		return;
		}

	/* ��³����λ����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_DISCARD_CLI_NBLK_READY));

	if (nblk_error != E_OK)
		syslog(LOG_NOTICE, "[TDC:%02d SND] connect error: %s", cepid, itron_strerror(nblk_error));
	else {
		get_tim(&time);
		syslog(LOG_NOTICE, "[TDC:%02d SND] connecting: %6ld, to:   %s.%d",
		                   cepid, time / SYSTIM_HZ, IP2STR(NULL, ipaddr), nblk_dst.portno);

		scount = total = 0;
		for (discard = NUM_DISCARD; discard -- > 0; ) {
			soff = 0;
			while (soff < SND_BUF_SIZE) {
				if ((slen = tcp_snd_dat(cepid, smsg + soff, sizeof(smsg) - soff, TMO_FEVR)) < 0) {
					syslog(LOG_NOTICE, "[TDC:%02d SND] send error: %s",
					                   cepid, itron_strerror(slen));
					goto cls_ret;
					}
				soff  += (uint16_t)slen;
				total +=     slen;
				scount ++;

#ifdef SHOW_RCV_RANGE
				syslog(LOG_NOTICE, "[TDC:%02d SND] snd: %2d, len: %4d, off: %4d",
				                   cepid, scount, (uint16_t)slen, soff);
#endif	/* of #ifdef SHOW_RCV_RANGE */

				syscall(dly_tsk(500 + net_rand() % SYSTIM_HZ));
				}
			}

	cls_ret:
		get_tim(&time);
		syslog(LOG_NOTICE, "[TDC:%02d SND] finished:   %6ld, snd: %4d,            len: %ld",
		                   cepid, time / SYSTIM_HZ, scount, total);

		if ((error = tcp_sht_cep(cepid)) < 0)
			syslog(LOG_NOTICE, "[TDC:%02d SND] shutdown error: %s", cepid, itron_strerror(error));

		if ((error = tcp_cls_cep(cepid, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TDC:%02d SND] close error: %s", cepid, itron_strerror(error));

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_DISCARD_CLI_NBLK_READY));
		}
	}

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

/*
 *  send_tcp_discard -- DISCARD/TCP �����Ф˥�å��������������롣
 */

static void
send_tcp_discard (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno)
{
	static char smsg[SND_BUF_SIZE];
	static T_IPEP src = {
		IP_ADDRANY,
		TCP_PORTANY,
		};

	T_IPEP		dst;
	ER_UINT		slen;
	ER		error;
	SYSTIM		time;
	uint16_t	pat, soff, discard, rep, scount, total;
	uint8_t		*p;

	dst.ipaddr = *ipaddr;
	dst.portno = portno;

	p = smsg;
	for (rep = NUM_REP_PAT; rep -- > 0; )
		for (pat = PAT_BEGIN; pat <= PAT_END; pat ++)
			*p ++ = pat;

	if ((error = TCP_CON_CEP(cepid, &src, &dst, 60 * 1000)) != E_OK) {
		syslog(LOG_NOTICE, "[TDC:%02d SND] connect error: %s", cepid, itron_strerror(error));
		return;
		}

	get_tim(&time);
	syslog(LOG_NOTICE, "[TDC:%02d SND] connecting: %6ld, to:   %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);

	scount = total = 0;
	for (discard = NUM_DISCARD; discard -- > 0; ) {
		soff = 0;
		while (soff < SND_BUF_SIZE) {
			if ((slen = tcp_snd_dat(cepid, smsg + soff, sizeof(smsg) - soff, TMO_FEVR)) < 0) {
				syslog(LOG_NOTICE, "[TDC:%02d SND] send error: %s", cepid, itron_strerror(slen));
				goto cls_ret;
				}
			soff  += (uint16_t)slen;
			total +=     slen;
			scount ++;

#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TDC:%02d SND] snd: %3d, len: %4d, off: %4d",
			                   cepid, scount, (uint16_t)slen, soff);
#endif	/* of #ifdef SHOW_RCV_RANGE */

			syscall(dly_tsk(500 + net_rand() % SYSTIM_HZ));
			}
		}

cls_ret:
	get_tim(&time);
	syslog(LOG_NOTICE, "[TDC:%02d SND] finished:   %6ld, snd: %4d,            len: %ld",
	                   cepid, time / SYSTIM_HZ, scount, total);

	if ((error = tcp_sht_cep(cepid)) < 0)
		syslog(LOG_NOTICE, "[TDC:%02d SND] shutdown error: %s", cepid, itron_strerror(error));

	if ((error = tcp_cls_cep(cepid, TMO_FEVR)) < 0)
		syslog(LOG_NOTICE, "[TDC:%02d SND] close error: %s", cepid, itron_strerror(error));
	}

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

void
tcp_discard_cli_task (intptr_t exinf)
{
	T_IN_ADDR	addr;
	ID		tskid, cepid;
	int_t		rep;
	uint32_t	count;
	uint16_t	portno;
	uint8_t		*line;

#ifdef USE_TCP_EXTENTIONS

	ER		error;
	T_TCP_CCEP	ccep;

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP DISCARD CLI:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		if (rcv_dtq(DTQ_TCP_DISCARD_CLI, (intptr_t*)&line) == E_OK) {
			line = skip_blanks(GET_IPADDR(&addr, skip_blanks(line)));	/* IP Address */

			if ('0' <= *line && *line <= '9') {				/* Port No */
				line = get_int(&rep, line);
				portno = (uint16_t)rep;
				}
			else {
				line ++;
				portno = DISCARD_SRV_PORTNO;
				}

			line = skip_blanks(line);
			if ('0' <= *line && *line <= '9')				/* Repeat */
				line = get_int(&rep, line);
			else
				rep = 1;

#ifdef USE_TCP_EXTENTIONS

			ccep.cepatr = 0;
			ccep.sbufsz = TCP_DISCARD_CLI_SWBUF_SIZE;
			ccep.rbufsz = 0;
			ccep.rbuf = NADR;

#ifdef TCP_CFG_SWBUF_CSAVE
			ccep.sbuf = NADR;
#else
			ccep.sbuf = tcp_discard_cli_swbuf;
#endif
#ifdef USE_TCP_NON_BLOCKING
			ccep.callback = (FP)callback_nblk_tcp_discard_cli;
#else
			ccep.callback = NULL;
#endif

			if ((error = alloc_tcp_cep(&cepid, tskid, &ccep)) != E_OK) {
				syslog(LOG_NOTICE, "[TDC:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
				continue;
				}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

			cepid = (ID)exinf;

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

			tcp_discard_cli_valid = true;
			for (count = rep; count -- > 0; ) {
				if (!tcp_discard_cli_valid) {
					syslog(LOG_NOTICE, "[TDC:%02d TSK] canceled.", (ID)exinf);
					break;
					}
				syslog(LOG_NOTICE, "[TDC:%02d TSK] start:              repeat: %d/%d",
				                   (ID)exinf, rep - count, rep);
				send_tcp_discard(cepid, &addr, portno);
				syslog(LOG_NOTICE, "[TDC:%02d TSK] finished:           repeat: %d/%d",
				                   (ID)exinf, rep - count, rep);
				syscall(dly_tsk(500 + net_rand() % SYSTIM_HZ));
				}

#ifdef USE_TCP_EXTENTIONS

			if ((error = free_tcp_cep(cepid)) != E_OK)
				syslog(LOG_NOTICE, "[TDC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

			}
		}
	}

#endif	/* of #ifdef USE_TCP_DISCARD_CLI */
