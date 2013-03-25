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
 *  @(#) $Id: tcp_echo_srv1.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  TCP ECHO ������ #1
 *
 *    ��������������Ʊ�췿
 *    ���Υ�֥�å��󥰥�����
 *    ���ʥ��ԡ� API
 *    ��IPv4/IPv6
 *    ���۵ޥǡ����μ���
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"
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
#include <netapp/echo.h>

#ifdef USE_TCP_ECHO_SRV1

/*
 *  ɽ��
 */

//#define SHOW_RCV_RANGE

/*
 *  ���ͥ������������ˡ�λ���
 */

#define USE_TCP_SHT_CEP

/*
 *  �����ॢ����
 */

//#define CLS_TMO		TMO_FEVR	/* Close Wait ��ɸ��� 60�� */
#define CLS_TMO		(70*SYSTIM_HZ+(net_rand()%SYSTIM_HZ)*10)
//#define RCV_TMO		TMO_FEVR
#define RCV_TMO		(30*SYSTIM_HZ+(net_rand()%SYSTIM_HZ)*30)
//#define SND_TMO		TMO_FEVR
#define SND_TMO		(40*SYSTIM_HZ+(net_rand()%SYSTIM_HZ)*20)

/*
 *  �����ѿ�
 */

/* TCP ������������ɥХåե� */

#ifndef TCP_CFG_SWBUF_CSAVE
uint8_t tcp_echo_srv_swbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_SWBUF_SIZE];
#endif

#ifndef TCP_CFG_RWBUF_CSAVE
uint8_t tcp_echo_srv_rwbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_RWBUF_SIZE];
#endif

/*
 *  �ѿ�
 */

/*
 *  ���:
 *
 *    BUF_SIZE �� TCP ��
 *    ����������ɥ��Хåե������� + ����������ɥ��Хåե��������� 
 *    3/2 �ܰʾ���礭�����ʤ���С��ǥåɥ�å������ǽ�������롣
 */

#define BUF_SIZE	((TCP_ECHO_SRV_SWBUF_SIZE + \
                          TCP_ECHO_SRV_RWBUF_SIZE) * 3 / 2)

static T_IPEP		dst;			/* ��³���		*/

#ifdef USE_TCP_NON_BLOCKING

static char		buffer[BUF_SIZE];
static ER		nblk_error = E_OK;
static ER_UINT		nblk_slen  = 0;
static ER_UINT		nblk_rlen  = 0;

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_COPYSAVE_API

#else	/* of #ifdef USE_COPYSAVE_API */

static char		buffer[BUF_SIZE];

#endif	/* of #ifdef USE_COPYSAVE_API */

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_TCP_NON_BLOCKING

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		nblk_error = *(ER*)p_parblk;
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_DAT:
		if ((nblk_rlen = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d CBN] recv error: %s", cepid, itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_SND_DAT:
		if ((nblk_slen = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d CBN] send error: %s", cepid, itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_CLS_CEP:
		if ((nblk_error = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d CBN] close error: %s", cepid, itron_strerror(nblk_error));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_BUF:
		if ((nblk_rlen = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d CBN] rbuf error: %s", cepid, itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_GET_BUF:
		if ((nblk_slen = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d CBN] sbuf error: %s", cepid, itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

#ifdef USE_TCP_EXTENTIONS

	case TEV_TCP_RCV_OOB:
		if ((nblk_rlen = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TES:%02d OOB] callback error: %s", cepid, itron_strerror(nblk_rlen));
		else if (nblk_rlen > 0) {
			char ch;

			if ((nblk_rlen = tcp_rcv_oob(cepid, &ch, sizeof(ch))) > 0)
				syslog(LOG_NOTICE, "[TES:%02d OOB] recv oob: 0x%02x", cepid, ch);
			else if (nblk_rlen < 0)
				syslog(LOG_NOTICE, "[TES:%02d OOB] recv error: %s", cepid, itron_strerror(nblk_rlen));
			}
		break;

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

#ifdef USE_COPYSAVE_API

static ER
tcp_echo_srv (ID cepid, ID repid)
{
	ER		error;
	SYSTIM		now;
	uint32_t	total;
	uint16_t	rblen, sblen, rlen, slen, soff, scount, rcount;
	char		*rbuf, *sbuf, head, tail;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(error));
		return error;
		}

	/* ��꤫����³�����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

	if (nblk_error == E_OK) {
		syscall(get_tim(&now));
		syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6lu, from: %s.%u",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
		}
	else {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(nblk_error));
		return nblk_error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	rlen = scount = rcount = total = 0;
	while (true) {
		if ((error = tcp_rcv_buf(cepid, (void**)&rbuf, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s", cepid, itron_strerror(error));
			break;
			}

		/* ��������ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_rlen < 0) {	/* ���顼 */
			syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s", 
			                   cepid, itron_strerror(nblk_rlen));
			break;
			}
		else if (nblk_rlen == 0)	/* ������λ */
			break;

		rblen = nblk_rlen;

		/* �Хåե��λĤ�ˤ�ꡢ����Ĺ��Ĵ�����롣*/
		if (rblen > BUF_SIZE - rlen)
			rblen = BUF_SIZE - rlen;
		total += rblen;
		rlen   = rblen;

		head = *rbuf;
		tail = *(rbuf + rblen - 1);
		rcount ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] "
		                   "rcount: %4d, len: %4d, data %02x -> %02x",
		                   cepid, rcount, rblen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */

		memcpy(buffer, rbuf, rblen);

		if ((error = tcp_rel_buf(cepid, rlen)) < 0) {
			syslog(LOG_NOTICE, "[TES:%02d REL] error: %s",
			                   cepid, itron_strerror(error));
			break;
			}

		soff = 0;
		while (rlen > 0) {

			if ((error = tcp_get_buf(cepid, (void**)&sbuf, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TES:%02d GET] error: %s",
				                   cepid, itron_strerror(error));
				goto err_fin;
				}

			/* �����Хåե��γ�������λ����ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_slen < 0) {
				syslog(LOG_NOTICE, "[TES:%02d GET] error: %s",
				                   cepid, itron_strerror(nblk_slen));
				goto err_fin;
				}

			sblen = nblk_slen;
			scount ++;
			slen = sblen < rlen ? sblen : rlen;
			memcpy(sbuf, buffer + soff, slen);

			if ((error = tcp_snd_buf(cepid, slen)) != E_OK) {
				syslog(LOG_NOTICE, "[TES:%02d SND] error: %s",
				                   cepid, itron_strerror(error));
				goto err_fin;
				}
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] scount: %4d, len: %4d",
			                   cepid, scount, slen);
#endif	/* of #ifdef SHOW_RCV_RANGE */

			rlen -= slen;
			soff += slen;
			}
		}
err_fin:

#ifdef USE_TCP_SHT_CEP
	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d SHT] error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

	if ((error = tcp_cls_cep(cepid, TMO_NBLK)) != E_WBLK)
		syslog(LOG_NOTICE, "[TES:%02d CLS] error: %s", cepid, itron_strerror(error));

	/* ��������λ����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d FIN] finished:   %6lu, snd: %4u, rcv: %4u, len: %lu",
	                   cepid, now / SYSTIM_HZ, scount, rcount, total);

	return error == E_WBLK ? E_OK : error;
	}

#else	/* of #ifdef USE_COPYSAVE_API */

static ER
tcp_echo_srv (ID cepid, ID repid)
{
	SYSTIM		now;
	ER		error;
	uint32_t	total;
	uint16_t	rlen, slen, soff, scount, rcount;
	char		head, tail;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(error));
		return error;
		}

	/* ��꤫����³�����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

	if (nblk_error == E_OK) {
		syscall(get_tim(&now));
		syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6lu, from: %s.%u",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
		}
	else {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(nblk_error));
		return nblk_error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	scount = rcount = total = 0;
	while (true) {
		if ((error = tcp_rcv_dat(cepid, buffer, BUF_SIZE - 1, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s",
			                   cepid, itron_strerror(error));
			break;
			}

		/* ������λ�ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_rlen < 0) {
			syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s",
			                   cepid, itron_strerror(nblk_rlen));
			break;
			}
		else if (nblk_rlen == 0)
			break;

		rlen = nblk_rlen;
		head = *buffer;
		tail = *(buffer + rlen - 1);
		rcount ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] rcount: %4d, len: %4d, data %02x -> %02x",
		                   cepid, rcount, rlen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */

		total += rlen;
		soff = 0;
		while (rlen > 0) {
			scount ++;
			if ((error = tcp_snd_dat(cepid, &buffer[soff], rlen, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TES:%02d SND] error: %s",
				                   cepid, itron_strerror(error));
				goto err_fin;
				}

			/* ������λ�ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_slen < 0) {
				syslog(LOG_NOTICE, "[TES:%02d SND] error: %s",
				                   cepid, itron_strerror(nblk_slen));
				goto err_fin;
				}

			slen = nblk_slen;

#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] scount: %4d, len: %4d",
			                   cepid, scount, slen);
#endif	/* of #ifdef SHOW_RCV_RANGE */

			rlen -= slen;
			soff += slen;
			}
		}
err_fin:

#ifdef USE_TCP_SHT_CEP
	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d SHT] error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

	if ((error = tcp_cls_cep(cepid, TMO_NBLK)) != E_WBLK)
		syslog(LOG_NOTICE, "[TES:%02d CLS] error: %s", cepid, itron_strerror(error));

	/* ��������λ����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d FIN] finished:   %6lu, snd: %4u, rcv: %4u, len: %lu",
	                   cepid, now / SYSTIM_HZ, scount, rcount, total);

	return error == E_WBLK ? E_OK : error;
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_COPYSAVE_API

static ER
tcp_echo_srv (ID cepid, ID repid)
{
	ER_UINT		rblen, sblen;
	SYSTIM		now;
	ER		error;
	uint32_t	total;
	uint16_t	rlen, slen, soff, scount, rcount;
	char		*rbuf, *sbuf, head, tail;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	scount = rcount = total = 0;
	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6lu, from: %s.%u",
	                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while (true) {
		if ((rblen = tcp_rcv_buf(cepid, (void**)&rbuf, RCV_TMO)) <= 0) {
			if (rblen != E_OK)
				syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s",
				                   cepid, itron_strerror(rblen));
			break;
			}

		head = *rbuf;
		tail = *(rbuf + rblen - 1);
		rcount ++;

		//syslog(LOG_NOTICE, "[TES:%02d RCV] len: %4d", cepid, (uint16_t)rblen);
#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] rcount: %4d, len: %4d, data %02x -> %02x",
		       cepid, rcount, (uint16_t)rblen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */

		rlen   = (uint16_t)rblen;
		total +=     rblen;
		soff = 0;
		while (rlen > 0) {

			if ((sblen = tcp_get_buf(cepid, (void**)&sbuf, SND_TMO)) < 0) {
				syslog(LOG_NOTICE, "[TES:%02d GET] error: %s",
				                   cepid, itron_strerror(sblen));
				goto err_fin;
				}

			//syslog(LOG_NOTICE, "[TES:%02d SND] len: %4d", cepid, (uint16_t)sblen);
			scount ++;
			slen = rlen < (uint16_t)sblen ? rlen : (uint16_t)sblen;
			memcpy(sbuf, rbuf + soff, slen);
			if ((error = tcp_snd_buf(cepid, slen)) != E_OK) {
				syslog(LOG_NOTICE, "[TES:%02d SND] error: %s",
				                   cepid, itron_strerror(error));
				goto err_fin;
				}
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] scount: %4d, len: %4d", cepid, scount, slen);
#endif	/* of #ifdef SHOW_RCV_RANGE */

			rlen -= slen;
			soff += slen;
			}

		if ((error = tcp_rel_buf(cepid, rblen)) < 0) {
			syslog(LOG_NOTICE, "[TES:%02d REL] error: %s", cepid, itron_strerror(error));
			break;
			}
		}
err_fin:

#ifdef USE_TCP_SHT_CEP
	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d SHT] error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

	if ((error = tcp_cls_cep(cepid, CLS_TMO)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d CLS] error: %s", cepid, itron_strerror(error));

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d FIN] finished:   %6lu, snd: %4u, rcv: %4u, len: %lu",
	                   cepid, now / SYSTIM_HZ, scount, rcount, total);

	return error;
	}

#else	/* of #ifdef USE_COPYSAVE_API */

/*
 *  tcp_echo_srv -- TCP ������������
 */

static ER
tcp_echo_srv (ID cepid, ID repid)
{
	ER_UINT		rlen, slen;
	ER		error = E_OK;
	SYSTIM		now;
	uint32_t	total;
	uint16_t	soff, scount, rcount;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	scount = rcount = total = 0;
	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6lu, from: %s.%u",
	                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while (true) {
		if ((rlen = tcp_rcv_dat(cepid, buffer, BUF_SIZE - 1, RCV_TMO)) <= 0) {
			if (rlen != E_OK)
				syslog(LOG_NOTICE, "[TES:%02d RCV] error: %s",
				                   cepid, itron_strerror(rlen));
			break;
			}

		rcount ++;
#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] rcount: %4d, len: %4d, data %02x -> %02x",
		       cepid, rcount, (uint16_t)rlen, *buffer, *(buffer + rlen - 1));
#endif	/* of #ifdef SHOW_RCV_RANGE */

		total += rlen;
		soff = 0;
		while (rlen > 0) {
			scount ++;
			if ((slen = tcp_snd_dat(cepid, &buffer[soff], rlen, SND_TMO)) < 0) {
				syslog(LOG_NOTICE, "[TES:%02d SND] error: %s",
				                   cepid, itron_strerror(slen));
				goto err_fin;
				}
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] scount: %4d, len: %4d", cepid, scount, (uint16_t)slen);
#endif	/* of #ifdef SHOW_RCV_RANGE */

			rlen -= slen;
			soff += slen;
			}
		}
err_fin:

#ifdef USE_TCP_SHT_CEP
	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d SHT] error: %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

	if ((error = tcp_cls_cep(cepid, CLS_TMO)) != E_OK)
		syslog(LOG_NOTICE, "[TES:%02d CLS] error: %s", cepid, itron_strerror(error));

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d FIN] finished:   %6lu, snd: %4u, rcv: %4u, len: %lu",
	                   cepid, now / SYSTIM_HZ, scount, rcount, total);

	return error;
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

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
	crep.myaddr.portno = UINT_C(7);

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
	ccep.sbufsz = TCP_ECHO_SRV_SWBUF_SIZE;
	ccep.rbufsz = TCP_ECHO_SRV_RWBUF_SIZE;

#ifdef TCP_CFG_SWBUF_CSAVE
	ccep.sbuf = NADR;
#else
	ccep.sbuf = tcp_echo_srv_swbuf;
#endif
#ifdef TCP_CFG_RWBUF_CSAVE
	ccep.rbuf = NADR;
#else
	ccep.rbuf = tcp_echo_srv_rwbuf;
#endif
#ifdef USE_TCP_NON_BLOCKING
	ccep.callback = (FP)callback_nblk_tcp_echo_srv;
#else
	ccep.callback = NULL;
#endif

	return alloc_tcp_cep(cepid, tskid, &ccep);
	}

/*
 *  tcp_echo_srv_task -- TCP �����������Х�����
 */

void
tcp_echo_srv_task (intptr_t exinf)
{
	ID	tskid, cepid, repid;
	ER	error = E_OK;

	syscall(get_tid(&tskid));
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d] started.", tskid);
	while (true) {

		syscall(slp_tsk());
		if ((error = get_tcp_cep (&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:00 EXT] CEP create error: %s", itron_strerror(error));
			continue;
			}

		while (true) {

			if ((error = get_tcp_rep (&repid)) != E_OK) {
				syslog(LOG_NOTICE, "[TES:00 EXT] REP create error: %s", itron_strerror(error));
				break;
				}
			else if ((error = tcp_echo_srv(cepid, repid)) != E_OK) {
				error = free_tcp_rep(repid, error != E_DLT);
				break;
				}
			}

		if ((error = free_tcp_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d EXT] CEP delete error: %s", cepid, itron_strerror(error));

		}
	}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

/*
 *  tcp_echo_srv_task -- TCP �����������Х�����
 */

void
tcp_echo_srv_task(intptr_t exinf)
{
	ID	tskid;
	ER	error;

	syscall(get_tid(&tskid));
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		while ((error = tcp_echo_srv((ID)exinf, TCP_ECHO_SRV_REPID)) == E_OK)
			;
		syslog(LOG_NOTICE, "[TES:%02d] goto sleep 60[s], error: %s", (ID)exinf, itron_strerror(error));
		tslp_tsk(60 * 1000);
		}
	}

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

#endif	/* of #ifdef USE_TCP_ECHO_SRV1 */
