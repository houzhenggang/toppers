/*
 *  FatFs for TOPPERS
 *      FAT File system/
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2007- by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 */

/*--------------------------------------------------------------------------/
/  FatFs - FAT file system module  R0.09                     (C)ChaN, 2007
/---------------------------------------------------------------------------/
/ FatFs module is an experimenal project to implement FAT file system to
/ cheap microcontrollers. This is a free software and is opened for education,
/ research and development under license policy of following trems.
/
/  Copyright (C) 2007, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is no warranty.
/ * You can use, modify and/or redistribute it for personal, non-profit or
/   profit use without any restriction under your responsibility.
/ * Redistributions of source code must retain the above copyright notice.
/---------------------------------------------------------------------------*/

/* 
 *  ファイルシステムのテストプログラム
 * 
 * フルセット版FatFs（ff.c, ff.h）のAPIの動作テストを行っている。記録メ
 * ディアは、FAT16またはFAT32でフォーマットされ、まだ、ファイルやディレ
 * クトリが書き込まれていない状態を想定している。
 * テスト項目を以下に示す。
 * 
 * ・f_write()のテスト(fwrite)
 * 　ファイルdata.txtを書き込みモードでオープンする。
 * 　クラスタ境界をまたいだ書き込みを行う。
 * 　ファイルdata.txtをクローズする。
 * 
 * ・f_read()のテスト(fread)
 * 　ファイルdata.txtを読み出しモードでオープンする。
 * 　クラスタ境界をまたいだ読み出しを行い、期待値と比較を行う。
 * 
 * ・f_lseek()のテスト(fseek)
 * 　ファイルdata.txtを読み出しモードでオープンする。
 * 　第2クラスタの先頭セクタにシークする。
 * 　シークした位置から読み出しを行い、期待値と比較する。
 * 
 * ・f_mkdir(), f_opendir()のテスト(mkdir, opendir)
 * 　/sub1, /sub1/sub2, sub1/sub2/sub3の順にディレクトリを作成し、
 * 　開けることを確認する。
 * 
 * ・f_readdir()のテスト(readdir)
 * 　メディアに記録されているすべてのファイル名とディレクトリ名を再帰
 * 　的に読み出す。
 * 　/data.txt, /sub1, /sub1/sub2, sub1/sub2/sub3が読み出せれば、成功。
 * 
 * ・f_chmod(), f_stat()のテスト(chmod, stat)
 * 　ファイルstat.txtを作成する。
 * 　stat.txtのファイル属性を読み出す。
 * 　stat.txtに読み取り専用のファイル属性を設定する。
 * 　stat.txtのファイル属性を再度、読み出し、読み取り専用のファイル属
 * 　性が設定されていることを確認する。（※）
 * 
 * 　　※　記録メディアが脱着可能な場合はパソコン上でもファイル属性を
 * 　　　　確認する。
 * 　
 * ・f_unlink()のテスト(unlink)
 * 　ファイルunlink.txtを作成する。
 * 　unlink.txtを削除する。
 * 　unlink.txtが削除されていることを確認する。（※）
 * 
 * 　　※　記録メディアが脱着可能な場合はパソコン上でもファイルが削除
 * 　　　　されていることを確認する。
 * 
 * ・f_rename()のテスト(rename)
 * 　ファイルold.txtを作成する。
 * 　old.txtをnew.txtにリネームする。
 * 　old.txtが存在しないことを確認する。（※）
 * 　new.txtが存在することを確認する。　（※）
 * 
 * 　　※　記録メディアが脱着可能な場合はパソコン上でもファイルが
 * 　　　　リネームされていることを確認する。
 * 
 * ・f_getfree()のテスト(statfs)
 * 　f_getfree()で空きクラスタ数を求める。
 * 　空きクラスタ数をバイト数に換算して、ログ表示する。（※）
 * 　
 * 　　※　記録メディアが脱着可能な場合はパソコン上でも空き容量を
 * 　　　　確認する。
 * 
 * テストが成功した場合のログを以下に示す。
 * 
 * System logging task is started on port 1.
 * Sample program starts (exinf = 0).
 * test write: OK
 * test read: OK
 * test seek: OK
 * test mkdir: OK
 * Dir: 0:/
 * File: 0:/data.txt
 * Dir: 0:/sub1/
 * Dir: 0:/sub1/sub2/
 * Dir: 0:/sub1/sub2/sub3/
 * Check read only attribute of file 0:/stat.txt by PC.
 * test stat: OK
 * test rename: OK
 * test unlink: OK
 * Waiting for f_getfree() .....
 * 2043789312(0x79d1c000) bytes available on the disk.
 * 　→この数値は、使用する記録メディアのサイズによって異なる。
 * Check free space by PC.
 * test getfree: OK
 * -- buffered messages --
 * Sample program ends.
 * 
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include <t_services.h>
#include "kernel_id.h"
#include "board_config.h"
#include "sample1.h"
#include "storagedevice.h"
#include "ff.h"
#include "fcntl.h"

#define DRIVE0		0u		/*  ドライブ番号  */
#define FDISK_FORMAT	0u		/*  フォーマット種別  */

#if 1
#define ROOT_DIR	"0:"
#else
#define ROOT_DIR	"1:"
#endif

#define FILENAME	ROOT_DIR "/data.txt"
#define FILENAME2	ROOT_DIR "/data2.txt"
#define STAT_FILENAME	ROOT_DIR "/stat.txt"
#define UNLNK_FILENAME	ROOT_DIR "/unlink.txt"
#define OLD_FILENAME	ROOT_DIR "/old.txt"
#define NEW_FILENAME	"new.txt"	/*  ドライブ番号はいらない  */
#define FNEW_FILENAME   ROOT_DIR "/new.txt"

#define SUB_DIR1	ROOT_DIR "/sub1"
#define SUB_DIR2	ROOT_DIR "/sub1/sub2"
#define SUB_DIR3	ROOT_DIR "/sub1/sub2/sub3"

#define SECTOR_SIZE	512UL	/*  セクタ・サイズ（バイト単位）  */
#define CLUSTER_SIZE	4U	/*  クラスタ・サイズ（セクタ単位）  */
#define WAIT_SYSLOG	500	/*  syslog()の表示待ち時間  */
#define WORD_MAX	0xffffUL	/*  WORD型の最大値  */

#define BUF_SIZE	300

/* sys/dirent.h */
struct dirent {
  unsigned long  d_fileno;		/* file number of entry */
  unsigned short d_reclen;		/* length of this record */
  unsigned char  d_type; 		/* file type, see below */
  unsigned char  d_namlen;		/* length of string in d_name */
#define	MAXNAMLEN	255
  char	d_name[MAXNAMLEN + 1];	/* name must be no longer than this */
};

/* File types */
#define DT_UNKMOWN  0
#define DT_FIFO     1
#define DT_CHAR     2
#define DT_DIR      4
#define DT_BLK      6
#define DT_REG      8
#define DT_LNK      10
#define DT_SOCK     12
#define DT_WHT      14

const static char test_data[] = 
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static const char monthday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static char buff[BUF_SIZE + 1];
static BOOL first_time = TRUE;

static void test_read_write(int clstsize);
static void test_seek(int clstsize);
static void test_mkdir(void);
static void test_dir(void);
static void scan_files (char* path);
static void test_read_write2(clstsize);

static void make_file(char *filename);
static void test_stat(void);
static void test_rename(void);
static void test_unlink(void);
static void test_getfree(void);

static int get_fat_time(void)
{
#ifndef SAMPLE_PROGRAM
	struct tm2 timedate;
	int    reqtime = 0;

	rtc_get_time(&timedate);
	reqtime  = ((timedate.tm_year-10)<<25)+(timedate.tm_mon<<21)+(timedate.tm_mday<<16);
	reqtime += (timedate.tm_hour<<11)+(timedate.tm_min<<5)+(timedate.tm_sec/2);
#else
	reqtime = 0x00210000;
#endif
	return reqtime;
}

/*
 *  メインタスク
 */
void main_task(VP_INT exinf)
{
	int  result;
	StorageDevice_t *psdev;
	FATFS   *fs;
	struct tm2 timedate;

	if(first_time == FALSE)
		goto start_test;

	vmsk_log(LOG_UPTO(LOG_NOTICE), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*
	 *  RTCがバッテリバックアップでないため、時刻の設定
	 */
	timedate.tm_sec = 0;
	timedate.tm_min = 0;
	timedate.tm_hour = 14;
	timedate.tm_mday = 23;
	timedate.tm_mon = 7;
	timedate.tm_year = 2011-1970;
	timedate.tm_isdst = 0;
	mktime((struct tm *)&timedate);
	rtc_set_time(&timedate);
	rtc_start(NULL);
	SDeviceHead._get_datetime = get_fat_time;

	/*
	 *  SDカードファイルシステムとMCIの初期化
	 */
	_sd_init();

	/*
	 *  設定時刻の再表示
	 */
	rtc_get_time(&timedate);
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
	first_time = FALSE;

	/*
	 *  SDカード検出待ち
	 */
start_test:
	psdev = SDMGetStorageDevice(0);
	fs = (FATFS *)psdev->_sdev_local[0];

	while((psdev->_sdev_attribute & SDEV_EMPLOY) == 0){
		SDMSence_task(0);
	}
	syslog_0(LOG_NOTICE, "found sdcard !");
	dly_tsk(5000);
	syslog_0(LOG_NOTICE, "start test !");

	/*
	 *  各種テスト関数の呼び出し
	 */
	test_read_write(fs->csize);
	test_seek(fs->csize);
	test_mkdir();
	test_dir();
	test_stat();
	test_rename();
	test_unlink();
	test_read_write2(fs->csize);
	test_getfree();

	syslog(LOG_NOTICE, "Sample program ends.");
	dly_tsk(200);
	ext_tsk();
	kernel_exit();
}


/*
 *  書き込みと読み出しテスト
 *　　複数クラスタにまたがるようにする。
 *　　
 *　　引数
 *　　　FATFS *fs：ファイルシステムのワークエリアの先頭アドレス
 */
static 
void test_read_write(int clstsize)
{
	int	cmp;
	UINT	times, i;
	UINT	n;
	size_t	data_length, total;
	FILE    *fid;
	int     result;

	fid = fopen(FILENAME, "rwb");
	assert(fid != NULL);

	/*
	 *　書き込むデータサイズの計算
	 *　　・複数クラスタにまたがるようにする。
	 *　　・上記のopen()呼び出しで、ワークエリアが初期化済みで
	 *　　　あることが保証される。
	 */
	data_length = strlen(test_data);
	assert(data_length <= WORD_MAX);
	total = clstsize * SECTOR_SIZE;
	assert((total / data_length) <= (INT_MAX - 2UL));
	times = (UINT)((total / data_length) + 2UL);

	/*  書き込みテスト  */
	for(i = 0; i < times; ++i) {
		n = fwrite(test_data, data_length, 1, fid);
		if (n != data_length) {
			syslog(LOG_NOTICE, "test write: Error!");
			dly_tsk(WAIT_SYSLOG);
			syslog(LOG_NOTICE, "   %dth trial is failed.", i);
			dly_tsk(WAIT_SYSLOG);
			syslog(LOG_NOTICE, "test read: Skip");
			dly_tsk(WAIT_SYSLOG);
			fclose(fid);
			return;
		}
	}
	syslog(LOG_NOTICE, "test write: OK");
	dly_tsk(WAIT_SYSLOG);

	result = fclose(fid);
	assert(result == 0);

	fid = fopen(FILENAME, "rb");
	assert(fid != NULL);

	/*  読み出しテスト  */
	for(i = 0; i < times; ++i) {
		buff[0] = '\0';
		buff[BUF_SIZE] = '\0';
		n = fread(buff, data_length, 1, fid);
		assert(n == data_length);
		cmp = strncmp(test_data, buff, data_length);
		assert(cmp == 0);
	}
	syslog(LOG_NOTICE, "test read: OK");
	dly_tsk(WAIT_SYSLOG);

	result = fclose(fid);
	assert(result == 0);
}

/*
 *  書き込みと読み出しテスト
 *　　複数クラスタにまたがるようにする。
 *　　
 *　　引数
 *　　　FATFS *fs：ファイルシステムのワークエリアの先頭アドレス
 */
static 
void test_read_write2(int clstsize)
{
	int	cmp;
	FILE    *fid;
	UINT	times, i;
	UINT	n;
	size_t	data_length, total;
	int     result;

	fid = fopen(FILENAME2, "wb");
	assert(fid != NULL);

	/*
	 *　書き込むデータサイズの計算
	 *　　・複数クラスタにまたがるようにする。
	 *　　・上記のf_open()呼び出しで、ワークエリアが初期化済みで
	 *　　　あることが保証される。
	 */
	data_length = strlen(test_data);
	assert(data_length <= WORD_MAX);
	total = clstsize * SECTOR_SIZE;
	assert((total / data_length) <= (INT_MAX - 2UL));
	times = (UINT)((total / data_length) + 2UL);
	
	/*  書き込みテスト  */
	for(i = 0; i < times; ++i) {
		n = fwrite(test_data, data_length, 1, fid);
		if (n != data_length) {
			syslog(LOG_NOTICE, "test fwrite: Error!");
			dly_tsk(WAIT_SYSLOG);
			syslog(LOG_NOTICE, "   %dth trial is failed.", i);
			dly_tsk(WAIT_SYSLOG);
			syslog(LOG_NOTICE, "test fread: Skip");
			dly_tsk(WAIT_SYSLOG);
			fclose(fid);
			return;
		}
	}
	syslog(LOG_NOTICE, "test fwrite: OK");
	dly_tsk(WAIT_SYSLOG);

	result = fclose(fid);
	assert(result == 0);

	fid = fopen(FILENAME2, "rb");
	assert(fid != NULL);

	/*  読み出しテスト  */
	for(i = 0; i < times; ++i) {
		buff[0] = '\0';
		buff[BUF_SIZE] = '\0';
		n = fread(buff, data_length, 1, fid);
		assert(n == data_length);
		cmp = strncmp(test_data, buff, data_length);
		assert(cmp == 0);
	}
	syslog(LOG_NOTICE, "test fread: OK");
	dly_tsk(WAIT_SYSLOG);

	result = fclose(fid);
	assert(result == 0);
	unlink(FILENAME2);
}

/*
 *  seekのテスト
 *　　複数クラスタにまたがるようにする。
 *　　
 *　　引数
 *　　　FATFS *fs：ファイルシステムのワークエリアの先頭アドレス
 */
static 
void test_seek(int clstsize)
{
	int	cmp;
	UINT	n;
	size_t	data_length;
	long	cluster_size;
	FILE    *fid;
	long    offset;
	int     result;

	/*
	 *　シークするオフセットの計算
	 *　　第２クラスタに到達するようにする。
	 */
	data_length = strlen(test_data);
	cluster_size = clstsize * SECTOR_SIZE;
	offset = cluster_size - (cluster_size % data_length);

	fid = fopen(FILENAME, "rb");
	assert(fid != NULL);

	result =fseek(fid, offset, SEEK_SET);
	assert(result == offset);

	buff[0] = '\0';
	buff[BUF_SIZE] = '\0';
	n = fread(buff, data_length, 1, fid);
	if (n != data_length) {
		syslog(LOG_NOTICE, "test seek: Error(data length error)");
		dly_tsk(WAIT_SYSLOG);
		fclose(fid);
		return;
	}
	cmp = strncmp(test_data, buff, data_length);
	assert(cmp == 0);

	syslog(LOG_NOTICE, "test seek: OK");
	dly_tsk(WAIT_SYSLOG);

	fclose(fid);
}

static 
void test_mkdir(void)
{
	int result;
	void *dirent;

	result = mkdir(SUB_DIR1);
	assert(result == 0);
	dirent = opendir(SUB_DIR1);
	assert(dirent != NULL);
	closedir(dirent);

	result = mkdir(SUB_DIR2);
	assert(result == 0);
	dirent = opendir(SUB_DIR2);
	assert(dirent != NULL);
	closedir(dirent);

	result = mkdir(SUB_DIR3);
	assert(result == 0);
	dirent = opendir(SUB_DIR3);
	assert(dirent != 0);
	closedir(dirent);

	syslog(LOG_NOTICE, "test mkdir: OK");
#if 0	/* ROI DEBUG */
	rmdir(SUB_DIR3);
	rmdir(SUB_DIR2);
	rmdir(SUB_DIR1);
#endif	/* ROI DEBUG */
	dly_tsk(WAIT_SYSLOG);
}

static 
void test_dir(void)
{
	strcpy(buff, ROOT_DIR);
	scan_files(buff);
	rmdir(SUB_DIR3);
	rmdir(SUB_DIR2);
	rmdir(SUB_DIR1);
}


/*
 *　指定されたディレクトリ以下のディレクトリとファイルを
 *　（再帰的に）すべて表示する。
 */
static 
void scan_files (char* path)
{
    size_t i;
	void *dir;
	struct dirent *pdirent;

    if ((dir = opendir(path)) != NULL) {
        syslog(LOG_NOTICE, "Dir: %s/", path);
		dly_tsk(WAIT_SYSLOG);

        i = strlen(path);
        while ((pdirent = readdir(dir)) != NULL && pdirent->d_name[0] >= ' ') {
            if (pdirent->d_type == DT_DIR) {
                sprintf(path+i, "/%s", pdirent->d_name);
                scan_files(path);
                *(path+i) = '\0';
            } else {
                syslog(LOG_NOTICE, "File: %s/%s", path, pdirent->d_name);
				dly_tsk(WAIT_SYSLOG);
            }
        }
		closedir(dir);
    }
}


/*
 *　テスト用にファイルを作る。
 */
static 
void make_file(char *filename)
{
	size_t	data_length;
	UINT	n;
	FILE    *fid;
	int     result;

	data_length = strlen(test_data);

	fid = fopen(filename, "wb");
	assert(fid != NULL);

	n = fwrite(test_data, data_length, 1, fid);
	assert(n == data_length);

	result = fclose(fid);
	assert(result == 0);
}


void test_stat(void)
{
	struct stat finfo;
	int    result;
	FILE   *fid;

	make_file(STAT_FILENAME);
	/*  ファイルができていることの確認  */
	fid = fopen(STAT_FILENAME, "rb");
	assert(fid != NULL);
	fclose(fid);
	result = stat(STAT_FILENAME, &finfo);
	assert(result == 0);

	// Set read-only flag , clear archive flag and others are not changed.
	result = chmod(STAT_FILENAME, 0x222);
	assert(result == 0);

	result = stat(STAT_FILENAME, &finfo);
	assert(result == 0);

	syslog(LOG_NOTICE, "Check read only attribute of file %s by PC.",
		STAT_FILENAME);
	syslog(LOG_NOTICE, "fsize=%d fdate=0x%x ftime=0x%x attr=0x%x", finfo.st_size, finfo.st_atime, finfo.st_mtime, finfo.st_mode);
	syslog(LOG_NOTICE, "test stat: OK");
	unlink(STAT_FILENAME);
	dly_tsk(WAIT_SYSLOG);
}

static 
void test_unlink(void)
{
	struct stat finfo;
	int    result;

	make_file(UNLNK_FILENAME);
	/*  ファイルができていることの確認  */
	result = stat(UNLNK_FILENAME, &finfo);
	assert(result == 0);

	result = unlink(UNLNK_FILENAME);
	assert(result == 0);

	/*  ファイルが削除されていることの確認  */
	result = stat(UNLNK_FILENAME, &finfo);
	assert(result != 0);

	syslog(LOG_NOTICE, "test unlink: OK");
	dly_tsk(WAIT_SYSLOG);
}

static 
void test_rename(void)
{
	struct stat finfo;
	int    fid, result;

	make_file(OLD_FILENAME);
	/*  ファイルができていることの確認  */
	result = stat(OLD_FILENAME, &finfo);
	assert(result == 0);

	result = rename(OLD_FILENAME, NEW_FILENAME);
	assert(result == 0);

	/*  ファイルがリネームされていることの確認  */
	result = stat(OLD_FILENAME, &finfo);
	assert(result != 0);

	result = stat(NEW_FILENAME, &finfo);
	assert(result == 0);
	unlink(FNEW_FILENAME);

	syslog(LOG_NOTICE, "test rename: OK");
	dly_tsk(WAIT_SYSLOG);
}

static 
void test_getfree(void)
{
	struct statfs2 status;
	int result;
	long fsize;

	// Get free clusters
	syslog(LOG_NOTICE, "Waiting for f_getfree() .....");
	result = statfs(ROOT_DIR, &status);
	assert(result == 0);

    	// Get free bytes
	fsize = status.f_bsize * status.f_bfree;
	syslog(LOG_NOTICE, "%u(0x%x) bytes available on the disk.", 
		fsize, fsize);
	syslog(LOG_NOTICE, "Check free space by PC.");

	syslog(LOG_NOTICE, "test getfree: OK");
	dly_tsk(WAIT_SYSLOG);
}
