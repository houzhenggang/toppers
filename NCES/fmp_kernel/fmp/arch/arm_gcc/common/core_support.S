/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: core_support.S 781 2011-02-16 00:52:10Z ertl-honda $
 */

/*
 *        ������¸�⥸�塼�� ������֥��������ARM�ѡ�
 */

#define TOPPERS_MACRO_ONLY
#define TOPPERS_ASM_MACRO
#define UINT_C(val)		(val)		/* uint_t�����������ޥ��� */
#define ULONG_C(val)	(val)		/* ulong_t�����������ޥ��� */
#include "kernel_impl.h"
#include "offset.h"

/*
 * �㳰�٥���
 */
    .section .vector,"a"
    .global vector_table
vector_table:
    ldr pc, reset_vector       /* �ꥻ�å�             */
    ldr pc, undef_vector       /* ̤���̿��           */
    ldr pc, swi_vector         /* ���եȥ����������   */
    ldr pc, prefech_vector     /* �ץ�ե��å����ܡ��� */
    ldr pc, data_abort_vector  /* �ǡ������ܡ���       */
    ldr pc, reset_vector
    ldr pc, irq_vector         /* IRQ                  */
    ldr pc, fiq_vector         /* FIQ                  */


/*
 *  �㳰�٥�����̿�ᤫ�黲�Ȥ����
 *  �������襢�ɥ쥹
 */
    .global vector_ref_tbl
vector_ref_tbl:
reset_vector:
    .long   start
undef_vector:
    .long   undef_handler
swi_vector:
    .long   swi_handler
prefech_vector:
    .long   prefetch_handler
data_abort_vector:
    .long   data_abort_handler
irq_vector:
    .long   irq_handler
fiq_vector:
    .long   fiq_handler

#include "target_asm.inc"

/*
 *  �������ǥ����ѥå���
 *
 */
    .text
    .align 2
    .globl dispatch
dispatch:
    /*
     *  ���Υ롼����ϡ�����������ƥ����ȡ�CPU���å����֡��ǥ����ѥå�
     *  ���ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ�
     *  ��롥
     */
    stmfd  sp!, {r4 - r11,lr}           /* �쥸��������¸ */
    my_pcb r0, r1                       /* p_runtsk���ɤ߹��� */
    ldr    r1, [r0,#PCB_p_runtsk]
    str    sp, [r1,#TCB_sp]             /* �����������å�����¸ */
    adr    r2, dispatch_r
    str    r2, [r1,#TCB_pc]             /* �¹ԺƳ����Ϥ���¸ */
    b      dispatcher

dispatch_r:
    ldmfd sp!,{r4 - r11,lr}     /* �쥸���������� */
    /*
     *  �������㳰�����롼����ε�ư
     *  dispatcher����ƤӽФ���뤿�ᡤTCB�Υ��ɥ쥹��r1�����äƤ���
     */
    ldrb  r0,[r1,#TCB_enatex]
    tst   r0,#TCB_enatex_mask
    beq   dispatch_r_1          /* enatex �� false �ʤ�꥿���� */
    ldr   r0,[r1,#TCB_texptn]   /* texptn ��0�Ǥʤ����         */
    tst   r0,r0                 
    bne   dispatch_call_texrtn  /* �������㳰�롼����θƤӽФ� */
dispatch_r_1:
    bx    lr

    /*
     *  ���������Υޥ����졼�����
     *  ����(r0)�˥ޥ����졼�������Υץ����å������äƤ��뤿���˲����ʤ�����
     */
    .text
    .align 2
    .globl dispatch_and_migrate
dispatch_and_migrate:
    stmfd  sp!, {r4 - r11,lr}           /* �쥸��������¸ */
    my_pcb r2, r1                       /* p_runtsk���ɤ߹��� */
    ldr    r1, [r2,#PCB_p_runtsk]
    str    sp, [r1,#TCB_sp]             /* �����������å�����¸ */
    adr    r3, dispatch_r
    str    r3, [r1,#TCB_pc]             /* �¹ԺƳ����Ϥ���¸ */
    ldr    sp, [r2,#PCB_istkpt]
    b      migrate_self                 /* ���������Υޥ����졼�����롼����� */

    /*
     *  ���ߤΥ���ƥ����Ȥ�Τƥޥ����졼�����
     *  ����(r0)�˥ޥ����졼�������Υץ����å������äƤ��뤿���˲����ʤ�����
     */
    .text
    .align 2
    .globl exit_and_migrate
exit_and_migrate:
    my_pcb r2, r1                       
    ldr    sp, [r2,#PCB_istkpt]         /* �󥿥�������ƥ������ѥ����å����ڤ��ؤ� */
    b      exit_and_migrate_self        /* ����������exit�ȥޥ����졼�����롼����� */

/*
 *  �ǥ����ѥå����ư��ϡ�cpu_support.S��
 */
    .globl start_dispatch
start_dispatch:
    /*
     *  ���Υ롼����ϡ������ͥ뵯ư���ˡ����٤Ƥγ���ߤ�ػߤ�������
     *  �ʳ���ߥ��å����֤�Ʊ���ˤǸƤӽФ���롥�ޤ����󥿥�������ƥ�
     *  ���Ȥ���ƤӽФ���뤳�Ȥ����ꤷ�Ƥ��롥
     *
     *  dispatcher�ϡ�CPU���å����֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����
     *  ������֡��㳰�ʳ����/CPU�㳰�ˤΥͥ��Ȳ��0�ǸƤӽФ���
     *  target_initialize�Ǥϡ��ʥ�ǥ��Ρ˳����ͥ���٥ޥ��������
     *  �Ȥ��������ͥ�������γ���ߤǤ���FIQ����Ĥ��뤳�Ȥǡ�
     *  CPU���å����֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ˤʤ롥
     *  �ޤ���initialize_task��disdsp��FALSE�˽�������Ƥ��뤿�ᡤ�ǥ�
     *  ���ѥå����ľ��֤ˤʤäƤ��롥
     *
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET) /* CPU���å����֤� */
    my_pcb r0, r1                          /* �㳰�ʳ����/CPU�㳰�ˤΥͥ��Ȳ�� */
    mov   r1, #0                           /* ��0��                              */
    str   r1, [r0, #PCB_excpt_nest_count]
    b     dispatcher_0

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 */
    .globl exit_and_dispatch
exit_and_dispatch:
    /* �ǥ����ѥå������Ρ�dispatcher�ˤ� */
    my_pcb r0, r1                       /* my_pcb���ɤ߹��� */

/*
 *  �ǥ����ѥå�������
 */
dispatcher:
    /*
     *  ���Υ롼����ϡ�����������ƥ����ȡ�CPU���å����֡��ǥ����ѥå�
     *  ���ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ�
     *  ��롥�¹ԺƳ����Ϥؤ⤳�ξ��֤Τޤ�ʬ�����롥
     *
     *  ���ʤ���������ѡ��Х������⡼�ɡ�IRQ�ػߤȤʤäƤ��롥
     *  r0�ˤϡ�my_pcb �ؤΥݥ��󥿤������
     */
#ifdef LOG_DSP_ENTER
    stmfd sp!, {r0}
    ldr   r1, [r0, #PCB_p_runtsk]
    mov   r0, r1
    bl    log_dsp_enter
    ldmfd sp!, {r0}
#endif /* LOG_DSP_ENTER */
dispatcher_0:
    ldr   r1, [r0, #PCB_p_schedtsk] /* p_schedtsk��p_runtsk�� */
    str   r1, [r0, #PCB_p_runtsk]
    cmp   r1, #0            /* p_runtsk��NULL�ʤ�dispatcher_1�� */
    beq   dispatcher_1
    ldr   sp, [r1,#TCB_sp]  /* �����������å������� */
#ifdef LOG_DSP_LEAVE
    mov   r0, r1            /* p_runtsk��ѥ�᡼���� */
    mov   r4, r1            /* r1�ϥ�����å��쥸�����ʤΤ���¸ */
    bl    log_dsp_leave
    mov   r1, r4
#endif /* LOG_DSP_LEAVE */
    ldr   pc, [r1,#TCB_pc]  /* �¹ԺƳ����Ϥ����� */

dispatcher_1:
    /*
     * CPU���å����֤β���ȡ��󥿥�������ƥ����ȼ¹Ծ��֤ؤ�
     * �����򤹤�
     */
    ldr   sp, [r0,#PCB_istkpt]         /* �󥿥�������ƥ����ȤΥ����å��� */
    add   r2, r0, #PCB_reqflg          /* r2 <- reqflg */
    add   r3, r0, #PCB_excpt_nest_count 
    mov   r0, #0
    mov   r1, #1
dispatcher_2:
    /*
     *  ����ߤ���Ĥ����󥿥�������ƥ����ȼ¹Ծ��֤Ȥ�����ߤ��Ԥġ�
     *
     *  �������󥿥�������ƥ����ȼ¹Ծ��֤��ڤ괹����Τϡ�������ȯ��
     *  �������߽����ˤɤΥ����å���Ȥ����Ȥ�������β��ȡ������
     *  �ϥ�ɥ���ǤΥ������ǥ����ѥå����ɻߤȤ���2�Ĥΰ�̣�����롥
     *
     *  �ץ����å��������Ԥ��˰ܹԤ���������ȡ�����ߵ��ĤȤϡ��Բ�
     *  ʬ�˹Ԥʤ�ɬ�פ����롥
     *  ������Բ�ʬ�˹Ԥʤ�ʤ���硤����ߤ���Ĥ���ľ��˳��
     *  �ߤ����ꡤ������ǥ��������¹Բ�ǽ���֤ˤʤ�ȡ��¹Ԥ��٤�����
     *  ��������ˤ⤫����餺�ץ����å���������Ԥ��ˤʤäƤ��ޤ���
     *
     *  ������Ԥ��δ֤ϡ�p_runtsk��NULL�ʡ�0�ˤ����ꤷ�ʤ���Фʤ��
     *  �������Τ褦�����ꤷ�ʤ��ȡ�����ߥϥ�ɥ餫��iget_tid��Ƥӽ�
     *  �����ݤ�ư����ͤ˹��פ��ʤ��ʤ롥
     *
     *  �������åȤˤ�äƤϡ������ϥ⡼�����˰ܹԤ��뤿�ᡤɸ�����ˡ��
     *  �ۤʤ��礬ɬ�פʾ�礬���롥
     *  ���Τ褦�ʥ������åȤǤϡ��������åȰ�¸�ˤ����ơ�TOPPERS_CUSTOM_IDLE
     *  ���������������֥�ޥ����Ȥ��ơ�toppers_asm_custom_idle ���Ѱ�
     *  ����Ф褤��toppers_asm_custom_idle �ε��Ҥˤ����äƤϡ����Υ쥸
     *  �����ϻ��ѤǤ��ʤ���
     *     r0, r1, r2, r3, s
     */
    str   r1, [r3]                          /* excpt_nest_count = 1 */

#ifdef TOPPERS_CUSTOM_IDLE
    toppers_asm_custom_idle
#else
    msr   cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET) /* �����ߵ���(�����ƥ�⡼��) */
    nop
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET) /* CPU���å�(�����ƥ�⡼��) */
#endif /* TOPPERS_CUSTOM_IDLE */
    ldr   r6, [r2]        /* reqflg��false�ʤ�dispatcher_2�� */
    cmp   r6, #0
    beq   dispatcher_2
    str   r0, [r2]        /* reqflg��FALSE�� */
    str   r0, [r3]        /* excpt_nest_count = 0 */
    my_pcb r0, r1         /* my_pcb���ɤ߹��� */
    b     dispatcher_0


/*
 *  �����ͥ�ν�λ�����θƽФ�
 *
 *  �⡼�ɤȥ����å����󥿥�������ƥ������Ѥ��ڤ��ؤ���
 */
    .globl call_exit_kernel
call_exit_kernel:
    msr  cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET|CPSR_IRQ_BIT|CPSR_FIQ_BIT) 
    my_pcb r2, r1                       
    ldr    sp, [r2,#PCB_istkpt]         /* �󥿥�������ƥ������ѥ����å����ڤ��ؤ� */ 
    b     exit_kernel

/*
 *  ���������ϻ�����
 *
 *  dispatcher����ƤӽФ���뤿�ᡤTCB�Υ��ɥ쥹��r1�����äƤ���
 */
    .text
    .globl start_r
start_r:
    msr   cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET) /* CPU���å�������֤� */
    ldr   lr, =ext_tsk                      /* ����������� */
    ldr   r2, [r1, #TCB_p_tinib]            /* p_runtsk->p_tinib��r2��  */
    ldr   r0, [r2, #TINIB_exinf]            /* exinf������쥸����r0��  */
    ldr   r1, [r2, #TINIB_task]             /* ��������ư���Ϥ˥����� */
    bx    r1

/*
 *  �ǥ����ѥå��׵��ѤΥץ����å��ֳ���ߤΥХ��ѥ�����
 *
 *  ���������Ѱդ���Ƥ��� ipi_handler ��ƤӽФ����˥ǥ����ѥå����
 *  �ƤӽФ����Ǥ⳰¦�Υ롼����Ǥʤ����ϡ�reqflg�򥻥åȤ��롥
 *  ��PCB�Υ��ɥ쥹��r0�����äƤ��뤳�Ȥ����ꤷ�Ƥ��롥
 */    
#ifdef USE_IPI_DIS_HANDER_BYPASS
    .global ret_int_ipi_dispatch
ret_int_ipi_dispatch:
    ldr   r2, [r0,#PCB_excpt_nest_count] /* ����褬����������ƥ����Ȥʤ� */
    cmp   r2, #0                         /* ret_int_4�� */
    beq   ret_int_4
    mov   r1, #1                         /* ����褬�󥿥�������ƥ����Ȥʤ� */
    str   r1, [r0, #PCB_reqflg]          /* reqflg��true�ˤ��ƥ꥿����       */
    b     ret_int_2                
#endif /* USE_IPI_DIS_HANDER_BYPASS */

/*
 *  CPU�㳰�ϥ�ɥ�и�����
 *
 *  ret_exc�ϡ�CPU�㳰�ϥ�ɥ餫����ä�ľ��˼¹Ԥ���롼����ǡ�
 *  CPU�㳰�ϥ�ɥ齪λ�塤�������åȰ�¸�ν�����¹Ԥ����塤
 *  �����ͥ�����γ���ߤ�ػߡ������å���CPU�㳰���Υ����å��ˡ�
 *  r0��CPU�㳰ȯ�����˼������Ƥ��륹�ԥ���å����ͤ����줿����
 *  �ǸƤӽФ���롥
 */
    .text
    .global ret_exc
ret_exc:
    /* 
     * CPU�㳰ȯ�����˥��ԥ���å���������Ƥ���С����ԥ���å�
     * �β����ϹԤ�ʤ���
     */
    cmp  r0, #0
    bne  ret_int_1

/*
 *  ����ߥϥ�ɥ�/CPU�㳰�ϥ�ɥ�и�����
 *
 *  ret_int�ϡ�����ߥϥ�ɥ餫����ä�ľ��˼¹Ԥ���롼����ǡ�
 *  ����ߥϥ�ɥ齪λ�塤�������åȰ�¸�ν�����¹Ԥ����塤
 *  �����ͥ�����γ���ߤ�ػߡ������å����������Υ����å��ˤ���
 *  ���֤ǸƤӽФ���롥
 */
    .global ret_int
ret_int:
    /*
     *  ���ԥ���å���������Ƥ���в������
     */
    my_pcb r0, r1  /* ���� */
    bl    force_unlock_spin

ret_int_1:
    /*
     *  �㳰������ߤΥͥ��ȥ�����ȡ�excpt_nest_count)�Υǥ������
     */
    my_pcb r0, r1
    ldr   r1, [r0,#PCB_excpt_nest_count] /* r1 <-excpt_nest_count */
    sub   r2, r1, #1
    str   r2, [r0,#PCB_excpt_nest_count]
    cmp   r2, #0                  /* ����褬�󥿥�������ƥ����Ȥʤ� */
    bne   ret_int_2               /* �����˥꥿����                   */

    /*
     *  reqflg������å��������˳���ߤ�ػߤ���Τϡ�reqflg������å�
     *  ����ľ��˳���ߥϥ�ɥ餬��ư���졤������ǥǥ����ѥå����׵�
     *  ���줿���ˡ������˥ǥ����ѥå�����ʤ��Ȥ������꤬�����뤿��
     *  �Ǥ��롥
     */
    ldr   r1, [r0, #PCB_reqflg] /* reqflg��true�Ǥ����ret_int_3�� */
    cmp   r1, #0
    bne   ret_int_3

    .global ret_int_2
ret_int_2:
    /*
     *  ����߽�������Υ꥿����ˤ�ꡤCPU���å�������֤˰ܹԤ��ʤ����
     *  �ʤ�ʤ���    
     *  ARM�Ǥϡ�CPSR��IRQ�ӥåȤ�CPU���å�������֤Ȥ��뤿�ᡤñ�˥꥿����
     *  ����Ф褤��
     */
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    ldmfd sp!,{r1}              /* CPSR���������� */
    msr   spsr, r1              /* ������cpsr��spsr������ */
    ldmfd sp!,{r0-r3,ip,lr,pc}^ /* ����ƥ����Ȥ�������^�դ��ʤΤǡ�cpsr <- spsr */
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    ldmfd sp!,{r0-r3,ip,lr}
    rfeia sp!
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

ret_int_3:
    /*
     *  �����Ǥϡ�����褬�������Ǥ��ꡤ�����å��ϡ������������å��ξ�
     *  �˥�����å��쥸�����Τߤ���¸���줿���֤ˤʤäƤ��롥�ޤ���
     *  �ץ����å��ϡ������ѡ��Х������⡼�ɡ������ͥ�����γ���ߤ�ػ�
     *  �������֤ȤʤäƤ��롥
     */
    mov   r1, #0                   /* reqflg��FALSE�� */
    str   r1, [r0, #PCB_reqflg]

    /*
     *  CPU���å����֤˰ܹԤ��롥
     *
     *  ���λ�����CPU���å����֤Ȥ���Τϡ�dispatcher��ʬ��������ȡ�
     *  call_texrtn��ƤӽФ����ˡ�CPU���å����֤ˤʤäƤ���ɬ�פ�����
     *  ����Ǥ��롥
     *
     *  ARM�Ǥϡ�CPSR��IRQ�ӥåȤ�CPU���å����֤�ɽ�����뤿�ᡤ�����Ǥϡ�
     *  �ä˲���Ԥ�ʤ���
     */

ret_int_4:
    /*
     *  dspflg��false�Ǥ�����ȡ�p_runtsk��p_schedtsk��Ʊ�����ˤϡ�
     *  �ǥ����ѥå���Ԥ�ʤ������Υ����å���ɬ�פʤΤϡ��������㳰��
     *  ���롼����θƽФ���ɬ�פʾ��ˡ��ǥ����ѥå���ɬ�פʤ��Ƥ⡤
     *  reqflg��TRUE�ˤ��뤿��Ǥ��롥
     */
    ldr   r1, [r0, #PCB_p_runtsk] /* p_runtsk ��r1���ɤ߹��� */
    ldr   r2, [r0, #PCB_dspflg]   /* dspflg��false�ʤ�ret_int_r_1�� */
    cmp   r2, #0
    beq   ret_int_r_1

    /*
     *  �ǥ����ѥå���ɬ����������å�
     */
    ldr   r2, [r0, #PCB_p_schedtsk] /* p_schedtsk ��r2���ɤ߹��� */
    cmp   r1, r2              /* p_runtsk��p_schedtsk��Ʊ���ʤ� */
    beq   ret_int_r_1         /*                    ret_int_r_1�� */
    stmfd sp!, {r4-r11}       /* �Ĥ�Υ쥸��������¸ */
    str   sp, [r1,#TCB_sp]    /* �����������å�����¸ */
    adr   r2, ret_int_r       /* �¹ԺƳ����Ϥ���¸   */
    str   r2, [r1,#TCB_pc]
    b     dispatcher

ret_int_r: 
    ldmfd sp!, {r4-r11}       /* �쥸���������� */
ret_int_r_1:
    /*
     *  enatex��true�ǡ�texptn��0�Ǥʤ���С��������㳰�����롼�����
     *  �ƤӽФ���
     *  dispatcher����ƤӽФ���뤿�ᡤTCB�Υ��ɥ쥹��r1�����äƤ���
     */
    ldrb  r0, [r1,#TCB_enatex]
    tst   r0, #TCB_enatex_mask
    beq   ret_int_r_2            /* enatex �� false �ʤ� ret_int_r2 �� */
    ldr   r0, [r1,#TCB_texptn]   /* texptn�������               */
    tst   r0, r0                 /* texptn ��0��̵�����         */
    blne  dispatch_call_texrtn   /* �������㳰�롼����θƤӽФ� */
ret_int_r_2:
    /*
     *  ����߽�������Υ꥿����ˤ�ꡤCPU���å�������֤˰ܹԤ����
     *  ���ˤ��롥ARM��CPSR��IRQ�ӥåȤˤ�ä�CPU���å����֤�ɽ���Ƥ�
     *  �뤿�ᡤ���Τޤޥ꥿���󤹤�Ф褤��
     */ 
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    ldmfd sp!, {r0}             /* spsr ������ */
    msr   spsr,r0               /* ������cpsr��spsr������ */
    ldmfd sp!,{r0-r3,ip,lr,pc}^ /* ������������ ^�դ��ʤΤǡ�cpsr <- spsr */
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    ldmfd sp!,{r0-r3,ip,lr}
    rfeia sp!
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

/*
 * CPU�㳰�ϥ�ɥ�
 *
 * CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롥
 * 
 */

/*
 *  ̤���̿�� �㳰�ϥ�ɥ�
 */
    .text
    .align 2
    .global undef_handler
undef_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */

    /*
     * spsr��������Ϥ�������뤿���̤����⡼�ɤ�
     */
    msr   cpsr, #(CPSR_UND|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(�����) spsr(cpsr_svc)�򥹡��ѡ��Х������⡼�ɤΥ����å���
     * ��¸��
     */
    srsdb #CPSR_SVC! 

    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     *  ����ߥ��å����֡�CPU���å����֤�CPU�㳰ȯ������
     *  ���֤�Ѿ����롥
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_UNDEF
    b     target_exc_handler

/*
 *  SWI �㳰�ϥ�ɥ�
 */
    .text
    .align 2
    .global swi_handler
swi_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     *  ���������ѡ��Х������⡼�ɤ�����CPU���å����֤Ȥ���
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(�����) spsr(cpsr_svc)�򥹡��ѡ��Х������⡼�ɤΥ����å���
     * ��¸��
     */
    srsdb #CPSR_SVC! 

    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     *  ����ߥ��å����֡�CPU���å����֤�CPU�㳰ȯ������
     *  ���֤�Ѿ����롥
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_SWI
    b     target_exc_handler

/*
 *  �ץ�ե��å����ܡ��� �㳰�ϥ�ɥ�
 */
    .text
    .align 2
    .global prefetch_handler
prefetch_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */

    /*
     * spsr��������Ϥ�������뤿��˥��ܡ��ȥ⡼�ɤ�
     */
    msr   cpsr, #(CPSR_ABT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(�����) spsr(cpsr_svc)�򥹡��ѡ��Х������⡼�ɤΥ����å���
     * ��¸��
     */
    srsdb #CPSR_SVC! 

    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_PABORT
    b     target_exc_handler

/*
 *  �ǡ������ܡ��� �㳰�ϥ�ɥ�
 */
    .text
    .align 2
    .global data_abort_handler
data_abort_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */

    /*
     * spsr��������Ϥ�������뤿��˥��ܡ��ȥ⡼�ɤ�
     */
    msr   cpsr, #(CPSR_ABT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(�����) spsr(cpsr_svc)�򥹡��ѡ��Х������⡼�ɤΥ����å���
     * ��¸��
     */
    srsdb #CPSR_SVC! 

    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_DABORT
    b     target_exc_handler


#ifndef TARGET_FIQ_HANDLER
/*
 *  FIQ �㳰�ϥ�ɥ�
 */
    .text
    .align 2
    .global fiq_handler
fiq_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_FIQ_BIT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pc�ϥ��ߡ� */

    /*
     * spsr��������Ϥ�������뤿���FIQ�⡼�ɤ�
     */
    msr   cpsr, #(CPSR_FIQ|CPSR_FIQ_BIT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(�����) spsr(cpsr_svc)�򥹡��ѡ��Х������⡼�ɤΥ����å���
     * ��¸��
     */
    srsdb #CPSR_SVC! 

    /* 
     *  �㳰ȯ������ư����⡼��(�����ѡ��Х������⡼��)��
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_FIQ
    b     target_exc_handler
#endif /* TARGET_FIQ_HANDLER */

/*
 *  ���������Ԥ�
 */
    .globl _sil_dly_nse
_sil_dly_nse:
    sub   r0, r0, #SIL_DLY_TIM1
    cmp   r0, #0
    bgt   _sil_dly_nse1
    bxle  lr
_sil_dly_nse1:
    sub   r0, r0, #SIL_DLY_TIM2
    cmp   r0, #0
    bgt   _sil_dly_nse1
    bxle  lr

#ifdef __thumb__
    .text
    .align 2
    .global current_sr
current_sr:
    mrs   r0, cpsr
    bx    lr

   .global set_sr
set_sr:
    msr   cpsr, r0
    bx    lr
#endif /* __thumb__ */