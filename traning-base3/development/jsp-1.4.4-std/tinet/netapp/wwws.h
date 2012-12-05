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
 *  @(#) $Id: wwws.h,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

#ifndef _WWWS_H_
#define _WWWS_H_

/* 
 *  WWW ������
 */

#include <tinet_defs.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>

#include <netinet6/in6.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#ifdef TOPPERS_S810_CLG3_85
#define	WWW_SRV_STACK_SIZE		768		/* �������Υ����å�������	*/
#else	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define	WWW_SRV_STACK_SIZE		1024		/* �������Υ����å�������	*/
#endif	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define WWW_SRV_MAIN_PRIORITY		5		/* ��������ͥ����		*/

/*
 *  TCP ������������ɥХåե�������
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define WWW_SRV_SWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_SWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_SWBUF_SIZE	(TCP6_MSS)
#endif

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_RWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_RWBUF_SIZE	(TCP6_MSS)
#endif

#define WWW_RBUFF_SIZE		(WWW_SRV_RWBUF_SIZE)
#define WWW_LINE_SIZE		80
#define WWW_NUM_FIELDS		4

#ifndef _MACRO_ONLY

typedef struct line {
	uint8_t		len;
	uint8_t		num;
	uint8_t		off[WWW_NUM_FIELDS];
	char		buf[WWW_LINE_SIZE + 1];
	} T_WWW_LINE;

#ifdef USE_COPYSAVE_API

typedef struct www_buffer {
	char		*buf;
	uint16_t	len;
	uint16_t	index;
	} T_WWW_BUFFER;

#else	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_buffer {
	uint16_t	len;
	uint16_t	index;
	char		buf[WWW_RBUFF_SIZE];
	} T_WWW_BUFFER;

#endif	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_rwbuf {
	T_WWW_BUFFER	sbuf;
	T_WWW_BUFFER	rbuf;
	char		unget;
	} T_WWW_RWBUF;

/* ������ */

extern void	www_srv_task (intptr_t exinf);

/*
 *  TCP �������Хåե�
 */

extern uint8_t www_srv_swbuf[NUM_WWW_SRV_TASKS][WWW_SRV_SWBUF_SIZE];
extern uint8_t www_srv_rwbuf[NUM_WWW_SRV_TASKS][WWW_SRV_RWBUF_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _WWWS_H_ */
