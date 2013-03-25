/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: tinet_kernel_defs.h,v 1.5 2009/12/24 05:38:58 abe Exp abe $
 */

/*
 *  �����ͥ�˴ؤ���ߴ�������ե�����
 */

#ifndef _TINET_KERNEL_DEFS_H_
#define _TINET_KERNEL_DEFS_H_

#if defined(TARGET_KERNEL_JSP)

#ifndef _MACRO_ONLY

/*
 *  �ǡ������������inttype.h��
 */

#ifdef _int8_
typedef _int8_			int8_t;		/* ����դ� 8 �ӥå����� */
typedef unsigned _int8_		uint8_t;	/* ���̵�� 8 �ӥå����� */
#endif	/* of #ifdef _int8_ */

#ifdef _int16_
typedef _int16_			int16_t;	/* ����դ� 16 �ӥå����� */
typedef unsigned _int16_	uint16_t;	/* ���̵�� 16 �ӥå����� */
#endif	/* of #ifdef _int16_ */

#ifdef _int32_
typedef _int32_			int32_t;	/* ����դ� 32 �ӥå����� */
typedef unsigned _int32_	uint32_t;	/* ���̵�� 32 �ӥå����� */
#endif	/* of #ifdef _int32_ */

#ifdef _int64_
typedef unsigned _int64_	uint64_t;	/* ���̵�� 64 �ӥå����� */
#endif	/* of #ifdef _int64_ */

typedef signed int		int_t;		/* �����ʥ�����������դ����� */
typedef unsigned int		uint_t;		/* �����ʥ����������̵������ */

typedef signed long		long_t;		/* Ĺ��Υ�����������դ����� */
typedef unsigned long		ulong_t;	/* Ĺ��Υ����������̵������ */

#ifdef _vp_int_
typedef _vp_int_		intptr_t;	/* �ݥ��󥿤ޤ�������դ����� */
#else	/* of #ifdef _vp_int_ */
typedef VP			intptr_t;	/* �ݥ��󥿤ޤ�������դ����� */
#endif	/* of #ifdef _vp_int_ */

typedef int			bool_t;		/* ������ */

#ifndef true
#define true			1		/* �� */
#endif /* true */

#ifndef false
#define false			0		/* �� */
#endif /* false */

#endif	/* of #ifndef _MACRO_ONLY */

/* ��¤�� structure ��Υե������ field �ΥХ��Ȱ��֤��֤��ޥ��� */
#ifndef offsetof
#define offsetof(structure, field) ((size_t) &(((structure *) 0)->field))
#endif	/* of #ifndef offsetof */

/*
 *  �����������ޥ���
 */
#ifndef UINT_C
#define UINT_C(val)		(val ## U)	/* uint_t�����������ޥ��� */
#endif /* UINT_C */

#ifndef ULONG_C
#define ULONG_C(val)		(val ## UL)	/* ulong_t�����������ޥ��� */
#endif /* ULONG_C */

#elif defined(TARGET_KERNEL_ASP)

#define syscall(api)		(api)

#endif	/* of #if defined(TARGET_KERNEL_JSP) */

#endif	/* of #ifndef _TINET_KERNEL_DEFS_H_ */
