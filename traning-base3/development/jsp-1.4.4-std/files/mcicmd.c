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
 *  @(#) $Id: mcicmd.c,v 1.1 2011/02/20 17:18:56 roi Exp $
 */

/*
 * ���Υץ�����ITRON���Ѥ�TYPE3���եȥ������Ǥ��롣
 * �ӣĥ��������ѥ��ȥ졼���ؿ��򥵥ݡ��Ȥ���
 * ����Ū�ʥ��ȥ졼���ؿ����Ǥ��ꡢɸ��饤�֥�ꥣ��ʬ���Ƥλ��Ѥ�˾�ޤ�����
 * 1. _sd_init                 ���δؿ����ν�����ؿ�(bss����������ξ�礳�δؿ�������)
 * 2. sdcard_sense             SD-CARD�Υ��󥹤�Ԥ�
 * 3. sdcard_diskstatus        SD-CARD�Υ��ơ���������
 * 4. sdcard_diskread          SD-CARD���ɤ߹���
 * 5. sdcard_diskwrite         SD-CARD�ν񤭹���
 * 6. sdcard_iocil             SD-CARD��IO����
 *
 */

#include "itron.h"
#include <stdlib.h>
#include <s_services.h>
#include <board_config.h>
#include "mcicmd.h"

struct mci_port_control_block {
	MCIPCMB com;
};

/*
 *  SD�����ɤΥ��������׻��ؿ�
 */
static UW MciDSCapacity(UW *resp)
{
	unsigned long c_size = 0;			/* device size                 [C_SIZE] */
	unsigned long c_size_mult = 0;		/* device size multiplier      [C_SIZE_MULT] */
	unsigned long read_bl_len = 0;		/* max. read data block length [READ_BL_LEN] */
	unsigned long mult = 0;				/* SDSC : 2^(c_size_mult +2 ) */
	unsigned long blocknr = 0;			/* SDSC : (c_size + 1 ) * mult */
	unsigned long block_ren = 0;		/* SDSC : 2^read_bl_len */
	unsigned long memory_capacity = 0;	/* SDSC : blocknr * block_ren / 1024 / 1024 (Mbyte) */
	int i;

	/* Memory Capacity Calculation (SDSC:Kbyte) */
	/* max. read data block length [R80:R83] 4bit */
	read_bl_len = (resp[1] >> 16) & 0x000F;
	/* rdevice size [R62:R73] 12bit */
	c_size = ((resp[1] << 2) & 0x0ffc) | (resp[2] >> 30);
	/* device size multiplier [R47:R49] 3bit */
	c_size_mult = (resp[2] >> 14) & 0x0007;
	/* SDSC */
	/* mult = 2^(c_size_mult +2 ) */
	for(i = 0 , mult = 1 ; i < (c_size_mult + 2) ; i++){
		mult *= 2;
	}
	/* blocknr = (c_size + 1 ) * mult */
	blocknr = ((c_size + 1 ) * mult);
	/* block_ren = 2^read_bl_len */
	for(i = 0 , block_ren = 1 ; i < read_bl_len ; i++){
		block_ren *= 2;
	}
	memory_capacity = ((blocknr * block_ren) / 1024);	/* kbyte */
	return memory_capacity * 0x0002;
}

/*
 *  SD�����ɤΥХ����������Ԥ�
 */
ER MciSDBusWidth(MCIPCB *pmci, W width)
{
	UW tmp = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK));
	W CmdRespStatus, i;
	W respValue[4];
	W buswidth = BUS_WIDTH_4BITS;
	ER ercd;

	if(width == SD_1_BIT)
		tmp &=  ~(1 << 11);	/* 1 bit bus */
	else if(width == SD_4_BIT)
		tmp |=  (1 << 11);	/* 4 bit bus */
	else
		return E_PAR;
	sil_dly_nse(3000);	/* delay 3MCLK + 2PCLK  */
	sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLOCK), tmp);

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		if(ercd = mci_snd_acmd(pmci) != E_OK){
			  return ercd;
		}
		/* Send ACMD6 command to set the bus width */
		mci_snd_cmd(pmci, MCI_CMD6, buswidth);
		ercd = mci_get_resp(pmci, MCI_CMD6, (W *)&respValue[0], &CmdRespStatus);
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0900)){
			 return E_OK;	/* response is back and correct. */
		}
		sil_dly_nse(2000);	/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  CID�μ���
 *  SD������CMD2,MMC������CMD1������Υ쥹�ݥ󥹼���
 */
ER MciCheckCID(MCIPCB *pmci)
{
	W CmdRespStatus;
	W respValue[4];
	int i;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		mci_snd_cmd(pmci, MCI_CMD2, 0);
		if(mci_get_resp(pmci, MCI_CMD2, (W *)&respValue[0], &CmdRespStatus) == E_OK){
			return E_OK;		/* response is back and correct. */
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  ���Х��ɥ쥹(RCA)�μ���
 */
ER MciSetAddress(MCIPCB *pmci)
{
	W respStatus, CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	ER  ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARD�ξ�祼�� */
		CmdArgument = 0;
	else			/* MMC_CARD�ξ��,�ǥե����RCA���ɥ쥹 */
		CmdArgument = MMC_DEFAULT_RCA;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		/* CMD3������, ���ｪλ�ޤǷ����֤� */
		mci_snd_cmd(pmci, MCI_CMD3, CmdArgument);
		ercd = mci_get_resp(pmci, MCI_CMD3, (W *)&respValue[0], &CmdRespStatus);
		/* bit 0 and bit 2 must be zero, or it's timeout or CRC error */
		/* It should go to IDEN state and bit 8 should be 1 */
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0500) ){
			pmci->com.cardRCA = respValue[0] & 0xFFFF0000;	/* SD_CARD�Ѥ�RCA�򥻡��֤��� */
			return E_OK;		/* ���ｪλ */
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  CSD(Card Specific DATA)�μ���
 */
ER MciSendCSD(MCIPCB *pmci, UW *pmaxsec)
{
	W CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	UW  tmp;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARD�ξ��RCA */
		CmdArgument = pmci->com.cardRCA;
	else			/* MMC_CARD�ξ��,�ǥե����RCA���ɥ쥹 */
		CmdArgument = MMC_DEFAULT_RCA;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR));
		tmp |= (MCI_CMD_TIMEOUT | MCI_CMD_CRC_FAIL | MCI_CMD_RESP_END);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), tmp);
		mci_snd_cmd(pmci, MCI_CMD9, CmdArgument);
		if(mci_get_resp(pmci, MCI_CMD9, (W *)&respValue[0], &CmdRespStatus) == E_OK){
			*pmaxsec = MciDSCapacity(&respValue[0]);
			return E_OK;
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  SELECT_CARD���ޥ�ɤ�����
 */
ER MciSelectCard(MCIPCB *pmci)
{
	W respStatus, CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	UW  tmp;
	ER  ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARD�ξ��RCA */
		CmdArgument = pmci->com.cardRCA;
	else			/* MMC_CARD�ξ��,�ǥե����RCA���ɥ쥹 */
		CmdArgument = MMC_DEFAULT_RCA;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR));
		tmp |= (MCI_CMD_TIMEOUT | MCI_CMD_CRC_FAIL | MCI_CMD_RESP_END);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), tmp);
		mci_snd_cmd(pmci, MCI_CMD7, CmdArgument);
		ercd = mci_get_resp(pmci, MCI_CMD7, (W *)&respValue[0], &CmdRespStatus);
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0700 )){	/* Should be in STANDBY state now and ready */
		  return E_OK;
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  �֥�å�Ĺ������
 */
ER MciSetBlockLen(MCIPCB *pmci, W blockLength)
{
	W CmdRespStatus;
	W respValue[4];
	int i;
	UW  tmp;
	ER  ercd;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		tmp  = sil_rew_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR));
		tmp |= (MCI_CMD_TIMEOUT | MCI_CMD_CRC_FAIL | MCI_CMD_RESP_END);
		sil_wrw_mem((VP)(pmci->com.base+TOFF_MCI_CLEAR), tmp);
		mci_snd_cmd(pmci, MCI_CMD16, blockLength);
		ercd = mci_get_resp(pmci, MCI_CMD16, (W *)&respValue[0], &CmdRespStatus);
		/* bit 9 through 12 should be in transfer state now. bit 8 is ready. */
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0900)){
			return E_OK;
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

