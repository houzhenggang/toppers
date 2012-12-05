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
 *	�������åȥ����ƥ��¸�⥸�塼���ADSP-BF531/2/3�ѡ�
 */

#include "jsp_kernel.h"
#include <sil.h>

#ifdef __GNUC__
#include "../cdefbf532.h"		/* gnu tool chain */
#elif defined(__ECC__)
#include <cdefbf53x.h>				/* VisualDSP++ */
#include <sys/exception.h>
#include <ccblkfn.h>
#include <sysreg.h>
#else
#error "Compiler is not supported"
#endif



#define SYSCFG_VALUE 0x36

/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
	// BF531/2/3�Υ��Ρ��ޥ꡼�к� rev 0.1, 0.2��
	Asm( "SYSCFG=%0;"  : :"d"(SYSCFG_VALUE) ) ;

	/*
	 *  PLL������
	 *
	 */
	/*
	 *  27MHz*22��=594MHz�����ꤹ��(600MHz)
	 *  27MHz*28��=756MHz�����ꤹ��(750MHz)
	 *  CSEL = 1; SSEL = 5 (600MHz)
	 *  CSEL = 1; SSEL = 6 (750MHz)
	 */
#ifndef FORCE_PLL_INITIALIZE
	 	// PLL������ͤΤޤޤǤ��ꡢ���ġ�SDRAM��������Ǥʤ����PLL����������
	 if ( ( *pPLL_CTL == 0x1400 ) && ( !(*pEBIU_SDBCTL & EBE ) ) )
#endif
	 {

		*pSIC_IWR = IWR_ENABLE(0);				// PLL�Τ�IWR�����
#if CSELVAL == 1
		*pPLL_DIV = CCLK_DIV1 | SCLK_DIV(SSELVAL);
#elif CSELVAL == 2
		*pPLL_DIV = CCLK_DIV2 | SCLK_DIV(SSELVAL);
#elif CSELVAL == 4
		*pPLL_DIV = CCLK_DIV4 | SCLK_DIV(SSELVAL);
#elif CSELVAL == 8
		*pPLL_DIV = CCLK_DIV8 | SCLK_DIV(SSELVAL);
#else
#error Wrong CSELVAL. Must be one of 1,2,4,8.
#endif

		*pPLL_CTL = MSELVAL << 9;

		asm("cli r0; csync; idle; sti r0;": : :"R0");
		*pSIC_IWR = IWR_ENABLE_ALL;
	}

}


unsigned int priority_mask[16]={
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x0000007F,
0x00000180,
0x00001E00,
0x0000E000,
0x00070000,
0x00180000,
0x00E00000,
0x00000000,
0x00000000
};


/*
* SIC_IARx����Ϥ��ơ����٥�Ƚ�̤��Ȥ˳�����Ƥ��Ƥ��������
* �Υӥåȥޥåפ��롣SIC_IARx�Υե�������ͤ�ͥ����-7�ʤΤ�
* ����ʬ�������롣
*/
#define INSTALL_PRIORITY    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                         /* IAR����ͥ���̤���Ф� */ \
        priority_mask[priority + 7] |= device;        /* ���Ф���ͥ���̤˴�Ť��ǥХ�������Ͽ */ \
        device <<= 1;                                 /* ���ΥǥХ��� */ \
        iar >>= 4;                                    /* ����IAR�ե������ */ \
    }

void make_priority_mask( void )
{
	unsigned int i, priority, device, iar;


	/*
 *  �����߽�̤��Ȥ�ISR�ӥåȥޥåפκ���
 *  SIC_IARx������Ϥ�����ʬ������˺Ѥޤ��뤳��
 */

 	for ( i=0; i<16; i++ ){
 		priority_mask[i] = 0;
 	}

	device = 1;
	iar = *pSIC_IAR0;
    INSTALL_PRIORITY

	iar = *pSIC_IAR1;
    INSTALL_PRIORITY

	iar = *pSIC_IAR2;
    INSTALL_PRIORITY

}


/*
 * �����ߤε��ġ��ػ�
 *
 */
ER ena_int( INTNO intno )
{
	unsigned int mask;

	if ( intno >= DEVICE_INTERRUPT_COUNT )
		return ( E_PAR );
	else {
		SIL_PRE_LOC;

		mask = 1 << intno;
		SIL_LOC_INT();			// �����������ߤޤǶػߤ���
		*pSIC_IMASK |= mask;
		asm volatile( "ssync;" );
		SIL_UNL_INT();			// �����ߺƵ���
		return (0);
	}
}
/*
 * dis_int()�ϡ����μ����Ǥ�SIC_IMASK�λ���ӥåȤ򥯥ꥢ���롣
 *
 * ��������SIC_IMASK�Υ��ꥢ�ϥ��ץꥱ�������¹���ˤϴ��Ǥ��ꡢ
 * Blackfin�Υޥ˥奢��Ǥ�ն��Ū�˶ػߤ���Ƥ��롣���Τ��ᡢTOPPERS/JSP for Blackfin
 * �Ǥϡ����δؿ���������ʤ���
 *
ER dis_int( INTNO intno )
{
	unsigned int mask;

	if ( intno >= DEVICE_INTERRUPT_COUNT )
		return ( E_PAR );
	else {
		mask = 1 << intno;
		mask = ~mask;
		*pSIC_IMASK &= mask;
		return (0);
	}
}
*/

/*
 * chg_ims()�ϡ����μ����Ǥ�SIC_IMASK���ѹ����롣
 *
 * ��������SIC_IMASK�ΥӥåȤΥ��ꥢ�ϥ��ץꥱ�������¹���ˤϴ��Ǥ��ꡢ
 * Blackfin�Υޥ˥奢��Ǥ�ն��Ū�˶ػߤ���Ƥ��롣���Τ��ᡢTOPPERS/JSP for
 * Blackfin�Ǥϡ����δؿ���������ʤ���
 *
ER chg_ims( IMS ims )
{
	*pSIC_IMASK = ims;
	return( 0 );
}
*/


extern ER get_ims( IMS * p_ims )
{
	*p_ims = *pSIC_IMASK;
	return( 0 );;
}


/*
 *  �����ߤ�ǥХ����˳�����Ƥ�
 */
void device_dispatcher(  unsigned int priority, unsigned int imask )
{
	unsigned int candidates, device;

	candidates = priority_mask[priority] & *pSIC_ISR & *pSIC_IMASK;	// ���ߤΥץ饤����ƥ��������������߸������ꤹ��

	asm volatile("sti %0;": : "d"(imask) );

	if ( ! candidates ) // �����߸�������Ǥ��ʤ��ʤ顢����ͳ��Ǥ���
	{
		if ( priority == ik_hardware_err)
			dev_vector[INHNO_HW_ERROR]();
		else
			if ( priority == ik_timer)
			dev_vector[INHNO_TIMER]();
		else
			dev_vector[INHNO_RAISE]();		//�����եȥ�����������

	}
	else
	{
		if ( candidates & 0x80000000 )
			device = 31;
		else
		{
#ifdef __GNUC__
	asm ( "r1.L = signbits %1; %0 = r1.L(z);":"=d"(device) :"d"(candidates): "R1"  );
#elif defined(__ECC__)
	asm( "%0 = signbits %1;" : "=l"( device ) : "d"( candidates ) );
#else
#error "Compiler is not supported"
#endif
			device = 30 - device;		// bit mask is converted to bit number
		}
		dev_vector[device]();
	}
}



/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit()
{
	while(1)
		;
}
/*
 *  �������åȥ����ƥ��ʸ������
 */
void
sys_putc(char c)
{
}



