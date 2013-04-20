/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2010 by Embedded and Real-Time Systems Laboratory
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: sample1.c 64 2009-01-13 16:37:04Z ertl-honda $
 */

/* 
 *  ����ץ�ץ����(1)������
 *
 *  FMP�����ͥ�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  �桼�����󥿥ե�������������ĥᥤ�󥿥����ʥ�����ID: MAIN_TASK��ͥ
 *  ����: MAIN_PRIORITY�ˤȡ�3�Ĥ�����¹Ԥ���륿�����ʥ�����ID:
 *  TASK1��TASK3�����ͥ����: MID_PRIORITY�ˤǹ�������롥�ޤ�����ư��
 *  ����2�äμ����ϥ�ɥ�ʼ����ϥ�ɥ�ID: CYCHDR1�ˤ��Ѥ��롥
 *
 *  ����¹Ԥ���륿�����ϡ�task_loop����롼�פ�¹Ԥ����٤ˡ���������
 *  �¹���Ǥ��뤳�Ȥ򤢤�魯��å�������ɽ�����롥
 *
 *  �����ϥ�ɥ�ϡ����Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��
 *  LOW_PRIORITY�ˤΥ�ǥ����塼���ž�����롥�ץ����ε�ưľ��ϡ�
 *  �����ϥ�ɥ����߾��֤ˤʤäƤ��롥
 *
 *  �ᥤ�󥿥����ϡ����ꥢ��I/O�ݡ��Ȥ����ʸ�����Ϥ�Ԥ���ʸ�����Ϥ�
 *  �ԤäƤ���֤ϡ�����¹Ԥ���륿�������¹Ԥ���Ƥ���ˡ����Ϥ��줿
 *  ʸ�����б�����������¹Ԥ��롥���Ϥ��줿ʸ���Ƚ����δط��ϼ����̤ꡥ
 *  Control-C�ޤ���'Q'�����Ϥ����ȡ��ץ�����λ���롥
 *
 *  '1' : �оݥ�������TASK1���ڤ괹����ʽ������ˡ�
 *  '2' : �оݥ�������TASK2���ڤ괹���롥
 *  '3' : �оݥ�������TASK3���ڤ괹���롥
 *  '4' : ���饹1�˽�°���륿��������ꤹ�롥
 *        �оݼ����ϥ�ɥ��CYCHDR1���ڤ��ؤ��롥
 *        �оݥ��顼��ϥ�ɥ��ALMHDR1���ڤ��ؤ��롥
 *  '5' : ���饹2�˽�°���륿��������ꤹ�롥
 *        �оݼ����ϥ�ɥ��CYCHDR2���ڤ��ؤ��롥
 *        �оݥ��顼��ϥ�ɥ��ALMHDR2���ڤ��ؤ��롥
 *  '6' : ���饹3�˽�°���륿��������ꤹ�롥
 *        �оݼ����ϥ�ɥ��CYCHDR3���ڤ��ؤ��롥
 *        �оݥ��顼��ϥ�ɥ��ALMHDR3���ڤ��ؤ��롥
 *  '7' : ���饹4�˽�°���륿��������ꤹ�롥
 *        �оݼ����ϥ�ɥ��CYCHDR4���ڤ��ؤ��롥
 *        �оݥ��顼��ϥ�ɥ��ALMHDR4���ڤ��ؤ��롥
 *  '8' : �ץ��å�1����ꤹ�롥
 *  '9' : �ץ��å�2����ꤹ�롥
 *  '0' : �ץ��å�3����ꤹ�롥
 *  '-' : �ץ��å�4����ꤹ�롥
 *  'a' : �оݥ�������act_tsk�ˤ�굯ư���롥
 *  'A' : �оݥ��������Ф��뵯ư�׵��can_act�ˤ�ꥭ��󥻥뤹�롥
 *  'e' : �оݥ�������ext_tsk��ƤӽФ�������λ�����롥
 *  't' : �оݥ�������ter_tsk�ˤ�궯����λ���롥
 *  '>' : �оݥ�������ͥ���٤�HIGH_PRIORITY�ˤ��롥
 *  '=' : �оݥ�������ͥ���٤�MID_PRIORITY�ˤ��롥
 *  '<' : �оݥ�������ͥ���٤�LOW_PRIORITY�ˤ��롥
 *  'G' : �оݥ�������ͥ���٤�get_pri���ɤ߽Ф���
 *  's' : �оݥ�������slp_tsk��ƤӽФ����������Ԥ��ˤ����롥
 *  'S' : �оݥ�������tslp_tsk(10��)��ƤӽФ����������Ԥ��ˤ����롥
 *  'w' : �оݥ�������wup_tsk�ˤ�굯�����롥
 *  'W' : �оݥ��������Ф��뵯���׵��can_wup�ˤ�ꥭ��󥻥뤹�롥
 *  'l' : �оݥ�������rel_wai�ˤ�궯��Ū���Ԥ�����ˤ��롥
 *  'u' : �оݥ�������sus_tsk�ˤ�궯���Ԥ����֤ˤ��롥
 *  'm' : �оݥ������ζ����Ԥ����֤�rsm_tsk�ˤ�������롥
 *  'd' : �оݥ�������dly_tsk(10��)��ƤӽФ��������ַв��Ԥ��ˤ����롥
 *  'x' : �оݥ��������㳰�ѥ�����0x0001���㳰�������׵᤹�롥
 *  'X' : �оݥ��������㳰�ѥ�����0x0002���㳰�������׵᤹�롥
 *  'y' : �оݥ�������dis_tex��ƤӽФ������������㳰��ػߤ��롥
 *  'Y' : �оݥ�������ena_tex��ƤӽФ������������㳰����Ĥ��롥
 *  'r' : 3�Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY�ˤΥ�
 *        �ǥ����塼���ž�����롥
 *  'c' : �����ϥ�ɥ��ư��Ϥ����롥
 *  'C' : �����ϥ�ɥ��ư����ߤ����롥
 *  'I' : �����ϥ�ɥ�γ��դ��ץ��å����ѹ����롥 
 *  'b' : ���顼��ϥ�ɥ��5�ø�˵�ư����褦ư��Ϥ����롥
 *  'B' : ���顼��ϥ�ɥ��ư����ߤ����롥
 *  'E' : ���顼��ϥ�ɥ�γ��դ��ץ��å����ѹ����롥   
 *  'z' : �оݥ�������CPU�㳰��ȯ��������ʥ�������λ������ˡ�
 *  'Z' : �оݥ�������CPU��å����֤�CPU�㳰��ȯ��������ʥץ�����
 *        ��λ����ˡ�
 *  'i' : �оݥ�������mig_tsk�ˤ����դ��ץ��å����ѹ����롥 
 *  'g' : �оݥ�������mig_tsk��ƤӽФ��������դ��ץ��å����ѹ����롥 
 *  'f' : �оݥ�������mact_tsk�ˤ�굯ư���롥  
 *  'p' : �оݥ�������get_pid��ƤӽФ������ץ��å��ֹ��ɽ�������롥
 *  'V' : get_utm����ǽɾ���ѥ����ƥ�����2���ɤࡥ
 *  'v' : ȯ�Ԥ��������ƥॳ�����ɽ������ʥǥե���ȡˡ�
 *  'q' : ȯ�Ԥ��������ƥॳ�����ɽ�����ʤ���
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

/*
 *  �����ӥ�������Υ��顼�Υ�����
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

/*
 *  ������ID�Υơ��֥�
 */
uint_t const sample_tskid[6] = {
    TASK1,TASK2,TASK3,TASK4,TASK5,TASK6,
};

/*
 *  �����ϥ�ɥ�ID�Υơ��֥�
 */
uint_t const sample_cycid[TNUM_PRCID] = {
    CYCHDR1,
    CYCHDR2,
};

/*
 *  ���顼��ID�Υơ��֥�
 */
uint_t const sample_almid[TNUM_PRCID] = {
    ALMHDR1,
    ALMHDR2,
};

/*
 *  ���ꥢ��ݡ����ֹ�Υơ��֥�
 */
uint_t const serial_port[TNUM_PRCID] = {
    TASK_PORTID_PRC1,
    TASK_PORTID_PRC2,
};

/*
 *  �¹Լ¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
char_t	message[6];


/*
 *  �롼�ײ��
 */
ulong_t	task_loop;		/* ��������ǤΥ롼�ײ�� */

/*
 *  �¹Լ¹Ԥ���륿����
 */
void task(intptr_t exinf)
{
	volatile ulong_t	i;
	int_t		n = 0;
	int_t		tskno = (int_t) (exinf);
	const char	*graph[] = { "|", "  +", "    *", "||", "  ++", "    **" };
	char_t		c;
	  
	while (1) {
		syslog(LOG_NOTICE, "task%d is running (%03d).   %s",
			   tskno, ++n, graph[tskno-1]);
		for (i = 0; i < task_loop; i++);
		c = message[tskno-1];
		message[tskno-1] = 0;
		switch (c) {
		case 'e':
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			SVC_PERROR(ext_tsk());
			assert(0);
		case 's':
			syslog(LOG_INFO, "#%d#slp_tsk()", tskno);
			SVC_PERROR(slp_tsk());
			break;
		case 'S':
			syslog(LOG_INFO, "#%d#tslp_tsk(10000)", tskno);
			SVC_PERROR(tslp_tsk(10000));
			break;
		case 'd':
			syslog(LOG_INFO, "#%d#dly_tsk(10000)", tskno);
			SVC_PERROR(dly_tsk(10000));
			break;
		default:
			break;
		}
	}
}

/*
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void cyclic_handler(intptr_t exinf)
{
	ID		prcid = exinf;

	syslog(LOG_NOTICE, "cyclic_handler %d start!", exinf);
	SVC_PERROR(imrot_rdq(HIGH_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(MID_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(LOW_PRIORITY, prcid));
}

/*
 *  ���顼��ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void alarm_handler(intptr_t exinf)
{
	ID		prcid = exinf;

	syslog(LOG_NOTICE, "alarm_handler %d start!", exinf);
	SVC_PERROR(imrot_rdq(HIGH_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(MID_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(LOW_PRIORITY, prcid));
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(intptr_t exinf)
{
	char_t	c;
	ER_UINT	ercd;
	PRI		tskpri;
	ID		prcid = exinf;
	ID		tskid = sample_tskid[(exinf - 1) * 3 ];
	int_t	        tskno = (exinf-1) * 3 + 1;
	ID		cycid = sample_cycid[(int_t)exinf-1];
	ID		almid = sample_almid[(int_t)exinf-1];
	bool_t  update_select = true;
//	uint_t  tme_select    = exinf;
	uint_t  prc_select    = exinf;
	uint32_t server_req;

#ifndef TASK_LOOP
	volatile ulong_t	i;
	SYSTIM	stime1, stime2;
#endif /* TASK_LOOP */
#ifdef G_SYSLOG
	uint_t e;
#endif /* G_SYSLOG */

	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int_t) exinf);

	/*
	 *  ���ꥢ��ݡ��Ȥν����
	 *
	 *  �����ƥ����������Ʊ�����ꥢ��ݡ��Ȥ�Ȥ����ʤɡ����ꥢ��
	 *  �ݡ��Ȥ������ץ�Ѥߤξ��ˤϤ�����E_OBJ���顼�ˤʤ뤬���پ��
	 *  �ʤ���
	 */
	ercd = serial_opn_por(((int_t)serial_port[exinf-1]));
	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
									itron_strerror(ercd), SERCD(ercd));
	}
	SVC_PERROR(serial_ctl_por(serial_port[exinf-1],
							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*
	 *  �롼�ײ��������
	 *
	 *  TASK_LOOP���ޥ����������Ƥ����硤¬�ꤻ���ˡ�TASK_LOOP����
	 *  �����줿�ͤ򡤥�������ǤΥ롼�ײ���Ȥ��롥
	 *
	 *  MEASURE_TWICE���ޥ����������Ƥ����硤1���ܤ�¬���̤�Τ�
	 *  �ơ�2���ܤ�¬���̤�Ȥ���1���ܤ�¬���Ĺ��λ��֤��Ф뤿�ᡥ
	 */
#ifdef TASK_LOOP
	task_loop = TASK_LOOP;
#else /* TASK_LOOP */

#ifdef MEASURE_TWICE
	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
#endif /* MEASURE_TWICE */

	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
	task_loop = LOOP_REF * 400UL / (stime2 - stime1);
#endif /* TASK_LOOP */

	/*
	 *  �������ε�ư
	 */
	SVC_PERROR(act_tsk(tskid));

	/*
 	 *  �ᥤ��롼��
	 */
	do {
		if (update_select) {
			prcid = prc_select;
			cycid = sample_cycid[prcid-1];
			almid = sample_almid[prcid-1];
			update_select = false;
			syslog(LOG_INFO, "select tskno 0x%x", tskno);
			syslog(LOG_INFO, "select cycid %d", cycid);
			syslog(LOG_INFO, "select almid %d", almid);
			syslog(LOG_INFO, "select processor %d", prcid);
		}
		
		SVC_PERROR(serial_rea_dat(serial_port[exinf-1], &c, 1));
		
		switch (c) {
		case 'e':
		case 's':
		case 'S':
		case 'd':
			message[tskno - 1] = c;
			break;
		case '1':
			tskno = 1;
                        tskid = TASK1;
			update_select = true;
			break;
		case '2':
			tskno = 2;
                        tskid = TASK2;
			update_select = true;
			break;
		case '3':
			tskno = 3;
                        tskid = TASK3;
			update_select = true;
			break;
		case '4':
			tskno = 4;
                        tskid = TASK4;
			update_select = true;
			break;
		case '5':
			tskno = 5;
                        tskid = TASK5;
			update_select = true;
			break;
		case '6':
			tskno = 6;
                        tskid = TASK6;
			update_select = true;
			break;
		case 'a':
			syslog(LOG_INFO, "#act_tsk(0x%x)", tskno);
			SVC_PERROR(act_tsk(tskid));
			break;
		case 'A':
			syslog(LOG_INFO, "#can_act(0x%x)", tskno);
			SVC_PERROR(ercd = can_act(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_act(0x%x) returns %d", tskno, ercd);
			}
			break;
		case '>':
			syslog(LOG_INFO, "#chg_pri(0x%x, HIGH_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, HIGH_PRIORITY));
			break;
		case '=':
			syslog(LOG_INFO, "#chg_pri(0x%x, MID_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, MID_PRIORITY));
			break;
		case '<':
			syslog(LOG_INFO, "#chg_pri(0x%x, LOW_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, LOW_PRIORITY));
			break;
		case 'G':
			syslog(LOG_INFO, "#get_pri(0x%x, &tskpri)", tskno);
			SVC_PERROR(ercd = get_pri(tskid, &tskpri));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "priority of task 0x%x is %d", tskno, tskpri);
			}
			break;
		case 'w':
			syslog(LOG_INFO, "#wup_tsk(0x%x)", tskno);
			SVC_PERROR(wup_tsk(tskid));
			break;
		case 'W':
			syslog(LOG_INFO, "#can_wup(0x%x)", tskno);
			SVC_PERROR(ercd = can_wup(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_wup(0x%x) returns %d", tskno, ercd);
			}
			break;
		case 'c':
			syslog(LOG_INFO, "#sta_cyc(%d)", cycid);
			SVC_PERROR(sta_cyc(cycid));
			break;
		case 'C':
			syslog(LOG_INFO, "#stp_cyc(%d)", cycid);
			SVC_PERROR(stp_cyc(cycid));
			break;
		case 'b':
			syslog(LOG_INFO, "#sta_alm(%d, %d)", almid, ALM_TIME);
			SVC_PERROR(sta_alm(almid, ALM_TIME));
			break;
		case 'B':
			syslog(LOG_INFO, "#stp_alm(%d)", almid);
			SVC_PERROR(stp_alm(almid));
			break;
		default:
			break;
		}
	} while (c != '\003' && c != 'Q');

	syslog(LOG_NOTICE, "Sample program ends.");
	SVC_PERROR(ext_ker());
	assert(0);
}
