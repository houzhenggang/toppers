/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003-2005 by Ryosuke Takeuchi
 *               Platform Development Center RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: m16c.c,v 1.1 2007/08/05 10:41:29 roi Exp $
 */

/* 
 *  TOPPERS/JSP�ѥ�������˥�CPU��¸�ץ���ࡥ
 *
 */

#include <t_services.h>
#include <s_services.h> 
#include <sil.h>
#include <stdio.h>
#include <string.h>
#include "jsp_kernel.h"
#include "task.h"
#include "task_expansion.h"
#include "monitor.h"

extern void _kernel_break_wait();

/*
 * �쥸�����ι�¤��
 */
typedef struct t_reg{
	UH	r0;
	UH	r1;
	UH	r2;
	UH	r3;
	UH	a0;
	UH	a1;
	UH	sb;
	UH	fb;
	UH	lpc;
	UB	lflg;
	UB	hpc;
}T_REG;

/*
 * ����Υޥåԥ������¤��
 */

typedef struct t_memdef{
	UW	mstart;
	UW	mend;
	UB	mtype;
	UB	mstate;
}T_MEMDEF;

/*
 * M16C�Υ���ޥåԥ�
 */

static T_MEMDEF const memdefine[] = {
	0x00000000,	0x000003FF, PORT_AREA,   MREAD_WRITE,
#if defined(OAKS16)
	0x00000400, 0x00002BFF, MEMORY_AREA, MREAD_WRITE,
	0x000E0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#elif defined(OAKS16_MINI)
	0x00000400, 0x00000BFF, MEMORY_AREA, MREAD_WRITE,
	0x000F0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#elif defined(M3029)
	0x00000400, 0x000033FF, MEMORY_AREA, MREAD_WRITE,
	0x000E0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#else
#error "No board type in M16C groups."
#endif
};

/******************************************************************************
 * �ϡ��ɥ������ݡ���°�����ȴؿ�
 ******************************************************************************/
/*
 *  ���ɥ쥹��������ΰ�°������Ф�
 *  mode=0:�ΰ�η�
 *  mode=1:�ɤ߼��񤭹���°��
 */

UB
getMemoryType(UW address, INT mode)
{
	INT count = sizeof(memdefine) / sizeof(T_MEMDEF);
	INT i;

	for(i = 0 ; i < count ; i++){
		if(address >= memdefine[i].mstart && address <= memdefine[i].mend){
			if(mode == 0)
				return memdefine[i].mtype;
			else
				return memdefine[i].mstate;
		}
	}
	return NONE_AREA;
}

/*
 *  ���ɥ쥹���饢�饤���Υ��ɥ쥹����Ф�
 */

UW
MonAlignAddress(UW address)
{
	return address;
}

/******************************************************************************
 * ���ꥢ�������Ѵؿ�
 ******************************************************************************/
/*
 *  �����ΰ���Ф����ɤ߽Ф��ؿ�
 *  �ΰ�Υ����å���Ԥ������顼�ʤ饼����֤�
 */
INT
MemoryRead(UW address, VP_INT p, INT type)
{
	INT  len;

	switch(getMemoryType(address, 0)){
	case PORT_AREA:
		if(type == 2){
			len = 2;
			*((UH _far *)p) = sil_reh_mem((VP)address);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)p) = sil_rew_mem((VP)address);
		}
		else{
			len = 1;
			*((UB _far *)p) = sil_reb_mem((VP)address);
		}
		break;
	case MEMORY_AREA:
		if(type == 2){
			len = 2;
			*((UH _far *)p) = *((UH _far *)address);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)p) = *((UW _far *)address);
		}
		else{
			len = 1;
			*((UB _far *)p) = *((UB _far *)address);
		}
		break;
	default:
		len = 0;
		break;
	}
	return len;
}

/*
 *  �����ΰ���Ф���񤭹��ߴؿ�
 *  �ΰ�Υ����å���Ԥ������顼�ʤ饼����֤�
 */
INT
MemoryWrite(UW address, VP_INT p, INT type)
{
	INT  len;

	switch(getMemoryType(address, 0)){
	case PORT_AREA:
		if(type == 2){
			len = 2;
			sil_wrh_mem((VP)address, *((UH _far *)p));
		}
		else if(type == 4){
			len = 4;
			sil_wrw_mem((VP)address, *((UW _far *)p));
		}
		else{
			len = 1;
			sil_wrb_mem((VP)address, *((UB _far *)p));
		}
		break;
	case MEMORY_AREA:
		if(getMemoryType(address, 1) == MREAD_ONLY){
			len = 0;
		}
		else if(type == 2){
			len = 2;
			*((UH _far *)address) = *((UH _far *)p);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)address) = *((UW _far *)p);
		}
		else{
			len = 1;
			*((UB _far *)address) = *((UB _far *)p);
		}
		break;
	default:
		len = 0;
		break;
	}
	return len;
}

/******************************************************************************
 * ��˥��Ѵؿ�
 ******************************************************************************/
/*
 *  �������ץ����ΰ������pc����Ф��ؿ�
 */
UW
get_exception_pc(VP p_excinf)
{
	UW pc;

	pc = *(UH*)((char*)p_excinf+16) | ((UW)(*((char*)p_excinf+19) & 0xf) << 16);
	return pc;
}

/*
 *  �쥸�������Ƥ�ɽ��
 */
void
display_registers(ID tskid)
{
	ER     ercd;
	T_RTST rtst;
	T_REG  reg;
	UW     pc;

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskpc == (FP)_kernel_break_wait){
			reg = *((T_REG *)rtst.tsksp);
			pc = reg.lpc | (((UW)reg.hpc & 0xf)<<16);
			printf("  PC=%06lx SP=%04x", (unsigned long)pc, (UW)rtst.tsksp+sizeof(T_REG));
			printf("       IPL=%1x U=%1x I=%1x", (reg.hpc>>4) & 0x7, (reg.lflg>>7) & 1, (reg.lflg>>6) & 1);
			printf(" O=%1x B=%1x S=%1x", (reg.lflg>>5) & 1, (reg.lflg>>4) & 1, (reg.lflg>>3) & 1);
			printf(" Z=%1x D=%1x C=%1x\n", (reg.lflg>>2) & 1, (reg.lflg>>1) & 1, reg.lflg & 1);
			printf("  R0=%04x R1=%04x R2=%04x", reg.r0, reg.r1, reg.r2);
			printf(" R3=%04x A0=%04x A1=%04x", reg.r3, reg.a0, reg.a1);
			printf(" SB=%04x FB=%04x\n", reg.sb, reg.fb);
			printf("     %06lx    %02x %02x\n", (unsigned long)pc, *((UB*)pc), *((UB*)(pc+1)));
			return;
		}
		else if(rtst.tskstat == TTS_DMT){
			printf("  wait in activate_r() !!\n");
			return;
		}
	}
	printf("  wait in dispatch() !!\n");
}

/******************************************************************************
 * ���顼�����Ѵؿ�
 ******************************************************************************/
/*
 * ���쥮��顼����ߥϥ�ɥ顼
 */
void
irregular_int_handler(void)
{
	if(runtsk){
		if(intnest > 1){
			syslog_1(LOG_EMERG, "Irregular Interrupt occured in tskid=%d !", TSKID(runtsk));
			kernel_exit();
		}
		else{
			syslog_1(LOG_ERROR, "Irregular Interrupt occured in tskid=%d  !", TSKID(runtsk));
			isus_tsk(TSKID(runtsk));
		}
	}
	else{
		syslog_0(LOG_EMERG, "Irregular Interrupt occured in Idle!");
		kernel_exit();
	}
}

/*
 * ���쥮��顼�������ץ����
 */
void
irregular_ext_handler(VP p_excinf)
{
	UW pc = get_exception_pc(p_excinf);

	if(runtsk){
		if(exc_sense_context(p_excinf)){
			syslog_1(LOG_EMERG, "Irregular Exception occured in not task Context pc=0x%x !", pc);
			kernel_exit();
		}
		else{
			syslog_2(LOG_ERROR, "Irregular Exception occured in tskid=%d pc=0x%x !", TSKID(runtsk), pc);
			isus_tsk(TSKID(runtsk));
		}
	}
	else{
		syslog_1(LOG_EMERG, "Irregular Exception occured in Idle pc=0x%x !", pc);
		kernel_exit();
	}
}

