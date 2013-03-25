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
 *  @(#) $Id: udp_echo_srv.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  UDP ECHO ������
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_UDP_ECHO_SRV

/*
 *  ���������ॢ����
 */

#define RCV_TMOUT	TMO_FEVR
//#define RCV_TMOUT	(30*ULONG_C(1000))

#define BUF_SIZE	2048

static char	echo_rcv_buf[BUF_SIZE];
static T_IPEP	dst;

#ifdef USE_UDP_CALL_BACK

/*
 *  ������Хå��ؿ�
 */

ER
callback_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_FEVR)) >= 0) {
		echo_rcv_buf[len] = '\0';
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d UCB] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, len);
			else
				syslog(LOG_NOTICE, "[UES:%02d UCB] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		len = E_OK;
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] recv error, %6ld: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len;
	}

#else	/* of #ifdef USE_UDP_CALL_BACK */

#ifdef USE_UDP_NON_BLOCKING

/*
 *  �ѿ�
 */

static ER_UINT		nblk_len;

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	SYSTIM	now;

	get_tim(&now);
	nblk_len = *(ER_UINT*)p_parblk;
	if (nblk_len < 0) {	/* 0 �ʲ��ξ��ϡ����顼������ */
		syslog(LOG_NOTICE, "[UES:%02d CBR] error,      %6ld: %s, fncd: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(nblk_len), in_strtfn(fncd));
		}
	else if (fncd == TFN_UDP_RCV_DAT) {
		echo_rcv_buf[nblk_len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d CBR] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		}
	syscall(wup_tsk(UDP_ECHO_SRV_TASK));
	return E_OK;
	}

/*
 *  UDP ECHO ������
 */

ER
udp_echo_srv (ID cepid)
{
	ER	error;
	SYSTIM	now;

	if ((error = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_NBLK)) != E_WBLK) {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(error));
		return error;
		}

	syscall(slp_tsk());
	if (nblk_len < 0)
		error = nblk_len;
	else {
		if ((error = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, nblk_len, TMO_NBLK)) != E_WBLK) {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
			                   cepid, now / SYSTIM_HZ, itron_strerror(error));
			return error;
			}

		syscall(slp_tsk());
		if (nblk_len < 0)
			error = nblk_len;
		else {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d", cepid, now / SYSTIM_HZ, nblk_len);
			error = E_OK;
			}
		}

	return error;
	}

#else	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO ������
 */

ER
udp_echo_srv (ID cepid)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), RCV_TMOUT)) >= 0) {
		get_tim(&now);
		echo_rcv_buf[len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d RCV] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, (uint16_t)len);
			else
				syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len >= 0 || len == E_TMOUT ? E_OK : len;
	}

#endif	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO �����Х�����
 */

#ifdef USE_UDP_EXTENTIONS

void
udp_echo_srv_task (intptr_t exinf)
{
	ID		tskid, cepid;
	ER		error;
	T_UDP_CCEP	ccep;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {

		syscall(slp_tsk());

		ccep.cepatr = UINT_C(0);
		ccep.myaddr.portno = UINT_C(7);

#if defined(SUPPORT_INET4)
		ccep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
		memcpy(&ccep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

#ifdef USE_UDP_NON_BLOCKING
		ccep.callback = (FP)callback_nblk_udp_echo_srv;
#else
		ccep.callback = NULL;
#endif

		if ((error = alloc_udp_cep(&cepid, tskid, &ccep)) != E_OK) {
			syslog(LOG_NOTICE, "[UES:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
			continue;
			}

		while (error == E_OK) {
			if ((error = udp_echo_srv(cepid)) != E_OK) {
				if ((error = free_udp_cep(cepid, !(error == E_NOEXS || error == E_DLT))) != E_OK)
					syslog(LOG_NOTICE, "[UEC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));
				break;
				}
			}

		}
	slp_tsk();
	}

#else	/* of #ifdef USE_UDP_EXTENTIONS */

void
udp_echo_srv_task (intptr_t exinf)
{
	ID	tskid;
	ER	error = E_OK;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (error == E_OK) {
		error = udp_echo_srv((ID)exinf);
		}
	slp_tsk();
	}

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

#endif	/* of #ifdef USE_UDP_CALL_BACK */

#endif	/* of #ifdef USE_UDP_ECHO_SRV */
