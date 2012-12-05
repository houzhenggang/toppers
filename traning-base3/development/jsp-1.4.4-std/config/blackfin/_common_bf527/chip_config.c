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
 *  Copyright (C) 2009-     by Monami Software Limited Partnership, JAPAN
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
 *	�������åȥ����ƥ��¸�⥸�塼���ADSP-BF527�ѡ�
 */

#include "jsp_kernel.h"
#include <sil.h>

#ifdef __GNUC__
#include "../cdefBF527.h"		/* gnu tool chain */
#elif defined(__ECC__)
#include <cdefBF527.h>				/* VisualDSP++ */
#include <sys/exception.h>
#include <ccblkfn.h>
#include <sysreg.h>
#else
#error "Compiler is not supported"
#endif




/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{

	/*
	 *  PLL������
	 *
	 */
	/*
	 *  SSELVAL, CSELVAL��board_config.h�ˤ������
	 */
#ifndef FORCE_PLL_INITIALIZE
	 	// PLL������ͤΤޤޤǤ��ꡢ���ġ�SDRAM��������Ǥʤ����PLL����������
	 if ( ( *pPLL_CTL == 0x0A00 ) && ( !(*pEBIU_SDBCTL & EBE ) ) )
#endif
	 {

		*pSIC_IWR0 = IWR_ENABLE(0);				// PLL�Τ�IWR�����
		*pSIC_IWR1 = IWR_DISABLE_ALL;
		*pPLL_LOCKCNT = 0x0200; /* anomaly 05000430 */
#if CSELVAL == 1
		*pPLL_DIV = CSEL_DIV1 | SET_SSEL(SSELVAL);
#elif CSELVAL == 2
		*pPLL_DIV = CSEL_DIV2 | SET_SSEL(SSELVAL);
#elif CSELVAL == 4
		*pPLL_DIV = CSEL_DIV4 | SET_SSEL(SSELVAL);
#elif CSELVAL == 8
		*pPLL_DIV = CSEL_DIV8 | SET_SSEL(SSELVAL);
#else
#error Wrong CSELVAL. Must be one of 1,2,4,8.
#endif

		*pPLL_CTL = MSELVAL << 9;

		asm("cli r0; csync; idle; sti r0;": : :"R0");
		*pSIC_IWR0 = IWR_ENABLE_ALL;
		*pSIC_IWR1 = IWR_ENABLE_ALL;
	}

}

        // priority_mask�ϡ�event���0..15�˱�����
        // �������׵�Υӥåȥޥåפ��ݻ����롣
IMS priority_mask[16]={
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x0007800000003FFFULL,
0x000000000000C000ULL,
0x00000000000F0000ULL,
0x00F8000003F00000ULL,
0x00000000FC000000ULL,
0x000003FF00000000ULL,
0x00007C0000000000ULL,
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
	unsigned int i, priority, iar;
	IMS device;


	/*
 *  �����߽�̤��Ȥ�ISR�ӥåȥޥåפκ���
 *  SIC_IARx������Ϥ�����ʬ������˺Ѥޤ��뤳��
 */

        // priority_mask�ϡ�event���0..15�˱�����
        // �������׵�Υӥåȥޥåפ��ݻ����롣
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

    iar = *pSIC_IAR3;
    INSTALL_PRIORITY

	iar = *pSIC_IAR4;
	INSTALL_PRIORITY

	iar = *pSIC_IAR5;
	INSTALL_PRIORITY

	iar = *pSIC_IAR6;
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

		SIL_LOC_INT();			// �����������ߤޤǶػߤ���
		if (intno < 32) {
			mask = 1 << intno;
			*pSIC_IMASK0 |= mask;
		} else {
			mask = 1 << (intno - 32);
			*pSIC_IMASK1 |= mask;
		}
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
		if (intno < 32) {
			mask = 1 << intno;
			mask = ~mask;
			*pSIC_IMASK0 &= mask;
		} else {
			mask = 1 << (intno - 32);
			mask = ~mask;
			*pSIC_IMASK1 &= mask;
		}
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
 * ER chg_ims( IMS ims )
{
	*pSIC_IMASK0 = ims;
	*pSIC_IMASK1 = ims >> 32;
	return( 0 );
}
*/

extern ER get_ims( IMS * p_ims )
{
	SIL_PRE_LOC;
	SIL_LOC_INT();
	*p_ims = *pSIC_IMASK0 | (UD)*pSIC_IMASK1 << 32;
	SIL_UNL_INT();
	return( 0 );;
}


/*
 *  �����ߤ�ǥХ����˳�����Ƥ�
 */
void device_dispatcher(  unsigned int priority, unsigned int imask )
{
	unsigned int candidates, device;
	unsigned int offset;

	candidates = (UW)(priority_mask[priority] >> 32) & *pSIC_ISR1 & *pSIC_IMASK1;	// ���ߤΥץ饤����ƥ��������������߸������ꤹ��
	if (candidates != 0) {
		offset = 32;
	} else {
		candidates = (UW)priority_mask[priority] & *pSIC_ISR0 & *pSIC_IMASK0;
		offset = 0;
	}

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
		dev_vector[device + offset]();
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



