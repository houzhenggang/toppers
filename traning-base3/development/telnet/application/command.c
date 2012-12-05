/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010-2011 by GJ Business Division RICOH COMPANY,LTD.
 *                   JAPAN
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
 *  @(#) $Id: command.c,v 1.2 2012/07/08 14:17:29 roi Exp $
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "config.h"
#include "shell.h"

extern void copy_file_func(FILE *sst, FILE *dst);

static int cmd_date(int argc, char **argv);
static int cmd_cd(int argc, char **argv);
static int cmd_ls(int argc, char **argv);
static int cmd_cat(int argc, char **argv);
static int cmd_echo(int argc, char **argv);
static int cmd_mkdir(int argc, char **argv);
static int cmd_rmdir(int argc, char **argv);
static int cmd_rm(int argc, char **argv);
static int cmd_mon(int argc, char **argv);
static int cmd_help(int argc, char **argv);
static int cmd(int argc, char **argv);

const command_type command_table[] = {
	{"date",	cmd_date},
	{"cd",      cmd_cd},
	{"ls",      cmd_ls},
	{"cat",     cmd_cat},
	{"echo",    cmd_echo},
	{"mkdir",   cmd_mkdir},
	{"rmdir",   cmd_rmdir},
	{"rm",      cmd_rm},
	{"mon",		cmd_mon},
	{"help",    cmd_help},
	{"cmd",		cmd},
	{0,			0}
};

static const char noargment[]   = "\nno arguments !\n\015";
static const char nodevice[]    = "\nno device !\n\015";
static const char nodirectory[] = "\nno directory !\n\015";
static const char nofile[]      = "\nno file !\n\015";

static struct dirent2 finfo;
static char   fname[256];

/*
 *  16進コード作成
 */
static char make_hex(int data)
{
	char h;

	if(data < 10)
		return data + '0';
	else
		return data - 10 + 'A';
}

/*
 *  日付・時間の設定表示
 */
static int cmd_date(int argc, char **argv)
{
	struct tm timedate;
	time_t ctime;
	int    tim[6], skipcnt = 0;
	char   *ps, *pd;
	ER     ercd;
	int    i, ii;

	if(argc < 2){
		time(&ctime);
		gmtime_r(&ctime, &timedate);
		printf("%02d/%02d  %02d:%02d:%02d %04d\n",
			timedate.tm_mon, timedate.tm_mday,
			timedate.tm_hour, timedate.tm_min,
			timedate.tm_sec, timedate.tm_year+1970);
	}
	else if(argc > 2){
		ps = argv[1];
		pd = argv[2];
		if(*ps == '-' && *(ps+1) == 's' && *pd == '"'){
			ercd = rtc_get_time((struct tm2 *)&timedate);
			tim[0] = 0;
			while((*pd > '9' || *pd < '0') && *pd != 0)
				pd++;		/* skip not decmal */
			for(i = 0 ; *pd != 0 && i < 6 ; pd++){
				if(*pd >= '0' && *pd <= '9'){
					tim[i] *= 10;
					tim[i] += *pd - '0';
					skipcnt = 0;
				}
				else{
					if(skipcnt == 0)
						tim[++i] = 0;
					skipcnt++;
				}
			}
			ii = i;
			for(i = 0 ; i < ii ; i++){
				switch(i){
				case 0:
	 				timedate.tm_mon  = tim[0];
					break;
				case 1:
					timedate.tm_mday = tim[1];
					break;
				case 2:
					timedate.tm_hour = tim[2];
					break;
				case 3:
					timedate.tm_min  = tim[3];
					break;
				case 4:
					timedate.tm_sec  = tim[4];
					break;
				case 5:
					timedate.tm_year = tim[5]-1970;
					break;
				default:
					break;
				}
			}
			rtc_set_time((struct tm2 *)&timedate);
		}
		else
			printf("date [-s [\"mm/dd hh:mm:ss year\"]]\n");
	}
	else
		printf("date [-s [\"mm/dd hh:mm:ss year\"]]\n");
	return 0;
}

/*
 *  Change Directoryコマンド
 */
static int cmd_cd(int argc, char **argv)
{
	char *path, spath[PATH_LEN+4], name[4];
	void *dir;
	int  i, len;

	if(argc < 2){
		fwrite(noargment, sizeof(noargment), 1, stderr);
		return -1;
	}
	path = argv[1];
	len = strlen(diskpath);
	if(path[0] == '.'){
		if(path[1] == '.'){
			for(i = len-1 ; i >= 0 ; i--){
				if(diskpath[i] == '/'){
					diskpath[i] = 0;
					break;
				}
				diskpath[i] = 0;
			}
		}
		name[0] = 0;
		name[1] = 0;
		path = name;
	}
	if(mkpath(path, spath) == NULL){
		fwrite(nodevice, sizeof(nodevice), 1, stderr);
		return -1;
	}
	dir = (void *)opendir(spath);
	if(dir == NULL){
		fwrite(nodirectory, sizeof(nodirectory), 1, stderr);
		return -1;
	}
	closedir(dir);
	strcpy(diskpath, &spath[2]);
	return 0;
}

/*
 *  ファイルやディレクトリを表示するコマンド
 */
static int cmd_ls(int argc, char **argv)
{
	StorageDevice_t *psdev;
	struct statfs2  status;
	char   spath[PATH_LEN+4], name[6];
	int    no, count;
	void   *dir;

	if(argc < 2){
		psdev = mkpath(NULL, spath);
	}
	else{
		psdev = mkpath(argv[1], spath);
	}
	if(psdev == 0){
		fwrite(nodevice, sizeof(nodevice), 1, stderr);
		return -1;
	}
	dir = (void *)opendir(spath);
	count = 0;
	if(dir != NULL){
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
		closedir(dir);
		if(statfs(spath, &status) == 0){
			printf("     %d free blocks %d bytes in a block\n", status.f_bfree, status.f_bsize);
		}
	}
	return 0;
}

/*
 *  ファイルの表示
 */
static int cmd_cat(int argc, char **argv)
{
	FILE *fid;
	int  c, i = 0;
	char buf[68];

	if(argc < 2){
		fwrite(noargment, sizeof(noargment), 1, stderr);
		return -1;
	}
	mkpath(argv[1], fname);
	fid = fopen(fname, "rb");
	if(fid == NULL){
		fwrite(nofile, sizeof(nofile), 1, stderr);
		return -1;
	}
	while((c = fgetc(fid)) >= 0){
		buf[i] = c;
		i++;
		if(c == CHAR_LF || i >= 64){
			buf[i] = 0;
			printf("%s", &buf[0]);
			i = 0;
		}
	}
	if(i > 0){
		buf[i+1] = 0;
		printf("%s", &buf[0]);
	}
	fclose(fid);
	return 0;
}

/*
 *  エコーコマンド
 */
static int cmd_echo(int argc, char **argv)
{
	int  c;

	while((c = fgetc(stdin)) >= 0){
		if(c == CHAR_CZ)
			break;
		else if(c > 0){
			if(c == CHAR_CR)
				putchar(CHAR_LF);
			else
				putchar(c);
		}
	}
	return 0;
}

/*
 *  ディレクトリの作成コマンド
 */
static int cmd_mkdir(int argc, char **argv)
{
	char spath[PATH_LEN+4];

	if(argc < 2){
		fwrite(noargment, sizeof(noargment), 1, stderr);
		return -1;
	}
	if(mkpath(argv[1], spath) == NULL){
		fwrite(nodevice, sizeof(nodevice), 1, stderr);
		return -1;
	}
	printf(" mkdir[%s]\n", spath);
	if(mkdir(spath, S_IRWXU|S_IRWXG|S_IRWXO) == 0)
		printf("   Ok\n");
	else
		printf("   Error\n");
	return 0;
}

/*
 *  ディレクトリの削除コマンド
 */
static int cmd_rmdir(int argc, char **argv)
{
	char spath[PATH_LEN+4];

	if(argc < 2){
		fwrite(noargment, sizeof(noargment), 1, stderr);
		return -1;
	}
	if(mkpath(argv[1], spath) == NULL){
		fwrite(nodevice, sizeof(nodevice), 1, stderr);
		return -1;
	}
	printf(" rmdir[%s]\n", spath);
	if(rmdir(spath) == 0)
		printf("   Ok\n");
	else
		printf("   Error\n");
	return 0;
}

/*
 *  ファイルの削除コマンド
 */
static int cmd_rm(int argc, char **argv)
{
	char spath[PATH_LEN+4];

	if(argc < 2){
		fwrite(noargment, sizeof(noargment), 1, stderr);
		return -1;
	}
	if(mkpath(argv[1], spath) == NULL){
		fwrite(nofile, sizeof(nofile), 1, stderr);
		return -1;
	}
	printf(" rm[%s]\n", spath);
	if(remove(spath) == 0)
		printf("   Ok\n");
	else
		printf("   Error\n");
	return 0;
}

/*
 *  ヘルプ表示
 */
static int cmd_help(int argc, char **argv)
{
	printf("date [year] [month] [day] [hour] [min] [sec]\n");
	printf("cd    [path] : change directory\n");
	printf("ls    [path] : list files \n");
	printf("cat   [path] : display text file\n");
	printf("mkdir [path] : make directory\n");
	printf("rmdir [path] : remove directory\n");
	printf("rm    [path] : remove file\n");
	printf("echo         : echo character\n");
	printf("mon          : change task monitor\n");
}

/*
 *  モニタ実行移行コマンド
 */
static int cmd_mon(int argc, char **argv)
{
	monitor_infile(stdin);
	sio_force_ierdy_rcv(MONITOR_PORTID);
	while(monitor_infile(NULL) == stdin && tcp_telnet_connect()){
		dly_tsk(100);
	}
	printf("exit mon command !\n");
	return 0;
}

/*
 *  コマンド引数表示コマンド
 */
static int cmd(int argc, char **argv)
{
	int i;
	printf("argc[%d]\n", argc);
	for(i = 0 ; i < argc ; i++){
		printf("[%d][%s]\n", i, argv[i]);
	}
	return 0;
}

