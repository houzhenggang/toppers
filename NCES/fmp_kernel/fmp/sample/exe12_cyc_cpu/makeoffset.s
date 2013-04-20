	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
	.file	"makeoffset.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.global	makeoffset
	.type	makeoffset, %function
makeoffset:
.LFB81:
	.file 1 "../../arch/arm_gcc/common/core_makeoffset.c"
	.loc 1 59 0
	.cfi_startproc
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 60 0
@ 60 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TCB_p_tinib = #8
@ 0 "" 2
	.loc 1 61 0
@ 61 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TCB_texptn = #16
@ 0 "" 2
	.loc 1 62 0
@ 62 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TCB_sp = #24
@ 0 "" 2
	.loc 1 63 0
@ 63 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TCB_pc = #28
@ 0 "" 2
	.loc 1 65 0
@ 65 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TINIB_exinf = #4
@ 0 "" 2
	.loc 1 66 0
@ 66 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF TINIB_task = #8
@ 0 "" 2
	.loc 1 68 0
@ 68 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_p_runtsk = #16
@ 0 "" 2
	.loc 1 69 0
@ 69 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_p_schedtsk = #20
@ 0 "" 2
	.loc 1 70 0
@ 70 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_reqflg = #24
@ 0 "" 2
	.loc 1 71 0
@ 71 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_disdsp = #88
@ 0 "" 2
	.loc 1 72 0
@ 72 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_dspflg = #28
@ 0 "" 2
	.loc 1 73 0
@ 73 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_locspnid = #32
@ 0 "" 2
	.loc 1 75 0
@ 75 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_p_firstlock = #8
@ 0 "" 2
	.loc 1 76 0
@ 76 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	OFFSET_DEF PCB_p_secondlock = #12
@ 0 "" 2
	.loc 1 78 0
	bx	lr
	.cfi_endproc
.LFE81:
	.size	makeoffset, .-makeoffset
	.align	2
	.global	sil_endian
	.type	sil_endian, %function
sil_endian:
.LFB82:
	.loc 1 82 0
	.cfi_startproc
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 87 0
@ 87 "../../arch/arm_gcc/common/core_makeoffset.c" 1
	SIL_ENDIAN = LITTLE
@ 0 "" 2
	.loc 1 90 0
	bx	lr
	.cfi_endproc
.LFE82:
	.size	sil_endian, .-sil_endian
	.align	2
	.global	target_makeoffset
	.type	target_makeoffset, %function
target_makeoffset:
.LFB83:
	.file 2 "../../target/at91skyeye_gcc/makeoffset.c"
	.loc 2 48 0
	.cfi_startproc
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 2 49 0
@ 49 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_excpt_nest_count = #68
@ 0 "" 2
	.loc 2 50 0
@ 50 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_istkpt = #72
@ 0 "" 2
	.loc 2 51 0
@ 51 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_p_exch_table = #76
@ 0 "" 2
	.loc 2 53 0
@ 53 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_idf = #44
@ 0 "" 2
	.loc 2 54 0
@ 54 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_ipm = #48
@ 0 "" 2
	.loc 2 55 0
@ 55 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_p_ipm_mask_table = #56
@ 0 "" 2
	.loc 2 56 0
@ 56 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_p_inh_table = #60
@ 0 "" 2
	.loc 2 57 0
@ 57 "../../target/at91skyeye_gcc/makeoffset.c" 1
	OFFSET_DEF PCB_p_inh_ipm_table = #64
@ 0 "" 2
	.loc 2 58 0
	bx	lr
	.cfi_endproc
.LFE83:
	.size	target_makeoffset, .-target_makeoffset
	.global	BIT_REF_4
	.global	BIT_REF_2
	.global	BIT_REF_1
	.global	BIT_LB_TCB_enatex
	.data
	.align	2
	.type	BIT_REF_4, %object
	.size	BIT_REF_4, 4
BIT_REF_4:
	.word	305419896
	.type	BIT_REF_2, %object
	.size	BIT_REF_2, 2
BIT_REF_2:
	.short	4660
	.type	BIT_REF_1, %object
	.size	BIT_REF_1, 1
BIT_REF_1:
	.byte	18
	.space	1
	.type	BIT_LB_TCB_enatex, %object
	.size	BIT_LB_TCB_enatex, 80
BIT_LB_TCB_enatex:
	.word	0
	.word	0
	.word	0
	.byte	0
	.byte	0
	.byte	4
	.space	1
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.text
.Letext0:
	.file 3 "../../arch/gcc/tool_stddef.h"
	.file 4 "../../include/t_stddef.h"
	.file 5 "../../include/kernel.h"
	.file 6 "../../arch/arm_gcc/common/core_pcb.h"
	.file 7 "../../kernel/pcb.h"
	.file 8 "../../target/at91skyeye_gcc/target_pcb.h"
	.file 9 "../../include/queue.h"
	.file 10 "../../kernel/task.h"
	.file 11 "../../kernel/time_event.h"
	.file 12 "../../arch/arm_gcc/common/core_config.h"
	.file 13 "../../kernel/winfo.h"
	.file 14 "../../target/at91skyeye_gcc/target_config.h"
	.section	.debug_info
	.4byte	0x9cc
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF147
	.byte	0x1
	.4byte	.LASF148
	.4byte	.LASF149
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x4
	.4byte	.LASF4
	.byte	0x3
	.byte	0x66
	.4byte	0x45
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x4
	.4byte	.LASF5
	.byte	0x3
	.byte	0x69
	.4byte	0x5e
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x4
	.4byte	.LASF7
	.byte	0x3
	.byte	0x6c
	.4byte	0x2c
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x3
	.byte	0x74
	.4byte	0x89
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x4
	.4byte	.LASF12
	.byte	0x3
	.byte	0x75
	.4byte	0x9b
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x5
	.4byte	.LASF26
	.byte	0x4
	.byte	0x4
	.byte	0x5b
	.4byte	0xbd
	.uleb128 0x6
	.4byte	.LASF28
	.byte	0x4
	.byte	0x5b
	.4byte	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x4
	.byte	0x5c
	.4byte	0xc8
	.uleb128 0x7
	.byte	0x4
	.4byte	0xce
	.uleb128 0x8
	.byte	0x1
	.4byte	0xda
	.uleb128 0x9
	.4byte	0xa2
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x4
	.byte	0x63
	.4byte	0x25
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x4
	.byte	0x66
	.4byte	0x25
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x4
	.byte	0x67
	.4byte	0x2c
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x4
	.byte	0x6a
	.4byte	0x9b
	.uleb128 0xa
	.ascii	"ER\000"
	.byte	0x4
	.byte	0x6d
	.4byte	0xe5
	.uleb128 0xa
	.ascii	"ID\000"
	.byte	0x4
	.byte	0x6e
	.4byte	0xe5
	.uleb128 0xa
	.ascii	"ATR\000"
	.byte	0x4
	.byte	0x6f
	.4byte	0xf0
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0x4
	.byte	0x71
	.4byte	0xf0
	.uleb128 0xa
	.ascii	"PRI\000"
	.byte	0x4
	.byte	0x72
	.4byte	0xe5
	.uleb128 0x4
	.4byte	.LASF20
	.byte	0x4
	.byte	0x73
	.4byte	0x90
	.uleb128 0xa
	.ascii	"FP\000"
	.byte	0x4
	.byte	0x7a
	.4byte	0xbd
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0x5
	.byte	0x53
	.4byte	0xf0
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0x5
	.byte	0x54
	.4byte	0xf0
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0x5
	.byte	0x5c
	.4byte	0x171
	.uleb128 0x7
	.byte	0x4
	.4byte	0x177
	.uleb128 0x8
	.byte	0x1
	.4byte	0x183
	.uleb128 0x9
	.4byte	0x7e
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF24
	.byte	0x5
	.byte	0x5d
	.4byte	0x18e
	.uleb128 0x7
	.byte	0x4
	.4byte	0x194
	.uleb128 0x8
	.byte	0x1
	.4byte	0x1a5
	.uleb128 0x9
	.4byte	0x150
	.uleb128 0x9
	.4byte	0x7e
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1ab
	.uleb128 0x8
	.byte	0x1
	.4byte	0x1b7
	.uleb128 0x9
	.4byte	0x1b7
	.byte	0x0
	.uleb128 0xb
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF25
	.byte	0x5
	.byte	0x6c
	.4byte	0x70
	.uleb128 0x5
	.4byte	.LASF27
	.byte	0x4
	.byte	0x5
	.byte	0x76
	.4byte	0x1df
	.uleb128 0x6
	.4byte	.LASF29
	.byte	0x5
	.byte	0x77
	.4byte	0x1df
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1c4
	.uleb128 0x4
	.4byte	.LASF30
	.byte	0x5
	.byte	0x78
	.4byte	0x1c4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1e5
	.uleb128 0xa
	.ascii	"PCB\000"
	.byte	0x6
	.byte	0x34
	.4byte	0x201
	.uleb128 0x5
	.4byte	.LASF31
	.byte	0xdc
	.byte	0x7
	.byte	0x3e
	.4byte	0x2ee
	.uleb128 0x6
	.4byte	.LASF32
	.byte	0x7
	.byte	0x43
	.4byte	0x3d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF33
	.byte	0x7
	.byte	0x4a
	.4byte	0x3d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF34
	.byte	0x7
	.byte	0x51
	.4byte	0x595
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.4byte	.LASF35
	.byte	0x7
	.byte	0x56
	.4byte	0x595
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF36
	.byte	0x7
	.byte	0x67
	.4byte	0x59b
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x6
	.4byte	.LASF37
	.byte	0x7
	.byte	0x72
	.4byte	0x59b
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x6
	.4byte	.LASF38
	.byte	0x7
	.byte	0x7a
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x6
	.4byte	.LASF39
	.byte	0x7
	.byte	0x82
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x6
	.4byte	.LASF40
	.byte	0x7
	.byte	0x8a
	.4byte	0x110
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x6
	.4byte	.LASF41
	.byte	0x7
	.byte	0x96
	.4byte	0x53
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x6
	.4byte	.LASF42
	.byte	0x7
	.byte	0x9b
	.4byte	0x5a1
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x6
	.4byte	.LASF43
	.byte	0x7
	.byte	0xa1
	.4byte	0x3c6
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x6
	.4byte	.LASF44
	.byte	0x7
	.byte	0xad
	.4byte	0x110
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x6
	.4byte	.LASF45
	.byte	0x7
	.byte	0xb5
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x6
	.4byte	.LASF46
	.byte	0x7
	.byte	0xbc
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x6
	.4byte	.LASF47
	.byte	0x7
	.byte	0xc9
	.4byte	0x5a7
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.byte	0x0
	.uleb128 0x5
	.4byte	.LASF48
	.byte	0xc
	.byte	0x6
	.byte	0x39
	.4byte	0x325
	.uleb128 0x6
	.4byte	.LASF49
	.byte	0x6
	.byte	0x3d
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF50
	.byte	0x6
	.byte	0x42
	.4byte	0x325
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF51
	.byte	0x6
	.byte	0x47
	.4byte	0x32b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1b9
	.uleb128 0x7
	.byte	0x4
	.4byte	0x331
	.uleb128 0xc
	.4byte	0x146
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x6
	.byte	0x48
	.4byte	0x2ee
	.uleb128 0x5
	.4byte	.LASF53
	.byte	0x24
	.byte	0x8
	.byte	0x43
	.4byte	0x3b0
	.uleb128 0xd
	.ascii	"idf\000"
	.byte	0x8
	.byte	0x47
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xd
	.ascii	"ipm\000"
	.byte	0x8
	.byte	0x4c
	.4byte	0x130
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF54
	.byte	0x8
	.byte	0x51
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.4byte	.LASF55
	.byte	0x8
	.byte	0x56
	.4byte	0x3b0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF56
	.byte	0x8
	.byte	0x5b
	.4byte	0x32b
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x6
	.4byte	.LASF57
	.byte	0x8
	.byte	0x60
	.4byte	0x3bb
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x6
	.4byte	.LASF58
	.byte	0x8
	.byte	0x65
	.4byte	0x336
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x3b6
	.uleb128 0xc
	.4byte	0x65
	.uleb128 0x7
	.byte	0x4
	.4byte	0x3c1
	.uleb128 0xc
	.4byte	0x130
	.uleb128 0x4
	.4byte	.LASF59
	.byte	0x8
	.byte	0x66
	.4byte	0x341
	.uleb128 0x4
	.4byte	.LASF60
	.byte	0x8
	.byte	0x6b
	.4byte	0x65
	.uleb128 0x5
	.4byte	.LASF61
	.byte	0x8
	.byte	0x9
	.byte	0x3f
	.4byte	0x405
	.uleb128 0x6
	.4byte	.LASF62
	.byte	0x9
	.byte	0x40
	.4byte	0x405
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF63
	.byte	0x9
	.byte	0x41
	.4byte	0x405
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x3dc
	.uleb128 0x4
	.4byte	.LASF64
	.byte	0x9
	.byte	0x42
	.4byte	0x3dc
	.uleb128 0xa
	.ascii	"TCB\000"
	.byte	0x7
	.byte	0x38
	.4byte	0x421
	.uleb128 0x5
	.4byte	.LASF65
	.byte	0x50
	.byte	0xa
	.byte	0xc7
	.4byte	0x537
	.uleb128 0x6
	.4byte	.LASF66
	.byte	0xa
	.byte	0xc8
	.4byte	0x40b
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF67
	.byte	0xa
	.byte	0xc9
	.4byte	0x8cf
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.4byte	.LASF68
	.byte	0xa
	.byte	0xcc
	.4byte	0x3a
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF69
	.byte	0xa
	.byte	0xd1
	.4byte	0x3a
	.byte	0x2
	.byte	0x23
	.uleb128 0xd
	.uleb128 0xe
	.4byte	.LASF70
	.byte	0xa
	.byte	0xd6
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xe
	.4byte	.LASF71
	.byte	0xa
	.byte	0xd7
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xe
	.4byte	.LASF72
	.byte	0xa
	.byte	0xd8
	.4byte	0x2c
	.byte	0x4
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF73
	.byte	0xa
	.byte	0xda
	.4byte	0x150
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x6
	.4byte	.LASF74
	.byte	0xa
	.byte	0xdc
	.4byte	0x8da
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x6
	.4byte	.LASF75
	.byte	0xa
	.byte	0xde
	.4byte	0x5de
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x6
	.4byte	.LASF76
	.byte	0xa
	.byte	0xe0
	.4byte	0x110
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x6
	.4byte	.LASF77
	.byte	0xa
	.byte	0xe3
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x6
	.4byte	.LASF78
	.byte	0xa
	.byte	0xe4
	.4byte	0xda
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x6
	.4byte	.LASF79
	.byte	0xa
	.byte	0xe5
	.4byte	0xf0
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xf
	.4byte	.LASF80
	.byte	0xa
	.2byte	0x104
	.4byte	0x106
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xf
	.4byte	.LASF81
	.byte	0xa
	.2byte	0x106
	.4byte	0x636
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xf
	.4byte	.LASF82
	.byte	0xa
	.2byte	0x108
	.4byte	0x8e0
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xf
	.4byte	.LASF83
	.byte	0xa
	.2byte	0x10a
	.4byte	0x820
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF84
	.byte	0x7
	.byte	0x39
	.4byte	0x542
	.uleb128 0x5
	.4byte	.LASF85
	.byte	0x14
	.byte	0xb
	.byte	0x53
	.4byte	0x595
	.uleb128 0x6
	.4byte	.LASF86
	.byte	0xb
	.byte	0x5a
	.4byte	0x5e9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF87
	.byte	0xb
	.byte	0x5f
	.4byte	0x5e9
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF88
	.byte	0xb
	.byte	0x64
	.4byte	0x5e9
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.4byte	.LASF89
	.byte	0xb
	.byte	0x75
	.4byte	0xf0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF90
	.byte	0xb
	.byte	0x7a
	.4byte	0x67b
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x3d1
	.uleb128 0x7
	.byte	0x4
	.4byte	0x416
	.uleb128 0x7
	.byte	0x4
	.4byte	0x537
	.uleb128 0x10
	.4byte	0x40b
	.4byte	0x5b7
	.uleb128 0x11
	.4byte	0x2c
	.byte	0xf
	.byte	0x0
	.uleb128 0x5
	.4byte	.LASF91
	.byte	0x8
	.byte	0xc
	.byte	0x6c
	.4byte	0x5de
	.uleb128 0xd
	.ascii	"sp\000"
	.byte	0xc
	.byte	0x6d
	.4byte	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xd
	.ascii	"pc\000"
	.byte	0xc
	.byte	0x6e
	.4byte	0x146
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF92
	.byte	0xc
	.byte	0x6f
	.4byte	0x5b7
	.uleb128 0x4
	.4byte	.LASF93
	.byte	0xb
	.byte	0x3b
	.4byte	0xfb
	.uleb128 0x4
	.4byte	.LASF94
	.byte	0xb
	.byte	0x40
	.4byte	0x1a5
	.uleb128 0x5
	.4byte	.LASF95
	.byte	0xc
	.byte	0xb
	.byte	0x42
	.4byte	0x636
	.uleb128 0x6
	.4byte	.LASF96
	.byte	0xb
	.byte	0x43
	.4byte	0xf0
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF97
	.byte	0xb
	.byte	0x44
	.4byte	0x5f4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xd
	.ascii	"arg\000"
	.byte	0xb
	.byte	0x45
	.4byte	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF98
	.byte	0xb
	.byte	0x46
	.4byte	0x5ff
	.uleb128 0x5
	.4byte	.LASF99
	.byte	0x8
	.byte	0xb
	.byte	0x4b
	.4byte	0x66a
	.uleb128 0x6
	.4byte	.LASF100
	.byte	0xb
	.byte	0x4c
	.4byte	0x5e9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF101
	.byte	0xb
	.byte	0x4d
	.4byte	0x66a
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x636
	.uleb128 0x4
	.4byte	.LASF102
	.byte	0xb
	.byte	0x4e
	.4byte	0x641
	.uleb128 0x7
	.byte	0x4
	.4byte	0x670
	.uleb128 0x5
	.4byte	.LASF103
	.byte	0x8
	.byte	0xd
	.byte	0x40
	.4byte	0x6aa
	.uleb128 0x6
	.4byte	.LASF104
	.byte	0xd
	.byte	0x41
	.4byte	0x11a
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF105
	.byte	0xd
	.byte	0x43
	.4byte	0x595
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF106
	.byte	0xd
	.byte	0x45
	.4byte	0x681
	.uleb128 0x5
	.4byte	.LASF107
	.byte	0xc
	.byte	0xd
	.byte	0x4a
	.4byte	0x6de
	.uleb128 0x6
	.4byte	.LASF108
	.byte	0xd
	.byte	0x4b
	.4byte	0x40b
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF109
	.byte	0xd
	.byte	0x4c
	.4byte	0x6de
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x6e4
	.uleb128 0xc
	.4byte	0x6aa
	.uleb128 0x4
	.4byte	.LASF110
	.byte	0xd
	.byte	0x50
	.4byte	0x6b5
	.uleb128 0x5
	.4byte	.LASF111
	.byte	0xc
	.byte	0xd
	.byte	0x58
	.4byte	0x72b
	.uleb128 0x6
	.4byte	.LASF112
	.byte	0xd
	.byte	0x59
	.4byte	0x15b
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF113
	.byte	0xd
	.byte	0x5a
	.4byte	0x125
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF114
	.byte	0xd
	.byte	0x5b
	.4byte	0x15b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF115
	.byte	0xd
	.byte	0x5c
	.4byte	0x6f4
	.uleb128 0x5
	.4byte	.LASF116
	.byte	0x4
	.byte	0xd
	.byte	0x64
	.4byte	0x751
	.uleb128 0x6
	.4byte	.LASF117
	.byte	0xd
	.byte	0x65
	.4byte	0x7e
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF118
	.byte	0xd
	.byte	0x66
	.4byte	0x736
	.uleb128 0x5
	.4byte	.LASF119
	.byte	0x8
	.byte	0xd
	.byte	0x6e
	.4byte	0x785
	.uleb128 0x6
	.4byte	.LASF117
	.byte	0xd
	.byte	0x6f
	.4byte	0x7e
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF120
	.byte	0xd
	.byte	0x70
	.4byte	0x130
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF121
	.byte	0xd
	.byte	0x71
	.4byte	0x75c
	.uleb128 0x5
	.4byte	.LASF122
	.byte	0x4
	.byte	0xd
	.byte	0x76
	.4byte	0x7ab
	.uleb128 0x6
	.4byte	.LASF123
	.byte	0xd
	.byte	0x77
	.4byte	0x1f0
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF124
	.byte	0xd
	.byte	0x78
	.4byte	0x790
	.uleb128 0x5
	.4byte	.LASF125
	.byte	0x4
	.byte	0xd
	.byte	0x7d
	.4byte	0x7d1
	.uleb128 0xd
	.ascii	"blk\000"
	.byte	0xd
	.byte	0x7e
	.4byte	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF126
	.byte	0xd
	.byte	0x7f
	.4byte	0x7b6
	.uleb128 0x12
	.4byte	.LASF83
	.byte	0xc
	.byte	0xd
	.byte	0x84
	.4byte	0x820
	.uleb128 0x13
	.ascii	"flg\000"
	.byte	0xd
	.byte	0x85
	.4byte	0x72b
	.uleb128 0x13
	.ascii	"dtq\000"
	.byte	0xd
	.byte	0x86
	.4byte	0x751
	.uleb128 0x13
	.ascii	"pdq\000"
	.byte	0xd
	.byte	0x87
	.4byte	0x785
	.uleb128 0x13
	.ascii	"mbx\000"
	.byte	0xd
	.byte	0x88
	.4byte	0x7ab
	.uleb128 0x13
	.ascii	"mpf\000"
	.byte	0xd
	.byte	0x89
	.4byte	0x7d1
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF127
	.byte	0xd
	.byte	0x8a
	.4byte	0x7dc
	.uleb128 0x5
	.4byte	.LASF128
	.byte	0x28
	.byte	0xa
	.byte	0x92
	.4byte	0x8c4
	.uleb128 0x6
	.4byte	.LASF129
	.byte	0xa
	.byte	0x93
	.4byte	0x11a
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.4byte	.LASF130
	.byte	0xa
	.byte	0x94
	.4byte	0x7e
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x6
	.4byte	.LASF131
	.byte	0xa
	.byte	0x95
	.4byte	0x166
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x6
	.4byte	.LASF132
	.byte	0xa
	.byte	0x96
	.4byte	0xf0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x6
	.4byte	.LASF133
	.byte	0xa
	.byte	0x9a
	.4byte	0x13b
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xd
	.ascii	"stk\000"
	.byte	0xa
	.byte	0x9b
	.4byte	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x6
	.4byte	.LASF134
	.byte	0xa
	.byte	0x9e
	.4byte	0x11a
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x6
	.4byte	.LASF135
	.byte	0xa
	.byte	0x9f
	.4byte	0x183
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x6
	.4byte	.LASF136
	.byte	0xa
	.byte	0xa0
	.4byte	0x110
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x6
	.4byte	.LASF137
	.byte	0xa
	.byte	0xa1
	.4byte	0xf0
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x4
	.4byte	.LASF138
	.byte	0xa
	.byte	0xa2
	.4byte	0x82b
	.uleb128 0x7
	.byte	0x4
	.4byte	0x8d5
	.uleb128 0xc
	.4byte	0x8c4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1f6
	.uleb128 0x7
	.byte	0x4
	.4byte	0x6e9
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF139
	.byte	0x1
	.byte	0x3a
	.byte	0x1
	.4byte	.LFB81
	.4byte	.LFE81
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF140
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF141
	.byte	0x2
	.byte	0x2f
	.byte	0x1
	.4byte	.LFB83
	.4byte	.LFE83
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x10
	.4byte	0x8da
	.4byte	0x92d
	.uleb128 0x15
	.byte	0x0
	.uleb128 0x16
	.4byte	.LASF142
	.byte	0x7
	.byte	0xcf
	.4byte	0x93a
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	0x922
	.uleb128 0x10
	.4byte	0x3b0
	.4byte	0x94f
	.uleb128 0x11
	.4byte	0x2c
	.byte	0x1
	.byte	0x0
	.uleb128 0x17
	.4byte	.LASF55
	.byte	0xe
	.2byte	0x124
	.4byte	0x95d
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	0x93f
	.uleb128 0x16
	.4byte	.LASF142
	.byte	0x7
	.byte	0xcf
	.4byte	0x96f
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	0x922
	.uleb128 0x17
	.4byte	.LASF55
	.byte	0xe
	.2byte	0x124
	.4byte	0x982
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	0x93f
	.uleb128 0x18
	.4byte	.LASF143
	.byte	0x1
	.byte	0x5c
	.4byte	0x65
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	BIT_REF_4
	.uleb128 0x18
	.4byte	.LASF144
	.byte	0x1
	.byte	0x5d
	.4byte	0x53
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	BIT_REF_2
	.uleb128 0x18
	.4byte	.LASF145
	.byte	0x1
	.byte	0x5e
	.4byte	0x3a
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	BIT_REF_1
	.uleb128 0x18
	.4byte	.LASF146
	.byte	0x1
	.byte	0x64
	.4byte	0x416
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	BIT_LB_TCB_enatex
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x82
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x9d0
	.4byte	0x8e6
	.ascii	"makeoffset\000"
	.4byte	0x8fa
	.ascii	"sil_endian\000"
	.4byte	0x90e
	.ascii	"target_makeoffset\000"
	.4byte	0x987
	.ascii	"BIT_REF_4\000"
	.4byte	0x999
	.ascii	"BIT_REF_2\000"
	.4byte	0x9ab
	.ascii	"BIT_REF_1\000"
	.4byte	0x9bd
	.ascii	"BIT_LB_TCB_enatex\000"
	.4byte	0x0
	.section	.debug_pubtypes,"",%progbits
	.4byte	0x39e
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x9d0
	.4byte	0x3a
	.ascii	"uint8_t\000"
	.4byte	0x53
	.ascii	"uint16_t\000"
	.4byte	0x65
	.ascii	"uint32_t\000"
	.4byte	0x7e
	.ascii	"intptr_t\000"
	.4byte	0x90
	.ascii	"uintptr_t\000"
	.4byte	0xa2
	.ascii	"TOPPERS_dummy_t\000"
	.4byte	0xbd
	.ascii	"TOPPERS_fp_t\000"
	.4byte	0xda
	.ascii	"bool_t\000"
	.4byte	0xe5
	.ascii	"int_t\000"
	.4byte	0xf0
	.ascii	"uint_t\000"
	.4byte	0xfb
	.ascii	"ulong_t\000"
	.4byte	0x106
	.ascii	"ER\000"
	.4byte	0x110
	.ascii	"ID\000"
	.4byte	0x11a
	.ascii	"ATR\000"
	.4byte	0x125
	.ascii	"MODE\000"
	.4byte	0x130
	.ascii	"PRI\000"
	.4byte	0x13b
	.ascii	"SIZE\000"
	.4byte	0x146
	.ascii	"FP\000"
	.4byte	0x150
	.ascii	"TEXPTN\000"
	.4byte	0x15b
	.ascii	"FLGPTN\000"
	.4byte	0x166
	.ascii	"TASK\000"
	.4byte	0x183
	.ascii	"TEXRTN\000"
	.4byte	0x1b9
	.ascii	"STK_T\000"
	.4byte	0x1c4
	.ascii	"t_msg\000"
	.4byte	0x1e5
	.ascii	"T_MSG\000"
	.4byte	0x1f6
	.ascii	"PCB\000"
	.4byte	0x2ee
	.ascii	"arm_processor_control_block\000"
	.4byte	0x336
	.ascii	"APCB\000"
	.4byte	0x341
	.ascii	"target_processor_control_block\000"
	.4byte	0x3c6
	.ascii	"TPCB\000"
	.4byte	0x3d1
	.ascii	"LOCK\000"
	.4byte	0x3dc
	.ascii	"queue\000"
	.4byte	0x40b
	.ascii	"QUEUE\000"
	.4byte	0x416
	.ascii	"TCB\000"
	.4byte	0x537
	.ascii	"TEVTCB\000"
	.4byte	0x201
	.ascii	"processor_control_block\000"
	.4byte	0x5b7
	.ascii	"task_context_block\000"
	.4byte	0x5de
	.ascii	"TSKCTXB\000"
	.4byte	0x5e9
	.ascii	"EVTTIM\000"
	.4byte	0x5f4
	.ascii	"CBACK\000"
	.4byte	0x5ff
	.ascii	"time_event_block\000"
	.4byte	0x636
	.ascii	"TMEVTB\000"
	.4byte	0x641
	.ascii	"time_event_node\000"
	.4byte	0x670
	.ascii	"TMEVTN\000"
	.4byte	0x542
	.ascii	"time_event_control_block\000"
	.4byte	0x681
	.ascii	"wait_object_initialization_block\000"
	.4byte	0x6aa
	.ascii	"WOBJINIB\000"
	.4byte	0x6b5
	.ascii	"wait_object_control_block\000"
	.4byte	0x6e9
	.ascii	"WOBJCB\000"
	.4byte	0x6f4
	.ascii	"winfo_flg\000"
	.4byte	0x72b
	.ascii	"WINFO_FLG\000"
	.4byte	0x736
	.ascii	"winfo_dtq\000"
	.4byte	0x751
	.ascii	"WINFO_DTQ\000"
	.4byte	0x75c
	.ascii	"winfo_pdq\000"
	.4byte	0x785
	.ascii	"WINFO_PDQ\000"
	.4byte	0x790
	.ascii	"winfo_mbx\000"
	.4byte	0x7ab
	.ascii	"WINFO_MBX\000"
	.4byte	0x7b6
	.ascii	"winfo_mpf\000"
	.4byte	0x7d1
	.ascii	"WINFO_MPF\000"
	.4byte	0x7dc
	.ascii	"winfo_obj\000"
	.4byte	0x820
	.ascii	"WINFO_OBJ\000"
	.4byte	0x82b
	.ascii	"task_initialization_block\000"
	.4byte	0x8c4
	.ascii	"TINIB\000"
	.4byte	0x421
	.ascii	"task_control_block\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",%progbits,1
.LASF50:
	.ascii	"istkpt\000"
.LASF83:
	.ascii	"winfo_obj\000"
.LASF53:
	.ascii	"target_processor_control_block\000"
.LASF68:
	.ascii	"tstat\000"
.LASF12:
	.ascii	"uintptr_t\000"
.LASF115:
	.ascii	"WINFO_FLG\000"
.LASF77:
	.ascii	"pend_relwai\000"
.LASF80:
	.ascii	"wercd\000"
.LASF98:
	.ascii	"TMEVTB\000"
.LASF141:
	.ascii	"target_makeoffset\000"
.LASF94:
	.ascii	"CBACK\000"
.LASF113:
	.ascii	"wfmode\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF16:
	.ascii	"int_t\000"
.LASF72:
	.ascii	"enatex\000"
.LASF102:
	.ascii	"TMEVTN\000"
.LASF127:
	.ascii	"WINFO_OBJ\000"
.LASF93:
	.ascii	"EVTTIM\000"
.LASF119:
	.ascii	"winfo_pdq\000"
.LASF20:
	.ascii	"SIZE\000"
.LASF57:
	.ascii	"_kernel_p_inh_ipm_table\000"
.LASF86:
	.ascii	"_kernel_current_time\000"
.LASF106:
	.ascii	"WOBJINIB\000"
.LASF8:
	.ascii	"long long int\000"
.LASF1:
	.ascii	"signed char\000"
.LASF109:
	.ascii	"p_wobjinib\000"
.LASF149:
	.ascii	"C:\\home\\fmp\\sample\\exe12_cyc_cpu\000"
.LASF15:
	.ascii	"bool_t\000"
.LASF104:
	.ascii	"wobjatr\000"
.LASF48:
	.ascii	"arm_processor_control_block\000"
.LASF17:
	.ascii	"uint_t\000"
.LASF11:
	.ascii	"long int\000"
.LASF121:
	.ascii	"WINFO_PDQ\000"
.LASF125:
	.ascii	"winfo_mpf\000"
.LASF132:
	.ascii	"ipriority\000"
.LASF5:
	.ascii	"uint16_t\000"
.LASF107:
	.ascii	"wait_object_control_block\000"
.LASF144:
	.ascii	"BIT_REF_2\000"
.LASF24:
	.ascii	"TEXRTN\000"
.LASF143:
	.ascii	"BIT_REF_4\000"
.LASF54:
	.ascii	"bitpat_cfgint\000"
.LASF135:
	.ascii	"texrtn\000"
.LASF46:
	.ascii	"disdsp\000"
.LASF47:
	.ascii	"ready_queue\000"
.LASF133:
	.ascii	"stksz\000"
.LASF126:
	.ascii	"WINFO_MPF\000"
.LASF89:
	.ascii	"_kernel_last_index\000"
.LASF45:
	.ascii	"kerflg\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF134:
	.ascii	"texatr\000"
.LASF31:
	.ascii	"processor_control_block\000"
.LASF13:
	.ascii	"long unsigned int\000"
.LASF58:
	.ascii	"arm_pcb\000"
.LASF88:
	.ascii	"_kernel_next_time\000"
.LASF18:
	.ascii	"ulong_t\000"
.LASF101:
	.ascii	"p_tmevtb\000"
.LASF49:
	.ascii	"excpt_nest_count\000"
.LASF43:
	.ascii	"target_pcb\000"
.LASF117:
	.ascii	"data\000"
.LASF55:
	.ascii	"_kernel_p_ipm_mask_table\000"
.LASF6:
	.ascii	"short unsigned int\000"
.LASF122:
	.ascii	"winfo_mbx\000"
.LASF112:
	.ascii	"waiptn\000"
.LASF36:
	.ascii	"p_runtsk\000"
.LASF130:
	.ascii	"exinf\000"
.LASF97:
	.ascii	"callback\000"
.LASF69:
	.ascii	"priority\000"
.LASF56:
	.ascii	"_kernel_p_inh_table\000"
.LASF10:
	.ascii	"intptr_t\000"
.LASF148:
	.ascii	"../../target/at91skyeye_gcc/makeoffset.c\000"
.LASF99:
	.ascii	"time_event_node\000"
.LASF25:
	.ascii	"STK_T\000"
.LASF118:
	.ascii	"WINFO_DTQ\000"
.LASF85:
	.ascii	"time_event_control_block\000"
.LASF90:
	.ascii	"p_tmevt_heap\000"
.LASF87:
	.ascii	"_kernel_min_time\000"
.LASF120:
	.ascii	"datapri\000"
.LASF124:
	.ascii	"WINFO_MBX\000"
.LASF108:
	.ascii	"wait_queue\000"
.LASF32:
	.ascii	"tsk_lock\000"
.LASF23:
	.ascii	"TASK\000"
.LASF79:
	.ascii	"pend_newpri\000"
.LASF28:
	.ascii	"TOPPERS_dummy_field\000"
.LASF82:
	.ascii	"p_wobjcb\000"
.LASF33:
	.ascii	"obj_lock\000"
.LASF100:
	.ascii	"time\000"
.LASF129:
	.ascii	"tskatr\000"
.LASF39:
	.ascii	"dspflg\000"
.LASF42:
	.ascii	"p_tevtcb\000"
.LASF70:
	.ascii	"actque\000"
.LASF21:
	.ascii	"TEXPTN\000"
.LASF95:
	.ascii	"time_event_block\000"
.LASF63:
	.ascii	"p_prev\000"
.LASF73:
	.ascii	"texptn\000"
.LASF103:
	.ascii	"wait_object_initialization_block\000"
.LASF81:
	.ascii	"tmevtb\000"
.LASF78:
	.ascii	"pend_chgpri\000"
.LASF116:
	.ascii	"winfo_dtq\000"
.LASF2:
	.ascii	"unsigned char\000"
.LASF26:
	.ascii	"TOPPERS_dummy_t\000"
.LASF145:
	.ascii	"BIT_REF_1\000"
.LASF140:
	.ascii	"sil_endian\000"
.LASF3:
	.ascii	"short int\000"
.LASF84:
	.ascii	"TEVTCB\000"
.LASF71:
	.ascii	"wupque\000"
.LASF44:
	.ascii	"prcid\000"
.LASF136:
	.ascii	"iaffinity\000"
.LASF62:
	.ascii	"p_next\000"
.LASF67:
	.ascii	"p_tinib\000"
.LASF59:
	.ascii	"TPCB\000"
.LASF51:
	.ascii	"_kernel_p_exch_table\000"
.LASF7:
	.ascii	"uint32_t\000"
.LASF74:
	.ascii	"p_pcb\000"
.LASF139:
	.ascii	"makeoffset\000"
.LASF123:
	.ascii	"pk_msg\000"
.LASF41:
	.ascii	"ready_primap\000"
.LASF14:
	.ascii	"TOPPERS_fp_t\000"
.LASF96:
	.ascii	"index\000"
.LASF60:
	.ascii	"LOCK\000"
.LASF37:
	.ascii	"p_schedtsk\000"
.LASF35:
	.ascii	"p_secondlock\000"
.LASF19:
	.ascii	"MODE\000"
.LASF52:
	.ascii	"APCB\000"
.LASF61:
	.ascii	"queue\000"
.LASF110:
	.ascii	"WOBJCB\000"
.LASF131:
	.ascii	"task\000"
.LASF92:
	.ascii	"TSKCTXB\000"
.LASF27:
	.ascii	"t_msg\000"
.LASF138:
	.ascii	"TINIB\000"
.LASF64:
	.ascii	"QUEUE\000"
.LASF65:
	.ascii	"task_control_block\000"
.LASF66:
	.ascii	"task_queue\000"
.LASF105:
	.ascii	"p_obj_lock\000"
.LASF146:
	.ascii	"BIT_LB_TCB_enatex\000"
.LASF38:
	.ascii	"reqflg\000"
.LASF137:
	.ascii	"affinity_mask\000"
.LASF91:
	.ascii	"task_context_block\000"
.LASF4:
	.ascii	"uint8_t\000"
.LASF142:
	.ascii	"_kernel_p_pcb_table\000"
.LASF75:
	.ascii	"tskctxb\000"
.LASF40:
	.ascii	"locspnid\000"
.LASF30:
	.ascii	"T_MSG\000"
.LASF147:
	.ascii	"GNU C 4.5.1\000"
.LASF111:
	.ascii	"winfo_flg\000"
.LASF29:
	.ascii	"pk_next\000"
.LASF34:
	.ascii	"p_firstlock\000"
.LASF22:
	.ascii	"FLGPTN\000"
.LASF128:
	.ascii	"task_initialization_block\000"
.LASF114:
	.ascii	"flgptn\000"
.LASF76:
	.ascii	"actprc\000"
	.ident	"GCC: (Sourcery G++ Lite 2010.09-51) 4.5.1"
