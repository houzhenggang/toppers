/*
 *  Copyright (C) 2006 by Nagoya University Extension Course for
 *                       Embedded Software Specialists(NEXCESS), JAPAN
 */

/*
 * �r�����䂠��2�^�X�N�o�̓v���O����
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
 * �r�W�[���[�v�֐�
 */ 
int
busy_wait_inc(int e){
    e++;
    sil_dly_nse(1000);
  
    return e;
}

/*
 * ���L�ϐ�
 */
int count = 0;

/*
 * �o�̓^�X�N
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
