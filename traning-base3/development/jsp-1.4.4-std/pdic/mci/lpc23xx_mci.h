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
 *  @(#) $Id: lpc23xx_mci.h,v 1.1 2010/08/12 17:38:40 roi Exp $
 */


/*
 *  MCIデバイスドライバ（lpc23xx用）
 */

#ifndef _LPC23XX_MCI_H_
#define _LPC23XX_MCI_H_

#include "lpc23xx_gpdma.h"

								   /* MCI clk freq = Pclk/(2* (Clkdiv +1) */
#define MCLKDIV_SLOW		0x60-1 /* 59 = 400,000Hz -> @48Mhz/(2*60) */ 
#define MCLKDIV_NORMAL		0x4-1  /* 3 = 6Mhz -> @48Mhz/(2*4) */

#define DATA_TIMER_VALUE	(1<<16)


#define DATA_BLOCK_LEN		9	/* Block size field in DATA_CTRL */
#define BLOCK_LENGTH		(1<<DATA_BLOCK_LEN)

#define BUS_WIDTH_1BIT		0
#define BUS_WIDTH_4BITS		10

/*
 *  MCI Status register bit information
 */
#define MCI_CMD_CRC_FAIL	(1<<0)
#define MCI_DATA_CRC_FAIL	(1<<1)
#define MCI_CMD_TIMEOUT		(1<<2)
#define MCI_DATA_TIMEOUT	(1<<3)
#define MCI_TX_UNDERRUN		(1<<4)
#define MCI_RX_OVERRUN		(1<<5)
#define MCI_CMD_RESP_END	(1<<6)
#define MCI_CMD_SENT		(1<<7)
#define MCI_DATA_END		(1<<8)
#define MCI_START_BIT_ERR	(1<<9)
#define MCI_DATA_BLK_END	(1<<10)
#define MCI_CMD_ACTIVE		(1<<11)
#define MCI_TX_ACTIVE		(1<<12)
#define MCI_RX_ACTIVE		(1<<13)
#define MCI_TX_HALF_EMPTY	(1<<14)
#define MCI_RX_HALF_FULL	(1<<15)
#define MCI_TX_FIFO_FULL	(1<<16)
#define MCI_RX_FIFO_FULL	(1<<17)
#define MCI_TX_FIFO_EMPTY	(1<<18)
#define MCI_RX_FIFO_EMPTY	(1<<19)
#define MCI_TX_DATA_AVAIL	(1<<20)
#define MCI_RX_DATA_AVAIL	(1<<21)

#define CMD_INT_MASK      (MCI_CMD_CRC_FAIL | MCI_CMD_TIMEOUT | MCI_CMD_RESP_END \
			             | MCI_CMD_SENT     | MCI_CMD_ACTIVE)

#define DATA_ERR_INT_MASK	(MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_TX_UNDERRUN \
			               | MCI_RX_OVERRUN | MCI_START_BIT_ERR)

#define ACTIVE_INT_MASK ( MCI_TX_ACTIVE | MCI_RX_ACTIVE)

#define FIFO_INT_MASK		(MCI_TX_HALF_EMPTY | MCI_RX_HALF_FULL \
                           | MCI_TX_FIFO_FULL  | MCI_RX_FIFO_FULL \
			               | MCI_TX_FIFO_EMPTY | MCI_RX_FIFO_EMPTY \
						   | MCI_DATA_BLK_END )

#define	FIFO_TX_INT_MASK (MCI_TX_HALF_EMPTY )
#define	FIFO_RX_INT_MASK (MCI_RX_HALF_FULL  )

#define DATA_END_INT_MASK    (MCI_DATA_END | MCI_DATA_BLK_END)

#define ERR_TX_INT_MASK (MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_TX_UNDERRUN | MCI_START_BIT_ERR)
#define ERR_RX_INT_MASK (MCI_DATA_CRC_FAIL | MCI_DATA_TIMEOUT | MCI_RX_OVERRUN  | MCI_START_BIT_ERR)

#ifndef _MACRO_ONLY

extern void   lpc23xx_mci_set_mask(MCIPCB *pmci, UW set, UW reset);
extern void   lpc23xx_mci_set_clock(MCIPCB *pmci, W clockrate );
extern ER     lpc23xx_mci_snd_acmd(MCIPCB *pmci);
extern ER     lpc23xx_mci_snd_cmd(MCIPCB *pmci, W cmd, W arg);
extern ER     lpc23xx_mci_get_resp(MCIPCB *pmci,  W cmd, W *presp, W *pcmdrespstatus);

extern MCIPCB *lpc23xx_mci_ini_por(void);
extern ER_ID  lpc23xx_mci_opn_por(MCIPCB *pmci);
extern ER     lpc23xx_mci_cls_por(MCIPCB *pmci);
extern ER     lpc23xx_mci_wri_blk(MCIPCB *pmci, B *buf, W blockNum);
extern ER     lpc23xx_mci_rea_blk(MCIPCB *pmci, B *buf,W blockNum);
extern ER     lpc23xx_mci_wai_trn(MCIPCB *pmci, W timeout);

#endif

#endif /* _LPC23XX_MCI_H_ */
