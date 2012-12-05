/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2008-2009 by Hokkaido Industrial Research Institute, JAPAN
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
 *  @(#) $Id: esp.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/esp.h,v 1.6 2002/04/19 04:46:22 suz Exp $	*/
/*	$KAME: esp.h,v 1.19 2001/09/04 08:43:19 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef _ESP_H_
#define _ESP_H_

#if defined(SUPPORT_INET6) || defined(SUPPORT_IPSEC)

/*
 *  RFC2406 �Ź沽�إå�
 */

typedef struct t_esp_hdr {
	int32_t	spi;	/* Security Parameter Index (SPI)	*/
	int32_t	seq;	/* ���������ֹ�			*/
	} T_ESP_HDR;

typedef struct t_esp_tail {
	int8_t	padlen;	/* �ѥǥ���Ĺ				*/	
	int8_t	next;	/* Next Header				*/
	} T_ESP_TAIL;

struct t_secas_var;

struct t_esp_algorithm {
	size_t padbound;	/* pad boundary, in byte */
	int_t ivlenval;		/* iv length, in byte */
	int_t (*mature) (struct t_secas_var *);
	int_t keymin;	/* in bits */
	int_t keymax;	/* in bits */
	//int_t (*schedlen) (const struct t_esp_algorithm *);
	int32_t (*schedlen) (const struct t_esp_algorithm *);
	const char *name;
	int_t (*ivlen) (const struct t_esp_algorithm *, struct t_secas_var *);
	int_t (*decrypt) (T_NET_BUF *, size_t,
		struct t_secas_var *, const struct t_esp_algorithm *, int_t,
			T_NET_BUF *, size_t);
	int_t (*encrypt) (T_NET_BUF *, size_t, size_t, int8_t*,
		struct t_secas_var *, const struct t_esp_algorithm *, int_t,
			T_NET_BUF *, size_t);
	/* not supposed to be called directly */
	int_t (*schedule) (const struct t_esp_algorithm *, struct t_secas_var *);
	int_t (*blockdecrypt) (const struct t_esp_algorithm *,
		struct t_secas_var *, int8_t *, int8_t *);
	int_t (*blockencrypt) (const struct t_esp_algorithm *,
		struct t_secas_var *, int8_t *, int8_t *);
};

typedef struct t_esp_algorithm T_ESP_ALGORITHM;

#define MAXIVLEN	16

/*
 * �ؿ�
 */

extern const struct t_esp_algorithm *esp_algorithm_lookup (int_t);
extern int_t esp_max_ivlen (void);
extern int_t esp_schedule (const struct t_esp_algorithm *, struct t_secas_var *);
extern int_t esp4_input(T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);

#ifdef T_IPSEC_REQUEST_DEFINED

extern int_t esp4_output(T_NET_BUF *m, T_IPSEC_REQUEST *isr, T_NET_BUF** result);

#endif	/* of #ifdef T_IPSEC_REQUEST_DEFINED */

#endif /* defined(SUPPORT_INET6) || defined(SUPPORT_IPSEC) */

#endif	/* of #ifndef _ESP_H_ */
