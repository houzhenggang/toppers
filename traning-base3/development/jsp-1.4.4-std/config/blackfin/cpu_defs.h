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
 *	�ץ��å��˰�¸���륢�ץꥱ��������ѻ񸻤������BLACKfin�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h �� sil.h �ǥ��󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥�
 *  ���롼�ɤ������ˡ�t_stddef.h �� itron.h �����󥯥롼�ɤ����Τǡ�
 *  �����˰�¸���Ƥ�褤��
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define BLACKFIN			/* �ץ��å�ά�� */


/*
 *  �����ƥࡦ���󥿡��ե��������쥤�䡼
 */
 
/*
 *  �ץ��å��Υ���ǥ�����
 */
#define	SIL_ENDIAN	SIL_ENDIAN_LITTLE	/* ��ȥ륨��ǥ����� */


/*
* �����ߥ�å�����
*/

#define SIL_PRE_LOC		UINT _intmask_
#define SIL_LOC_INT()	asm volatile ( "cli %0;": "=d"(_intmask_) )
#define SIL_UNL_INT()	asm volatile ( "sti %0;": :"d"(_intmask_) )
 
 



#ifndef _MACRO_ONLY

/*
 *  ����ߡ�CPU�㳰�ϥ�ɥ��ֹ�η�
 */
typedef	UINT	INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	UINT	EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */



/*
 *  ���������Ԥ�
 *  �����ƥ��¸���� SIL_DLY_TIM1��SIL_DLY_TIM2��������Ƥ�����
 *  SIL_DLY_TIM1��sil_dly_nse�θƤӽФ������С��إå�(nS)
 *  SIL_DLY_TIM2��sil_dly_nse�Υ롼�פ�Ĺ��(nS)
 */
void sil_dly_nse(UINT dlytim);



/*
 *  ��ǽɾ���ѥ����ƥ����λ���
 *  cycle�����󥿤���64�ӥåȤ��ͤ���Ф���
 */
typedef	long long	SYSUTIM;	/* ��ǽɾ���ѥ����ƥ���� */

Inline  ER	vxget_tim(SYSUTIM *p_sysutim)
{
	unsigned int lo, hi;
	
	Asm( "%0=CYCLES; %1=CYCLES2;" :"=d"(lo), "=d"(hi) );
	((unsigned int *)p_sysutim)[0] = lo;
	((unsigned int *)p_sysutim)[1] = hi;
	return(0);
}

/*
* �����ƥࡦ���ꡦ��������
*/

#define sil_wrb_iop(iop, data)	sil_wrh_mem( iop, (UB)data )
#define sil_wrh_iop	sil_wrh_mem
#define sil_wrw_iop	sil_wrw_mem
#define sil_wrh_lep sil_wrh_lem
#define sil_wrw_lep sil_wrw_lem
#define sil_wrh_bep sil_wrh_bem
#define sil_wrw_bep sil_wrw_bem

VB sil_reb_iop(VP iop);
VH sil_reh_iop(VP iop);
VW sil_rew_iop(VP iop);
VH sil_reh_lep(VP iop);
VW sil_rew_lep(VP iop);
VH sil_reh_bep(VP iop);
VW sil_rew_bep(VP iop);


#endif /* _MACRO_ONLY */




#endif /* _CPU_DEFS_H_ */
