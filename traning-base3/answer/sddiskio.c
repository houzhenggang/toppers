/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2011 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: sddickio.c,v 1.2 2011/07/17 15:18:56 roi Exp $
 */

/*
 * ���Υץ�����ITRON���Ѥ�TYPE3���եȥ������Ǥ��롣
 * �ӣĥ��������ѥ��ȥ졼���ؿ��򥵥ݡ��Ȥ���
 * ����Ū�ʥ��ȥ졼���ؿ����Ǥ��ꡢɸ��饤�֥�ꥣ��ʬ���Ƥλ��Ѥ�˾�ޤ�����
 * 1. _sd_init                 ���δؿ����ν�����ؿ�(bss����������ξ�礳�δؿ�������)
 * 2. sdcard_sense             SD-CARD�Υ��󥹤�Ԥ�
 * 3. sdcard_diskstatus        SD-CARD�Υ��ơ���������:�ʤ�
 * 4. sdcard_diskread          SD-CARD���ɤ߹���:�ʤ�
 * 5. sdcard_diskwrite         SD-CARD�ν񤭹���:�ʤ�
 * 6. sdcard_iocil             SD-CARD��IO����:�ʤ�
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
 *  SDCARD���󥹴ؿ�
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
 *  FatFs��SD�����ɥե�����ɥ饤�Фν����
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
 *  �ǥ��������ɥ饤�֤ν����
 *��������
 *������ BYTE Drive	ʪ���ɥ饤���ֹ�
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
 *  �ǥ��������ɥ饤�֤ξ��ּ���
 *��������
 *������ BYTE Drive	ʪ���ɥ饤���ֹ�
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
 *  �ǥ�����������ɤ߹���
 *��������
 *������ BYTE Drive����������ʪ���ɥ饤���ֹ�
 *������ BYTE* Buffer        �ɤ߽Ф��Хåե��ؤΥݥ���
 *������ DWORD SectorNumber  �ɤ߽Ф����ϥ������ֹ�
 *������ BYTE SectorCount    �ɤ߽Ф���������
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
 *  �ǥ������ؤν񤭹���
 *��������
 *������ BYTE Drive����������ʪ���ɥ饤���ֹ�
 *������ BYTE* Buffer        �񤭹���ǡ����ؤΥݥ���
 *������ DWORD SectorNumber  �񤭹��߳��ϥ������ֹ�
 *������ BYTE SectorCount    �񤭹��ߥ�������
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
 *  FatFs��SDCARDIO����ؿ�
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
 *  ���ա�����μ���
 *  ����ToDo��̤����
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


