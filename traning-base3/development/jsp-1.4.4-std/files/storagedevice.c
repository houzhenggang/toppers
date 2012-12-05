/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010      by GJ Designing Center RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: storagedevice.c,v 1.1 2010/06/10 18:39:56 roi Exp $
 */

#include <stdlib.h>
#include <string.h>
#include "kernel_id.h"
#include "storagedevice.h"

#define SENSE_DEVICE    (SDEV_ACTIVE|SDEV_INSERTCHK)


/*
 *  Storage Device Mnanager���������
 */
StorageDeviceHead_t SDeviceHead;

/*
 *  �ǥХ���ñ�̤ι�¤���ΰ����
 */
static StorageDevice_t SDevice[NUM_STORAGEDEVICE];



void sdev_init(VP_INT exinf)
{
	unsigned int no;

	for(no = 0 ; no < NUM_STORAGEDEVICE ; no++){
		memset(&SDevice[no], 0, sizeof(StorageDevice_t));
	}
	memset(&SDeviceHead, 0, sizeof(StorageDeviceHead_t));
	SDeviceHead._psd            = &SDevice[0];
	SDeviceHead._default_device = DEAFULT_DEVNO;
    SDeviceHead._sdev_active    = TRUE;
}

void sdev_terminate(void)
{
	SDeviceHead._sdev_active    = FALSE;
}

ER SDMSetupDevice(H devno, StorageDevice_t **ppsdev)
{
	StorageDevice_t *psdev;
	unsigned int    no;

	if(devno < MINIMUM_DEVNO || devno > MAXIMUM_DEVNO)
		return E_ID;
	if(SDeviceHead._num_activedev >= NUM_STORAGEDEVICE)
		return E_OBJ;
	for(no = 0, psdev = SDeviceHead._psd ; no < SDeviceHead._num_activedev ; no++, psdev++){
		if(devno == psdev->_sdev_devno)
			return E_ID;
	}
	psdev->_sdev_attribute = SDEV_ACTIVE;
	psdev->_sdev_devno     = devno;
	*ppsdev = psdev;
	SDeviceHead._num_activedev++;
	return E_OK;
}

ER_ID SDMGetDeviceNo(const char **ppathname)
{
	ER_ID devno = DEAFULT_DEVNO;
	const char *p = *ppathname;

	if(*p >= '0'&& *p <= '9'){
		devno = *p++ - '0';
		while(*p >= '0' && *p <= '9'){
			devno *= 10;
			devno  = *p++ - '0';
		}
		if(devno < MINIMUM_DEVNO || devno > MAXIMUM_DEVNO)
			devno = E_ID;
	}
	if(*p == ':')
		p++;
	*ppathname = p;
	return devno;
}

StorageDevice_t *SDMGetStorageDevice(int devno)
{
	StorageDevice_t *psdev = SDeviceHead._psd;
	unsigned int no;

    for(no = 0 ; no < SDeviceHead._num_activedev ; no++){
		if((psdev->_sdev_attribute & SDEV_ACTIVE) != 0
			 && psdev->_sdev_devno == devno)
			return psdev;
		psdev++;
	}
	return NULL;
}

ER SDMEmploy(StorageDevice_t *psdev, BOOL sw)
{
	if(psdev == 0)
		return E_PAR;
	if((psdev->_sdev_attribute & SDEV_ACTIVE) == 0)
		return E_PAR;
	if(sw)
		psdev->_sdev_attribute |= SDEV_EMPLOY;
	else
		psdev->_sdev_attribute &= ~SDEV_EMPLOY;
	return E_OK;
}

void SDMSence_task(VP_INT exinf)
{
	StorageDevice_t *psdev;
	unsigned int dno;
	BOOL         employ;

	while(SDeviceHead._sdev_active == TRUE){
		psdev = SDeviceHead._psd;
		for(dno = 0 ; dno < SDeviceHead._num_activedev ; dno++, psdev++){
			if((psdev->_sdev_attribute & SENSE_DEVICE) == SENSE_DEVICE){
				employ = (psdev->_sdev_attribute & SDEV_EMPLOY) != 0;
				if(!employ && psdev->pdevf->_sdevf_sense(psdev, employ) != 0){
					psdev->_sdev_attribute |= SDEV_EMPLOY;
                    if(psdev->_sdev_notice)
						psdev->_sdev_notice(psdev, TRUE);
				}
				else if((psdev->_sdev_attribute & SDEV_CHKREMOVE) != 0 && employ){
					if(psdev->pdevf->_sdevf_sense(psdev, employ) != 0){
						psdev->_sdev_attribute &= ~SDEV_EMPLOY;
	                    if(psdev->_sdev_notice)
							psdev->_sdev_notice(psdev, FALSE);
					}
				}
			}
		}
		dly_tsk(500);	/* wait 500ms */
#ifdef SDEV_SENSE_ONETIME
		break;
#endif
	}
}


