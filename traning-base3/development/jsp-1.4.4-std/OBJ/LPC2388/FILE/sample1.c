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
 *  �ե����륷���ƥ�Υƥ��ȥץ����
 * 
 * �ե륻�å���FatFs��ff.c, ff.h�ˤ�API��ư��ƥ��Ȥ�ԤäƤ��롣��Ͽ��
 * �ǥ����ϡ�FAT16�ޤ���FAT32�ǥե����ޥåȤ��졢�ޤ����ե������ǥ���
 * ���ȥ꤬�񤭹��ޤ�Ƥ��ʤ����֤����ꤷ�Ƥ��롣
 * �ƥ��ȹ��ܤ�ʲ��˼�����
 * 
 * ��f_write()�Υƥ���(fwrite)
 * ���ե�����data.txt��񤭹��ߥ⡼�ɤǥ����ץ󤹤롣
 * �����饹��������ޤ������񤭹��ߤ�Ԥ���
 * ���ե�����data.txt�򥯥������롣
 * 
 * ��f_read()�Υƥ���(fread)
 * ���ե�����data.txt���ɤ߽Ф��⡼�ɤǥ����ץ󤹤롣
 * �����饹��������ޤ������ɤ߽Ф���Ԥ��������ͤ���Ӥ�Ԥ���
 * 
 * ��f_lseek()�Υƥ���(fseek)
 * ���ե�����data.txt���ɤ߽Ф��⡼�ɤǥ����ץ󤹤롣
 * ����2���饹������Ƭ�������˥��������롣
 * ���������������֤����ɤ߽Ф���Ԥ��������ͤ���Ӥ��롣
 * 
 * ��f_mkdir(), f_opendir()�Υƥ���(mkdir, opendir)
 * ��/sub1, /sub1/sub2, sub1/sub2/sub3�ν�˥ǥ��쥯�ȥ���������
 * �������뤳�Ȥ��ǧ���롣
 * 
 * ��f_readdir()�Υƥ���(readdir)
 * ����ǥ����˵�Ͽ����Ƥ��뤹�٤ƤΥե�����̾�ȥǥ��쥯�ȥ�̾��Ƶ�
 * ��Ū���ɤ߽Ф���
 * ��/data.txt, /sub1, /sub1/sub2, sub1/sub2/sub3���ɤ߽Ф���С�������
 * 
 * ��f_chmod(), f_stat()�Υƥ���(chmod, stat)
 * ���ե�����stat.txt��������롣
 * ��stat.txt�Υե�����°�����ɤ߽Ф���
 * ��stat.txt���ɤ߼�����ѤΥե�����°�������ꤹ�롣
 * ��stat.txt�Υե�����°������١��ɤ߽Ф����ɤ߼�����ѤΥե�����°
 * ���������ꤵ��Ƥ��뤳�Ȥ��ǧ���롣�ʢ���
 * 
 * ����������Ͽ��ǥ�����æ���ǽ�ʾ��ϥѥ������Ǥ�ե�����°����
 * ����������ǧ���롣
 * ��
 * ��f_unlink()�Υƥ���(unlink)
 * ���ե�����unlink.txt��������롣
 * ��unlink.txt�������롣
 * ��unlink.txt���������Ƥ��뤳�Ȥ��ǧ���롣�ʢ���
 * 
 * ����������Ͽ��ǥ�����æ���ǽ�ʾ��ϥѥ������Ǥ�ե����뤬���
 * ������������Ƥ��뤳�Ȥ��ǧ���롣
 * 
 * ��f_rename()�Υƥ���(rename)
 * ���ե�����old.txt��������롣
 * ��old.txt��new.txt�˥�͡��ह�롣
 * ��old.txt��¸�ߤ��ʤ����Ȥ��ǧ���롣�ʢ���
 * ��new.txt��¸�ߤ��뤳�Ȥ��ǧ���롣���ʢ���
 * 
 * ����������Ͽ��ǥ�����æ���ǽ�ʾ��ϥѥ������Ǥ�ե����뤬
 * ����������͡��व��Ƥ��뤳�Ȥ��ǧ���롣
 * 
 * ��f_getfree()�Υƥ���(statfs)
 * ��f_getfree()�Ƕ������饹��������롣
 * ���������饹������Х��ȿ��˴������ơ���ɽ�����롣�ʢ���
 * ��
 * ����������Ͽ��ǥ�����æ���ǽ�ʾ��ϥѥ������Ǥ�������̤�
 * ����������ǧ���롣
 * 
 * �ƥ��Ȥ������������Υ���ʲ��˼�����
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
 * �������ο��ͤϡ����Ѥ��뵭Ͽ��ǥ����Υ������ˤ�äưۤʤ롣
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

#define DRIVE0		0u		/*  �ɥ饤���ֹ�  */
#define FDISK_FORMAT	0u		/*  �ե����ޥåȼ���  */

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
#define NEW_FILENAME	"new.txt"	/*  �ɥ饤���ֹ�Ϥ���ʤ�  */
#define FNEW_FILENAME   ROOT_DIR "/new.txt"

#define SUB_DIR1	ROOT_DIR "/sub1"
#define SUB_DIR2	ROOT_DIR "/sub1/sub2"
#define SUB_DIR3	ROOT_DIR "/sub1/sub2/sub3"

#define SECTOR_SIZE	512UL	/*  ���������������ʥХ���ñ�̡�  */
#define CLUSTER_SIZE	4U	/*  ���饹�����������ʥ�����ñ�̡�  */
#define WAIT_SYSLOG	500	/*  syslog()��ɽ���Ԥ�����  */
#define WORD_MAX	0xffffUL	/*  WORD���κ�����  */

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
 *  �ᥤ�󥿥���
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
	 *  RTC���Хåƥ�Хå����åפǤʤ����ᡢ���������
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
	 *  SD�����ɥե����륷���ƥ��MCI�ν����
	 */
	_sd_init();

	/*
	 *  �������κ�ɽ��
	 */
	rtc_get_time(&timedate);
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
	first_time = FALSE;

	/*
	 *  SD�����ɸ����Ԥ�
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
	 *  �Ƽ�ƥ��ȴؿ��θƤӽФ�
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
 *  �񤭹��ߤ��ɤ߽Ф��ƥ���
 *����ʣ�����饹���ˤޤ�����褦�ˤ��롣
 *����
 *��������
 *������FATFS *fs���ե����륷���ƥ�Υ�����ꥢ����Ƭ���ɥ쥹
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
	 *���񤭹���ǡ����������η׻�
	 *������ʣ�����饹���ˤޤ�����褦�ˤ��롣
	 *�������嵭��open()�ƤӽФ��ǡ�������ꥢ��������Ѥߤ�
	 *���������뤳�Ȥ��ݾڤ���롣
	 */
	data_length = strlen(test_data);
	assert(data_length <= WORD_MAX);
	total = clstsize * SECTOR_SIZE;
	assert((total / data_length) <= (INT_MAX - 2UL));
	times = (UINT)((total / data_length) + 2UL);

	/*  �񤭹��ߥƥ���  */
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

	/*  �ɤ߽Ф��ƥ���  */
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
 *  �񤭹��ߤ��ɤ߽Ф��ƥ���
 *����ʣ�����饹���ˤޤ�����褦�ˤ��롣
 *����
 *��������
 *������FATFS *fs���ե����륷���ƥ�Υ�����ꥢ����Ƭ���ɥ쥹
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
	 *���񤭹���ǡ����������η׻�
	 *������ʣ�����饹���ˤޤ�����褦�ˤ��롣
	 *�������嵭��f_open()�ƤӽФ��ǡ�������ꥢ��������Ѥߤ�
	 *���������뤳�Ȥ��ݾڤ���롣
	 */
	data_length = strlen(test_data);
	assert(data_length <= WORD_MAX);
	total = clstsize * SECTOR_SIZE;
	assert((total / data_length) <= (INT_MAX - 2UL));
	times = (UINT)((total / data_length) + 2UL);
	
	/*  �񤭹��ߥƥ���  */
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

	/*  �ɤ߽Ф��ƥ���  */
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
 *  seek�Υƥ���
 *����ʣ�����饹���ˤޤ�����褦�ˤ��롣
 *����
 *��������
 *������FATFS *fs���ե����륷���ƥ�Υ�����ꥢ����Ƭ���ɥ쥹
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
	 *�����������륪�ե��åȤη׻�
	 *�����裲���饹������ã����褦�ˤ��롣
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
 *�����ꤵ�줿�ǥ��쥯�ȥ�ʲ��Υǥ��쥯�ȥ�ȥե������
 *���ʺƵ�Ū�ˡˤ��٤�ɽ�����롣
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
 *���ƥ����Ѥ˥ե�������롣
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
	/*  �ե����뤬�Ǥ��Ƥ��뤳�Ȥγ�ǧ  */
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
	/*  �ե����뤬�Ǥ��Ƥ��뤳�Ȥγ�ǧ  */
	result = stat(UNLNK_FILENAME, &finfo);
	assert(result == 0);

	result = unlink(UNLNK_FILENAME);
	assert(result == 0);

	/*  �ե����뤬�������Ƥ��뤳�Ȥγ�ǧ  */
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
	/*  �ե����뤬�Ǥ��Ƥ��뤳�Ȥγ�ǧ  */
	result = stat(OLD_FILENAME, &finfo);
	assert(result == 0);

	result = rename(OLD_FILENAME, NEW_FILENAME);
	assert(result == 0);

	/*  �ե����뤬��͡��व��Ƥ��뤳�Ȥγ�ǧ  */
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
