/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
 *  Copyright (C) 2009-     by Monami Software Limited Partnership, JAPAN
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
 *
 *
 */

/*
 *	ターゲットシステム依存モジュール（ADSP-BF527用）
 */

#include "jsp_kernel.h"
#include <sil.h>

#ifdef __GNUC__
#include "../cdefBF527.h"		/* gnu tool chain */
#elif defined(__ECC__)
#include <cdefBF527.h>				/* VisualDSP++ */
#include <sys/exception.h>
#include <ccblkfn.h>
#include <sysreg.h>
#else
#error "Compiler is not supported"
#endif




/*
 *  ターゲットシステム依存の初期化
 */
void
sys_initialize()
{

	/*
	 *  PLLの設定
	 *
	 */
	/*
	 *  SSELVAL, CSELVALはboard_config.hにて定義。
	 */
#ifndef FORCE_PLL_INITIALIZE
	 	// PLLが初期値のままであり、かつ、SDRAMが利用中でなければPLLを初期化する
	 if ( ( *pPLL_CTL == 0x0A00 ) && ( !(*pEBIU_SDBCTL & EBE ) ) )
#endif
	 {

		*pSIC_IWR0 = IWR_ENABLE(0);				// PLLのみIWRを許す
		*pSIC_IWR1 = IWR_DISABLE_ALL;
		*pPLL_LOCKCNT = 0x0200; /* anomaly 05000430 */
#if CSELVAL == 1
		*pPLL_DIV = CSEL_DIV1 | SET_SSEL(SSELVAL);
#elif CSELVAL == 2
		*pPLL_DIV = CSEL_DIV2 | SET_SSEL(SSELVAL);
#elif CSELVAL == 4
		*pPLL_DIV = CSEL_DIV4 | SET_SSEL(SSELVAL);
#elif CSELVAL == 8
		*pPLL_DIV = CSEL_DIV8 | SET_SSEL(SSELVAL);
#else
#error Wrong CSELVAL. Must be one of 1,2,4,8.
#endif

		*pPLL_CTL = MSELVAL << 9;

		asm("cli r0; csync; idle; sti r0;": : :"R0");
		*pSIC_IWR0 = IWR_ENABLE_ALL;
		*pSIC_IWR1 = IWR_ENABLE_ALL;
	}

}

        // priority_maskは、event順位0..15に応じた
        // 割り込み要求のビットマップを保持する。
IMS priority_mask[16]={
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x0007800000003FFFULL,
0x000000000000C000ULL,
0x00000000000F0000ULL,
0x00F8000003F00000ULL,
0x00000000FC000000ULL,
0x000003FF00000000ULL,
0x00007C0000000000ULL,
0x00000000,
0x00000000
};


/*
* SIC_IARxを解析して、イベント順位ごとに割り当てられている割り込み
* のビットマップを作る。SIC_IARxのフィールド値は優先順位-7なので
* その分補正する。
*/
#define INSTALL_PRIORITY    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                         /* IARから優先順位を取り出す */ \
        priority_mask[priority + 7] |= device;        /* 取り出した優先順位に基づきデバイスを登録 */ \
        device <<= 1;                                 /* 次のデバイス */ \
        iar >>= 4;                                    /* 次のIARフィールド */ \
    }

void make_priority_mask( void )
{
	unsigned int i, priority, iar;
	IMS device;


	/*
 *  割り込み順位ごとのISRビットマップの作成
 *  SIC_IARxの設定はこの部分より前に済ませること
 */

        // priority_maskは、event順位0..15に応じた
        // 割り込み要求のビットマップを保持する。
 	for ( i=0; i<16; i++ ){
 		priority_mask[i] = 0;
 	}

	device = 1;
	iar = *pSIC_IAR0;
	INSTALL_PRIORITY

	iar = *pSIC_IAR1;
    INSTALL_PRIORITY

	iar = *pSIC_IAR2;
    INSTALL_PRIORITY

    iar = *pSIC_IAR3;
    INSTALL_PRIORITY

	iar = *pSIC_IAR4;
	INSTALL_PRIORITY

	iar = *pSIC_IAR5;
	INSTALL_PRIORITY

	iar = *pSIC_IAR6;
	INSTALL_PRIORITY
}


/*
 * 割り込みの許可、禁止
 *
 */
ER ena_int( INTNO intno )
{
	unsigned int mask;

	if ( intno >= DEVICE_INTERRUPT_COUNT )
		return ( E_PAR );
	else {
		SIL_PRE_LOC;

		SIL_LOC_INT();			// 管理外割り込みまで禁止する
		if (intno < 32) {
			mask = 1 << intno;
			*pSIC_IMASK0 |= mask;
		} else {
			mask = 1 << (intno - 32);
			*pSIC_IMASK1 |= mask;
		}
		asm volatile( "ssync;" );
		SIL_UNL_INT();			// 割り込み再許可
		return (0);
	}
}

/*
 * dis_int()は、この実装ではSIC_IMASKの指定ビットをクリアする。
 *
 * しかし、SIC_IMASKのクリアはアプリケーション実行中には危険であり、
 * Blackfinのマニュアルでも婉曲的に禁止されている。そのため、TOPPERS/JSP for Blackfin
 * では、この関数を実装しない。
 *
 ER dis_int( INTNO intno )
{
	unsigned int mask;

	if ( intno >= DEVICE_INTERRUPT_COUNT )
		return ( E_PAR );
	else {
		if (intno < 32) {
			mask = 1 << intno;
			mask = ~mask;
			*pSIC_IMASK0 &= mask;
		} else {
			mask = 1 << (intno - 32);
			mask = ~mask;
			*pSIC_IMASK1 &= mask;
		}
		return (0);
	}
}
*/

/*
 * chg_ims()は、この実装ではSIC_IMASKを変更する。
 *
 * しかし、SIC_IMASKのビットのクリアはアプリケーション実行中には危険であり、
 * Blackfinのマニュアルでも婉曲的に禁止されている。そのため、TOPPERS/JSP for
 * Blackfinでは、この関数を実装しない。
 * ER chg_ims( IMS ims )
{
	*pSIC_IMASK0 = ims;
	*pSIC_IMASK1 = ims >> 32;
	return( 0 );
}
*/

extern ER get_ims( IMS * p_ims )
{
	SIL_PRE_LOC;
	SIL_LOC_INT();
	*p_ims = *pSIC_IMASK0 | (UD)*pSIC_IMASK1 << 32;
	SIL_UNL_INT();
	return( 0 );;
}


/*
 *  割り込みをデバイスに割り当てる
 */
void device_dispatcher(  unsigned int priority, unsigned int imask )
{
	unsigned int candidates, device;
	unsigned int offset;

	candidates = (UW)(priority_mask[priority] >> 32) & *pSIC_ISR1 & *pSIC_IMASK1;	// 現在のプライオリティに相当する割込み源を特定する
	if (candidates != 0) {
		offset = 32;
	} else {
		candidates = (UW)priority_mask[priority] & *pSIC_ISR0 & *pSIC_IMASK0;
		offset = 0;
	}

	asm volatile("sti %0;": : "d"(imask) );

	if ( ! candidates ) // 割り込み源が特定できないなら、コア由来である
	{
		if ( priority == ik_hardware_err)
			dev_vector[INHNO_HW_ERROR]();
		else
			if ( priority == ik_timer)
			dev_vector[INHNO_TIMER]();
		else
			dev_vector[INHNO_RAISE]();		//　ソフトウェア割り込み

	}
	else
	{
		if ( candidates & 0x80000000 )
			device = 31;
		else
		{
#ifdef __GNUC__
	asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates): "R1"  );
#elif defined(__ECC__)
	asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates ) );
#else
#error "Compiler is not supported"
#endif
			device = 30 - device;		// bit mask is converted to bit number
		}
		dev_vector[device + offset]();
	}
}



/*
 *  ターゲットシステムの終了
 */
void
sys_exit()
{
	while(1)
		;
}

/*
 *  ターゲットシステムの文字出力
 */
void
sys_putc(char c)
{
}



