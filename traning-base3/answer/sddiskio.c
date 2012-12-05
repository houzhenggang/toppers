/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2011 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: sddickio.c,v 1.2 2011/07/17 15:18:56 roi Exp $
 */

/*
 * このプログラムはITRON専用のTYPE3ソフトウェアである。
 * ＳＤカード専用ストレージ関数をサポートする
 * 擬似的なストレージ関数郡であり、標準ライブラリィと分けての使用が望ましい。
 * 1. _sd_init                 この関数郡の初期化関数(bssがゼロ設定の場合この関数は不要)
 * 2. sdcard_sense             SD-CARDのセンスを行う
 * 3. sdcard_diskstatus        SD-CARDのステータス取得:なし
 * 4. sdcard_diskread          SD-CARDの読み込み:なし
 * 5. sdcard_diskwrite         SD-CARDの書き込み:なし
 * 6. sdcard_iocil             SD-CARDのIO制御:なし
 *
 */

#include "itron.h"
#include <stdlib.h>
#include <string.h>
#include <t_services.h>
#include <board_config.h>
#include "fcntl.h"
#include "mcicmd.h"
#include "storagedevice.h"
#include "ff.h"
#include "diskio.h"

#define RETRY_COUNT    8

#define SDCARD_DEVNO   0
#define SDCRAD_PORTID  0

#ifndef NUM_FIL
#define NUM_FIL        64
#endif

struct mci_port_control_block {
	MCIPCMB com;
};

static int sdcard_sense(void *psdev, BOOL on);

static const StorageDeviceFunc_t fatfsSDeviceFunc = {
	sdcard_sense,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

static FATFS ActiveFatFsObj;

extern void  _sd_setfcntldev(int no);
extern const StorageDeviceFileFunc_t fatfsSDeviceFileFunc;

/*
 *  SDCARDセンス関数
 */
static int sdcard_sense(void *pif, BOOL on)
{
	StorageDevice_t *psdev = pif;
	int      card = 0;
	MCIPCB   *pmci;
	int      result;

	pmci = psdev->_sdev_local[1];
	if(on){
		return FALSE;
	}
	else if(!on){
		card = mci_opn_por(pmci);
		if(card <= 0)
			return FALSE;
		if(MciCheckCID(pmci) != E_OK){
			psdev->_sdev_attribute |= SDEV_DEVERROR;
			return TRUE;
		}
		if(MciSetAddress(pmci) != E_OK){
			psdev->_sdev_attribute |= SDEV_DEVERROR;
			return TRUE;
		}
		if(MciSendCSD(pmci, &psdev->_sdev_maxsec) != E_OK){
			psdev->_sdev_attribute |= SDEV_DEVERROR;
			return TRUE;
		}
		if(MciSelectCard(pmci) != E_OK){
			psdev->_sdev_attribute |= SDEV_DEVERROR;
			return TRUE;
		}
		if(card == SD_CARD){
			mci_set_clock(pmci, NORMAL_RATE );
			if(MciSDBusWidth(pmci, SD_4_BIT ) != E_OK){
    	      psdev->_sdev_attribute |= SDEV_DEVERROR;
        	  return TRUE;
			}
		}
		if(MciSetBlockLen(pmci, BLOCK_LENGTH) != E_OK){
    		psdev->_sdev_attribute |= SDEV_DEVERROR;
			return TRUE;
		}
		result = f_mount(psdev->_sdev_devno, &ActiveFatFsObj);
		if(result != FR_OK)
			psdev->_sdev_attribute |= SDEV_DEVERROR;
		else
			psdev->_sdev_local[0]   = &ActiveFatFsObj;
		return TRUE;
	}
	else
		return FALSE;
}

/*
 *  FatFs用SDカードファイルドライバの初期化
 */
int _sd_init(void)
{
	StorageDevice_t *psdev;
	int result;

	result = SDMSetupDevice(SDCARD_DEVNO, &psdev);
	assert(result == E_OK);
	psdev->pdevf            = (StorageDeviceFunc_t *)&fatfsSDeviceFunc;
	psdev->pdevff           = (StorageDeviceFileFunc_t *)&fatfsSDeviceFileFunc;
	psdev->_sdev_secsize    = 512;
	psdev->_sdev_port       = SDCRAD_PORTID;
	psdev->_sdev_local[1]   = mci_ini_por();
	assert(psdev->_sdev_local[1] != NULL);
	psdev->_sdev_attribute |= SDEV_INSERTCHK|SDEV_CHKREMOVE;
	_sd_setfcntldev(SDCRAD_PORTID);
	return 1;
}

/*
 *  ディスク・ドライブの初期化
 *　　引数
 *　　　 BYTE Drive	物理ドライブ番号
 */
DSTATUS
disk_initialize(BYTE Drive)
{
	StorageDevice_t *psdev = SDMGetStorageDevice(Drive);
	MCIPCB          *pmci;

	if(psdev == NULL)
		return STA_NODISK;
	pmci = psdev->_sdev_local[1];
	if((psdev->_sdev_attribute & (SDEV_EMPLOY|SDEV_NOTUSE)) != SDEV_EMPLOY || pmci == NULL)
		return STA_NOINIT;
	else if((pmci->com.mode & SDMODE_PROTECT) != 0)
		return STA_PROTECT;
	else
		return 0;
}

/*
 *  ディスク・ドライブの状態取得
 *　　引数
 *　　　 BYTE Drive	物理ドライブ番号
 */
DSTATUS
disk_status(BYTE Drive)
{
	StorageDevice_t *psdev = SDMGetStorageDevice(Drive);
	MCIPCB          *pmci;

	if(psdev == NULL)
		return STA_NODISK;
	pmci = psdev->_sdev_local[1];
	if((psdev->_sdev_attribute & (SDEV_EMPLOY|SDEV_NOTUSE)) != SDEV_EMPLOY || pmci == NULL)
		return STA_NOINIT;
	else if((pmci->com.mode & SDMODE_PROTECT) != 0)
		return STA_PROTECT;
	else
		return 0;
}

/*
 *  ディスクからの読み込み
 *　　引数
 *　　　 BYTE Drive　　　　　物理ドライブ番号
 *　　　 BYTE* Buffer        読み出しバッファへのポインタ
 *　　　 DWORD SectorNumber  読み出し開始セクタ番号
 *　　　 BYTE SectorCount    読み出しセクタ数
 */
DRESULT
disk_read(BYTE Drive, BYTE* Buffer, DWORD SectorNumber, BYTE SectorCount)
{
	StorageDevice_t *psdev = SDMGetStorageDevice(Drive);
	MCIPCB          *pmci;
	int             i;

#ifndef SAMPLE_PROGRAM
	if(psdev == NULL)
		return RES_ERROR;
	pmci = psdev->_sdev_local[1];
	if((psdev->_sdev_attribute & (SDEV_EMPLOY|SDEV_NOTUSE)) != SDEV_EMPLOY || pmci == NULL)
		return RES_ERROR;
	for(i = 0 ; i < SectorCount ; i++){
		if(mci_rea_blk(pmci, Buffer, SectorNumber) != E_OK)
			return RES_ERROR;
		if(mci_wai_trn(pmci, 5000) != E_OK)
			return RES_ERROR;
		SectorNumber++;
		Buffer += psdev->_sdev_secsize;
	}
#endif
	return RES_OK;
}

/*
 *  ディスクへの書き込み
 *　　引数
 *　　　 BYTE Drive　　　　　物理ドライブ番号
 *　　　 BYTE* Buffer        書き込むデータへのポインタ
 *　　　 DWORD SectorNumber  書き込み開始セクタ番号
 *　　　 BYTE SectorCount    書き込みセクタ数
 */
DRESULT
disk_write(BYTE Drive, const BYTE* Buffer, DWORD SectorNumber, BYTE SectorCount)
{
	StorageDevice_t *psdev = SDMGetStorageDevice(Drive);
	MCIPCB          *pmci;
	int             i;

	if(psdev == NULL)
		return RES_ERROR;
	pmci = psdev->_sdev_local[1];
	if((psdev->_sdev_attribute & (SDEV_EMPLOY|SDEV_NOTUSE)) != SDEV_EMPLOY || pmci == NULL)
		return RES_ERROR;
	for(i = 0 ; i < SectorCount ; i++){
		if(mci_wri_blk(pmci, Buffer, SectorNumber) != E_OK){
			return RES_ERROR;
		}
		if(mci_wai_trn(pmci, 5000) != E_OK)
			return RES_ERROR;
		Buffer += psdev->_sdev_secsize;
		SectorNumber++;
	}
	return RES_OK;
}

/*
 *  FatFs用SDCARDIO制御関数
 */
DRESULT
disk_ioctl(BYTE Drive, BYTE Func, void* Buffer)
{
	StorageDevice_t *psdev = SDMGetStorageDevice(Drive);
	DRESULT         result;

	if(psdev == NULL)
		return RES_ERROR;
	if((psdev->_sdev_attribute & (SDEV_EMPLOY|SDEV_NOTUSE)) != SDEV_EMPLOY)
		return RES_ERROR;
	switch(Func){
	case CTRL_SYNC:
		result = RES_OK;			/* no action */
		break;
	case GET_SECTOR_COUNT:
		*((DWORD *)Buffer) = psdev->_sdev_maxsec;
		syslog_2(LOG_NOTICE, "ioctl notuse (%d)(%d) ", (int)Func, psdev->_sdev_maxsec);
		result = RES_OK;
		break;
	case GET_BLOCK_SIZE:
		*((DWORD *)Buffer) = 135;	/* ERASE_BLK */
		syslog_1(LOG_NOTICE, "call disk_ioctl(GET_BLOCK_SIZE, %08x)", (int)(*((DWORD *)Buffer)));
		result = RES_OK;
		break;
	default:
		syslog_2(LOG_NOTICE, "call disk_ioctl(%d, %08x)", (int)psdev->_sdev_devno, (int)Buffer);
		slp_tsk();
		result = RES_PARERR;
		break;
	}
	return result;
}

/*
 *  日付・時刻の取得
 *  　　ToDo：未実装
 */
DWORD
get_fattime(void)
{
	SYSTIM systim;
	DWORD  fdate = ((1980-1980)<<25)+(1<<21)+(1<<16);
	DWORD  ftime;

	if(SDeviceHead._get_datetime != 0)
		return (DWORD)SDeviceHead._get_datetime();
	else{
		get_tim(&systim);
		systim = (systim+1000L) /2000L;
		ftime  = systim % 30;
		ftime += ((systim/30) % 60)<<5;
		ftime += ((systim/(60*30))<<11);
		return (fdate+ftime);
	}
}


