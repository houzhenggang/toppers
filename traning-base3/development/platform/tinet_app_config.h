/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
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
 *  @(#) $Id: tinet_app_config.h,v 1.3.1.2 2006/07/11 01:00:04 abe Exp abe $
 */

#ifndef _TINET_APP_CONFIG_H_
#define _TINET_APP_CONFIG_H_

/*
 *  ���󥿡��ͥåȥץ�ȥ���ե��ߥ꡼�Υ��ݡ���
 *
 *    Makefile �ǻ��ꤷ�Ƥ��ɤ�
 */

/*#define SUPPORT_INET4		TCP/IP,IPv4		*/
/*#define SUPPORT_INET6		TCP/IP,IPv6		*/
/*#define SUPPORT_TCP		TCP			*/
/*#define SUPPORT_UDP		UDP			*/

/*�ǡ�������ؤΥͥåȥ�����󥿥ե����������򤹤�	*/
/*�����줫��Ĥ�������Ǥ��롣				*/

/*#define SUPPORT_PPP		PointtoPointProtocol	*/
/*#define SUPPORT_LOOP		LocalLoopBack		*/
/*#define SUPPORT_ETHER		Ethernet		*/

/*#define SUPPORT_MIB		MIB(SNMP)		*/

/*
 *  TCP/IP �˴ؤ������
 */

/* TCP �˴ؤ������ */

#define TCP_CFG_PASSIVE_OPEN	/* TCP Passive Open	*/

/*
 *  MAX_TCP_SND_SEG: �����������ȥ������κ�����
 *
 *    ��꤫�� MSS ���ץ����ǥ������ȥ���������ꤵ��Ƥ⡢
 *    �����ͤǡ��������ȥ����������¤Ǥ��롣
 */

#ifdef USE_TCP_MSS_SEG

#ifdef MAX_TCP_SND_SEG
#undef MAX_TCP_SND_SEG
#endif

#ifdef SUPPORT_INET4
#define MAX_TCP_SND_SEG		TCP_MSS
#endif

#ifdef SUPPORT_INET6
#define MAX_TCP_SND_SEG		TCP6_MSS
#endif

#endif	/* of #ifdef USE_TCP_MSS_SEG */

/*
 *  DEF_TCP_RCV_SEG: �����������ȥ������ε�����
 */

#ifdef USE_TCP_MSS_SEG

#ifdef DEF_TCP_RCV_SEG
#undef DEF_TCP_RCV_SEG
#endif

#ifdef SUPPORT_INET4
#define DEF_TCP_RCV_SEG		TCP_MSS
#endif

#ifdef SUPPORT_INET6
#define DEF_TCP_RCV_SEG		TCP6_MSS
#endif

#endif	/* of #ifdef USE_TCP_MSS_SEG */

/* IPv4 �˴ؤ������ */

#ifdef SUPPORT_INET4

#ifdef SUPPORT_PPP

#if 1
#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(192,168,11,98)
#else
#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(0,0,0,0)		/* ���˳�����ƤƤ�餦���	*/
#endif

#if 1
#define IPV4_ADDR_REMOTE		MAKE_IPV4_ADDR(192,168,1,31)
#else
#define IPV4_ADDR_REMOTE		MAKE_IPV4_ADDR(0,0,0,0)		/* ���˳�����ƤƤ�餦���	*/
#endif

#define NUM_STATIC_ROUTE_ENTRY		1
#define NUM_REDIRECT_ROUTE_ENTRY	0

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_ETHER

#ifdef DHCP_CFG

#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(0,0,0,0)
#define IPV4_ADDR_LOCAL_MASK	MAKE_IPV4_ADDR(0,0,0,0)

#define IPV4_ADDR_DEFAULT_GW	MAKE_IPV4_ADDR(0,0,0,0)

#else	/* of #ifdef DHCP_CFG */

#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(192,168,11,98)
#define IPV4_ADDR_LOCAL_MASK	MAKE_IPV4_ADDR(255,255,255,0)

#define IPV4_ADDR_DEFAULT_GW	MAKE_IPV4_ADDR(192,168,11,1)

#endif	/* of #ifdef DHCP_CFG */

#define NUM_STATIC_ROUTE_ENTRY		3
#define NUM_REDIRECT_ROUTE_ENTRY	1

#endif	/* of #ifdef SUPPORT_ETHER */

#ifdef SUPPORT_LOOP

#define NUM_STATIC_ROUTE_ENTRY		1
#define NUM_REDIRECT_ROUTE_ENTRY	0

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #ifdef SUPPORT_INET4 */

/* IPv6 �˴ؤ������ */

#ifdef SUPPORT_INET6

#ifdef SUPPORT_PPP

#define NUM_STATIC_ROUTE_ENTRY		0
#define NUM_REDIRECT_ROUTE_ENTRY	0

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

#define NUM_STATIC_ROUTE_ENTRY		0
#define NUM_REDIRECT_ROUTE_ENTRY	0

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_ETHER

#define NUM_STATIC_ROUTE_ENTRY		0
#define NUM_REDIRECT_ROUTE_ENTRY	1

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  �ǡ�������� (�ͥåȥ�����󥿥ե�����) �˴ؤ������
 */

/*
 *  PPP �˴ؤ������
 */

#define HDLC_PORTID		1	/* HDLC(PPP)���Ѥ��륷�ꥢ��ݡ����ֹ�	*/

/*#define PPP_IDLE_TIMEOUT	(180*NET_TIMER_HZ)*/
					/* ���ǤޤǤΥ����ɥ���֡�		*/
					/* ���Ǥ��ʤ����ϥ����ȥ����Ȥ��롣	*/

/*#define PPP_CFG_MODEM			 ��ǥ���³�ξ��ϥ����Ȥ򳰤���	*/

#define MODEM_CFG_INIT		"ATE1&D0&S0\\V0\\Q1S0=1"
					/* ��ǥ�����ʸ����			*/
					/* NTT DoComo ��Х��륢���ץ� 96F ��	*/
					/*   E1: �������Хå�����			*/
					/*  &D0: ER����̵��			*/
					/*  &S0: DR������ ON			*/
					/*  \V0: �ꥶ��ȥ����� TYPE 1		*/
					/*  \Q1: XON/XOFF �ե�����		*/
					/* S0=1: ��ư�忮��󥰲�� = 1 ��	*/

#define MODEM_CFG_PHONE_NUMBER	"090-xxxx-9242"

					/* ����������ε�����			*/
#define DEF_LCP_LOCAL_CFGS	(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

					/* ���˵�����������ε�����		*/
#define DEF_LCP_REMOTE_CFGS	(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

/*
 *  ǧ�ڤ˴ؤ������
 */

#define AUTH_CFG_CLIENT		   	/* ǧ�ڥ��饤����ȥ⡼�ɤλ��ϥ����Ȥ򳰤���	*/
#define AUTH_CFG_SERVER			/* ǧ�ڥ����Х⡼�ɤλ��ϥ����Ȥ򳰤���		*/

#define AUTH_LOCAL_USER		"h8"		/* ���ۥ��ȤؤΥ�����ǧ�ڥ桼��̾	*/
#define AUTH_LOCAL_PASSWD	"3048f"		/* ���ۥ��ȤؤΥ�����ǧ�ڥѥ����	*/
#define AUTH_REMOTE_USER	"pen3"		/* ���ؤΥ�����ǧ�ڥ桼��̾		*/
#define AUTH_REMOTE_PASSWD	"600MHz"	/* ���ؤΥ�����ǧ�ڥѥ����		*/

/*
 *  ARP �˴ؤ������
 */

/*#define ARP_CFG_CALLBACK_DUPLICATED*/	/* IP ���ɥ쥹��ʣ���Х�����Хå��ؿ���	*/
					/* ���������ϥ����Ȥ򳰤���		*/

/*
 *  ICMPv4/v6 �˴ؤ������
 */

/*#define ICMP_CFG_CALLBACK_ECHO_REPLY*/	/* ICMP ECHO ��������������Ȥ��ƽФ�������Хå��ؿ���	*/
					/* ���������ϥ����Ȥ򳰤���			*/

/*
 *  �ͥåȥ���Хåե����γ������
 */

#ifdef SUPPORT_ETHER

/*
 *  �������ͥåȤξ��Υͥåȥ���Хåե����γ������
 */

/*
 *  ���!!
 *
 *  NE2000 �ߴ� NIC �Υǥ��Х����ɥ饤�С�if_ed�ˤκ��������Ĺ��
 *  60�ʥ��饤�󤷤� 62�˥����ƥåȤΤ��� IF + IPv4 +TCP ����
 *  64 �����ƥåȤΥͥåȥ���Хåե���������Ŭ�Ǥ��롣
 */

#ifdef SUPPORT_INET6

#ifdef NUM_MPF_NET_BUF_CSEG
#undef NUM_MPF_NET_BUF_CSEG
#endif
#define NUM_MPF_NET_BUF_CSEG	2	/* IF + IP + TCP	*/

#endif	/* of #ifdef SUPPORT_INET6 */

#ifdef SUPPORT_INET4

#ifdef NUM_MPF_NET_BUF_64
#undef NUM_MPF_NET_BUF_64
#endif
#define NUM_MPF_NET_BUF_64	2	/* 64 �����ƥå�	*/

#endif	/* #ifdef SUPPORT_INET4 */

#ifdef NUM_MPF_NET_BUF_128
#undef NUM_MPF_NET_BUF_128
#endif
#define NUM_MPF_NET_BUF_128	1	/* 128 �����ƥå�	*/

#ifdef NUM_MPF_NET_BUF_256
#undef NUM_MPF_NET_BUF_256
#endif
#define NUM_MPF_NET_BUF_256	1	/* 256 �����ƥå�	*/

#ifdef NUM_MPF_NET_BUF_512
#undef NUM_MPF_NET_BUF_512
#endif
#define NUM_MPF_NET_BUF_512	1	/* 512 �����ƥå�	*/

#ifdef SUPPORT_INET4

#ifdef NUM_MPF_NET_BUF_IP_MSS
#undef NUM_MPF_NET_BUF_IP_MSS
#endif

#ifdef USE_TCP_MSS_SEG
#define NUM_MPF_NET_BUF_IP_MSS	2	/* IF + 576 �����ƥå�	*/
#else
#define NUM_MPF_NET_BUF_IP_MSS	0	/* IF + 576 �����ƥå�	*/
#endif

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef NUM_MPF_NET_BUF_1024
#undef NUM_MPF_NET_BUF_1024
#endif
#define NUM_MPF_NET_BUF_1024	1	/* 1024 �����ƥå�	*/

#ifdef SUPPORT_INET6

#ifdef NUM_MPF_NET_BUF_IPV6_MMTU
#undef NUM_MPF_NET_BUF_IPV6_MMTU
#endif

#ifdef USE_TCP_MSS_SEG
#define NUM_MPF_NET_BUF_IPV6_MMTU	2	/* IF + 1280	*/
#else
#define NUM_MPF_NET_BUF_IPV6_MMTU	0	/* IF + 1280	*/
#endif

#endif	/* of #ifdef SUPPORT_INET6 */

#ifdef NUM_MPF_NET_BUF_IF_PDU
#undef NUM_MPF_NET_BUF_IF_PDU
#endif

#ifdef USE_TCP_MSS_SEG
#define NUM_MPF_NET_BUF_IF_PDU	0	/* IF ���� PDU ������	*/
#else
#define NUM_MPF_NET_BUF_IF_PDU	3	/* IF ���� PDU ������	*/
#endif

#endif	/* of #ifdef SUPPORT_ETHER */

#endif /* _TINET_APP_CONFIG_H_ */
