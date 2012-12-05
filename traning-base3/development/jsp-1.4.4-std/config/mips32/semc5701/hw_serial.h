/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 */

/*
 *	シリアルI/Oデバイス（SIO）ドライバ（CBUS UART (tty2)用）
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include <cbus_uart.h>		/* siopcb, cbus_uart_openflag */

/*
 *  SIOの割込みハンドラのベクタ番号
 */
#define INHNO_SIO1		INTNO_SERIAL0

/*
 *  SIOドライバの初期化ルーチン
 */
#define	sio_initialize		cbus_uart_initialize

/*
 *  カーネル起動時用の初期化 (sys_putcで利用)
 */
#define sio_init		cbus_uart_init

#ifndef _MACRO_ONLY

/*
 *  シリアルI/Oポートのオープン
 */
Inline SIOPCB *
sio_opn_por(ID siopid, VP_INT exinf)
{
	SIOPCB	*siopcb;

	/*
	 *  デバイス依存のオープン処理．
	 */
	siopcb = cbus_uart_opn_por(siopid, exinf);

	/*
	 *  シリアルI/O割込みの割込みレベルを設定し，マスクを解除する．
	 */
	all_set_ilv( INTNO_SERIAL0, &((IPM) IPM_SCC0) );
							/* 割込みレベル設定 */
	x_enable_int(INTNO_SERIAL0);
							/* マスク設定処理 */

	return(siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
Inline void
sio_cls_por(SIOPCB *siopcb)
{
	/*
	 *  デバイス依存のクローズ処理．
	 */
	cbus_uart_cls_por(siopcb);

	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	x_disable_int(INTNO_SERIAL0);
							/* マスク設定処理 */
}

#endif /* _MACRO_ONLY */

/*
 *  SIOの割込みハンドラ
 */
#define	sio1_handler		cbus_uart_uart0_isr

/*
 *  シリアルI/Oポートへの文字送信
 */
#define	sio_snd_chr		cbus_uart_snd_chr

/*
 *  シリアルI/Oポートへの文字送信（ポーリング）
 */
#define	sio_snd_chr_pol		cbus_uart_putchar_pol

/*
 *  シリアルI/Oポートからの文字受信
 */
#define	sio_rcv_chr		cbus_uart_rcv_chr

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
#define	sio_ena_cbr		cbus_uart_ena_cbr

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
#define	sio_dis_cbr		cbus_uart_dis_cbr

/*
 *  シリアルI/Oポートからの送信可能コールバック
 */
#define	sio_ierdy_snd		cbus_uart_ierdy_snd

/*
 *  シリアルI/Oポートからの受信通知コールバック
 */
#define	sio_ierdy_rcv		cbus_uart_ierdy_rcv

#endif /* _HW_SERIAL_H_ */
