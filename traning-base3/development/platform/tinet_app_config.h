/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次の条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: tinet_app_config.h,v 1.3.1.2 2006/07/11 01:00:04 abe Exp abe $
 */

#ifndef _TINET_APP_CONFIG_H_
#define _TINET_APP_CONFIG_H_

/*
 *  インターネットプロトコルファミリーのサポート
 *
 *    Makefile で指定しても良い
 */

/*#define SUPPORT_INET4		TCP/IP,IPv4		*/
/*#define SUPPORT_INET6		TCP/IP,IPv6		*/
/*#define SUPPORT_TCP		TCP			*/
/*#define SUPPORT_UDP		UDP			*/

/*データリンク層のネットワークインタフェースを選択する	*/
/*いずれか一つだけ選択できる。				*/

/*#define SUPPORT_PPP		PointtoPointProtocol	*/
/*#define SUPPORT_LOOP		LocalLoopBack		*/
/*#define SUPPORT_ETHER		Ethernet		*/

/*#define SUPPORT_MIB		MIB(SNMP)		*/

/*
 *  TCP/IP に関する定義
 */

/* TCP に関する定義 */

#define TCP_CFG_PASSIVE_OPEN	/* TCP Passive Open	*/

/*
 *  MAX_TCP_SND_SEG: 送信セグメントサイズの最大値
 *
 *    相手から MSS オプションでセグメントサイズを指定されても、
 *    この値で、セグメントサイズを制限できる。
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
 *  DEF_TCP_RCV_SEG: 受信セグメントサイズの規定値
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

/* IPv4 に関する定義 */

#ifdef SUPPORT_INET4

#ifdef SUPPORT_PPP

#if 1
#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(192,168,11,98)
#else
#define IPV4_ADDR_LOCAL			MAKE_IPV4_ADDR(0,0,0,0)		/* 相手に割り当ててもらう場合	*/
#endif

#if 1
#define IPV4_ADDR_REMOTE		MAKE_IPV4_ADDR(192,168,1,31)
#else
#define IPV4_ADDR_REMOTE		MAKE_IPV4_ADDR(0,0,0,0)		/* 相手に割り当ててもらう場合	*/
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

/* IPv6 に関する定義 */

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
 *  データリンク層 (ネットワークインタフェース) に関する定義
 */

/*
 *  PPP に関する定義
 */

#define HDLC_PORTID		1	/* HDLC(PPP)に用いるシリアルポート番号	*/

/*#define PPP_IDLE_TIMEOUT	(180*NET_TIMER_HZ)*/
					/* 切断までのアイドル時間、		*/
					/* 切断しない場合はコメントアウトする。	*/

/*#define PPP_CFG_MODEM			 モデム接続の場合はコメントを外す。	*/

#define MODEM_CFG_INIT		"ATE1&D0&S0\\V0\\Q1S0=1"
					/* モデム初期化文字列			*/
					/* NTT DoComo モバイルアダプタ 96F 用	*/
					/*   E1: エコーバックあり			*/
					/*  &D0: ER信号無視			*/
					/*  &S0: DR信号常時 ON			*/
					/*  \V0: リザルトコード TYPE 1		*/
					/*  \Q1: XON/XOFF フロー制御		*/
					/* S0=1: 自動着信リング回数 = 1 回	*/

#define MODEM_CFG_PHONE_NUMBER	"090-xxxx-9242"

					/* 自構成情報の規定値			*/
#define DEF_LCP_LOCAL_CFGS	(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

					/* 相手に許す構成情報の規定値		*/
#define DEF_LCP_REMOTE_CFGS	(LCP_CFG_MRU|LCP_CFG_ACCM|LCP_CFG_MAGIC|LCP_CFG_ACCOMP|LCP_CFG_PCOMP|LCP_CFG_PAP)

/*
 *  認証に関する定義
 */

#define AUTH_CFG_CLIENT		   	/* 認証クライアントモードの時はコメントを外す。	*/
#define AUTH_CFG_SERVER			/* 認証サーバモードの時はコメントを外す。		*/

#define AUTH_LOCAL_USER		"h8"		/* 自ホストへのログイン認証ユーザ名	*/
#define AUTH_LOCAL_PASSWD	"3048f"		/* 自ホストへのログイン認証パスワード	*/
#define AUTH_REMOTE_USER	"pen3"		/* 相手へのログイン認証ユーザ名		*/
#define AUTH_REMOTE_PASSWD	"600MHz"	/* 相手へのログイン認証パスワード		*/

/*
 *  ARP に関する定義
 */

/*#define ARP_CFG_CALLBACK_DUPLICATED*/	/* IP アドレス重複検出コールバック関数を	*/
					/* 定義する場合はコメントを外す。		*/

/*
 *  ICMPv4/v6 に関する定義
 */

/*#define ICMP_CFG_CALLBACK_ECHO_REPLY*/	/* ICMP ECHO 応答を受信したとき呼出すコールバック関数を	*/
					/* 定義する場合はコメントを外す。			*/

/*
 *  ネットワークバッファ数の割り当て
 */

#ifdef SUPPORT_ETHER

/*
 *  イーサネットの場合のネットワークバッファ数の割り当て
 */

/*
 *  注意!!
 *
 *  NE2000 互換 NIC のディバイスドライバ（if_ed）の最低割当て長は
 *  60（アラインして 62）オクテットのため IF + IPv4 +TCP よりは
 *  64 オクテットのネットワークバッファの方が最適である。
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
#define NUM_MPF_NET_BUF_64	2	/* 64 オクテット	*/

#endif	/* #ifdef SUPPORT_INET4 */

#ifdef NUM_MPF_NET_BUF_128
#undef NUM_MPF_NET_BUF_128
#endif
#define NUM_MPF_NET_BUF_128	1	/* 128 オクテット	*/

#ifdef NUM_MPF_NET_BUF_256
#undef NUM_MPF_NET_BUF_256
#endif
#define NUM_MPF_NET_BUF_256	1	/* 256 オクテット	*/

#ifdef NUM_MPF_NET_BUF_512
#undef NUM_MPF_NET_BUF_512
#endif
#define NUM_MPF_NET_BUF_512	1	/* 512 オクテット	*/

#ifdef SUPPORT_INET4

#ifdef NUM_MPF_NET_BUF_IP_MSS
#undef NUM_MPF_NET_BUF_IP_MSS
#endif

#ifdef USE_TCP_MSS_SEG
#define NUM_MPF_NET_BUF_IP_MSS	2	/* IF + 576 オクテット	*/
#else
#define NUM_MPF_NET_BUF_IP_MSS	0	/* IF + 576 オクテット	*/
#endif

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef NUM_MPF_NET_BUF_1024
#undef NUM_MPF_NET_BUF_1024
#endif
#define NUM_MPF_NET_BUF_1024	1	/* 1024 オクテット	*/

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
#define NUM_MPF_NET_BUF_IF_PDU	0	/* IF 最大 PDU サイズ	*/
#else
#define NUM_MPF_NET_BUF_IF_PDU	3	/* IF 最大 PDU サイズ	*/
#endif

#endif	/* of #ifdef SUPPORT_ETHER */

#endif /* _TINET_APP_CONFIG_H_ */
