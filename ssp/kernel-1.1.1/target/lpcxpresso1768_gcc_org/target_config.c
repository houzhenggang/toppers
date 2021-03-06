/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by TOPPERS/ASP for LPC project
 *              http://sourceforge.jp/projects/toppersasp4lpc/
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
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
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */
/**
 * \addtogroup TOPPERS_TARGET
 * \{
 */

/**
 * \file target_config.c
 * \brief カーネル実装のターゲット依存モジュール（NXP LPC1768用）
 * \details
 * カーネル構築に必要でターゲットに依存する定義をこのファイルで行う。
 */
#include "kernel_impl.h"
#include <sil.h>
#include "lpcxpresso1768.h"
#include "target_serial.h"
#include "target_syssvc.h"

/**
 * \brief UART0のTX信号(P0.2)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART0_TX	(0x01<<4)

/**
 * \brief UART0のRX信号(P0.3)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART0_RX	(0x01<<6)

/**
* \brief UART1のTX信号(P2.0)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART1_TX	(0x02)

/**
 * \brief UART1のRX信号(P2.1)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART1_RX	(0x02<<2)

/**
 * \brief UART2のTX信号(P0.10)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART2_TX	(0x01<<20)

/**
 * \brief UART2のRX信号(P0.11)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART2_RX	(0x01<<22)

/**
 * \brief UART3のTX信号(P0.0)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART3_TX	(0x02)

/**
 * \brief UART3のRX信号(P0.1)にピンを割り付けるためのビットフィールド定義
 *
 */
#define PINSEL_UART3_RX	(0x02<<2)

/**
 * \brief PCOMPレジスタのUART2ビット
 * \details
 * UART2は、デフォルトでは電源オフなので、使う前にオンにしなければならない。
 *
 */
#define PCUART2 (1<<24)

/**
 * \brief PCOMPレジスタのUART3ビット
 * \details
 * UART3は、デフォルトでは電源オフなので、使う前にオンにしなければならない。
 *
 */
#define PCUART3 (1<<25)

/**
 * \brief ターゲット依存部　初期化処理
 * \details
 * sta_ker() の中から呼び出されてターゲットのハードウェアの初期化を行う。この関数の中では
 * PLLの初期化やペリフェラル・ピンの初期化などを行う。
 */
void target_initialize(void)
{

	/*
	 *  チップ依存部の初期化。この呼び出しは削除してはいけない。
	 */
	chip_initialize();

	/* Flash Accelerator を初期化。100MHz動作に対応 */
	LPC_SC->FLASHCFG = 0x403a;

	/*
	 *  プロセッサクロックの初期化
	 */
		// PLLの設定 (2 * 50 * 4MHz)/1/4 = 100MHz
	initPLL0(
			eIrc, 	// pllClockSource_type 	clkSrc,
			0,		// unsigned int 			isMainOsc20MHzMore,
			1,		// unsigned int			N,
			50,		// unsigned int			M,
			4		// unsigned int			cpuClkDiv
		);


	/*
	 *  SIOポートの初期化
	 *
	 *  以下のコードは、SIO_PORTIDの値に応じて自動的にピン・コンフィギュレーションを行うが、
	 *  これはLPC1768の一部機能に過ぎないことに注意。LPC1768は、UART1や2の割り当て先を複数
	 *  種類持っている。以下のコードはそれらのうちの一つに対応しているにすぎない。必要に応じて
	 *  アプリケーション・プログラマが書き換えて使うこと。
	 */
#if (SIO_PORTID==1)
	/* Port0.2,3 ピンをUART0に割り当てる。*/
	LPC_PINCON->PINSEL0 |= PINSEL_UART0_TX | PINSEL_UART0_RX;
#elif (SIO_PORTID==2)
	/* Port2.0,1 ピンをUART1に割り当てる。*/
	LPC_PINCON->PINSEL4 |= PINSEL_UART1_TX | PINSEL_UART1_RX;
#elif (SIO_PORTID==3)
	/* Port0.10,11 ピンをUART2に割り当てる。*/
	LPC_PINCON->PINSEL0 |= PINSEL_UART2_TX | PINSEL_UART2_RX;
	/* UART2 の電源をオンにする */
	LPC_SC->PCONP |=  PCUART2;
#elif (SIO_PORTID==4)
	/* Port0.0,1 ピンをUART3に割り当てる。*/
	LPC_PINCON->PINSEL0 |= PINSEL_UART3_TX | PINSEL_UART3_RX;
	/* UART3 の電源をオンにする */
	LPC_SC->PCONP |=  PCUART3;
#else
#error "SIO_PORTID NOT Supported"
#endif


	/*
	 *  バナー出力用のシリアル初期化
	 */
	target_uart_init(SIO_PORTID);
}




/**
 * \brief ターゲット依存部　終了処理
 * \details
 * システム終了時にカーネルから呼ばれる。この関数は呼び出し元に戻らない。
 */
void target_exit(void)
{
	/* チップ依存部の終了処理 */
	chip_exit();

	while(1)
		;
}

/**
 * \brief システムログの低レベル出力のための文字出力
 * \param c 出力キャラクタ
 * \details
 * コンソールに１文字出力する。チップ依存部が供給する出力関数をそのまま利用する。
 */
void target_fput_log(char_t c)
{
	chip_fput_log(c);
}



/**
 * \}
 */

