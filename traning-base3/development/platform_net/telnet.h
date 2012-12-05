/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: telnet.h,v 1.0 2010/11/28 07:28:04 roi Exp $
 */

#ifndef _TELNET_H_
#define _TELNET_H_

#include <t_services.h>

/* 
 *  サーバ試験プログラム
 */

#define TCP_TELNET_SRV_STACK_SIZE	1024	/* TCP TELNET サーバタスクのスタックサイズ		*/

#ifdef MAIN_PRIORITY
#define SRV_PRIORITY    (MAIN_PRIORITY+1)
#else
#define SRV_PRIORITY    6
#endif

/*
 *  使用する API の選択
 */

#define USE_TCP_NON_BLOCKING
#define USE_COPYSAVE_API

/*
 *  TCP 送受信ウインドバッファサイズ
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
 *  TCP 送受信バッファ
 */

extern UB tcp_telnet_srv_swbuf[];
extern UB tcp_telnet_srv_rwbuf[];

/*
 *  タスク
 */

extern void tcp_telnet_srv_task(VP_INT exinf);

/*
 *  関数
 */

extern ER callback_nblk_tcp_telnet_srv (ID cepid, FN fncd, VP p_parblk);
extern void macaddr_init(VP_INT exinf);

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _TELNET_H_ */
