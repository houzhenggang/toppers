/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: telnet.c,v 1.0 2010/11/28 14:10:04 roi Exp $
 */

/* 
 *  IPv4��TCP TELNET �����С�������������Ʊ�췿
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#include <tinet_config.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "telnet.h"

/*  TELNET ���ץ���� */

#define TELNET_OPT_SE		(240)
#define TELNET_OPT_NOP		(241)
#define TELNET_OPT_DM		(242)
#define TELNET_OPT_BRK		(243)
#define TELNET_OPT_IP		(244)
#define TELNET_OPT_AO		(245)
#define TELNET_OPT_AYT		(246)
#define TELNET_OPT_EC		(247)
#define TELNET_OPT_EL		(248)
#define TELNET_OPT_GA		(249)
#define TELNET_OPT_SB		(250)
#define TELNET_OPT_WILL		(251)
#define TELNET_OPT_WONT		(252)
#define TELNET_OPT_DO		(253)
#define TELNET_OPT_DONT		(254)
#define TELNET_OPT_IAC		(255)

/*
 *  �����ؿ������
 */

extern const char *itron_strerror (ER ercd);

/*
 *  ���:
 *
 *    BUF_SIZE �� TCP ��
 *    ����������ɥ��Хåե������� + ����������ɥ��Хåե��������� 
 *    3/2 �ܰʾ���礭�����ʤ���С��ǥåɥ�å������ǽ�������롣
 */

#define BUF_SIZE	((TCP_TELNET_SRV_SWBUF_SIZE + \
                          TCP_TELNET_SRV_RWBUF_SIZE) * 3 / 2)

static T_IPV4EP		dst;

#ifdef USE_TCP_NON_BLOCKING

static ER		nblk_error = E_OK;
static ER_UINT		nblk_slen  = 0;
static ER_UINT		nblk_rlen  = 0;
static BOOL     connect = FALSE;

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_COPYSAVE_API

static UB 		buffer[BUF_SIZE];

#endif	/* of #ifndef USE_COPYSAVE_API */

/*
 *  TCP �������Хåե�
 */

UB tcp_telnet_srv_swbuf[TCP_TELNET_SRV_SWBUF_SIZE];
UB tcp_telnet_srv_rwbuf[TCP_TELNET_SRV_RWBUF_SIZE];

static int
net_getc_raw(UB **rbuf, UH *slen, UH *rlen)
{
	UB  *p = *rbuf;
	int ch;

	if(*slen > 0){
		(*rlen)++;
		ch = *p;
		(*rbuf)++;
		(*slen)--;
	}
	else
		ch = -1;
	return ch;
}

/*
 *  TELNET�����֤Σ�ʸ������ʸ
 */
static int
netlocal_getc(UB **rbuf, UH *slen, UH *rlen)
{
	int ch, req;

	ch = net_getc_raw(rbuf, slen, rlen);
	while(ch == TELNET_OPT_IAC){
		req = net_getc_raw(rbuf, slen, rlen);
		switch (req) {
		case TELNET_OPT_WILL:
		case TELNET_OPT_WONT:
		case TELNET_OPT_DO:
		case TELNET_OPT_DONT:
			req = net_getc_raw(rbuf, slen, rlen);
			break;
		case TELNET_OPT_SB:
			while ((req = net_getc_raw(rbuf, slen, rlen)) != -1 && req != TELNET_OPT_IAC) {
				if ((req = net_getc_raw(rbuf, slen, rlen)) == -1 || req == TELNET_OPT_SE)
					break;
			}
			break;
		default:
			break;
		}
		ch = net_getc_raw(rbuf, slen, rlen);
	}
	return ch;
}

int telnet_copy(UB *sbuf, UB *rbuf, UH slen, UH *rlen)
{
	int ch, len = 0;

	*rlen = 0;
	while(slen > 0){
		ch = netlocal_getc(&rbuf, &slen, rlen);
		*sbuf++ = ch;
		len++;
	}
	return len;
}


#ifdef USE_TCP_NON_BLOCKING

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp_telnet_srv (ID cepid, FN fncd, VP p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		nblk_error = *(ER*)p_parblk;
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_DAT:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CBN] recv err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NRCV_READY));
		break;

	case TFN_TCP_SND_DAT:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CBN] send err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NSND_READY));
		break;

	case TFN_TCP_CLS_CEP:
		if ((nblk_error = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CBN] clse err: %s", itron_strerror(nblk_error));
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_BUF:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CBN] rbuf err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NRCV_READY));
		break;

	case TFN_TCP_GET_BUF:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CBN] sbuf err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_TELNET_SRV_NSND_READY));
		break;

	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
	}
	return error;
}

/*
 *  ��³��ǧ
 */
BOOL tcp_telnet_connect(void)
{
	return connect;
}

#ifdef USE_COPYSAVE_API

void
tcp_telnet_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rblen, sblen, rlen, slen, soff, count;
	UB	*rbuf, *sbuf, head, tail;
	ID	tskid;
	ER	error = E_OK;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK):%d,%d] (copy save API) started.", tskid, (INT)exinf);

	while (TRUE) {
		if ((error = tcp_acp_cep((INT)exinf, TCP_TELNET_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
			}

		/* ��꤫����³�����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NBLK_READY));

		if (nblk_error == E_OK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] connected from %s:%d", ip2str(NULL, &dst.ipaddr), dst.portno);
		else {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
		}
		connect = TRUE;

		total = rlen = count = 0;
		while (TRUE) {
			if ((error = tcp_rcv_buf((INT)exinf, (VP *)&rbuf, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s", itron_strerror(error));
				break;
			}

			/* ��������ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_TELNET_SRV_NRCV_READY));

			if (nblk_rlen < 0) {		/* ���顼 */
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s", itron_strerror(nblk_rlen));
				break;
			}
			else if (nblk_rlen == 0)	/* ������λ */
				break;

			rblen = (UH)nblk_rlen;

			/* �Хåե��λĤ�ˤ�ꡢ����Ĺ��Ĵ�����롣*/
			if (rblen > BUF_SIZE - rlen)
				rblen = BUF_SIZE - rlen;
			total += rblen;
			rlen   = rblen;

			head = *rbuf;
			tail = *(rbuf + rblen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] "
			                   "count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rblen, head, tail);*/
			memcpy(buffer, rbuf, rblen);

			if ((error = tcp_rel_buf((INT)exinf, rlen)) < 0) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) REL] error: %s",
				                   itron_strerror(error));
				break;
			}

			soff = 0;
			while (rlen > 0) {

				if ((error = tcp_get_buf((INT)exinf, (VP *)&sbuf, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) GET] error: %s",
					                   itron_strerror(error));
					goto err_fin;
				}

				/* �����Хåե��γ�������λ����ޤ��Ԥġ�*/
				syscall(wai_sem(SEM_TCP_TELNET_SRV_NSND_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) GET] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
				}
				else
					/*syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) GET] len: %d", nblk_slen)*/;

				sblen = (UH)nblk_slen;
				slen = sblen < rlen ? sblen : rlen;
#if 0	/* ROI DEBUG */
				memcpy(sbuf, buffer + soff, slen);
#else	/* ROI DEBUG */
				slen = telnet_copy(sbuf, buffer + soff, slen, &rblen);
#endif	/* ROI DEBUG */

				if ((error = tcp_snd_buf((INT)exinf, slen)) != E_OK) {
					syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
				}
				/*syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] len: %d", slen);*/

#if 0	/* ROI DEBUG */
				rlen -= slen;
#else	/* ROI DEBUG */
				rlen -= rblen;
#endif	/* ROI DEBUG */
				soff += slen;
			}
		}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CLS] error: %s", itron_strerror(error));
		connect = FALSE;

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) FIN] finished, total count: %d, len: %d", count, total);
	}
}

#else	/* of #ifdef USE_COPYSAVE_API */

void
tcp_telnet_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rlen, slen, soff, count, sblen, rblen;
	ID	tskid;
	ER	error;
	UB	head, tail;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK):%d,%d] started.", tskid, (INT)exinf);

	while (TRUE) {
		if ((error = tcp_acp_cep((INT)exinf, TCP_TELNET_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
		}

		/* ��꤫����³�����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NBLK_READY));

		if (nblk_error == E_OK) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] connected from %s:%d",
			                   ip2str(NULL, &dst.ipaddr), dst.portno);
		}
		else {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
		}
		connect = TRUE;

		count = total = 0;
		while (TRUE) {
			if ((error = tcp_rcv_dat((INT)exinf, buffer, BUF_SIZE - 1, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s",
				                   itron_strerror(error));
				break;
			}

			/* ������λ�ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_TELNET_SRV_NRCV_READY));

			if (nblk_rlen < 0) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s",
				                   itron_strerror(nblk_rlen));
				break;
			}
			else if (nblk_rlen == 0)
				break;

			rlen   = (UH)nblk_rlen;
			total += (UW)nblk_rlen;
			head = *buffer;
			tail = *(buffer + rlen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rlen, head, tail);*/
			soff = 0;
			while (rlen > 0) {
				sblen, telnet_copy(buffer + soff, buffer + soff, rlen, &rblen);
				if ((error = tcp_snd_dat((INT)exinf, &buffer[soff], sblen, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
				}

				/* ������λ�ޤ��Ԥġ�*/
				syscall(wai_sem(SEM_TCP_TELNET_SRV_NSND_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
				}
				else
					/*syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] len: %4d", nblk_slen)*/;

				slen = (UH)nblk_slen;
				rlen -= rblen;
				soff += slen;
			}
		}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CLS] error: %s", itron_strerror(error));
		connect = FALSE;

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) FIN] finished, total cnt: %d, len: %d", count, total);
	}
}

#endif	/* of #ifdef USE_COPYSAVE_API */

#else	/* of #ifdef USE_TCP_NON_BLOCKING */
#error "Not support this tcpip api."
#endif	/* of #ifdef USE_TCP_NON_BLOCKING */
