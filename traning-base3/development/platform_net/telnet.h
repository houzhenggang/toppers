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
 *  @(#) $Id: telnet.h,v 1.0 2010/11/28 07:28:04 roi Exp $
 */

#ifndef _TELNET_H_
#define _TELNET_H_

#include <t_services.h>

/* 
 *  �����л�ץ����
 */

#define TCP_TELNET_SRV_STACK_SIZE	1024	/* TCP TELNET �����Х������Υ����å�������		*/

#ifdef MAIN_PRIORITY
#define SRV_PRIORITY    (MAIN_PRIORITY+1)
#else
#define SRV_PRIORITY    6
#endif

/*
 *  ���Ѥ��� API ������
 */

#define USE_TCP_NON_BLOCKING
#define USE_COPYSAVE_API

/*
 *  TCP ������������ɥХåե�������
 */

#ifdef SUPPORT_INET4

#define TCP_TELNET_SRV_SWBUF_SIZE	(TCP_MSS)
#define TCP_TELNET_SRV_RWBUF_SIZE	(TCP_MSS)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

#define TCP_TELNET_SRV_SWBUF_SIZE	(TCP6_MSS)
#define TCP_TELNET_SRV_RWBUF_SIZE	(TCP6_MSS)

#endif	/* of #ifdef SUPPORT_INET6 */

#ifndef _MACRO_ONLY

/*
 *  TCP �������Хåե�
 */

extern UB tcp_telnet_srv_swbuf[];
extern UB tcp_telnet_srv_rwbuf[];

/*
 *  ������
 */

extern void tcp_telnet_srv_task(VP_INT exinf);

/*
 *  �ؿ�
 */

extern ER callback_nblk_tcp_telnet_srv (ID cepid, FN fncd, VP p_parblk);
extern void macaddr_init(VP_INT exinf);

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _TELNET_H_ */
