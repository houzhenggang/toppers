/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2006-2011 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: $
 */

#ifndef _TINET_SYS_CONFIG_H_
#define _TINET_SYS_CONFIG_H_

/*
 *  データリンク層 (ネットワークインタフェース) に関する定義
 */

/*
 *  NIC (EMAC 互換) に関する定義
 */
#define TMO_IF_ED_GET_NET_BUF	1	/* [ms]、受信用 net_buf 獲得タイムアウト	*/
					/* [s]、 送信タイムアウト			*/
#define TMO_IF_ED_XMIT		(2*IF_TIMER_HZ)

/*#define IF_ED_CFG_ACCEPT_ALL		 マルチキャスト、エラーフレームも受信するときはコメントを外す。*/

/*
 *  イーサネット出力時に、NIC で net_buf を開放する場合に指定する。
 *
 *  注意: 以下の指定は、指定例であり、if_ed では、
 *        開放しないので、以下のコメントを外してはならない。
 */

/*#define ETHER_NIC_CFG_RELEASE_NET_BUF*/

/*
 *  EMACに関する定義
 */

#define INHNO_ETHER		INTNO_ETHER		/* IRQ5 */

#define LPC_ETHER_ADDR_LEN	6			/* Ethernet (MAC) Addressの長さ	*/

/* MAC用のクロック設定値 */
#define PCONP_EMAC_CLOCK	0x40000000

/* EMAC MODULE ID	*/
#define PHILIPS_EMAC_MODULE_ID	((0x3902 << 16) | 0x2000)

/*
 *  PHYに関する定義
 */
#define PHY_ADDRNO      1				/* PHYアドレス番号 */
#define USE_RMII						/* PHYとの通信にRMIIを使用 */

#ifndef _MACRO_ONLY

#define ed_ena_inter(ipm)	chg_ipm(ipm)

/*
 *  データ
 */
extern UB lp23xx_macaddr[LPC_ETHER_ADDR_LEN];

/*
 *  関数
 */
void tinet_sys_initialize(void);


#endif	/* of #ifndef _MACRO_ONLY */

#endif /* _TINET_SYS_CONFIG_H_ */
