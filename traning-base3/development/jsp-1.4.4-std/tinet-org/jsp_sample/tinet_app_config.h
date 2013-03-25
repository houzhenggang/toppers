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
 *  @(#) $Id: tinet_app_config.h,v 1.5 2009/12/24 05:40:11 abe Exp abe $
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

/*
 *  TCP��ǽư�����ץ�Τߥ��ݡ��Ȥ��뤳�Ȥ���ꤹ�롣
 */

#ifdef UNDEF_TCP_CFG_PASSIVE_OPEN
#undef TCP_CFG_PASSIVE_OPEN
#endif

/*
 *  TCP �̿�ü����������������ɥХåե��ξʥ��ԡ���ǽ
 *    ���: Makefile �ǻ��ꤷ�Ƥ��롣
 */
/*#define TCP_CFG_RWBUF_CSAVE_ONLY*/
			/* TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ�Τ�ͭ���ˤ��롣	*/
/*#define TCP_CFG_RWBUF_CSAVE*/
			/* TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ˤ��롣	*/
/*#define TCP_CFG_SWBUF_CSAVE_ONLY*/
			/* TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ�Τ�ͭ���ˤ��롣	*/
/*#define TCP_CFG_SWBUF_CSAVE*/
			/* TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ˤ��롣	*/

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ�Ρ�
 *  ����������ɥХåե����塼�κ��票��ȥ����
 *  ������������˼��������������Ȥ��˴����뤿�ᡢ������������ä��롣
 *  �ޤ������ꤷ�ʤ������¤��ʤ���
 */
/*#define TCP_CFG_RWBUF_CSAVE_MAX_QUEUES	2*/

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ�ǡ�
 *  ����������ɥХåե��˻��Ѥ���ͥåȥ���Хåե��Υ�������
 */

#ifdef USE_TCP_MSS_SEG

#ifdef SUPPORT_INET4
#define TCP_CFG_SWBUF_CSAVE_MAX_SIZE	(IF_HDR_SIZE + IP4_MSS)		/* ���祵���� */
#endif

#ifdef SUPPORT_INET6
#define TCP_CFG_SWBUF_CSAVE_MAX_SIZE	(IF_HDR_SIZE + IPV6_MMTU)	/* ���祵���� */
#endif

#else	/* of #ifdef USE_TCP_MSS_SEG */

#define TCP_CFG_SWBUF_CSAVE_MAX_SIZE	IF_PDU_SIZE			/* ���祵���� */

#endif	/* of #ifdef USE_TCP_MSS_SEG */

#define TCP_CFG_SWBUF_CSAVE_MIN_SIZE	0				/* �Ǿ������� */

/*
 *  TCP �ΥΥ�֥�å��󥰥����뵡ǽ
 */

#ifdef UNDEF_TCP_CFG_NON_BLOCKING
#undef TCP_CFG_NON_BLOCKING
#endif

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
#define MAX_TCP_SND_SEG			TCP_MSS
#endif

#ifdef SUPPORT_INET6
#define MAX_TCP_SND_SEG			TCP6_MSS
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
#define DEF_TCP_RCV_SEG			TCP_MSS
#endif

#ifdef SUPPORT_INET6
#define DEF_TCP_RCV_SEG			TCP6_MSS
#endif

#endif	/* of #ifdef USE_TCP_MSS_SEG */

/*
 *  ����������� Time Wait ���֤� TCP �̿�ü��ʬΥ��ǽ
 *
 *  Time Wait ���֤� TCP �̿�ü���Υ���ȥ������ꤹ�롣
 *  ���ꤷ�ʤ�����0 ����ꤹ��ȡ�
 *  ���������� Time Wait ���֤� TCP �̿�ü����ʬΥ���뵡ǽ���ȹ��ޤʤ���
 */
#if defined(USE_TCP_MSS_SEG)
#define NUM_TCP_TW_CEP_ENTRY		3
#else
#define NUM_TCP_TW_CEP_ENTRY		6
#endif

/*
 *  TCP �إå��Υȥ졼�����ϵ�ǽ
 */
//#define TCP_CFG_TRACE

/*
 *  �ȥ졼�������оݤΥ�⡼�ȥۥ��Ȥ� IPv4 ���ɥ쥹
 *  IPV4_ADDRANY ����ꤹ��ȡ����ƤΥۥ��Ȥ��оݤȤ��롣
 */
#define TCP_CFG_TRACE_IPV4_RADDR	IPV4_ADDRANY

/*
 *  �ȥ졼�������оݤΥ�⡼�ȥۥ��ȤΥݡ����ֹ�
 *  TCP_PORTANY ����ꤹ��ȡ����ƤΥݡ����ֹ���оݤˤ��롣
 */
#define TCP_CFG_TRACE_RPORTNO		TCP_PORTANY
//#define TCP_CFG_TRACE_RPORTNO		UINT_C(7)

/*
 *  �ȥ졼�������оݤΥ�����ۥ��ȤΥݡ����ֹ�
 *  TCP_PORTANY ����ꤹ��ȡ����ƤΥݡ����ֹ���оݤˤ��롣
 */
#define TCP_CFG_TRACE_LPORTNO		TCP_PORTANY
//#define TCP_CFG_TRACE_LPORTNO		UINT_C(7)

/*
 *  ITRON TCP/IP API��TCP �γ�ĥ��ǽ
 */
//#define TCP_CFG_EXTENTIONS

/*
 *  TCP_CFG_URG_OFFSET: �۵ޥǡ����κǸ�ΥХ��ȤΥ��ե��å�
 *
 *    -1: BSD �μ������۵ޥݥ��󥿤ϡ��۵ޥǡ����κǸ�ΥХ��Ȥμ��ΥХ��Ȥ򺹤���
 *     0: RFC1122 �ε��ꡢ�۵ޥݥ��󥿤ϡ��۵ޥǡ����κǸ�ΥХ��Ȥ򺹤���
 */

//#define TCP_CFG_URG_OFFSET	-1
//#define TCP_CFG_URG_OFFSET	0

/* UDP �˴ؤ������ */

/*
 *  UDP �ΥΥ�֥�å��󥰥����뵡ǽ
 */

#ifdef UNDEF_UDP_CFG_NON_BLOCKING
#undef UDP_CFG_NON_BLOCKING
#endif

/*
 *  ITRON TCP/IP API��UDP �γ�ĥ��ǽ
 */
//#define UDP_CFG_EXTENTIONS

/* IPv4 �˴ؤ������ */

#ifdef SUPPORT_INET4

#ifdef SUPPORT_PPP

#if 1
#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(192,168,1,21)
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
#define IPV4_ADDR_LOCAL_MASK		MAKE_IPV4_ADDR(0,0,0,0)
#define IPV4_ADDR_DEFAULT_GW		MAKE_IPV4_ADDR(0,0,0,0)

#else	/* of #ifdef DHCP_CFG */

#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(172,25,193,190)
#define IPV4_ADDR_LOCAL_MASK		MAKE_IPV4_ADDR(255,255,240,0)
#define IPV4_ADDR_DEFAULT_GW		MAKE_IPV4_ADDR(172,25,193,140)

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
 *  �������ͥåȤ˴ؤ������
 */

/*
 *  PPP �˴ؤ������
 */

#define HDLC_PORTID			1	/* HDLC(PPP)���Ѥ��륷�ꥢ��ݡ����ֹ�	*/

/*#define PPP_IDLE_TIMEOUT		(180*NET_TIMER_HZ)*/
					/* ���ǤޤǤΥ����ɥ���֡�		*/
					/* ���Ǥ��ʤ����ϥ����ȥ����Ȥ��롣	*/

/*#define PPP_CFG_MODEM			 ��ǥ���³�ξ��ϥ����Ȥ򳰤���	*/

#define MODEM_CFG_INIT			"ATE1&D0&S0\\V0\\Q1S0=1"
					/* ��ǥ�����ʸ����			*/
					/* NTT DoComo ��Х��륢���ץ� 96F ��	*/
					/*   E1: �������Хå�����			*/
					/*  &D0: ER����̵��			*/
					/*  &S0: DR������ ON			*/
					/*  \V0: �ꥶ��ȥ����� TYPE 1		*/
					/*  \Q1: XON/XOFF �ե�����		*/
					/* S0=1: ��ư�忮��󥰲�� = 1 ��	*/

#define MODEM_CFG_PHONE_NUMBER		"090-xxxx-9242"

					/* ����������ε�����			*/
#define DEF_LCP_LOCAL_CFGS		(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|\
					 LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

					/* ���˵�����������ε�����		*/
#define DEF_LCP_REMOTE_CFGS		(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|\
					 LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

/*
 *  ǧ�ڤ˴ؤ������
 */

#define AUTH_CFG_CLIENT		   	/* ǧ�ڥ��饤����ȥ⡼�ɤλ��ϥ����Ȥ򳰤���	*/
#define AUTH_CFG_SERVER			/* ǧ�ڥ����Х⡼�ɤλ��ϥ����Ȥ򳰤���		*/

#define AUTH_LOCAL_USER			"h8"		/* ���ۥ��ȤؤΥ�����ǧ�ڥ桼��̾	*/
#define AUTH_LOCAL_PASSWD		"3048f"		/* ���ۥ��ȤؤΥ�����ǧ�ڥѥ����	*/
#define AUTH_REMOTE_USER		"pen3"		/* ���ؤΥ�����ǧ�ڥ桼��̾		*/
#define AUTH_REMOTE_PASSWD		"600MHz"	/* ���ؤΥ�����ǧ�ڥѥ����		*/

/*
 *  ARP �˴ؤ������
 */

/*#define ARP_CFG_CALLBACK_DUPLICATED*/	/* IP ���ɥ쥹��ʣ���Х�����Хå��ؿ���	*/
					/* ���������ϥ����Ȥ򳰤���		*/

/*
 *  ICMPv4/v6 �˴ؤ������
 */

#ifdef USE_PING

#define ICMP_CFG_CALLBACK_ECHO_REPLY	/* ICMP ECHO ��������������Ȥ��ƽФ�������Хå��ؿ���	*/
					/* ���������ϥ����Ȥ򳰤���			*/

#endif	/* of #ifdef USE_PING */

/*
 *  �ͥåȥ���Хåե��˴ؤ������
 */

#ifdef SUPPORT_ETHER

/*
 *  �������ͥåȤξ��Υͥåȥ���Хåե����γ������
 */

/*
 *  64 �����ƥå�
 *
 *    IPv4 �ǤΤ߳�����Ƥ롣
 *
 *    IPv6 �Ǥϡ�TCP ���楻�����ȡ�CSEG��SDU �ʤ��˥�������
 *    �ͥåȥ���Хåե���IF + IPv6 + TCP = 74�˰ʲ���
 *    �ͥåȥ���Хåե������פǤ��롣
 */

#ifdef NUM_MPF_NET_BUF_64
#undef NUM_MPF_NET_BUF_64
#endif

#ifdef SUPPORT_INET4
#define NUM_MPF_NET_BUF_64		2
#else
#define NUM_MPF_NET_BUF_64		0
#endif

/*
 *  CSEG��IF + IP + TCP��
 *
 *    IPv6 �ǤΤ߳�����Ƥ롣
 *
 *    NE2000 �ߴ� NIC �Υǥ��Х����ɥ饤�С�if_ed�ˤκ��������Ĺ�ϡ�
 *    �������ͥåȥե졼��κ�ûĹ�Ǥ��� 60��CRC �� 4 �����ƥåȤ������
 *    ���˥��饤�󤷤� 62�˥����ƥåȤǤ��롣
 *    ���äơ�IPv4 �Ǥϡ�CSEG �������Υͥåȥ���Хåե�
 *   ��IF + IPv4 + TCP = 54�ˤ����פǤ��롣
 */

#ifdef NUM_MPF_NET_BUF_CSEG
#undef NUM_MPF_NET_BUF_CSEG
#endif

#ifdef SUPPORT_INET6
#define NUM_MPF_NET_BUF_CSEG		2
#else
#define NUM_MPF_NET_BUF_CSEG		0
#endif

/*
 *  128 �����ƥå�
 *
 *    IPv4 �ǡ�TCP MSS��IP MSS��IF + 576 �����ƥåȡˤ�
 *    �ͥåȥ���Хåե��������Ƥ��硢
 *    128 �����ƥåȤΥͥåȥ���Хåե��ϳ�����Ƥʤ���
 */

#ifdef NUM_MPF_NET_BUF_128
#undef NUM_MPF_NET_BUF_128
#endif

#if defined(USE_TCP_MSS_SEG)
#define NUM_MPF_NET_BUF_128		0
#else
#define NUM_MPF_NET_BUF_128		1
#endif

/*
 *  256 �����ƥå�
 *
 *    IPv4 �ǡ�TCP MSS��IP MSS��IF + 576 �����ƥåȡˤ�
 *    �ͥåȥ���Хåե��������Ƥ��硢
 *    256 �����ƥåȤΥͥåȥ���Хåե��ϳ�����Ƥʤ���
 */

#ifdef NUM_MPF_NET_BUF_256
#undef NUM_MPF_NET_BUF_256
#endif

#if defined(USE_TCP_MSS_SEG)
#define NUM_MPF_NET_BUF_256		0
#else
#define NUM_MPF_NET_BUF_256		1
#endif

/*
 *  512 �����ƥå�	
 *
 *    IPv4 �ǡ�TCP MSS��IP MSS��IF + 576 �����ƥåȡˤ�
 *    �ͥåȥ���Хåե��������Ƥ��硢
 *    512 �����ƥåȤΥͥåȥ���Хåե��ϳ�����Ƥʤ���
 */

#ifdef NUM_MPF_NET_BUF_512
#undef NUM_MPF_NET_BUF_512
#endif

#if defined(USE_TCP_MSS_SEG)
#define NUM_MPF_NET_BUF_512		0
#else
#define NUM_MPF_NET_BUF_512		1
#endif

/*
 *  TCP MSS��IP MSS��IF + 576 �����ƥåȡ�
 *
 *   ��IPv4 �ǤΤ߳�����Ƥ롣
 *   ��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ǡ�
 *     �ʥ��ԡ� API ����Ѥ���Ȥ��ϡ�+1 ������Ƥ롣
 */

#ifdef NUM_MPF_NET_BUF_IP_MSS
#undef NUM_MPF_NET_BUF_IP_MSS
#endif

#if defined(SUPPORT_INET4) && defined(USE_TCP_MSS_SEG)

#if (defined(TCP_CFG_RWBUF_CSAVE)      || defined(TCP_CFG_SWBUF_CSAVE) ||	\
     defined(TCP_CFG_RWBUF_CSAVE_ONLY) || defined(TCP_CFG_SWBUF_CSAVE_ONLY)) && defined(USE_COPYSAVE_API)
#define NUM_MPF_NET_BUF_IP_MSS		3
#else
#define NUM_MPF_NET_BUF_IP_MSS		2	/* IF + 576 �����ƥå�	*/
#endif

#else	/* of #if defined(SUPPORT_INET4) && defined(USE_TCP_MSS_SEG) */

#define NUM_MPF_NET_BUF_IP_MSS		0	/* IF + 576 �����ƥå�	*/

#endif	/* of #if defined(SUPPORT_INET4) && defined(USE_TCP_MSS_SEG) */

/*
 *  1024 �����ƥå�	
 *
 *    TCP MSS �Υͥåȥ���Хåե��������Ƥ��硢
 *    1024 �����ƥåȤΥͥåȥ���Хåե��ϳ�����Ƥʤ���
 */

#ifdef NUM_MPF_NET_BUF_1024
#undef NUM_MPF_NET_BUF_1024
#endif

#if defined(USE_TCP_MSS_SEG)
#define NUM_MPF_NET_BUF_1024		0	/* 1024 �����ƥå�	*/
#else
#define NUM_MPF_NET_BUF_1024		1	/* 1024 �����ƥå�	*/
#endif

/*
 *  TCP MSS��IPV6 MMTU��IF + 1280 �����ƥåȡ�
 *
 *   ��IPv6 �ǤΤ߳�����Ƥ롣
 *   ��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ǡ�
 *     �ʥ��ԡ� API ����Ѥ���Ȥ��ϡ�+1 ������Ƥ롣
 */

#ifdef NUM_MPF_NET_BUF_IPV6_MMTU
#undef NUM_MPF_NET_BUF_IPV6_MMTU
#endif

#if defined(SUPPORT_INET6) && (defined(USE_TCP_MSS_SEG) || defined(USE_IPV6_MMTU))

#if (defined(TCP_CFG_RWBUF_CSAVE)      || defined(TCP_CFG_SWBUF_CSAVE) ||	\
     defined(TCP_CFG_RWBUF_CSAVE_ONLY) || defined(TCP_CFG_SWBUF_CSAVE_ONLY)) && defined(USE_COPYSAVE_API)
#define NUM_MPF_NET_BUF_IPV6_MMTU	3	/* IF + 1280	*/
#else
#define NUM_MPF_NET_BUF_IPV6_MMTU	2	/* IF + 1280	*/
#endif

#else	/* of #if defined(SUPPORT_INET6) && (defined(USE_TCP_MSS_SEG) || defined(USE_IPV6_MMTU)) */

#define NUM_MPF_NET_BUF_IPV6_MMTU	0	/* IF + 1280	*/

#endif	/* of #if defined(SUPPORT_INET6) && (defined(USE_TCP_MSS_SEG) || defined(USE_IPV6_MMTU)) */

/*
 *  IF ���� PDU ������
 *
 *   ��TCP MSS �Υͥåȥ���Хåե��������Ƥ��硢
 *     IF ���� PDU �������Υͥåȥ���Хåե��ϳ�����Ƥʤ���
 *   ��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ǡ�
 *     �ʥ��ԡ� API ����Ѥ���Ȥ��ϡ�+1 ������Ƥ롣
 */

#ifdef NUM_MPF_NET_BUF_IF_PDU
#undef NUM_MPF_NET_BUF_IF_PDU
#endif

#ifdef USE_TCP_MSS_SEG

#define NUM_MPF_NET_BUF_IF_PDU		0

#else	/* of #ifdef USE_TCP_MSS_SEG */

#if (defined(TCP_CFG_RWBUF_CSAVE) || defined(TCP_CFG_SWBUF_CSAVE)) && defined(USE_COPYSAVE_API)
#define NUM_MPF_NET_BUF_IF_PDU		6
#else
#define NUM_MPF_NET_BUF_IF_PDU		5
#endif

#endif	/* of #ifdef USE_TCP_MSS_SEG */

/*
 *  65536 �����ƥå�
 *
 *  ��NET_BUF_CFG_LONG_LEN ����������Ȥ��Τ߳�����Ƥ롣
 */

#ifdef NET_BUF_CFG_LONG_LEN

/* IPv6 �� */

#ifdef NUM_MPF_NET_BUF6_65536
#undef NUM_MPF_NET_BUF6_65536
#endif

#if defined(USE_TCP_MSS_SEG)
#define NUM_MPF_NET_BUF6_65536	0
#else
#define NUM_MPF_NET_BUF6_65536	2
#endif

#else	/* of ifdef NET_BUF_CFG_LONG_LEN */

#define NUM_MPF_NET_BUF6_65536	0

#endif	/* of ifdef NET_BUF_CFG_LONG_LEN */

#endif	/* of #ifdef SUPPORT_ETHER */

#endif /* _TINET_APP_CONFIG_H_ */
