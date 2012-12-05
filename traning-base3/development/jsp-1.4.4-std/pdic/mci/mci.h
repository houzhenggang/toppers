/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
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
 *  @(#) $Id: mci.h,v 1.1 2011/02/13 21:18:56 roi Exp $
 */

#ifndef _MCI_H_
#define _MCI_H_


#define INHNO_MMC           INTNO_MMC

#define CMD_SHORTRESP       (1<<6)	/* short response */
#define CMD_LONGRESP        (1<<7)	/* long response */
#define CMD_SLONGRESP       (CMD_SHORTRESP|CMD_LONGRESP)
#define CMD_TIMEOUT         (1<<8)	/* timeout request bit */
#define CMD_SETLAST         (1<<10)
#define CMD_MASK            0xFFFF
#define CMD_IGNOREIRES      (1<<16)
#define CMD_INDEX           0x003F

/*
 *  SD/MMC コマンドリスト
 */
#define MCI_CMD0			(0x0000)								/* GO_IDLE_STATE(MMC) or RESET(SD) */
#define MCI_CMD1			(0x0001|CMD_SHORTRESP|CMD_IGNOREIRES)	/* SEND_OP_COND(MMC) or CMD1(SD) */
#define MCI_CMD2			(0x0002|CMD_SLONGRESP|CMD_IGNOREIRES)	/* ALL SEND_CID */
#define MCI_CMD3			(0x0003|CMD_SHORTRESP)					/* SET_RELATE_ADDR */
#define MCI_CMD6			(0x0006|CMD_SHORTRESP)
#define MCI_CMD7			(0x0007|CMD_SHORTRESP)					/* SELECT/DESELECT_CARD */
#define MCI_CMD9			(0x0009|CMD_SLONGRESP|CMD_IGNOREIRES)	/* SEND_CSD */
#define MCI_CMD12			(0x000C|CMD_SHORTRESP)					/* Stop either READ or WRITE operation */
#define MCI_CMD13			(0x000D|CMD_SHORTRESP)					/* SEND_STATUS */
#define MCI_CMD16			(0x0010|CMD_SHORTRESP)					/* SET_BLOCK_LEN */
#define MCI_CMD17			(0x0011|CMD_SHORTRESP)					/* READ_SINGLE_BLOCK */
#define MCI_CMD24			(0x0018|CMD_SHORTRESP)					/* WRITE_BLOCK */
#define MCI_ACMD41			(0x0029|CMD_SHORTRESP|CMD_IGNOREIRES)	/* ACMD41 for SD card */		
#define MCI_CMD55			(0x0037|CMD_SHORTRESP)					/* APP_CMD, the following will a ACMD */

#define RES_CMD1            (MCI_CMD1 & CMD_INDEX)
#define RES_CMD12           (MCI_CMD12 & CMD_INDEX)
#define RES_ACMD41          (MCI_ACMD41 & CMD_INDEX)

#define OCR_INDEX			0x00FF8000

#define CARD_STATUS_ACMD_ENABLE		(1<<5)
#define CARD_STATUS_RDY_DATA		(1<<8)
#define CARD_STATUS_CURRENT_STATE	(0x0F<<9)
#define CARD_STATUS_ERASE_RESET		(1<<13)

#define SLOW_RATE			1
#define NORMAL_RATE			2

#define SD_1_BIT 			0
#define SD_4_BIT			1

#define MMC_CARD			1
#define SD_CARD				2

#define MCI_NOTEND          0
#define MCI_END             1
#define MCI_ERREND          2

/* Error code on the command response. */
#define INVALID_RESPONSE	0xFFFFFFFF

#define SDMODE_PROTECT      (1<<0)
#define SDMODE_WRITE        (1<<7)

#ifndef _MACRO_ONLY

/*
 *  MCI-I/Oポートの共有管理領域
 */
typedef struct mci_port_common_block {
	UINT    base;
	UINT    status;
	UINT    mask;
	UINT    cardRCA;
	UINT    cardType;
	UB      retryCount;
	UB      endFlag;
	UH      mode;
}MCIPCMB;

/*
 *  MCI-I/Oポート管理ブロックの定義
 */
typedef struct mci_port_control_block	MCIPCB;

extern void  mci_init(VP_INT exinf);
extern void  dma_init(VP_INT exinf);
extern void  mci_isr0(void);
extern void  dma_isr0(void);

#endif	/* _MACRO_ONLY */

#if defined(LPC2388)
#include "lpc23xx_mci.h"
#else
#error "not support mci board."
#endif

#endif /* end _MCI_H_ */
