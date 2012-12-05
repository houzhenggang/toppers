/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010      by GJ Designing Center RICOH COMPANY,LTD. JAPAN
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
 *  表示コマンドテーブル
 */
static struct SUBCOMMAND_TABLE const mon_volume[] = {
	{"FORMAT",		MONVOLUME_FORMAT },	/* ボリュームフォーマット */
	{"DIR",			MONVOLUME_DIR },	/* ディレクトリ表示 */
	{"MKDIR",		MONVOLUME_MKDIR },	/* ディレクトリ作成 */
	{"RMDIR",		MONVOLUME_RMDIR },	/* ディレクトリ削除 */
	{"ERASE",		MONVOLUME_DELETE }	/* ファイル削除 */
};

static struct dirent2 finfo;

/*
 *  ストレージボリュームコマンド
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
	case MONVOLUME_FORMAT:			/* フォーマット */
		break;
	default:						/* デフォルト */
	case MONVOLUME_DIR:				/* ディレクトリ表示 */
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
	case MONVOLUME_MKDIR:			/* ディレクトリの作成 */
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
	case MONVOLUME_RMDIR:			/* ディレクトリの削除 */
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
	case MONVOLUME_DELETE:			/* ファイルの削除 */
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

