/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: lpc23xx_gpdma.h,v 1.1 2010/07/25 10:38:40 roi Exp $
 */


/*
 *  LPC23XX GPDMA用インクルードファイル
 */

#ifndef _LPC23XX_GPDMA_H_
#define _LPC23XX_GPDMA_H_

#define INHNO_DMA       INTNO_GPDMA

#define NUM_DMA_CHANNEL 2
#define DMA_MCI			0x7FD01000

/* DMA mode */
#define M2MD			0x00
#define M2PD			0x01
#define P2MD			0x02
#define P2PD			0x03
#define M2MP            0x04
#define M2PP            0x05
#define P2MP            0x06
#define P2PP            0x07

/* Peripheral */
#define PDUMMY          0x00
#define PSSP0TX         0x00
#define PSSP0RX         0x01
#define PSSP1TX         0x02
#define PSSP1RX         0x03
#define PMCI            0x04
#define PI2SC0          0x05
#define PI2SC1          0x06

#ifndef _MACRO_ONLY

extern void dma_init(VP_INT exinf);
extern void dma_isr0(void);

extern ER lpc23xx_set_trn(UB cnum, UB mode, UW src, UW dst, UW size );
extern ER lpc23xx_set_cfg(UB cnum, UB sp, UB dp, UB mode);


#endif /* _MACRO_ONLY */
#endif /* _LPC23XX_GPDMA_H_ */
