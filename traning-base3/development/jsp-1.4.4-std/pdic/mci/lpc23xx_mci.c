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
 *  @(#) $Id: lpc23xx_mci.c,v 1.1 2010/08/12 17:18:56 roi Exp $
 */

/*
 *    LPC23XX��MCI�ǥХ����ɥ饤��
 */

#include <s_services.h>
#include <string.h>
#include "mci.h"

#ifdef MCI_FIFOMODE
#define lpc23xx_mci_txenable(p)     lpc23xx_mci_set_mask(p, (FIFO_TX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_TX_INT_MASK), 0)
#define lpc23xx_mci_txdisable(p)    lpc23xx_mci_set_mask(p, 0, (FIFO_TX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_TX_INT_MASK))
#define lpc23xx_mci_rxenable(p)     lpc23xx_mci_set_mask(p, (FIFO_RX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_RX_INT_MASK), 0)
#define lpc23xx_mci_rxdisable(p)    lpc23xx_mci_set_mask(p, 0, (FIFO_RX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_RX_INT_MASK))
#else
#define lpc23xx_mci_txenable(p)     lpc23xx_mci_set_mask(p, (DATA_END_INT_MASK)|(ERR_TX_INT_MASK), 0)
#define lpc23xx_mci_txdisable(p)    lpc23xx_mci_set_mask(p, 0, (DATA_END_INT_MASK)|(ERR_TX_INT_MASK))
#define lpc23xx_mci_rxenable(p)     lpc23xx_mci_set_mask(p, (DATA_END_INT_MASK)|(ERR_RX_INT_MASK), 0)
#define lpc23xx_mci_rxdisable(p)    lpc23xx_mci_set_mask(p, 0, (DATA_END_INT_MASK)|(ERR_RX_INT_MASK))
#endif

struct mci_port_control_block {
	MCIPCMB com;

	char    *dmaaddr;
	char    *trnaddr;
	UINT    TxBlockCounter;
	UINT    RxBlockCounter;

	UINT    DataEndCount;
	UINT    DataBlockEndCount;

	UH      cmdCrcFailCount;
	UH      cmdTimeoutCount;
	UH      cmdRespEndCount;
	UH      cmdSentCount;
	UH      cmdActiveCount;

	UH      dataCrcFailCount;
	UH      dataTimeoutErrorCount;
	UH      dataTxUnderrunErrorCount;
	UH      dataRxOverrunErrorCount;
	UH      dataStartBitErrorCount;
};

static MCIPCB Mci_Control_Block;

/*
 * MCI-I/O����ߵ��Ķػ�����
 */
void lpc23xx_mci_set_mask(MCIPCB *pmci, UW set, UW reset)
{
	pmci->com.mask |= set;
	pmci->com.mask &= ~reset;
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_MASK0), pmci->com.mask);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_MASK1), pmci->com.mask);
}

/*
 *  ����å�����
 */
void lpc23xx_mci_set_clock(MCIPCB *pmci, W ClockRate)
{
	UW ClkValue = 0;
	UW tmp;

	if(ClockRate == SLOW_RATE)
		ClkValue |= MCLKDIV_SLOW;	/* slow clock */
	else if(ClockRate == NORMAL_RATE)
		ClkValue |= MCLKDIV_NORMAL;	/* normal clock */

	tmp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK)) & ~0x00ff;
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK), tmp | (1<<8) | ClkValue);
	sil_dly_nse(3000);	/* 3 micro sec�Ԥ� */
}

/*
 *  ���ޥ�ɼ¹Գ���߽���
 */
static void mci_cmd_inter(MCIPCB *pmci)
{
	if(pmci->com.status & MCI_CMD_CRC_FAIL)
		pmci->cmdCrcFailCount++;
	if(pmci->com.status & MCI_CMD_TIMEOUT)
		pmci->cmdTimeoutCount++;
	if(pmci->com.status & MCI_CMD_RESP_END)	/* Cmd Resp End or Cmd Sent */
		pmci->cmdRespEndCount++;
	if(pmci->com.status & MCI_CMD_SENT)
		pmci->cmdSentCount++;
	if(pmci->com.status & MCI_CMD_ACTIVE)
		pmci->cmdActiveCount++;
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), pmci->com.status & (MCI_CMD_CRC_FAIL|MCI_CMD_RESP_END|MCI_CMD_SENT|MCI_CMD_ACTIVE));
}

/*
 *  �ǡ������顼����߽���
 */
static void mci_dataerror_inter(MCIPCB *pmci)
{
	if(pmci->com.status & MCI_DATA_CRC_FAIL){
		pmci->dataCrcFailCount++;
		pmci->com.endFlag |= MCI_ERREND;
	}
	if(pmci->com.status & MCI_DATA_TIMEOUT){
		pmci->dataTimeoutErrorCount++;
		pmci->com.endFlag |= MCI_ERREND;
	}
	if(pmci->com.status & MCI_TX_UNDERRUN){		/* Tx Underrun */
		pmci->dataTxUnderrunErrorCount++;
		pmci->com.endFlag |= MCI_ERREND;
	}
	if(pmci->com.status & MCI_RX_OVERRUN){		/* Rx overrun */
		pmci->dataRxOverrunErrorCount++;
		pmci->com.endFlag |= MCI_ERREND;
	}
	if(pmci->com.status & MCI_START_BIT_ERR){	/* Start bit error on data signal */
		pmci->dataStartBitErrorCount++;
		pmci->com.endFlag |= MCI_ERREND;
	}
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), pmci->com.status & (MCI_DATA_CRC_FAIL|MCI_DATA_TIMEOUT|MCI_RX_OVERRUN|MCI_START_BIT_ERR));
}

/*
 *  �ǡ�������ɳ���߽���
 */
static void mci_data_end_inter(MCIPCB *pmci)
{
	if(pmci->com.status &  MCI_DATA_END){		/* Data end */
		pmci->DataEndCount++;
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), MCI_DATA_END);
		return;
	}
	if(pmci->com.status &  MCI_DATA_BLK_END){	/* Data Block end */
		pmci->DataBlockEndCount++;
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), MCI_DATA_BLK_END);
		lpc23xx_mci_txdisable(pmci);
		pmci->com.endFlag |= MCI_END;
		return;
	}
}

/*
 *  FIFO����߽���
 */
static void mci_fifo_inter(MCIPCB *pmci)
{
#ifdef MCI_FIFOMODE
	UW *p;

	if(pmci->com.status & (FIFO_RX_INT_MASK)){
		if(pmci->com.status & MCI_RX_HALF_FULL){	/* Rx half full */
			p = &ReadBlock[pmci->RxBlockCounter];
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			*p++ = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_FIFO));
			pmci->RxBlockCounter += 32;
		}
		if(pmci->RxBlockCounter == BLOCK_LENGTH){	/* block complete */
			pmci->RxBlockCounter = 0;
		}
	}
	else if(pmci->com.status & (FIFO_TX_INT_MASK)){
		if(pmci->com.status & MCI_TX_HALF_EMPTY){	/* Tx half full */
			p = &WriteBlock[pmci->TxBlockCounter];
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_FIFO), *p++);
			pmci->TxBlockCounter += 32;
		}
		if(pmci->TxBlockCounter == BLOCK_LENGTH){	/* block complete */
			pmci->TxBlockCounter = 0;
			lpc23xx_mci_set_mask(pmci, 0, (FIFO_TX_INT_MASK));
		}
	}
#endif
}

/*
 *  MCI����ߥϥ�ɥ�
 */
void mci_isr0(void)
{
	MCIPCB *pmci = &Mci_Control_Block;

	pmci->com.status = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_STATUS));
	if(pmci->com.status & DATA_ERR_INT_MASK){
		mci_dataerror_inter(pmci);
	}
	if(pmci->com.status & DATA_END_INT_MASK){
		mci_data_end_inter(pmci);
	}
	else if(pmci->com.status & FIFO_INT_MASK){
		mci_fifo_inter(pmci);
	}
	else if(pmci->com.status & CMD_INT_MASK){
		mci_cmd_inter(pmci);
	}
	syslog_2(LOG_INFO, "## MCI_IRQHandler[%08x][%08x] ##", pmci->com.status, pmci->com.mask);
}

/*
 *  MCI�ɥ饤�Хϡ��ɥ������ν����
 */
void mci_init(VP_INT exinf)
{
	MCIPCB *pmci = &Mci_Control_Block;
	UW tmp;

	memset(pmci, 0, sizeof(MCIPCB));
	pmci->com.base = TADR_MCI_BASE;
	pmci->com.retryCount = 32;
#ifndef MCI_FIFOMODE
	pmci->dmaaddr = (char *)(DMA_MCI);
#endif

	tmp = sil_rew_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP));
	tmp |= 1 << 28;				/* MMC�ѥ���� */
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_SCB_PCONP), tmp);

	tmp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK));
	if(tmp & (1 << 8)){
		tmp &= ~(1 << 8);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK), tmp);
	}
	tmp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_POWER));
	if(tmp & 0x02){
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_POWER), 0x00000000);
	}
	sil_dly_nse(100000);		/* 100 micro sec�Ԥ� */

	/*
	 *  MCI�γ���߶ػ�
	 */
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_MASK0), 0x00000000);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_MASK1), 0x00000000);

	tmp = sil_rew_mem((VP)(TADR_SCB_BASE+TOFF_SCB_SCS));
	tmp &= ~0x00000008;
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_SCB_SCS), tmp);

	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_MCI_COMMAND), 0x0000);
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_MCI_DATA_CTRL), 0x0000);
	sil_wrw_mem((VP)(TADR_SCB_BASE+TOFF_MCI_CLEAR), 0x07FF);

	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_POWER), 0x00000002);	/* power up */
	while((sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_POWER)) & 0x00000002) == 0);
	sil_dly_nse(10000);		/* 10 micro sec�Ԥ� */

	lpc23xx_mci_set_clock(pmci, SLOW_RATE);	/* ��������å� */
	tmp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_POWER));
	tmp |= 0x00000001;		/* power on */
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_POWER), tmp);
}

/*
 *  MCI ACOMMAND����
 */
ER lpc23xx_mci_snd_acmd(MCIPCB *pmci)
{
	W CmdArgument, CmdRespStatus, i;
	W respValue[4];
	ER ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD-CARD�ξ�硢RCA�ͤ����� */
		CmdArgument = pmci->com.cardRCA;
	else								/* MMC�����ɤξ�硢��������� */
		CmdArgument = 0x00000000;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		lpc23xx_mci_snd_cmd(pmci, MCI_CMD55, CmdArgument);	/* CMD55���� */
		ercd = lpc23xx_mci_get_resp(pmci, MCI_CMD55, (W *)&respValue[0], &CmdRespStatus);
		if(ercd == E_OK && (respValue[0] & CARD_STATUS_ACMD_ENABLE))	/* Check if APP_CMD enabled */
			return E_OK;
		sil_dly_nse(2000);		/* 2 micro sec �Ԥ� */
	}
	return E_TMOUT;
}

/*
 *  COMMAND����
 */
ER lpc23xx_mci_snd_cmd(MCIPCB *pmci, W cmd, W arg)
{
	W retryCount = pmci->com.retryCount * 1024;
	W CmdStatus;

	/* ���ޥ�ɥ����ƥ����Ԥ� */
	while ( (CmdStatus = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_STATUS))) & MCI_CMD_ACTIVE ){
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_COMMAND), 0);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), CmdStatus | MCI_CMD_ACTIVE);
		if(retryCount-- <= 0)
			return E_TMOUT;
		sil_dly_nse(10000);		/* wait 10 micro sec */
	}
	sil_dly_nse(20000);			/* wait 20 micro sec */

	/* �����ȥ��ޥ�ɤ����� */
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_ARGUMENT), arg);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_COMMAND), (cmd | CMD_SETLAST) & CMD_MASK);
	return E_OK;
}

/*
 *  �쥹�ݥ󥹤μ���
 *  cmd:           �������ޥ��
 *  presp:         �쥹�ݥ󥹳�Ǽ�ΰ�Υݥ���
 *  pcmdrespstatus:���ơ�����(INFO)��Ǽ�ΰ�Υݥ���
 */
ER lpc23xx_mci_get_resp(MCIPCB *pmci, W cmd, W *presp, W *pcmdrespstatus)
{
	W LastCmdIndex;

	*pcmdrespstatus = 0;
	if((cmd & CMD_SLONGRESP) == 0){
		return E_OK;
	}

	while ( 1 ){
		*pcmdrespstatus = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_STATUS));
		if(*pcmdrespstatus & (MCI_CMD_TIMEOUT)){
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), *pcmdrespstatus | MCI_CMD_TIMEOUT);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_COMMAND), 0x00000000);
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_ARGUMENT), 0xFFFFFFFF);
			return E_TMOUT;
		}
		if(*pcmdrespstatus & MCI_CMD_CRC_FAIL){	/* CRC ���顼 */
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), *pcmdrespstatus | MCI_CMD_CRC_FAIL);
			LastCmdIndex = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_COMMAND)) & CMD_INDEX;
			if(LastCmdIndex == RES_CMD1 || LastCmdIndex == RES_ACMD41 || LastCmdIndex == RES_CMD12){
				sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_COMMAND), 0x00000000);
				sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_ARGUMENT), 0xFFFFFFFF);
				break;			/* CMD1,ACMD41�ξ���CRC���顼��̵�� */
			}
			else{
				return E_OK;
			}
		}
		else if(*pcmdrespstatus & MCI_CMD_RESP_END ){	/* �쥹�ݥ󥹥���� */
			sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), *pcmdrespstatus | MCI_CMD_RESP_END);
			break;	/* cmd response is received, expecting response */
		}
	}

	if((sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP_CMD)) & 0x3F) != (cmd & 0x3F)){
	/* �������ޥ�ɤȥ쥹�ݥ󥹥��ޥ�ɤ��ۤʤ���ϡ�
	   ���ޥ�ɤ�CMD_IGNOREIRES���ʤ���Х��顼�Ȥ��� */
		if((cmd & CMD_IGNOREIRES) == 0){
			return E_NOSPT;
		}
	}

	if((cmd & CMD_LONGRESP) != 0){	/* CMD_SLONGRESP */
		*presp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP0));
		*(presp+1) = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP1));
		*(presp+2) = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP2));
		*(presp+3) = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP2));
	}
	else{		/* CMD_SHORTRESP */
		*presp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_RESP0));
	}
	return E_OK;
}

/*
 *  �����ɥ륹�ơ��Ȱܹ��׵�
 */
static BOOL lpc23xx_mci_idle_state(MCIPCB *pmci)
{
	W CmdRespStatus, i;
	W respValue[4];
	ER ercd = E_TMOUT;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		ercd = lpc23xx_mci_snd_cmd(pmci, MCI_CMD0, 0x00000000);
		if(ercd != E_OK)
			return FALSE;
		ercd = lpc23xx_mci_get_resp(pmci, MCI_CMD0, (W *)respValue, &CmdRespStatus );
		if(ercd == E_OK)
			break;
	}
	return(ercd == E_OK);	/* if E_OK, return TRUE */
}

/*
 *  MMC������OP_COND���ޥ��
 */
static BOOL lpc23xx_mci_snd_op_cond(MCIPCB *pmci)
{
	W CmdRespStatus, i;
	W respValue[4];
	ER ercd;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		ercd = lpc23xx_mci_snd_cmd(pmci, MCI_CMD1, OCR_INDEX);	/* CMD1���� */
		if(ercd != E_OK)
			break;
		ercd = lpc23xx_mci_get_resp(pmci, MCI_CMD1, (W *)&respValue[0], &CmdRespStatus);
		/* bit 0 and bit 2 must be zero, or it's timeout or CRC error */
		if(ercd == E_OK && (respValue[0] & 0x80000000)){
			return TRUE;	/* �쥹�ݥ� OK */
		}
		sil_dly_nse(2000);	/* 2 micro sec�Ԥ� */
	}
	return FALSE;
}

/*
 *  SD������OP_COND���ޥ��
 */
static BOOL lpc23xx_mci_snd_aop_cond(MCIPCB *pmci)
{
	W retryCount = pmci->com.retryCount * 16;
	W CmdRespStatus, i;
	W respValue[4];
	UW tmp;
	ER ercd;

	for(i = 0 ; i < retryCount ; i++){
		tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_POWER));
		tmp &= ~(1 << 6);		/* Clear Open Drain output control for SD */
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_POWER), tmp);
		dly_tsk(1);		/* 1 msec�Ԥ� */

		if(lpc23xx_mci_snd_acmd(pmci) != E_OK){
			return FALSE;
		}

		lpc23xx_mci_snd_cmd(pmci, MCI_ACMD41, OCR_INDEX);	/* ACMD41���� */
		ercd = lpc23xx_mci_get_resp(pmci, MCI_ACMD41, (W *)&respValue[0], &CmdRespStatus);
		if(ercd == E_OK && (respValue[0] & 0x80000000)){
			return TRUE;	/* �쥹�ݥ� OK */
		}
		sil_dly_nse(2000);	/* 2 micro sec�Ԥ� */
	}
	return FALSE;
}

/*
 *  MCI�ɥ饤�Фν�����롼����
 */
MCIPCB* lpc23xx_mci_ini_por(void)
{
	MCIPCB *pmci = &Mci_Control_Block;
	UW tmp;

	pmci->com.cardType = 0;
	if(!lpc23xx_mci_idle_state(pmci)){
		return NULL;
	}

	tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_POWER));
	tmp |= (1 << 6);	/* Set Open Drain output control for MMC */
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_POWER), tmp);
	dly_tsk(1);			/* wait 1 msec */
	return pmci;
}

/*
 *  MCI-I/O�ݡ��ȤΥ����ץ�
 */
ER_ID lpc23xx_mci_opn_por(MCIPCB *pmci)
{
	if(lpc23xx_mci_snd_op_cond(pmci)){	/* MMC�����ɤθ��� */
		pmci->com.cardType = MMC_CARD;
		return MMC_CARD;
	}
	else if(lpc23xx_mci_snd_aop_cond(pmci)){	/* SD�����ɤθ��� */
		pmci->com.cardType = SD_CARD;
		return SD_CARD;
	}
	else{								/* �����ɸ��м��� */
		return E_ID;
	}
}

/*
 *  MCI-I/O�ݡ��ȤΥ�����
 */
ER lpc23xx_mci_cls_por(MCIPCB *pmci)
{
	return E_OK;
}

/*
 *  �ޥ��󥹥ơ������Υ����å�
 */
static BOOL lpc23xx_mci_chk_status(MCIPCB *pmci)
{
	W retryCount = pmci->com.retryCount * 256;
	W CmdRespStatus, i;
	W respValue[4];
	W CmdArgument;
	UW tmp;
	ER ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD������RCA */
		CmdArgument = pmci->com.cardRCA;
	else								/* MMC�����ɥǥե�������� */
		CmdArgument = 0x00010000;

	for(i = 0 ; i < retryCount ; i++){
		tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR));
		tmp |= (MCI_CMD_TIMEOUT | MCI_CMD_CRC_FAIL | MCI_CMD_RESP_END);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), tmp);
		lpc23xx_mci_snd_cmd(pmci, MCI_CMD13, CmdArgument);	/* CMD13���� */
		ercd = lpc23xx_mci_get_resp(pmci, MCI_CMD13, (W *)&respValue[0], &CmdRespStatus);
		if(ercd == E_OK && (respValue[0] & (0x0F << 8)) == 0x0900){
			return TRUE;	/* �쥹�ݥ� OK */
		}
	}
	return FALSE;
}

/*
 *  MCIž�����ȥå�����
 */
static BOOL lpc23xx_mci_cmd_stop(MCIPCB *pmci)
{
	W  CmdRespStatus, i;
	W  respValue[4];
	ER ercd;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), 0x07FF);
		lpc23xx_mci_snd_cmd(pmci, MCI_CMD12, 0x00000000);
		ercd = lpc23xx_mci_get_resp(pmci, MCI_CMD12, (W *)respValue, &CmdRespStatus);
		/* ready bit, bit 8, should be set in the card status register */
		if(ercd == E_OK && (respValue[0] & (1 << 8))){
			return TRUE;
		}
		sil_dly_nse(2000);			/* wait 2 micro sec */
	}
	return FALSE;
}

/*
 *  �֥�å��ֹ������
 */
static BOOL lpc23xx_set_blocknum(MCIPCB *pmci, W cmd, W blockNum)
{
	W  CmdRespStatus, i;
	W  respValue[4];
	ER ercd;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), 0x07FF);
		lpc23xx_mci_snd_cmd(pmci, cmd, blockNum * BLOCK_LENGTH);
		ercd = lpc23xx_mci_get_resp(pmci, cmd, (W *)&respValue[0], &CmdRespStatus);
		/* it should be in the transfer state, bit 9~12 is 0x0100 and bit 8 is 1 */
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0900)){
			return TRUE;		/* �쥹�ݥ� OK */
		}
		sil_dly_nse(2000);		/* 2 micro sec�Ԥ� */
	}
	return FALSE;				/* Fatal error */
}

/*
 *  MCI�ǥХ����ؤν񤭹���
 */
ER lpc23xx_mci_wri_blk(MCIPCB *pmci, B *buf, W blockNum)
{
	W DataCtrl = 0;

	pmci->trnaddr = buf;
	pmci->com.mode   |= SDMODE_WRITE;
	if(pmci->dmaaddr != NULL)
		memcpy(pmci->dmaaddr, pmci->trnaddr, BLOCK_LENGTH);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), 0x07FF);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_CTRL), 0x0000);
	sil_dly_nse(1000);		/* 1 micro sec�Ԥ� */

	if(!lpc23xx_mci_chk_status(pmci)){	/* �ޥ��󥹥ơ����������å� */
		lpc23xx_mci_cmd_stop(pmci);
		return E_SYS;
	}

	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_TMR), DATA_TIMER_VALUE);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_LEN), BLOCK_LENGTH);
	pmci->com.endFlag = MCI_NOTEND;
	lpc23xx_mci_txenable(pmci);
	if(lpc23xx_set_blocknum(pmci, MCI_CMD24, blockNum) == FALSE){
		return E_SYS;
	}

#ifdef MCI_FIFOMODE
	/* Write, block transfer, and data length */
	DataCtrl |= ((1 << 0) | (DATA_BLOCK_LEN << 4));
#else
	lpc23xx_set_trn(0, M2PP, (UW)pmci->dmaaddr, TADR_MCI_BASE+TOFF_MCI_FIFO, BLOCK_LENGTH);
	lpc23xx_set_cfg(0, PDUMMY, PMCI, M2PP);
	/* Write, block transfer, DMA, and data length */
	DataCtrl |= ((1 << 0) | (1 << 3) | (DATA_BLOCK_LEN << 4));
#endif
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_CTRL), DataCtrl);
	sil_dly_nse(1000);		/* 1 micro sec�Ԥ� */
	return E_OK;
}

/*
 *  MCI�ǥХ���������ɤ߹���
 */
ER lpc23xx_mci_rea_blk(MCIPCB *pmci, B *buf, W blockNum)
{
	W DataCtrl = 0;

	pmci->trnaddr = buf;
	pmci->com.mode   &= ~SDMODE_WRITE;
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), 0x07FF);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_CTRL), 0x0000);
	sil_dly_nse(1000);		/* wait 1 micro sec */

	if(!lpc23xx_mci_chk_status(pmci)){	/* �ޥ��󥹥ơ����������å� */
		lpc23xx_mci_cmd_stop(pmci);
		return E_SYS;
	}
	lpc23xx_mci_rxenable(pmci);

	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_TMR), DATA_TIMER_VALUE);
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_LEN), BLOCK_LENGTH);
	pmci->com.endFlag = MCI_NOTEND;
	if(lpc23xx_set_blocknum(pmci, MCI_CMD17, blockNum) == FALSE){
		return E_SYS;
	}

#ifdef MCI_FIFOMODE
	/* Read, enable, block transfer, and data length */
	DataCtrl |= ((1 << 0) | (1 << 1) | (DATA_BLOCK_LEN << 4));
#else
	lpc23xx_set_trn(1, P2MP, TADR_MCI_BASE+TOFF_MCI_FIFO, (UW)pmci->dmaaddr, BLOCK_LENGTH);
	lpc23xx_set_cfg(1, PMCI, PDUMMY, P2MP);
	/* Write, block transfer, DMA, and data length */
	DataCtrl |= ((1 << 0) | (1 << 1) | (1 << 3) | (DATA_BLOCK_LEN << 4));
#endif
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_DATA_CTRL), DataCtrl);
	sil_dly_nse(1000);		/* wait 1 micro sec */
	return E_OK;
}

/*
 *  MCI�ǥХ����ǡ���ž���Ԥ�
 */
ER lpc23xx_mci_wai_trn(MCIPCB *pmci, W timeout)
{
    while (pmci->com.endFlag == MCI_NOTEND){
		dly_tsk(10);
		timeout -= 10;
		if(timeout <= 0)
			return E_TMOUT;
    }
	if(pmci->com.endFlag != MCI_END)
		return E_SYS;
	else if(pmci->dmaaddr != NULL && !(pmci->com.mode & SDMODE_WRITE))
		memcpy(pmci->trnaddr, pmci->dmaaddr, BLOCK_LENGTH);
	return E_OK;
}

