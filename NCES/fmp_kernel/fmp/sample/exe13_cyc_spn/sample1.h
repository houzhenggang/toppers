/*
 *  Copyright (C) 2006 by Nagoya University Extension Course for
 *                       Embedded Software Specialists(NEXCESS), JAPAN
 */

#define STACK_SIZE         386  /* �^�X�N�̃X�^�b�N�T�C�Y */
#define MID_PRIORITY     8  /* �^�X�N�̗D��x */

#define ROT_INTERVAL 1

#ifndef TOPPERS_MACRO_ONLY
extern void task(intptr_t exinf);
void cyc_handler(void);
#endif /* _MACRO_ONLY */
