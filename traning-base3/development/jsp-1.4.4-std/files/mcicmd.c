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
 *  @(#) $Id: mcicmd.c,v 1.1 2011/02/20 17:18:56 roi Exp $
 */

/*
 * このプログラムはITRON専用のTYPE3ソフトウェアである。
 * ＳＤカード専用ストレージ関数をサポートする
 * 擬似的なストレージ関数郡であり、標準ライブラリィと分けての使用が望ましい。
 * 1. _sd_init                 この関数郡の初期化関数(bssがゼロ設定の場合この関数は不要)
 * 2. sdcard_sense             SD-CARDのセンスを行う
 * 3. sdcard_diskstatus        SD-CARDのステータス取得
 * 4. sdcard_diskread          SD-CARDの読み込み
 * 5. sdcard_diskwrite         SD-CARDの書き込み
 * 6. sdcard_iocil             SD-CARDのIO制御
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
 *  SDカードのセクタ数計算関数
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
 *  SDカードのバス幅の設定を行う
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
 *  CIDの取得
 *  SDカードCMD2,MMCカードCMD1送信後のレスポンス受信
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
 *  相対アドレス(RCA)の取得
 */
ER MciSetAddress(MCIPCB *pmci)
{
	W respStatus, CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	ER  ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARDの場合ゼロ */
		CmdArgument = 0;
	else			/* MMC_CARDの場合,デフォルトRCAアドレス */
		CmdArgument = MMC_DEFAULT_RCA;

	for(i = 0 ; i < pmci->com.retryCount ; i++){
		/* CMD3を送信, 正常終了まで繰り返す */
		mci_snd_cmd(pmci, MCI_CMD3, CmdArgument);
		ercd = mci_get_resp(pmci, MCI_CMD3, (W *)&respValue[0], &CmdRespStatus);
		/* bit 0 and bit 2 must be zero, or it's timeout or CRC error */
		/* It should go to IDEN state and bit 8 should be 1 */
		if(ercd == E_OK && ((respValue[0] & (0x0F << 8)) == 0x0500) ){
			pmci->com.cardRCA = respValue[0] & 0xFFFF0000;	/* SD_CARD用のRCAをセーブする */
			return E_OK;		/* 正常終了 */
		}
		sil_dly_nse(2000);		/* wait 2 micro sec */
	}
	return E_TMOUT;
}

/*
 *  CSD(Card Specific DATA)の取得
 */
ER MciSendCSD(MCIPCB *pmci, UW *pmaxsec)
{
	W CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	UW  tmp;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARDの場合RCA */
		CmdArgument = pmci->com.cardRCA;
	else			/* MMC_CARDの場合,デフォルトRCAアドレス */
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
 *  SELECT_CARDコマンドの送信
 */
ER MciSelectCard(MCIPCB *pmci)
{
	W respStatus, CmdRespStatus;
	W respValue[4];
	W CmdArgument;
	int i;
	UW  tmp;
	ER  ercd;

	if(pmci->com.cardType == SD_CARD)	/* SD_CARDの場合RCA */
		CmdArgument = pmci->com.cardRCA;
	else			/* MMC_CARDの場合,デフォルトRCAアドレス */
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
 *  ブロック長の設定
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

