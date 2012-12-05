/*
 *  TOPPERS/JSP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
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
 *  @(#) $Id: powerpc32.c,v 1.2 2009/03/02 16:20:29 roi Exp $
 */

/* 
 *  TOPPERS/JSP�ѥ�������˥�CPU��¸�ץ���ࡥ
 *
 */

#include <t_services.h>
#include <s_services.h> 
#include <sil.h>
#include <stdio.h>
#include "jsp_kernel.h"
#include "task.h"
#include "task_expansion.h"
#ifdef PANEL_SIMULATION
#include "netdevice.h"
#endif
#include "monitor.h"

extern void _kernel_break_wait();

#define set_align(a, b)	((UW)a & ~(b-1))

/*
 * �쥸�����ι�¤��
 */
typedef struct t_reg{
#ifdef SUPPORT_FLOATING_POINT_REG
	UW  memo_msr;
	UW  memo_off;
	UW  fps[33*2+1];
#endif	/* SUPPORT_FLOATING_POINT_REG */
	UW  r13;
	UW  r14;
	UW  r15;
	UW  r16;
	UW  r17;
	UW  r18;
	UW  r19;
	UW  r20;
	UW  r21;
	UW  r22;
	UW  r23;
	UW  r24;
	UW  r25;
	UW  r26;
	UW  r27;
	UW  r28;
	UW  r29;
	UW  r30;
	UW  r31;
	UW  lr2;

	UW	r0;
	UW	r3;
	UW	r4;
	UW	r5;
	UW	r6;
	UW	r7;
	UW	r8;
	UW	r9;
	UW	r10;
	UW	r11;
	UW	r12;
	UW	srr0;
	UW	srr1;
	UW  lr;
	UW	ctr;
	UW	cr;
	UW	xer;
	UW  dummy;
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
 * POWERPC32�Υ���ޥåԥ�
 */

static T_MEMDEF const memdefine[] = {
	{0x00000000, 0x0FFFFFFF, MEMORY_AREA, MREAD_WRITE},
#ifdef SUPPORT_MIRROR_MEMORY
	{0x20000000, 0x2FFFFFFF, MEMORY_AREA, MREAD_WRITE},
#endif
#if defined(SANTAMARIA)
	{0xEC000000, 0xEC7FFFFF, MEMORY_AREA, MREAD_ONLY },
	{0xFF400000, 0xFF4FFFFF, PORT_AREA,   MREAD_WRITE},
	{0xFFF00000, 0xFFFFFFFF, MEMORY_AREA, MREAD_ONLY }
#elif defined(EP440XC)
	{0xE0000000, 0xE00004FF, PORT_AREA,   MREAD_ONLY },
	{0xE0010000, 0xE0013FFF, MEMORY_AREA, MREAD_WRITE},
	{0xEF600000, 0xEF6011FF, PORT_AREA,   MREAD_WRITE},
	{0xFFF00000, 0xFFFFFFFF, MEMORY_AREA, MREAD_ONLY }
#elif defined(EP460XC)
	{0xD8000000, 0xD8FFFFFF, PORT_AREA,   MREAD_WRITE},
	{0xE2000000, 0xE20FFFFF, PORT_AREA,   MREAD_WRITE},
	{0xEF600000, 0xEF6011FF, PORT_AREA,   MREAD_WRITE},
	{0xFFF00000, 0xFFFFFFFF, MEMORY_AREA, MREAD_ONLY }
#else
#error "No board type in POWERPC32 groups."
#endif
};

static T_REG  sreg;

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
#ifdef PANEL_SIMULATION
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
#endif
			asm("eieio");
			*((UH *)p) = sil_reh_mem((VP)address);
		}
		else if(type == 4){
			len = 4;
#ifdef PANEL_SIMULATION
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
#endif
			*((UW *)p) = sil_rew_mem_ppc((VP)address);
		}
		else{
#ifdef PANEL_SIMULATION
			len = 1;
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
				*((UB *)p) = sil_reb_mem_ppc((VP)address);
#else
			len = 1;
			*((UB *)p) = sil_reb_mem_ppc((VP)address);
#endif
		}
		break;
	case MEMORY_AREA:
		if(type == 2){
			len = 2;
			*((UH *)p) = *((UH *)set_align(address, len));
		}
		else if(type == 4){
			len = 4;
			*((UW *)p) = *((UW *)set_align(address, len));
		}
		else{
			len = 1;
			*((UB *)p) = *((UB *)address);
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
			address = set_align(address, len);
#ifdef PANEL_SIMULATION
            if(!NetDeviceWrite((unsigned long)address, len, (void *)p))
#endif
			sil_wrh_mem((VP)address, *((UH *)p));
		}
		else if(type == 4){
			len = 4;
			address = set_align(address, len);
#ifdef PANEL_SIMULATION
            if(!NetDeviceWrite((unsigned long)address, len, (void *)p))
#endif
			sil_wrw_mem((VP)address, *((UW *)p));
		}
		else{
#ifdef PANEL_SIMULATION
			len = 1;
            if(!NetDeviceWrite((unsigned long)address, len, (void *)p))
				sil_wrb_mem((VP)address, *((UB *)p));
#else
			len = 1;
			sil_wrb_mem((VP)address, *((UB *)p));
#endif
		}
		break;
	case MEMORY_AREA:
		if(getMemoryType(address, 1) == MREAD_ONLY){
			len = 0;
		}
		else if(type == 2){
			len = 2;
			*((UH *)address) = *((UH *)set_align(p, len));
		}
		else if(type == 4){
			len = 4;
			*((UW *)address) = *((UW *)set_align(p, len));
		}
		else{
			len = 1;
			*((UB *)address) = *((UB *)p);
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
 *  �쥸�������Ƥ�ɽ��
 */
void
display_registers(ID tskid)
{
	ER     ercd;
	T_RTST rtst;

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskpc == (FP)_kernel_break_wait){
			sreg = *((T_REG *)(rtst.tsksp-4));
			printf(" PC =%08lx SP =%08x MSR =%08x", (long)sreg.srr0, (UW)((long)rtst.tsksp+sizeof(T_REG)), sreg.srr1);
			printf(" LR =%08x CTR=%08x CR=%08x\n", sreg.lr, sreg.ctr, sreg.cr);
			printf(" R0 =%08x R3 =%08x R4 =%08x", sreg.r0, sreg.r3, sreg.r4);
			printf(" R5 =%08x R6 =%08x R7 =%08x\n", sreg.r5, sreg.r6, sreg.r7);
			printf(" R8 =%08x R9 =%08x R10=%08x", sreg.r8, sreg.r9, sreg.r10);
			printf(" R11=%08x R12=%08x R13=%08x\n", sreg.r11, sreg.r12, sreg.r13);
			printf(" R14=%08x R15=%08x R16=%08x\n", sreg.r14, sreg.r15, sreg.r16);
			printf(" R17=%08x R18=%08x R19=%08x\n", sreg.r17, sreg.r18, sreg.r19);
			printf(" R20=%08x R21=%08x R22=%08x\n", sreg.r20, sreg.r21, sreg.r22);
			printf(" R23=%08x R24=%08x R25=%08x\n", sreg.r23, sreg.r24, sreg.r25);
			printf(" R26=%08x R27=%08x R28=%08x\n", sreg.r26, sreg.r27, sreg.r28);
			printf(" R29=%08x R30=%08x R31=%08x\n", sreg.r29, sreg.r30, sreg.r31);
			printf(" XER=%08x\n", sreg.xer);
			printf("     %08lx    %08x\n", (long)sreg.srr0, *((UW*)sreg.srr0));
			return;
		}
		else if(rtst.tskstat == TTS_DMT){
			printf("  wait in activate_r() !!\n");
			return;
		}
	}
	printf("  wait in dispatch() !!\n");
}


void __va_arg_type_violation(void)
{}

