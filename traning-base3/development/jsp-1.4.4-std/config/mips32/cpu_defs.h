/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN
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
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

/*
 *  �ץ��å��˰�¸���������MIPS32�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥�
 *  ���롼�ɤ������ˡ�t_stddef.h �� itron.h �����󥯥롼�ɤ����Τǡ�
 *  �����˰�¸���Ƥ�褤��
 */

#define MIPS32

/* �����ͥ뵯ư���Υ�å����� */
#define COPYRIGHT_CPU \
"Copyright (C) 2001-2003 by Industrial Technology Institute,\n" \
"                            Miyagi Prefectural Government, JAPAN\n" \
"Copyright (C) 2007-     by Monami Software Limited Partnership, JAPAN\n"

#ifndef _MACRO_ONLY

/*
 *  ����ߡ�CPU�㳰�ϥ�ɥ��ֹ�η�
 */
typedef	UINT	INHNO;			/* ����ߥϥ�ɥ��ֹ� */
typedef	UINT	EXCNO;			/* CPU�㳰�ϥ�ɥ��ֹ� */

/*
 *  ����ߥޥ����η��ȳ���ߥޥ������ѹ�������
 */

/* MIPS32�����γ���ߥޥ����η���� (����ͤϥ����ƥ��¸���˵���) */
typedef	UW	CORE_IPM;

/* ����ߥޥ����η� */
typedef	struct {
	CORE_IPM	core;	/*  MIPS32�����γ���ߥޥ���  */
#if TNUM_ICU_INTNO == 0
#else /* TNUM_ICU_INTNO != 0 */
	ICU_IPM		icu;	/*  ����ߥ���ȥ���γ���ߥޥ���  */
#endif
} IPM;

/* ����ߥޥ�������Ѥδؿ� */
extern ER	chg_ipm(IPM p_ipm) throw();	/* ����ߥޥ������ѹ� */
extern ER	get_ipm(IPM *p_ipm) throw();	/* ����ߥޥ����μ��� */

#endif /* _MACRO_ONLY */

/*
 *  ����ߥ�å����֤�����
 *    MIPS32�Ǥϡ����Ƥγ����ߤ������ͥ������ʤΤǡ�
 *      ����ߥ�å����� = CPU��å�����
 *    �Ȥʤꡢ���Υޥ�������Ƥϡ�ɸ����󶡤���Ƥ����Τ�Ȥ���
 *    (�⤷�����̤�����򤷤褦�Ȥ���ʤ�С������Τ褦�ˤʤ롣)
 */
/*
#define	SIL_PRE_LOC
#define	SIL_LOC_INT()	t_lock_cpu()
#define	SIL_UNL_INT()	t_unlock_cpu()
*/
/*============================================================================*/
/*  ���̥ɥ�����Ȥ�̵�����  */

#ifndef _MACRO_ONLY

/*  ����ߥϥ�ɥ顿����ߥޥ��������ơ��֥��Ѥη�  */
typedef struct {
	FP		inthdr;		/*  ����ߥϥ�ɥ����Ƭ���ɥ쥹  */
	CORE_IPM	intmask;	/*  MIPS32�����γ���ߥޥ���  */
} INT_TABLE;

#endif /* _MACRO_ONLY */

#endif /* _CPU_DEFS_H_ */
