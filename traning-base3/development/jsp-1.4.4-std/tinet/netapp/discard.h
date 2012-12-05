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
 *  @(#) $Id: discard.h,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

#ifndef _DISCARD_H_
#define _DISCARD_H_

/* 
 *  DISCARD �����С����饤����ȤΥ����å�������
 */

#define TCP_DISCARD_SRV_STACK_SIZE	1024		/* TCP DISCARD �����Х������Υ����å������� */
#define TCP_DISCARD_CLI_STACK_SIZE	1024		/* TCP DISCARD ���饤����ȥ������Υ����å������� */
#define UDP_DISCARD_CLI_STACK_SIZE	1024		/* UDP DISCARD ���饤����ȥ������Υ����å������� */

/* 
 *  DISCARD �����С����饤����Ȥ�ͥ����
 */

#define TCP_DISCARD_SRV_MAIN_PRIORITY	5	/* TCP DISCARD �����Х�������ͥ���� */
#define TCP_DISCARD_CLI_MAIN_PRIORITY	5	/* TCP DISCARD ���饤����ȥ�������ͥ���� */
#define UDP_DISCARD_CLI_MAIN_PRIORITY	5	/* UDP DISCARD ���饤����ȥ�������ͥ���� */

/*
 *  TCP ������������ɥХåե�������
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define TCP_DISCARD_CLI_SWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)
#define TCP_DISCARD_SRV_RWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)

#define TCP_DISCARD_CLI_SWBUF_SIZE	(TCP_MSS)
#define TCP_DISCARD_SRV_RWBUF_SIZE	(TCP_MSS)

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_DISCARD_CLI_SWBUF_SIZE	(TCP6_MSS)
#define TCP_DISCARD_SRV_RWBUF_SIZE	(TCP6_MSS)

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

/*
 *  �ѿ�
 */

extern bool_t	tcp_discard_cli_valid;
extern bool_t	udp_discard_cli_valid;

/* TCP �������Хåե� */

extern uint8_t tcp_discard_cli_swbuf[];
extern uint8_t tcp_discard_cli_rwbuf[];

extern uint8_t tcp_discard_srv_swbuf[];
extern uint8_t tcp_discard_srv_rwbuf[];

/*
 *  ������
 */

extern void tcp_discard_srv_task(intptr_t exinf);
extern void tcp_discard_cli_task(intptr_t exinf);

extern void udp_discard_cli_task(intptr_t exinf);

/*
 *  �ؿ�
 */

extern ER callback_nblk_tcp_discard_cli (ID cepid, FN fncd, void *p_parblk);

#endif	/* of #ifndef _DISCARD_H_ */
