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
 *  @(#) $Id: shell.c,v 1.2 2012/07/08 13:20:29 roi Exp $
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include "config.h"
#include "fcntl.h"
#include "shell.h"

#define	TSHELL_PRVER	0x1000		/* カーネルのバージョン番号 */

#define NO_REDIRECTION  0
#define REDIRECT_OUT    1


/*
 *  モニタバナー表示
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
 *  次のキャラクタの判定
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
 *  アプリケーションの初期化
 */
void application_init(VP_INT exinf)
{
	first_call = TRUE;
	diskpath[0] = 0;
	comlen     = 0;
	application = dispatcher;
}


/*
 *  パスを生成する
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
 *  ファイル構造体をコピーする
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
 *  プロンプト表示
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
	 *  文字列のチェック
	 */
	if(len == 0 || buf[0] <= ' '){
		if(mode == 0)	/* normal dispatch */
			prompt();
		return 1;
	}
	/*
	 *  引数の設定
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
	 *  リダイレクションの設定
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
	 *  コマンドの実行
	 */
	for(cno = 0 ; command_table[cno].cmdstr != 0 ; cno++){
		if(strcmp(command_table[cno].cmdstr, argb[0]) == 0){
			result = command_table[cno].func(argc, argb);
			break;
		}
	}
	/*
	 *  リダイレクション後処理
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


