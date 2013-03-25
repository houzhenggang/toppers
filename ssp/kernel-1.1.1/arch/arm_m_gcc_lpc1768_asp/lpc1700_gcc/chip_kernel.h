/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by TOPPERS/ASP for LPC project
 *              http://sourceforge.jp/projects/toppersasp4lpc/
 *
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
 * \addtogroup TOPPERS_CHIP
 * \{
 */


/**
 * \file chip_kernel.h
 * \brief kernel.hのターゲット依存部（NXP LPC17XX汎用）
 * \details
 *  このインクルードファイルは，kernel.hでインクルードされる．他のファ
 *  イルから直接インクルードすることはない．このファイルをインクルード
 *  する前に，t_stddef.hがインクルードされるので，それらに依存してもよ
 *  い．
 */

#ifndef TOPPERS_CHIP_KERNEL_H
#define TOPPERS_CHIP_KERNEL_H

/**
 * \brief 割込み優先度の最小値（最高値）。
 * \details
 * SoC設計者によるCORTEX-M3のコンフィギュレーションに従った値を
 * 指定する。 prc_user.txtによれば、CORTEX-M3においてはTMIN_INTPRIの値は
 * \code
 *    -(2^(TBITW_IPRI)) + (2^TBITW_SUBIPRI)) 〜 -1
 * \endcode
 * の範囲内にしなければならない。UM10360によれば、LPC1768は
 * TBIW_IPRI = 5, TBITW_SUIPRI = 0となるため、上記範囲は
 * \code
 *    -32 + 1 〜 -1
 * \endcode
 * となる。そこで、lpc1700_gcc依存部では、TMIN_INTPRIを-31と定めている。
 *
 */
#define TMIN_INTPRI		(-31)

/**
 * \brief サポートする機能の定義
 * \details
 * get_utim()関数をアプリケーションに提供することを宣言する。
 */
#define TOPPERS_SUPPORT_GET_UTM		/* get_utmをサポートする */

/**
 * \brief タイムティックの周期の分子
 * \details
 * porting.txtの５章で要請されており、タイマーの割り込み周期から
 * 1mSのシステム・タイマーを作るために宣言する。タイマーの割り込み
 * 周期が1mSなら、1でいい。
 */
#define TIC_NUME			1U

/**
 * \brief タイムティックの周期の分母
 * \details
 * porting.txtの５章で要請されており、タイマーの割り込み周期から
 * 1mSのシステム・タイマーを作るために宣言する。タイマーの割り込み
 * 周期が1mSなら、1でいい。
 */
#define TIC_DENO			1U

/*
 *  プロセッサで共通な定義
 */
#include "arm_m_gcc/common/core_kernel.h"

#endif /* TOPPERS_CHIP_KERNEL_H */

/**
 * \}
 */


