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
 *  @(#) $Id: udp_discard_cli.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  UDP DISCARD ���饤�����
 */

#include <stdlib.h>
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

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/discard.h>

#ifdef USE_UDP_DISCARD_CLI

/* discard �����ФΥݡ����ֹ� */

#define DISCARD_SRV_PORTNO	UINT_C(9)

/*
 * �ѿ�
 */

#define PAT_BEGIN	' '
#define PAT_END		'~'

/*
 *  �����ѿ�
 */

bool_t udp_discard_cli_valid;

/*
 *  send_udp_discard -- DISCARD/UDP �����Ф˥�å��������������롣
 */

static ER
send_udp_discard (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno)
{
	static char smsg[IF_MTU - IP_UDP_HDR_SIZE];

	T_IPEP		dst;
	ER_UINT		len;
	SYSTIM		time;
	char		*p;
	uint32_t	total;
	uint16_t	pat, slen, scount;

	dst.ipaddr = *ipaddr;
	dst.portno = portno;

	p = smsg;
	for (slen = IF_MTU - IP_UDP_HDR_SIZE; slen > 0; )
		for (pat = PAT_BEGIN; slen > 0 && pat <= PAT_END; pat ++, slen --)
			*p ++ = pat;

	get_tim(&time);
	syslog(LOG_NOTICE, "[UDC:%02d SND] sending:    %6ld, to:   %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);

	scount = total = 0;
	udp_discard_cli_valid = true;
	for (slen = IF_MTU - IP_UDP_HDR_SIZE; udp_discard_cli_valid && slen > 0; slen --) {
		scount ++;
		if ((len = UDP_SND_DAT(cepid, &dst, smsg, slen, TMO_FEVR)) < 0) {
			syslog(LOG_NOTICE, "[UDC:%02d SND] send error: %s", cepid, itron_strerror(len));
			return len;
			}
		else
			syslog(LOG_NOTICE, "[UDC:%02d SND] send: %4d, %4d", cepid, scount, slen);
		total += len;
		dly_tsk(10 * SYSTIM_HZ + net_rand() % (10 * SYSTIM_HZ));
		}

	get_tim(&time);
	syslog(LOG_NOTICE, "[UDC:%02d SND] finished:   %6ld, snd: %4d,            len: %ld",
		           cepid, time / SYSTIM_HZ, scount, total);
	return E_OK;
	}

/*
 *  UDP DISCARD ���饤���������������
 */

void
udp_discard_cli_task (intptr_t exinf)
{
	T_IN_ADDR	addr;
	ID		tskid, cepid;
	ER		error;
	char		*line;
	int_t		no;
	uint16_t	portno;

#ifdef USE_UDP_EXTENTIONS

	T_UDP_CCEP	ccep;

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP DISCARD CLI:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		if (rcv_dtq(DTQ_UDP_DISCARD_CLI, (intptr_t*)&line) == E_OK) {
			line = skip_blanks(GET_IPADDR(&addr, skip_blanks(line)));	/* IP Address */

			if ('0' <= *line && *line <= '9') {				/* Port No */
				line = get_int(&no, line);
				portno = (uint16_t)no;
				}
			else {
				line ++;
				portno = DISCARD_SRV_PORTNO;
				}

#ifdef USE_UDP_EXTENTIONS

			ccep.cepatr = UINT_C(0);
			ccep.callback = NULL;
			ccep.myaddr.portno = UDP_PORTANY;

#if defined(SUPPORT_INET4)
			ccep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
			memcpy(&ccep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

			if ((error = alloc_udp_cep(&cepid, tskid, &ccep)) != E_OK) {
				syslog(LOG_NOTICE, "[UDC:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
				continue;
				}

#else	/* of #ifdef USE_UDP_EXTENTIONS */

			cepid = (ID)exinf;

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

			if ((error = send_udp_discard(cepid, &addr, portno)) != E_OK)
				syslog(LOG_NOTICE, "[UDC:%02d TSK] error: %s", cepid, itron_strerror(error));

#ifdef USE_UDP_EXTENTIONS

			if ((error = free_udp_cep(cepid, !(error == E_NOEXS || error == E_DLT))) != E_OK)
				syslog(LOG_NOTICE, "[UDC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

			}
		}
	}

#endif	/* of #ifdef USE_UDP_DISCARD_CLI */
