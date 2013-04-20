/*
 *  Copyright (C) 2006 by Nagoya University Extension Course for
 *                       Embedded Software Specialists(NEXCESS), JAPAN
 */

/*
 * �Z�}�t�H�r������ �^�X�N VS �n���h�� �o�̓v���O����
 */
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

#define DELAY_LOOP 0x40000L


/*
 * �r�W�[���[�v�֐�
 */ 
int
busy_wait_inc(int e){
    e++;
    sil_dly_nse(50000);
  
    return e;
}

/*
 * ���L�ϐ�
 */
int count = 0;
/*
 * ���L�ϐ�(�v���Z�b�T�P����̂݃A�N�Z�X)
 */
int pro1_count = 0;

/*
 * �o�̓^�X�N
 */ 
void
task(intptr_t exinf){	
    int local_count = 0,i;
    for (i = 0 ; i < 100 ; i++) {
        local_count = busy_wait_inc(local_count);
        count = busy_wait_inc(count);
        syslog(LOG_NOTICE, "Task %d : count = %d, local_count = %d", exinf, count, local_count);
    }
}

/*
 * �����n���h��
 */
void
cyc_handler(void){
    if(pro1_count < 100){
        pro1_count = busy_wait_inc(pro1_count);
        count = busy_wait_inc(count);
    }
    syslog(LOG_NOTICE, "Cyc : count = %d, pro1_count = %d",  count, pro1_count);
}