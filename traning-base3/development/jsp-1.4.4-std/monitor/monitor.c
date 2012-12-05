/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003-2008 by Ryosuke Takeuchi
 *                     GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
 *  ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ�������֥륪��
 *      �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
 *      ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
 *      �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
 *      �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: monitor.c,v 1.12 2011/01/03 17:52:20 roi Exp $
 */

/* 
 *  TOPPERS/JSP�ѥ�������˥��ץ���ࡥ
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
 *  ��˥������
 */
#define	HEX_BASE			16			/* 16�ʻ��� */
#define	DEC_BASE			10			/* 10�ʻ��� */

#define	MONDISPLAY_BYTE	DATA_BYTE	/* �Х���ñ�̥���ɽ�� */
#define	MONDISPLAY_HALF	DATA_HALF	/* �ϡ���ñ�̥���ɽ�� */
#define	MONDISPLAY_WORD	DATA_WORD	/* ���ñ�̥���ɽ�� */
#define	MONDISPLAY_TASK	3			/* ����������ɽ�� */
#define	MONDISPLAY_REG	5			/* �쥸������ɽ�� */
#define	MONDISPLAY_ASM	6

#define	MONSET_BYTE		DATA_BYTE	/* �Х���ñ�̥������� */
#define	MONSET_HALF		DATA_HALF	/* �ϡ���ñ�̥������� */
#define	MONSET_WORD		DATA_WORD	/* ���ñ�̥������� */
#define	MONSET_COMMAND	3			/* ���ޥ�ɥ⡼������ */
#define	MONSET_SERIAL	5			/* ���ꥢ������ */
#define	MONSET_TASK		6			/* ���������� */
#define MONSET_IN       7			/* �������� */

#define	MONTASK_ACTIVE	0			/* ��ư�׵�(act_tsk) */
#define	MONTASK_TERM	1			/* ������λ(ter_tsk) */
#define	MONTASK_SUSPEND	2			/* �Ԥ��׵�(sus_tsk) */
#define	MONTASK_RESUME	3			/* �Ԥ��Ƴ�(rsm_tsk) */
#define	MONTASK_RELEASE 4			/* �Ԥ����(rel_wai) */
#define	MONTASK_WAKEUP  5			/* ����������(wup_tsk) */
#define	MONTASK_PRIORITY 6			/* ͥ�����ѹ�(chg_pri) */

#define	MONLOG_MODE		0			/* ���󥰥⡼������ */
#define	MONLOG_TASK		1			/* ��������˥����� */
#define	MONLOG_PORT		2			/* �ݡ��ȥ�˥����� */

/*
 *  �ץ�ȥ��������
 *
 *  ���Υ⥸�塼����ǻ��Ѥ��Ƥ���ؿ�
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
 *  ��˥��Хʡ�ɽ��
 */
static char const banner[] = "\n"
"JSP TASK Monitor Release %d.%d.%d for " TARGET_NAME
" (" __DATE__ ", " __TIME__ ")\n"
"Copyright (C) 2003-2007 by GJ Business Division RICOH COMPANY,LTD. JAPAN\n";

/*
 *  �إ�ץ�å�����
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
 *  �ᥤ�󥳥ޥ�ɥơ��֥�
 */
static struct COMMAND_TABLE const mon_dispatch[] = {
	{"DISPLAY",		display_command },	/* ɽ�� */
	{"SET",			set_command     },	/* ���� */
	{"TASK",		task_command    },	/* itron TASK */
	{"LOG",			log_command     },	/* ���� */
#ifdef SUPPORT_VOLUME
    {"VOLUME",      volume_command  },	/* �ǥ��������ޥ�� */
#endif
#ifdef SUPPORT_PIPE
    {"PIPE",        pipe_command    },	/* ��ĥ���ޥ�� */
#endif
	{"HELP",		help_command    }	/* �إ�� */
};

/*
 *  ɽ�����ޥ�ɥơ��֥�
 */
static struct SUBCOMMAND_TABLE const mon_display[] = {
	{"BYTE",		MONDISPLAY_BYTE },	/* �Х���ñ�̥���ɽ�� */
	{"HALF",		MONDISPLAY_HALF },	/* �ϡ���ñ�̥���ɽ�� */
	{"WORD",		MONDISPLAY_WORD },	/* ���ñ�̥���ɽ�� */
	{"TASK",		MONDISPLAY_TASK },	/* ����������ɽ�� */
	{"REGISTER",	MONDISPLAY_REG  },	/* �������쥸������ɽ�� */
	{"ASSEMBLER",	MONDISPLAY_ASM  }	/* ������֥顼ɽ�� */
};

/*
 *  ���ꥳ�ޥ�ɥơ��֥�
 */
static struct SUBCOMMAND_TABLE const mon_set[] = {
	{"BYTE",		MONSET_BYTE     },	/* �Х���ñ�̥������� */
	{"HALF",		MONSET_HALF     },	/* �ϡ���ñ�̥������� */
	{"WORD",		MONSET_WORD     },	/* ���ñ�̥������� */
	{"COMMAND",		MONSET_COMMAND  },	/* ���ޥ�ɥ⡼������ */
	{"SERIAL",		MONSET_SERIAL   },	/* ���ꥢ������ */
	{"TASK",		MONSET_TASK     },	/* ���������� */
	{"IN",			MONSET_IN       }	/* �������� */
};

/*
 *  ���������ޥ�ɥơ��֥�
 */
static struct SUBCOMMAND_TABLE const mon_task[] = {
	{"ACTIVATE",	MONTASK_ACTIVE  },	/* ��ư�׵�(act_tsk) */
	{"TERMINATE",	MONTASK_TERM    },	/* ������λ(ter_tsk) */
	{"SUSPEND",		MONTASK_SUSPEND },	/* �Ԥ��׵�(sus_tsk) */
	{"RESUME",		MONTASK_RESUME  },	/* �Ԥ��Ƴ�(rsm_tsk) */
	{"RELEASE",		MONTASK_RELEASE },	/* �Ԥ����(rel_wai) */
	{"WAKEUP",		MONTASK_WAKEUP  },	/* ����������(wup_tsk) */
	{"PRIORITY",	MONTASK_PRIORITY}	/* ͥ�����ѹ�(chg_pri) */
};

/*
 *  ���󥰥��ޥ�ɥơ��֥�
 */
static struct SUBCOMMAND_TABLE const mon_log[] = {
	{"MODE",		MONLOG_MODE     },	/* ���󥰥⡼������ */
	{"TASK",		MONLOG_TASK     },	/* ��������˥����� */
	{"PORT",		MONLOG_PORT     }	/* �ݡ��ȥ�˥����� */
};

/*
 *  �Хå����ڡ���
 */
static const char backspace[] = "\b \b";

/*
 *  �������⡼��ɽ���ơ��֥�
 */
#define	TSTATE_LEN		11

static char const task_state[6][TSTATE_LEN] = {
	"RUNNING",						/* �¹��� */
	"RUNNABLE",						/* �¹ԤǤ������ */
	"WAITING",						/* �Ԥ����� */
	"SUSPENDED",					/* �����Ԥ����� */
	"WSUSPENDED",					/* ����Ԥ����� */
	"DORMANT"						/* �ٻ߾��� */
};

/*
 *  ���󥰥⡼��ɽ���ơ��֥�
 */
static char const log_mode[8][12] = {
	"LOG_EMERG",					/* ����åȥ�������ͤ��륨�顼 */
	"LOG_ALERT",
	"LOG_CRIT",
	"LOG_ERROR",					/* �����ƥ२�顼 */
	"LOG_WARNING",					/* �ٹ��å����� */
	"LOG_NOTICE",
	"LOG_INFO",
	"LOG_DEBUG"						/* �ǥХå��ѥ�å����� */
};

/*
 * ��˥��ǻ��Ѥ����ǡ����ΰ�
 */
static ID   current_tskid;			/* ��˥����оݤȤ��륿���� */
static B    mon_command[MAX_COMMAND_LENGTH+1];
static B    mon_datatype;			/* ��˥������ꤹ��ǡ��������פΥǥե������ */
static UW   mon_address;			/* ��˥������ꤹ�륢�ɥ쥹�Υǥե������ */
static INT  mon_mode;				/* ��˥������ꤹ�륳�ޥ�ɥ⡼�� */
static UINT mon_logmask;			/* ��˥������ꤹ�뵭Ͽ�����Ϥ��٤������� */
static UINT mon_lowmask;			/* ��˥������ꤹ�����٥���Ϥ��٤������� */
static ID   mon_default_portid;		/* ��˥��Υǥե���ȥݡ���ID */
static FILE *mon_infile;			/* ��˥������ϥե����� */

ID          mon_portid;				/* ��˥��ΥǥХ����ݡ���ID */

/*
 *  ��˥�������
 */
void monitor(VP_INT exinf)
{
	INT  no, point;
	B    c;

	/* ��˥��ǻ��Ѥ���ǡ����ν���� */

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

	/* ��˥��Υᥤ��Υǥ��ѥå� */

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
 *  ��˥��Υץ��ץȤ�ɽ��
 *
 *  ����Υ�����ID����˥��ʳ��ξ���
 *  �������ξ��֤ˤ�äƥץ��ץȤ�ɽ�����Ƥ��ѹ����롥
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
 *  ���ޥ�ɤΥǥ��ѥå�
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
 *  ɽ�����ޥ��
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
	default:						/* �ǥե���� */
		cmd = mon_datatype;
	case MONDISPLAY_BYTE:			/* �Х���ñ�̥���ɽ�� */
	case MONDISPLAY_HALF:			/* �ϡ���ñ�̥���ɽ�� */
	case MONDISPLAY_WORD:			/* ���ñ�̥���ɽ�� */
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
	case MONDISPLAY_TASK:			/* ����������ɽ�� */
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
	case MONDISPLAY_REG:			/* �쥸������ɽ�� */
		if(current_tskid != MONTASK)
			display_registers(current_tskid);
		break;
	}
	return 0;
}

/*
 *  ���ꥳ�ޥ��
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
	default:						/* �ǥե���� */
		cmd = mon_datatype;
	case MONSET_BYTE:				/* �Х���ñ�̥������� */
	case MONSET_HALF:				/* �ϡ���ñ�̥������� */
	case MONSET_WORD:				/* ���ñ�̥������� */
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
	case MONSET_COMMAND:			/* ���ޥ�ɥ⡼������ */
		if(get_value(command, &point, &value1, DEC_BASE)){
			if(value1 == 1 || value1 == 2){
				printf("  set %d command(s) mode !\n", value1);
				mon_mode = value1;
			}
		}
		printf("  set command mode=%d word(s) !\n", mon_mode);
		break;
	case MONSET_SERIAL:				/* ���ꥢ������ */
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
	case MONSET_TASK:				/* ���������� */
		if(get_value(command, &point, &value1, DEC_BASE)){
			if(value1 >= TMIN_TSKID && value1 < (TMIN_TSKID+tmax_tskid))
				current_tskid = value1;
			else
				current_tskid = MONTASK;
		}
		else
			current_tskid = MONTASK;
		break;
	case MONSET_IN:					/* �������� */
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
 *  ���������ޥ��
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

	if(current_tskid == MONTASK){	/* ��˥����Τ�����ϤǤ��ʤ� */
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
	case MONTASK_ACTIVE:			/* ��ư�׵�(act_tsk) */
		ercd = act_tsk(current_tskid);
		printf("  execute act_tsk(%d)", current_tskid);
		break;
	case MONTASK_TERM:				/* ������λ(ter_tsk) */
		ercd = ter_tsk(current_tskid);
		printf("  execute ter_tsk(%d)", current_tskid);
		break;
	case MONTASK_SUSPEND:			/* �Ԥ��׵�(sus_tsk) */
		ercd = sus_tsk(current_tskid);
		printf("  execute sus_tsk(%d)", current_tskid);
		break;
	case MONTASK_RESUME:			/* �Ԥ��Ƴ�(rsm_tsk) */
		ercd = rsm_tsk(current_tskid);
		printf("  execute rsm_tsk(%d)", current_tskid);
		break;

	case MONTASK_RELEASE:			/* �Ԥ����(rel_wai) */
		ercd = rel_wai(current_tskid);
		printf("  execute rel_wai(%d)", current_tskid);
		break;

	case MONTASK_WAKEUP:			/* ����������(wup_tsk) */
		ercd = wup_tsk(current_tskid);
		printf("  execute wup_tsk(%d)", current_tskid);
		break;

	case MONTASK_PRIORITY:			/* ͥ�����ѹ�(chg_pri) */
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
		tslp_tsk(100);				/* �����å��� */
	}
	return 0;
}

/*
 *  �����ޥ��
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
	case MONLOG_MODE:				/* ���󥰥⡼������ */
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
	case MONLOG_TASK:				/* ��������˥����� */
		if(!get_value(command, &point, &value1, DEC_BASE))
			value1 = 0;
		if(value1 < 100)
			value1 = 0;
		value2 = 0;
		do{
			count = get_tsklog(&loglist);
			if(value2 == 0){		/* �Ϥ���Σ��� */
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
	case MONLOG_PORT:				/* �ݡ��ȥ�˥����� */
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
 *  �إ�ץ��ޥ��
 */
static UW
help_command(B *command)
{
	printf(help);
	return 0;
}


/*
 *  ����饯�������
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
 *  �����������ֹ����Ф�
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
 *  ��˥��Υ��ޥ���ɤ߹���ʸ
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
 *  ��˥����ޥ�ɥ֥졼����Ƚ��
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
 *  ��˥����ϥե�������ڤ��ؤ�
 */
void *
monitor_infile(void *file)
{
	void *ofile = mon_infile;

	if(file != NULL)
		mon_infile = file;
	return ofile;
}

