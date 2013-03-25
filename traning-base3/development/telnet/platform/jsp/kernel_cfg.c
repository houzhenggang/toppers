/* Configured with [-s tmpfile1 -c -obj -cpu armv4 -system lpc2388 ] */

#include "kernel_cfg.h"
#include "kernel_id.h"

#if TKERNEL_PRVER >= 0x1040
#define CFG_INTHDR_ENTRY(inthdr) INTHDR_ENTRY(inthdr)
#define CFG_EXCHDR_ENTRY(exchdr) EXCHDR_ENTRY(exchdr)
#define CFG_INT_ENTRY(inthdr) INT_ENTRY(inthdr)
#define CFG_EXC_ENTRY(exchdr) EXC_ENTRY(exchdr)
#else
#error "This configuration file has no compatibility with TOPPERS/JSP rel 1.3 or earlier."
#endif

#ifndef __EMPTY_LABEL
#define __EMPTY_LABEL(x,y) x y[0]
#endif

#if TKERNEL_PRID != 0x0001u /* TOPPERS/JSP */
#error "You can not use this configuration file without TOPPERS/JSP"
#endif

	/* User specified include files*/
#include "config.h"
#include "tinet_id.h"
#include "monitor.h"
#include <tinet_defs.h>
#include <tinet_config.h>
#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/ppp_var.h>
#include <net/ether_var.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>
#include <netinet6/in6.h>
#include <netinet6/ip6_var.h>
#include "if_lpcemac.h"
#include "ff.h"
#include "storagedevice.h"
#include "lpc23xx_rtc.h"
#include "hw_timer.h"
#include "timer.h"
#include "hw_serial.h"
#include "serial.h"
#include "logtask.h"


	/* Object initializer [task] */

#define TNUM_TSKID 9

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static __STK_UNIT __stack_MAIN_TASK[__TCOUNT_STK_UNIT(4096)];
static __STK_UNIT __stack_TCP_TELNET_SRV_TASK[__TCOUNT_STK_UNIT(4096)];
static __STK_UNIT __stack_MONTASK[__TCOUNT_STK_UNIT(2046)];
static __STK_UNIT __stack_NET_TIMER_TASK[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT __stack_ETHER_OUTPUT_TASK[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT __stack_ETHER_INPUT_TASK[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT __stack_TCP_OUTPUT_TASK[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT __stack_UDP_OUTPUT_TASK[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT __stack_LOGTASK[__TCOUNT_STK_UNIT(LOGTASK_STACK_SIZE)];

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{0x00u | 0x02u, (VP_INT)(0), (FP)(main_task), INT_PRIORITY(4), __TROUND_STK_UNIT(4096), __stack_MAIN_TASK, TA_NULL, (FP)(NULL)},
	{0, (VP_INT)(TCP_TELNET_SRV_CEPID), (FP)(tcp_telnet_srv_task), INT_PRIORITY(5), __TROUND_STK_UNIT(4096), __stack_TCP_TELNET_SRV_TASK, TA_NULL, (FP)(NULL)},
	{0x00u | 0x02u, (VP_INT)(( VP_INT ) 1), (FP)(monitor), INT_PRIORITY(3), __TROUND_STK_UNIT(2046), __stack_MONTASK, TA_NULL, (FP)(NULL)},
	{0, (VP_INT)(0), (FP)(net_timer_task), INT_PRIORITY(5), __TROUND_STK_UNIT(1024), __stack_NET_TIMER_TASK, TA_NULL, (FP)(NULL)},
	{0, (VP_INT)(0), (FP)(_tinet_ether_output_task), INT_PRIORITY(5), __TROUND_STK_UNIT(1024), __stack_ETHER_OUTPUT_TASK, TA_NULL, (FP)(NULL)},
	{0x00u | 0x02u, (VP_INT)(0), (FP)(_tinet_ether_input_task), INT_PRIORITY(5), __TROUND_STK_UNIT(1024), __stack_ETHER_INPUT_TASK, TA_NULL, (FP)(NULL)},
	{0, (VP_INT)(0), (FP)(tcp_output_task), INT_PRIORITY(5), __TROUND_STK_UNIT(1024), __stack_TCP_OUTPUT_TASK, TA_NULL, (FP)(NULL)},
	{0, (VP_INT)(0), (FP)(udp_output_task), INT_PRIORITY(5), __TROUND_STK_UNIT(1024), __stack_UDP_OUTPUT_TASK, TA_NULL, (FP)(NULL)},
	{0x00u | 0x02u, (VP_INT)(( VP_INT ) 1), (FP)(logtask), INT_PRIORITY(LOGTASK_PRIORITY), __TROUND_STK_UNIT(LOGTASK_STACK_SIZE), __stack_LOGTASK, TA_NULL, (FP)(NULL)}
};

const ID _kernel_torder_table[TNUM_TSKID] = {1,2,3,4,5,6,7,8,9};

TCB _kernel_tcb_table[TNUM_TSKID];


	/* Object initializer [semaphore] */

#define TNUM_SEMID 28

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{1, 0, 1},
	{1, 0, 1},
	{1, 0, 1},
	{1, 1, 1},
	{1, 5, 5},
	{1, 0, 5},
	{1, 1, 1},
	{1, 0, NUM_NET_CALLOUT},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1},
	{0, 1, 1},
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 1}
};

SEMCB _kernel_semcb_table[TNUM_SEMID];


	/* Object initializer [eventflag] */

#define TNUM_FLGID 3

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

const FLGINIB _kernel_flginib_table[TNUM_FLGID] = {
	{0x00u | 0x00u, TCP_CEP_EVT_CLOSED},
	{0x00u | 0x00u, TCP_CEP_EVT_SWBUF_READY},
	{0x00u | 0x00u, 0}
};

FLGCB _kernel_flgcb_table[TNUM_FLGID];


	/* Object initializer [dataqueue] */

#define TNUM_DTQID 2

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

#if (2) > 0
  static VP_INT __dataqueue_DTQ_ETHER_OUTPUT[2];
#else
  #define __dataqueue_DTQ_ETHER_OUTPUT NULL
#endif
#if (1) > 0
  static VP_INT __dataqueue_DTQ_UDP_RCVQ1[1];
#else
  #define __dataqueue_DTQ_UDP_RCVQ1 NULL
#endif

const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {
	{0, 2, __dataqueue_DTQ_ETHER_OUTPUT},
	{0, 1, __dataqueue_DTQ_UDP_RCVQ1}
};

DTQCB _kernel_dtqcb_table[TNUM_DTQID];


	/* Object initializer [mailbox] */

#define TNUM_MBXID 0

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

__EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
__EMPTY_LABEL(MBXCB, _kernel_mbxcb_table);


	/* Object initializer [mempfix] */

#define TNUM_MPFID 6

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_64[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_64 )) * ((2))];
static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_128[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_128 )) * ((1))];
static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_256[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_256 )) * ((1))];
static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_512[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_512 )) * ((1))];
static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_1024[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_1024 )) * ((1))];
static __MPF_UNIT __fixedsize_memorypool_MPF_NET_BUF_IF_PDU[__TCOUNT_MPF_UNIT(sizeof ( T_NET_BUF_IF_PDU )) * ((3))];

const MPFINIB _kernel_mpfinib_table[TNUM_MPFID] = {
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_64 )), __fixedsize_memorypool_MPF_NET_BUF_64, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_64 + sizeof(__fixedsize_memorypool_MPF_NET_BUF_64))},
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_128 )), __fixedsize_memorypool_MPF_NET_BUF_128, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_128 + sizeof(__fixedsize_memorypool_MPF_NET_BUF_128))},
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_256 )), __fixedsize_memorypool_MPF_NET_BUF_256, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_256 + sizeof(__fixedsize_memorypool_MPF_NET_BUF_256))},
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_512 )), __fixedsize_memorypool_MPF_NET_BUF_512, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_512 + sizeof(__fixedsize_memorypool_MPF_NET_BUF_512))},
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_1024 )), __fixedsize_memorypool_MPF_NET_BUF_1024, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_1024 + sizeof(__fixedsize_memorypool_MPF_NET_BUF_1024))},
	{0, __TROUND_MPF_UNIT(sizeof ( T_NET_BUF_IF_PDU )), __fixedsize_memorypool_MPF_NET_BUF_IF_PDU, (VP)((VB *)__fixedsize_memorypool_MPF_NET_BUF_IF_PDU + sizeof(__fixedsize_memorypool_MPF_NET_BUF_IF_PDU))}
};

MPFCB _kernel_mpfcb_table[TNUM_MPFID];


	/* Object initializer [cyclic] */

#define TNUM_CYCID 2

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{0,0,(FP)(cyclic_handler),500,0},
	{0x00u | 0x02u,0,(FP)(net_timer_handler),NET_TIMER_CYCLE,1}
};

CYCCB _kernel_cyccb_table[TNUM_CYCID];


	/* Object initializer [interrupt] */

#define TNUM_INHNO 7

const UINT _kernel_tnum_inhno = TNUM_INHNO;

CFG_INTHDR_ENTRY(rtc_isr0);
CFG_INTHDR_ENTRY(if_ether_handler);
CFG_INTHDR_ENTRY(mci_isr0);
CFG_INTHDR_ENTRY(dma_isr0);
CFG_INTHDR_ENTRY(timer_handler);
CFG_INTHDR_ENTRY(uart_isr0);
CFG_INTHDR_ENTRY(uart_isr1);

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{13,0,(FP)CFG_INT_ENTRY(rtc_isr0)},
	{21,0,(FP)CFG_INT_ENTRY(if_ether_handler)},
	{24,0,(FP)CFG_INT_ENTRY(mci_isr0)},
	{25,0,(FP)CFG_INT_ENTRY(dma_isr0)},
	{4,0,(FP)CFG_INT_ENTRY(timer_handler)},
	{INHNO_SIO0,0,(FP)CFG_INT_ENTRY(uart_isr0)},
	{INHNO_SIO1,0,(FP)CFG_INT_ENTRY(uart_isr1)}
};


	/* Object initializer [exception] */

#define TNUM_EXCNO 0

const UINT _kernel_tnum_excno = TNUM_EXCNO;

__EMPTY_LABEL(const EXCINIB, _kernel_excinib_table);
	/* Initialization handler */

void
_kernel_call_inirtn(void)
{
	macaddr_init( (VP_INT)(0) );
	application_init( (VP_INT)(0) );
	sdev_init( (VP_INT)(0) );
	stdfile_init( (VP_INT)(0) );
	rtc_init( (VP_INT)(0) );
	mci_init( (VP_INT)(0) );
	dma_init( (VP_INT)(0) );
	timer_initialize( (VP_INT)(0) );
	serial_initialize( (VP_INT)(0) );
}

void
_kernel_call_terrtn(void)
{
	timer_terminate( (VP_INT)(0) );
}

	/* Object initialization routine */

void
_kernel_object_initialize(void)
{
	_kernel_task_initialize();
	_kernel_semaphore_initialize();
	_kernel_eventflag_initialize();
	_kernel_dataqueue_initialize();
	_kernel_mempfix_initialize();
	_kernel_cyclic_initialize();
	_kernel_interrupt_initialize();
}

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID];

	/* Variables for kernel checker */
const UW _checker_magic_number = 0x01234567;

