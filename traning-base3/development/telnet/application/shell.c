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
 *  @(#) $Id: shell.c,v 1.2 2012/07/08 13:20:29 roi Exp $
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include "config.h"
#include "fcntl.h"
#include "shell.h"

#define	TSHELL_PRVER	0x1000		/* �����ͥ�ΥС�������ֹ� */

#define NO_REDIRECTION  0
#define REDIRECT_OUT    1


/*
 *  ��˥��Хʡ�ɽ��
 */
static char const banner[] = 
"Telnet Shell %d.%d.%d for "
" (" __DATE__ ", " __TIME__ ")\n";
static const char noredirect[] = "\nno redirection arguments !\n\015";
static const char errredirect[] = "\nerror redirection file !\n\015";

ID    diskid = 0;
int   redirect_mode = NO_REDIRECTION;
char  diskpath[PATH_LEN];

static BOOL  first_call;
static BOOL  comin;
static INT   comlen;
static UB    combuf[COM_LEN];

INT dispatcher(INT mode);

/*
 *  ���Υ���饯����Ƚ��
 */
static BOOL test_next(char c)
{
	if(comin){
		if(c == '"')
			comin = FALSE;
		return FALSE;
	}
	else if(c == ' ' || c == '\t')
		return TRUE;
	else
		return FALSE;
}

/*
 *  ���ץꥱ�������ν����
 */
void application_init(VP_INT exinf)
{
	first_call = TRUE;
	diskpath[0] = 0;
	comlen     = 0;
	application = dispatcher;
}


/*
 *  �ѥ�����������
 */
StorageDevice_t *mkpath(char *path, char *tpath)
{
	char *spath = tpath;
	char dpath[4];
	int  devno, len;

	if(tpath == NULL)
		return NULL;
	if(path == NULL){
		dpath[0] = 0;
		dpath[1] = 0;
		path = dpath;
	}
	if(path[1] == ':'){
		strcpy(tpath, path);
	}
	else{
		tpath[0] = diskid+'0';
		tpath[1] = ':';
		if(path[0] == '/'){
			strcpy(&tpath[2], path);
		}
		else{
			strcpy(&tpath[2], diskpath);
			len = strlen(diskpath);
			if(path[0] != 0){
				tpath[len+2] = '/';
				strcpy(&tpath[len+3], path);
			}
		}
	}
	devno = SDMGetDeviceNo((const char **)&path);
	return SDMGetStorageDevice(devno);
}

/*
 *  �ե����빽¤�Τ򥳥ԡ�����
 */
void copy_file_func(FILE *sst, FILE *dst)
{
	dst->_file       = sst->_file;
	dst->_func_in    = sst->_func_in;
	dst->_func_ins   = sst->_func_ins;
	dst->_func_out   = sst->_func_out;
	dst->_func_outs  = sst->_func_outs;
	dst->_func_flush = sst->_func_flush;
	dst->_dev        = sst->_dev;
}

/*
 *  �ץ��ץ�ɽ��
 */
void prompt(void)
{
	printf("%d:", diskid);
	if(diskpath[0] != 0)
		printf("%s:", diskpath);
}

/*
 *  TELNET SHELL
 */
INT tsh(char *buf, INT len, INT mode)
{
	INT  argc, no;
	char *argb[16];
	FILE *fd;
	INT  cno = 0;
	INT  result = 0;
	FILE  save_file;
	char  rediectpath[256];

	/*
	 *  ʸ����Υ����å�
	 */
	if(len == 0 || buf[0] <= ' '){
		if(mode == 0)	/* normal dispatch */
			prompt();
		return 1;
	}
	/*
	 *  ����������
	 */
	for(no = argc = 0 ; argc < 16 && no < len ; no++){
		if(test_next(buf[no])){
			buf[no] = 0;
			cno = 0;
		}
		else if(no < len){
			if(cno == 0){
				argb[argc++] = &buf[no];
				if(buf[no] == '"')
					comin = TRUE;
			}
			cno++;
		}
	}
	buf[no] = 0;
	/*
	 *  ������쥯����������
	 */
	for(no = 1 ; no < argc ; no++){
		if(*(argb[no]) == '>'){
			if(argc <= (no+1)){
				fwrite(noredirect, sizeof(noredirect), 1, stderr);
				goto tsh_exit;
			}
			mkpath(argb[no+1], rediectpath);
			fd = fopen(rediectpath, "wb");
			if(fd == NULL){
				fwrite(errredirect, sizeof(errredirect), 1, stderr);
				goto tsh_exit;
			}
			if(*(argb[no]+1) == '>'){
				fseek(fd, 0, SEEK_END);
			}
			copy_file_func(stdout, &save_file);
			copy_file_func(fd, stdout);
			argc = no;
			redirect_mode = REDIRECT_OUT;
			break;
		}
	}
	/*
	 *  ���ޥ�ɤμ¹�
	 */
	for(cno = 0 ; command_table[cno].cmdstr != 0 ; cno++){
		if(strcmp(command_table[cno].cmdstr, argb[0]) == 0){
			result = command_table[cno].func(argc, argb);
			break;
		}
	}
	/*
	 *  ������쥯���������
	 */
	if(redirect_mode == REDIRECT_OUT){
		fclose(fd);
		copy_file_func(&save_file, stdout);
	}
tsh_exit:
	redirect_mode = NO_REDIRECTION;
	prompt();
	return result;
}

/*
 *  COMMAND DISPATHER
 */
INT dispatcher(INT mode)
{
	INT ch = 0;
	INT len, result;

	if(first_call){
		printf(banner,
		(TSHELL_PRVER >> 12) & 0x0f,
		(TSHELL_PRVER >> 4) & 0xff,
		TSHELL_PRVER & 0x0f);
		prompt();
		first_call = FALSE;
	}
	ch = getchar();
	if(ch == '\b' || ch == 127){
		if(comlen > 0){
			comlen--;
			printf("\b \b");
		}
	}
	else if(ch == CHAR_CR){
		putchar(CHAR_LF);
		combuf[comlen] = 0;
		len = comlen;
		comlen = 0;
		result = tsh(combuf, len, mode);
	}
	else if(ch > 0 && ch != CHAR_LF){
		combuf[comlen++] = ch;
		putchar(ch);
	}
	return ch;
}


