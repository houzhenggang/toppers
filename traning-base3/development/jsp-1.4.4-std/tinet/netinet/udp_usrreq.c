/*
 *  TINET (UDP/IP Protocol Stack)
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
 *  @(#) $Id: udp_usrreq.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
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
 * 2. Redistributions in binary form must ceproduce the above copyright
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
 *	@(#)udp_usrreq.c	8.6 (Berkeley) 5/23/95
 * $FreeBSD: src/sys/netinet/udp_usrreq.c,v 1.49.2.2 1999/08/29 16:29:58 peter Exp $
 */

/*
 *  �Υ�֥�å��󥰥�������ȹ��ޤʤ����˥�󥯤����ؿ������
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp_ipcp.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/icmp6.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#ifdef SUPPORT_UDP

/*
 *  IPv4 �� IPv6 ���ڤ��ؤ��ޥ���
 */

#if defined(SUPPORT_INET4)

#define UDP_CRE_CEP	udp_cre_cep
#define UDP_SND_DAT	udp_snd_dat
#define UDP_RCV_DAT	udp_rcv_dat

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define UDP_CRE_CEP	udp6_cre_cep
#define UDP_SND_DAT	udp6_snd_dat
#define UDP_RCV_DAT	udp6_rcv_dat

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  TINET ��饤�֥�경���ʤ����ϡ����Ƥε�ǽ��
 *  ���֥������ȥե�����˽��Ϥ��뤿�ᡢ�ޥ����ͭ���ˤ��롣
 */

#ifndef UDP_CFG_LIBRARY

#define __udp_send_data
#define __udp_cre_cep
#define __udp_del_cep
#define __udp_can_cep
#define __udp_set_opt
#define __udp_get_opt
#define __udp_can_snd
#define __udp_can_rcv
#define __udp_snd_dat
#define __udp_rcv_dat

#endif	/* of #ifndef UDP_CFG_LIBRARY */

#ifdef __udp_send_data

/*
 *  udp_send_data -- �ѥ��å������μ�����
 */

ER_UINT
udp_send_data (T_UDP_CEP *cep, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_NET_BUF	*output;
	T_UDP_HDR	*udph;
	SYSTIM		before, after;
	ER		error = E_OK;

#ifdef UDP_CFG_OUT_CHECKSUM
	uint16_t	sum;
#endif	/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	NET_COUNT_UDP(net_count_udp.out_octets,  len);
	NET_COUNT_UDP(net_count_udp.out_packets, 1);

	/* IP �ǡ�������������Ƥλ��֤� tmout ���鸺���롣*/
	if (!(tmout == TMO_POL || tmout == TMO_FEVR))
		syscall(get_tim(&before));

	/* IP �ǡ��������������Ƥ롣*/
	if ((error = IN_GET_DATAGRAM(&output, (uint_t)(UDP_HDR_SIZE + len), 0,
	                             &p_dstaddr->ipaddr,
	                             &cep->myaddr.ipaddr,
	                             IPPROTO_UDP, IP_DEFTTL, 
	                             NBA_SEARCH_ASCENT, tmout)) != E_OK)
		goto err_ret;

	/* IP �ǡ�������������Ƥλ��֤� tmout ���鸺���롣*/
	if (!(tmout == TMO_POL || tmout == TMO_FEVR)) {
		syscall(get_tim(&after));
		if (after - before > tmout) {
			syscall(rel_net_buf(output));
			error = E_TMOUT;
			goto err_ret;
			}
		tmout -= (TMO)(after - before);
		}

	/* UDP �إå��˾�������ꤹ�롣*/
	udph		= GET_UDP_HDR(output, IF_IP_UDP_HDR_OFFSET);
	udph->sport	= htons(cep->myaddr.portno);
	udph->dport	= htons(p_dstaddr->portno);
	udph->ulen	= htons(UDP_HDR_SIZE + len);
	udph->sum	= 0;

	/* �ǡ����򥳥ԡ����롣*/
	memcpy((void*)GET_UDP_SDU(output, IF_IP_UDP_HDR_OFFSET), data, (size_t)len);

#ifdef UDP_CFG_OUT_CHECKSUM

	sum = IN_CKSUM(output, IPPROTO_UDP, IF_IP_UDP_HDR_OFFSET, (uint_t)(UDP_HDR_SIZE + len));

	/* �׻����������å�������ͤ� 0 �ʤ� 0xffff ������롣*/
	if (sum == 0)
		sum = 0xffff;
	udph->sum = sum;

#endif	/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* �ͥåȥ���Хåե�Ĺ��Ĵ�����롣*/
	output->len = (uint16_t)(IF_IP_UDP_HDR_SIZE + len);

	/* �ͥåȥ���� (IP) �ν��ϴؿ���ƤӽФ���*/
	if ((error = IP_OUTPUT(output, tmout)) == E_OK) {
		NET_COUNT_MIB(udp_stats.udpOutDatagrams, 1);
		cep->snd_tskid = TA_NULL;
		return len;
		}

err_ret:
	NET_COUNT_UDP(net_count_udp.out_err_packets, 1);
	cep->snd_tskid = TA_NULL;
	return error;
	}

#endif	/* of #ifdef __udp_send_data */

/*
 *  udp_cre_cep -- UDP �̿�ü���������ڳ�ĥ��ǽ��
 */

#ifdef __udp_cre_cep

#ifdef UDP_CFG_EXTENTIONS

ER
UDP_CRE_CEP (ID cepid, T_UDP_CCEP *pk_ccep)
{
	T_UDP_CEP	*cep;
	ER		error;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* pk_ccep �� NULL �ʤ饨�顼 */
	if (pk_ccep == NULL)
		return E_PAR;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (VALID_UDP_CEP(cep))
		return E_OBJ;

	/* UDP �̿�ü������ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_UDP_CEP(cep))
		return E_ID;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * UDP �̿�ü��������å����롣�����ѤߤǤ���Х��顼
	 */
	if (VALID_UDP_CEP(cep))
		error = E_OBJ;
	else {

		/*
		 *  ���ݡ����ֹ椬 UDP_PORTANY �ʤ顢��ư�ǳ�����Ƥ롣
		 */
		if (pk_ccep->myaddr.portno == UDP_PORTANY)
			error = udp_alloc_auto_port(cep);
		else 
			error = udp_alloc_port(cep, pk_ccep->myaddr.portno);
		
                if (error == E_OK) {

			/* UDP �̿�ü����������򥳥ԡ����롣*/
			cep->cepatr        = pk_ccep->cepatr;			/* �̿�ü��°��		*/
			cep->myaddr.ipaddr = pk_ccep->myaddr.ipaddr;		/* ��ʬ�Υ��ɥ쥹	*/
			cep->callback      = (void*)pk_ccep->callback;		/* ������Хå�		*/

			/* UDP �̿�ü���������Ѥߤˤ��롣*/
			cep->flags |= UDP_CEP_FLG_VALID;
			}
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

#endif	/* of #ifdef __udp_cre_cep */

/*
 *  udp_del_cep -- UDP �̿�ü���κ���ڳ�ĥ��ǽ��
 */

#ifdef __udp_del_cep

#ifdef UDP_CFG_EXTENTIONS

ER
udp_del_cep (ID cepid)
{
	T_UDP_CEP	*cep;
	ER		error;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/* UDP �̿�ü������ưŪ�����ѤǤʤ���Х��顼 */
	if (!DYNAMIC_UDP_CEP(cep))
		return E_ID;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * UDP �̿�ü��������å����롣̤�����ξ��ϥ��顼
	 * ��̤������
	 */
	if (!VALID_UDP_CEP(cep))
		error = E_NOEXS;
	else {
		udp_can_snd(cep, E_DLT);
		udp_can_rcv(cep, E_DLT);

		/* UDP �̿�ü����̤�����ˤ��롣*/
		cep->flags &= ~UDP_CEP_FLG_VALID;
		error = E_OK;
		}

	/* �̿�ü���Υ�å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

#endif	/* of #ifdef __udp_del_cep */

#ifdef __udp_can_cep

/*
 *  udp_can_cep -- �ڥ�ǥ��󥰤��Ƥ�������Υ���󥻥��ɸ�ൡǽ��
 */

ER
udp_can_cep (ID cepid, FN fncd)
{
	T_UDP_CEP	*cep;
	ER		error = E_OK, snd_err, rcv_err;

	/* API ��ǽ�����ɤ�����å����롣*/
	if (!VALID_TFN_UDP_CAN(fncd))
		return E_PAR;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if (fncd == TFN_UDP_ALL) {	/* TFN_UDP_ALL �ν��� */

		snd_err = udp_can_snd(cep, E_RLWAI);
		rcv_err = udp_can_rcv(cep, E_RLWAI);

		/*
		 *  snd_err �� rcv_err �Τɤ���� EV_NOPND
		 *  �ʤ顢�ڥ�ǥ��󥰤��Ƥ��ʤ��Τǥ��顼
		 */
		if (snd_err == EV_NOPND && rcv_err == EV_NOPND)
			error = E_OBJ;
		else {
			if (snd_err == EV_NOPND)
				snd_err = E_OK;
			if (rcv_err == EV_NOPND)
				rcv_err = E_OK;

			if (snd_err != E_OK)
				error = snd_err;
			else if (rcv_err != E_OK)
				error = rcv_err;
			}
		}
	else if (fncd == TFN_UDP_SND_DAT) {	/* ���������Υ���󥻥� */
		if ((error = udp_can_snd(cep, E_RLWAI)) == EV_NOPND)
			error = E_OBJ;
		}
	else if (fncd == TFN_UDP_RCV_DAT) {	/* ���������Υ���󥻥� */
		if ((error = udp_can_rcv(cep, E_RLWAI)) == EV_NOPND)
			error = E_OBJ;
		}
	else
		error = E_PAR;

	/* �̿�ü�����å��������롣*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef __udp_can_cep */

/*
 *  udp_set_opt -- UDP �̿�ü�����ץ���������ڳ�ĥ��ǽ��
 *
 *  ���: �����ǽ�� UDP �̿�ü�����ץ�����̵�����ᡢE_PAR ���֤���롣
 */

#ifdef __udp_set_opt

#ifdef UDP_CFG_EXTENTIONS

ER
udp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_UDP_CEP	*cep;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

#endif	/* of #ifdef __udp_set_opt */

/*
 *  udp_get_opt -- UDP �̿�ü�����ץ���������ڳ�ĥ��ǽ��
 *
 *  ���: �����ǽ�� UDP �̿�ü�����ץ�����̵�����ᡢE_PAR ���֤���롣
 */

#ifdef __udp_get_opt

#ifdef UDP_CFG_EXTENTIONS

ER
udp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_UDP_CEP	*cep;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

#endif	/* of #ifdef __udp_get_opt */

#ifdef UDP_CFG_NON_BLOCKING

#include "udp_usrreq_nblk.c"

#else	/* of #ifdef UDP_CFG_NON_BLOCKING */

#ifdef __udp_can_snd

/*
 *  udp_can_snd -- �ڥ�ǥ��󥰤��Ƥ��������Υ���󥻥�
 */

ER
udp_can_snd (T_UDP_CEP *cep, ER error)
{
	if (cep->snd_tskid != TA_NULL) {	/* ��Υ�֥�å��󥰥�����ǥڥ�ǥ����� */

#ifdef UDP_CFG_EXTENTIONS

		/* �Ԥ����ȯ���������顼��������ꤹ�롣*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->snd_tskid);
		cep->snd_tskid = TA_NULL;
		}
	else					/* �ɤ���Ǥ�ʤ��ʤ�ڥ�ǥ��󥰤��Ƥ��ʤ� */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_snd */

#ifdef __udp_can_rcv

/*
 *  udp_can_rcv -- �ڥ�ǥ��󥰤��Ƥ�������Υ���󥻥�
 */

ER
udp_can_rcv (T_UDP_CEP *cep, ER error)
{
	if (cep->rcv_tskid != TA_NULL) {	/* ��Υ�֥�å��󥰥�����ǥڥ�ǥ����� */

#ifdef UDP_CFG_EXTENTIONS

		/* �Ԥ����ȯ���������顼��������ꤹ�롣*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->rcv_tskid);
		cep->rcv_tskid = TA_NULL;
		}
	else					/* �ɤ���Ǥ�ʤ��ʤ�ڥ�ǥ��󥰤��Ƥ��ʤ� */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_rcv */

#ifdef __udp_snd_dat

/*
 *  udp_snd_dat -- �ѥ��åȤ�������ɸ�ൡǽ��
 */

ER_UINT
UDP_SND_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_UDP_CEP	*cep;
	ER		error;

	/* p_dstaddr �ޤ��� data �� NULL ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (p_dstaddr == NULL || data == NULL || tmout == TMO_NBLK)
		return E_PAR;

	/* �ǡ���Ĺ������å����롣*/
	if (len < 0 || len + IP_HDR_SIZE + UDP_HDR_SIZE > IF_MTU)
		return E_PAR;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/*
	 *  ���ݡ����ֹ椬 UDP_PORTANY �ʤ顢��ư�ǳ�����Ƥ롣
	 */
	if (cep->myaddr.portno == UDP_PORTANY) {
		if ((error = udp_alloc_auto_port(cep)) != E_OK)
			return error;
		}
	
	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if (cep->snd_tskid != TA_NULL) {

		/* ��Υ�֥�å��󥰥�����ǥڥ�ǥ����� */
		error = E_QOVR;

		/* �̿�ü�����å��������롣*/
		syscall(sig_sem(cep->semid_lock));
		}
	else {
		/* ���ߤΥ��������̻Ҥ�Ͽ���롣*/
		get_tid(&(cep->snd_tskid));

#ifdef UDP_CFG_EXTENTIONS

		/* �Ԥ����ȯ���������顼�����ꥻ�åȤ��롣*/
		cep->error = E_OK;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		/* �̿�ü�����å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		/* �ѥ��åȤ��������롣*/
		error = udp_send_data(cep, p_dstaddr, data, len, tmout);

#ifdef UDP_CFG_EXTENTIONS

		/* �Ԥ����ȯ���������顼������֤���*/
		if (error == E_RLWAI)
			error = cep->error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */
		}

	return error;
	}

#endif	/* of #ifdef __udp_snd_dat */

#ifdef __udp_rcv_dat

/*
 *  udp_rcv_dat -- �ѥ��åȤμ�����ɸ�ൡǽ��
 */

ER_UINT
UDP_RCV_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_NET_BUF	*input;
	T_UDP_CEP	*cep;
	T_UDP_HDR	*udph;
	ER_UINT		error;
	uint_t		ulen, uhoff;

	/* p_dstaddr �ޤ��� data �� NULL ��len < 0 ����tmout �� TMO_NBLK �ʤ饨�顼 */
	if (p_dstaddr == NULL || data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

	/* UDP �̿�ü�� ID ������å����롣*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �̿�ü�������롣*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �̿�ü��������å����롣*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/* �̿�ü�����å����롣*/
	syscall(wai_sem(cep->semid_lock));

	if (cep->rcv_tskid != TA_NULL) {

		/* ��Υ�֥�å��󥰥�����ǥڥ�ǥ����� */
		error = E_QOVR;

		/* �̿�ü�����å��������롣*/
		syscall(sig_sem(cep->semid_lock));
		}
	else {

		/* ���ߤΥ��������̻Ҥ�Ͽ���롣*/
		get_tid(&(cep->rcv_tskid));

#ifdef UDP_CFG_EXTENTIONS

		/* �Ԥ����ȯ���������顼�����ꥻ�åȤ��롣*/
		cep->error = E_OK;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		/* �̿�ü�����å��������롣*/
		syscall(sig_sem(cep->semid_lock));

		/* ���Ϥ�����ޤ��Ԥġ�*/
		if (cep->cb_netbuf != NULL) {

			/*
			 *  �����ˤ�����ϡ�������Хå��ؿ����椫��
			 *  udp_rcv_dat ��ƤӽФ��Ƥ��뤳�Ȥˤʤꡢ
			 *  ���Ǥ����ϺѤߤǤ��롣
			 */
			input = cep->cb_netbuf;
			cep->cb_netbuf = NULL;
			}
		else if ((error = trcv_dtq(cep->rcvqid, (intptr_t*)&input, tmout)) != E_OK) {

#ifdef UDP_CFG_EXTENTIONS

			/* �Ԥ����ȯ���������顼������֤���*/
			if (error == E_RLWAI)
				error = cep->error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

			cep->rcv_tskid = TA_NULL;
			return error;
			}

		/* p_dstaddr �����ꤹ�롣*/
		uhoff = (uint_t)GET_UDP_HDR_OFFSET(input);
		udph = GET_UDP_HDR(input, uhoff);
		p_dstaddr->portno = ntohs(udph->sport);
		IN_COPY_TO_HOST(&p_dstaddr->ipaddr, &GET_IP_HDR(input)->src);

		/* �ǡ�����Хåե��˰ܤ���*/
		ulen = ntohs(udph->ulen);
		if (ulen - UDP_HDR_SIZE > len)
			error = E_BOVR;
		else {
			len   =    (uint_t)(ulen - UDP_HDR_SIZE);
			error = (ER_UINT)(ulen - UDP_HDR_SIZE);
			}

		memcpy(data, GET_UDP_SDU(input, uhoff), (size_t)len);

		syscall(rel_net_buf(input));

		cep->rcv_tskid = TA_NULL;
		}

	return error;
	}

#endif	/* of #ifdef __udp_rcv_dat */

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
