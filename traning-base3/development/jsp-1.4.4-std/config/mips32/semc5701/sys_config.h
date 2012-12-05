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

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#include <sys_rename.h>

/*
 *  ����ߥ���ȥ��顦�ܡ��ɰ�¸�Υ��󥯥롼�ɥե�������ɤ߹���
 */
#include <malta_icu.h>	/* ����ߥ���ȥ���ط��ξ����<CPU>���Ϥ��� */
#include <malta_processor.h>	/* NOP_FOR_CP0_HAZARD�ξ����cpu_support.S���Ϥ��� */
#include <malta_system.h>

/*
 *  vgxet_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_VXGET_TIM

/*
 *  ���ꥢ��ݡ��ȿ������
 */
#define TNUM_SIOP	1u	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
#define TNUM_PORT	1u	/* ���ݡ��Ȥ��륷�ꥢ��I/O�ݡ��Ȥο� */


/*
 *  �����ƥॿ�����˴ؤ������
 */
#define	LOGTASK_PORTID	1u	/* �����ƥ������Ϥ��륷�ꥢ��ݡ����ֹ� */

/*
 *  ���������Ԥ��Τ�������
 */
#define	SIL_DLY_TIM1	2865
#define	SIL_DLY_TIM2	398

#ifndef _MACRO_ONLY

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void	sys_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���ROM��˥��ƽФ��Ǽ¸����뤳�Ȥ����ꤷ
 *  �Ƥ��롥
 */
extern void	sys_exit(void);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥��ƽФ��Ǽ¸����뤳
 *  �Ȥ����ꤷ�Ƥ��롥
 */

extern void	sys_putc(char c) throw();

#endif /* _MACRO_ONLY */

/*============================================================================*/
/* �ʲ��ϡ����̥ɥ�����Ȥ�̵���ȼ������ */

/*
 *  ����ߥޥ����ν���� (MIPS32�����Τ⥿�����åȥ����ƥ��¸�ʤΤǡ����������)
 */

/*  MIPS32�����δط� */
/*  �¼�Ū�ʳ��������ϡ���������ߥ���ȥ���ǹԤ����ᡢMIPS32�����˴ؤ��Ƥ�
    ��ǽ��ʬ����Ĥ��롣*/
/*  Malta�Ǥϳ�������ߥ���ȥ�����б����Ƥ��ʤ��� */
#define INIT_CORE_IPM	0

/*
 *  ���ơ������쥸�����ν����
 */
#if STATUS_BEV == 0
#define INIT_SR		(INIT_CORE_IPM)
#else /* STATUS_BEV == 1 */
#define INIT_SR		(SR_BEV | INIT_CORE_IPM)
#endif

/*
 *  ����ե����쥸��������������ѥޥ���
 */
#define INIT_CONFIG_MASK	0x0

/*
 *  ���ꥢ�륳��ȥ���Υܡ��졼�Ȥ����� (ʬ��������ǡ�����[bps]�ǻ���)
 */
#define DEVIDE_RATIO	38400u	/*  38400bps������  */

#endif /* _SYS_CONFIG_H_ */
