/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2005 by Ryosuke Takeuchi
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
 *  @(#) $Id: task_expansion.h,v 1.3 2007/07/18 17:16:45 roi Exp $
 */

/*
 *	��˥��ѥ������ѳ�ĥ���
 */

#ifndef _TASK_EXPANSION_H_
#define _TASK_EXPANSION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "kernel_debug.h"
#include <t_services.h>

/*
 *  ���������֡ʴʰ��ǡˤΥѥ��åȷ���
 */

typedef struct t_rtst{
	STAT    tskstat;			/* ���������� */
	STAT    tskwait;			/* �Ԥ��װ� */
	PRI     tskpri;				/* �������θ��ߤ�ͥ���� */
	FP      tskpc;				/* �������θ��ߤΥץ���५���� */
	VP      tsksp;				/* �������θ��ߤΥ����å��ݥ��� */
	VP      inistk;				/* �������Υ����å����ɥ쥹 */
	SIZE    inistksz;			/* �������Υ����å������� */
}T_RTST;

#define	TTW_OTHR	0x0040		/* ����¾���Ԥ����� */
					/* TOPPERS�Ԥ�����TTW_SEM,TTW_FLG, TTW_SDTQ */
					/* TTW_MBX, TTW_MPF���Ԥ����ֶ��̤ǤϤʤ� */

/*
 *  ���ޥե����֤Υѥ��åȷ���
 */
typedef struct t_rsem {
	ID      wtskid;				/* ���ޥե����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	UINT    semcnt;				/* ���ޥե��θ��ߤλ񸻿� */
}T_RSEM;

/*
 *  �ǡ������塼���֤Υѥ��åȷ���
 */
typedef struct t_rdtq{
	ID      stskid;				/* �ǡ������塼�������Ԥ��������Ƭ�Υ�������ID�ֹ� */
	ID      rtskid;				/* �ǡ������塼�μ����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	UINT    sdtqcnt;			/* �ǡ������塼�����äƤ���ǡ����ο� */
}T_RDTQ;

/*
 *  �������μ¹Ծ��ֹ�¤�����
 */
#define	MAX_TASK_LOG	8		/* ���������ơ��֥�ο� */
#define	ANA_STIC		10		/* ���֥��å��� */

typedef struct t_tlog{
	INT		runcount;			/* �������μ¹Բ�� */
	SYSTIM	runtimes;			/* �������μ¹Ի���(MS) */
}T_TLOG;

/*
 *  �������Υ�������Ф���¤�����
 */

#define	NUM_LDSP		6		/* ɽ���ѤΥ�������Ф��ΰ�κ���� */

typedef struct t_tprm{
	SYSTIM  pervtime;			/* ���λ��Ȼ��� */
	SYSTIM  currtime;			/* ����λ��Ȼ��� */
	T_TLOG	tlog[NUM_LDSP];		/* ���Ф��������� */
}T_TPRM;

/*
 *  �ǥХ����ݡ���Ƚ��ơ��֥�ι�¤�����
 */

#define	NUM_PCHK		4		/* �ǥХ����ݡ���Ƚ��ơ��֥�Υ����ƥ�� */

typedef struct t_pchk{
	UB		logtype;			/* ��ɽ��Ƚ����� */
	UW		portaddress;		/* �ݡ��ȥ��ɥ쥹 */
}T_PCHK;

/*
 *  �ץ�ȥ��������
 */

extern ER isus_tsk(ID tskid);
extern ER ref_tst(ID tskid, T_RTST *pk_rtst);
extern ER ref_sem(ID semid, T_RSEM *pk_rsem);
extern ER ref_dtq(ID dtqid, T_RDTQ *pk_rdtq);
extern void iana_tsk(void);
extern void ana_rdv(UW address, UW data, INT size);
extern void ana_wdv(UW address, UW data, INT size);
extern INT  get_tsklog(T_TPRM *pprm);
extern T_PCHK *get_device_log(UW no);

#ifdef __cplusplus
}
#endif

#endif /* _TASK_EXPANSION_H_ */

