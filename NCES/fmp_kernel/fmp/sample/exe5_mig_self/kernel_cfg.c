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

PCB* const _kernel_p_pcb_table[TNUM_PRCID] = {
	&_kernel_prc1_pcb,
	&_kernel_prc2_pcb
};

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_LOGTASK1[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_LOGTASK2[COUNT_STK_T(LOGTASK_STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK3[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK1[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc1s_tstack"),nocommon));
static STK_T _kernel_stack_TASK4[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK5[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_TASK6[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));
static STK_T _kernel_stack_MAIN_TASK2[COUNT_STK_T(STACK_SIZE)]  __attribute__((section(".bss._kernel_prc2s_tstack"),nocommon));

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC1), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_PRC2), (logtask_main), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(1), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(2), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK2, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(3), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK3, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(1), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(4), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK4, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(5), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK5, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(6), (task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK6, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(2), (main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK2, (TA_NULL), (NULL), 2, (uint_t)(0x0000000f) }
};

TCB _kernel_tcb_LOGTASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_LOGTASK2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK2	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK3	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK1	__attribute__((section(".bss._kernel_prc1s_tskcb"),nocommon));
TCB _kernel_tcb_TASK4	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK5	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_TASK6	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));
TCB _kernel_tcb_MAIN_TASK2	__attribute__((section(".bss._kernel_prc2s_tskcb"),nocommon));


TCB* const _kernel_p_tcb_table[TNUM_TSKID] ={
	&_kernel_tcb_LOGTASK1,
	&_kernel_tcb_LOGTASK2,
	&_kernel_tcb_TASK1,
	&_kernel_tcb_TASK2,
	&_kernel_tcb_TASK3,
	&_kernel_tcb_MAIN_TASK1,
	&_kernel_tcb_TASK4,
	&_kernel_tcb_TASK5,
	&_kernel_tcb_TASK6,
	&_kernel_tcb_MAIN_TASK2
};

const ID _kernel_torder_table[TNUM_TSKID] = {
	LOGTASK1, LOGTASK2, TASK1, TASK2, TASK3, MAIN_TASK1, TASK4, TASK5, TASK6, MAIN_TASK2
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (1), (1) },
	{ (TA_TPRI), (&(_kernel_prc2_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc2_pcb.obj_lock)), (1), (1) }
};

SEMCB _kernel_semcb_SERIAL_RCV_SEM1 __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM1 __attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_RCV_SEM2 __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));
SEMCB _kernel_semcb_SERIAL_SND_SEM2 __attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));

SEMCB* const _kernel_p_semcb_table[TNUM_SEMID] = {
	&_kernel_semcb_SERIAL_RCV_SEM1,
	&_kernel_semcb_SERIAL_SND_SEM1,
	&_kernel_semcb_SERIAL_RCV_SEM2,
	&_kernel_semcb_SERIAL_SND_SEM2
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

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
TOPPERS_EMPTY_LABEL(DTQCB* const, _kernel_p_dtqcb_table);

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
	{ (TA_NULL), (intptr_t)(2), (cyclic_handler), (CYC_TIME), (0), 2, (uint_t)(0x0000000f) }
};

CYCCB _kernel_cyccb_CYCHDR1	__attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
CYCCB _kernel_cyccb_CYCHDR2	__attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));

CYCCB* const _kernel_p_cyccb_table[TNUM_CYCID] = {
	&_kernel_cyccb_CYCHDR1,
	&_kernel_cyccb_CYCHDR2
};

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(1), (alarm_handler), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(2), (alarm_handler), 2, (uint_t)(0x0000000f) }
};

ALMCB _kernel_almcb_ALMHDR1	__attribute__((section(".bss._kernel_prc1s_objcb"),nocommon));
ALMCB _kernel_almcb_ALMHDR2	__attribute__((section(".bss._kernel_prc2s_objcb"),nocommon));

ALMCB* const _kernel_p_almcb_table[TNUM_ALMID] = {
	&_kernel_almcb_ALMHDR1,
	&_kernel_almcb_ALMHDR2
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


#define TNUM_INHNO	6
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER_PRC1, 0x10005, target_timer_handler)
INTHDR_ENTRY(INHNO_TIMER_PRC2, 0x20005, target_timer_handler)
INTHDR_ENTRY(INHNO_SIO_PRC1, 0x10002, sio_handler)
INTHDR_ENTRY(INHNO_SIO_PRC2, 0x20002, sio_handler)
INTHDR_ENTRY(INHNO_IPI_PRC1, 0x10010, _kernel_ipi_handler)
INTHDR_ENTRY(INHNO_IPI_PRC2, 0x20010, _kernel_ipi_handler)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC1, target_timer_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_TIMER_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC2, target_timer_handler)), 2, (uint_t)(0x2) },
	{ (INHNO_SIO_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC1, sio_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_SIO_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_SIO_PRC2, sio_handler)), 2, (uint_t)(0x2) },
	{ (INHNO_IPI_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC1, _kernel_ipi_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_IPI_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_PRC2, _kernel_ipi_handler)), 2, (uint_t)(0x2) }
};

#define TNUM_INTNO	6
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER_PRC1), (TA_ENAINT|INTATR_TIMER_PRC1), (INTPRI_TIMER_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_TIMER_PRC2), (TA_ENAINT|INTATR_TIMER_PRC2), (INTPRI_TIMER_PRC2),  2, (uint_t)(0x2)},
	{ (INTNO_SIO_PRC1), (INTATR_SIO_PRC1), (INTPRI_SIO_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_SIO_PRC2), (INTATR_SIO_PRC2), (INTPRI_SIO_PRC2),  2, (uint_t)(0x2)},
	{ (INTNO_IPI_PRC1), (TA_ENAINT), (INTPRI_IPI_PRC1),  1, (uint_t)(0x1)},
	{ (INTNO_IPI_PRC2), (TA_ENAINT), (INTPRI_IPI_PRC2),  2, (uint_t)(0x2)}
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

const SIZE _kernel_istksz_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTKSZ,
	TOPPERS_PRC2_ISTKSZ
};

STK_T *const _kernel_istk_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTK,
	TOPPERS_PRC2_ISTK
};

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt_table[TNUM_PRCID] = {
	TOPPERS_ISTKPT(TOPPERS_PRC1_ISTK, TOPPERS_PRC1_ISTKSZ),
	TOPPERS_ISTKPT(TOPPERS_PRC2_ISTK, TOPPERS_PRC2_ISTKSZ)
};
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_prc1_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc1s_tevt"),nocommon));
TMEVTN   _kernel_prc2_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID] __attribute__((section(".bss._kernel_prc2s_tevt"),nocommon));

TMEVTN* const _kernel_p_tmevt_heap_table[TNUM_PRCID] = {
	  _kernel_prc1_tmevt_heap,
	  _kernel_prc2_tmevt_heap
};

TEVTCB   _kernel_prc1_tevtcb __attribute__((section(".bss._kernel_prc1s_tevt"),nocommon));
TEVTCB   _kernel_prc2_tevtcb __attribute__((section(".bss._kernel_prc2s_tevt"),nocommon));

TEVTCB* const _kernel_p_tevtcb_table[TNUM_PRCID] = {
	  &_kernel_prc1_tevtcb,
	  &_kernel_prc2_tevtcb
};


/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
		_kernel_initialize_semaphore();
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

const FP* const _kernel_p_exch_table[TNUM_PRCID] = {
	_kernel_prc1_exch_table,
	_kernel_prc2_exch_table
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

const PRI* const _kernel_p_inh_ipm_table[TNUM_PRCID] = {
	_kernel_prc1_inh_ipm_table,
	_kernel_prc2_inh_ipm_table
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

const uint32_t* const _kernel_p_ipm_mask_table[TNUM_PRCID] = {
	_kernel_prc1_ipm_mask_table,
	_kernel_prc2_ipm_mask_table
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

const FP* const _kernel_p_inh_table[TNUM_PRCID] = {
	_kernel_prc1_inh_table,
	_kernel_prc2_inh_table
};

