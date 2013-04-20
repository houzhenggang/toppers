/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#ifndef TOPPERS_EMPTY_LABEL
#define TOPPERS_EMPTY_LABEL(x,y) x y[0]
#endif

#if TKERNEL_PRID != 0x08u
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives (#include)
 */

#include "sample1.h"
#include "target_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "target_ipi.h"
#include "logtrace/trace_config.h"

/*
 *  Default Definitions of Trace Log Macros
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

/*
 *  Processor Management Functions
 */

PCB _kernel_prc1_pcb __attribute__((section(".bss._kernel_prc1s_pcb"),nocommon));
PCB _kernel_prc2_pcb __attribute__((section(".bss._kernel_prc2s_pcb"),nocommon));
PCB _kernel_prc3_pcb __attribute__((section(".bss._kernel_prc3s_pcb"),nocommon));
PCB _kernel_prc4_pcb __attribute__((section(".bss._kernel_prc4s_pcb"),nocommon));

PCB* const _kernel_p_pcb_table[TNUM_PRCID] = {
	&_kernel_prc1_pcb,
	&_kernel_prc2_pcb,
	&_kernel_prc3_pcb,
	&_kernel_prc4_pcb
};

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_LOGTASK1[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_LOGTASK2[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_LOGTASK3[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_LOGTASK4[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));
static STK_T _kernel_stack_TASK1_1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK1_2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK1_3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_SERVER_TASK1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK2_1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK2_2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK2_3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_SERVER_TASK2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK3_1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_TASK3_2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_TASK3_3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_SERVER_TASK3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc3s_tstack"),nocommon));
static STK_T _kernel_stack_TASK4_1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));
static STK_T _kernel_stack_TASK4_2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));
static STK_T _kernel_stack_TASK4_3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK4[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));
static STK_T _kernel_stack_SERVER_TASK4[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc4s_tstack"),nocommon));

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC1), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC2), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC3), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK3, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC4), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK4, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|1), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|2), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_2, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|3), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_3, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(1), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(1), (server_task), INT_PRIORITY(SERVER_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_SERVER_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x20000|1), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK2_1, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x20000|2), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK2_2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x20000|3), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK2_3, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(2), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(2), (server_task), INT_PRIORITY(SERVER_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_SERVER_TASK2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x30000|1), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK3_1, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x30000|2), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK3_2, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x30000|3), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK3_3, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(3), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK3, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(3), (server_task), INT_PRIORITY(SERVER_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_SERVER_TASK3, (TA_NULL), (NULL), 3, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x40000|1), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK4_1, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x40000|2), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK4_2, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x40000|3), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK4_3, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(4), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK4, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(4), (server_task), INT_PRIORITY(SERVER_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_SERVER_TASK4, (TA_NULL), (NULL), 4, (uint_t)(0x0000000f) }
};

TCB _kernel_tcb_LOGTASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_LOGTASK2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_LOGTASK3	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_LOGTASK4	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));
TCB _kernel_tcb_TASK1_1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK1_2	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK1_3	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_SERVER_TASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK2_1	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK2_2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK2_3	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_SERVER_TASK2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK3_1	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_TASK3_2	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_TASK3_3	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK3	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_SERVER_TASK3	__attribute__((section(".bss._kernel_prc3s_tskcb"),nocommon));
TCB _kernel_tcb_TASK4_1	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));
TCB _kernel_tcb_TASK4_2	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));
TCB _kernel_tcb_TASK4_3	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK4	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));
TCB _kernel_tcb_SERVER_TASK4	__attribute__((section(".bss._kernel_prc4s_tskcb"),nocommon));


TCB* const _kernel_p_tcb_table[TNUM_TSKID] ={
	&_kernel_tcb_LOGTASK1,
	&_kernel_tcb_LOGTASK2,
	&_kernel_tcb_LOGTASK3,
	&_kernel_tcb_LOGTASK4,
	&_kernel_tcb_TASK1_1,
	&_kernel_tcb_TASK1_2,
	&_kernel_tcb_TASK1_3,
	&_kernel_tcb_MAIN_TASK1,
	&_kernel_tcb_SERVER_TASK1,
	&_kernel_tcb_TASK2_1,
	&_kernel_tcb_TASK2_2,
	&_kernel_tcb_TASK2_3,
	&_kernel_tcb_MAIN_TASK2,
	&_kernel_tcb_SERVER_TASK2,
	&_kernel_tcb_TASK3_1,
	&_kernel_tcb_TASK3_2,
	&_kernel_tcb_TASK3_3,
	&_kernel_tcb_MAIN_TASK3,
	&_kernel_tcb_SERVER_TASK3,
	&_kernel_tcb_TASK4_1,
	&_kernel_tcb_TASK4_2,
	&_kernel_tcb_TASK4_3,
	&_kernel_tcb_MAIN_TASK4,
	&_kernel_tcb_SERVER_TASK4
};

const ID _kernel_torder_table[TNUM_TSKID] = {
	LOGTASK1, LOGTASK2, LOGTASK3, LOGTASK4, TASK1_1, TASK1_2, TASK1_3, MAIN_TASK1, SERVER_TASK1, TASK2_1, TASK2_2, TASK2_3, MAIN_TASK2, SERVER_TASK2, TASK3_1, TASK3_2, TASK3_3, MAIN_TASK3, SERVER_TASK3, TASK4_1, TASK4_2, TASK4_3, MAIN_TASK4, SERVER_TASK4
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (1), (1) },
	{ (TA_TPRI), (&(_kernel_prc2_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc2_pcb.obj_lock)), (1), (1) },
	{ (TA_TPRI), (&(_kernel_prc3_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc3_pcb.obj_lock)), (1), (1) },
	{ (TA_TPRI), (&(_kernel_prc4_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc4_pcb.obj_lock)), (1), (1) }
};

SEMCB _kernel_semcb_SERIAL_RCV_SEM1 __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM1 __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_RCV_SEM2 __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM2 __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_RCV_SEM3 __attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM3 __attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_RCV_SEM4 __attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM4 __attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));

SEMCB* const _kernel_p_semcb_table[TNUM_SEMID] = {
	&_kernel_semcb_SERIAL_RCV_SEM1,
	&_kernel_semcb_SERIAL_SND_SEM1,
	&_kernel_semcb_SERIAL_RCV_SEM2,
	&_kernel_semcb_SERIAL_SND_SEM2,
	&_kernel_semcb_SERIAL_RCV_SEM3,
	&_kernel_semcb_SERIAL_SND_SEM3,
	&_kernel_semcb_SERIAL_RCV_SEM4,
	&_kernel_semcb_SERIAL_SND_SEM4
};

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB* const, _kernel_p_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

static intptr_t _kernel_dtqmb_SERVER_DTQ1[NUM_SERVER_DTQ] __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
static intptr_t _kernel_dtqmb_SERVER_DTQ2[NUM_SERVER_DTQ] __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
static intptr_t _kernel_dtqmb_SERVER_DTQ3[NUM_SERVER_DTQ] __attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
static intptr_t _kernel_dtqmb_SERVER_DTQ4[NUM_SERVER_DTQ] __attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));

const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (NUM_SERVER_DTQ), (_kernel_dtqmb_SERVER_DTQ1)  },
	{ (TA_TPRI), (&(_kernel_prc2_pcb.obj_lock)), (NUM_SERVER_DTQ), (_kernel_dtqmb_SERVER_DTQ2)  },
	{ (TA_TPRI), (&(_kernel_prc3_pcb.obj_lock)), (NUM_SERVER_DTQ), (_kernel_dtqmb_SERVER_DTQ3)  },
	{ (TA_TPRI), (&(_kernel_prc4_pcb.obj_lock)), (NUM_SERVER_DTQ), (_kernel_dtqmb_SERVER_DTQ4)  }
};

DTQCB _kernel_dtqcb_SERVER_DTQ1 __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
DTQCB _kernel_dtqcb_SERVER_DTQ2 __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
DTQCB _kernel_dtqcb_SERVER_DTQ3 __attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
DTQCB _kernel_dtqcb_SERVER_DTQ4 __attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));

DTQCB* const _kernel_p_dtqcb_table[TNUM_DTQID] = {
	&_kernel_dtqcb_SERVER_DTQ1,
	&_kernel_dtqcb_SERVER_DTQ2,
	&_kernel_dtqcb_SERVER_DTQ3,
	&_kernel_dtqcb_SERVER_DTQ4
};

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB* const, _kernel_p_pdqcb_table);

/*
 *  Mailbox Functions
 */

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

TOPPERS_EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
TOPPERS_EMPTY_LABEL(MBXCB* const, _kernel_p_mbxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB* const, _kernel_p_mpfcb_table);

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_NULL), (intptr_t)(1), (cyclic_handler), (CYC_TIME), (0), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(2), (cyclic_handler), (CYC_TIME), (0), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(3), (cyclic_handler), (CYC_TIME), (0), 3, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(4), (cyclic_handler), (CYC_TIME), (0), 4, (uint_t)(0x0000000f) }
};

CYCCB _kernel_cyccb_CYCHDR1	__attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
CYCCB _kernel_cyccb_CYCHDR2	__attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
CYCCB _kernel_cyccb_CYCHDR3	__attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
CYCCB _kernel_cyccb_CYCHDR4	__attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));

CYCCB* const _kernel_p_cyccb_table[TNUM_CYCID] = {
	&_kernel_cyccb_CYCHDR1,
	&_kernel_cyccb_CYCHDR2,
	&_kernel_cyccb_CYCHDR3,
	&_kernel_cyccb_CYCHDR4
};

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(1), (alarm_handler), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(2), (alarm_handler), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(3), (alarm_handler), 3, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(4), (alarm_handler), 4, (uint_t)(0x0000000f) }
};

ALMCB _kernel_almcb_ALMHDR1	__attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
ALMCB _kernel_almcb_ALMHDR2	__attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
ALMCB _kernel_almcb_ALMHDR3	__attribute__((section(".bss._kernel_prc3s_objcb"),nocommon));
ALMCB _kernel_almcb_ALMHDR4	__attribute__((section(".bss._kernel_prc4s_objcb"),nocommon));

ALMCB* const _kernel_p_almcb_table[TNUM_ALMID] = {
	&_kernel_almcb_ALMHDR1,
	&_kernel_almcb_ALMHDR2,
	&_kernel_almcb_ALMHDR3,
	&_kernel_almcb_ALMHDR4
};

/*
 *  Spin Lock Functions
 */

const ID _kernel_tmax_spnid = (TMIN_SPNID + TNUM_SPNID - 1);

TOPPERS_EMPTY_LABEL(const SPNINIB, _kernel_spninib_table);
TOPPERS_EMPTY_LABEL(SPNCB* const, _kernel_p_spncb_table);

/*
 *  Interrupt Management Functions
 */


#define TNUM_INHNO	12
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER_PRC1, 0x10005, target_timer_handler)
INTHDR_ENTRY(INHNO_TIMER_PRC2, 0x20005, target_timer_handler)
INTHDR_ENTRY(INHNO_TIMER_PRC3, 0x30005, target_timer_handler)
INTHDR_ENTRY(INHNO_TIMER_PRC4, 0x40005, target_timer_handler)
INTHDR_ENTRY(INHNO_SIO_PRC1, 0x10002, sio_handler)
INTHDR_ENTRY(INHNO_SIO_PRC2, 0x20002, sio_handler)
INTHDR_ENTRY(INHNO_SIO_PRC3, 0x30002, sio_handler)
INTHDR_ENTRY(INHNO_SIO_PRC4, 0x40002, sio_handler)
INTHDR_ENTRY(INHNO_IPI_PRC1, 0x10010, _kernel_ipi_handler)
INTHDR_ENTRY(INHNO_IPI_PRC2, 0x20010, _kernel_ipi_handler)
INTHDR_ENTRY(INHNO_IPI_PRC3, 0x30010, _kernel_ipi_handler)
INTHDR_ENTRY(INHNO_IPI_PRC4, 0x40010, _kernel_ipi_handler)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC1, target_timer_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_TIMER_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC2, target_timer_handler)), 2, (uint_t)(0x2) },
	{ (INHNO_TIMER_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC3, target_timer_handler)), 3, (uint_t)(0x4) },
	{ (INHNO_TIMER_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC4, target_timer_handler)), 4, (uint_t)(0x8) },
	{ (INHNO_SIO_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC1, sio_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_SIO_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC2, sio_handler)), 2, (uint_t)(0x2) },
	{ (INHNO_SIO_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC3, sio_handler)), 3, (uint_t)(0x4) },
	{ (INHNO_SIO_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC4, sio_handler)), 4, (uint_t)(0x8) },
	{ (INHNO_IPI_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC1, _kernel_ipi_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_IPI_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC2, _kernel_ipi_handler)), 2, (uint_t)(0x2) },
	{ (INHNO_IPI_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC3, _kernel_ipi_handler)), 3, (uint_t)(0x4) },
	{ (INHNO_IPI_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC4, _kernel_ipi_handler)), 4, (uint_t)(0x8) }
};

#define TNUM_INTNO	12
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER_PRC1), (TA_ENAINT|INTATR_TIMER_PRC1), (INTPRI_TIMER_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_TIMER_PRC2), (TA_ENAINT|INTATR_TIMER_PRC2), (INTPRI_TIMER_PRC2),  2, (uint_t)(0x2)},
	{ (INTNO_TIMER_PRC3), (TA_ENAINT|INTATR_TIMER_PRC3), (INTPRI_TIMER_PRC3),  3, (uint_t)(0x4)},
	{ (INTNO_TIMER_PRC4), (TA_ENAINT|INTATR_TIMER_PRC4), (INTPRI_TIMER_PRC4),  4, (uint_t)(0x8)},
	{ (INTNO_SIO_PRC1), (INTATR_SIO_PRC1), (INTPRI_SIO_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_SIO_PRC2), (INTATR_SIO_PRC2), (INTPRI_SIO_PRC2),  2, (uint_t)(0x2)},
	{ (INTNO_SIO_PRC3), (INTATR_SIO_PRC3), (INTPRI_SIO_PRC3),  3, (uint_t)(0x4)},
	{ (INTNO_SIO_PRC4), (INTATR_SIO_PRC4), (INTPRI_SIO_PRC4),  4, (uint_t)(0x8)},
	{ (INTNO_IPI_PRC1), (TA_ENAINT), (INTPRI_IPI_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_IPI_PRC2), (TA_ENAINT), (INTPRI_IPI_PRC2),  2, (uint_t)(0x2)},
	{ (INTNO_IPI_PRC3), (TA_ENAINT), (INTPRI_IPI_PRC3),  3, (uint_t)(0x4)},
	{ (INTNO_IPI_PRC4), (TA_ENAINT), (INTPRI_IPI_PRC4),  4, (uint_t)(0x8)}
};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_PRC1_ISTK
#define TOPPERS_PRC1_ISTKSZ		DEFAULT_PRC1_ISTKSZ
#define TOPPERS_PRC1_ISTK		DEFAULT_PRC1_ISTK
#else /* DEAULT_PRC1_ISTK */
static STK_T					_kernel_prc1_istack[COUNT_STK_T(DEFAULT_PRC1_ISTKSZ)] __attribute__((section(".bss._kernel_prc1p_istack"),nocommon));
#define TOPPERS_PRC1_ISTKSZ		ROUND_STK_T(DEFAULT_PRC1_ISTKSZ)
#define TOPPERS_PRC1_ISTK		_kernel_prc1_istack
#endif /* DEAULT_PRC1_ISTK */

#ifdef DEFAULT_PRC2_ISTK
#define TOPPERS_PRC2_ISTKSZ		DEFAULT_PRC2_ISTKSZ
#define TOPPERS_PRC2_ISTK		DEFAULT_PRC2_ISTK
#else /* DEAULT_PRC2_ISTK */
static STK_T					_kernel_prc2_istack[COUNT_STK_T(DEFAULT_PRC2_ISTKSZ)] __attribute__((section(".bss._kernel_prc2p_istack"),nocommon));
#define TOPPERS_PRC2_ISTKSZ		ROUND_STK_T(DEFAULT_PRC2_ISTKSZ)
#define TOPPERS_PRC2_ISTK		_kernel_prc2_istack
#endif /* DEAULT_PRC2_ISTK */

#ifdef DEFAULT_PRC3_ISTK
#define TOPPERS_PRC3_ISTKSZ		DEFAULT_PRC3_ISTKSZ
#define TOPPERS_PRC3_ISTK		DEFAULT_PRC3_ISTK
#else /* DEAULT_PRC3_ISTK */
static STK_T					_kernel_prc3_istack[COUNT_STK_T(DEFAULT_PRC3_ISTKSZ)] __attribute__((section(".bss._kernel_prc3p_istack"),nocommon));
#define TOPPERS_PRC3_ISTKSZ		ROUND_STK_T(DEFAULT_PRC3_ISTKSZ)
#define TOPPERS_PRC3_ISTK		_kernel_prc3_istack
#endif /* DEAULT_PRC3_ISTK */

#ifdef DEFAULT_PRC4_ISTK
#define TOPPERS_PRC4_ISTKSZ		DEFAULT_PRC4_ISTKSZ
#define TOPPERS_PRC4_ISTK		DEFAULT_PRC4_ISTK
#else /* DEAULT_PRC4_ISTK */
static STK_T					_kernel_prc4_istack[COUNT_STK_T(DEFAULT_PRC4_ISTKSZ)] __attribute__((section(".bss._kernel_prc4p_istack"),nocommon));
#define TOPPERS_PRC4_ISTKSZ		ROUND_STK_T(DEFAULT_PRC4_ISTKSZ)
#define TOPPERS_PRC4_ISTK		_kernel_prc4_istack
#endif /* DEAULT_PRC4_ISTK */

const SIZE _kernel_istksz_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTKSZ,
	TOPPERS_PRC2_ISTKSZ,
	TOPPERS_PRC3_ISTKSZ,
	TOPPERS_PRC4_ISTKSZ
};

STK_T *const _kernel_istk_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTK,
	TOPPERS_PRC2_ISTK,
	TOPPERS_PRC3_ISTK,
	TOPPERS_PRC4_ISTK
};

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt_table[TNUM_PRCID] = {
	TOPPERS_ISTKPT(TOPPERS_PRC1_ISTK, TOPPERS_PRC1_ISTKSZ),
	TOPPERS_ISTKPT(TOPPERS_PRC2_ISTK, TOPPERS_PRC2_ISTKSZ),
	TOPPERS_ISTKPT(TOPPERS_PRC3_ISTK, TOPPERS_PRC3_ISTKSZ),
	TOPPERS_ISTKPT(TOPPERS_PRC4_ISTK, TOPPERS_PRC4_ISTKSZ)
};
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_prc1_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc1s_tevt"),nocommon));
TMEVTN   _kernel_prc2_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc2s_tevt"),nocommon));
TMEVTN   _kernel_prc3_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc3s_tevt"),nocommon));
TMEVTN   _kernel_prc4_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc4s_tevt"),nocommon));

TMEVTN* const _kernel_p_tmevt_heap_table[TNUM_PRCID] = {
	  _kernel_prc1_tmevt_heap,
	  _kernel_prc2_tmevt_heap,
	  _kernel_prc3_tmevt_heap,
	  _kernel_prc4_tmevt_heap
};

TEVTCB   _kernel_prc1_tevtcb __attribute__((section(".bss._kernel_prc1s_tevt"),nocommon));
TEVTCB   _kernel_prc2_tevtcb __attribute__((section(".bss._kernel_prc2s_tevt"),nocommon));
TEVTCB   _kernel_prc3_tevtcb __attribute__((section(".bss._kernel_prc3s_tevt"),nocommon));
TEVTCB   _kernel_prc4_tevtcb __attribute__((section(".bss._kernel_prc4s_tevt"),nocommon));

TEVTCB* const _kernel_p_tevtcb_table[TNUM_PRCID] = {
	  &_kernel_prc1_tevtcb,
	  &_kernel_prc2_tevtcb,
	  &_kernel_prc3_tevtcb,
	  &_kernel_prc4_tevtcb
};


/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
		_kernel_initialize_semaphore();
		_kernel_initialize_dataqueue();
		_kernel_initialize_cyclic();
		_kernel_initialize_alarm();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_global_inirtn(void)
{
	((INIRTN)(trace_initialize))((intptr_t)(TRACE_AUTOSTOP));
}

void
_kernel_call_local_inirtn(void)
{
	if (x_prc_index() == INDEX_PRC(1)) {
		((INIRTN)(target_timer_initialize))((intptr_t)(0));
		((INIRTN)(syslog_initialize))((intptr_t)(0));
		((INIRTN)(print_banner_copyright))((intptr_t)(0));
		((INIRTN)(print_banner))((intptr_t)(0));
		((INIRTN)(sio_initialize))((intptr_t)(0));
		((INIRTN)(serial_initialize))((intptr_t)(0));
	}

	if (x_prc_index() == INDEX_PRC(2)) {
		((INIRTN)(target_timer_initialize))((intptr_t)(0));
		((INIRTN)(syslog_initialize))((intptr_t)(0));
		((INIRTN)(print_banner))((intptr_t)(0));
		((INIRTN)(sio_initialize))((intptr_t)(1));
		((INIRTN)(serial_initialize))((intptr_t)(1));
	}

	if (x_prc_index() == INDEX_PRC(3)) {
		((INIRTN)(target_timer_initialize))((intptr_t)(0));
		((INIRTN)(syslog_initialize))((intptr_t)(0));
		((INIRTN)(print_banner))((intptr_t)(0));
		((INIRTN)(sio_initialize))((intptr_t)(2));
		((INIRTN)(serial_initialize))((intptr_t)(2));
	}

	if (x_prc_index() == INDEX_PRC(4)) {
		((INIRTN)(target_timer_initialize))((intptr_t)(0));
		((INIRTN)(syslog_initialize))((intptr_t)(0));
		((INIRTN)(print_banner))((intptr_t)(0));
		((INIRTN)(sio_initialize))((intptr_t)(3));
		((INIRTN)(serial_initialize))((intptr_t)(3));
	}

}

/*
 *  Termination Routine
 */

void
_kernel_call_global_terrtn(void)
{
	((TERRTN)(trace_dump))((intptr_t)(target_fput_log_file));
}

void
_kernel_call_local_terrtn(void)
{
	if (x_prc_index() == INDEX_PRC(1)) {
		((TERRTN)(logtask_terminate))((intptr_t)(0));
		((TERRTN)(target_timer_terminate))((intptr_t)(0));
	}

	if (x_prc_index() == INDEX_PRC(2)) {
		((TERRTN)(logtask_terminate))((intptr_t)(0));
		((TERRTN)(target_timer_terminate))((intptr_t)(0));
	}

	if (x_prc_index() == INDEX_PRC(3)) {
		((TERRTN)(logtask_terminate))((intptr_t)(0));
		((TERRTN)(target_timer_terminate))((intptr_t)(0));
	}

	if (x_prc_index() == INDEX_PRC(4)) {
		((TERRTN)(logtask_terminate))((intptr_t)(0));
		((TERRTN)(target_timer_terminate))((intptr_t)(0));
	}
}


const FP _kernel_prc1_exch_table[TNUM_EXCH] = {
 	(FP)(_kernel_default_exc_handler) /* 0 */,
 	(FP)(_kernel_default_exc_handler) /* 1 */,
 	(FP)(_kernel_default_exc_handler) /* 2 */,
 	(FP)(_kernel_default_exc_handler) /* 3 */,
 	(FP)(_kernel_default_exc_handler) /* 4 */,
 	(FP)(_kernel_default_exc_handler) /* 5 */,
 	(FP)(_kernel_default_exc_handler) /* 6 */
};

const FP _kernel_prc2_exch_table[TNUM_EXCH] = {
 	(FP)(_kernel_default_exc_handler) /* 0 */,
 	(FP)(_kernel_default_exc_handler) /* 1 */,
 	(FP)(_kernel_default_exc_handler) /* 2 */,
 	(FP)(_kernel_default_exc_handler) /* 3 */,
 	(FP)(_kernel_default_exc_handler) /* 4 */,
 	(FP)(_kernel_default_exc_handler) /* 5 */,
 	(FP)(_kernel_default_exc_handler) /* 6 */
};

const FP _kernel_prc3_exch_table[TNUM_EXCH] = {
 	(FP)(_kernel_default_exc_handler) /* 0 */,
 	(FP)(_kernel_default_exc_handler) /* 1 */,
 	(FP)(_kernel_default_exc_handler) /* 2 */,
 	(FP)(_kernel_default_exc_handler) /* 3 */,
 	(FP)(_kernel_default_exc_handler) /* 4 */,
 	(FP)(_kernel_default_exc_handler) /* 5 */,
 	(FP)(_kernel_default_exc_handler) /* 6 */
};

const FP _kernel_prc4_exch_table[TNUM_EXCH] = {
 	(FP)(_kernel_default_exc_handler) /* 0 */,
 	(FP)(_kernel_default_exc_handler) /* 1 */,
 	(FP)(_kernel_default_exc_handler) /* 2 */,
 	(FP)(_kernel_default_exc_handler) /* 3 */,
 	(FP)(_kernel_default_exc_handler) /* 4 */,
 	(FP)(_kernel_default_exc_handler) /* 5 */,
 	(FP)(_kernel_default_exc_handler) /* 6 */
};

const FP* const _kernel_p_exch_table[TNUM_PRCID] = {
	_kernel_prc1_exch_table,
	_kernel_prc2_exch_table,
	_kernel_prc3_exch_table,
	_kernel_prc4_exch_table
};

const PRI _kernel_prc1_inh_ipm_table[TNUM_INH] = {
	0, /* 0x10000 */
	0, /* 0x10001 */
	INTPRI_SIO_PRC1, /* 0x10002 */
	0, /* 0x10003 */
	0, /* 0x10004 */
	INTPRI_TIMER_PRC1, /* 0x10005 */
	0, /* 0x10006 */
	0, /* 0x10007 */
	0, /* 0x10008 */
	0, /* 0x10009 */
	0, /* 0x1000a */
	0, /* 0x1000b */
	0, /* 0x1000c */
	0, /* 0x1000d */
	0, /* 0x1000e */
	0, /* 0x1000f */
	INTPRI_IPI_PRC1, /* 0x10010 */
	0, /* 0x10011 */
	0, /* 0x10012 */
	0, /* 0x10013 */
	0, /* 0x10014 */
	0, /* 0x10015 */
	0, /* 0x10016 */
	0, /* 0x10017 */
	0, /* 0x10018 */
	0, /* 0x10019 */
	0, /* 0x1001a */
	0, /* 0x1001b */
	0, /* 0x1001c */
	0, /* 0x1001d */
	0, /* 0x1001e */
	0, /* 0x1001f */
};

const PRI _kernel_prc2_inh_ipm_table[TNUM_INH] = {
	0, /* 0x20000 */
	0, /* 0x20001 */
	INTPRI_SIO_PRC2, /* 0x20002 */
	0, /* 0x20003 */
	0, /* 0x20004 */
	INTPRI_TIMER_PRC2, /* 0x20005 */
	0, /* 0x20006 */
	0, /* 0x20007 */
	0, /* 0x20008 */
	0, /* 0x20009 */
	0, /* 0x2000a */
	0, /* 0x2000b */
	0, /* 0x2000c */
	0, /* 0x2000d */
	0, /* 0x2000e */
	0, /* 0x2000f */
	INTPRI_IPI_PRC2, /* 0x20010 */
	0, /* 0x20011 */
	0, /* 0x20012 */
	0, /* 0x20013 */
	0, /* 0x20014 */
	0, /* 0x20015 */
	0, /* 0x20016 */
	0, /* 0x20017 */
	0, /* 0x20018 */
	0, /* 0x20019 */
	0, /* 0x2001a */
	0, /* 0x2001b */
	0, /* 0x2001c */
	0, /* 0x2001d */
	0, /* 0x2001e */
	0, /* 0x2001f */
};

const PRI _kernel_prc3_inh_ipm_table[TNUM_INH] = {
	0, /* 0x30000 */
	0, /* 0x30001 */
	INTPRI_SIO_PRC3, /* 0x30002 */
	0, /* 0x30003 */
	0, /* 0x30004 */
	INTPRI_TIMER_PRC3, /* 0x30005 */
	0, /* 0x30006 */
	0, /* 0x30007 */
	0, /* 0x30008 */
	0, /* 0x30009 */
	0, /* 0x3000a */
	0, /* 0x3000b */
	0, /* 0x3000c */
	0, /* 0x3000d */
	0, /* 0x3000e */
	0, /* 0x3000f */
	INTPRI_IPI_PRC3, /* 0x30010 */
	0, /* 0x30011 */
	0, /* 0x30012 */
	0, /* 0x30013 */
	0, /* 0x30014 */
	0, /* 0x30015 */
	0, /* 0x30016 */
	0, /* 0x30017 */
	0, /* 0x30018 */
	0, /* 0x30019 */
	0, /* 0x3001a */
	0, /* 0x3001b */
	0, /* 0x3001c */
	0, /* 0x3001d */
	0, /* 0x3001e */
	0, /* 0x3001f */
};

const PRI _kernel_prc4_inh_ipm_table[TNUM_INH] = {
	0, /* 0x40000 */
	0, /* 0x40001 */
	INTPRI_SIO_PRC4, /* 0x40002 */
	0, /* 0x40003 */
	0, /* 0x40004 */
	INTPRI_TIMER_PRC4, /* 0x40005 */
	0, /* 0x40006 */
	0, /* 0x40007 */
	0, /* 0x40008 */
	0, /* 0x40009 */
	0, /* 0x4000a */
	0, /* 0x4000b */
	0, /* 0x4000c */
	0, /* 0x4000d */
	0, /* 0x4000e */
	0, /* 0x4000f */
	INTPRI_IPI_PRC4, /* 0x40010 */
	0, /* 0x40011 */
	0, /* 0x40012 */
	0, /* 0x40013 */
	0, /* 0x40014 */
	0, /* 0x40015 */
	0, /* 0x40016 */
	0, /* 0x40017 */
	0, /* 0x40018 */
	0, /* 0x40019 */
	0, /* 0x4001a */
	0, /* 0x4001b */
	0, /* 0x4001c */
	0, /* 0x4001d */
	0, /* 0x4001e */
	0, /* 0x4001f */
};

const PRI* const _kernel_p_inh_ipm_table[TNUM_PRCID] = {
	_kernel_prc1_inh_ipm_table,
	_kernel_prc2_inh_ipm_table,
	_kernel_prc3_inh_ipm_table,
	_kernel_prc4_inh_ipm_table
};

const uint32_t _kernel_prc1_ipm_mask_table[8]={
	UINT32_C(0x00000000), /* Priority 0  */
	UINT32_C(0x00000000), /* Priority -1  */
	UINT32_C(0x00010004), /* Priority -2  */
	UINT32_C(0x00010004), /* Priority -3  */
	UINT32_C(0x00010004), /* Priority -4  */
	UINT32_C(0x00010004), /* Priority -5  */
	UINT32_C(0x00010024), /* Priority -6  */
	UINT32_C(0x00010024), /* Priority -7  */
};

const uint32_t _kernel_prc2_ipm_mask_table[8]={
	UINT32_C(0x00000000), /* Priority 0  */
	UINT32_C(0x00000000), /* Priority -1  */
	UINT32_C(0x00010004), /* Priority -2  */
	UINT32_C(0x00010004), /* Priority -3  */
	UINT32_C(0x00010004), /* Priority -4  */
	UINT32_C(0x00010004), /* Priority -5  */
	UINT32_C(0x00010024), /* Priority -6  */
	UINT32_C(0x00010024), /* Priority -7  */
};

const uint32_t _kernel_prc3_ipm_mask_table[8]={
	UINT32_C(0x00000000), /* Priority 0  */
	UINT32_C(0x00000000), /* Priority -1  */
	UINT32_C(0x00010004), /* Priority -2  */
	UINT32_C(0x00010004), /* Priority -3  */
	UINT32_C(0x00010004), /* Priority -4  */
	UINT32_C(0x00010004), /* Priority -5  */
	UINT32_C(0x00010024), /* Priority -6  */
	UINT32_C(0x00010024), /* Priority -7  */
};

const uint32_t _kernel_prc4_ipm_mask_table[8]={
	UINT32_C(0x00000000), /* Priority 0  */
	UINT32_C(0x00000000), /* Priority -1  */
	UINT32_C(0x00010004), /* Priority -2  */
	UINT32_C(0x00010004), /* Priority -3  */
	UINT32_C(0x00010004), /* Priority -4  */
	UINT32_C(0x00010004), /* Priority -5  */
	UINT32_C(0x00010024), /* Priority -6  */
	UINT32_C(0x00010024), /* Priority -7  */
};

const uint32_t* const _kernel_p_ipm_mask_table[TNUM_PRCID] = {
	_kernel_prc1_ipm_mask_table,
	_kernel_prc2_ipm_mask_table,
	_kernel_prc3_ipm_mask_table,
	_kernel_prc4_ipm_mask_table
};

const FP _kernel_prc1_inh_table[TNUM_INH] = {
	(FP)(_kernel_default_int_handler), /* 0x10000 */
	(FP)(_kernel_default_int_handler), /* 0x10001 */
	(FP)(sio_handler), /* 0x10002 */
	(FP)(_kernel_default_int_handler), /* 0x10003 */
	(FP)(_kernel_default_int_handler), /* 0x10004 */
	(FP)(target_timer_handler), /* 0x10005 */
	(FP)(_kernel_default_int_handler), /* 0x10006 */
	(FP)(_kernel_default_int_handler), /* 0x10007 */
	(FP)(_kernel_default_int_handler), /* 0x10008 */
	(FP)(_kernel_default_int_handler), /* 0x10009 */
	(FP)(_kernel_default_int_handler), /* 0x1000a */
	(FP)(_kernel_default_int_handler), /* 0x1000b */
	(FP)(_kernel_default_int_handler), /* 0x1000c */
	(FP)(_kernel_default_int_handler), /* 0x1000d */
	(FP)(_kernel_default_int_handler), /* 0x1000e */
	(FP)(_kernel_default_int_handler), /* 0x1000f */
	(FP)(_kernel_ipi_handler), /* 0x10010 */
	(FP)(_kernel_default_int_handler), /* 0x10011 */
	(FP)(_kernel_default_int_handler), /* 0x10012 */
	(FP)(_kernel_default_int_handler), /* 0x10013 */
	(FP)(_kernel_default_int_handler), /* 0x10014 */
	(FP)(_kernel_default_int_handler), /* 0x10015 */
	(FP)(_kernel_default_int_handler), /* 0x10016 */
	(FP)(_kernel_default_int_handler), /* 0x10017 */
	(FP)(_kernel_default_int_handler), /* 0x10018 */
	(FP)(_kernel_default_int_handler), /* 0x10019 */
	(FP)(_kernel_default_int_handler), /* 0x1001a */
	(FP)(_kernel_default_int_handler), /* 0x1001b */
	(FP)(_kernel_default_int_handler), /* 0x1001c */
	(FP)(_kernel_default_int_handler), /* 0x1001d */
	(FP)(_kernel_default_int_handler), /* 0x1001e */
	(FP)(_kernel_default_int_handler), /* 0x1001f */
};

const FP _kernel_prc2_inh_table[TNUM_INH] = {
	(FP)(_kernel_default_int_handler), /* 0x20000 */
	(FP)(_kernel_default_int_handler), /* 0x20001 */
	(FP)(sio_handler), /* 0x20002 */
	(FP)(_kernel_default_int_handler), /* 0x20003 */
	(FP)(_kernel_default_int_handler), /* 0x20004 */
	(FP)(target_timer_handler), /* 0x20005 */
	(FP)(_kernel_default_int_handler), /* 0x20006 */
	(FP)(_kernel_default_int_handler), /* 0x20007 */
	(FP)(_kernel_default_int_handler), /* 0x20008 */
	(FP)(_kernel_default_int_handler), /* 0x20009 */
	(FP)(_kernel_default_int_handler), /* 0x2000a */
	(FP)(_kernel_default_int_handler), /* 0x2000b */
	(FP)(_kernel_default_int_handler), /* 0x2000c */
	(FP)(_kernel_default_int_handler), /* 0x2000d */
	(FP)(_kernel_default_int_handler), /* 0x2000e */
	(FP)(_kernel_default_int_handler), /* 0x2000f */
	(FP)(_kernel_ipi_handler), /* 0x20010 */
	(FP)(_kernel_default_int_handler), /* 0x20011 */
	(FP)(_kernel_default_int_handler), /* 0x20012 */
	(FP)(_kernel_default_int_handler), /* 0x20013 */
	(FP)(_kernel_default_int_handler), /* 0x20014 */
	(FP)(_kernel_default_int_handler), /* 0x20015 */
	(FP)(_kernel_default_int_handler), /* 0x20016 */
	(FP)(_kernel_default_int_handler), /* 0x20017 */
	(FP)(_kernel_default_int_handler), /* 0x20018 */
	(FP)(_kernel_default_int_handler), /* 0x20019 */
	(FP)(_kernel_default_int_handler), /* 0x2001a */
	(FP)(_kernel_default_int_handler), /* 0x2001b */
	(FP)(_kernel_default_int_handler), /* 0x2001c */
	(FP)(_kernel_default_int_handler), /* 0x2001d */
	(FP)(_kernel_default_int_handler), /* 0x2001e */
	(FP)(_kernel_default_int_handler), /* 0x2001f */
};

const FP _kernel_prc3_inh_table[TNUM_INH] = {
	(FP)(_kernel_default_int_handler), /* 0x30000 */
	(FP)(_kernel_default_int_handler), /* 0x30001 */
	(FP)(sio_handler), /* 0x30002 */
	(FP)(_kernel_default_int_handler), /* 0x30003 */
	(FP)(_kernel_default_int_handler), /* 0x30004 */
	(FP)(target_timer_handler), /* 0x30005 */
	(FP)(_kernel_default_int_handler), /* 0x30006 */
	(FP)(_kernel_default_int_handler), /* 0x30007 */
	(FP)(_kernel_default_int_handler), /* 0x30008 */
	(FP)(_kernel_default_int_handler), /* 0x30009 */
	(FP)(_kernel_default_int_handler), /* 0x3000a */
	(FP)(_kernel_default_int_handler), /* 0x3000b */
	(FP)(_kernel_default_int_handler), /* 0x3000c */
	(FP)(_kernel_default_int_handler), /* 0x3000d */
	(FP)(_kernel_default_int_handler), /* 0x3000e */
	(FP)(_kernel_default_int_handler), /* 0x3000f */
	(FP)(_kernel_ipi_handler), /* 0x30010 */
	(FP)(_kernel_default_int_handler), /* 0x30011 */
	(FP)(_kernel_default_int_handler), /* 0x30012 */
	(FP)(_kernel_default_int_handler), /* 0x30013 */
	(FP)(_kernel_default_int_handler), /* 0x30014 */
	(FP)(_kernel_default_int_handler), /* 0x30015 */
	(FP)(_kernel_default_int_handler), /* 0x30016 */
	(FP)(_kernel_default_int_handler), /* 0x30017 */
	(FP)(_kernel_default_int_handler), /* 0x30018 */
	(FP)(_kernel_default_int_handler), /* 0x30019 */
	(FP)(_kernel_default_int_handler), /* 0x3001a */
	(FP)(_kernel_default_int_handler), /* 0x3001b */
	(FP)(_kernel_default_int_handler), /* 0x3001c */
	(FP)(_kernel_default_int_handler), /* 0x3001d */
	(FP)(_kernel_default_int_handler), /* 0x3001e */
	(FP)(_kernel_default_int_handler), /* 0x3001f */
};

const FP _kernel_prc4_inh_table[TNUM_INH] = {
	(FP)(_kernel_default_int_handler), /* 0x40000 */
	(FP)(_kernel_default_int_handler), /* 0x40001 */
	(FP)(sio_handler), /* 0x40002 */
	(FP)(_kernel_default_int_handler), /* 0x40003 */
	(FP)(_kernel_default_int_handler), /* 0x40004 */
	(FP)(target_timer_handler), /* 0x40005 */
	(FP)(_kernel_default_int_handler), /* 0x40006 */
	(FP)(_kernel_default_int_handler), /* 0x40007 */
	(FP)(_kernel_default_int_handler), /* 0x40008 */
	(FP)(_kernel_default_int_handler), /* 0x40009 */
	(FP)(_kernel_default_int_handler), /* 0x4000a */
	(FP)(_kernel_default_int_handler), /* 0x4000b */
	(FP)(_kernel_default_int_handler), /* 0x4000c */
	(FP)(_kernel_default_int_handler), /* 0x4000d */
	(FP)(_kernel_default_int_handler), /* 0x4000e */
	(FP)(_kernel_default_int_handler), /* 0x4000f */
	(FP)(_kernel_ipi_handler), /* 0x40010 */
	(FP)(_kernel_default_int_handler), /* 0x40011 */
	(FP)(_kernel_default_int_handler), /* 0x40012 */
	(FP)(_kernel_default_int_handler), /* 0x40013 */
	(FP)(_kernel_default_int_handler), /* 0x40014 */
	(FP)(_kernel_default_int_handler), /* 0x40015 */
	(FP)(_kernel_default_int_handler), /* 0x40016 */
	(FP)(_kernel_default_int_handler), /* 0x40017 */
	(FP)(_kernel_default_int_handler), /* 0x40018 */
	(FP)(_kernel_default_int_handler), /* 0x40019 */
	(FP)(_kernel_default_int_handler), /* 0x4001a */
	(FP)(_kernel_default_int_handler), /* 0x4001b */
	(FP)(_kernel_default_int_handler), /* 0x4001c */
	(FP)(_kernel_default_int_handler), /* 0x4001d */
	(FP)(_kernel_default_int_handler), /* 0x4001e */
	(FP)(_kernel_default_int_handler), /* 0x4001f */
};

const FP* const _kernel_p_inh_table[TNUM_PRCID] = {
	_kernel_prc1_inh_table,
	_kernel_prc2_inh_table,
	_kernel_prc3_inh_table,
	_kernel_prc4_inh_table
};

