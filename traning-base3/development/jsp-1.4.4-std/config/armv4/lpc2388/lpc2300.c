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
 *  @(#) $Id: lpc2300.c,v 1.1 2010/07/25 08:39:22 roi Exp $
 *  
 */

/*
 * lpc2300 ������ǽ�ѥɥ饤��
 */
#include <s_services.h>
#include <lpc23xx.h>

#define US_TXEMPTY	0x20
#define US_RXRDY    0x01

#define US_ETXI     0x02
#define US_ERXI     0x01

#define DEFAULT_PCLK    12000000
#define DEFAULT_DLL 0x00000003
#define DEFAULT_FDR 0x00000067

/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
    {(VP)(TADR_UART0_BASE), INTNO_UART0
    },
    {(VP)(TADR_UART1_BASE), INTNO_UART1
    }
};


/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB  siopcb_table[TNUM_SIOP];


/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((UINT)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))


/*
 * ʸ�������������?
 */ 
Inline BOOL
uart_getready(SIOPCB *siopcb)
{
    return(((sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_LSR)) & US_RXRDY)!=0));
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
uart_putready(SIOPCB *siopcb)
{
	return((sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_LSR)) & US_TXEMPTY) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline UB
uart_getchar(SIOPCB *siopcb)
{
    return((UB)sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_RBR)));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
uart_putchar(SIOPCB *siopcb, UB c)
{
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_THR), c);
}

/*
 *  ��������ߵ���
 */
Inline void
uart_enable_send(SIOPCB *siopcb)
{
	unsigned long tmp = sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER));
	tmp |= US_ETXI;
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), tmp);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_send(SIOPCB *siopcb)
{
	unsigned long tmp = sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER));
	tmp &= ~US_ETXI;
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), tmp);
}


/*
 *  ��������ߵ���
 */
Inline void
uart_enable_rcv(SIOPCB *siopcb)
{
	unsigned long tmp = sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER));
	tmp |= US_ERXI;
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), tmp);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_rcv(SIOPCB *siopcb)
{
	unsigned long tmp = sil_rew_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER));
	tmp &= ~US_ERXI;
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), tmp);
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 *  1�ݡ��Ȥ����ʤ����ᡤ���ޤ��̣�Ϥʤ�
 */
void
uart_initialize()
{
    SIOPCB  *siopcb;
    UINT    i;

    /*
     *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
     */
    for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
        siopcb->siopinib = &(siopinib_table[i]);
        siopcb->openflag = FALSE;
        siopcb->sendflag = FALSE;
    }
}

/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫
 */
BOOL
uart_openflag(void)
{
    return(siopcb_table[0].openflag);
}

/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
uart_opn_por(ID siopid, VP_INT exinf)
{
/*    unsigned int baud = ((MCK * 10) / (BAUDRATE * 16));*/

    SIOPCB      *siopcb;
    const SIOPINIB  *siopinib;
#if DEF_BARDRATE != 115200
	UW    tmp;
#endif

    siopcb = get_siopcb(siopid);
    siopinib = siopcb->siopinib;

    /*
     * Wait ������롥
     */
    sil_dly_nse(5000);

	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_LCR), 0x00000083);	/* 8 bits, no Parity, 1 Stop bit*/
#if DEF_BARDRATE == 115200
	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_DLL), DEFAULT_DLL);	/* for 12MHz PCLK Clock         */
	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_FDR), DEFAULT_FDR);	/* Fractional Divider           */
#else
	tmp = (DEFAULT_PCLK * 10) / 16 / DEF_BAUDRATE;
	tmp = (tmp + 5) / 10;
	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_DLL), tmp & 0xff);	/* set divisor */
	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_DLM), tmp >> 8);
#endif
	sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_LCR), 0x00000003);	/* DLAB = 0                     */
												/* Enable RDA and THRE interrupts      */
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), US_ETXI|US_ERXI);

    siopcb->exinf = exinf;
    siopcb->getready = siopcb->putready = FALSE;
    siopcb->openflag = TRUE;

    return(siopcb);
}



/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
uart_cls_por(SIOPCB *siopcb)
{
    const SIOPINIB  *siopinib;

    siopinib = siopcb->siopinib;
    sil_wrw_mem((VP)(siopcb->siopinib->uart_base+TOFF_UART_IER), 0x00000000);
    siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
uart_snd_chr(SIOPCB *siopcb, char c)
{
    if (uart_putready(siopcb)){
        uart_putchar(siopcb, c);
        return(TRUE);
    }
    return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
uart_rcv_chr(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        return((INT)(UB) uart_getchar(siopcb));
    }
    return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            uart_enable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            uart_enable_rcv(siopcb);
            break;
    }
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
    case SIO_ERDY_SND:
        uart_disable_send(siopcb);
        break;
    case SIO_ERDY_RCV:
        uart_disable_rcv(siopcb);
        break;
    }
}



/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
uart_isr_siop(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        uart_ierdy_rcv(siopcb->exinf);
    }
    if (uart_putready(siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        uart_ierdy_snd(siopcb->exinf);
    }
}

#if CONSOLE_PORTID == 1
void
lpc2300_uart_putc(char c)
{
	while((sil_rew_mem((VP)(TADR_UART0_BASE+TOFF_UART_LSR)) & US_TXEMPTY) == 0);
	sil_wrw_mem((VP)(TADR_UART0_BASE+TOFF_UART_THR), c);
}
#else	/* CONSOLE_PORTID == 2 */
void
lpc2300_uart_putc(char c)
{
	while((sil_rew_mem((VP)(TADR_UART1_BASE+TOFF_UART_LSR)) & US_TXEMPTY) == 0);
	sil_wrw_mem((VP)(TADR_UART1_BASE+TOFF_UART_THR), c);
}
#endif	/* CONSOLE_PORTID */

void
uart_isr0()
{
    uart_isr_siop(&(siopcb_table[0]));
}

void
uart_isr1()
{
    uart_isr_siop(&(siopcb_table[1]));
}

