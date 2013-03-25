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
 *  @(#) $Id: tinet_config.h,v 1.5 2009/12/24 05:38:58 abe Exp abe $
 */

#ifndef _TINET_CONFIG_H_
#define _TINET_CONFIG_H_

/*
 *  TINET 1.2 �Ȥθߴ����Τ�������
 */

/* TCP�μ�ư�����ץ�򥵥ݡ��Ȥ��롣*/

#define TCP_CFG_PASSIVE_OPEN

/* TCP�ΥΥ�֥�å��󥰥����뵡ǽ���ȹ��ࡣ*/

#define TCP_CFG_NON_BLOCKING

/* UDP�ΥΥ�֥�å��󥰥����뵡ǽ���ȹ��ࡣ*/

#define UDP_CFG_NON_BLOCKING

/*
 *  NIC�������ƥࡢCPU�����ѥץ�����
 *  ��¸��������ե�����򥤥󥯥롼�ɤ��롣
 */

#if defined(TARGET_KERNEL_JSP)

#ifdef SUPPORT_ETHER

#include "tinet_nic_config.h"

#endif	/* of #ifdef SUPPORT_ETHER */

#include "tinet_sys_config.h"
#include "tinet_cpu_config.h"
#include "tinet_app_config.h"

#elif defined(TARGET_KERNEL_ASP)

#ifdef SUPPORT_ETHER

#include "tinet_nic_config.h"

#endif	/* of #ifdef SUPPORT_ETHER */

#include "tinet_target_config.h"
#include "tinet_app_config.h"

#endif	/* of #if defined(TARGET_KERNEL_JSP) */

/*
 *  TINET 1.1 �Ȥθߴ����Τ�������
 */

#ifdef  TMO_ICMP4_OUTPUT
#define TMO_ICMP_OUTPUT	TMO_ICMP4_OUTPUT
#endif

/*
 *  TINET 1.2 �Ȥθߴ����Τ�������
 */

#ifdef  NUM_MPF_NET_BUF_4096
#define NUM_MPF_NET_BUF_REASSM	NUM_MPF_NET_BUF_4096
#endif

/*
 *  TINET 1.3 �Ȥθߴ����Τ�������

#ifdef  NUM_MPF_NET_BUF_REASSM
#define NUM_MPF_NET_BUF4_REASSM	NUM_MPF_NET_BUF_REASSM
#endif
 */

/*
 *  TCP �˴ؤ������
 */

/*
 *  MAX_TCP_RCV_SEG: �����������ȥ������κ�����
 *
 *    ���: �ѹ����٤��ǤϤʤ���
 */

#ifndef MAX_TCP_RCV_SEG
#define MAX_TCP_RCV_SEG		(IF_MTU - (IP_HDR_SIZE + TCP_HDR_SIZE))
#endif

/*
 *  DEF_TCP_SND_SEG: �����������ȥ������ε�����
 */

#ifndef DEF_TCP_SND_SEG
#define DEF_TCP_SND_SEG		MAX_TCP_SND_SEG
#endif

/*
 *  TCP �̿�ü����������������ɥХåե��ξʥ��ԡ���ǽ
 */

#ifdef  TCP_CFG_SWBUF_CSAVE_ONLY
#ifndef TCP_CFG_SWBUF_CSAVE
#define TCP_CFG_SWBUF_CSAVE
#endif
#endif	/* of #ifdef  TCP_CFG_SWBUF_CSAVE_ONLY */

#ifdef  TCP_CFG_RWBUF_CSAVE_ONLY
#ifndef TCP_CFG_RWBUF_CSAVE
#define TCP_CFG_RWBUF_CSAVE
#endif
#endif	/* of #ifdef  TCP_CFG_RWBUF_CSAVE_ONLY */

/*
 *  TCP_CFG_URG_OFFSET: �۵ޥǡ����κǸ�ΥХ��ȤΥ��ե��å�
 *
 *    -1: BSD �μ������۵ޥݥ��󥿤ϡ��۵ޥǡ����κǸ�ΥХ��Ȥμ��ΥХ��Ȥ򺹤���
 *     0: RFC1122 �ε��ꡢ�۵ޥݥ��󥿤ϡ��۵ޥǡ����κǸ�ΥХ��Ȥ򺹤���
 */

#ifndef TCP_CFG_URG_OFFSET
#define TCP_CFG_URG_OFFSET	-1
#endif

/*
 *  ARP �˴ؤ������
 */

#ifndef ARP_CACHE_KEEP
#define ARP_CACHE_KEEP		(20*60*NET_TIMER_HZ)	/* ARP ����å���Υ����ॢ����	*/
#endif

/*
 *  �롼�ץХå����󥿥ե������˴ؤ������
 */

#ifndef LOMTU
#define LOMTU			1500	/* �롼�ץХå��� MTU			*/
#endif

/*
 * TINET ���ݡ��ȴؿ��˴ؤ������
 */

#ifndef NUM_IPV4ADDR_STR_BUFF		/* ip2str �ˤ����� IP ���ɥ쥹ʸ�����ѥХåե��� */

#if defined(SUPPORT_PPP)

#define NUM_IPV4ADDR_STR_BUFF	2

#else	/* of #if defined(SUPPORT_PPP) */

#define NUM_IPV4ADDR_STR_BUFF	1

#endif	/* of #if defined(SUPPORT_PPP) */

#endif	/* of #ifndef NUM_IPV4ADDR_STR_BUFF */

#ifndef NUM_IPV6ADDR_STR_BUFF
#define NUM_IPV6ADDR_STR_BUFF	2	/* ip62str �ˤ����� IP ���ɥ쥹ʸ�����ѥХåե��� */
#endif

#ifndef NUM_MACADDR_STR_BUFF		/* macstr �ˤ����� MAC ���ɥ쥹ʸ�����ѥХåե��� */

#if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING)

#define NUM_MACADDR_STR_BUFF	2

#else	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING) */

#define NUM_MACADDR_STR_BUFF	1

#endif	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING) */

#endif	/* of #ifndef NUM_MACADDR_STR_BUFF */

/*
 *  TINET �����Υ����ॢ�����ͤ�����
 */

#ifndef TMO_IP4_FRAG_GET_NET_BUF
#define TMO_IP4_FRAG_GET_NET_BUF	ULONG_C(1000)	/* [ms]��IPv4 �ǡ��������ƹ����ѥͥåȥ���Хåե����������ॢ����	*/
#endif

#ifndef TMO_IP6_FRAG_GET_NET_BUF
#define TMO_IP6_FRAG_GET_NET_BUF	ULONG_C(1000)	/* [ms]��IPv6 �ǡ��������ƹ����ѥͥåȥ���Хåե����������ॢ����	*/
#endif

#ifndef TMO_PPP_GET_NET_BUF
#define TMO_PPP_GET_NET_BUF		ULONG_C(1000)	/* [ms]��PPP �����ѥͥåȥ���Хåե����������ॢ����	*/
#endif

#ifndef TMO_ARP_GET_NET_BUF
#define TMO_ARP_GET_NET_BUF		ULONG_C(1000)	/* [ms]��ARP �Υͥåȥ���Хåե����������ॢ����	*/
#endif

#ifndef TMO_TCP_GET_NET_BUF
#define TMO_TCP_GET_NET_BUF		ULONG_C(1000)	/* [ms]��TCP �Υͥåȥ���Хåե����������ॢ����	*/
#endif

#ifndef TMO_TCP_OUTPUT
#define TMO_TCP_OUTPUT			ULONG_C(1000)	/* [ms]��TCP ���ϥ����ॢ����				*/
#endif

#ifndef TMO_UDP_OUTPUT
#define TMO_UDP_OUTPUT			ULONG_C(1000)	/* [ms]��UDP ���ϥ����ॢ����				*/
#endif

#ifndef TMO_ICMP_OUTPUT
#define TMO_ICMP_OUTPUT			ULONG_C(1000)	/* [ms]��ICMP ���ϥ����ॢ����				*/
#endif

#ifndef TMO_ND6_NS_OUTPUT
#define TMO_ND6_NS_OUTPUT		ULONG_C(1000)	/* [ms]�������������ϥ����ॢ����			*/
#endif

#ifndef TMO_ND6_NA_OUTPUT
#define TMO_ND6_NA_OUTPUT		ULONG_C(1000)	/* [ms]���������ν��ϥ����ॢ����			*/
#endif

#ifndef TMO_ND6_RS_OUTPUT
#define TMO_ND6_RS_OUTPUT		ULONG_C(1000)	/* [ms]���롼���������ϥ����ॢ����			*/
#endif

#ifndef TMO_ARP_OUTPUT
#define TMO_ARP_OUTPUT			ULONG_C(1000)	/* [ms]�����ɥ쥹����׵���ϥ����ॢ����		*/
#endif

#ifndef TMO_ND6_RTR_SOL_DELAY
#define TMO_ND6_RTR_SOL_DELAY		ULONG_C(1000)	/* [ms]���롼�����������ٱ�				*/
#endif

#ifndef TMO_ND6_RTR_SOL_INTERVAL
#define TMO_ND6_RTR_SOL_INTERVAL	ULONG_C(4000)	/* [ms]���롼���������ϴֳ�				*/
#endif

#ifndef TMO_IN_REDIRECT
					/* [s]������ľ���롼�ƥ��󥰥���ȥ꥿���ॢ����*/
#define TMO_IN_REDIRECT			(10*60*NET_TIMER_HZ)
#endif

/*
 *  TINET �����Υ������Υ����å�������������
 */

#ifndef TCP_OUT_TASK_STACK_SIZE
#define	TCP_OUT_TASK_STACK_SIZE	1024	/* TCP ���ϥ������Υ����å�������		*/
#endif

#ifndef UDP_OUT_TASK_STACK_SIZE
#define	UDP_OUT_TASK_STACK_SIZE	1024	/* UDP ���ϥ������Υ����å�������			*/
#endif

#ifndef PPP_INPUT_STACK_SIZE
#define	PPP_INPUT_STACK_SIZE	1024	/* PPP �������Υ����å�������		*/
#endif

#ifndef PPP_OUTPUT_STACK_SIZE
#define	PPP_OUTPUT_STACK_SIZE	1024	/* PPP ���ϥ������Υ����å�������		*/
#endif

#ifndef ETHER_INPUT_STACK_SIZE
#define	ETHER_INPUT_STACK_SIZE	1024	/* Ethernet ���ϥ������Υ����å�������	*/
#endif

#ifndef ETHER_OUTPUT_STACK_SIZE
#define	ETHER_OUTPUT_STACK_SIZE	1024	/* Ethernet ���ϥ������Υ����å�������	*/
#endif

#ifndef LOOP_INPUT_STACK_SIZE
#define	LOOP_INPUT_STACK_SIZE	1024	/* �롼�ץХå����ϥ������Υ����å�������	*/
#endif

#ifndef LOOP_OUTPUT_STACK_SIZE
#define	LOOP_OUTPUT_STACK_SIZE	1024	/* �롼�ץХå����ϥ������Υ����å�������	*/
#endif

#ifndef NET_TIMER_STACK_SIZE
#define	NET_TIMER_STACK_SIZE	1024	/* �ͥåȥ�������ޥ������Υ����å������� */
#endif

/*
 *  TINET �����Υ�������ͥ���٤�����
 */

#ifndef TCP_OUT_TASK_PRIORITY
#define TCP_OUT_TASK_PRIORITY	5	/* TCP ���ϥ�������ͥ����			*/
#endif

#ifndef UDP_OUT_TASK_PRIORITY
#define UDP_OUT_TASK_PRIORITY	5	/* UDP ���ϥ�������ͥ����				*/
#endif

#ifndef PPP_INPUT_PRIORITY
#define PPP_INPUT_PRIORITY	5	/* PPP ��������ͥ����			*/
#endif

#ifndef PPP_OUTPUT_PRIORITY
#define PPP_OUTPUT_PRIORITY	5	/* PPP ��������ͥ����			*/
#endif

#ifndef ETHER_INPUT_PRIORITY
#define ETHER_INPUT_PRIORITY	5	/* Ethernet ���ϥ�������ͥ����		*/
#endif

#ifndef ETHER_OUTPUT_PRIORITY
#define ETHER_OUTPUT_PRIORITY	5	/* Ethernet ���ϥ�������ͥ����		*/
#endif

#ifndef LOOP_INPUT_PRIORITY
#define LOOP_INPUT_PRIORITY	5	/* �롼�ץХå����ϥ�������ͥ����		*/
#endif

#ifndef LOOP_OUTPUT_PRIORITY
#define LOOP_OUTPUT_PRIORITY	5	/* �롼�ץХå����ϥ�������ͥ����		*/
#endif

#ifndef NET_TIMER_PRIORITY
#define NET_TIMER_PRIORITY	5	/* �ͥåȥ�������ޥ�������ͥ���� */
#endif

/*
 *  TINET �����Υǡ������塼�Υ���ȥ��������
 */

/* UDP �������塼������ */

#ifndef NUM_DTQ_UDP_RCVQ
#define NUM_DTQ_UDP_RCVQ	1	/* �󥳡���Хå���	*/
#endif

#ifndef NUM_DTQ_UDP_OUTPUT
#define NUM_DTQ_UDP_OUTPUT	1	/* UDP ���ϥǡ������塼������			*/
#endif

#ifndef NUM_DTQ_PPP_OUTPUT
#define NUM_DTQ_PPP_OUTPUT	2	/* PPP ���ϥǡ������塼��������2 �ʾ�	*/
#endif

#ifndef NUM_DTQ_ETHER_OUTPUT
#define NUM_DTQ_ETHER_OUTPUT	2	/* Ethernet ���ϥǡ������塼������	*/
#endif

#ifndef NUM_DTQ_LOOP_INPUT
#define NUM_DTQ_LOOP_INPUT	0	/* �롼�ץХå����ϥǡ������塼������	*/
#endif

#ifndef NUM_DTQ_LOOP_OUTPUT
#define NUM_DTQ_LOOP_OUTPUT	0	/* �롼�ץХå����ϥǡ������塼������	*/
#endif

/*
 *  TINET �ץ�ȥ��륹���å������Υ�͡���
 */

#include <net/net_rename.h>
#include <netinet/in_rename.h>

#ifdef SUPPORT_INET6

#include <netinet6/in6_rename.h>

#endif	/* of #ifdef SUPPORT_INET6 */

#endif /* _TINET_CONFIG_H_ */
