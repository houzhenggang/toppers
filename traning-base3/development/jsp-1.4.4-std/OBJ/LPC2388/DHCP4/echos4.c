/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次の条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: echos4.c,v 1.5 2009/12/24 05:40:11 abe Exp abe $
 */

/* 
 *  IPv4、TCP ECHO サーバ、送受信タスク同一型
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
 *  外部関数の定義
 */

extern const char *itron_strerror (ER ercd);

/*
 *  注意:
 *
 *    BUF_SIZE は TCP の
 *    送信ウインドウバッファサイズ + 受信ウインドウバッファサイズの 
 *    3/2 倍以上の大きさがなければ、デッドロックする可能性がある。
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
 *  TCP 送受信バッファ
 */

UB tcp_echo_srv_swbuf[TCP_ECHO_SRV_SWBUF_SIZE];
UB tcp_echo_srv_rwbuf[TCP_ECHO_SRV_RWBUF_SIZE];

/*
 *  MACアドレスの設定
 */
void
macaddr_init(VP_INT exinf)
{
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE1};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}


#ifdef USE_TCP_NON_BLOCKING

/*
 *  ノンブロッキングコールのコールバック関数
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
	 * 自分のMACアドレス読み込み
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

		/* 相手から接続されるまで待つ。*/
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

			/* 受信するまで待つ。*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_rlen < 0) {		/* エラー */
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s", itron_strerror(nblk_rlen));
				break;
				}
			else if (nblk_rlen == 0)	/* 受信終了 */
				break;

			rblen = (UH)nblk_rlen;

			/* バッファの残りにより、受信長を調整する。*/
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

				/* 送信バッファの獲得が完了するまで待つ。*/
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

		/* 開放が完了するまで待つ。*/
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
	 * 自分のMACアドレス読み込み
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

		/* 相手から接続されるまで待つ。*/
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

			/* 受信完了まで待つ。*/
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

				/* 送信完了まで待つ。*/
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

		/* 開放が完了するまで待つ。*/
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
	 * 自分のMACアドレス読み込み
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
	 * 自分のMACアドレス読み込み
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
