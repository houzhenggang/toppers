/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2009 by Ryosuke Takeuchi
 *                     GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: stddev.c,v 1.4 2010/11/28 16:25:29 roi Exp $
 */

/* 
 *  TOPPERS/JSP用タスクモニタCPU依存プログラム．
 *
 */

#include <t_services.h>
#include <s_services.h> 
#include <stdio.h>
#include <string.h>


#ifdef _SMALL_STDIO_
/******************************************************************************
 * 縮小版標準入出力の設定
 ******************************************************************************/

FILE _iob[4];
static ID   dummyid = CONSOLE_PORTID;
static ID * stdport = &dummyid;

/*
 *  モニタの１文字入力文
 */
static int
local_getc(FILE *st)
{
	char buf[2];

	serial_rea_dat(*stdport, buf, 1);
	return (int)buf[0];
}

/*
 *  モニタの文字列入力文
 */
static int
local_gets(FILE *st, unsigned int len, char *s)
{
	return serial_rea_dat(*stdport, s, len);
}

/*
 *  モニタの１文字出力文
 */
static void
local_putc(FILE *st, int c)
{
	char buf[2];

	buf[0] = c;
	serial_wri_dat(*stdport, buf, 1);
}

/*
 *  モニタの文字列出力文
 */
static int
local_puts(FILE *st, unsigned int len, char *s)
{
	return serial_wri_dat(*stdport, s, len);
}

/*
 *  モニタのデータフラッシュ文
 */
static int
local_flush(FILE *st)
{
	return 0;
}

/*
 *  標準出力関数
 */
int fputc(int c, FILE *st)
{
	if(st == NULL)
		st = stdout;
	if(c == '\n')
		st->_func_out(st, '\r');
	st->_func_out(st, c);
	return 1;
}

/*
 *  標準文字列出力関数
 */
int fputs(const char *s, FILE *st)
{
	int status;

	if(st == NULL)
		st = stdout;
	status = st->_func_outs(st, strlen(s), (char *)s);
	st->_func_out(st, '\r');
	st->_func_out(st, '\n');
	return status;
}

/*
 *  標準入力関数
 */
int fgetc(FILE *st)
{
	if(st == NULL)
		st = stdin;
	return st->_func_in(st);
}

/*
 *  標準文字列入力関数
 */
int fgets(char *buf, int size, FILE *st)
{
	if(st == NULL)
		st = stdin;
	return st->_func_ins(st, size, buf);
}

/*
 *  標準データ読み出し関数
 */
size_t fread(void *buf, size_t size, size_t count, FILE *st)
{
	if(st == NULL)
		st = stdin;
	return st->_func_ins(st, size*count, buf);
}

/*
 *  標準データ書き込み関数
 */
size_t fwrite(const void *buf, size_t size, size_t count, FILE *st)
{
	if(st == NULL)
		st = stdout;
	return st->_func_outs(st, size*count, (char *)buf);
}

/*
 *  標準文字列出力関数
 */
int puts(const char *s)
{
	int status;

	status = stdout->_func_outs(stdout, strlen(s), (char *)s);
	stdout->_func_out(stdout, '\r');
	stdout->_func_out(stdout, '\n');
	return status;
}

/*
 *  一文字出力プログラム
 */
int putchar(c)
{
	return fputc(c,stdout);
}

/*
 *  バッファのフラッシュ関数
 */
int fflush(FILE *st)
{
	if(st == NULL)
		st = stdout;
	return st->_func_flush(st);
}

/*
 *  標準入出力用ストリーム取り出し関数
 */
FILE *_get_stdio(int no)
{
	return &_iob[no];
}

/*
 *  標準入出力ストリーム初期化関数
 */
int _set_stdio(int no)
{
	if(no >= 0 && no < 3){
		_iob[no]._file       = -1;
		_iob[no]._func_in    = local_getc;
		_iob[no]._func_ins   = local_gets;
		_iob[no]._func_out   = local_putc;
		_iob[no]._func_outs  = local_puts;
		_iob[no]._func_flush = local_flush;
		_iob[no]._dev        = 0;
		return no;
	}
	else
		return -1;
}

/*
 *  標準入出力初期化関数
 */
void _setup_stdio(signed int *pport)
{
	int i;

	stdport = pport;
	for(i = 0 ; i < 3 ; i++){
		_set_stdio(i);
	}
}

#endif /* _SMALL_STDIO_ */

