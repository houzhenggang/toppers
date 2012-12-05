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
 *  @(#) $Id: echo.h,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

#ifndef _ECHO_H_
#define _ECHO_H_

/* 
 *  ECHO ���饤����ȡ������ФΥ����å�������
 */

#define TCP_ECHO_SRV_STACK_SIZE		1024		/* TCP ECHO �����Х������Υ����å�������		*/

#ifdef TOPPERS_S810_CLG3_85
#define TCP_ECHO_CLI_RCV_STACK_SIZE	512		/* TCP ECHO ���饤����ȼ����������Υ����å�������	*/
#define TCP_ECHO_CLI_SND_STACK_SIZE	512		/* TCP ECHO ���饤����������������Υ����å�������	*/
#else	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define TCP_ECHO_CLI_RCV_STACK_SIZE	1024		/* TCP ECHO ���饤����ȼ����������Υ����å�������	*/
#define TCP_ECHO_CLI_SND_STACK_SIZE	1024		/* TCP ECHO ���饤����������������Υ����å�������	*/
#endif	/* of #ifdef TOPPERS_S810_CLG3_85 */

#define UDP_ECHO_SRV_STACK_SIZE		1024		/* UDP ECHO �����Х������Υ����å�������		*/
#define UDP_ECHO_CLI_STACK_SIZE		1024		/* UDP ECHO ���饤����ȥ������Υ����å�������	*/

/* 
 *  ECHO ���饤����ȡ������Ф�ͥ����
 */

#define TCP_ECHO_SRV_MAIN_PRIORITY	5		/* TCP ECHO �����Х�������ͥ����			*/
#define TCP_ECHO_CLI_RCV_MAIN_PRIORITY	5		/* TCP ECHO ���饤����ȼ�����������ͥ����		*/
#define TCP_ECHO_CLI_SND_MAIN_PRIORITY	5		/* TCP ECHO ���饤�����������������ͥ����		*/

#define UDP_ECHO_SRV_MAIN_PRIORITY	5		/* UDP ECHO �����Х�������ͥ����			*/
#define UDP_ECHO_CLI_MAIN_PRIORITY	5		/* UDP ECHO ���饤����ȥ�������ͥ����		*/

/*
 *  TCP ������������ɥХåե�������
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define TCP_ECHO_CLI_SWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)
#define TCP_ECHO_CLI_RWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#define TCP_ECHO_SRV_SWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*2)
#define TCP_ECHO_SRV_RWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*2)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)

#define TCP_ECHO_CLI_SWBUF_SIZE		(TCP_MSS)
#define TCP_ECHO_CLI_RWBUF_SIZE		(TCP_MSS)

#define TCP_ECHO_SRV_SWBUF_SIZE		(TCP_MSS)
#define TCP_ECHO_SRV_RWBUF_SIZE		(TCP_MSS)

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_ECHO_CLI_SWBUF_SIZE		(TCP6_MSS)
#define TCP_ECHO_CLI_RWBUF_SIZE		(TCP6_MSS)

#define TCP_ECHO_SRV_SWBUF_SIZE		(TCP6_MSS)
#define TCP_ECHO_SRV_RWBUF_SIZE		(TCP6_MSS)

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

/*
 *  ��������
 */

#if !(defined(USE_TCP_ECHO_SRV1) && !defined(USE_TCP_NON_BLOCKING) && defined(USE_COPYSAVE_API))

#undef  NUM_TCP_ECHO_SRV_TASKS
#define NUM_TCP_ECHO_SRV_TASKS		1

#endif	/* of #if !(defined(USE_TCP_ECHO_SRV1) && !defined(USE_TCP_NON_BLOCKING) && defined(USE_COPYSAVE_API)) */

/*
 *  �ѿ�
 */

extern bool_t	tcp_echo_cli_valid;
extern bool_t	udp_echo_cli_valid;

/* TCP �������Хåե� */

extern uint8_t tcp_echo_cli_swbuf[];
extern uint8_t tcp_echo_cli_rwbuf[];

#ifdef _TCP_H_

extern uint8_t tcp_echo_srv_swbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_SWBUF_SIZE];
extern uint8_t tcp_echo_srv_rwbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_RWBUF_SIZE];

#endif	/* of #ifdef _TCP_H_ */

/*
 *  ������
 */

extern void	tcp_echo_srv_task(intptr_t exinf);
extern void	tcp_echo_srv_rcv_task(intptr_t exinf);
extern void	tcp_echo_srv_snd_task(intptr_t exinf);
extern void	tcp_echo_cli_rcv_task(intptr_t exinf);
extern void	tcp_echo_cli_snd_task(intptr_t exinf);

extern void	udp_echo_srv_task(intptr_t exinf);
extern void	udp_echo_cli_task(intptr_t exinf);

/*
 *  �ؿ�
 */

extern ER callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_nblk_tcp_echo_cli (ID cepid, FN fncd, void *p_parblk);

extern ER callback_udp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_udp_echo_cli (ID cepid, FN fncd, void *p_parblk);

extern ER callback_nblk_udp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_nblk_udp_echo_cli (ID cepid, FN fncd, void *p_parblk);

#endif	/* of #ifndef _ECHO_H_ */
