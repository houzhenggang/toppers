/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: config.h,v 1.01 2011/12/10 17:43:52 roi Exp $
 */

/*
 *  ����ץ�ץ����(1)�Υإå��ե�����
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <s_services.h>
#include <t_services.h>
#include <board_config.h>
#include "lpc23xx_rtc.h"
#include "lpc23xx_gpdma.h"
#include "storagedevice.h"

#include "monitor.h"

/*
 *  �ƥ�������ͥ���٤����
 */

#define MAIN_PRIORITY	  4		/* �ᥤ�󥿥������������ͥ���� */
#define DEFAULT_PRIORITY  7		/* �ᥤ�󥿥�����ͥ���� */
#define SRV_PRIORITY      5

/*
 *  ���Ѥ��� API ������
 */

#define USE_TCP_NON_BLOCKING
#define USE_COPYSAVE_API

/*
 *  TCP ������������ɥХåե�������
 */

#ifdef SUPPORT_INET4

#define TCP_TELNET_SRV_SWBUF_SIZE	(TCP_MSS)
#define TCP_TELNET_SRV_RWBUF_SIZE	(TCP_MSS)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

#define TCP_TELNET_SRV_SWBUF_SIZE	(TCP6_MSS)
#define TCP_TELNET_SRV_RWBUF_SIZE	(TCP6_MSS)

#endif	/* of #ifdef SUPPORT_INET6 */


/*
 *  �������åȰ�¸�������CPU�㳰�ϥ�ɥ�ε�ư��ˡ�ʤɡ�
 */

#ifdef M68K

#define CPUEXC1		5		/* ��������㳰 */
#define RAISE_CPU_EXCEPTION	syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0)

#elif defined(SH3)

#define CPUEXC1		224		/* ���ɥ��顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))

#elif defined(SH1)

#define CPUEXC1		9		/* CPU���ɥ쥹���顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))
#ifdef TOKIWA_SH1
#define	STACK_SIZE	512		/* �������Υ����å������� */
#endif /* TOKIWA_SH1 */

#elif defined(ARMV4)

#define CPUEXC1		4		/* ���ɥ��顼�㳰 */
#define RAISE_CPU_EXCEPTION	(*((volatile int *) 0xFFFFFEC1))

#elif defined(V850)

#elif defined(H8)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */

#elif defined(H8S)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define LOOP_REF	4000L		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(MICROBLAZE)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define STACK_SIZE	2048		/* �������Υ����å������� */

#elif defined(IA32)

#define CPUEXC1		0		/* ��������㳰 */
#define RAISE_CPU_EXCEPTION   syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0)
#define OMIT_VGET_TIM

#elif defined(TMS320C54X)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define STACK_SIZE	320		/* �������Υ����å������� */
#define LOOP_REF	500000L		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(XSTORMY16)

#define CPUEXC1		0		/* ̵��̿���㳰 */
#define RAISE_CPU_EXCEPTION	__asm__( ".hword 0x0006" )
#define OMIT_VGET_TIM			/* vxget_tim()���󥵥ݡ��� */
#define LOOP_REF 	4000L		/* ®�ٷ�¬�ѤΥ롼�ײ�� */
#define STACK_SIZE	256		/* �������Υ����å������� */
#define TASK_PORTID	2		/* SIO�ϥݡ���2���Ѥ��� */

#elif defined(MIPS3) || defined(MIPS64)

#define CPUEXC1     Bp      /* �֥졼���ݥ�����㳰�ʥ����������ȯ���� */
#define RAISE_CPU_EXCEPTION   syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0)

#elif defined(M16C) && defined(OAKS16)

#define CPUEXC1     32      /* CPU�㳰�ϥ�ɥ��ֹ� */
#define RAISE_CPU_EXCEPTION asm("   int #32") /* ���եȥ����������ȯ�� */
#define STACK_SIZE  512     /* �������Υ����å������� */
#define TASK_PORTID 2       /* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */

#elif defined(M16C) && defined(OAKS16_MINI)

#define CPUEXC1     32      /* CPU�㳰�ϥ�ɥ��ֹ� */
#define RAISE_CPU_EXCEPTION asm("   int #32") /* ���եȥ����������ȯ�� */
#define STACK_SIZE  384     /* �������Υ����å������� */
#define TASK_PORTID 2       /* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */

#elif defined(M16C) && defined(M3029) 

#define CPUEXC1     32      /* CPU�㳰�ϥ�ɥ��ֹ� */
#define RAISE_CPU_EXCEPTION asm("   int #32") /* ���եȥ����������ȯ�� */
#define STACK_SIZE  512     /* �������Υ����å������� */
#define TASK_PORTID 1       /* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */

#elif defined(LINUX)

#undef CPUEXC1				/* CPU�㳰�ϥ�ɥ�򥵥ݡ��Ȥ��ʤ� */
#define OMIT_VGET_TIM
#define LOOP_REF	4000000		/* ®�ٷ�¬�ѤΥ롼�ײ�� */

#elif defined(NIOS2)

#define CPUEXC1		0		  /* ̤����̿���㳰 */
#define RAISE_CPU_EXCEPTION	  Asm("div zero, zero, zero");

#elif defined(M32C)

#define CPUEXC1 32 /* CPU�㳰�ϥ�ɥ��ֹ� */
#define RAISE_CPU_EXCEPTION asm(" int #32") /* ���եȥ����������ȯ�� */
#define STACK_SIZE 512 /* �������Υ����å������� */
#define TASK_PORTID 1 /* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */ 

#elif defined(M32R)

#define CPUEXC1 EXC_TRAP00
#define RAISE_CPU_EXCEPTION Asm("trap 0")

#elif defined(TLCS_900) && defined(ZUP_F16_EX)

#define CPUEXC1     3      /* CPU�㳰�ϥ�ɥ��ֹ� */
#define RAISE_CPU_EXCEPTION Asm("   swi 2") /* ���եȥ����������ȯ�� */
#define STACK_SIZE  512     /* �������Υ����å������� */
#define TASK_PORTID 1       /* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */
#define OMIT_VGET_TIM

#endif

/*
 *  �������åȤ˰�¸�����ǽ���Τ�����������
 */

#ifndef TASK_PORTID
#define	TASK_PORTID	1		/* ʸ�����Ϥ��륷�ꥢ��ݡ���ID */
#endif /* TASK_PORTID */

#ifndef STACK_SIZE
#define	STACK_SIZE	4096		/* �������Υ����å������� */
#endif /* STACK_SIZE */

#define TCP_TELNET_SRV_STACK_SIZE	STACK_SIZE	/* TCP TELNET �����Х������Υ����å�������		*/

/*
 *  TELNET APL���Ф������
 */

#define EOF	        (-1)

#define CHAR_LF     0x0a
#define CHAR_CR     0x0d
#define CHAR_CZ     0x1a


/*
 *  �ǡ��������
 */
#ifndef _MACRO_ONLY

/*
 *  TCP TELENT�μ¹ԥ⡼��
 */
enum {
	TCP_TELNET_IN = 0,
	TCP_TELNET_OUT
};

/*
 *  TCP �������Хåե�
 */

extern UB tcp_telnet_srv_swbuf[];
extern UB tcp_telnet_srv_rwbuf[];

#endif /* _MACRO_ONLY */

/*
 *  �ؿ��Υץ�ȥ��������
 */
#ifndef _MACRO_ONLY

extern int   (*application)(INT mode);

extern void	main_task(VP_INT exinf);
extern void	cyclic_handler(VP_INT exinf);
extern void rtc_init(VP_INT exinf);
extern void dma_init(VP_INT exinf);
extern void rtc_isr0(void);
extern void dma_isr0(void);
extern void macaddr_init(VP_INT exinf);
extern void application_init(VP_INT exinf);

extern void tcp_telnet_srv_task(VP_INT exinf);
extern void tcp_telnet_srv_init(void (*func)(INT mode));
extern INT  tcp_telnet_srv_set_file(void *pt);
extern BOOL tcp_telnet_connect(void);
extern ER callback_nblk_tcp_telnet_srv(ID cepid, FN fncd, VP p_parblk);

#endif /* _MACRO_ONLY */
#endif /* _CONFIG_H_ */
