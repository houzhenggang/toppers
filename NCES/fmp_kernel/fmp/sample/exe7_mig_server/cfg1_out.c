/* cfg1_out.c */
#define TOPPERS_CFG1_OUT  1
#include "kernel/kernel_int.h"
#include "sample1.h"
#include "target_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "target_ipi.h"
#include "logtrace/trace_config.h"


#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include <target_cfg1_out.h>

const uint32_t TOPPERS_cfg_magic_number = 0x12345678;
const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);
const unsigned_t TOPPERS_cfg_CHAR_BIT = CHAR_BIT;
const unsigned_t TOPPERS_cfg_CHAR_MAX = CHAR_MAX;
const unsigned_t TOPPERS_cfg_CHAR_MIN = CHAR_MIN;
const unsigned_t TOPPERS_cfg_SCHAR_MAX = SCHAR_MAX;
const unsigned_t TOPPERS_cfg_SHRT_MAX = SHRT_MAX;
const unsigned_t TOPPERS_cfg_INT_MAX = INT_MAX;
const unsigned_t TOPPERS_cfg_LONG_MAX = LONG_MAX;

const unsigned_t TOPPERS_cfg_TA_NULL = TA_NULL;
const unsigned_t TOPPERS_cfg_TA_ACT = TA_ACT;
const unsigned_t TOPPERS_cfg_TA_TPRI = TA_TPRI;
const unsigned_t TOPPERS_cfg_TA_MPRI = TA_MPRI;
const unsigned_t TOPPERS_cfg_TA_WMUL = TA_WMUL;
const unsigned_t TOPPERS_cfg_TA_CLR = TA_CLR;
const unsigned_t TOPPERS_cfg_TA_STA = TA_STA;
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = TA_NONKERNEL;
const unsigned_t TOPPERS_cfg_TA_ENAINT = TA_ENAINT;
const unsigned_t TOPPERS_cfg_TA_EDGE = TA_EDGE;
const signed_t TOPPERS_cfg_TMIN_TPRI = TMIN_TPRI;
const signed_t TOPPERS_cfg_TMAX_TPRI = TMAX_TPRI;
const signed_t TOPPERS_cfg_TMIN_DPRI = TMIN_DPRI;
const signed_t TOPPERS_cfg_TMAX_DPRI = TMAX_DPRI;
const signed_t TOPPERS_cfg_TMIN_MPRI = TMIN_MPRI;
const signed_t TOPPERS_cfg_TMAX_MPRI = TMAX_MPRI;
const signed_t TOPPERS_cfg_TMIN_ISRPRI = TMIN_ISRPRI;
const signed_t TOPPERS_cfg_TMAX_ISRPRI = TMAX_ISRPRI;
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = TMAX_MAXSEM;
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = TMAX_RELTIM;
const signed_t TOPPERS_cfg_TMIN_INTPRI = TMIN_INTPRI;
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = 
#if defined(OMIT_INITIALIZE_INTERRUPT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = 
#if defined(OMIT_INITIALIZE_EXCEPTION)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_TSKINICTXB = 
#if defined(USE_TSKINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TNUM_PRCID = TNUM_PRCID;
const unsigned_t TOPPERS_cfg_TTYPE_KLOCK = TTYPE_KLOCK;
const unsigned_t TOPPERS_cfg_G_KLOCK = G_KLOCK;
const unsigned_t TOPPERS_cfg_P_KLOCK = P_KLOCK;
const unsigned_t TOPPERS_cfg_F_KLOCK = F_KLOCK;
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_LOCAL = 
#if defined(TOPPERS_SYSTIM_LOCAL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_GLOBAL = 
#if defined(TOPPERS_SYSTIM_GLOBAL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_PRCID = TOPPERS_SYSTIM_PRCID;
const unsigned_t TOPPERS_cfg_TTYPE_SPN = TTYPE_SPN;
const unsigned_t TOPPERS_cfg_NATIVE_SPN = NATIVE_SPN;
const unsigned_t TOPPERS_cfg_EMULATE_SPN = EMULATE_SPN;
const signed_t TOPPERS_cfg_TMAX_NATIVE_SPN = TMAX_NATIVE_SPN;
const unsigned_t TOPPERS_cfg_sizeof_ID = sizeof(ID);
const unsigned_t TOPPERS_cfg_sizeof_uint_t = sizeof(uint_t);
const unsigned_t TOPPERS_cfg_sizeof_SIZE = sizeof(SIZE);
const unsigned_t TOPPERS_cfg_sizeof_ATR = sizeof(ATR);
const unsigned_t TOPPERS_cfg_sizeof_PRI = sizeof(PRI);
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_VP = sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = sizeof(intptr_t);
const unsigned_t TOPPERS_cfg_sizeof_FP = sizeof(FP);
const unsigned_t TOPPERS_cfg_sizeof_TINIB = sizeof(TINIB);
const unsigned_t TOPPERS_cfg_sizeof_STK_T_prt = sizeof(STK_T*);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = offsetof(TINIB,tskatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = offsetof(TINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = offsetof(TINIB,task);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = offsetof(TINIB,ipriority);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texatr = offsetof(TINIB,texatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texrtn = offsetof(TINIB,texrtn);
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = sizeof(SEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = offsetof(SEMINIB,sematr);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = offsetof(SEMINIB,isemcnt);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = offsetof(SEMINIB,maxsem);
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = sizeof(FLGPTN);
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = sizeof(FLGINIB);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = offsetof(FLGINIB,flgatr);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = offsetof(FLGINIB,iflgptn);
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = sizeof(DTQINIB);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = offsetof(DTQINIB,dtqatr);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = offsetof(DTQINIB,dtqcnt);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = offsetof(DTQINIB,p_dtqmb);
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = sizeof(PDQINIB);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = offsetof(PDQINIB,pdqatr);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = offsetof(PDQINIB,pdqcnt);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = offsetof(PDQINIB,maxdpri);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = offsetof(PDQINIB,p_pdqmb);
const unsigned_t TOPPERS_cfg_sizeof_MBXINIB = sizeof(MBXINIB);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_mbxatr = offsetof(MBXINIB,mbxatr);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_maxmpri = offsetof(MBXINIB,maxmpri);
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = sizeof(MPFINIB);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = offsetof(MPFINIB,mpfatr);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = offsetof(MPFINIB,blkcnt);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = offsetof(MPFINIB,blksz);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = offsetof(MPFINIB,mpf);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = offsetof(MPFINIB,p_mpfmb);
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = sizeof(CYCINIB);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = offsetof(CYCINIB,cycatr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = offsetof(CYCINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cychdr = offsetof(CYCINIB,cychdr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = offsetof(CYCINIB,cyctim);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = offsetof(CYCINIB,cycphs);
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = sizeof(ALMINIB);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = offsetof(ALMINIB,almatr);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = offsetof(ALMINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almhdr = offsetof(ALMINIB,almhdr);
const unsigned_t TOPPERS_cfg_sizeof_INHNO = sizeof(INHNO);
const unsigned_t TOPPERS_cfg_sizeof_INTNO = sizeof(INTNO);
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = sizeof(EXCNO);
const unsigned_t TOPPERS_cfg_TA_HIGHLEVEL = TA_HIGHLEVEL;


/* #include "sample1.h" */
/* #include "target_timer.h" */

#ifdef TOPPERS_SYSTIM_LOCAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 13 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_0 = TCL_1;
#line 14 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_0 = 0;
const unsigned_t TOPPERS_cfg_valueof_iniatr_0 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_1 = TCL_1;
#line 15 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
const unsigned_t TOPPERS_cfg_valueof_teratr_1 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_2 = TCL_1;
#line 16 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
const unsigned_t TOPPERS_cfg_valueof_inhno_2 = ( INHNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_2 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_3 = TCL_1;
#line 17 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
const unsigned_t TOPPERS_cfg_valueof_intno_3 = ( INTNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_3 = ( TA_ENAINT|INTATR_TIMER_PRC1 ); const signed_t TOPPERS_cfg_valueof_intpri_3 = ( INTPRI_TIMER_PRC1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 18 "../../target/at91skyeye_gcc/target_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PRCID >= 2 

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 21 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_4 = TCL_2;
#line 22 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
const unsigned_t TOPPERS_cfg_valueof_iniatr_4 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_5 = TCL_2;
#line 23 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
const unsigned_t TOPPERS_cfg_valueof_teratr_5 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_6 = TCL_2;
#line 24 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
const unsigned_t TOPPERS_cfg_valueof_inhno_6 = ( INHNO_TIMER_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_6 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_7 = TCL_2;
#line 25 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
const unsigned_t TOPPERS_cfg_valueof_intno_7 = ( INTNO_TIMER_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_7 = ( TA_ENAINT|INTATR_TIMER_PRC2 ); const signed_t TOPPERS_cfg_valueof_intpri_7 = ( INTPRI_TIMER_PRC2 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 26 "../../target/at91skyeye_gcc/target_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 30 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_8 = TCL_3;
#line 31 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
const unsigned_t TOPPERS_cfg_valueof_iniatr_8 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_9 = TCL_3;
#line 32 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
const unsigned_t TOPPERS_cfg_valueof_teratr_9 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_10 = TCL_3;
#line 33 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
const unsigned_t TOPPERS_cfg_valueof_inhno_10 = ( INHNO_TIMER_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_10 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_11 = TCL_3;
#line 34 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
const unsigned_t TOPPERS_cfg_valueof_intno_11 = ( INTNO_TIMER_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_11 = ( TA_ENAINT|INTATR_TIMER_PRC3 ); const signed_t TOPPERS_cfg_valueof_intpri_11 = ( INTPRI_TIMER_PRC3 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 35 "../../target/at91skyeye_gcc/target_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 39 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_12 = TCL_4;
#line 40 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
const unsigned_t TOPPERS_cfg_valueof_iniatr_12 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_13 = TCL_4;
#line 41 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
const unsigned_t TOPPERS_cfg_valueof_teratr_13 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_14 = TCL_4;
#line 42 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
const unsigned_t TOPPERS_cfg_valueof_inhno_14 = ( INHNO_TIMER_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_14 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_15 = TCL_4;
#line 43 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
const unsigned_t TOPPERS_cfg_valueof_intno_15 = ( INTNO_TIMER_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_15 = ( TA_ENAINT|INTATR_TIMER_PRC4 ); const signed_t TOPPERS_cfg_valueof_intpri_15 = ( INTPRI_TIMER_PRC4 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 44 "../../target/at91skyeye_gcc/target_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#else  

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 49 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_16 = TCL_SYSTIM_PRC;
#line 50 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
const unsigned_t TOPPERS_cfg_valueof_iniatr_16 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_17 = TCL_SYSTIM_PRC;
#line 51 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
const unsigned_t TOPPERS_cfg_valueof_teratr_17 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_18 = TCL_SYSTIM_PRC;
#line 52 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
const unsigned_t TOPPERS_cfg_valueof_inhno_18 = ( INHNO_TIMER_SYSTIM ); const unsigned_t TOPPERS_cfg_valueof_inhatr_18 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_19 = TCL_SYSTIM_PRC;
#line 53 "../../target/at91skyeye_gcc/target_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
const unsigned_t TOPPERS_cfg_valueof_intno_19 = ( INTNO_TIMER_SYSTIM ); const unsigned_t TOPPERS_cfg_valueof_intatr_19 = ( TA_ENAINT|INTATR_TIMER_SYSTIM ); const signed_t TOPPERS_cfg_valueof_intpri_19 = ( INTPRI_TIMER_SYSTIM ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 54 "../../target/at91skyeye_gcc/target_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 
/* #include "syssvc/syslog.h" */

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 12 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_20 = TCL_1;
#line 13 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
const unsigned_t TOPPERS_cfg_valueof_iniatr_20 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 14 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 18 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_21 = TCL_2;
#line 19 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
const unsigned_t TOPPERS_cfg_valueof_iniatr_21 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 20 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 24 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_22 = TCL_3;
#line 25 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
const unsigned_t TOPPERS_cfg_valueof_iniatr_22 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 26 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 30 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_23 = TCL_4;
#line 31 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
const unsigned_t TOPPERS_cfg_valueof_iniatr_23 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 32 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#ifdef G_SYSLOG

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 36 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_24 = TCL_1;
#line 37 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
#define G_SYSLOG_SPN	(<>)

#line 37 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_spnatr_24 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 38 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 
/* #include "syssvc/banner.h" */

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 12 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_25 = TCL_1;
#line 13 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
const unsigned_t TOPPERS_cfg_valueof_iniatr_25 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_26 = TCL_1;
#line 14 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
const unsigned_t TOPPERS_cfg_valueof_iniatr_26 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 15 "../../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 19 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_27 = TCL_2;
#line 20 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
const unsigned_t TOPPERS_cfg_valueof_iniatr_27 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 21 "../../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 25 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_28 = TCL_3;
#line 26 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
const unsigned_t TOPPERS_cfg_valueof_iniatr_28 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 27 "../../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 31 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_29 = TCL_4;
#line 32 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
const unsigned_t TOPPERS_cfg_valueof_iniatr_29 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 33 "../../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "target_syssvc.h" */
/* #include "target_serial.h" */

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 10 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_30 = TCL_1;
#line 11 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
const unsigned_t TOPPERS_cfg_valueof_iniatr_30 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_31 = TCL_1;
#line 12 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_31 = 31;
const unsigned_t TOPPERS_cfg_valueof_inhno_31 = ( INHNO_SIO_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_31 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_32 = TCL_1;
#line 13 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_32 = 32;
const unsigned_t TOPPERS_cfg_valueof_intno_32 = ( INTNO_SIO_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_32 = ( INTATR_SIO_PRC1 ); const signed_t TOPPERS_cfg_valueof_intpri_32 = ( INTPRI_SIO_PRC1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 14 "../../target/at91skyeye_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_SIOP >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 17 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_33 = TCL_2;
#line 18 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_33 = 33;
const unsigned_t TOPPERS_cfg_valueof_iniatr_33 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_34 = TCL_2;
#line 19 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_34 = 34;
const unsigned_t TOPPERS_cfg_valueof_inhno_34 = ( INHNO_SIO_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_34 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_35 = TCL_2;
#line 20 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_35 = 35;
const unsigned_t TOPPERS_cfg_valueof_intno_35 = ( INTNO_SIO_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_35 = ( INTATR_SIO_PRC2 ); const signed_t TOPPERS_cfg_valueof_intpri_35 = ( INTPRI_SIO_PRC2 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 21 "../../target/at91skyeye_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_SIOP >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 25 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_36 = TCL_3;
#line 26 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_36 = 36;
const unsigned_t TOPPERS_cfg_valueof_iniatr_36 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_37 = TCL_3;
#line 27 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_37 = 37;
const unsigned_t TOPPERS_cfg_valueof_inhno_37 = ( INHNO_SIO_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_37 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_38 = TCL_3;
#line 28 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_38 = 38;
const unsigned_t TOPPERS_cfg_valueof_intno_38 = ( INTNO_SIO_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_38 = ( INTATR_SIO_PRC3 ); const signed_t TOPPERS_cfg_valueof_intpri_38 = ( INTPRI_SIO_PRC3 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 29 "../../target/at91skyeye_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_SIOP >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 33 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_39 = TCL_4;
#line 34 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_39 = 39;
const unsigned_t TOPPERS_cfg_valueof_iniatr_39 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_40 = TCL_4;
#line 35 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_40 = 40;
const unsigned_t TOPPERS_cfg_valueof_inhno_40 = ( INHNO_SIO_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_40 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_41 = TCL_4;
#line 36 "../../target/at91skyeye_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_41 = 41;
const unsigned_t TOPPERS_cfg_valueof_intno_41 = ( INTNO_SIO_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_41 = ( INTATR_SIO_PRC4 ); const signed_t TOPPERS_cfg_valueof_intpri_41 = ( INTPRI_SIO_PRC4 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 37 "../../target/at91skyeye_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "syssvc/serial.h" */

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 14 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_42 = TCL_1;
#line 15 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_42 = 42;
const unsigned_t TOPPERS_cfg_valueof_iniatr_42 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_43 = TCL_1;
#line 16 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_43 = 43;
#define SERIAL_RCV_SEM1	(<>)

#line 16 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_43 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_43 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_43 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_44 = TCL_1;
#line 17 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_44 = 44;
#define SERIAL_SND_SEM1	(<>)

#line 17 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_44 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_44 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_44 = ( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 18 "../../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PORT >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 20 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_45 = TCL_2;
#line 21 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_45 = 45;
const unsigned_t TOPPERS_cfg_valueof_iniatr_45 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_46 = TCL_2;
#line 22 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_46 = 46;
#define SERIAL_RCV_SEM2	(<>)

#line 22 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_46 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_46 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_46 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_47 = TCL_2;
#line 23 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_47 = 47;
#define SERIAL_SND_SEM2	(<>)

#line 23 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_47 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_47 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_47 = ( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 24 "../../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PORT >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 28 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_48 = TCL_3;
#line 29 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_48 = 48;
const unsigned_t TOPPERS_cfg_valueof_iniatr_48 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_49 = TCL_3;
#line 30 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_49 = 49;
#define SERIAL_RCV_SEM3	(<>)

#line 30 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_49 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_49 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_49 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_50 = TCL_3;
#line 31 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_50 = 50;
#define SERIAL_SND_SEM3	(<>)

#line 31 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_50 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_50 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_50 = ( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 32 "../../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PORT >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 36 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_51 = TCL_4;
#line 37 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_51 = 51;
const unsigned_t TOPPERS_cfg_valueof_iniatr_51 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_52 = TCL_4;
#line 38 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_52 = 52;
#define SERIAL_RCV_SEM4	(<>)

#line 38 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_52 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_52 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_52 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_53 = TCL_4;
#line 39 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_53 = 53;
#define SERIAL_SND_SEM4	(<>)

#line 39 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_53 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_53 = ( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_53 = ( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 40 "../../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "syssvc/logtask.h" */

#ifdef G_SYSLOG

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 13 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_54 = TCL_1;
#line 14 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_54 = 54;
#define LOGTASK1	(<>)

#line 14 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_54 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_54 = ( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_54 = ( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_55 = TCL_1;
#line 16 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_55 = 55;
const unsigned_t TOPPERS_cfg_valueof_teratr_55 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 17 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#else 

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 22 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_56 = TCL_1;
#line 23 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_56 = 56;
#define LOGTASK1	(<>)

#line 23 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_56 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_56 = ( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_56 = ( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_57 = TCL_1;
#line 25 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_57 = 57;
const unsigned_t TOPPERS_cfg_valueof_teratr_57 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 26 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 31 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_58 = TCL_2;
#line 32 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_58 = 58;
#define LOGTASK2	(<>)

#line 32 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_58 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_58 = ( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_58 = ( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_59 = TCL_2;
#line 34 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_59 = 59;
const unsigned_t TOPPERS_cfg_valueof_teratr_59 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 35 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 39 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_60 = TCL_3;
#line 40 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_60 = 60;
#define LOGTASK3	(<>)

#line 40 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_60 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_60 = ( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_60 = ( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_61 = TCL_3;
#line 42 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_61 = 61;
const unsigned_t TOPPERS_cfg_valueof_teratr_61 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 43 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 47 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_62 = TCL_4;
#line 48 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_62 = 62;
#define LOGTASK4	(<>)

#line 48 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_62 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_62 = ( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_62 = ( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_63 = TCL_4;
#line 50 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_63 = 63;
const unsigned_t TOPPERS_cfg_valueof_teratr_63 = ( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 51 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#endif 
/* #include "target_ipi.h" */

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 3 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_64 = TCL_1;
#line 4 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_64 = 64;
const unsigned_t TOPPERS_cfg_valueof_inhno_64 = ( INHNO_IPI_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_64 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_65 = TCL_1;
#line 5 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_65 = 65;
const unsigned_t TOPPERS_cfg_valueof_intno_65 = ( INTNO_IPI_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_65 = ( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_65 = ( INTPRI_IPI_PRC1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 6 "../../target/at91skyeye_gcc/target_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PRCID >= 2 

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 9 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_66 = TCL_2;
#line 10 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_66 = 66;
const unsigned_t TOPPERS_cfg_valueof_inhno_66 = ( INHNO_IPI_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_66 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_67 = TCL_2;
#line 11 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_67 = 67;
const unsigned_t TOPPERS_cfg_valueof_intno_67 = ( INTNO_IPI_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_67 = ( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_67 = ( INTPRI_IPI_PRC2 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 12 "../../target/at91skyeye_gcc/target_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 16 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_68 = TCL_3;
#line 17 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_68 = 68;
const unsigned_t TOPPERS_cfg_valueof_inhno_68 = ( INHNO_IPI_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_68 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_69 = TCL_3;
#line 18 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_69 = 69;
const unsigned_t TOPPERS_cfg_valueof_intno_69 = ( INTNO_IPI_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_69 = ( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_69 = ( INTPRI_IPI_PRC3 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 19 "../../target/at91skyeye_gcc/target_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 23 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_70 = TCL_4;
#line 24 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_70 = 70;
const unsigned_t TOPPERS_cfg_valueof_inhno_70 = ( INHNO_IPI_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_70 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_71 = TCL_4;
#line 25 "../../target/at91skyeye_gcc/target_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_71 = 71;
const unsigned_t TOPPERS_cfg_valueof_intno_71 = ( INTNO_IPI_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_71 = ( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_71 = ( INTPRI_IPI_PRC4 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 26 "../../target/at91skyeye_gcc/target_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 19 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_72 = TCL_1;
#line 20 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_72 = 72;
#define TASK1	(<>)

#line 20 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_72 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_72 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_72 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_73 = TCL_1;
#line 21 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_73 = 73;
#define TASK2	(<>)

#line 21 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_73 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_73 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_73 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_74 = TCL_1;
#line 22 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_74 = 74;
#define TASK3	(<>)

#line 22 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_74 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_74 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_74 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_75 = TCL_1;
#line 23 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_75 = 75;
#define MAIN_TASK1	(<>)

#line 23 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_75 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_75 = ( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_75 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_76 = TCL_1;
#line 24 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_76 = 76;
#define CYCHDR1	(<>)

#line 24 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_76 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_76 = ( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_76 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_77 = TCL_1;
#line 25 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_77 = 77;
#define ALMHDR1	(<>)

#line 25 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_77 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_78 = TCL_1;
#line 26 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_78 = 78;
#define SERVER_TASK1	(<>)

#line 26 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_78 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_78 = ( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_78 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_79 = TCL_1;
#line 27 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_79 = 79;
#define SERVER_DTQ1	(<>)

#line 27 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_79 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_79 = ( NUM_SERVER_DTQ ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 28 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 30 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_80 = TCL_2;
#line 31 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_80 = 80;
#define TASK4	(<>)

#line 31 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_80 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_80 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_80 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_81 = TCL_2;
#line 32 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_81 = 81;
#define TASK5	(<>)

#line 32 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_81 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_81 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_81 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_82 = TCL_2;
#line 33 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_82 = 82;
#define TASK6	(<>)

#line 33 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_82 = ( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_82 = ( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_82 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_83 = TCL_2;
#line 34 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_83 = 83;
#define MAIN_TASK2	(<>)

#line 34 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_83 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_83 = ( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_83 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_84 = TCL_2;
#line 35 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_84 = 84;
#define CYCHDR2	(<>)

#line 35 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_84 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_84 = ( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_84 = ( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_85 = TCL_2;
#line 36 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_85 = 85;
#define ALMHDR2	(<>)

#line 36 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_85 = ( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_86 = TCL_2;
#line 37 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_86 = 86;
#define SERVER_TASK2	(<>)

#line 37 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_86 = ( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_86 = ( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_86 = ( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_87 = TCL_2;
#line 38 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_87 = 87;
#define SERVER_DTQ2	(<>)

#line 38 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_87 = ( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_87 = ( NUM_SERVER_DTQ ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 39 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

/* #include "logtrace/trace_config.h" */

#line 41 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_88 = 88;
const unsigned_t TOPPERS_cfg_valueof_iniatr_88 = ( TA_NULL ); 
#line 42 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_89 = 89;
const unsigned_t TOPPERS_cfg_valueof_teratr_89 = ( TA_NULL ); 
#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

