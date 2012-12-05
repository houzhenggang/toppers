/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: lpc23xx_mci.h,v 1.1 2010/08/12 17:38:40 roi Exp $
 */


/*
 *  MCI�ǥХ����ɥ饤�С�lpc23xx�ѡ�
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
