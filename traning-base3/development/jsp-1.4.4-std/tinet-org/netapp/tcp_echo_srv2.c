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
 *  @(#) $Id: tcp_echo_srv2.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  TCP ECHO ������ #2
 *
 *    ��������������ʬΥ��
 *    ���Υ�֥�å��󥰥�����
 *    ��IPv4/IPv6
 */

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
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_TCP_ECHO_SRV2

/*
 *  ɽ��
 */

/*#define SHOW_RCV_RANGE*/

/*
 *  ���ͥ������������ˡ�λ���
 */

/*#define USE_TCP_SHT_CEP*/

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

static char	buffer[BUF_SIZE];	/* �Хåե�		*/

static T_IPEP	dst;			/* ��³���		*/
static bool_t	ena_rcv;		/* ������ǽ�ե饰	*/
static char	*rptr = buffer;		/* �����ݥ���		*/
static char	*sptr = buffer;		/* �����ݥ���		*/
static uint32_t	rcv_total;		/* ����ʸ����		*/
static uint32_t	snd_total;		/* ����ʸ����		*/
static uint16_t	chars;			/* �Хåե����ʸ����	*/
static uint16_t	rcv_count;		/* �������		*/
static uint16_t	snd_count;		/* �������		*/

#ifdef USE_TCP_NON_BLOCKING

static ER	rcv_error = E_OK;	/* �������Υ�֥�å��󥰥����륨�顼 */
static ER	snd_error = 1;		/* �������Υ�֥�å��󥰥����륨�顼 */

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER		error = E_OK;
	ER_UINT		slen, rlen;
	SYSTIM		now;
	uint16_t	last;
	char		head, tail;

	get_tim(&now);

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		rcv_error = *(ER*)p_parblk;
		if (rcv_error == E_OK) {
			sptr = rptr = buffer;
			snd_count = snd_total = rcv_count = rcv_total = chars = 0;
			snd_error = 1;
			ena_rcv   = true;
			syslog(LOG_NOTICE, "[TES:%02d CBN] connected:  %6ld, from: %s.%d",
			                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
			}
		else
			syslog(LOG_NOTICE, "[TES:%02d CBN] accept error: %s\n", cepid, itron_strerror(rcv_error));

		syscall(sig_sem(SEM_TCP_ECHO_SRV_RCV_READY));
		break;

	case TFN_TCP_SND_DAT:
		slen = snd_error = *(ER*)p_parblk;
		if (slen > 0) {
			head = *sptr;
			tail = *(sptr + slen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d CBN] send len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)slen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			snd_count ++;
			snd_total += slen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* �����ݥ��󥿤�ʤ�롣*/
			if (sptr - buffer + slen >= sizeof(buffer))
				sptr -= sizeof(buffer) - slen;
			else
				sptr += slen;

			/* �Хåե����ʸ�����򸺤餹��*/
			last   = chars;
			chars -= slen;

 			/* �Хåե����ʸ��������С������������򵯾����롣*/
			if (chars > 0 || (!ena_rcv && chars == 0))
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* ������ǽ�ǡ��Хåե���˶������Ǥ���С������������򵯾����롣*/
			if (ena_rcv && last == sizeof(buffer) && sizeof(buffer) - chars > 0)
				syscall(sig_sem(SEM_TCP_ECHO_SRV_RCV_READY));

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}
		else {
			syslog(LOG_NOTICE, "[TES:%02d CBN] send error = %s", cepid, itron_strerror(snd_error));
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);
			}
		break;

	case TFN_TCP_RCV_DAT:
		rlen = rcv_error = *(ER*)p_parblk;
		if (rlen > 0) {
			head = *rptr;
			tail = *(rptr + rlen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d CBN] recv len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)rlen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			rcv_count ++;
			rcv_total += rlen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* �����ݥ��󥿤�ʤ�롣*/
			if (rptr - buffer + rlen >= sizeof(buffer))
				rptr -= sizeof(buffer) - rlen;
			else
				rptr += rlen;

			/* �Хåե����ʸ���������䤹��*/
			last   = chars;
			chars += rlen;

 			/* �Хåե����ʸ��������С������������򵯾����롣*/
			if (last == 0 && chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* �Хåե���˶���������С������������򵯾����롣*/
			if (sizeof(buffer) - chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}
		else {
			if (rlen < 0)
				syslog(LOG_NOTICE, "[TES:%02d CBN] recv error = %s", cepid, itron_strerror(rcv_error));
			sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);
			}
		break;

	case TFN_TCP_CLS_CEP:
		snd_error = *(ER*)p_parblk;
		if (snd_error != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d CBN] close error = %s", cepid, itron_strerror(snd_error));

		syslog(LOG_NOTICE, "[TES:%02d CBN] finished:   %6ld, snd: %4d, rcv: %4d, len: %ld",
		                   cepid, now / SYSTIM_HZ, snd_count, rcv_count, snd_total);

		sig_sem(SEM_TCP_ECHO_SRV_CLS_READY);
		break;

	case TFN_TCP_CON_CEP:
	case TFN_TCP_GET_BUF:
	case TFN_TCP_RCV_BUF:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		}
	return error;
	}

/*
 *  TCP ECHO �����м����롼���� (�Υ�֥�å��󥰥��������)
 */

ER
tcp_echo_srv_rcv (ID cepid, ID repid)
{
	ER		error;
	uint16_t	blen;

	if ((error = psnd_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t)cepid)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d RCV] sync error: %s", cepid, itron_strerror(error));
		return error;
		}

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] accept error = %s", cepid, itron_strerror(error));
		return error;
		}

	/* ���ͥ�������ߴ�λ�ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));

	/* �ԤäƤ���֤˥��顼�ˤʤä��顢���ͥ������γ����Ԥ�����롣*/
	if (rcv_error != E_OK)
		return rcv_error;

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	while (true) {

		/* ������������׻����롣*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
		if (sptr > rptr)
			blen = sptr - rptr;
		else
			blen = sizeof(buffer) - (rptr - buffer);
		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* �������롣*/
		if ((error = tcp_rcv_dat(cepid, rptr, blen, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d RCV] recv error = %s", cepid, itron_strerror(error));
			break;
			}

		/* �����Хåե��˶����Ǥ���ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));

		/* �ԤäƤ���֤ˡ�����ʸ������ 0 �ˤʤ뤫�����顼�ˤʤä��齪λ���롣*/
		if (rcv_error <= 0)
			break;

		}

	/* ������λ */
	ena_rcv = false;

	/* �����Хåե���ʸ��������Τ��ԤäƤ��������������򵯾����롣*/
	if (chars == 0)
		sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

	/* ���ͥ���������Ǵ�λ�ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_CLS_READY));

	return error == E_WBLK ? E_OK : error;
	}

/*
 *  TCP ECHO ���������������� (�Υ�֥�å��󥰥��������)
 */

void
tcp_echo_srv_snd_task(intptr_t exinf)
{
	ER		error;
	ID		tskid, cepid;
	uint16_t	blen;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND:%d] started.", tskid);
	while (true) {
		if ((error = rcv_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t*)&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] sync error: %s",
			                   cepid, itron_strerror(error));
			continue;
			}

		while (true) {

			/* �Хåե���ʸ��������ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_SND_READY));

			/* �ԤäƤ���֤˥��顼�ˤʤä��齪λ���롣*/
			if (snd_error <= 0)
				break;

			/* ������λ�ǡ��Хåե���ʸ�����ʤ���н�λ���롣*/
			if (!ena_rcv && chars == 0)
				break;

			/* ������������׻����롣*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
			if (rptr > sptr)
				blen = rptr - sptr;
			else
				blen = sizeof(buffer) - (sptr - buffer);
			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* �������롣*/
			if ((error = tcp_snd_dat(cepid, sptr, blen, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TES:%02d SND] send error = %s", cepid, itron_strerror(error));
				break;
				}
			}

		/* �����Хåե��˶����Ǥ�����ԤäƤ�������������򵯾����롣*/
		if (chars == sizeof(buffer))
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

#ifdef USE_TCP_SHT_CEP
		if ((error = tcp_sht_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] shutdown error = %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

		if ((error = tcp_cls_cep(cepid, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] close error = %s", cepid, itron_strerror(error));
			}

		pol_sem(SEM_TCP_ECHO_SRV_SND_READY);
		pol_sem(SEM_TCP_ECHO_SRV_RCV_READY);
		}
	}

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

/*
 *  TCP ECHO �����м����롼����
 */

ER
tcp_echo_srv_rcv (ID cepid, ID repid)
{
	ER_UINT		rlen;
	ER		error;
	SYSTIM		now;
	uint16_t	blen, last;
	char		head, tail;

	if ((error = psnd_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t)cepid)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d RCV] sync error: %s", cepid, itron_strerror(error));
		return error;
		}

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] accept error = %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6ld, from: %s.%d",
	                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	sptr = rptr = buffer;
	snd_count = snd_total = rcv_count = rcv_total = chars = 0;
	ena_rcv   = true;
	while (true) {

		/* ������������׻����롣*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
		if (sptr > rptr)
			blen = sptr - rptr;
		else
			blen = sizeof(buffer) - (rptr - buffer);
		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* �������롣*/
		if ((rlen = tcp_rcv_dat(cepid, rptr, blen, TMO_FEVR)) <= 0) {
			if (rlen < 0)
				syslog(LOG_NOTICE, "[TES:%02d RCV] recv error = %s",
				                   cepid, itron_strerror(rlen));
			break;
			}
		head = *rptr;
		tail = *(rptr + rlen - 1);
#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] len: %4d, data %02x -> %02x",
		                   cepid, (uint16_t)rlen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
		rcv_count ++;
		rcv_total += rlen;

		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* �����ݥ��󥿤�ʤ�롣*/
		if (rptr - buffer + rlen >= sizeof(buffer))
			rptr -= sizeof(buffer) - rlen;
		else
			rptr += rlen;

		/* �Хåե����ʸ���������䤹��*/
		last   =     chars;
		chars += (uint16_t)rlen;

 				/* �Хåե����ʸ��������С������������򵯾����롣*/
		if (last == 0 && chars > 0)
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 				/* �Хåե���˶���������С������������򵯾����롣*/
		if (sizeof(buffer) - chars > 0)
			sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* �Хåե��˶������Ǥ���ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));
		}

	/* ������λ */
	ena_rcv = false;

	/* �����Хåե���ʸ��������Τ��ԤäƤ��������������򵯾����롣*/
	if (chars == 0)
		sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

	/* ���ͥ����������Ǥ���λ����ޤ��Ԥġ�*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_CLS_READY));

	return error;
	}

/*
 *  TCP ECHO ����������������
 */

void
tcp_echo_srv_snd_task(intptr_t exinf)
{
	ID		tskid, cepid;
	ER		error;
	ER_UINT		slen;
	SYSTIM		now;
	uint16_t	blen, last;
	char		head, tail;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV SND:%d] started.", tskid);
	while (true) {
		if ((error = rcv_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t*)&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] sync error: %s",
			                   cepid, itron_strerror(error));
			continue;
			}

		while (true) {

			/* �Хåե���ʸ��������ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_SND_READY));

			/* ������λ�ǡ��Хåե���ʸ�����ʤ���н�λ���롣*/
			if (!ena_rcv && chars == 0)
				break;

			/* ������������׻����롣*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
			if (rptr > sptr)
				blen = rptr - sptr;
			else
				blen = sizeof(buffer) - (sptr - buffer);
			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

			if ((slen = tcp_snd_dat(cepid, sptr, blen, TMO_FEVR)) <= 0) {
				syslog(LOG_NOTICE, "[TES:%02d SND] send error = %s", cepid, itron_strerror(slen));
				break;
				}

			head = *sptr;
			tail = *(sptr + slen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)slen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			snd_count ++;
			snd_total += slen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* �����ݥ��󥿤�ʤ�롣*/
			if (sptr - buffer + slen >= sizeof(buffer))
				sptr -= sizeof(buffer) - slen;
			else
				sptr += slen;

			/* �Хåե����ʸ�����򸺤餹��*/
			last   =     chars;
			chars -= (uint16_t)slen;

			/* ������λ�ǡ��Хåե���ʸ�����ʤ���н�λ���롣*/
			if (!ena_rcv && chars == 0) {
				syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
				break;
				}

 			/* �Хåե����ʸ��������С������������򵯾����롣*/
			if (chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* ������ǽ�ǡ��Хåե���˶������Ǥ���С������������򵯾����롣*/
			if (ena_rcv && last == sizeof(buffer) && sizeof(buffer) - chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}

		/* �����Хåե��˶����Ǥ�����ԤäƤ�������������򵯾����롣*/
		if (chars == sizeof(buffer))
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

#ifdef USE_TCP_SHT_CEP
		if ((error = tcp_sht_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] shtudown error = %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

		if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] close error = %s", cepid, itron_strerror(error));

		get_tim(&now);
		syslog(LOG_NOTICE, "[TES:%02d SND] finished:   %6ld, snd: %4d, rcv: %4d, len: %ld",
		                   cepid, now / SYSTIM_HZ, snd_count, rcv_count, snd_total);

		sig_sem(SEM_TCP_ECHO_SRV_CLS_READY);

		pol_sem(SEM_TCP_ECHO_SRV_SND_READY);
		pol_sem(SEM_TCP_ECHO_SRV_RCV_READY);
		}
	}

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
 *  get_tcp_cep -- TCP �̿�ü����������롣
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
 *  TCP ECHO �����м���������
 */

void
tcp_echo_srv_rcv_task (intptr_t exinf)
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
			else if ((error = tcp_echo_srv_rcv(cepid, repid)) != E_OK) {
				error = free_tcp_rep(repid, error != E_DLT);
				break;
				}
			}

		if ((error = free_tcp_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d EXT] CEP delete error: %s", cepid, itron_strerror(error));

		}
	}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

void
tcp_echo_srv_rcv_task(intptr_t exinf)
{
	ID	tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV RCV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		while (tcp_echo_srv_rcv((ID)exinf, TCP_ECHO_SRV_REPID) == E_OK)
			;
		}
	}

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

#endif	/* of #ifdef USE_TCP_ECHO_SRV2 */
