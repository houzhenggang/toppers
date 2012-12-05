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
 *  @(#) $Id: tcp_subr_ncs.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)tcp_subr.c	8.2 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_subr.c,v 1.49.2.4 1999/08/29 16:29:55 peter Exp $
 */

#include <string.h>

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
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/in_itron.h>

#ifdef SUPPORT_TCP

#ifndef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ��̵��
 */

/*
 *  tcp_read_swbuf -- ����������ɥХåե�����ǡ������ɤ߽Ф���
 */

void
tcp_read_swbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	uint8_t	*wptr, *rptr;

	/* SDU ���礭��������å����롣*/
	if (GET_IP_SDU_SIZE(GET_IP_HDR(output)) < GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len) {
		syslog(LOG_INFO, "[TCP] shrink SUD len: %d -> %d",
		       (uint16_t)len, (uint16_t)(GET_IP_SDU_SIZE(GET_IP_HDR(output)) - GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET)));
		len = GET_IP_SDU_SIZE(GET_IP_HDR(output)) - GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET);
		}

	wptr = GET_TCP_SDU(output, IF_IP_TCP_HDR_OFFSET);

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	rptr = cep->sbuf_rptr + doff;
	if (rptr - (uint8_t*)cep->sbuf > cep->sbufsz) {

		/* ž�����Ϥ�����������ɥХåե��ν�����Ķ����Ȥ��ν�����*/
		rptr = (uint8_t*)cep->sbuf_rptr - (cep->sbufsz - doff);
		}
	else if (len + (rptr - (uint8_t*)cep->sbuf) > cep->sbufsz) {
		uint_t sub;

		/* ž���ϰϤ��饦��ɤ���Ȥ��ν��� */
		sub = (uint_t)(cep->sbufsz - (rptr - (uint8_t*)cep->sbuf));
		memcpy((void*)wptr, rptr, (size_t)sub);
		len  -= sub;
		wptr += sub;
		rptr  = (uint8_t*)cep->sbuf;
		}
	memcpy((void*)wptr, rptr, (size_t)len);

	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_DATA_SEGS],   1);
	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_DATA_OCTETS], len);

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));
	}

/*
 *  tcp_drop_swbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ������롣
 */

void
tcp_drop_swbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	uint_t	last;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	last = cep->swbuf_count;

	if (cep->sbuf_rptr + len > (uint8_t*)cep->sbuf + cep->sbufsz)
		/* �饦��ɤ���Ȥ��η׻� */
		cep->sbuf_rptr -= cep->sbufsz - len;
	else
		cep->sbuf_rptr += len;
	cep->swbuf_count -= (uint16_t)len;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->snd_nblk_tfn == TFN_TCP_GET_BUF) {	/* �Υ�֥�å��󥰥����� */

		/* �̿�ü�����å����롣*/
		syscall(wai_sem(cep->semid_lock));

		/* �����ǡ���Ĺ��׻����롣*/
		if (cep->sbufsz - cep->swbuf_count > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf))
			/* ����ߥݥ��󥿤��饦��ɤ���Ȥ��ϡ�����ߥݥ��󥿤�������������ɥХåե��ν����ޤ� */
			len = (uint_t)(cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf));
		else
			len = cep->sbufsz - cep->swbuf_count;

		/* �̿�ü���Υ�å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		if (len > 0) {

			/* tcp_get_buf �γ�����Ĺ�����ꤹ�롣*/
			cep->get_buf_len = len;

			/* ����������ɥХåե��Υ��ɥ쥹���֤���*/
			*cep->snd_p_buf = cep->sbuf_wptr;

			if (IS_PTR_DEFINED(cep->callback))
#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
			cep->snd_tskid = TA_NULL;
			cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			}
		}

#ifdef TCP_CFG_EXTENTIONS

	else if (cep->snd_nblk_tfn == TFN_TCP_SND_DAT ||
	         cep->snd_nblk_tfn == TFN_TCP_SND_OOB) {	/* �Υ�֥�å��󥰥����� */

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

	else if (cep->snd_nblk_tfn == TFN_TCP_SND_DAT) {	/* �Υ�֥�å��󥰥����� */

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		ER_UINT	error;

	 	/* ����������ɥХåե��˥ǡ�����񤭹��ࡣ*/
		error = TCP_WRITE_SWBUF(cep, cep->snd_data, (uint_t)cep->snd_len);

#ifdef TCP_CFG_EXTENTIONS

		/* �����۵ޥݥ��󥿤����ꤹ�롣*/
	        if (cep->snd_nblk_tfn == TFN_TCP_SND_OOB)
			cep->snd_up = cep->snd_una + error;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->snd_tskid = TA_NULL;
		cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ����������ɥХåե��˶��������褿����ϥ������򵯾����롣*/
		if (last == cep->sbufsz && cep->swbuf_count < cep->sbufsz)
			syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	if (cep->swbuf_count > 0) {
		/* ����������ɥХåե��˥ǡ���������н��Ϥ�ݥ��Ȥ��롣*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_write_swbuf -- ����������ɥХåե��˥ǡ�����񤭹��ࡣ
 */

ER_UINT
tcp_write_swbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len)
{
	uint_t	offset;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* len ������������ɥХåե��ζ����ξ���������ܤ��ǡ������ˤ��롣*/
	if (len > (cep->sbufsz - cep->swbuf_count))
		len = cep->sbufsz - cep->swbuf_count;

	/* �񤭹��ߥݥ��󥿤��饦��ɤ���Ȥ��ν��� */
	if (len > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf)) {
		offset = (uint_t)(cep->sbufsz - (cep->sbuf_wptr -(uint8_t*)cep->sbuf));
		memcpy(cep->sbuf_wptr, data, (size_t)offset);
		cep->sbuf_wptr  = (uint8_t*)cep->sbuf;
		cep->swbuf_count += offset;
		}
	else
		offset = 0;

	memcpy(cep->sbuf_wptr, (void*)((uint8_t*)data + offset), (size_t)(len - offset));
	cep->sbuf_wptr  += len - offset;
	cep->swbuf_count += len - offset;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return (ER_UINT)len;
	}

/*
 *  tcp_wait_swbuf -- ����������ɥХåե��������Τ��Ԥġ�
 */

ER
tcp_wait_swbuf_ncs (T_TCP_CEP *cep, TMO tmout)
{
	ER	error;
	FLGPTN	flag;

	while (cep->swbuf_count >= cep->sbufsz) {
		/*
		 *  ����������ɥХåե��ζ������ʤ���С����Ϥ�ݥ��Ȥ��ơ�
		 *  ����������ɥХåե��������ޤ��Ԥġ�
		 */
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY, TWF_ORW, &flag, tmout)) != E_OK) {
			return error;
			}
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/*
		 *  �����Ǥ��뤫��CEP �� FSM ���֤򸫤롣
		 *  ����������ɥХåե��������ޤ��ԤĴ֤ˡ�������ǽ�ˤʤä����ϡ�
		 *  ���ͥ���������Ǥ��줿���Ȥ��̣���Ƥ��롣
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state)) {
			return E_CLS;
			}
		}

	return E_OK;
	}
/*
 *  tcp_get_swbuf_addr -- ����������ɥХåե��ζ������ɥ쥹��������롣
 */

ER_UINT
tcp_get_swbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf)
{
	uint_t	len;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* ����������ɥХåե��ζ������ɥ쥹����Ƭ�����ꤹ�롣*/
	*p_buf = cep->sbuf_wptr;

	/* ����������ɥХåե��ζ�����������׻����롣*/
	if (cep->sbufsz - cep->swbuf_count > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf))
		/* ����ߥݥ��󥿤��饦��ɤ���Ȥ��ϡ�����ߥݥ��󥿤�������������ɥХåե��ν����ޤ� */
		len = (uint_t)(cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf));
	else
		len = cep->sbufsz - cep->swbuf_count;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* ����������ɥХåե��ζ����ǡ���Ĺ�����ꤷ�������ͤ��֤���*/
	cep->get_buf_len = len;
	return (ER_UINT)len;
	}

/*
 *  tcp_send_swbuf -- ����������ɥХåե��Υǡ�����������ǽ�ˤ��롣
 */

void
tcp_send_swbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	cep->sbuf_wptr  += len;
	cep->swbuf_count += len;

	/* ����ߥݥ��󥿤��饦��ɤ���Ȥ��ν��� */
	if (cep->sbuf_wptr >= (uint8_t*)cep->sbuf + cep->sbufsz)
		cep->sbuf_wptr  = (uint8_t*)cep->sbuf;

	/* tcp_get_buf �γ�����Ĺ��ꥻ�åȤ��롣*/
	cep->get_buf_len = 0;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* ����������ɥХåե����ե�ΤȤ��϶���Ū���������롣*/
	if (cep->swbuf_count >= cep->sbufsz)
		cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;
	}

/*
 *  tcp_is_swbuf_full -- ����������ɥХåե������դ������å����롣
 */

bool_t
tcp_is_swbuf_full_ncs (T_TCP_CEP *cep)
{
	return cep->swbuf_count >= cep->sbufsz;
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE_ONLY */

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��̵��
 */

/*
 *  tcp_drop_rwbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ������롣
 */

void
tcp_drop_rwbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	cep->rwbuf_count -= len;
	cep->rbuf_rptr  += len;

	/* �ɤ߽Ф��ݥ��󥿤��饦��ɤ���Ȥ��ν��� */
	if (cep->rbuf_rptr >= (uint8_t*)cep->rbuf + cep->rbufsz)
		cep->rbuf_rptr  = (uint8_t*)cep->rbuf;
	}

/*
 *  tcp_read_rwbuf -- ����������ɥХåե�������ꤵ�줿�����ƥå�ʬ�ɤ߽Ф���
 */

uint_t
tcp_read_rwbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len)
{
	uint_t	offset;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* len �ȼ���������ɥХåե��Υǡ������ξ�����������Ф��ǡ������ˤ��롣*/
	if (len > cep->rwbuf_count)
		len = cep->rwbuf_count;

	/* �ɤ߽Ф��ݥ��󥿤��饦��ɤ���Ȥ��ν��� */
	if (len > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf)) {
		offset = (uint_t)(cep->rbufsz - (cep->rbuf_rptr -(uint8_t*)cep->rbuf));
		memcpy(data, cep->rbuf_rptr, (size_t)offset);
		cep->rwbuf_count -= offset;
		cep->rbuf_rptr   = (uint8_t*)cep->rbuf;
		}
	else
		offset = 0;

	memcpy((void*)((uint8_t*)data + offset), cep->rbuf_rptr, (size_t)(len - offset));
	cep->rwbuf_count -= len - offset;
	cep->rbuf_rptr  += len - offset;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return len;
	}

/*
 *  tcp_get_rwbuf_addr -- ����������ɥХåե��ζ������ɥ쥹��������롣
 */

uint_t
tcp_get_rwbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf)
{
	uint_t	len;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/* ����������ɥХåե��Υǡ���Ĺ��׻����롣*/
	if (cep->rwbuf_count > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf))
		/* �ݥ��󥿤��饦��ɤ���Ȥ��ϼ���������ɥХåե��ν����ޤ� */
		len = (uint_t)(cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf));
	else
		len = cep->rwbuf_count;

	/* ����������ɥХåե��Υǡ����Υ��ɥ쥹����Ƭ�����ꤹ�롣*/
	*p_buf = cep->rbuf_rptr;

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	/* ����������ɥХåե��Υǡ���Ĺ�����ꤷ�������ͤ��֤���*/
	cep->rcv_buf_len = len;
	return len;
	}

/*
 *  tcp_write_rwbuf -- ����������ɥХåե��˥ǡ�����񤭹��ࡣ
 *
 *    ���:
 *	���� input �ϡ�T_TCP_Q_HDR �ˤ���󥯤��졢
 *	�¤��ؤ�����λ���Ƥ��ʤ���Фʤ�ʤ����ޤ���
 *	�ɲä���ǡ����ϡ�����������ɥХåե��˼��ޤ뤳�ȡ�
 */

void
tcp_write_rwbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		offset, inlen, last;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	/* �����Ѥߥ��������ֹ�򹹿����롣*/
	cep->rcv_nxt += qhdr->slen;

	last  = cep->rwbuf_count;
	inlen = qhdr->slen;

	/* �۵ޥǡ����� SDU ������Ԥ���*/
	if (qhdr->urp > 0 && inlen > 0) {
		inlen      -= qhdr->urp;
		qhdr->slen -= qhdr->urp;
		qhdr->urp   = 0;
		}

	/*
	 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
	 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
	 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
	 */
	if (inlen > 0) {

		/* �񤭹��ߥݥ��󥿤��饦��ɤ���Ȥ��ν��� */
		if (inlen > cep->rbufsz - (cep->rbuf_wptr - (uint8_t*)cep->rbuf)) {
			offset = (uint_t)(cep->rbufsz - (cep->rbuf_wptr - (uint8_t*)cep->rbuf));
			memcpy(cep->rbuf_wptr, (void*)(GET_TCP_SDU(input, thoff) + qhdr->soff), (size_t)offset);
			cep->rbuf_wptr   = (uint8_t*)cep->rbuf;
			cep->rwbuf_count += offset;
			inlen           -= offset;
			}
		else
			offset	= 0;

		memcpy(cep->rbuf_wptr, (void*)(GET_TCP_SDU(input, thoff) + qhdr->soff + offset), (size_t)inlen);
		cep->rbuf_wptr  += inlen;
		cep->rwbuf_count += inlen;

		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_SEGS],   1);
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_OCTETS], inlen);
		}

	syscall(rel_net_buf(input));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->rcv_nblk_tfn == TFN_TCP_RCV_BUF) {	/* �Υ�֥�å��󥰥����� */

		int_t	len;

		/* ����������ɥХåե��ζ����ǡ���Ĺ��׻����롣*/
		if (cep->rwbuf_count > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf)) {
			/* �ݥ��󥿤��饦��ɤ���Ȥ��ϼ���������ɥХåե��ν����ޤ� */
			len = (uint_t)(cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf));
			}
		else
			len = cep->rwbuf_count;

		/* �̿�ü���Υ�å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		/*
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if (len > 0 || inlen == 0) {

			/* tcp_rcv_buf �γ�����Ĺ�����ꤹ�롣*/
			cep->rcv_buf_len = len;

			/* ����������ɥХåե��Υ��ɥ쥹���֤���*/
			*cep->rcv_p_buf = cep->rbuf_rptr;


			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			if (len == 0) {

				/*
				 *  �̿�ü�����å����ơ�
				 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
				 */
				syscall(wai_sem(cep->semid_lock));
				TCP_FREE_RWBUFQ(cep);
				syscall(sig_sem(cep->semid_lock));
				}
			}

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}

	else if (cep->rcv_nblk_tfn == TFN_TCP_RCV_DAT) {	/* �Υ�֥�å��󥰥����� */
		ER_UINT	len;

		/* �̿�ü���Υ�å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		/* ����������ɥХåե�����ǡ�������Ф���*/
		if ((len = TCP_READ_RWBUF(cep, cep->rcv_data, (uint_t)cep->rcv_len)) > 0) {
			/* ���˥�����ɥ����������Ѥ�ä����Ȥ��Τ餻�뤿����Ϥ�ݥ��Ȥ��롣*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

		/*
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if (len > 0 || inlen == 0) {

			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
			}

		/* ��������Ƥ��륿���� ID �� API ��ǽ�����ɤ򥯥ꥢ�����롣*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;

		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* �̿�ü���Υ�å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		if (inlen == 0 && cep->rwbuf_count == 0) {
			/*
			 *  ����������ɥХåե���Υǡ������� 0 �ǡ�
			 *  ��꤫�� FIN �ե饰���դ����������Ȥ���������Ȥ��ϡ�
			 *  �̿�ü�����å����ơ�
			 *  ����������ɥХåե����塼�Υͥåȥ���Хåե���������롣
			 */
			syscall(wai_sem(cep->semid_lock));
			TCP_FREE_RWBUFQ(cep);
			syscall(sig_sem(cep->semid_lock));
			}

		/*
		 *  ����������ɥХåե��˥ǡ��������뤫�� inlen == 0 �λ������ϥ������򵯾����롣
		 *  FIN �ե饰���դ����������Ȥ� inlen == 0 �ˤʤ뤳�Ȥ⤢�롣
		 *  ����ϡ����ץꥱ�������ˡ���꤫�餳��ʾ�ǡ�����������
		 *  ���ʤ����Ȥ��Τ餻�뤿��Ǥ��롣
		 */
		if ((last == 0 && cep->rwbuf_count > 0) || inlen == 0)
			syscall(set_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE_ONLY */

#endif	/* of #ifdef SUPPORT_TCP */
