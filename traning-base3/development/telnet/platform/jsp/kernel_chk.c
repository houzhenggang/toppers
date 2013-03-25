#include "jsp_kernel.h"
#include "logtask.h"
#include "timer.h"

#define OBJECT(x,y) __asm("d" #x "," #y "@");
#define MEMBER(x,y) __asm("s" #x "::" #y ",(%0),(%1)@" ::\
     "i"(sizeof(((struct x *)0)->y)), "i"(&((struct x *)0)->y));
#define VAR(x) __asm("s" #x ",(%0),(0)@" :: "i"(sizeof(x)));
#define EVAR(x,y) __asm("s" #y ",(%0),(0)@" :: "i"(sizeof(x)));
#define SVAR(x) __asm("s" #x ",(%0),(0)@" :: "i"(sizeof(x[0])));
#define DEFS(x) __asm("s" #x ",(%0),(0)@" :: "i"((unsigned long)x));

#include "queue.h"

#include "task.h"
#include "semaphore.h"
#include "eventflag.h"
#include "dataqueue.h"
#include "mailbox.h"
#include "mempfix.h"
#include "cyclic.h"
#include "../kernel/exception.h"
#include "interrupt.h"
#include "wait.h"

void checker_function(void)
{
	DEFS(TMAX_TPRI);
	DEFS(TMIN_TPRI);

	DEFS(TMAX_MPRI);
	DEFS(TMIN_MPRI);

	DEFS(TMAX_RELTIM);

	MEMBER(queue,next);
	MEMBER(queue,prev);


		/* task */

	OBJECT(task_6,ETHER_INPUT_TASK);
	OBJECT(task_5,ETHER_OUTPUT_TASK);
	OBJECT(task_9,LOGTASK);
	OBJECT(task_1,MAIN_TASK);
	OBJECT(task_3,MONTASK);
	OBJECT(task_4,NET_TIMER_TASK);
	OBJECT(task_7,TCP_OUTPUT_TASK);
	OBJECT(task_2,TCP_TELNET_SRV_TASK);
	OBJECT(task_8,UDP_OUTPUT_TASK);
	EVAR(ID,_kernel_tmax_tskid);
	EVAR(TINIB,_kernel_tinib_table);
	MEMBER(task_initialization_block,tskatr);
	MEMBER(task_initialization_block,exinf);
	MEMBER(task_initialization_block,task);
	MEMBER(task_initialization_block,ipriority);
	MEMBER(task_initialization_block,stksz);
	MEMBER(task_initialization_block,stk);
	MEMBER(task_initialization_block,texatr);
	MEMBER(task_initialization_block,texrtn);


		/* semaphore */

	OBJECT(semaphore_24,RTCSEM);
	OBJECT(semaphore_19,SEMID_FATFS1);
	OBJECT(semaphore_20,SEMID_FATFS2);
	OBJECT(semaphore_21,SEMID_FATFS3);
	OBJECT(semaphore_22,SEMID_FATFS4);
	OBJECT(semaphore_11,SEM_ARP_CACHE_LOCK);
	OBJECT(semaphore_7,SEM_CALL_OUT_LOCK);
	OBJECT(semaphore_8,SEM_CALL_OUT_TIMEOUT);
	OBJECT(semaphore_6,SEM_IF_EMAC_RBUF_READY);
	OBJECT(semaphore_5,SEM_IF_EMAC_SBUF_READY);
	OBJECT(semaphore_12,SEM_IN_ROUTING_TBL);
	OBJECT(semaphore_9,SEM_IP2STR_BUFF_LOCK);
	OBJECT(semaphore_10,SEM_MAC2STR_BUFF_LOCK);
	OBJECT(semaphore_23,SEM_STDFILE);
	OBJECT(semaphore_14,SEM_TCP_CEP);
	OBJECT(semaphore_17,SEM_TCP_CEP_LOCK1);
	OBJECT(semaphore_13,SEM_TCP_POST_OUTPUT);
	OBJECT(semaphore_4,SEM_TCP_TELNET_QUEUE_LOCK);
	OBJECT(semaphore_1,SEM_TCP_TELNET_SRV_NBLK_READY);
	OBJECT(semaphore_2,SEM_TCP_TELNET_SRV_NRCV_READY);
	OBJECT(semaphore_3,SEM_TCP_TELNET_SRV_NSND_READY);
	OBJECT(semaphore_16,SEM_UDP_CEP);
	OBJECT(semaphore_18,SEM_UDP_CEP_LOCK1);
	OBJECT(semaphore_15,SEM_UDP_POST_OUTPUT);
	OBJECT(semaphore_25,SERIAL_RCV_SEM1);
	OBJECT(semaphore_27,SERIAL_RCV_SEM2);
	OBJECT(semaphore_26,SERIAL_SND_SEM1);
	OBJECT(semaphore_28,SERIAL_SND_SEM2);
	EVAR(ID,_kernel_tmax_semid);
	EVAR(SEMINIB,_kernel_seminib_table);
	MEMBER(semaphore_initialization_block,sematr);
	MEMBER(semaphore_initialization_block,isemcnt);
	MEMBER(semaphore_initialization_block,maxsem);


		/* eventflag */

	OBJECT(eventflag_1,FLG_TCP_CEP_EST1);
	OBJECT(eventflag_3,FLG_TCP_CEP_RCV1);
	OBJECT(eventflag_2,FLG_TCP_CEP_SND1);
	EVAR(ID,_kernel_tmax_flgid);
	EVAR(FLGINIB,_kernel_flginib_table);
	MEMBER(eventflag_initialization_block,flgatr);
	MEMBER(eventflag_initialization_block,iflgptn);


		/* dataqueue */

	OBJECT(dataqueue_1,DTQ_ETHER_OUTPUT);
	OBJECT(dataqueue_2,DTQ_UDP_RCVQ1);
	EVAR(ID,_kernel_tmax_dtqid);
	EVAR(DTQINIB,_kernel_dtqinib_table);
	MEMBER(dataqueue_initialization_block,dtqatr);
	MEMBER(dataqueue_initialization_block,dtqcnt);
	MEMBER(dataqueue_initialization_block,dtq);


		/* mailbox */

	EVAR(ID,_kernel_tmax_mbxid);
	EVAR(MBXINIB,_kernel_mbxinib_table);
	MEMBER(mailbox_initialization_block,mbxatr);
	MEMBER(mailbox_initialization_block,maxmpri);


		/* mempfix */

	OBJECT(mempfix_5,MPF_NET_BUF_1024);
	OBJECT(mempfix_2,MPF_NET_BUF_128);
	OBJECT(mempfix_3,MPF_NET_BUF_256);
	OBJECT(mempfix_4,MPF_NET_BUF_512);
	OBJECT(mempfix_1,MPF_NET_BUF_64);
	OBJECT(mempfix_6,MPF_NET_BUF_IF_PDU);
	EVAR(ID,_kernel_tmax_mpfid);
	EVAR(MPFINIB,_kernel_mpfinib_table);
	MEMBER(fixed_memorypool_initialization_block,mpfatr);
	MEMBER(fixed_memorypool_initialization_block,blksz);
	MEMBER(fixed_memorypool_initialization_block,mpf);
	MEMBER(fixed_memorypool_initialization_block,limit);


		/* cyclic */

	OBJECT(cyclic_1,CYCHDR1);
	OBJECT(cyclic_2,NET_TIMER_HANDLER);
	EVAR(ID,_kernel_tmax_cycid);
	EVAR(CYCINIB,_kernel_cycinib_table);
	MEMBER(cyclic_handler_initialization_block,cycatr);
	MEMBER(cyclic_handler_initialization_block,exinf);
	MEMBER(cyclic_handler_initialization_block,cychdr);
	MEMBER(cyclic_handler_initialization_block,cyctim);
	MEMBER(cyclic_handler_initialization_block,cycphs);


		/* interrupt */

	OBJECT(interrupt_0,13);
	OBJECT(interrupt_1,21);
	OBJECT(interrupt_2,24);
	OBJECT(interrupt_3,25);
	OBJECT(interrupt_4,4);
	OBJECT(interrupt_5,INHNO_SIO0);
	OBJECT(interrupt_6,INHNO_SIO1);
	EVAR(ID,_kernel_tnum_inhno);
	EVAR(INHINIB,_kernel_inhinib_table);
	MEMBER(interrupt_handler_initialization_block,inhno);
	MEMBER(interrupt_handler_initialization_block,inhatr);
	MEMBER(interrupt_handler_initialization_block,inthdr);


		/* exception */

	EVAR(ID,_kernel_tnum_excno);
	EVAR(EXCINIB,_kernel_excinib_table);
	MEMBER(cpu_exception_handler_initialization_block,excno);
	MEMBER(cpu_exception_handler_initialization_block,excatr);
	MEMBER(cpu_exception_handler_initialization_block,exchdr);

}
