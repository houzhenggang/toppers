/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003      by Advanced Data Controls, Corp
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: sys_config.c,v 1.1 2010/09/05 16:18:56 roi Exp $
 */

/*
 *    �������åȥ����ƥ��¸�⥸�塼���lpc23xx�ѡ�
 */

#include "jsp_kernel.h"
#include <lpc23xx.h>


#define DEFAULT_PCLK    12000000
#define DEFAULT_DLL     0x00000003
#define DEFAULT_FDR     0x00000067

/*interrupt mask*/
UB int_mode_table[MAX_INT_NUM]={
    0,			/* 00: wdt */
    0,
    0,
    0,
    14,			/* 04: timer #0 lowest system timer */
    15,			/* 05: timer #1 */
    7,			/* 06: uart #0 console 1 */
    7,			/* 07: uart #1 console 2 */
    15,
    15,
    15,
    15,
    15,
    12,			/* 13: RTC */
    15,
    15,
    15,
    15,
    15,
    15,
    15,
    8,			/* 21: ETHER */
    15,
    15,
    3,			/* 24: MMC */
    9,			/* 25: GPDMA */
    15,			/* 26: timer #2 */
    15,			/* 27: timer #3 */
    15,			/* 28: uart #2 */
    15,			/* 29: uart #3 */
    15,
    15
};

/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
	unsigned long tmp;
	unsigned int  i;

   /* initialize VIC */
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_INTENCLR), 0xffffffff);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_VECTADDR), 0x00000000);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_INTSELECT), 0x00000000);

	for(i = 0 ; i < MAX_INT_NUM ; i++){
		sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_VECTADDRB+i*4), 0x00000000);
		sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_VECTPRIO+i*4), 0x0000000f);
	}

   /* Configure UART0 for 115200 baud. */
	tmp  = sil_rew_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL0));
	tmp &= ~0x000000f0;
	tmp |= 0x00000050;                   /* Enable RxD0 TxD0 pin         */
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL0), tmp);

	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_LCR), 0x00000083);	/* 8 bits, no Parity, 1 Stop bit*/
#if DEF_BAUDRATE == 115200
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_DLL), DEFAULT_DLL);	/* for 12MHz PCLK Clock         */
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_FDR), DEFAULT_FDR);	/* Fractional Divider           */
#else
	tmp = (DEFAULT_PCLK * 10) / 16 / DEF_BAUDRATE;
	tmp = (tmp+5) / 10;
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_DLL), tmp & 0xff);	/* set divisor */
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_DLM), tmp >> 8);
#endif
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_LCR), 0x00000003);	/* DLAB = 0                     */

   /* Configure UART1 for 115200 baud. */
	tmp  = sil_rew_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL0));
	tmp &= ~0xC0000000;
	tmp |= 0x40000000;                   /* Enable TxD1 pin              */
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL0), tmp);
	tmp  = sil_rew_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL1));
	tmp &= ~0x00000003;
	tmp |= 0x00000001;                   /* Enable RxD1 pin              */

	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL1), tmp);

	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_LCR), 0x00000083);	/* 8 bits, no Parity, 1 Stop bit*/
#if DEF_BAUDRATE == 115200
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_DLL), DEFAULT_DLL);	/* for 12MHz PCLK Clock         */
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_FDR), DEFAULT_FDR);	/* Fractional Divider           */
#else
	tmp = (DEFAULT_PCLK * 10) / 16 / DEF_BAUDRATE;
	tmp = (tmp+5) / 10;
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_DLL), tmp & 0xff);	/* set divisor */
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_DLM), tmp >> 8);
#endif
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_LCR), 0x00000003);	/* DLAB = 0                     */

	/* MMC pin seklect (MCI poweron pin to GPIO) */
	tmp  = sil_rew_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL1));
	tmp &= ~0x00003fc0;
	tmp |= 0x00002A80;
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL1), tmp);
	tmp  = sil_rew_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL4));
	tmp &= ~0x0fc00000;
	tmp |= 0x0A800000;
	sil_wrw_mem((VP)(TADR_PINSEL_BASE+TOFF_PINSEL4), tmp);

#if 0	/* ROI DEBUG */
	sil_wrw_mem((VP)(TADR_FIO_BASE+TOFF_FIO2_CLR), 0x000000aa);		/* led on */
#endif	/* ROI DEBUG */
}


/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit(void)
{
    syslog(LOG_EMERG, "End Kernel.....!");
    while(1);
}

/*
 *  �������åȥ����ƥ��ʸ������
 */

void
sys_putc(char c)
{
    if (c == '\n') {
        lpc2300_uart_putc('\r');
    }
    lpc2300_uart_putc(c);
}

/*
 *  ����ߥϥ�ɥ������
 *
 *  ������ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
void
define_inh(INHNO inhno, FP inthdr)
{
    assert(inhno < MAX_INT_NUM);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_INTENCLR), 1<<inhno);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_VECTADDRB+inhno*4), (UW)inthdr);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_VECTPRIO+inhno*4), (UW)int_mode_table[inhno]);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_SOFTINTCLR), 1<<inhno);
	sil_wrw_mem((VP)(TADR_VIC_BASE+TOFF_VIC_INTENABLE), 1<<inhno);
}

/*
 *  ̤����γ���ߤ����ä����ν���
 */
void
undef_interrupt(){
    syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
    while(1);
}

