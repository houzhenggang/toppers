MEMORY
{
	VECTOR_RESET : ORIGIN = 0xa0200200, LENGTH = 0x00000200
	VECTOR_TLB   : ORIGIN = 0x80000000, LENGTH = 0x00000080
	VECTOR_XTLB  : ORIGIN = 0x80000080, LENGTH = 0x00000080
	VECTOR_CACHE : ORIGIN = 0xa0000100, LENGTH = 0x00000080
	VECTOR_OTHER : ORIGIN = 0x80000180, LENGTH = 0x00000080
	RO_KSEG1     : ORIGIN = 0xa0200400, LENGTH = 0x0000fc00
	RO_KSEG0     : ORIGIN = 0x80220000, LENGTH = 0x000e0000
	RW_KSEG1     : ORIGIN = 0xa0300000, LENGTH = 0x00010000
	RW_KSEG0     : ORIGIN = 0x80320000, LENGTH = 0x000e0000
}

PROVIDE(_stack_top = 0x80320000 - 16);
PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);

SECTIONS
{
	.vector_reset :
	{
		*(.vector_reset)
	} > VECTOR_RESET

	.vector_tlb :
	{
		*(.vector_tlb)
	} > VECTOR_TLB

	.vector_xtlb :
	{
		*(.vector_xtlb)
	} > VECTOR_XTLB

	.vector_cache :
	{
		*(.vector_cache)
	} > VECTOR_CACHE

	.vector_other :
	{
		*(.vector_other)
	} > VECTOR_OTHER

	.text_uncached :		/* キャッシュ初期化などを含む */
	{
		*(.text_uncached)
	} > RO_KSEG1

	.text :
	{
		_stext = . ;
		*(.text)
		_etext  = . ;
	} > RO_KSEG0

	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
	} > RO_KSEG0

	. = ALIGN(4);
	__idata_start = .;
	.data : AT ( __idata_start )
	{
		__data_start  = . ;
		*(.data)
	} > RW_KSEG0

	/* 理由は良く分からないけれども、こう書くのが一般的らしい。 */
	_gp = . + 0x8000;

	/* sdata セクションは chk で引っかかるので、保留。
	   コンパイル時に、-G 0 オプションで避けています。 */

	__isdata_start = .;
	.sdata . : AT ( __idata_start + SIZEOF(.data) )
	{
		*(.lit8) 
		*(.lit4) 
		*(.sdata) 
		. = ALIGN(4);
	} > RW_KSEG0
	__idata_end = __idata_start + SIZEOF(.data) + SIZEOF(.sdata);

	__bss_start = .	;

	.sbss : 
	{
		_fbss = . ;
		*(.sbss)
		*(.scommon)
	} > RW_KSEG0

	.bss : 
	{
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = .;
		_end = . ;
	} > RW_KSEG0

	PROVIDE (end = .);

	.comment 	0 : { *(.comment) }
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
}

PROVIDE(memcpy = _dummy_memcpy);
