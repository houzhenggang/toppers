/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010-2011 by GJ Business Division RICOH COMPANY,LTD.
 *                   JAPAN
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
 *  16�ʥ����ɺ���
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
 *  ���ա����֤�����ɽ��
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
 *  Change Directory���ޥ��
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
 *  �ե������ǥ��쥯�ȥ��ɽ�����륳�ޥ��
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
 *  �ե������ɽ��
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
 *  ���������ޥ��
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
 *  �ǥ��쥯�ȥ�κ������ޥ��
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
 *  �ǥ��쥯�ȥ�κ�����ޥ��
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
 *  �ե�����κ�����ޥ��
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
 *  �إ��ɽ��
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
 *  ��˥��¹԰ܹԥ��ޥ��
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
 *  ���ޥ�ɰ���ɽ�����ޥ��
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

