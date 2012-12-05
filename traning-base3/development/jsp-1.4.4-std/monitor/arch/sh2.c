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
 *  @(#) $Id: sh2.c,v 1.4 2006/05/13 16:05:29 roi Exp $
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
#ifdef SUPPORT_NETDEV
#include "netdevice.h"
#endif
#include "monitor.h"

extern void _kernel_break_wait();
#ifdef SUPPORT_NETDEV
extern unsigned long vectors[];
#endif

#define set_align(a, b)	((UW)a & ~(b-1))

/*
 * �쥸�����ι�¤��
 */
typedef struct t_reg{
	UW	gbr;
	UW	macl;
	UW	mach;
	UW	r14;
	UW	r13;
	UW	r12;
	UW	r11;
	UW	r10;
	UW	r9;
	UW	r8;
	UW	pr;
	UW	r7;
	UW	r6;
	UW	r5;
	UW	r4;
	UW	r3;
	UW	r2;
	UW	r1;
	UW	r0;
	UW	pc;
	UW	sr;
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
 * SH2�Υ���ޥåԥ�
 */

static T_MEMDEF const memdefine[] = {
#if defined(HSB7616IT)
	{0x00000000, 0x0001FFFF, MEMORY_AREA, MREAD_ONLY },
	{0x02000000, 0x021FFFFF, MEMORY_AREA, MREAD_ONLY },
	{0x04000000, 0x040FFFFF, MEMORY_AREA, MREAD_WRITE},
	{0xFFFFE000, 0xFFFFFFFF, PORT_AREA,   MREAD_WRITE}
#elif defined(MS72060SEP01)
	{0x00000000, 0x001FFFFF, MEMORY_AREA, MREAD_ONLY },
	{0x01000000, 0x01FFFFFF, MEMORY_AREA, MREAD_ONLY },
	{0x0C000000, 0x0FFFFFFF, MEMORY_AREA, MREAD_WRITE},
	{0x10000000, 0xFFF7FFFF, PORT_AREA,   MREAD_WRITE},
	{0xFFF80000, 0xFFF9FFFF, MEMORY_AREA, MREAD_WRITE},
	{0xFFFA0000, 0xFFFFFFFF, PORT_AREA,   MREAD_WRITE}
#elif defined(CRB_H3)
	{0x00000000, 0x0003FFFF, MEMORY_AREA, MREAD_ONLY },
	{0x00200000, 0x0021FFFF, MEMORY_AREA, MREAD_WRITE},
	{0x00220000, 0x0022FFFF, MEMORY_AREA, MREAD_ONLY },
	{0x00230000, 0x0023FFFF, PORT_AREA,   MREAD_WRITE},
	{0xFFF00000, 0xFFFCFFFF, PORT_AREA,   MREAD_WRITE},
	{0xFFFD0000, 0xFFFFFFFF, MEMORY_AREA, MREAD_WRITE}
#else
#error "No board type in SH2 groups."
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
#ifdef SUPPORT_NETDEV
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
#endif
			*((UH *)p) = sil_reh_mem((VP)address);
		}
		else if(type == 4){
			len = 4;
#ifdef SUPPORT_NETDEV
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
#endif
			*((UW *)p) = sil_rew_mem((VP)address);
		}
		else{
#ifdef SUPPORT_NETDEV
			len = 1;
            if(!NetDeviceRead((unsigned long)address, len, (void *)p))
				*((UB *)p) = sil_reb_mem((VP)address);
#else
			len = 1;
			*((UB *)p) = sil_reb_mem((VP)address);
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
#ifdef SUPPORT_NETDEV
            if(!NetDeviceWrite((unsigned long)address, len, (void *)p))
#endif
			sil_wrh_mem((VP)address, *((UH *)p));
		}
		else if(type == 4){
			len = 4;
			address = set_align(address, len);
#ifdef SUPPORT_NETDEV
            if(!NetDeviceWrite((unsigned long)address, len, (void *)p))
#endif
			sil_wrw_mem((VP)address, *((UW *)p));
		}
		else{
#ifdef SUPPORT_NETDEV
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
 *  �������ץ����ΰ������pc����Ф��ؿ�
 */
UW
get_exception_pc(VP p_excinf)
{
	UW pc;

	pc = *(UW*)((char*)p_excinf-4);
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

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskpc == (FP)_kernel_break_wait){
			sreg = *((T_REG *)rtst.tsksp);
			printf(" PC =%08lx SP =%08x PR =%08x", (long)sreg.pc, (UW)((long)rtst.tsksp+sizeof(T_REG)), sreg.pr);
			printf(" SR =%08x MBH=%08x MBL=%08x\n", sreg.sr, sreg.mach, sreg.macl);
			printf(" R0 =%08x R1 =%08x R2 =%08x", sreg.r0, sreg.r1, sreg.r2);
			printf(" R3 =%08x R4 =%08x R5 =%08x\n", sreg.r3, sreg.r4, sreg.r5);
			printf(" R6 =%08x R7 =%08x R8 =%08x", sreg.r6, sreg.r7, sreg.r8);
			printf(" R9 =%08x R10=%08x R11=%08x\n", sreg.r9, sreg.r10, sreg.r11);
			printf(" R12=%08x R13=%08x R14=%08x\n", sreg.r12, sreg.r13, sreg.r14);
			printf("     %08lx    %02x %02x\n", (long)sreg.pc, *((UB*)sreg.pc), *((UB*)(sreg.pc+1)));
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
 * ���쥮��顼�������ץ����
 */
static void
irregular_ext_handler(VP p_excinf, const char *s)
{
	UW pc = get_exception_pc(p_excinf);

	if(runtsk){
		if(exc_sense_context(p_excinf)){
			syslog_3(LOG_EMERG, "Irregular Exception(%s) occured in not task Context pc=0x%x p_excinf=0x%x !", s, pc, p_excinf);
			kernel_exit();
		}
		else{
			syslog_4(LOG_ERROR, "Irregular Exception(%s) occured in tskid=%d pc=0x%x p_excinf=0x%x !", s, TSKID(runtsk), pc, p_excinf);
			isus_tsk(TSKID(runtsk));
		}
	}
	else{
		syslog_3(LOG_EMERG, "Irregular Exception(%s) occured in Idle pc=0x%x p_excinf=0x%x !", s, pc, p_excinf);
		kernel_exit();
	}
}

/*
 *  ��������̿��:General Illegal Instruction
 */
void
irregular_extgii_handler(VP p_excinf)
{
	irregular_ext_handler(p_excinf, "GII");
}

/*
 *  ����å�����̿��:Slot Illegal Instruction
 */
void
irregular_extsii_handler(VP p_excinf)
{
	irregular_ext_handler(p_excinf, "SII");
}

/*
 *  CPU���ɥ쥹���顼:CPU Address Error
 */
void
irregular_extcae_handler(VP p_excinf)
{
	irregular_ext_handler(p_excinf, "CAE");
}

/*
 *  DMA���ɥ쥹���顼:DMA Address Error
 */
void
irregular_extdae_handler(VP p_excinf)
{
	irregular_ext_handler(p_excinf, "DAE");
}

