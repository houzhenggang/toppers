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
 *  @(#) $Id: diskutils.c,v 1.1 2010/06/07 16:39:56 roi Exp $
 */

#include <stdio.h>
#include "storagedevice.h"
#include "monitor.h"

#define MONVOLUME_FORMAT    0
#define MONVOLUME_DIR       1
#define MONVOLUME_MKDIR     2
#define MONVOLUME_RMDIR     3
#define MONVOLUME_DELETE    4

/*
 *  ɽ�����ޥ�ɥơ��֥�
 */
static struct SUBCOMMAND_TABLE const mon_volume[] = {
	{"FORMAT",		MONVOLUME_FORMAT },	/* �ܥ�塼��ե����ޥå� */
	{"DIR",			MONVOLUME_DIR },	/* �ǥ��쥯�ȥ�ɽ�� */
	{"MKDIR",		MONVOLUME_MKDIR },	/* �ǥ��쥯�ȥ���� */
	{"RMDIR",		MONVOLUME_RMDIR },	/* �ǥ��쥯�ȥ��� */
	{"ERASE",		MONVOLUME_DELETE }	/* �ե������� */
};

static struct dirent2 finfo;

/*
 *  ���ȥ졼���ܥ�塼�ॳ�ޥ��
 */
UW
volume_command(B *command)
{
	StorageDevice_t *psdev;
	struct statfs2  status;
	INT    point=0;
	B      cmd=0;
	char   *path, *spath, name[16];
	int    devno, no, count;
	void   *dir;

	count = sizeof(mon_volume) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_volume[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_volume[no].type;
				break;
			}
		}
	}
	switch(cmd){
	case MONVOLUME_FORMAT:			/* �ե����ޥå� */
		break;
	default:						/* �ǥե���� */
	case MONVOLUME_DIR:				/* �ǥ��쥯�ȥ�ɽ�� */
		spath = path = &command[point];
		devno = SDMGetDeviceNo((const char **)&path);
		psdev = SDMGetStorageDevice(devno);
		if(psdev == 0){
			printf("\nno device !\n");
			break;
		}
		if(psdev->pdevff == 0 || psdev->pdevff->_sdevff_opendir == 0){
			printf("\nno function !\n");
			break;
		}
		count = 0;
		dir = psdev->pdevff->_sdevff_opendir(spath);
		if(dir != NULL){
			if(*spath == 0){
				name[0] = devno + '0';
				name[1] = ':';
				name[2] = '/';
				name[3] = 0;
				spath = name;
			}
			printf("\nDirectory [%s]\n", spath);
			while(psdev->pdevff->_sdevff_readdir(dir, &finfo) != 0 && finfo.d_name[0] != 0){
				count++;
				printf("%3d %s ", count, finfo.d_name);
				no = strlen(finfo.d_name);
				while(no < 24){
					putchar(' ');
					no++;
				}
				printf("%04d/%02d/%02d ", (finfo.d_date>>9)+1980, (finfo.d_date>>5) & 15, finfo.d_date & 31);
				printf("%02d:%02d:%02d ", finfo.d_time>>11, (finfo.d_time>>5) & 63, (finfo.d_time & 31)*2);
				if(finfo.d_type & AM_HID)
					name[0] = '*';
				else
					name[0] = ' ';
				if(finfo.d_type & AM_SYS)
					name[1] = 'S';
				else
					name[1] = ' ';
				name[2] = 'R';
				if(finfo.d_type & AM_RDO)
					name[3] = ' ';
				else
					name[3] = 'W';
				name[4] = 0;
				if(finfo.d_type & AM_DIR)
					printf("<DIR>  \n");
				else if(finfo.d_type & AM_VOL)
					printf("<VOL>  \n");
				else
					printf("[%s]  %8d\n", name, (int)finfo.d_fsize);
			}
			printf("     %d file(s)\n", count);
			psdev->pdevff->_sdevff_closedir(dir);
			if(psdev->pdevff->_sdevff_statfs != 0
				 && psdev->pdevff->_sdevff_statfs(spath, &status) == 0){
				printf("     %d free blocks %d bytes in a block\n", status.f_bfree, status.f_bsize);
			}
		}
		break;
	case MONVOLUME_MKDIR:			/* �ǥ��쥯�ȥ�κ��� */
		spath = path = &command[point];
		if(*path != 0){
			devno = SDMGetDeviceNo((const char **)&path);
			psdev = SDMGetStorageDevice(devno);
			if(psdev == 0){
				printf("\nno device !\n");
				break;
			}
			if(psdev->pdevff == 0 || psdev->pdevff->_sdevff_mkdir == 0){
				printf("\nno function !\n");
				break;
			}
			printf(" mkdir[%s]\n", path);
			if(psdev->pdevff->_sdevff_mkdir(spath) >= 0)
				printf("   Ok\n");
			else
				printf("   Error\n");
		}
		break;
	case MONVOLUME_RMDIR:			/* �ǥ��쥯�ȥ�κ�� */
		spath = path = &command[point];
		if(*path != 0){
			devno = SDMGetDeviceNo((const char **)&path);
			psdev = SDMGetStorageDevice(devno);
			if(psdev == 0){
				printf("\nno device !\n");
				break;
			}
			if(psdev->pdevff == 0 || psdev->pdevff->_sdevff_rmdir == 0){
				printf("\nno function !\n");
				break;
			}
			printf(" rmdir[%s]\n", path);
			if(psdev->pdevff->_sdevff_rmdir(spath) >= 0)
				printf("   Ok\n");
			else
				printf("   Error\n");
		}
		break;
	case MONVOLUME_DELETE:			/* �ե�����κ�� */
		spath = path = &command[point];
		if(*path != 0){
			devno = SDMGetDeviceNo((const char **)&path);
			psdev = SDMGetStorageDevice(devno);
			if(psdev == 0){
				printf("\nno device !\n");
				break;
			}
			if(psdev->pdevff == 0 || psdev->pdevff->_sdevff_unlink == 0){
				printf("\nno function !\n");
				break;
			}
			printf(" unlink[%s]\n", path);
			if(psdev->pdevff->_sdevff_unlink(spath) >= 0)
				printf("   Ok\n");
			else
				printf("   Error\n");
		}
		break;
	}
	return 0;
}

