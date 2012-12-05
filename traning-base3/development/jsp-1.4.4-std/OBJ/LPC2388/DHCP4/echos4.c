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
 *  @(#) $Id: echos4.c,v 1.5 2009/12/24 05:40:11 abe Exp abe $
 */

/* 
 *  IPv4��TCP ECHO �����С�������������Ʊ�췿
 */

#include <string.h>

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#include <tinet_config.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "dhcp.h"
#include "echos4.h"

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

#define BUF_SIZE	((TCP_ECHO_SRV_SWBUF_SIZE + \
                          TCP_ECHO_SRV_RWBUF_SIZE) * 3 / 2)

static T_IPV4EP		dst;

#ifdef USE_TCP_NON_BLOCKING

static ER		nblk_error = E_OK;
static ER_UINT		nblk_slen  = 0;
static ER_UINT		nblk_rlen  = 0;

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifndef USE_COPYSAVE_API

static UB 		buffer[BUF_SIZE];

#endif	/* of #ifndef USE_COPYSAVE_API */

/*
 *  TCP �������Хåե�
 */

UB tcp_echo_srv_swbuf[TCP_ECHO_SRV_SWBUF_SIZE];
UB tcp_echo_srv_rwbuf[TCP_ECHO_SRV_RWBUF_SIZE];

/*
 *  MAC���ɥ쥹������
 */
void
macaddr_init(VP_INT exinf)
{
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE1};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}


#ifdef USE_TCP_NON_BLOCKING

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp_echo_srv (ID cepid, FN fncd, VP p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		nblk_error = *(ER*)p_parblk;
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_DAT:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] recv err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_SND_DAT:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] send err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_CLS_CEP:
		if ((nblk_error = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] clse err: %s", itron_strerror(nblk_error));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_BUF:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] rbuf err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_GET_BUF:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] sbuf err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

#ifdef USE_COPYSAVE_API

void
tcp_echo_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rblen, sblen, rlen, slen, soff, count;
	UB	*rbuf, *sbuf, head, tail;
	ID	tskid;
	ER	error = E_OK;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK):%d,%d] (copy save API) started.", tskid, (INT)exinf);

	/*
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}
	while (TRUE) {
		if ((error = tcp_acp_cep((INT)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
			}

		/* ��꤫����³�����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_error == E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] connected from %s:%d", ip2str(NULL, &dst.ipaddr), dst.portno);
		else {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
			}

		total = rlen = count = 0;
		while (TRUE) {
			if ((error = tcp_rcv_buf((INT)exinf, (VP *)&rbuf, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s", itron_strerror(error));
				break;
				}

			/* ��������ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_rlen < 0) {		/* ���顼 */
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s", itron_strerror(nblk_rlen));
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
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] "
			                   "count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rblen, head, tail);*/
			memcpy(buffer, rbuf, rblen);

			if ((error = tcp_rel_buf((INT)exinf, rlen)) < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) REL] error: %s",
				                   itron_strerror(error));
				break;
				}

			soff = 0;
			while (rlen > 0) {

				if ((error = tcp_get_buf((INT)exinf, (VP *)&sbuf, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}

				/* �����Хåե��γ�������λ����ޤ��Ԥġ�*/
				syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
					}
				else
					/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] len: %d", nblk_slen)*/;

				sblen = (UH)nblk_slen;
				slen = sblen < rlen ? sblen : rlen;
				memcpy(sbuf, buffer + soff, slen);

				if ((error = tcp_snd_buf((INT)exinf, slen)) != E_OK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] len: %d", slen);*/

				rlen -= slen;
				soff += slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CLS] error: %s", itron_strerror(error));

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) FIN] finished, total count: %d, len: %d", count, total);
		}
	}

#else	/* of #ifdef USE_COPYSAVE_API */

void
tcp_echo_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rlen, slen, soff, count;
	ID	tskid;
	ER	error;
	UB	head, tail;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK):%d,%d] started.", tskid, (INT)exinf);

	/*
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}
	while (TRUE) {
		if ((error = tcp_acp_cep((INT)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
			}

		/* ��꤫����³�����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_error == E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] connected from %s:%d",
			                   ip2str(NULL, &dst.ipaddr), dst.portno);
			}
		else {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
			}

		count = total = 0;
		while (TRUE) {
			if ((error = tcp_rcv_dat((INT)exinf, buffer, BUF_SIZE - 1, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s",
				                   itron_strerror(error));
				break;
				}

			/* ������λ�ޤ��Ԥġ�*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_rlen < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s",
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
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rlen, head, tail);*/
			soff = 0;
			while (rlen > 0) {
				if ((error = tcp_snd_dat((INT)exinf, &buffer[soff], rlen, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}

				/* ������λ�ޤ��Ԥġ�*/
				syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
					}
				else
					/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] len: %4d", nblk_slen)*/;

				slen = (UH)nblk_slen;
				rlen -= slen;
				soff += slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CLS] error: %s", itron_strerror(error));

		/* ��������λ����ޤ��Ԥġ�*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_COPYSAVE_API

void
tcp_echo_srv_task(VP_INT exinf)
{
	UW	total;
	UH	rlen, slen, soff, count;
	UB	*rbuf, *sbuf, head, tail;
	ID	tskid;
	ER_UINT	rblen, sblen;
	ER	error = E_OK;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d,%d] (copy save API) started.", tskid, (INT)exinf);

	/*
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}
	while (TRUE) {
		if (tcp_acp_cep((INT)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_FEVR) != E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] error: %s", itron_strerror(error));
			continue;
			}

		total = count = 0;
		syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] connected from %s:%d", ip2str(NULL, &dst.ipaddr), dst.portno);
		while (TRUE) {
			if ((rblen = tcp_rcv_buf((INT)exinf, (VP *)&rbuf, TMO_FEVR)) <= 0) {
				if (rblen != E_OK)
					syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] error: %s", itron_strerror(rblen));
				break;
				}

			rlen   = (UH)rblen;
			total += (UW)rblen;
			head = *rbuf;
			tail = *(rbuf + rlen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] count: %4d, len: %4d, data %02x -> %02x",
			       ++ count, rlen, head, tail);*/

			soff = 0;
			while (rlen > 0) {

				if ((sblen = tcp_get_buf((INT)exinf, (VP *)&sbuf, TMO_FEVR)) < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV GET] error: %s",
					                   itron_strerror(sblen));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV GET] len: %d", sblen);*/
			
				slen = rlen < (UH)sblen ? rlen : (UH)sblen;
				memcpy(sbuf, rbuf + soff, slen);
				if ((error = tcp_snd_buf((INT)exinf, slen)) != E_OK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV SND] len: %d", slen);*/

				rlen -= slen;
				soff += slen;
				}

			if ((error = tcp_rel_buf((INT)exinf, rblen)) < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV REL] error: %s", itron_strerror(error));
				break;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV CLS] error: %s", itron_strerror(error));

		syslog(LOG_NOTICE, "[TCP ECHO SRV FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#else	/* of #ifdef USE_COPYSAVE_API */

void
tcp_echo_srv_task(VP_INT exinf)
{
	UH	soff, count, total;
	ID	tskid;
	ER_UINT	rlen, slen;
	ER	error = E_OK;
    T_IF_SOFTC  *ic;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d,%d] started.", tskid, (INT)exinf);

	/*
	 * ��ʬ��MAC���ɥ쥹�ɤ߹���
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}
	while (TRUE) {
		if (tcp_acp_cep((INT)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_FEVR) != E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] error: %s", itron_strerror(error));
			continue;
			}

		total = count = 0;
		syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] connected from %s:%d",
		                   ip2str(NULL, &dst.ipaddr), dst.portno);
		while (TRUE) {
			if ((rlen = tcp_rcv_dat((INT)exinf, buffer, BUF_SIZE - 1, TMO_FEVR)) <= 0) {
				if (rlen != E_OK)
					syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] error: %s",
					                   itron_strerror(rlen));
				break;
				}

			/*syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] count: %4d, len: %4d, data %02x -> %02x",
			       ++ count, (UH)rlen, *buffer, *(buffer + rlen - 1));*/
			count ++;
			total += (UH)rlen;
			soff = 0;
			while (rlen > 0) {
				if ((slen = tcp_snd_dat((INT)exinf, &buffer[soff], rlen, TMO_FEVR)) < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV SND] error: %s",
					                   itron_strerror(slen));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV SND] len: %d", slen);*/
				rlen -=     slen;
				soff += (UH)slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((INT)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((INT)exinf, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV CLS] error: %s", itron_strerror(error));

		syslog(LOG_NOTICE, "[TCP ECHO SRV FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */
