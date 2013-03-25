/*
* GENERATED FILE - DO NOT EDIT
* (C) Code Red Technologies Ltd, 2008-10
* Generated linker script file for LPC1768
* Created from nxp_lpc17_c.ld (vLPCXpresso 3.8 (2 [Build 129] [31/01/2011] ))
* By LPCXpresso 3.8.2 [Build 129] [31/01/2011]  on Sat Feb 26 21:43:28 JST 2011
*/

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);


MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x0, LENGTH = 0x20000 /* 128k */
  RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 /* 32k */
  RamAHB32 (rwx) : ORIGIN = 0x2007c000, LENGTH = 0x8000 /* 32k */
  CANAccFilterRAM (rwx) : ORIGIN = 0x40038000, LENGTH = 0x800 /* 2k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x0 + 0x80000;
  __top_RamLoc32 = 0x10000000 + 0x8000;
  __top_RamAHB32 = 0x2007c000 + 0x8000;
  __top_CANAccFilterRAM = 0x40038000 + 0x800;

STARTUP(start.o)  /* LPCXpresso IDEの場合、この文があるとビルドに失敗する */
/* ENTRY(_start) */

SECTIONS
{

	/* MAIN TEXT SECTION */	
	.text : ALIGN(4)
	{
		FILL(0xff)
	    _vector_start_lma = ALIGN(8);
		KEEP(*(.vector))
		
		/* Global Section Table */
		. = ALIGN(4) ;
		__section_table_start = .;
		__data_section_table = .;
		LONG(LOADADDR(.data));
		LONG(    ADDR(.data)) ;
		LONG(  SIZEOF(.data));
		LONG(LOADADDR(.data_RAM2));
		LONG(    ADDR(.data_RAM2)) ;
		LONG(  SIZEOF(.data_RAM2));
		LONG(LOADADDR(.data_RAM3));
		LONG(    ADDR(.data_RAM3)) ;
		LONG(  SIZEOF(.data_RAM3));
		__data_section_table_end = .;
		__bss_section_table = .;
		LONG(    ADDR(.bss));
		LONG(  SIZEOF(.bss));
		LONG(    ADDR(.bss_RAM2));
		LONG(  SIZEOF(.bss_RAM2));
		LONG(    ADDR(.bss_RAM3));
		LONG(  SIZEOF(.bss_RAM3));
		__bss_section_table_end = .;
		__section_table_end = . ;
		/* End of Global Section Table */
		

		*(.after_vectors*)

		
		*(.text*)
		*(.rodata .rodata.*)
		. = ALIGN(4);
		
	} > MFlash512

	/*
	 * for exception handling/unwind - some Newlib functions (in common
	 * with C++ and STDC++) use this.
	 */
	.ARM.extab : ALIGN(4)
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > MFlash512
	__exidx_start = .;
	
	.ARM.exidx : ALIGN(4)
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > MFlash512
	__exidx_end = .;
	
	_etext = .;
		
	
	.data_RAM2 : ALIGN(4)
	{
	   FILL(0xff)
		*(.data.$RAM2*)
		*(.data.$RamAHB32*)
	   . = ALIGN(4) ;
	} > RamAHB32 AT>MFlash512
	
	.data_RAM3 : ALIGN(4)
	{
	   FILL(0xff)
		*(.data.$RAM3*)
		*(.data.$CANAccFilterRAM*)
	   . = ALIGN(4) ;
	} > CANAccFilterRAM AT>MFlash512
	
	/* MAIN DATA SECTION */

	.uninit_RESERVED : ALIGN(4)
	{
		KEEP(*(.bss.$RESERVED*))
	} > RamLoc32

    __idata_start = .;
	.data : ALIGN(4)
	{
		FILL(0xff)
		_data = .;
       __data_start = .;
		*(vtable)
		*(.data*)
		. = ALIGN(4) ;
		_edata = .;
	} > RamLoc32 AT>MFlash512
   __idata_end = __idata_start + SIZEOF(.data);

	
	.bss_RAM2 : ALIGN(4)
	{
		*(.bss.$RAM2*)
		*(.bss.$RamAHB32*)
	   . = ALIGN(4) ;
	} > RamAHB32
	
	.bss_RAM3 : ALIGN(4)
	{
		*(.bss.$RAM3*)
		*(.bss.$CANAccFilterRAM*)
	   . = ALIGN(4) ;
	} > CANAccFilterRAM

	/* MAIN BSS SECTION */
	.bss : ALIGN(4)
	{
		_bss = .;
		__bss_start = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4) ;
		_ebss = .;
		__bss_end = .;
		PROVIDE(end = .);
	} > RamLoc32
	
	PROVIDE(_pvHeapStart = .);
	PROVIDE(_vStackTop = __top_RamLoc32 - 0);
}
