/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: devtest.c,v 1.1 2012/07/08 13:35:29 roi Exp $
 */

/* 
 *  サンプルプログラム(1)の本体
 *
 *  RTCをテストプログラム．
 *
 *  プログラムの概要:
 *
 *  1.RTCに日時設定する．
 *  2.2分後にアラーム設定する．
 *  3.年と秒のインクリメント割込みを設定する.
 *  4.割込み発生時、または２秒ごとに日時を表示する.
 *    これを202秒間繰り返す
 *  5.終了日時を表示する．
 *
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "config.h"
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

/* sys/dirent.h */
struct dirent {
  unsigned long  d_fileno;		/* file number of entry */
  unsigned short d_reclen;		/* length of this record */
  unsigned char  d_type; 		/* file type, see below */
  unsigned char  d_namlen;		/* length of string in d_name */
#define	MAXNAMLEN	255
  char	d_name[MAXNAMLEN + 1];	/* name must be no longer than this */
};

const static char test_data[] = 
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
  "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static BOOL alarm_on;
static char buff[BUF_SIZE + 1];
static ID   test_task;

static alarm_event(int event)
{
	alarm_on = TRUE;
	iwup_tsk(test_task);
	syslog_1(LOG_NOTICE, "alarmevent[%08x] !", event);
}

/*
 *  RTCテスト
 */
void rtc_test(VP_INT exinf)
{
	SYSTIM stime;
	int i;
	time_t time;
	struct tm timedate;

	timedate.tm_min += 2;
	timedate.tm_hour = -1;
	timedate.tm_mday = -1;
	timedate.tm_mon = -1;
	timedate.tm_year = -1;
	timedate.tm_wday = -1;
	timedate.tm_yday = -1;
	timedate.tm_isdst = -1;
	syscall(rtc_set_alarm((struct tm2 *)&timedate));	/* アラームの設定 */
	syslog_0(LOG_NOTICE, "set alarm date/time");

	timedate.tm_sec = -1;
	timedate.tm_min = 0;
	timedate.tm_year = 0;
	syscall(rtc_set_event((struct tm2 *)&timedate));	/* 秒と年のインクリメント割込みを設定 */

	alarm_on = FALSE;
	syscall(get_tid(&test_task));
	syscall(rtc_start(alarm_event));
	syslog_0(LOG_NOTICE, "RTC start");

	for(i = 0 ; i < 101 ; i++) {
		syscall(rtc_get_time((struct tm2 *)&timedate));
		get_tim(&stime);
		syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
		syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
		syslog_3(LOG_NOTICE, "count[%d] alarm[%d] systime[%d]", i, alarm_on, stime);
		tslp_tsk(2000);
		alarm_on = FALSE;
	}
	syscall(rtc_get_time((struct tm2 *)&timedate));	/* 終了時刻の取り出し */
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);

	syslog(LOG_NOTICE, "Sample program ends.");
	memset(&timedate, 0xff, sizeof(struct tm));
	syscall(rtc_set_alarm((struct tm2 *)&timedate));	/* アラームの設定 */
	syscall(rtc_set_event((struct tm2 *)&timedate));	/* 秒と年のインクリメント割込みを設定 */
}

/*
 *  FILEテスト
 */
void file_test(VP_INT exinf)
{
	int  result;
	StorageDevice_t *psdev;
	FATFS   *fs;

	/*
	 *  SDカード検出待ち
	 */
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

