/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: core_support.S 781 2011-02-16 00:52:10Z ertl-honda $
 */

/*
 *        コア依存モジュール アセンブリ言語部（ARM用）
 */

#define TOPPERS_MACRO_ONLY
#define TOPPERS_ASM_MACRO
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#include "kernel_impl.h"
#include "offset.h"

/*
 * 例外ベクタ
 */
    .section .vector,"a"
    .global vector_table
vector_table:
    ldr pc, reset_vector       /* リセット             */
    ldr pc, undef_vector       /* 未定義命令           */
    ldr pc, swi_vector         /* ソフトウェア割込み   */
    ldr pc, prefech_vector     /* プリフェッチアボート */
    ldr pc, data_abort_vector  /* データアボート       */
    ldr pc, reset_vector
    ldr pc, irq_vector         /* IRQ                  */
    ldr pc, fiq_vector         /* FIQ                  */


/*
 *  例外ベクタの命令から参照される
 *  ジャンプ先アドレス
 */
    .global vector_ref_tbl
vector_ref_tbl:
reset_vector:
    .long   start
undef_vector:
    .long   undef_handler
swi_vector:
    .long   swi_handler
prefech_vector:
    .long   prefetch_handler
data_abort_vector:
    .long   data_abort_handler
irq_vector:
    .long   irq_handler
fiq_vector:
    .long   fiq_handler

#include "target_asm.inc"

/*
 *  タスクディスパッチャ
 *
 */
    .text
    .align 2
    .globl dispatch
dispatch:
    /*
     *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
     *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
     *  れる．
     */
    stmfd  sp!, {r4 - r11,lr}           /* レジスタの保存 */
    my_pcb r0, r1                       /* p_runtskを読み込む */
    ldr    r1, [r0,#PCB_p_runtsk]
    str    sp, [r1,#TCB_sp]             /* タスクスタックを保存 */
    adr    r2, dispatch_r
    str    r2, [r1,#TCB_pc]             /* 実行再開番地を保存 */
    b      dispatcher

dispatch_r:
    ldmfd sp!,{r4 - r11,lr}     /* レジスタの復帰 */
    /*
     *  タスク例外処理ルーチンの起動
     *  dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
     */
    ldrb  r0,[r1,#TCB_enatex]
    tst   r0,#TCB_enatex_mask
    beq   dispatch_r_1          /* enatex が false ならリターン */
    ldr   r0,[r1,#TCB_texptn]   /* texptn が0でなければ         */
    tst   r0,r0                 
    bne   dispatch_call_texrtn  /* タスク例外ルーチンの呼び出し */
dispatch_r_1:
    bx    lr

    /*
     *  自タスクのマイグレーション
     *  引数(r0)にマイグレーション先のプロセッサが入っているため破壊しないこと
     */
    .text
    .align 2
    .globl dispatch_and_migrate
dispatch_and_migrate:
    stmfd  sp!, {r4 - r11,lr}           /* レジスタの保存 */
    my_pcb r2, r1                       /* p_runtskを読み込む */
    ldr    r1, [r2,#PCB_p_runtsk]
    str    sp, [r1,#TCB_sp]             /* タスクスタックを保存 */
    adr    r3, dispatch_r
    str    r3, [r1,#TCB_pc]             /* 実行再開番地を保存 */
    ldr    sp, [r2,#PCB_istkpt]
    b      migrate_self                 /* 自タスクのマイグレーションルーチンへ */

    /*
     *  現在のコンテキストを捨てマイグレーション
     *  引数(r0)にマイグレーション先のプロセッサが入っているため破壊しないこと
     */
    .text
    .align 2
    .globl exit_and_migrate
exit_and_migrate:
    my_pcb r2, r1                       
    ldr    sp, [r2,#PCB_istkpt]         /* 非タスクコンテキスト用スタックへ切り替え */
    b      exit_and_migrate_self        /* 自タスクのexitとマイグレーションルーチンへ */

/*
 *  ディスパッチャの動作開始（cpu_support.S）
 */
    .globl start_dispatch
start_dispatch:
    /*
     *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
     *  （割込みロック状態と同等）で呼び出される．また，非タスクコンテキ
     *  ストから呼び出されることを想定している．
     *
     *  dispatcherは，CPUロック状態，（モデル上の）割込み優先度マスク全
     *  解除状態，例外（割込み/CPU例外）のネスト回数0で呼び出す．
     *  target_initializeでは，（モデル上の）割込み優先度マスク全解除
     *  とし，カーネル管理外の割込みであるFIQを許可することで，
     *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
     *  また，initialize_taskでdisdspをFALSEに初期化しているため，ディ
     *  スパッチ許可状態になっている．
     *
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET) /* CPUロック状態へ */
    my_pcb r0, r1                          /* 例外（割込み/CPU例外）のネスト回数 */
    mov   r1, #0                           /* を0に                              */
    str   r1, [r0, #PCB_excpt_nest_count]
    b     dispatcher_0

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
    .globl exit_and_dispatch
exit_and_dispatch:
    /* ディスパッチャ本体（dispatcher）へ */
    my_pcb r0, r1                       /* my_pcbを読み込む */

/*
 *  ディスパッチャ本体
 */
dispatcher:
    /*
     *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
     *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
     *  れる．実行再開番地へもこの状態のまま分岐する．
     *
     *  すなわち，スーパーバイザーモード，IRQ禁止となっている．
     *  r0には，my_pcb へのポインタを入れる
     */
#ifdef LOG_DSP_ENTER
    stmfd sp!, {r0}
    ldr   r1, [r0, #PCB_p_runtsk]
    mov   r0, r1
    bl    log_dsp_enter
    ldmfd sp!, {r0}
#endif /* LOG_DSP_ENTER */
dispatcher_0:
    ldr   r1, [r0, #PCB_p_schedtsk] /* p_schedtskをp_runtskに */
    str   r1, [r0, #PCB_p_runtsk]
    cmp   r1, #0            /* p_runtskがNULLならdispatcher_1へ */
    beq   dispatcher_1
    ldr   sp, [r1,#TCB_sp]  /* タスクスタックを復帰 */
#ifdef LOG_DSP_LEAVE
    mov   r0, r1            /* p_runtskをパラメータに */
    mov   r4, r1            /* r1はスクラッチレジスタなので保存 */
    bl    log_dsp_leave
    mov   r1, r4
#endif /* LOG_DSP_LEAVE */
    ldr   pc, [r1,#TCB_pc]  /* 実行再開番地を復帰 */

dispatcher_1:
    /*
     * CPUロック状態の解除と，非タスクコンテキスト実行状態への
     * 準備をする
     */
    ldr   sp, [r0,#PCB_istkpt]         /* 非タスクコンテキストのスタックへ */
    add   r2, r0, #PCB_reqflg          /* r2 <- reqflg */
    add   r3, r0, #PCB_excpt_nest_count 
    mov   r0, #0
    mov   r1, #1
dispatcher_2:
    /*
     *  割込みを許可し，非タスクコンテキスト実行状態とし割込みを待つ．
     *
     *  ここで非タスクコンテキスト実行状態に切り換えるのは，ここで発生
     *  する割込み処理にどのスタックを使うかという問題の解決と，割込み
     *  ハンドラ内でのタスクディスパッチの防止という2つの意味がある．
     *
     *  プロセッサを割込み待ちに移行させる処理と，割込み許可とは，不可
     *  分に行なう必要がある．
     *  これを不可分に行なわない場合，割込みを許可した直後に割込
     *  みが入り，その中でタスクが実行可能状態になると，実行すべきタス
     *  クがあるにもかかわらずプロセッサが割込み待ちになってしまう．
     *
     *  割込み待ちの間は，p_runtskをNULL（＝0）に設定しなければならな
     *  い．このように設定しないと，割込みハンドラからiget_tidを呼び出
     *  した際の動作が仕様に合致しなくなる．
     *
     *  ターゲットによっては，省電力モード等に移行するため，標準の方法と
     *  異なる手順が必要な場合がある．
     *  そのようなターゲットでは，ターゲット依存において，TOPPERS_CUSTOM_IDLE
     *  を定義し，アセンブラマクロとして，toppers_asm_custom_idle を用意
     *  すればよい．toppers_asm_custom_idle の記述にあたっては，次のレジ
     *  スタは使用できない．
     *     r0, r1, r2, r3, s
     */
    str   r1, [r3]                          /* excpt_nest_count = 1 */

#ifdef TOPPERS_CUSTOM_IDLE
    toppers_asm_custom_idle
#else
    msr   cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET) /* 割り込み許可(システムモード) */
    nop
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET) /* CPUロック(システムモード) */
#endif /* TOPPERS_CUSTOM_IDLE */
    ldr   r6, [r2]        /* reqflgがfalseならdispatcher_2へ */
    cmp   r6, #0
    beq   dispatcher_2
    str   r0, [r2]        /* reqflgをFALSEに */
    str   r0, [r3]        /* excpt_nest_count = 0 */
    my_pcb r0, r1         /* my_pcbを読み込む */
    b     dispatcher_0


/*
 *  カーネルの終了処理の呼出し
 *
 *  モードとスタックを非タスクコンテキスト用に切り替え．
 */
    .globl call_exit_kernel
call_exit_kernel:
    msr  cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET|CPSR_IRQ_BIT|CPSR_FIQ_BIT) 
    my_pcb r2, r1                       
    ldr    sp, [r2,#PCB_istkpt]         /* 非タスクコンテキスト用スタックへ切り替え */ 
    b     exit_kernel

/*
 *  タスク開始時処理
 *
 *  dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
 */
    .text
    .globl start_r
start_r:
    msr   cpsr, #(CPSR_SVC|CPSR_ALWAYS_SET) /* CPUロック解除状態に */
    ldr   lr, =ext_tsk                      /* 戻り番地設定 */
    ldr   r2, [r1, #TCB_p_tinib]            /* p_runtsk->p_tinibをr2に  */
    ldr   r0, [r2, #TINIB_exinf]            /* exinfを引数レジスタr0に  */
    ldr   r1, [r2, #TINIB_task]             /* タスク起動番地にジャンプ */
    bx    r1

/*
 *  ディスパッチ要求用のプロセッサ間割込みのバイパス処理
 *
 *  共通部で用意されている ipi_handler を呼び出さずにディスパッチャを
 *  呼び出す．最も外側のルーチンでない場合は，reqflgをセットする．
 *  自PCBのアドレスがr0に入っていることを想定している．
 */    
#ifdef USE_IPI_DIS_HANDER_BYPASS
    .global ret_int_ipi_dispatch
ret_int_ipi_dispatch:
    ldr   r2, [r0,#PCB_excpt_nest_count] /* 戻り先がタスクコンテキストなら */
    cmp   r2, #0                         /* ret_int_4へ */
    beq   ret_int_4
    mov   r1, #1                         /* 戻り先が非タスクコンテキストなら */
    str   r1, [r0, #PCB_reqflg]          /* reqflgをtrueにしてリターン       */
    b     ret_int_2                
#endif /* USE_IPI_DIS_HANDER_BYPASS */

/*
 *  CPU例外ハンドラ出口処理
 *
 *  ret_excは，CPU例外ハンドラから戻った直後に実行するルーチンで，
 *  CPU例外ハンドラ終了後，ターゲット依存の処理を実行した後，
 *  カーネル管理の割込みを禁止，スタックをCPU例外前のスタックに，
 *  r0にCPU例外発生時に取得しているスピンロックの値を入れた状態
 *  で呼び出される．
 */
    .text
    .global ret_exc
ret_exc:
    /* 
     * CPU例外発生時にスピンロックを取得していれば，スピンロック
     * の解放は行わない．
     */
    cmp  r0, #0
    bne  ret_int_1

/*
 *  割込みハンドラ/CPU例外ハンドラ出口処理
 *
 *  ret_intは，割込みハンドラから戻った直後に実行するルーチンで，
 *  割込みハンドラ終了後，ターゲット依存の処理を実行した後，
 *  カーネル管理の割込みを禁止，スタックを割込み前のスタックにした
 *  状態で呼び出される．
 */
    .global ret_int
ret_int:
    /*
     *  スピンロックを取得していれば解除する
     */
    my_pcb r0, r1  /* 引数 */
    bl    force_unlock_spin

ret_int_1:
    /*
     *  例外・割込みのネストカウント（excpt_nest_count)のデクリメント
     */
    my_pcb r0, r1
    ldr   r1, [r0,#PCB_excpt_nest_count] /* r1 <-excpt_nest_count */
    sub   r2, r1, #1
    str   r2, [r0,#PCB_excpt_nest_count]
    cmp   r2, #0                  /* 戻り先が非タスクコンテキストなら */
    bne   ret_int_2               /* すぐにリターン                   */

    /*
     *  reqflgをチェックする前に割込みを禁止するのは，reqflgをチェック
     *  した直後に割込みハンドラが起動され，その中でディスパッチが要求
     *  された場合に，すぐにディスパッチされないという問題が生じるため
     *  である．
     */
    ldr   r1, [r0, #PCB_reqflg] /* reqflgがtrueであればret_int_3へ */
    cmp   r1, #0
    bne   ret_int_3

    .global ret_int_2
ret_int_2:
    /*
     *  割込み処理からのリターンにより，CPUロック解除状態に移行しなければ
     *  ならない．    
     *  ARMでは，CPSRのIRQビットでCPUロック解除状態とするため，単にリターン
     *  すればよい．
     */
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    ldmfd sp!,{r1}              /* CPSRの復帰処理 */
    msr   spsr, r1              /* 戻り先のcpsrをspsrに設定 */
    ldmfd sp!,{r0-r3,ip,lr,pc}^ /* コンテキストの復帰，^付きなので、cpsr <- spsr */
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    ldmfd sp!,{r0-r3,ip,lr}
    rfeia sp!
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

ret_int_3:
    /*
     *  ここでは，戻り先がタスクであり，スタックは，タスクスタックの上
     *  にスクラッチレジスタのみが保存された状態になっている．また，
     *  プロセッサは，スーパーバイザーモード・カーネル管理の割込みを禁止
     *  した状態となっている．
     */
    mov   r1, #0                   /* reqflgをFALSEに */
    str   r1, [r0, #PCB_reqflg]

    /*
     *  CPUロック状態に移行する．
     *
     *  この時点でCPUロック状態とするのは，dispatcherへ分岐する時と，
     *  call_texrtnを呼び出す時に，CPUロック状態になっている必要がある
     *  ためである．
     *
     *  ARMでは，CPSRのIRQビットでCPUロック状態を表現するため，ここでは，
     *  特に何も行わない．
     */

ret_int_4:
    /*
     *  dspflgがfalseである場合と，p_runtskとp_schedtskが同じ場合には，
     *  ディスパッチを行わない．このチェックが必要なのは，タスク例外処
     *  理ルーチンの呼出しが必要な場合に，ディスパッチが必要なくても，
     *  reqflgをTRUEにするためである．
     */
    ldr   r1, [r0, #PCB_p_runtsk] /* p_runtsk をr1に読み込む */
    ldr   r2, [r0, #PCB_dspflg]   /* dspflgがfalseならret_int_r_1へ */
    cmp   r2, #0
    beq   ret_int_r_1

    /*
     *  ディスパッチの必要性をチェック
     */
    ldr   r2, [r0, #PCB_p_schedtsk] /* p_schedtsk をr2に読み込む */
    cmp   r1, r2              /* p_runtskとp_schedtskが同じなら */
    beq   ret_int_r_1         /*                    ret_int_r_1へ */
    stmfd sp!, {r4-r11}       /* 残りのレジスタを保存 */
    str   sp, [r1,#TCB_sp]    /* タスクスタックを保存 */
    adr   r2, ret_int_r       /* 実行再開番地を保存   */
    str   r2, [r1,#TCB_pc]
    b     dispatcher

ret_int_r: 
    ldmfd sp!, {r4-r11}       /* レジスタの復帰 */
ret_int_r_1:
    /*
     *  enatexがtrueで，texptnが0でなければ，タスク例外処理ルーチンを
     *  呼び出す．
     *  dispatcherから呼び出されるため，TCBのアドレスはr1に入っている
     */
    ldrb  r0, [r1,#TCB_enatex]
    tst   r0, #TCB_enatex_mask
    beq   ret_int_r_2            /* enatex が false なら ret_int_r2 へ */
    ldr   r0, [r1,#TCB_texptn]   /* texptnをロード               */
    tst   r0, r0                 /* texptn が0で無ければ         */
    blne  dispatch_call_texrtn   /* タスク例外ルーチンの呼び出し */
ret_int_r_2:
    /*
     *  割込み処理からのリターンにより，CPUロック解除状態に移行するよ
     *  うにする．ARMはCPSRのIRQビットによってCPUロック状態を表してい
     *  るため，そのままリターンすればよい．
     */ 
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    ldmfd sp!, {r0}             /* spsr を復帰 */
    msr   spsr,r0               /* 戻り先のcpsrをspsrに設定 */
    ldmfd sp!,{r0-r3,ip,lr,pc}^ /* タスクに復帰 ^付きなので、cpsr <- spsr */
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    ldmfd sp!,{r0-r3,ip,lr}
    rfeia sp!
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

/*
 * CPU例外ハンドラ
 *
 * CPU例外ハンドラは，非タスクコンテキストで実行する．
 * 
 */

/*
 *  未定義命令 例外ハンドラ
 */
    .text
    .align 2
    .global undef_handler
undef_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pcはダミー */

    /*
     * spsrと戻り番地を取得するために未定義モードへ
     */
    msr   cpsr, #(CPSR_UND|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(戻り先) spsr(cpsr_svc)をスーパーバイザーモードのスタックへ
     * 保存．
     */
    srsdb #CPSR_SVC! 

    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     *  割込みロック状態，CPUロック状態はCPU例外発生時の
     *  状態を継承する．
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_UNDEF
    b     target_exc_handler

/*
 *  SWI 例外ハンドラ
 */
    .text
    .align 2
    .global swi_handler
swi_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     *  元々スーパーバイザーモードだが，CPUロック状態とする
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pcはダミー */
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(戻り先) spsr(cpsr_svc)をスーパーバイザーモードのスタックへ
     * 保存．
     */
    srsdb #CPSR_SVC! 

    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     *  割込みロック状態，CPUロック状態はCPU例外発生時の
     *  状態を継承する．
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_SWI
    b     target_exc_handler

/*
 *  プリフェッチアボード 例外ハンドラ
 */
    .text
    .align 2
    .global prefetch_handler
prefetch_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pcはダミー */

    /*
     * spsrと戻り番地を取得するためにアボートモードへ
     */
    msr   cpsr, #(CPSR_ABT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(戻り先) spsr(cpsr_svc)をスーパーバイザーモードのスタックへ
     * 保存．
     */
    srsdb #CPSR_SVC! 

    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_PABORT
    b     target_exc_handler

/*
 *  データアボード 例外ハンドラ
 */
    .text
    .align 2
    .global data_abort_handler
data_abort_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pcはダミー */

    /*
     * spsrと戻り番地を取得するためにアボートモードへ
     */
    msr   cpsr, #(CPSR_ABT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(戻り先) spsr(cpsr_svc)をスーパーバイザーモードのスタックへ
     * 保存．
     */
    srsdb #CPSR_SVC! 

    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_DABORT
    b     target_exc_handler


#ifndef TARGET_FIQ_HANDLER
/*
 *  FIQ 例外ハンドラ
 */
    .text
    .align 2
    .global fiq_handler
fiq_handler:
#if (__TARGET_ARCH_ARM == 4) || (__TARGET_ARCH_ARM == 5)
    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_FIQ_BIT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    stmfd sp!, {r0-r3,ip,lr,pc} /* pcはダミー */

    /*
     * spsrと戻り番地を取得するためにFIQモードへ
     */
    msr   cpsr, #(CPSR_FIQ|CPSR_FIQ_BIT|CPSR_CPULOCK|CPSR_ALWAYS_SET)
    mov   r0, lr
    mrs   r1, spsr
#else /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
    /* 
     * lr(戻り先) spsr(cpsr_svc)をスーパーバイザーモードのスタックへ
     * 保存．
     */
    srsdb #CPSR_SVC! 

    /* 
     *  例外発生前の動作時モード(スーパーバイザーモード)へ
     */
    msr   cpsr, #(CPSR_SVC|CPSR_CPULOCK|CPSR_ALWAYS_SET)    
    stmfd sp!, {r0-r3,ip,lr} 
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */

    mov   r2, #EXCH_NO_FIQ
    b     target_exc_handler
#endif /* TARGET_FIQ_HANDLER */

/*
 *  微少時間待ち
 */
    .globl _sil_dly_nse
_sil_dly_nse:
    sub   r0, r0, #SIL_DLY_TIM1
    cmp   r0, #0
    bgt   _sil_dly_nse1
    bxle  lr
_sil_dly_nse1:
    sub   r0, r0, #SIL_DLY_TIM2
    cmp   r0, #0
    bgt   _sil_dly_nse1
    bxle  lr

#ifdef __thumb__
    .text
    .align 2
    .global current_sr
current_sr:
    mrs   r0, cpsr
    bx    lr

   .global set_sr
set_sr:
    msr   cpsr, r0
    bx    lr
#endif /* __thumb__ */
