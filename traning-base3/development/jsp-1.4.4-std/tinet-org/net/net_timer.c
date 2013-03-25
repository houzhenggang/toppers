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
 *  @(#) $Id: net_timer.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
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
 */

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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp_timer.h>

/*
 *  �ѿ�
 */

static T_NET_CALLOUT callout[NUM_NET_CALLOUT];

/*
 *  �ƽФ�����ȥ���Ͽ
 */

void
timeout (callout_func func, void *arg, RELTIM timeout)
{
	int_t ix;

	/* �ƽФ�����ȥ��������� */
	syscall(wai_sem(SEM_CALL_OUT_LOCK));
	for (ix = NUM_NET_CALLOUT; callout[-- ix].func != NULL; )
		if (ix == 0) {
			syslog(LOG_WARNING, "[NET] callout busy, size=%d.", NUM_NET_CALLOUT);
			syscall(sig_sem(SEM_CALL_OUT_LOCK));
			return;
			}

	/* �ƽФ�����ȥ�����ꤹ�� */
	callout[ix].func	= func;
	callout[ix].arg		= arg;
	callout[ix].timeout	= timeout;
	syscall(sig_sem(SEM_CALL_OUT_LOCK));
	}

/*
 *  �ƽФ�����ȥ���
 */

void
untimeout (callout_func func, void *arg)
{
	int_t ix;

	/* ����ȥ��õ�� */
	for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
		syscall(wai_sem(SEM_CALL_OUT_LOCK));
		if (callout[ix].func == func && callout[ix].arg == arg && callout[ix].timeout > 0) {
			callout[ix].func = NULL;
			syscall(sig_sem(SEM_CALL_OUT_LOCK));
			break;
			}
		syscall(sig_sem(SEM_CALL_OUT_LOCK));
		}
	}

/*
 *  �ͥåȥ�������ޥ�����
 *
 *    ���: ����������ƥ����ȤǼ¹Ԥ���ɬ�פ����뤿�ᡤ
 *          �����ϥ�ɥ�ϻ��ѤǤ��ʤ���
 */

static char const tinet_banner[] =
"\n"
"TINET %d.%d.%d (" __DATE__ ", " __TIME__ ")\n"
"Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering\n"
"                    Tomakomai National College of Technology, JAPAN\n";

void
net_timer_task(intptr_t exinf)
{
	ID		tskid;
	int_t		ix;
	callout_func	func;
	void 		*arg;

	get_tid(&tskid);
	syslog(LOG_NOTICE, tinet_banner,
	       (TINET_PRVER   >> 12) & UINT_C(0x0f),
	       (TINET_PRVER   >>  4) & UINT_C(0x0f),
	        TINET_PRVER          & UINT_C(0x0f));
	syslog(LOG_NOTICE, "[NET/TIMER:%d] started.", tskid);

	/* IP ���������롣*/
	IP_INIT();

#ifdef SUPPORT_TCP

	/* TCP ���ϥ�������ư���� */
	syscall(act_tsk(TCP_OUTPUT_TASK));

#endif	/* of #ifdef SUPPORT_TCP */

#if defined(SUPPORT_UDP) && defined(UDP_CFG_NON_BLOCKING)

	/* UDP ���ϥ�������ư���� */
	syscall(act_tsk(UDP_OUTPUT_TASK));

#endif	/* of #if defined(SUPPORT_UDP) && defined(UDP_CFG_NON_BLOCKING) */

	while (true) {
		/* �����ॢ���Ȥ�������ȥ��ƽФ���*/
		syscall(wai_sem(SEM_CALL_OUT_TIMEOUT));
		for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
			syscall(wai_sem(SEM_CALL_OUT_LOCK));
			if (callout[ix].func != NULL && callout[ix].timeout == 0) {
				func = callout[ix].func;
				arg  = callout[ix].arg;
				callout[ix].func = NULL;
				syscall(sig_sem(SEM_CALL_OUT_LOCK));
				(func)(arg);
				}
			else
				syscall(sig_sem(SEM_CALL_OUT_LOCK));
			}
		}
	}

/*
 *  �ͥåȥ�������ޥϥ�ɥ�
 *
 *    NET_TIMER_CYCLE (100ms) ��˸ƽФ���롣
 */

void
net_timer_handler(intptr_t exinf)
{
	int_t	ix, count = 0;

	for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
		if (callout[ix].func != NULL && callout[ix].timeout > 0) {
			callout[ix].timeout --;
			if (callout[ix].timeout == 0)
				count ++;
			}
		}

	if (count)
		syscall(isig_sem(SEM_CALL_OUT_TIMEOUT));
	}
