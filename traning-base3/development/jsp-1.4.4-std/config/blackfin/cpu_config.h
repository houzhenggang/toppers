/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
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
 * 
 *  
 */


/*
 *	�ץ��å���¸�Υ����ͥ�񸻡�BLACKfin�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �����ӥ�����������ޥ�����ɤ߹���
 */
#ifdef __GNUC__
/*
* �����ӥ�����������ϡ�configure������ץȤ������ʤ��Τǡ�gnu�Ķ��Ǥ�����
*/
//#include <api.h>
#elif defined(__ECC__)
/*
* �����ӥ�����������ϡ�IPA���Ԥ��Τǡ�VisualDSP++�Ķ��ǤϤ��٤����򤷤Ƥ���
*/
#include <api.h>
#else
#error "Compiler is not supported"
#endif
/*
 *  BLACKfin��Ϣ�ե�������ɤ߹���
 */
#ifdef __GNUC__
#include "cdef_lpblackfin.h"		/* gnu tool chain */
#elif defined(__ECC__)
#include <cdef_lpblackfin.h>	/* VisualDSP++ */
#else
#error "Compiler is not supported"
#endif

/*
*  ���٥�ȥץ饤����ƥ����. sys_config.h �� device_dispatcher()�ǻȤ���
*/
#ifdef __GNUC__
#define ik_timer 6
#define ik_hardware_err 5
#elif defined(__ECC__)
#else
#error "Compiler is not supported"
#endif

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#include <cpu_rename.h>

/*
*	BLACKfin�Υӥåȥޥå׸�����ǽ��Ȥ�
*   BLACKfin��MSB��������롣
*/
#define	CPU_BITMAP_SEARCH
#define	PRIMAP_BIT(pri)		(0x40000000u >> (pri))


/*
 *  TCB ��Υե�����ɤΥӥå��������
 *
 *  cpu_context.h ��������������쥬��Ȥ��������Ȥΰ�¸���δط��ǡ�
 *  cpu_context.h �ˤ�������ʤ���
 */
#define	TBIT_TCB_TSTAT		8	/* tstat �ե�����ɤΥӥå��� */
#define	TBIT_TCB_PRIORITY	8	/* priority �ե�����ɤΥӥå��� */


/*
*	BLACKfin��IMASK�ؤ�����ѥ�����
*
*/
#define IMASK_LOCK   0xc01f
#define IMASK_UNLOCK 0xffff

#ifndef _MACRO_ONLY
/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
/*
 *  ��ǥ����塼�������Τ���Υӥåȥޥåץ������ؿ�
 *
 *  �ӥåȥޥåפβ���16�ӥåȤ���Ѥ����ǲ��̥ӥåȤ����ͥ���٤��б�
 *  �����롥
 */


Inline UINT
bitmap_search(UINT bitmap)
{
	UINT	numOfSign;

	/*
	 *  ���Υ����ɤϡ�bitmap��UINT���ˤ�32�ӥåȤǤ��뤳�Ȥ��ꤷ
	 *  �Ƥ��롥Signbits ̿���32�ӥå��������ä�MSB����Ϣ³����
	 *  ���ӥå� - 1 ���֤���all 0�ΤȤ���31���֤���LSB�Τߤ�1��
	 *  �Ȥ���30���֤���
	 */
#ifdef __GNUC__			// gcc
	// gcc 3.4.1 �λ����Ǥϡ����ڥ��ɤ˲��̥ϡ��ե쥸���������
	// �Ǥ��ʤ����ᡢ;�פʥ����ɤ�ɬ�פˤʤ롣
	Asm( "r0.L=signbits %1; %0 = r0.L;": "=d"(numOfSign) : "d"(bitmap) : "R0" );
#elif defined(__ECC__)	// visualdsp
	Asm( "%0=signbits %1;": "=l"(numOfSign) : "d"(bitmap) );
#else
#error "Compiler is not supported"
#endif
	return( numOfSign );
}



/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	VP	sp;		/* �����å��ݥ��� */
	FP	pc;		/* �ץ���५���� */
} CTXB;


/*
 *  �����ƥ���ֻ���
 *	�֤��ͤϰʲ��ΤȤ���
 *	TRUE : �󥿥�������ƥ�����
 *	FALSE: ����������ƥ�����
 *				IPEND��$8000��$8010�λ�������������ƥ����ȤǤ��롣����ʳ��ΤȤ����󥿥�������ƥ����ȡ�
 */

Inline BOOL
sense_context()
{
	return( *pIPEND & 0x7FEF );
}

/*
* ���ߤΥ�å����֤�Ĵ�٤롣�����������ߤޤǥ�å�����sil_loc_int()��
* ����å����֤ϡ�����sense_lock()�Ǥ�̵�뤹�롣
*/
Inline BOOL
sense_lock()
{
#ifdef UNMANAGED_INT
	return((*pIMASK & ~UNMANAGED_INT )== 0xC01F );
#else
	return(*pIMASK == 0xC01F );
#endif
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock


/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ�
 *  �Ȥ��ʤ����ˤϡ�task_intmask ����� 0 �ˤʤäƤ���ȹͤ���Ф褤��
 *
 */

#ifdef SUPPORT_CHG_IPM
extern UH	task_intmask;	/* ����������ƥ����ȤǤγ���ߥޥ��� */
#endif /* SUPPORT_CHG_IPM */

#ifdef UNMANAGED_INT
#if UNMANAGED_INT & 0xC01F
// �����������ߤ��ϰϥ����å��������������ߤ�IVHW����IVG13�δ֤Ǥʤ���Фʤ�ʤ�
#error "Illegal un-managed interrupt : must be IVHW-IVG13"
#endif
#endif


// BLACKfin�Ǥ�IMASK��0xC01F��񤭹����CPU���å����롣
Inline void
t_lock_cpu()
{
#ifdef UNMANAGED_INT
	unsigned int imask;
	Asm( "cli %0;" :"=d"(imask) );
	Asm( "sti %0;" : :"d"(0xC01f | (imask & UNMANAGED_INT) ) );
#else
    Asm( "cli r0;" : : :"R0" );
	Asm( "sti %0;" : :"d"(0xC01F) );
#endif
}

Inline void
t_unlock_cpu()
{
#ifdef UNMANAGED_INT
	unsigned int imask;
	Asm( "cli %0;" :"=d"(imask) );
	Asm( "sti %0;" : :"d"( (0xffff & ~UNMANAGED_INT) | (imask & UNMANAGED_INT) ) );
#else
	Asm( "sti %0;" : :"d"(0xffff) );
#endif
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */


Inline void
i_lock_cpu()
{
#ifdef UNMANAGED_INT
	unsigned int imask;
	Asm( "cli %0;" :"=d"(imask) );
	Asm( "sti %0;" : :"d"(0xC01f | (imask & UNMANAGED_INT) ) );
#else
    Asm( "cli r0;" : : :"R0" );
	Asm( "sti %0;" : :"d"(0xC01F) );
#endif
}

Inline void
i_unlock_cpu()
{
#ifdef UNMANAGED_INT
	unsigned int imask;
	Asm( "cli %0;" :"=d"(imask) );
	Asm( "sti %0;" : :"d"( (0xffff & ~UNMANAGED_INT) | (imask & UNMANAGED_INT) ) );
#else
	Asm( "sti %0;" : :"d"(0xffff) );
#endif
}

/*
 *  �������ǥ����ѥå��� 
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���cpu_support.S��
 *
 *  dispatch �ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ����������
 *  ��ǡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	dispatch(void);

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���cpu_support.S��
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	exit_and_dispatch(void);

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ������
 */


/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 * evtvector ��start.asm���������Ƥ��롣
 */
extern void (* dev_vector[])(void) ;

extern void (* exc_vector)(VP) ;
Inline void
define_inh(INHNO inhno, FP inthdr)
{
	dev_vector[inhno] = inthdr;
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr �����ꤹ�롥
 */
Inline void
define_exc(EXCNO excno, FP exchdr)
{
//	exc_vector[excno] = exchdr;		// �㳰�ϥ�ɥ������˳�Ǽ 
	exc_vector = (void (*)(VP))exchdr;		// �㳰�ϥ�ɥ���Ǽ
}

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

#define	INTHDR_ENTRY(inthdr)	extern void inthdr(void);	
#define	INT_ENTRY(inthdr)	inthdr

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

#define	EXCHDR_ENTRY(exchdr)	extern void exchdr( VP );
#define	EXC_ENTRY(exchdr)	exchdr

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	return( *pIPEND & 0x7FE6 );				// IVG15, GIE, EXP, EMU �ʳ��ΥӥåȤ�Ω�äƤ�����󥿥�������ƥ�����
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ��ȡ������������ߤξ��֤�̵�뤹�롣
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
#ifdef UNMANAGED_INT
	return((*pIMASK | UNMANAGED_INT) != 0xFFFF );		// 0xFFFF�ʤ饢���å�
#else
	return(*pIMASK != 0xFFFF );				// 0xFFFF�ʤ饢���å�
#endif
}

/*
 *  �ץ��å���¸�ν����
 */
extern void	cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	cpu_terminate(void);

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
