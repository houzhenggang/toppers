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

#define _MACRO_ONLY

#include "jsp_kernel.h"
#include "offset.h"		/* INT_TABLE_intmaskのために必要 */

	.set at
	.set noreorder

/*============================================================================*/

/* 割込み処理に関する、割込み要因の判断分岐処理のシステム依存部 */

	.section .text
	.align 2

	.global proc_interrupt_sys

	/*  呼び出されたとき、       */
	/*    a1にステータスレジスタ */
	/*    a2に原因レジスタ       */
	/*  の値が入っている         */

proc_interrupt_sys:
	and     t2, a2, a1          /*  割込み要求ビットにマスクをかける  */
	sll t1, t2, 16
	clz t1, t1 /* t1 = (t2 & Cause_IP7) ? 0 : (t2 & Cause_IP6) ? 1 : (t2 & Cause_IP5) ? 2 : ... */
	li t0, 7
	subu t0, t0, t1
	bltz t0, proc_interrupt_sys_0
	nop

/*  ステータスレジスタのマスク設定とC言語ルーチン呼び出し  */
/*    t0に割込み要因番号が設定された状態でここに来る  */
	la      t3, int_table   /*  擬似ベクタアドレス  */
	sll     t4, t0, 3       /*  割込み要因番号を8倍
				      TNT_TABLE型は、
					ハンドラのアドレス(4バイト)
					＋MIPS32コアの割込みマスク(4バイト)
				      の、合計8バイト。 */
	addu     t5, t3, t4      /*  ベクタアドレスを算出  */
	lw      t6, INT_TABLE_intmask(t5)
           		    	/*  IPM(割込み許可ビット)読み出し。*/
	and t6, t6, a1
	ori t4, a1, (SR_IM | SR_EXL | SR_IE)
	xori t4, t4, (SR_IM | SR_EXL | SR_IE)
	or t6, t6, t4
	mtc0 t6, Status /* EXL = 0, IE = 0 */
	ori t6, t6, SR_IE
	lw      t7, (t5)        /*  C言語ルーチン先頭アドレス読み出し  */

	jalr    t7          /*  C言語ルーチン呼び出し  */
	mtc0 t6, Status /* EXL = 0, IE = 1 */

	mfc0    t0, Status
	ori t0, t0, SR_IE
	xori t0, t0, SR_IE
	mtc0 t0, Status /* IE = 0 */

	/*  CP0ハザードのための時間稼ぎ  */
#ifdef NOP_FOR_CP0_HAZARD
	NOP_FOR_CP0_HAZARD
#endif /* NOP_FOR_CP0_HAZARD */

proc_interrupt_sys_0:
	j	join_interrupt_and_exception
	nop

