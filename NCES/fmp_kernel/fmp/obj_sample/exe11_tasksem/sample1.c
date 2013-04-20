/*
 *  Copyright (C) 2006 by Nagoya University Extension Course for
 *                       Embedded Software Specialists(NEXCESS), JAPAN
 */

/*
 * 排他制御あり2タスク出力プログラム
 */
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

#define DELAY_LOOP 0x400000L

/*
 * ビジーループ関数
 */ 
int
busy_wait_inc(int e){
    e++;
    sil_dly_nse(1000);
  
    return e;
}

/*
 * 共有変数
 */
int count = 0;

/*
 * 出力タスク
 */ 
void
task(intptr_t exinf){	
    int local_count = 0,i;
  
    for (i = 0 ; i < 100 ; i++) {
        local_count = busy_wait_inc(local_count);
        count = busy_wait_inc(count);
        syslog_3(LOG_NOTICE, "Task %d : count = %d, local_count = %d", exinf, count, local_count);
    }
}
