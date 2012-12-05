/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003-2008 by Ryosuke Takeuchi
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
 *  @(#) $Id: monitor.c,v 1.12 2011/01/03 17:52:20 roi Exp $
 */

/* 
 *  TOPPERS/JSP用タスクモニタプログラム．
 *
 */

#include <t_services.h>
#include <stdio.h>
#include "jsp_kernel.h"
#include "task.h"
#include "kernel_id.h"
#include "task_expansion.h"
#include "logtask.h"
#include "monitor.h"

/*
 *  モニタ内定義
 */
#define	HEX_BASE			16			/* 16進指定 */
#define	DEC_BASE			10			/* 10進指定 */

#define	MONDISPLAY_BYTE	DATA_BYTE	/* バイト単位メモリ表示 */
#define	MONDISPLAY_HALF	DATA_HALF	/* ハーフ単位メモリ表示 */
#define	MONDISPLAY_WORD	DATA_WORD	/* ワード単位メモリ表示 */
#define	MONDISPLAY_TASK	3			/* タスク状態表示 */
#define	MONDISPLAY_REG	5			/* レジスタの表示 */
#define	MONDISPLAY_ASM	6

#define	MONSET_BYTE		DATA_BYTE	/* バイト単位メモリ設定 */
#define	MONSET_HALF		DATA_HALF	/* ハーフ単位メモリ設定 */
#define	MONSET_WORD		DATA_WORD	/* ワード単位メモリ設定 */
#define	MONSET_COMMAND	3			/* コマンドモード設定 */
#define	MONSET_SERIAL	5			/* シリアル設定 */
#define	MONSET_TASK		6			/* タスク設定 */
#define MONSET_IN       7			/* 入力設定 */

#define	MONTASK_ACTIVE	0			/* 起動要求(act_tsk) */
#define	MONTASK_TERM	1			/* 強制終了(ter_tsk) */
#define	MONTASK_SUSPEND	2			/* 待ち要求(sus_tsk) */
#define	MONTASK_RESUME	3			/* 待ち再開(rsm_tsk) */
#define	MONTASK_RELEASE 4			/* 待ち解除(rel_wai) */
#define	MONTASK_WAKEUP  5			/* タスク起床(wup_tsk) */
#define	MONTASK_PRIORITY 6			/* 優先度変更(chg_pri) */

#define	MONLOG_MODE		0			/* ロギングモード設定 */
#define	MONLOG_TASK		1			/* タスクモニタ設定 */
#define	MONLOG_PORT		2			/* ポートモニタ設定 */

/*
 *  プロトタイプ宣言
 *
 *  このモジュール内で使用している関数
 */
static void prompt(ID tskid);
static INT  dispatch_command(B *command, INT *point);
static UW   display_command(B *command);
static UW   set_command(B *command);
static UW   task_command(B *command);
static UW   log_command(B *command);
static UW   help_command(B *command);
static UH   get_taskstate(STAT tskstat);
static B    monitor_getstring(B *s, INT *point);
static BOOL monitor_break(void);

extern UW   net_command(B *command);
extern UW   volume_command(B *command);
extern UW   pipe_command(B *command);
extern const char	*itron_strerror(ER ercd);

/*
 *  モニタバナー表示
 */
static char const banner[] = "\n"
"JSP TASK Monitor Release %d.%d.%d for " TARGET_NAME
" (" __DATE__ ", " __TIME__ ")\n"
"Copyright (C) 2003-2007 by GJ Business Division RICOH COMPANY,LTD. JAPAN\n";

/*
 *  ヘルプメッセージ
 */
static char const help[] =
"  Display BYTE     [start address] [end address]\n"
"          HELF     [start address] [end address]\n"
"          WORD     [start address] [end address]\n"
"          TASK\n"
"          REGISTER\n"
"  Set     BYTE     [start address]\n"
"          HELF     [start address]\n"
"          WORD     [start address]\n"
"          COMMAND  [mode]  mode=1 or (2)\n"
"          SERIAL   [port id]\n"
"          TASK     [task id]\n"
"          IN       [stdio]\n"
"  Task    ACTIVATE          (act_tsk)\n"
"          TERMINATE         (ter_tsk)\n"
"          SUSPEND           (sus_tsk)\n"
"          RESUME            (rsm_tsk)\n"
"          PRIORITY [pri]    (chg_pri)\n"
#ifdef SUPPORT_VOLUME
"  Volume  FORMAT   [drive]\n"
"          DIR      [path] \n"
"          MKDIR    [path] \n"
"          RMDIR    [path] \n"
"          ERASE    [path] \n"
#endif
#ifdef SUPPORT_PIPE
"  Pipe    HELP     (check pipe command)\n"
#endif
"  Log     MODE     [logmask] [lowmask]\n"
"          TASK     [cycle time(ms)]\n"
"          PORT     [no] [logno] [portaddress]\n"
"  Help\n";

/*
 *  メインコマンドテーブル
 */
static struct COMMAND_TABLE const mon_dispatch[] = {
	{"DISPLAY",		display_command },	/* 表示 */
	{"SET",			set_command     },	/* 設定 */
	{"TASK",		task_command    },	/* itron TASK */
	{"LOG",			log_command     },	/* ロギング */
#ifdef SUPPORT_VOLUME
    {"VOLUME",      volume_command  },	/* ディスクコマンド */
#endif
#ifdef SUPPORT_PIPE
    {"PIPE",        pipe_command    },	/* 拡張コマンド */
#endif
	{"HELP",		help_command    }	/* ヘルプ */
};

/*
 *  表示コマンドテーブル
 */
static struct SUBCOMMAND_TABLE const mon_display[] = {
	{"BYTE",		MONDISPLAY_BYTE },	/* バイト単位メモリ表示 */
	{"HALF",		MONDISPLAY_HALF },	/* ハーフ単位メモリ表示 */
	{"WORD",		MONDISPLAY_WORD },	/* ワード単位メモリ表示 */
	{"TASK",		MONDISPLAY_TASK },	/* タスク状態表示 */
	{"REGISTER",	MONDISPLAY_REG  },	/* タスクレジスター表示 */
	{"ASSEMBLER",	MONDISPLAY_ASM  }	/* アセンブラー表示 */
};

/*
 *  設定コマンドテーブル
 */
static struct SUBCOMMAND_TABLE const mon_set[] = {
	{"BYTE",		MONSET_BYTE     },	/* バイト単位メモリ設定 */
	{"HALF",		MONSET_HALF     },	/* ハーフ単位メモリ設定 */
	{"WORD",		MONSET_WORD     },	/* ワード単位メモリ設定 */
	{"COMMAND",		MONSET_COMMAND  },	/* コマンドモード設定 */
	{"SERIAL",		MONSET_SERIAL   },	/* シリアル設定 */
	{"TASK",		MONSET_TASK     },	/* タスク選択 */
	{"IN",			MONSET_IN       }	/* 入力設定 */
};

/*
 *  タスクコマンドテーブル
 */
static struct SUBCOMMAND_TABLE const mon_task[] = {
	{"ACTIVATE",	MONTASK_ACTIVE  },	/* 起動要求(act_tsk) */
	{"TERMINATE",	MONTASK_TERM    },	/* 強制終了(ter_tsk) */
	{"SUSPEND",		MONTASK_SUSPEND },	/* 待ち要求(sus_tsk) */
	{"RESUME",		MONTASK_RESUME  },	/* 待ち再開(rsm_tsk) */
	{"RELEASE",		MONTASK_RELEASE },	/* 待ち解除(rel_wai) */
	{"WAKEUP",		MONTASK_WAKEUP  },	/* タスク起床(wup_tsk) */
	{"PRIORITY",	MONTASK_PRIORITY}	/* 優先度変更(chg_pri) */
};

/*
 *  ロギングコマンドテーブル
 */
static struct SUBCOMMAND_TABLE const mon_log[] = {
	{"MODE",		MONLOG_MODE     },	/* ロギングモード設定 */
	{"TASK",		MONLOG_TASK     },	/* タスクモニタ設定 */
	{"PORT",		MONLOG_PORT     }	/* ポートモニタ設定 */
};

/*
 *  バックスペース
 */
static const char backspace[] = "\b \b";

/*
 *  タスクモード表示テーブル
 */
#define	TSTATE_LEN		11

static char const task_state[6][TSTATE_LEN] = {
	"RUNNING",						/* 実行中 */
	"RUNNABLE",						/* 実行できる状態 */
	"WAITING",						/* 待ち状態 */
	"SUSPENDED",					/* 強制待ち状態 */
	"WSUSPENDED",					/* 二重待ち状態 */
	"DORMANT"						/* 休止状態 */
};

/*
 *  ロギングモード表示テーブル
 */
static char const log_mode[8][12] = {
	"LOG_EMERG",					/* シャットダウンに値するエラー */
	"LOG_ALERT",
	"LOG_CRIT",
	"LOG_ERROR",					/* システムエラー */
	"LOG_WARNING",					/* 警告メッセージ */
	"LOG_NOTICE",
	"LOG_INFO",
	"LOG_DEBUG"						/* デバッグ用メッセージ */
};

/*
 * モニタで使用されるデータ領域
 */
static ID   current_tskid;			/* モニタが対象とするタスク */
static B    mon_command[MAX_COMMAND_LENGTH+1];
static B    mon_datatype;			/* モニタが指定するデータタイプのデフォルト値 */
static UW   mon_address;			/* モニタが指定するアドレスのデフォルト値 */
static INT  mon_mode;				/* モニタが指定するコマンドモード */
static UINT mon_logmask;			/* モニタが指定する記録／出力すべき重要度 */
static UINT mon_lowmask;			/* モニタが指定する低レベル出力すべき重要度 */
static ID   mon_default_portid;		/* モニタのデフォルトポートID */
static FILE *mon_infile;			/* モニタの入力ファイル */

ID          mon_portid;				/* モニタのデバイスポートID */

/*
 *  モニタタスク
 */
void monitor(VP_INT exinf)
{
	INT  no, point;
	B    c;

	/* モニタで使用するデータの初期化 */

	mon_portid   = mon_default_portid = (ID)exinf;
	mon_datatype = DATA_BYTE;
	mon_logmask  = LOG_NOTICE;
	mon_lowmask  = LOG_EMERG;
	current_tskid = MONTASK;
	mon_infile   = stdin;

	if(mon_portid != CONSOLE_PORTID)
		syscall(serial_opn_por(mon_portid));
#ifdef NEED_MONITOR
	if(!need_monitor())
		ext_tsk();
#endif	/* NEED_MONITOR */
	_setup_stdio(&mon_portid);
#ifdef MONITOR_DELAY
	dly_tsk(MONITOR_DELAY);
#endif	/* MONITOR_DELAY */
#if defined(LOGTASK) && (LOGTASK_PRIORITY <= MONITOR_PRIORITY)
	chg_pri(LOGTASK, MONITOR_PRIORITY+1);
	dly_tsk(50);
	printf("change log task priority %d to %d !\n", LOGTASK_PRIORITY, MONITOR_PRIORITY+1);
#endif
	printf(banner,
		(TMONITOR_PRVER >> 12) & 0x0f,
		(TMONITOR_PRVER >> 4) & 0xff,
		TMONITOR_PRVER & 0x0f);
	vmsk_log(LOG_UPTO(mon_logmask), LOG_UPTO(mon_lowmask));
	syscall(serial_ctl_por(mon_portid, (IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/* モニタのメインのデスパッチ */

	do{
		prompt(current_tskid);
		c = monitor_getstring(mon_command, &point);
		no = dispatch_command(mon_command, &point);
		putecho('\n');
		if(no >= 0)
			mon_dispatch[no].func(&mon_command[point]);
		fflush(NULL);
	}while(c != KEY_EXT);
	printf("exit monitor !!\n");
}

/*
 *  モニタのプロンプトの表示
 *
 *  指定のタスクIDがモニタ以外の場合は
 *  タスクの状態によってプロンプトの表示内容を変更する．
 */
static void
prompt(ID tskid)
{
	T_RTST rtst;

	if(tskid == MONTASK)
		printf("mon");
	else{
		ref_tst(tskid, &rtst);
		printf("%03d(%s)", tskid, (VP_INT)task_state[get_taskstate(rtst.tskstat)]);
	}
	putchar('>');
}

/*
 *  コマンドのデスパッチ
 */
static INT
dispatch_command(B *command, INT *point)
{
	int no, count;

	count = sizeof(mon_dispatch) / sizeof(struct COMMAND_TABLE);
	skip_space(command, point);
	if(command[*point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_dispatch[no].command, &command[*point], mon_mode)){
				skip_word(command, point);
				return no;
			}
		}
	}
	return -1;
}

/*
 *  表示コマンド
 */
static UW
display_command(B *command)
{
	INT    point=0;
	B      cmd=0;
	T_RTST rtst;
	UB     b;
	UH     h;
	UW     w, value1, value2;
	int    no, count;
	char   tstate[TSTATE_LEN];

	count = sizeof(mon_display) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_display[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_display[no].type;
				break;
			}
		}
	}
	switch(cmd){
	default:						/* デフォルト */
		cmd = mon_datatype;
	case MONDISPLAY_BYTE:			/* バイト単位メモリ表示 */
	case MONDISPLAY_HALF:			/* ハーフ単位メモリ表示 */
	case MONDISPLAY_WORD:			/* ワード単位メモリ表示 */
		value2 = 128;
		if(!get_value(command, &point, &value1, HEX_BASE))
			value1 = mon_address;
		value1 = MonAlignAddress(value1);
		if(command[point] == '+'){
			point++;
			if(!get_value(command, &point, &value2, HEX_BASE))
				value2 = 128;
		}
		else{
			if(!get_value(command, &point, &value2, HEX_BASE))
				value2 = value1 + 128;
			value2 -= value1;
		}
		mon_datatype = cmd;
		while((W)value2 > 0){
			printf("%08lx  ", (long)value1);
			for(no = 0 ; no < 16 ; no += mon_datatype){
				if(no == 8)
					putchar(' ');
				switch(mon_datatype){
				case DATA_HALF:
					if(MemoryRead(value1+no, &h, 2) == 0)
						h = -1;
					printf("%04x  ", h);
					break;
				case DATA_WORD:
					if(MemoryRead(value1+no, &w, 4) == 0)
						w = -1;
					printf("%08lx    ", (long)w);
					break;
				default:
					if(MemoryRead(value1+no, &b, 1) == 0)
						b = -1;
					printf("%02x ", b);
					break;
				}
			}
			if(getMemoryType(value1+no, 0) == MEMORY_AREA){
				for(no = 0 ; no < 16 ; no++){
					if(MemoryRead(value1+no, &b, 1)){
						if(b < ' ' || b >= 0xE0)
							b = '.';
						else if(b >= 127 && b < 0xA0)
							b = '.';
					}
					else
						b = '.';
					putchar(b);
				}
			}
			putchar('\n');
			value1 += 16;
			value2 -= 16;
			tslp_tsk(50);
			if(monitor_break())
				value2 = 0;
		}
		mon_address = value1;
		break;
	case MONDISPLAY_TASK:			/* タスク状態表示 */
		printf("cur id  pri state      pc       stack    inistack inisize\n");
		for(no = 0 ; no < tmax_tskid ; no++){
			ref_tst(no+TMIN_TSKID, &rtst);
			if(current_tskid == (no+TMIN_TSKID))
				printf(" * ");
			else
				printf("   ");
			if(MONTASK == (no+TMIN_TSKID))
				printf(" mon");
			else
				printf(" %03d", no+TMIN_TSKID);
			value1 = get_taskstate(rtst.tskstat);
			for(count = 0 ; count < TSTATE_LEN-1 ; count++){
				if((tstate[count] = task_state[value1][count]) == 0)
					tstate[count] = ' ';
			}
			tstate[count] = 0;
			printf(" %3d %s", rtst.tskpri, (VP_INT)tstate);
			if(rtst.tskstat == TTS_RUN)
				printf("         ");
			else
				printf(" %08lx", (unsigned long)rtst.tskpc);
			printf(" %08lx %08lx %5ld\n", (unsigned long)rtst.tsksp, (unsigned long)rtst.inistk, (unsigned long)rtst.inistksz);
		}
		putchar('\n');
		break;
	case MONDISPLAY_REG:			/* レジスタの表示 */
		if(current_tskid != MONTASK)
			display_registers(current_tskid);
		break;
	}
	return 0;
}

/*
 *  設定コマンド
 */
static UW
set_command(B *command)
{
	INT  point=0;
	B    cmd=0;
	UB   b;
	UH   h;
	UW   w, value1, value2;
	int  no, count;
	BOOL cont;

	count = sizeof(mon_set) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_set[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_set[no].type;
				break;
			}
		}
	}
	switch(cmd){
	default:						/* デフォルト */
		cmd = mon_datatype;
	case MONSET_BYTE:				/* バイト単位メモリ設定 */
	case MONSET_HALF:				/* ハーフ単位メモリ設定 */
	case MONSET_WORD:				/* ワード単位メモリ設定 */
		if(!get_value(command, &point, &value1, HEX_BASE))
			value1 = mon_address;
		value1 = MonAlignAddress(value1);
		mon_datatype = cmd;
		do{
			printf("  %08lx", (unsigned long)value1);
			switch(mon_datatype){
			case DATA_HALF:
				if(MemoryRead(value1, &h, 2) == 0)
					h = -1;
				printf(" %04x =", h);
				break;
			case DATA_WORD:
				if(MemoryRead(value1, &w, 4) == 0)
					w = -1;
				printf(" %08lx =", (unsigned long)w);
				break;
			default:
				if(MemoryRead(value1, &b, 1) == 0)
					b = -1;
				printf(" %02x =", b);
				break;
			}
			monitor_getstring(mon_command, &point);
			if(get_value(mon_command, &point, &value2, HEX_BASE)){
				switch(mon_datatype){
				case DATA_HALF:
					h = value2;
					MemoryWrite(value1, &h, 2);
					if(MemoryRead(value1, &h, 2) == 0)
						h = -1;
					printf(" %04x\n", h);
					break;
				case DATA_WORD:
					w = value2;
					MemoryWrite(value1, &w, 4);
					if(MemoryRead(value1, &w, 4) == 0)
						w = -1;
					printf(" %08lx\n", (unsigned long)w);
					break;
				default:
					b = value2;
					MemoryWrite(value1, &b, 1);
					if(MemoryRead(value1, &b, 1) == 0)
						b = -1;
					printf(" %02x\n", b);
					break;
				}
				value1 += mon_datatype;
				cont = TRUE;
			}
			else
				cont = FALSE;
		}while(cont || point == 0);
		putchar('\n');
		mon_address = value1;
		break;
	case MONSET_COMMAND:			/* コマンドモード設定 */
		if(get_value(command, &point, &value1, DEC_BASE)){
			if(value1 == 1 || value1 == 2){
				printf("  set %d command(s) mode !\n", value1);
				mon_mode = value1;
			}
		}
		printf("  set command mode=%d word(s) !\n", mon_mode);
		break;
	case MONSET_SERIAL:				/* シリアル設定 */
		if(get_value(command, &point, &value1, DEC_BASE)){
			if(value1 > 0 && mon_portid != value1){
				if(mon_portid != mon_default_portid && mon_portid != CONSOLE_PORTID)
					syscall(serial_cls_por(mon_portid));
				mon_portid = value1;
				if(mon_portid != mon_default_portid && mon_portid != CONSOLE_PORTID)
					syscall(serial_opn_por(mon_portid));
				syscall(serial_ctl_por(mon_portid, (IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
				printf(banner,
					(TMONITOR_PRVER >> 12) & 0x0f,
					(TMONITOR_PRVER >> 4) & 0xff,
					TMONITOR_PRVER & 0x0f);
			}
		}
		printf("  set serial port id=%d !\n", mon_portid);
		break;
	case MONSET_TASK:				/* タスク選択 */
		if(get_value(command, &point, &value1, DEC_BASE)){
			if(value1 >= TMIN_TSKID && value1 < (TMIN_TSKID+tmax_tskid))
				current_tskid = value1;
			else
				current_tskid = MONTASK;
		}
		else
			current_tskid = MONTASK;
		break;
	case MONSET_IN:					/* 入力設定 */
		value1 = 0;
		get_value(command, &point, &value1, DEC_BASE);
		if(value1 == 1)
			mon_infile = stdout;
		else if(value1 == 2)
			mon_infile = stderr;
		else
			mon_infile = stdin;
		break;
	}
	return 0;
}

/*
 *  タスクコマンド
 */
static UW
task_command(B *command)
{
	INT  point=0;
	B    cmd=-1;
	UW   w;
	int  no, count;
	BOOL result=TRUE;
	ER   ercd = E_OK;

	if(current_tskid == MONTASK){	/* モニタ自体の制御はできない */
		printf(" Can't control the monitor!!\n");
		return 0;
	}
	count = sizeof(mon_task) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_task[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_task[no].type;
				break;
			}
		}
	}
	switch(cmd){
	case MONTASK_ACTIVE:			/* 起動要求(act_tsk) */
		ercd = act_tsk(current_tskid);
		printf("  execute act_tsk(%d)", current_tskid);
		break;
	case MONTASK_TERM:				/* 強制終了(ter_tsk) */
		ercd = ter_tsk(current_tskid);
		printf("  execute ter_tsk(%d)", current_tskid);
		break;
	case MONTASK_SUSPEND:			/* 待ち要求(sus_tsk) */
		ercd = sus_tsk(current_tskid);
		printf("  execute sus_tsk(%d)", current_tskid);
		break;
	case MONTASK_RESUME:			/* 待ち再開(rsm_tsk) */
		ercd = rsm_tsk(current_tskid);
		printf("  execute rsm_tsk(%d)", current_tskid);
		break;

	case MONTASK_RELEASE:			/* 待ち解除(rel_wai) */
		ercd = rel_wai(current_tskid);
		printf("  execute rel_wai(%d)", current_tskid);
		break;

	case MONTASK_WAKEUP:			/* タスク起床(wup_tsk) */
		ercd = wup_tsk(current_tskid);
		printf("  execute wup_tsk(%d)", current_tskid);
		break;

	case MONTASK_PRIORITY:			/* 優先度変更(chg_pri) */
		if(get_value(command, &point, &w, DEC_BASE)){
			ercd = chg_pri(current_tskid, w);
			printf("  execute chg_pri(%d, %d)", current_tskid, w);
		}
		else
			result = FALSE;
		break;
	default:
		result = FALSE;
		break;
	}
	if(result){
		printf(" :: result = %s !\n", (VP_INT)itron_strerror(ercd));
		tslp_tsk(100);				/* スイッチング */
	}
	return 0;
}

/*
 *  ログコマンド
 */
static UW
log_command(B *command)
{
	T_TPRM loglist;
	T_PCHK *p;
	INT    point=0;
	B      cmd=-1;
	UW     value1, value2;
	UW     tcount, ttime;
	UW     type, address;
	int    no, count;

	count = sizeof(mon_log) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_log[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_log[no].type;
				break;
			}
		}
	}
	switch(cmd){
	case MONLOG_MODE:				/* ロギングモード設定 */
		if(!get_value(command, &point, &value1, DEC_BASE))
			value1 = mon_logmask;
		if(!get_value(command, &point, &value2, DEC_BASE))
			value2 = mon_lowmask;
		if(value1 <= LOG_DEBUG)
			mon_logmask = value1;
		if(value2 <= LOG_DEBUG)
			mon_lowmask = value2;
		vmsk_log(LOG_UPTO(mon_logmask), LOG_UPTO(mon_lowmask));
		printf("  set logmask=%s lowmask=%s !\n", (VP_INT)log_mode[mon_logmask], (VP_INT)log_mode[mon_lowmask]);
		break;
	case MONLOG_TASK:				/* タスクモニタ設定 */
		if(!get_value(command, &point, &value1, DEC_BASE))
			value1 = 0;
		if(value1 < 100)
			value1 = 0;
		value2 = 0;
		do{
			count = get_tsklog(&loglist);
			if(value2 == 0){		/* はじめの１回 */
				value2 =loglist.currtime;
				printf("-- time --");
				for(no = 1 ; no <= NUM_LOG_DISP ; no++)
					printf(" --id=%04u --", no);
				printf(" -- others --  -vacancy-\n");
			}
			value2 += value1;
			if(value1 == 0)
				printf("%010lu\n", (unsigned long)loglist.pervtime);
			printf("%010lu", (unsigned long)loglist.currtime);
			tcount = ttime = 0;
			for(no = 1 ; no <= count ; no++){
				if(no <= NUM_LOG_DISP){
					printf(" %04u %05lu.%01u", loglist.tlog[no].runcount, (unsigned long)(loglist.tlog[no].runtimes/10),
							(int)(loglist.tlog[no].runtimes%10));
				}
				else{
					tcount += loglist.tlog[no].runcount;
					ttime += loglist.tlog[no].runtimes;
				}
			}
			printf(" %04u %05lu.%01u", (int)tcount, (unsigned long)(ttime/10), (int)(ttime%10));
			printf("  %07lu.%01u\n", (unsigned long)(loglist.tlog[0].runtimes/10), (int)(loglist.tlog[0].runtimes%10));
			if(value1){
				tslp_tsk(value2 - loglist.currtime);
				if(monitor_break())
					value1 = 0;
			}
		}while(value1);
		break;
	case MONLOG_PORT:				/* ポートモニタ設定 */
		value2 = NUM_PCHK-1;
		if(get_value(command, &point, &value1, DEC_BASE)){
			if((p = get_device_log(value1)) != 0){
				value2 = value1;
				if(!get_value(command, &point, &type, DEC_BASE)){
					if(p->logtype == 0)
						printf("  %02u %1u OFF      =", (int)value1, (int)p->logtype);
					else
						printf("  %02u %1u %s =", (int)value1, (int)p->logtype, (VP_INT)log_mode[p->logtype]);
					command = mon_command;
					monitor_getstring(command, &point);
					if(!get_value(command, &point, &type, DEC_BASE))
						type = 0;
					putchar('\n');
				}
				if(type >= LOG_DEBUG)
					type = 0;
				p->logtype = type;
				if(!get_value(command, &point, &address, HEX_BASE)){
					if(p->logtype == 0)
						printf("  %02d   OFF      %08lx =", (int)value1, (unsigned long)p->portaddress);
					else
						printf("  %02d   %s %08lx =", (int)value1, (VP_INT)log_mode[p->logtype], (unsigned long)p->portaddress);
					command = mon_command;
					monitor_getstring(command, &point);
					address = p->portaddress;
					get_value(command, &point, &address, HEX_BASE);
					putchar('\n');
				}
				p->portaddress = address;
			}
		}
		else
			value1 = 0;
		while(value1 <= value2){
			if((p = get_device_log(value1)) != 0){
				if(p->logtype > 0)
					printf("  %02d   %s port=%08lx\n", (int)value1, (VP_INT)log_mode[p->logtype], (unsigned long)p->portaddress);
				else
					printf("  %02d   OFF      port=%08lx\n", (int)value1, (unsigned long)p->portaddress);
			}
			else
				break;
			value1++;
		}
		break;
	default:
		break;
	}
	return 0;
}

/*
 *  ヘルプコマンド
 */
static UW
help_command(B *command)
{
	printf(help);
	return 0;
}


/*
 *  キャラクタの比較
 */
BOOL
compare_word(const char *s, B *d, INT mode)
{
	B    c;

	if(*d == 0)
		return FALSE;
	while(*s != 0 && *d != 0 && *d != ' ' && *d != ','){
		c = *d++;
		if(c >= 'a' && c <= 'z')
			c -= 0x20;
		if(*s++ != c)
			return FALSE;
		if(mode == 1)
			break;
	}
	return TRUE;
}

/*
 *  タスク状態番号を取り出す
 */
static UH
get_taskstate(STAT tskstat)
{
	UH no;

	if(tskstat == TTS_RUN)
		no = 0;
	else if(tskstat == TTS_RDY)
		no = 1;
	else if(tskstat == TTS_WAI)
		no = 2;
	else if(tskstat == TTS_SUS)
		no = 3;
	else if(tskstat == TTS_DMT)
		no = 5;
	else
		no = 4;
	return no;
}

/*
 *  モニタのコマンド読み込み文
 */
B
monitor_getstring(B *s, INT *point)
{
	char c;

	*point  = 0;
	do{
		c = getc(mon_infile);
		if(c >= ' ' && *point < MAX_COMMAND_LENGTH){
			putecho((int)c);
			s[(*point)++] = c;
		}
		else if((c == KEY_BS || c == KEY_DEL) && *point > 0){
			printecho(backspace);
			(*point)--;
		}
	}while(c != KEY_NL && c != KEY_CR && c != KEY_EXT);
	s[*point] = 0;
	*point = 0;
	return c;
}

/*
 *  モニタコマンドブレークの判定
 */
static BOOL
monitor_break()
{
	T_SERIAL_RPOR k_rpor;

	if(mon_infile != stdin)
		return FALSE;
	serial_ref_por(mon_portid, &k_rpor);
	if(k_rpor.reacnt > 0){
		getc(mon_infile);
		return TRUE;
	}
	else
		return FALSE;
}

/*
 *  モニタ入力ファイルの切り替え
 */
void *
monitor_infile(void *file)
{
	void *ofile = mon_infile;

	if(file != NULL)
		mon_infile = file;
	return ofile;
}

