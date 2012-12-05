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
 *  @(#) $Id: udp_var.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)udp_var.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/udp_var.h,v 1.16.2.2 1999/08/29 16:29:59 peter Exp $
 */
 
#ifndef _UDP_VAR_H_
#define _UDP_VAR_H_

/*
 *  UDP �إå����ڥ����ɥ��������ޥ���
 */

#define IP_UDP_HDR_SIZE			(IP_HDR_SIZE + UDP_HDR_SIZE)
#define IF_IP_UDP_HDR_SIZE		(IF_IP_HDR_SIZE + UDP_HDR_SIZE)
#define IF_IP_UDP_HDR_OFFSET		(IF_IP_HDR_SIZE)

#define GET_UDP_HDR(nbuf,uhoff)		((T_UDP_HDR*)((uint8_t*)((nbuf)->buf) + uhoff))
#define GET_UDP_SDU(nbuf,uhoff)		((uint8_t*)((nbuf)->buf) + uhoff+ UDP_HDR_SIZE)

#define GET_UDP_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_IP_UDP_HDR_SIZE(nbuf)	(GET_IP_HDR_SIZE(GET_IP_HDR(nbuf)) + UDP_HDR_SIZE)
#define GET_IF_IP_UDP_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP_UDP_HDR_SIZE(nbuf))

/*
 *  TINET 1.1 �Ȥθߴ����Τ�������
 */

#if defined(SUPPORT_INET4)

#define IP4_UDP_HDR_SIZE		IP_UDP_HDR_SIZE
#define IF_IP4_UDP_HDR_SIZE		IF_IP_UDP_HDR_SIZE
#define GET_IP4_UDP_HDR_SIZE(nbuf)	GET_IP_UDP_HDR_SIZE(nbuf)	
#define GET_IF_IP4_UDP_HDR_SIZE(nbuf)	GET_IF_IP_UDP_HDR_SIZE(nbuf)

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  ������Хå��ؿ������
 */

typedef ER	(*t_udp_callback)(ID cepid, FN fncd, void *p_parblk);

/*
 *  UDP �̿�ü��
 */


/*
 *  IPv4 UDP �̿�ü��
 */
typedef struct t_udp4_cep {

	/*
	 * ITRON TCP/IP API��TCP �̿�ü����Ʊ������
	 */
	ATR		cepatr;		/* UDP �̿�ü��°��		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	t_udp_callback	callback;	/* ������Хå��ؿ�		*/

	/*
	 * TINET �ȼ��Υ���
	 */
	uint16_t	flags;		/* �̿�ü���ե饰		*/
	ID		semid_lock;	/* �̿�ü����å�		*/
	ID		snd_tskid;	/* �������������̻�		*/
	ID		rcv_tskid;	/* �������������̻�		*/
	ID		rcvqid;		/* �󥳡���Хå��Ѽ������塼���̻�*/
	T_NET_BUF	*cb_netbuf;	/* ������Хå��Ѽ����ͥåȥ���Хåե�*/

#ifdef UDP_CFG_NON_BLOCKING

	T_IPV4EP 	*snd_p_dstaddr;	/* �������Υ��ɥ쥹�ؤΥݥ���*/
	T_IPV4EP 	*rcv_p_dstaddr;	/* �������Υ��ɥ쥹�ؤΥݥ���*/
	void		*snd_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		snd_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		*rcv_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		rcv_len;	/* �����ǡ����ΰ��Ĺ��		*/

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#ifdef UDP_CFG_EXTENTIONS
	ER		error;		/* �Ԥ����ȯ���������顼	*/
#endif

	} T_UDP4_CEP;

#if defined(SUPPORT_INET4)
#define T_UDP_CEP	T_UDP4_CEP
#endif

/*
 *  IPv6 UDP �̿�ü��
 */

typedef struct t_udp6_cep {

	/*
	 * ITRON TCP/IP API��TCP �̿�ü����Ʊ������
	 */
	ATR		cepatr;		/* UDP �̿�ü��°��		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	t_udp_callback	callback;	/* ������Хå��ؿ�		*/

	/*
	 * TINET �ȼ��Υ���
	 */
	uint16_t	flags;		/* �̿�ü���ե饰		*/
	ID		semid_lock;	/* �̿�ü����å�		*/
	ID		snd_tskid;	/* �������������̻�		*/
	ID		rcv_tskid;	/* �������������̻�		*/
	ID		rcvqid;		/* �󥳡���Хå��Ѽ������塼���̻�*/
	T_NET_BUF	*cb_netbuf;	/* ������Хå��Ѽ����ͥåȥ���Хåե�*/

#ifdef UDP_CFG_NON_BLOCKING

	T_IPV6EP 	*snd_p_dstaddr;	/* �������Υ��ɥ쥹�ؤΥݥ���*/
	T_IPV6EP 	*rcv_p_dstaddr;	/* �������Υ��ɥ쥹�ؤΥݥ���*/
	void		*snd_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		snd_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		*rcv_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		rcv_len;	/* �����ǡ����ΰ��Ĺ��		*/

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#ifdef UDP_CFG_EXTENTIONS
	ER		error;		/* �Ԥ����ȯ���������顼	*/
#endif

	} T_UDP6_CEP;

#if defined(SUPPORT_INET6)
#define T_UDP_CEP	T_UDP6_CEP
#endif

/*
 *  UDP �̿�ü���ե饰
 */

#define UDP_CEP_FLG_POST_OUTPUT	UINT_C(0x0200)	/* �����򳫻Ϥ��롣		*/
#define UDP_CEP_FLG_DYNAMIC	UINT_C(0x0400)	/* ưŪ�����������ǽ�̿�ü����	*/
#define UDP_CEP_FLG_VALID	UINT_C(0x0800)	/* �����Ѥߤ�ͭ�����̿�ü����	*/

/*
 *  ���֥������� ID �κǾ��ͤ����
 */

#define	TMIN_UDP_CEPID		1	/* UDP �̿�ü�� ID �κǾ��� */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

typedef struct t_udp_stats {
	uint32_t	udpInDatagrams;
	uint32_t	udpNoPorts;
	uint32_t	udpInErrors;
	uint32_t	udpOutDatagrams;
} T_UDP_STATS;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ؿ����ߥ�졼�����ޥ���
 */

#define VALID_UDP_CEPID(id)	(TMIN_UDP_CEPID<=(id)&&(id)<=tmax_udp_cepid)

#define INDEX_UDP_CEP(id)	((id)-TMIN_UDP_CEPID)

#define GET_UDP_CEP(id)		(&(udp_cep[INDEX_UDP_CEP(id)]))

#define GET_UDP_CEPID(cep)	((ID)(((cep)-udp_cep)+TMIN_UDP_CEPID))

#define VALID_TFN_UDP_CAN(t)	((t)==TFN_UDP_SND_DAT||(t)==TFN_UDP_RCV_DAT||\
				 (t)==TFN_UDP_ALL)

#define VALID_UDP_CEP(cep)	(((cep)->flags&UDP_CEP_FLG_VALID)!=0)
#define DYNAMIC_UDP_CEP(cep)	(((cep)->flags&UDP_CEP_FLG_DYNAMIC)!=0)

/*
 *  �����ѿ�
 */

extern T_UDP_CEP udp_cep[];
extern const ID tmax_udp_cepid;

#ifdef SUPPORT_MIB

extern T_UDP_STATS udp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  TINET 1.3 �Ȥθߴ����Τ�������
 */

#define	TMIN_UDP_CCEPID		TMIN_UDP_CEPID
#define	TNUM_UDP_CCEPID		TNUM_UDP_CEPID

/*
 *  �ؿ�
 */

extern uint_t udp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern ER_UINT udp_send_data (T_UDP_CEP *cep, T_IPEP *p_dstaddr,
                              void *data, int_t len, TMO tmout);
extern ER udp_can_snd (T_UDP_CEP *cep, ER error);
extern ER udp_can_rcv (T_UDP_CEP *cep, ER error);
extern ER udp_alloc_auto_port (T_UDP_CEP *cep);
extern ER udp_alloc_port (T_UDP_CEP *cep, uint16_t portno);

/* �Υ�֥�å��󥰥������Ԥ������Ȥ߹��ॿ���� */

extern void	udp_output_task(intptr_t exinf);

#endif	/* of #ifndef _UDP_VAR_H_ */
