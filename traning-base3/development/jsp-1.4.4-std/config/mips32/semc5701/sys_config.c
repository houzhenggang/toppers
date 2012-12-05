/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 */

#include "jsp_kernel.h"
#include <hw_serial.h>		/* ���ꥢ�륳��ȥ���ط� */

/*
 *  �������åȥ����ƥ��¸ ������롼����
 */
void sys_initialize() {
}

/*
 *  �������åȥ����ƥ�ν�λ�롼����
 */
void sys_exit(void) {
  /* TODO: describe malta_exit() */
#ifndef GDB_STUB
	while (1);
#else	/*  GDB_STUB  */
	malta_exit();
#endif	/*  GDB_STUB  */

}

/*
 *  GDB STUB / ľ�ܸƽФ� ���󥽡���ƽФ��롼����
 */

/*
 *  gdb stub �ˤ�륳�󥽡������
 */
/* a0($4) = 0xfe00, a1($5) = ���Ϥ���������饯�� ���������ơ�
   SYSCALL �㳰��ȯ�������롣 */

/* ���δؿ���ƤӽФ����ˤϡ����ơ������쥸������EXL�ӥå� = 0 �ǸƤӽФ����ȡ�
   �ʤ������ߡ������ͥ�Ǥϡ��Хʡ�ɽ���������ꥢ����ϻ��˸ƽФ�ԤäƤ��롣*/
Inline void stub_putc(int c) {

	Asm("	move	$5, %0;		\
	     	li	$4, 0xfe00;	\
		syscall;		\
		nop"
		:: "r"(c)
		: "$4","$5" );
}

#if 0
#define malta_putc(c) yamon_putc( c )
void yamon_putc(char c) {
	void (*yamon_print_count)(int, char *, int) = *(void (**)(int, char *, int))(0x9fc00500 + 4);
	yamon_print_count(0, &c, 1);
}
#else /* patch */
#define malta_putc(c) sio_snd_chr_pol( c )
#endif

/*
 *   �����ƥ�ʸ��������λ���
 */
void
sys_putc(char c)
{
	if (c == '\n') {
		malta_putc('\r');
	}
	malta_putc(c);
}

