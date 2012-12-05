#include "jsp_kernel.h"

#ifdef __GNUC__
#include "../cdefbf532.h"       /* gnu tool chain */
#elif defined(__ECC__)
#error "Don't use sys_debugboot.c for VDSP "
#else
#error "Compiler is not supported"
#endif


/*
* gdbserver���������åȤΥꥻ�åȵ�ǽ���󶡤��ʤ����ᡢgdb��ͳ�ǥ������å�
* �˥��ץ�å����������������ɤ����������ư��ʤ����Ȥ����롣
* ���Υ롼����ϥ������åȤ���٤����ꥻ�åȤ��롣
*/
void boot_for_gdb(void)
{
    if ( ! (*pSWRST & RESET_SOFTWARE ) ){   /* ���եȥ������ꥻ�åȤ������Ƥ��ʤ��ʤ�ʲ��¹ԡ�*/
        *pSWRST = 0x07;                     /* ��¢�ڥ�ե����Υꥻ�åȡ�*/
        asm volatile( "ssync;" );
        *pSWRST = 0x00;                     /* ��¢�ڥ�ե����Υꥻ�åȲ���� */
        asm volatile( "ssync;" );
        *pSYSCR |= 0x10;                    /* no boot on core reset */
        asm volatile( "ssync;" );
        asm volatile( "raise 1;" );         /* �����ꥻ�å� */
        while( 1 )
            ;                               /*�ꥻ�åȤ�ȯ������ޤǥ롼��*/ 
    }
}
