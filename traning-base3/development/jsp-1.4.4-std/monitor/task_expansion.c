/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003 by Ryosuke Takeuchi
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
 *  @(#) $Id: task_expansion.c,v 1.4 2005/12/04 11:50:20 roi Exp $
 */

/*
 *	������������ĥ��ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "wait.h"
#include "time_event.h"
#include "semaphore.h"
#include "dataqueue.h"
#include "task_expansion.h"
#include "kernel_id.h"

#define	TS_WAIT_MASK	(TS_WAIT_SLEEP | TS_WAIT_WOBJ | TS_WAIT_WOBJCB)

/*
 *  ����ƥ������椫��ζ����Ԥ����֤ؤΰܹ�
 */
SYSCALL ER
isus_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(tstat)) {
		/*
		 *  �¹ԤǤ�����֤��鶯���Ԥ����֤ؤ�����
		 */
		tcb->tstat = TS_SUSPENDED;
		if (make_non_runnable(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (TSTAT_SUSPENDED(tstat)) {
		ercd = E_QOVR;
	}
	else {
		/*
		 *  �Ԥ����֤�������Ԥ����֤ؤ�����
		 */
		tcb->tstat |= TS_SUSPENDED;
		ercd = E_OK;
	}
	i_unlock_cpu();

    exit:
	return(ercd);
}

/*
 *  ���������ֻ��ȡʴʰ��ǡ�
 */
SYSCALL ER
ref_tst(ID tskid, T_RTST *pk_rtst)
{
	TCB	*tcb;
	UB	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	pk_rtst->tskwait  = 0;
	pk_rtst->tskpri   = EXT_TSKPRI(tcb->priority);
	pk_rtst->inistk   = (VP)tcb->tinib->stk;
	pk_rtst->inistksz = tcb->tinib->stksz;

	tstat = tcb->tstat;
	if (TSTAT_RUNNABLE(tstat)) {
		if (tcb == runtsk) {
			pk_rtst->tskstat = TTS_RUN;
		}
		else {
			pk_rtst->tskstat = TTS_RDY;
		}
	}
	else if (TSTAT_WAITING(tstat)) {
		if (TSTAT_SUSPENDED(tstat)) {
			pk_rtst->tskstat = TTS_WAS;
		}
		else {
			pk_rtst->tskstat = TTS_WAI;
		}
		if (!(tstat & TS_WAIT_MASK)) {
			pk_rtst->tskwait = TTW_DLY;
		}
		else if ((tstat & TS_WAIT_MASK) == TS_WAIT_SLEEP) {
			pk_rtst->tskwait = TTW_SLP;
		}
		else if ((tstat & TS_WAIT_MASK) == TS_WAIT_WOBJ) {
			pk_rtst->tskwait = TTW_RDTQ;
		}
		else {
			pk_rtst->tskwait = TTW_OTHR;
		}
	}
	else if (TSTAT_SUSPENDED(tstat)) {
		pk_rtst->tskstat = TTS_SUS;
	}
	else {
		pk_rtst->tskstat = TTS_DMT;
	}
	if (pk_rtst->tskstat == TTS_DMT)
		pk_rtst->tskpc = (FP)tcb->tinib->task;
	else
		pk_rtst->tskpc = (FP)tcb->tskctxb.pc;
	pk_rtst->tsksp   = (VP)tcb->tskctxb.sp;
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	return(ercd);
}

/*
 *  ���ޥե�ID�κ����͡�kernel_cfg.c��
 */
extern const ID tmax_semid;

/*
 *  ���ޥե������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern SEMCB semcb_table[];

/*
 *  ���ޥե�ID���饻�ޥե������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SEM(semid)	((UINT)((semid) - TMIN_SEMID))
#define get_semcb(semid)	(&(semcb_table[INDEX_SEM(semid)]))

/*
 *  ���ޥե��ξ��ֻ���
 */
SYSCALL ER
ref_sem(ID semid, T_RSEM *pk_rsem)
{
	SEMCB	*semcb;
	QUEUE   *queue;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_SEMID(semid);
	semcb = get_semcb(semid);

	t_lock_cpu();
	queue = &(semcb->wait_queue);
	if (queue->next == queue) {
		pk_rsem->wtskid = 0;
	}
	else{
		pk_rsem->wtskid = TSKID((TCB *)queue->next);
	}
	pk_rsem->semcnt = semcb->semcnt;
	ercd = E_OK;
	t_unlock_cpu();

    exit:
	return(ercd);
}

#ifdef NEED_REFDTQ
/*
 *  �ǡ������塼ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_dtqid;

/*
 *  �ǡ������塼�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern DTQCB	dtqcb_table[];

/*
 *  �ǡ������塼ID����ǡ������塼�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_DTQ(dtqid)	((UINT)((dtqid) - TMIN_DTQID))
#define get_dtqcb(dtqid)	(&(dtqcb_table[INDEX_DTQ(dtqid)]))

/*
 *  �ǡ������塼�ξ��ֻ���
 */
SYSCALL ER
ref_dtq(ID dtqid, T_RDTQ *pk_rdtq)
{
	DTQCB	*dtqcb;
	QUEUE   *queue;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_DTQID(dtqid);
	dtqcb = get_dtqcb(dtqid);

	t_lock_cpu();
	pk_rdtq->sdtqcnt = dtqcb->count;
	queue = &(dtqcb->swait_queue);
	if(queue->next == queue)
		pk_rdtq->stskid = 0;
	else
		pk_rdtq->stskid = TSKID((TCB *)queue->next);
	queue = &(dtqcb->rwait_queue);
	if(queue->next == queue)
		pk_rdtq->rtskid = 0;
	else
		pk_rdtq->rtskid = TSKID((TCB *)queue->next);
	t_unlock_cpu();
	ercd = E_OK;

    exit:
	return(ercd);
}
#endif	/* NEED_REFDTQ */

/*
 *  ���������֤Υ��󥰳�Ǽ�ΰ�
 */

static T_TLOG tsk_log[MAX_TASK_LOG+1];
static ID     check_tskid;
static SYSTIM check_time;
static SYSTIM pervious_time;

/*
 *  �����ƥ���ּ��Ф��ؿ�
 *  �������Ǥ���ѤǤ������̲��Ǥ���褦��
 *  ����饤��ؿ��Ȥ��롥
 */
Inline SYSTIM get_systime(void)
{
	return systim_offset + next_time;
}

/*
 *  �������¹��ΰ�����ؿ�
 *  ���δؿ���dispatch�Υ�������������ޤ��ϡ������ɥ����
 *  �������CPU��å����֤ǸƤӽФ���
 */
#include "hw_timer.h"

void iana_tsk(void)
{
	T_TLOG  *t;
	SYSTIM  time;
#if TIC_DENO != 1
	INT     subtime;
#endif /* TIC_DENO != 1 */
	CLOCK   clock;
	BOOL    ireq;

	/*
	 * ���֤μ��Ф��ϥ���ƥ�������Ǥ�Ԥ���Τ�
	 * vxget_tim��Ʊ���ε��Ҥ򤳤��ˤ�����
	 */
#if TIC_DENO != 1
	subtime = (INT) next_subtime;
#endif /* TIC_DENO != 1 */
	clock = hw_timer_get_current();
	ireq = hw_timer_fetch_interrupt();

	time = get_systime() * ANA_STIC;
#if TIC_DENO != 1
	time += subtime * ANA_STIC / TIC_DENO;
#endif /* TIC_DENO != 1 */
	if (!(ireq) || clock >= (TO_CLOCK(TIC_NUME, TIC_DENO)
					- GET_TOLERANCE)) {
		time -= TIC_NUME * ANA_STIC / TIC_DENO;
	}
	time += clock * ANA_STIC / TIMER_CLOCK;

	if(check_tskid < 0)
		t = &tsk_log[0];
	else if(check_tskid < MAX_TASK_LOG)
		t = &tsk_log[check_tskid];
	else
		t = &tsk_log[MAX_TASK_LOG];
	t->runcount++;
	t->runtimes += time - check_time;

	if(runtsk)
		check_tskid = TSKID(runtsk);
	else
		check_tskid = 0;
	check_time = time;
}

/*
 *  �����������ּ��Ф��ؿ�
 */
INT get_tsklog(T_TPRM * pprm)
{
	INT no;
	INT num_item=0;

	get_tim(&pprm->currtime);
	t_lock_cpu();
	pprm->pervtime = pervious_time;
	pervious_time  = pprm->currtime;
	for(no = 0 ; no <= tmax_tskid && no <= MAX_TASK_LOG ; no++){
		if(no < NUM_LDSP){
			pprm->tlog[no] = tsk_log[no];
			num_item = no;
		}
		else{
			pprm->tlog[NUM_LDSP-1].runcount += tsk_log[no].runcount;
			pprm->tlog[NUM_LDSP-1].runtimes += tsk_log[no].runtimes;
			num_item = NUM_LDSP-1;
		}
		tsk_log[no].runcount = 0;
		tsk_log[no].runtimes = 0;
	}
	t_unlock_cpu();
	return num_item;
}


/*
 *  �ǥХ������ݡ��ȤΥ��������׵�Ƚ���ѥǡ����ΰ�
 */

static T_PCHK port_log[NUM_PCHK];

/*
 *  �ǥХ�������Ԥ����ɤ�����Ƚ��
 */
static UINT check_device_log(UW address, UW size)
{
	int    i;
	T_PCHK *p;

	for(i = 0 ; i < NUM_PCHK ; i++){
		p = &port_log[i];
		if(p->portaddress >= address && p->portaddress < (address+size) && p->logtype)
			return (UINT)p->logtype;
	}
	return 0;
}

/*
 *  �ǥХ������ݡ��ȤΥ�Ƚ��ǡ����μ��Ф�
 */
T_PCHK *get_device_log(UW no){
	if(no < NUM_PCHK)
		return &port_log[no];
	else
		return 0;
}

/*
 *  �ǥХ����ɤ߽Ф�ɽ��Ƚ��ȥ������ȴؿ�
 */
void
ana_rdv(UW address, UW data, INT size)
{
	SYSTIM time = get_systime();
	ID     id;
	UINT   logtype = check_device_log(address, size);

	if(logtype == 0)
		return;
	if(sense_context() || !runtsk)
		syslog_3(logtype, "Device Read  time=%09d interrupt port=%08x data=0x%x", time, address, data);
	else{
		id = TSKID(runtsk);
		switch(size){
		case 4:
			syslog_4(logtype, "Device Read  time=%09d task=%04d port=%08x data=%08x", time, id, address, data);
			break;
		case 2:
			syslog_4(logtype, "Device Read  time=%09d task=%04d port=%08x data=%04x", time, id, address, data);
			break;
		default:
			syslog_4(logtype, "Device Read  time=%09d task=%04d port=%08x data=%02x", time, id, address, data);
			break;
		}
	}
}

/*
 *  �ǥХ����񤭹���ɽ��Ƚ��ȥ������ȴؿ�
 */
void
ana_wdv(UW address, UW data, INT size)
{
	SYSTIM time = get_systime();
	ID     id;
	UINT   logtype = check_device_log(address, size);

	if(logtype == 0)
		return;
	if(sense_context() || !runtsk)
		syslog_3(logtype, "Device Write  time=%09d interrupt port=%08x data=0x%x", time, address, data);
	else{
		id = TSKID(runtsk);
		switch(size){
		case 4:
			syslog_4(logtype, "Device Write time=%09d task=%04d port=%08x data=%08x", time, id, address, data);
			break;
		case 2:
			syslog_4(logtype, "Device Write time=%09d task=%04d port=%08x data=%04x", time, id, address, data);
			break;
		default:
			syslog_4(logtype, "Device Write time=%09d task=%04d port=%08x data=%02x", time, id, address, data);
			break;
		}
	}
}

