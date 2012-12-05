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
#include <stdio.h>

#include "config.h"

#include "kernel_id.h"
#include "tinet_id.h"

#include <tinet_config.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

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
#define RBUF_SIZE   384

typedef struct netqueue {
	UH   head;					/* netqueue head */
	UH   tail;					/* netqueue tail */
	UH   cnt;
	UH   size;					/* �Хåե������� */
	UB   *pbuffer;				/* �Хåե����ꥢ */
} NETQUEUE;

typedef struct netdev {
	NETQUEUE *sndq;
	NETQUEUE *rcvq;
} NETDEV;

static T_IPV4EP	dst;

#ifdef USE_TCP_NON_BLOCKING

static ER		nblk_error = E_OK;
static ER_UINT	nblk_slen  = 0;
static ER_UINT	nblk_rlen  = 0;
static BOOL     connect = FALSE;
static UB 		sbuffer[BUF_SIZE];
static UB       rbuffer[RBUF_SIZE];
static NETQUEUE sndqueue;
static NETQUEUE rcvqueue;
static NETDEV   telnetdev;
static void (*callback_telnet)(INT) = NULL;

#else	/* of #ifdef USE_TCP_NON_BLOCKING */
#error "Not support this tcpip api."
#endif	/* of #ifdef USE_TCP_NON_BLOCKING */


/*
 *  TCP �������Хåե�
 */

UB tcp_telnet_srv_swbuf[TCP_TELNET_SRV_SWBUF_SIZE];
UB tcp_telnet_srv_rwbuf[TCP_TELNET_SRV_RWBUF_SIZE];

#ifdef USE_TCP_NON_BLOCKING

static INT
setqueue(NETQUEUE *que, UB *buf, INT len)
{
	INT slen;

	syscall(wai_sem(SEM_TCP_TELNET_QUEUE_LOCK));
	for(slen = 0 ; len > 0 && que->cnt < que->size ; len--, slen++){
		que->pbuffer[que->tail++] = *buf++;
		que->cnt++;
		if(que->tail >= que->size)
			que->tail = 0;
	}
	syscall(sig_sem(SEM_TCP_TELNET_QUEUE_LOCK));
	return slen;
}

static INT
getqueue(NETQUEUE *que, UB *buf, INT len)
{
	INT slen;
	UB  ch;

	syscall(wai_sem(SEM_TCP_TELNET_QUEUE_LOCK));
	for(slen = 0 ; len > 0 && que->cnt > 0 && connect ; len--, slen++){
		ch = que->pbuffer[que->head++];
		*buf++ = ch;
		que->cnt--;
		if(que->head >= que->size)
			que->head = 0;
	}
	syscall(sig_sem(SEM_TCP_TELNET_QUEUE_LOCK));
	return slen;
}

/*
 *  TELNET�����֤�ʸ�������ʸ
 */
static int
netlocal_puts(FILE *st, unsigned int len, char *s)
{
	NETQUEUE *que = ((NETDEV*)st->_dev)->sndq;
	int cnt, slen;

	for(cnt = 0 ; len > 0 ;){
		slen = setqueue(que, s+cnt, len);
		len -= slen;
		cnt += slen;
		if(len > 0)
			dly_tsk(10);
	}
	return cnt;
}

/*
 *  TELNET�����֤Σ�ʸ������ʸ
 */
static int
netlocal_putc(FILE *st, INT ch)
{
	char buf[2];

	buf[0] = ch;
	return netlocal_puts(st, 1, buf);
}

/*
 *  TELNET�����֤�ʸ��������ʸ
 */
static int
netlocal_gets(FILE *st, unsigned int len, char *s)
{
	NETQUEUE *que = ((NETDEV*)st->_dev)->rcvq;
	int cnt, slen;

	for(cnt = 0 ; len > 0 && connect ;){
		slen = getqueue(que, s+cnt, len);
		len -= slen;
		cnt += slen;
		if(len > 0)
			dly_tsk(10);
	}
	return cnt;
}

static int
net_getc_raw(FILE *st)
{
	char buf[2];

	netlocal_gets(st, 1, buf);
	return (int)buf[0];
}

/*
 *  TELNET�����֤Σ�ʸ������ʸ
 */
static int
netlocal_getc(FILE *st)
{
	int ch, req;

	ch = net_getc_raw(st);
	while(ch == TELNET_OPT_IAC){
		req = net_getc_raw(st);
		switch (req) {
		case TELNET_OPT_WILL:
		case TELNET_OPT_WONT:
		case TELNET_OPT_DO:
		case TELNET_OPT_DONT:
			req = net_getc_raw(st);
			break;
		case TELNET_OPT_SB:
			while ((req = net_getc_raw(st)) != EOF && req != TELNET_OPT_IAC) {
				if ((req = net_getc_raw(st)) == EOF || req == TELNET_OPT_SE)
					break;
			}
			break;
		default:
			break;
		}
		ch = net_getc_raw(st);
	}
	return ch;
}

/*
 *  TELNET�����֤Υǡ����ե�å���ʸ
 */
static int
netlocal_flush(FILE *st)
{
	dly_tsk(100);
	return 0;
}

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

void
tcp_telnet_srv_init(void (*func)(INT mode))
{
	NETQUEUE *sndq = &sndqueue;
	NETQUEUE *rcvq = &rcvqueue;

	callback_telnet = func;
	sndq->head = 0;
	sndq->tail = 0;
	sndq->cnt  = 0;
	sndq->size = BUF_SIZE;
	sndq->pbuffer = sbuffer;
	rcvq->head = 0;
	rcvq->tail = 0;
	rcvq->cnt  = 0;
	rcvq->size = RBUF_SIZE;
	rcvq->pbuffer = rbuffer;
	telnetdev.sndq = sndq;
	telnetdev.rcvq = rcvq;

	act_tsk(TCP_TELNET_SRV_TASK);
}

/*
 *  ɸ������������
 */
INT
tcp_telnet_srv_set_file(void *pt)
{
	FILE *st = pt;

	st->_file = -1;
	st->_func_in    = netlocal_getc;
	st->_func_ins   = netlocal_gets;
	st->_func_out   = netlocal_putc;
	st->_func_outs  = netlocal_puts;
	st->_func_flush = netlocal_flush;
	st->_dev        = (void *)&telnetdev;
	return 1;
}

/*
 *  ��³��ǧ
 */
BOOL tcp_telnet_connect(void)
{
	return connect;
}

#ifdef USE_COPYSAVE_API

static INT
tcp_send_buffer(ID cepid, NETQUEUE *que)
{
	INT len = 0;
	UB  *sbuf;
	INT slen;
	ER	error = E_OK;

	while(que->cnt > 0){
		if ((error = tcp_get_buf((INT)cepid, (VP *)&sbuf, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) GET] error: %s",
			                   itron_strerror(error));
			return -1;
		}

		/* �����Хåե��γ�������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NSND_READY));

		if (nblk_slen < 0) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) GET] error: %s",
			                   itron_strerror(nblk_slen));
			return -1;
		}

		slen = getqueue(que, sbuf, nblk_slen);
		if ((error = tcp_snd_buf((INT)cepid, slen)) != E_OK) {
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
			                   itron_strerror(error));
			return -1;
		}
		len += slen;
	}
	return len;
}

void
tcp_telnet_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rlen, count;
	UB	*rbuf;
	ID	tskid;
	ER	error = E_OK;
	NETQUEUE *sndq = &sndqueue;
	NETQUEUE *rcvq = &rcvqueue;

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
		if(callback_telnet != NULL)
			callback_telnet(TCP_TELNET_IN);

		total = count = 0;
		while (TRUE) {
			if ((error = tcp_rcv_buf((INT)exinf, (VP *)&rbuf, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s", itron_strerror(error));
				break;
			}

			/* ��������ޤ��Ԥġ�*/
			do{
				if(tcp_send_buffer((ID)exinf, sndq) < 0)
					goto err_fin;
				error = twai_sem(SEM_TCP_TELNET_SRV_NRCV_READY, 20);
			}while(error != E_OK);

			if (nblk_rlen < 0) {		/* ���顼 */
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s", itron_strerror(nblk_rlen));
				break;
				}
			else if (nblk_rlen == 0)	/* ������λ */
				break;

			rlen = setqueue(rcvq, rbuf, nblk_rlen);
			total += rlen;
			count ++;

			if ((error = tcp_rel_buf((INT)exinf, rlen)) < 0) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) REL] error: %s",
				                   itron_strerror(error));
				break;
			}
		}
	err_fin:
		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CLS] error: %s", itron_strerror(error));
		if(callback_telnet != NULL)
			callback_telnet(TCP_TELNET_OUT);
		connect = FALSE;

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_TELNET_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) FIN] finished, total count: %d, len: %d", count, total);
	}
}

#else	/* of #ifdef USE_COPYSAVE_API */

static INT
tcp_send_buffer(ID cepid, NETQUEUE *que)
{
	INT len = 0;
	UH  slen, soff;
	ER	error = E_OK;
	static UB  buffer[BUF_SIZE];

	while(que->cnt > 0){
		slen = getqueue(que, buffer, BUF_SIZE);
		soff = 0;
		while(slen > 0){
			if ((error = tcp_snd_dat(cepid, &buffer[soff], slen, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
				                   itron_strerror(error));
				return -1;
			}

			/* ������λ�ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_TELNET_SRV_NSND_READY));

			if (nblk_slen < 0) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SND] error: %s",
				                   itron_strerror(nblk_slen));
				return -1;
			}

			slen -= (UH)nblk_slen;
			soff += (UH)nblk_slen;
			len  += (UH)nblk_slen;
		}
	}
	return len;
}

void
tcp_telnet_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rlen, roff, /*soff,*/ count;
	ID	tskid;
	ER	error;
	NETQUEUE *sndq = &sndqueue;
	NETQUEUE *rcvq = &rcvqueue;
	static UB buffer[BUF_SIZE];

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
		if(callback_telnet != NULL)
			callback_telnet(TCP_TELNET_IN);

		count = total = 0;
		while (TRUE) {
			if ((error = tcp_rcv_dat((INT)exinf, buffer, BUF_SIZE - 1, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s",
				                   itron_strerror(error));
				break;
			}

			/* ������λ�ޤ��Ԥġ�*/
			do{
				if(tcp_send_buffer((ID)exinf, sndq) < 0)
					goto err_fin;
				error = twai_sem(SEM_TCP_TELNET_SRV_NRCV_READY, 20);
			}while(error != E_OK);

			if (nblk_rlen < 0) {
				syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) RCV] error: %s",
				                   itron_strerror(nblk_rlen));
				break;
			}
			else if (nblk_rlen == 0)
				break;

			roff = 0;
			while(roff != nblk_rlen){
				roff += setqueue(rcvq, buffer+roff, nblk_rlen-roff);
				if(tcp_send_buffer((ID)exinf, sndq) < 0)
					goto err_fin;
				dly_tsk(10);
			}
			total += (UW)nblk_rlen;
			count ++;
		}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP TELNET SRV (NBLK) CLS] error: %s", itron_strerror(error));
		if(callback_telnet != NULL)
			callback_telnet(TCP_TELNET_OUT);
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

