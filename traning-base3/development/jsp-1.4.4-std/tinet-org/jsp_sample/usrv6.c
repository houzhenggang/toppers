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
 *  @(#) $Id: usrv6.c,v 1.5 2009/12/24 05:40:11 abe Exp abe $
 */

/* 
 *  UDP ECHO ������
 *
 *    ��������������Ʊ�췿
 */

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include "usrv6.h"

/*
 *  �����ؿ������
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ѿ�
 */

#define BUF_SIZE	2048

/*
 *  UDP ECHO �����Х�����
 */

void
usrv_task(VP_INT exinf)
{
	static UB buffer[BUF_SIZE];

	T_IPV6EP	dst;
	T_IN6_ADDR	addr;
	ER_UINT		len;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (TRUE) {
		if ((len = udp6_rcv_dat((ID)exinf, &dst, buffer, sizeof(buffer), 20 * 1000)) >= 0) {
			buffer[len] = '\0';
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, addr: %s:%d,\n"
			                   "                     len: %d, msg: '%s'",
			                   ipv62str(NULL, &dst.ipaddr), dst.portno, len, buffer);
			if ((int)len > 0) {
				if ((len = udp6_snd_dat((ID)exinf, &dst, buffer, len, TMO_FEVR)) < 0)
					syslog(LOG_NOTICE, "[UDP ECHO SRV] send, error: %s", itron_strerror(len));
				}
			}
		else
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, error: %s", itron_strerror(len));
		}
	}
