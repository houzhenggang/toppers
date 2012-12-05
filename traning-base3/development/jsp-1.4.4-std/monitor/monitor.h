/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003-2010 by Ryosuke Takeuchi
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
 *  @(#) $Id: monitor.h,v 1.7 2010/11/27 23:22:20 roi Exp $
 */

#ifndef _MONITOR_H_
#define	_MONITOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 
 *  ��˥�������ץ�ץ����Υإå��ե�����
 */
#include <t_services.h>

/*
 *  ������ͥ���٤�����
 */
#define MONITOR_PRIORITY	3

/*
 *  ��˥��Υ�����������
 */
#if defined(M16C)
#define	MONITOR_STACK_SIZE	512		/* �������Υ����å������� */
#elif defined(H8)
#define	MONITOR_STACK_SIZE	768		/* �������Υ����å������� */
#else
#define	MONITOR_STACK_SIZE	2046	/* �������Υ����å������� */
#endif
#define	MAX_COMMAND_LENGTH	80		/* ��˥��κ��祳�ޥ��Ĺ */
#define	NUM_LOG_DISP		3		/* ����ɽ�������ƥ�� */
#ifndef MONITOR_PORTID
#define MONITOR_PORTID      CONSOLE_PORTID
#endif

/*
 *  �С���������
 */
#define	TMONITOR_PRVER	0x1011		/* �����ͥ�ΥС�������ֹ� */

/*
 *  ����������Ƥ����
 */
#define	KEY_BS			(8)			/* �Хå����ڡ��� */
#define	KEY_DEL			(127)		/* ��� */
#define KEY_NL			(10)		/* ����1 */
#define	KEY_CR			(13)		/* ����2 */
#define	KEY_EXT			(1)			/* ��λ */

/*
 *  �ǡ������������
 */
#define	DATA_BYTE		1			/* �Х��ȥǡ����ʣ��Х��ȡ�*/
#define	DATA_HALF		2			/* �ϡ��եǡ����ʣ��Х��ȡ�*/
#define	DATA_WORD		4			/* ��ɥǡ����ʣ��Х��ȡ�*/

/*
 *  �ΰ�°�������
 */
#define	NONE_AREA		0			/* �ΰ�γ�����ƤΤʤ��ΰ� */
#define	PORT_AREA		1			/* �ϡ��ɥ������Υݡ����ΰ� */
#define	MEMORY_AREA		2			/* �����ΰ衡*/

#define	MREAD_ONLY		1			/* �ɤ߹������� */
#define	MWRITE_ONLY		2			/* �񤭹������� */
#define	MREAD_WRITE		(MREAD_ONLY+MWRITE_ONLY)

#ifndef _MACRO_ONLY

/*
 *  ���ޥ�ɥǥ��ѥå��Ѥι�¤�����
 */
struct COMMAND_TABLE {
	const char *command;			/* ���ޥ��ʸ */
	UW  (*func)(B * command);		/* �¹Դؿ� */
};

struct SUBCOMMAND_TABLE {
	const char *subcommand;			/* ���֥��ޥ��ʸ */
	B const type;					/* �¹ԥ����� */
};

/*
 *  ������������
 */
#define putecho(a)      putchar(a)
#define printecho(a)    printf(a)

/*
 *  �ؿ��Υץ�ȥ��������
 */

extern BOOL need_monitor(void);
extern void	monitor(VP_INT exinf);
extern void *monitor_infile(void* file);
extern BOOL compare_word(const char *s, B *d, INT mode);
extern UB   getMemoryType(UW address, INT mode);
extern INT  MemoryRead(UW address, VP_INT p, INT type);
extern INT  MemoryWrite(UW address, VP_INT p, INT type);
extern UW   MonAlignAddress(UW address);
extern INT  MemoryRead(UW address, VP_INT p, INT type);
extern INT  MemoryWrite(UW address, VP_INT p, INT type);
extern UW   get_exception_pc(VP p_excinf);
extern void display_registers(ID tskid);
extern UW   display_assembler(UW pc);

/*
 *  ���ڡ����򥹥��åפ���
 */
Inline void
skip_space(B *command, INT *point)
{
	while(command[*point] == ' ' || command[*point] == '\t')
		(*point)++;
}

/*
 *  ʸ����򥹥��åפ���
 */
Inline void
skip_word(B *command, INT *point)
{
	while(command[*point] != ' ' && command[*point] != '\t'
             && command[*point] != ',' && command[*point] != 0)
		(*point)++;
	if(command[*point] != 0)
		(*point)++;
	skip_space(command, point);
}

/*
 *  ʸ���󤫤��������Ф�
 *  ����ͤ�FALSE�ʤ��ͤ�̤����Ǥ��뤳�Ȥ򼨤�
 */
Inline BOOL
get_value(B *s, INT *point, UW *v, INT card)
{
	B    c;

	*v = 0;
	if(s[*point] == 0)
		return FALSE;
	else if(s[*point] == ' ' || s[*point] == '\t'
               || s[*point] == ',' || s[*point] == '.'){
		(*point)++;
		skip_space(s, point);
		return FALSE;
	}
	else{
		while(s[*point]){
			c = s[*point];
			(*point)++;
			if(c >= '0' && c <= '9')
				c -= '0';
			else if(c >= 'A' && c <= 'Z')
				c -= 'A' - 10;
			else if(c >= 'a' && c <= 'z')
				c -= 'a' - 10;
			else
				break;
			*v = *v * card + c;
		}
		skip_space(s, point);
		return TRUE;
	}
}

#endif /* _MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* _MONITOR_H_ */

