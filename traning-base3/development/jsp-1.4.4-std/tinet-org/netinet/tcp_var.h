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
 *  @(#) $Id: tcp_var.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1993, 1994, 1995
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
 *	@(#)tcp_var.h	8.4 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_var.h,v 1.49.2.1 1999/08/29 16:29:57 peter Exp $
 */
 
#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_

/*
 *  TCP �إå����ڥ����ɥ��������ޥ���
 */

#define IP_TCP_HDR_SIZE			(IP_HDR_SIZE + TCP_HDR_SIZE)
#define IF_IP_TCP_HDR_SIZE		(IF_IP_HDR_SIZE + TCP_HDR_SIZE)
#define IF_IP_TCP_HDR_OFFSET		(IF_IP_HDR_SIZE)
#define IF_IP_TCP_SDU_OFFSET		(IF_IP_TCP_HDR_SIZE)

#define GET_TCP_HDR(nbuf,thoff)		((T_TCP_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_OPT(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + TCP_HDR_SIZE)
#define GET_TCP_SDU(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + GET_TCP_HDR_SIZE2(nbuf,thoff))

#define GET_TCP_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_TCP_HDR_SIZE2(nbuf,thoff)	(TCP_HDR_LEN(GET_TCP_HDR(nbuf,thoff)->doff))
#define GET_IP_TCP_HDR_SIZE2(nbuf,thoff) \
					(GET_IP_HDR_SIZE(GET_IP_HDR(nbuf)) + GET_TCP_HDR_SIZE2(nbuf,thoff))
#define GET_IF_IP_TCP_HDR_SIZE2(nbuf,thoff) \
					(IF_HDR_SIZE + GET_IP_TCP_HDR_SIZE2(nbuf,thoff))

/*
 *  TINET 1.1 �Ȥθߴ����Τ�������
 */

#if defined(SUPPORT_INET4)

#define IP4_TCP_HDR_SIZE		IP_TCP_HDR_SIZE
#define IF_IP4_TCP_HDR_SIZE		IF_IP_TCP_HDR_SIZE
#define GET_IP4_TCP_HDR_SIZE(nbuf)	GET_IP_TCP_HDR_SIZE(nbuf)	
#define GET_IF_IP4_TCP_HDR_SIZE(nbuf)	GET_IF_IP_TCP_HDR_SIZE(nbuf)	

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  TINET 1.3 �Ȥθߴ����Τ�������
 */

#define	TMIN_TCP_CREPID			TMIN_TCP_REPID
#define	TMIN_TCP_CCEPID			TMIN_TCP_CEPID
#define	TNUM_TCP_CREPID			TNUM_TCP_REPID
#define	TNUM_TCP_CCEPID			TNUM_TCP_CEPID

/*
 *  ������Хå��ؿ������
 */

typedef ER	(*t_tcp_callback)(ID cepid, FN fncd, void *p_parblk);

/*
 *  TCP ���ո�
 */

/* IPv4 �� TCP ���ո� */
typedef struct t_tcp4_rep {

	/*
	 * ITRON TCP/IP API��TCP ���ո���Ʊ������
	 */
	ATR		repatr;		/* ���ո�°��		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹	*/

#ifdef TCP_CFG_EXTENTIONS
	uint16_t	flags;		/* ���ո��ե饰		*/
	ID		semid_lock;	/* ���ո���å�		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	} T_TCP4_REP;

/* IPv6 �� TCP ���ո� */
typedef struct t_tcp6_rep {

	/*
	 * ITRON TCP/IP API��TCP ���ո���Ʊ������
	 */
	ATR		repatr;		/* ���ո�°��		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹	*/

#ifdef TCP_CFG_EXTENTIONS
	uint16_t	flags;		/* ���ո��ե饰		*/
	ID		semid_lock;	/* ���ո���å�		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	} T_TCP6_REP;

#if defined(SUPPORT_INET4)
#define T_TCP_REP	T_TCP4_REP
#endif

#if defined(SUPPORT_INET6)
#define T_TCP_REP	T_TCP6_REP
#endif

/*
 *  ���ո��ե饰
 */

#define TCP_REP_FLG_DYNAMIC	UINT_C(0x0400)	/* ưŪ�����������ǽ���ո���	*/
#define TCP_REP_FLG_VALID	UINT_C(0x0800)	/* �����Ѥߤ�ͭ���ʼ��ո���	*/

/*
 *  TCP �̿�ü��
 */

typedef uint32_t T_TCP_SEQ;
typedef uint16_t T_TCP_SEG;
typedef uint16_t T_TCP_WND;

/*
 * �̾�� IPv4 TCP �̿�ü��
 */
typedef struct t_tcp4_cep {

	/*
	 * ITRON TCP/IP API��TCP �̿�ü����Ʊ������
	 */
	ATR		cepatr;		/* �̿�ü��°��			*/
	void		*sbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		sbufsz;		/* �����ѥ�����ɥХåե�������	*/
	void		*rbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		rbufsz;		/* �����ѥ�����ɥХåե�������	*/
	t_tcp_callback	callback;	/* ������Хå��ؿ�		*/

	/*
	 * TINET �ȼ��Υ���
	 */
	uint32_t	flags;		/* �̿�ü���ե饰		*/
	ID		semid_lock;	/* �̿�ü����å�		*/
	ID		est_flgid;	/* ���ͥ��������֥��٥�ȥե饰	*/
	ID		snd_flgid;	/* �������٥�ȥե饰		*/
	ID		rcv_flgid;	/* �������٥�ȥե饰		*/
	ID		snd_tskid;	/* �������������̻�		*/
	ID		rcv_tskid;	/* �������������̻�		*/
	uint8_t		*sbuf_rptr;	/* �������ɤ߽Ф��ݥ���	*/
	uint8_t		*sbuf_wptr;	/* �����ѽ񤭹��ߥݥ���	*/
	uint8_t		*rbuf_rptr;	/* �������ɤ߽Ф��ݥ���	*/
	uint8_t		*rbuf_wptr;	/* �����ѽ񤭹��ߥݥ���	*/
	T_TCP_SEQ	snd_ssthresh;	/* ���ԥ�����ɥ�����(snd_cwnd)	*/
					/* �Τ�������			*/
	T_TCP_TIME	rxtcur;		/* ���ߤκ��������ॢ����	*/
	T_TCP_TIME	srtt;		/* ʿ�경���줿 RTT		*/
	T_TCP_TIME	rttvar;		/* ʿ�경���줿ʬ��		*/
	T_TCP_WND	snd_cwnd;	/* ���ԥ�����ɥ�����		*/

	/*
	 *  ���κ�������������ȥ�����	
	 *
	 *    ���ꥸ�ʥ�Ǥϡ����̤Υ������Ȥκ��祵���� (t_maxseg) �ȡ�
	 *    ���ץ�����դ��Υ������Ȥκ��祵���� (t_maxopd) ���̤�
	 *    �ʤäƤ��롣����ϡ����ߤΥ��󥿡��ͥåȤǤϡ����ץ�����դ���
	 *    �������ȤΤۤ���¿���������������Ƥ��뤿��Ǥ��롣
	 *    �ܼ����Ǥϡ����祻�����ȥ��������ץ����ʳ��Υ��ץ�����
	 *    �������ʤ��Τǡ�t_maxseg �λ��Ѥ��롣
	 */
	T_TCP_SEG	maxseg;

	int16_t		snd_tfn;	/* ����ư����� API ��ǽ������	*/
	int16_t		rcv_tfn;	/* ����ư����� API ��ǽ������	*/

#ifdef TCP_CFG_NON_BLOCKING

	T_IPV4EP 	*p_dstaddr;	/* ���Υ��ɥ쥹�ؤΥݥ���	*/
	T_IPV4EP 	*p_myaddr;	/* ��ʬ�Υ��ɥ쥹�ؤΥݥ���	*/
	int16_t		snd_nblk_tfn;	/* ����ư����� API ��ǽ������	*/
	int16_t		rcv_nblk_tfn;	/* ����ư����� API ��ǽ������	*/
	void		*snd_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		snd_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		*rcv_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		rcv_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		**snd_p_buf;	/* �����Хåե��ؤΥݥ���	*/
	void		**rcv_p_buf;	/* �����Хåե��ؤΥݥ���	*/

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

#ifdef TCP_CFG_SWBUF_CSAVE
	T_NET_BUF	*swbufq;	/* ����������ɥХåե����塼	*/
#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

	/*
	 *  ����ʹߤΥ��С��� tcp_init_cep() �ؿ��ǥ����ꥢ������롣
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP �Υ�����		*/
	T_IPV4EP	dstaddr;	/* ���Υ��ɥ쥹		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	T_TCP4_REP	*rep;		/* ���ո�			*/
	T_NET_BUF	*reassq;	/* �����ƹ������塼		*/

#ifdef TCP_CFG_RWBUF_CSAVE
	T_NET_BUF	*rwbufq;	/* ����������ɥХåե����塼	*/
#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_EXTENTIONS
	T_TCP_HDR	*urg_tcph;	/* �۵ޥǡ�������Υ������Ȥ� TCP �إå�	*/
	T_TCP_SEQ	snd_up;		/* ���������۵ޥݥ���		*/
	T_TCP_SEQ	rcv_up;		/* ���������۵ޥݥ���		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	T_TCP_SEQ	snd_una;	/* ̤��ǧ�κǾ����� SEQ �Ĥޤ�	*/
					/* ��ǧ���줿�������� SEQ	*/
	T_TCP_SEQ	snd_max;	/* ������������ SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* ������������ SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* ���� snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* ���󥦥���ɤ򹹿����� SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* ���󥦥���ɤ򹹿����� ACK	*/
	T_TCP_SEQ	iss;		/* ��ʬ�� SEQ �ν����		*/
	T_TCP_SEQ	irs;		/* ���� SEQ �ν����		*/
	T_TCP_SEQ	rcv_nxt;	/* ��������Ԥ��Ƥ���Ǿ��� SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* ��������Ԥ��Ƥ������� SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* ������ǽ�ʥ�����ɥ�����	*/
	T_TCP_SEQ	rtseq;		/* ���ַ�¬��Ϥ᤿ SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* �Ǹ���������� ACK		*/
	T_TCP_TIME	idle;		/* �����ɥ����			*/
	ER		error;		/* ��Ʊ����ȯ���������顼	*/
	ER		net_error;	/* �ͥåȥ���Υ��顼����	*/
	T_TCP_WND	snd_wnd;	/* ���μ�����ǽ������ɥ�����	*/
	T_TCP_WND	max_sndwnd;	/* ���ޤǤκ�������������ɥ�����	*/
	T_TCP_TIME	rtt;		/* ��������				*/
	uint16_t	swbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint16_t	rwbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf �γ�����Ĺ	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf �γ�����Ĺ	*/
	uint8_t		rxtshift;	/* ����������� log(2)		*/
	uint8_t		fsm_state;	/* FSM ����			*/
	uint8_t		dupacks;	/* ���� ACK ��			*/

#if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)
	uint8_t		rwbufq_entries;	/* ����������ɥХåե����塼�Υ���ȥ��	*/
#endif	/* of #if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)	*/

	} T_TCP4_CEP;

/*
 * Time Wait �� IPv4 TCP �̿�ü��
 */
typedef struct t_tcp4_twcep {
	int_t		rbufsz;		/* �����ѥ�����ɥХåե�������	*/
	T_TCP_TIME	timer_2msl;	/* 2MSL ������			*/
	T_IPV4EP	dstaddr;	/* ���Υ��ɥ쥹		*/
	T_IPV4EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	T_TCP_SEQ	snd_una;	/* ̤��ǧ�κǾ����� SEQ �Ĥޤ�	*/
					/* ��ǧ���줿�������� SEQ	*/
	T_TCP_SEQ	rcv_nxt;	/* ��������Ԥ��Ƥ���Ǿ��� SEQ	*/
	uint16_t	rwbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint8_t		fsm_state;	/* FSM ����			*/

	} T_TCP4_TWCEP;

/*
 * �̾�� IPv6 TCP �̿�ü��
 */
typedef struct t_tcp6_cep {

	/*
	 * ITRON TCP/IP API��TCP �̿�ü����Ʊ������
	 */
	ATR		cepatr;		/* �̿�ü��°��			*/
	void		*sbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		sbufsz;		/* �����ѥ�����ɥХåե�������	*/
	void		*rbuf;		/* �����ѥ�����ɥХåե�	*/
	int_t		rbufsz;		/* �����ѥ�����ɥХåե�������	*/
	t_tcp_callback	callback;	/* ������Хå��ؿ�		*/

	/*
	 * TINET �ȼ��Υ���
	 */
	uint32_t	flags;		/* �̿�ü���ե饰		*/
	ID		semid_lock;	/* �̿�ü����å�		*/
	ID		est_flgid;	/* ���ͥ��������֥��٥�ȥե饰	*/
	ID		snd_flgid;	/* �������٥�ȥե饰		*/
	ID		rcv_flgid;	/* �������٥�ȥե饰		*/
	ID		snd_tskid;	/* �������������̻�		*/
	ID		rcv_tskid;	/* �������������̻�		*/
	uint8_t		*sbuf_rptr;	/* �������ɤ߽Ф��ݥ���		*/
	uint8_t		*sbuf_wptr;	/* �����ѽ񤭹��ߥݥ���		*/
	uint8_t		*rbuf_rptr;	/* �������ɤ߽Ф��ݥ���		*/
	uint8_t		*rbuf_wptr;	/* �����ѽ񤭹��ߥݥ���		*/
	T_TCP_SEQ	snd_ssthresh;	/* ���ԥ�����ɥ�����(snd_cwnd)	*/
					/* �Τ�������			*/
	T_TCP_TIME	rxtcur;		/* ���ߤκ��������ॢ����		*/
	T_TCP_TIME	srtt;		/* ʿ�경���줿 RTT		*/
	T_TCP_TIME	rttvar;		/* ʿ�경���줿ʬ��		*/
	T_TCP_WND	snd_cwnd;	/* ���ԥ�����ɥ�����		*/

	/*
	 *  ���κ�������������ȥ�����	
	 *
	 *    ���ꥸ�ʥ�Ǥϡ����̤Υ������Ȥκ��祵���� (t_maxseg) �ȡ�
	 *    ���ץ�����դ��Υ������Ȥκ��祵���� (t_maxopd) ���̤�
	 *    �ʤäƤ��롣����ϡ����ߤΥ��󥿡��ͥåȤǤϡ����ץ�����դ���
	 *    �������ȤΤۤ���¿���������������Ƥ��뤿��Ǥ��롣
	 *    �ܼ����Ǥϡ����祻�����ȥ��������ץ����ʳ��Υ��ץ�����
	 *    �������ʤ��Τǡ�t_maxseg �λ��Ѥ��롣
	 */
	T_TCP_SEG	maxseg;

	T_IPV6EP 	*p_dstaddr;	/* ���Υ��ɥ쥹�ؤΥݥ���	*/
	T_IPV6EP 	*p_myaddr;	/* ��ʬ�Υ��ɥ쥹�ؤΥݥ���	*/
	int16_t		snd_tfn;	/* ����ư����� API ��ǽ������	*/
	int16_t		rcv_tfn;	/* ����ư����� API ��ǽ������	*/

#ifdef TCP_CFG_NON_BLOCKING

	int16_t		snd_nblk_tfn;	/* ����ư����� API ��ǽ������	*/
	int16_t		rcv_nblk_tfn;	/* ����ư����� API ��ǽ������	*/
	void		*snd_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		snd_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		*rcv_data;	/* �����ǡ����ΰ����Ƭ���ɥ쥹	*/
	int_t		rcv_len;	/* �����ǡ����ΰ��Ĺ��		*/
	void		**snd_p_buf;	/* �����Хåե��ؤΥݥ���	*/
	void		**rcv_p_buf;	/* �����Хåե��ؤΥݥ���	*/

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

#ifdef TCP_CFG_SWBUF_CSAVE
	T_NET_BUF	*swbufq;	/* ����������ɥХåե����塼	*/
#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

	/*
	 *  ����ʹߤΥ��С��� tcp_init_cep() �ؿ��ǥ����ꥢ������롣
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP �Υ�����		*/
	T_IPV6EP	dstaddr;	/* ���Υ��ɥ쥹		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	T_TCP6_REP	*rep;		/* ���ո�			*/
	T_NET_BUF	*reassq;	/* �����ƹ������塼		*/

#ifdef TCP_CFG_RWBUF_CSAVE
	T_NET_BUF	*rwbufq;	/* ����������ɥХåե����塼	*/
#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_EXTENTIONS
	T_TCP_HDR	*urg_tcph;	/* �۵ޥǡ�������Υ������Ȥ� TCP �إå�	*/
	T_TCP_SEQ	snd_up;		/* ���������۵ޥݥ���		*/
	T_TCP_SEQ	rcv_up;		/* ���������۵ޥݥ���		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	T_TCP_SEQ	snd_una;	/* ̤��ǧ�κǾ����� SEQ �Ĥޤ�	*/
					/* ��ǧ���줿�������� SEQ	*/
	T_TCP_SEQ	snd_max;	/* ������������ SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* ������������ SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* ���� snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* ���󥦥���ɤ򹹿����� SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* ���󥦥���ɤ򹹿����� ACK	*/
	T_TCP_SEQ	iss;		/* ��ʬ�� SEQ �ν����		*/
	T_TCP_SEQ	irs;		/* ���� SEQ �ν����		*/
	T_TCP_SEQ	rcv_nxt;	/* ��������Ԥ��Ƥ���Ǿ��� SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* ��������Ԥ��Ƥ������� SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* ������ǽ�ʥ�����ɥ�����	*/
	T_TCP_SEQ	rtseq;		/* ���ַ�¬��Ϥ᤿ SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* �Ǹ���������� ACK		*/
	T_TCP_TIME	idle;		/* �����ɥ����			*/
	ER		error;		/* ��Ʊ����ȯ���������顼		*/
	ER		net_error;	/* �ͥåȥ���Υ��顼����	*/
	T_TCP_WND	snd_wnd;	/* ���μ�����ǽ������ɥ�����	*/
	T_TCP_WND	max_sndwnd;	/* ���ޤǤκ�������������ɥ�����	*/
	T_TCP_TIME	rtt;		/* ��������			*/
	uint16_t	swbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint16_t	rwbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf �γ�����Ĺ	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf �γ�����Ĺ	*/
	uint8_t		rxtshift;	/* ����������� log(2)		*/
	uint8_t		fsm_state;	/* FSM ����			*/
	uint8_t		dupacks;	/* ���� ACK ��			*/

#if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)
	uint8_t		rwbufq_entries;	/* ����������ɥХåե����塼�Υ���ȥ��	*/
#endif	/* of #if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)	*/

	} T_TCP6_CEP;

/*
 * Time Wait �� IPv6 TCP �̿�ü��
 */
typedef struct t_tcp6_twcep {
	int_t		rbufsz;		/* �����ѥ�����ɥХåե�������	*/
	T_TCP_TIME	timer_2msl;	/* 2MSL ������			*/
	T_IPV6EP	dstaddr;	/* ���Υ��ɥ쥹		*/
	T_IPV6EP	myaddr;		/* ��ʬ�Υ��ɥ쥹		*/
	T_TCP_SEQ	snd_una;	/* ̤��ǧ�κǾ����� SEQ �Ĥޤ�	*/
					/* ��ǧ���줿�������� SEQ	*/
	T_TCP_SEQ	iss;		/* ��ʬ�� SEQ �ν����		*/
	T_TCP_SEQ	irs;		/* ���� SEQ �ν����		*/
	T_TCP_SEQ	rcv_nxt;	/* ��������Ԥ��Ƥ���Ǿ��� SEQ	*/
	T_TCP_WND	snd_wnd;	/* ���μ�����ǽ������ɥ�����	*/
	uint16_t	rwbuf_count;	/* ����������ɥХåե��λ����極����	*/
	uint8_t		fsm_state;	/* FSM ����			*/

	} T_TCP6_TWCEP;

#if defined(SUPPORT_INET4)
#define T_TCP_CEP	T_TCP4_CEP
#define T_TCP_TWCEP	T_TCP4_TWCEP
#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)
#define T_TCP_CEP	T_TCP6_CEP
#define T_TCP_TWCEP	T_TCP6_TWCEP
#endif	/* of #if defined(SUPPORT_INET6) */

#define T_TCP_CEP_DEFINED

/*
 *  TCP �̿�ü���ξ��֥ե饰
 */

#define TCP_CEP_FLG_ACK_NOW		ULONG_C(0x00000001)	/* ľ�������� ACK �����롣	*/
#define TCP_CEP_FLG_DEL_ACK		ULONG_C(0x00000002)	/* ACK ���ٱ䤹�롣		*/
#define TCP_CEP_FLG_SENT_FIN		ULONG_C(0x00000004)	/* FIN �����äƤ��롣		*/
#define TCP_CEP_FLG_NEED_SYN		ULONG_C(0x00000008)	/* SYN ���������롣		*/
#define TCP_CEP_FLG_NEED_FIN		ULONG_C(0x00000010)	/* FIN ���������롣		*/
#define TCP_CEP_FLG_FORCE		ULONG_C(0x00000020)	/* ����������			*/
#define TCP_CEP_FLG_NO_PUSH		ULONG_C(0x00000040)	/* push ���ʤ���		*/
#define TCP_CEP_FLG_NO_DELAY		ULONG_C(0x00000080)	/* �ٱ䤷�ʤ���			*/
#define TCP_CEP_FLG_FORCE_CLEAR		ULONG_C(0x00000100)	/* ��������������ե饰�򥯥ꥢ�����롣*/
#define TCP_CEP_FLG_POST_OUTPUT		ULONG_C(0x00000200)	/* �����򳫻Ϥ��롣		*/
#define TCP_CEP_FLG_RESERVE_OUTPUT	ULONG_C(0x00000400)	/* ������ͽ�󤹤롣		*/
#define TCP_CEP_FLG_DYNAMIC		ULONG_C(0x00001000)	/* ưŪ�����������ǽ�̿�ü����	*/
#define TCP_CEP_FLG_VALID		ULONG_C(0x00002000)	/* �����Ѥߤ�ͭ�����̿�ü����	*/
#define TCP_CEP_FLG_CLOSE_AFTER_OUTPUT	ULONG_C(0x00004000)	/* ���������女�ͥ��������Ĥ��롣*/
#define TCP_CEP_FLG_RESTORE_NEXT_OUTPUT	ULONG_C(0x00008000)	/* ���������塢snd_nxt �򸵤��᤹��*/

/* ������������ɥХåե��ξʥ��ԡ���ǽ */
#define TCP_CEP_FLG_WBCS_NBUF_REQ	ULONG_C(0x00080000)	/* �ͥåȥ���Хåե��������׵�	*/
#define TCP_CEP_FLG_WBCS_MASK		ULONG_C(0x00070000)	/* �ޥ���			*/
#define TCP_CEP_FLG_WBCS_FREE		ULONG_C(0x00000000)	/* ����������ɥХåե�̤����	*/
#define TCP_CEP_FLG_WBCS_WOPEN_PEND	ULONG_C(0x00010000)	/* ���μ���������ɤγ����Ԥ�	*/
#define TCP_CEP_FLG_WBCS_NBUF_PEND	ULONG_C(0x00020000)	/* �ͥåȥ���Хåե�ͽ���Ԥ�	*/
#define TCP_CEP_FLG_WBCS_NBUF_RSVD	ULONG_C(0x00030000)	/* �ͥåȥ���Хåե�ͽ��Ѥ�	*/
#define TCP_CEP_FLG_WBCS_NBUF_READY	ULONG_C(0x00040000)	/* �ͥåȥ���Хåե������ƺѤ�	*/
#define TCP_CEP_FLG_WBCS_SEND_READY	ULONG_C(0x00050000)	/* ������ǽ			*/
#define TCP_CEP_FLG_WBCS_SENT		ULONG_C(0x00060000)	/* �����Ѥߤǡ�ACK�Ԥ�		*/
#define TCP_CEP_FLG_WBCS_ACKED		ULONG_C(0x00070000)	/* �����Ѥߤǡ�ACK��λ		*/

/*
 *  �̿�ü�����٥�ȥե饰
 */

#define TCP_CEP_EVT_ESTABLISHED		ULONG_C(0x00000001)	/* ���ͥ�������Ω		*/
#define TCP_CEP_EVT_CLOSED		ULONG_C(0x00000002)	/* ̤���Ѿ���			*/
#define TCP_CEP_EVT_SWBUF_READY		ULONG_C(0x00000004)	/* ����������ɥХåե�����	*/
#define TCP_CEP_EVT_RWBUF_READY		ULONG_C(0x00000008)	/* ����������ɥХåե��ǡ�������	*/
#define TCP_CEP_EVT_ALL			ULONG_C(0xffffffff)	/* �����٥��			*/

/*
 *  �ɲ� API ��ǽ�����ݥ�����
 */

/* TCP �ط� */

#define TFN_TCP_UNDEF		(0)

/*
 *  srtt:   ʿ�경���줿 RTT
 *  rttvar: ʿ�경���줿ʬ��
 *  rtt:    ¬�ꤵ�줿��������
 *
 *  ʿ�경���줿 RTT (srtt) ��ʿ�경���줿ʬ�� (rttvar) ��
 *  �������Ƿ׻����뤿��ˡ������եȤ��ƥ������뤹�롣
 *  srtt �� 2 �ʾ������ʲ� 3 �ӥåȡ�
 *  rttvar �� 2 �ʾ������ʲ� 2 �ӥåȤ��ݻ����롣
 */

#define TCP_DELTA_SHIFT		2
			/* ��ʬ = rtt/8 + srtt*7/8 �η׻��Τ���Υ��ե���	*/
#define TCP_SRTT_SHIFT		(TCP_DELTA_SHIFT + 3)
					/* srtt �Υ��ե��͡�3(+2)�ӥå�	*/
#define TCP_RTTVAR_SHIFT	(TCP_DELTA_SHIFT + 2)
					/* rttvar �Υ��ե��͡�2(+2)�ӥå�	*/
#define TCP_SRTT_SCALE		(1<<TCP_SRTT_SHIFT)
#define TCP_RTTVAR_SCALE	(1<<TCP_RTTVAR_SHIFT)

/*
 *  ��®��ž���򳫻Ϥ������ ACK ���Τ�������
 */

#define MAX_TCP_REXMT_THRESH	3

/*
 *  �����ƹ������塼�Ǥ� TCP �إå�
 */

typedef struct t_tcp_q_hdr {
	uint16_t	sport;		/* �������ݡ����ֹ�			*/
	uint16_t	dport;		/* ����ݡ����ֹ�			*/

	uint32_t	seq;		/* SEQ �ֹ�				*/

	T_NET_BUF 	*next;		/* ���Υ������ȡ����� ACK �ֹ�(ack)	*/

	uint8_t		doff;		/* �ǡ������ե��å�(���4�ӥå�)	*/
	uint8_t		flags;		/* �ե饰(����6�ӥå�)			*/
	uint16_t	soff;		/* SDU ���ե��åȡ����ϥ�����ɥ�����(win)	*/

	uint16_t	slen;		/* SDU Ĺ�����ϥ����å�����(sum)	*/
	uint16_t	urp;		/* �۵ޥݥ��󥿡�SDU Ĺ������		*/
	} T_TCP_Q_HDR;

#define GET_TCP_Q_HDR(nbuf,thoff)	((T_TCP_Q_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_IP_Q_HDR(nbuf)		((T_TCP_IP_Q_HDR*)GET_IP_HDR(nbuf))

/*
 *  ���֥������� ID �κǾ��ͤ����
 */

#define	TMIN_TCP_REPID		1	/* TCP ���ո�   ID �κǾ���			*/
#define	TMIN_TCP_CEPID		1	/* TCP �̿�ü�� ID �κǾ���			*/
#define	TMIN_TCP_TWCEPID	1	/* Time Wait �� TCP �̿�ü�� ID �κǾ���	*/

/*
 *  ���楻�����ȡʥǡ����ʤ��˥������Υͥåȥ���Хåե�
 */

typedef struct t_net_buf_cseg {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_HDR_SIZE + IP_HDR_SIZE + TCP_HDR_SIZE];
				/* �Хåե�����		*/
	} T_NET_BUF_CSEG;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

typedef struct t_tcp_stats {
	uint32_t	tcpActiveOpens;
	uint32_t	tcpPassiveOpens;
	uint32_t	tcpAttemptFails;
	uint32_t	tcpEstabResets;
/*	uint32_t	tcpCurrEstab;*/
	uint32_t	tcpInSegs;
	uint32_t	tcpOutSegs;
	uint32_t	tcpRetransSegs;
	uint32_t	tcpInErrs;
	uint32_t	tcpOutRsts;
} T_TCP_STATS;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �ؿ����ߥ�졼�����ޥ���
 */

#define VAID_TCP_REPID(id)	(TMIN_TCP_REPID<=(id)&&(id)<=tmax_tcp_repid)
#define VAID_TCP_CEPID(id)	(TMIN_TCP_CEPID<=(id)&&(id)<=tmax_tcp_cepid)

#define INDEX_TCP_REP(id)	((id)-TMIN_TCP_REPID)
#define INDEX_TCP_CEP(id)	((id)-TMIN_TCP_CEPID)

#define GET_TCP_REP(id)		(&(tcp_rep[INDEX_TCP_REP(id)]))
#define GET_TCP_CEP(id)		(&(tcp_cep[INDEX_TCP_CEP(id)]))

#define GET_TCP_REPID(rep)	((ID)(((rep)-tcp_rep)+TMIN_TCP_REPID))
#define GET_TCP_CEPID(cep)	((ID)(((cep)-tcp_cep)+TMIN_TCP_CEPID))
#define GET_TCP_TWCEPID(cep)	((ID)(((cep)-tcp_twcep)+TMIN_TCP_TWCEPID))

#define IS_TFN_TCP_RCV(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_RCV_BUF||(t)==TFN_TCP_REL_BUF||\
				 (t)==TFN_TCP_RCV_OOB)

#define VALID_TFN_TCP_CAN(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_CON_CEP||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_SND_DAT||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_GET_BUF||(t)==TFN_TCP_RCV_BUF||\
				 (t)==TFN_TCP_SND_OOB||\
				 (t)==TFN_TCP_ALL)

#define VALID_URG_POINTER(urg)	(TCP_CFG_URG_OFFSET==0||urg!=0)

#define VALID_TCP_CEP(cep)	(((cep)->flags&TCP_CEP_FLG_VALID)!=0)
#define DYNAMIC_TCP_CEP(cep)	(((cep)->flags&TCP_CEP_FLG_DYNAMIC)!=0)

#ifdef TCP_CFG_EXTENTIONS

#define VALID_TCP_REP(rep)	(((rep)->flags&TCP_REP_FLG_VALID)!=0)
#define DYNAMIC_TCP_REP(rep)	(((rep)->flags&TCP_REP_FLG_DYNAMIC)!=0)

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

#define VALID_TCP_REP(rep)	(true)
#define DYNAMIC_TCP_REP(rep)	(false)

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

/*
 *  �����ѿ�
 */

extern T_TCP_REP tcp_rep[];
extern T_TCP_CEP tcp_cep[];
extern uint8_t tcp_initialized;
extern const ID tmax_tcp_repid;
extern const ID tmax_tcp_cepid;
extern T_TCP_TWCEP tcp_twcep[];

#ifdef SUPPORT_MIB

extern T_TCP_STATS tcp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  Inline �ؿ�
 */

#ifndef TCP_CFG_RWBUF_CSAVE

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��
 *  ̵���ξ��ϲ��⤷�ʤ�����Υ��ߡ��δؿ�
 */

/*
 *  tcp_free_rwbufq -- ����������ɥХåե����塼��������롣
 */

Inline void
tcp_free_rwbufq_ncs (T_TCP_CEP *cep)
{
	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ�Τߤ�
 *  ͭ���ξ��ϲ��⤷�ʤ�����Υ��ߡ��δؿ�
 */

/*
 *  tcp_read_swbuf_cs -- ����������ɥХåե�����ǡ������ɤ߽Ф���
 */

Inline void
tcp_read_swbuf_cs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#ifndef TCP_CFG_SWBUF_CSAVE

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ��
 *  ̵���ξ��ϲ��⤷�ʤ�����Υ��ߡ��δؿ�
 */

/*
 *  tcp_free_swbufq -- ����������ɥХåե����塼��������롣
 */

Inline void
tcp_free_swbufq_ncs (T_TCP_CEP *cep)
{
	}

/*
 *  tcp_alloc_swbuf -- ����������ɥХåե��ѤΥͥåȥ���Хåե��γ�����Ƥ�ؼ����롣
 */

Inline void
tcp_alloc_swbuf_ncs (T_TCP_CEP *cep)
{
	}

/*
 *  tcp_push_res_nbuf -- �ͥåȥ���Хåե���ͽ�󤹤롣
 */

Inline T_NET_BUF *
tcp_push_res_nbuf_ncs (T_NET_BUF *nbuf)
{
	return nbuf;
	}

/*
 *  tcp_pull_res_nbuf -- ͽ�󤷤Ƥ���ͥåȥ���Хåե��֤���
 */

Inline T_NET_BUF *
tcp_pull_res_nbuf_ncs (ATR nbatr)
{
	return NULL;
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE */

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ���ڤ��ؤ��ޥ���
 */

#ifdef TCP_CFG_RWBUF_CSAVE

#ifdef TCP_CFG_RWBUF_CSAVE_ONLY

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq_cs(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf_cs(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf_cs(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr_cs(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf_cs(cep,input,thoff)

#else	/* of #ifdef TCP_CFG_RWBUF_CSAVE_ONLY */

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf(cep,input,thoff)

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_ONLY */

#else	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq_ncs(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf_ncs(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf_ncs(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr_ncs(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf_ncs(cep,input,thoff)

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ���ڤ��ؤ��ޥ���
 */

#ifdef TCP_CFG_SWBUF_CSAVE

#define TCP_PUSH_RES_NBUF(nbuf)			tcp_push_res_nbuf(nbuf)
#define TCP_PULL_RES_NBUF(atr)			tcp_pull_res_nbuf(atr)

#ifdef TCP_CFG_SWBUF_CSAVE_ONLY

#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq_cs(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf_cs(cep)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf_cs(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf_cs(cep,data,len)
#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf_cs(cep,output,len,doff)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf_cs(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr_cs(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf_cs(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full_cs(cep)

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf(cep)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf(cep,data,len)
#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf(cep,output,len,doff)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full(cep)

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf_ncs(cep,output,len,doff)
#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq_ncs(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf_ncs(cep)
#define TCP_PUSH_RES_NBUF(nbuf)			tcp_push_res_nbuf_ncs(nbuf)
#define TCP_PULL_RES_NBUF(atr)			tcp_pull_res_nbuf_ncs(atr)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf_ncs(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf_ncs(cep,data,len)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf_ncs(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr_ncs(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf_ncs(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full_ncs(cep)

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

/*
 *  �ؿ�
 */

extern uint_t tcp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void tcp_init (void);
extern void tcp_init_iss (void);
extern T_TCP_CEP *tcp_close (T_TCP_CEP *cep);
extern T_TCP_CEP *tcp_drop  (T_TCP_CEP *cep, ER errno);
extern void tcp_respond (T_NET_BUF *nbuf, T_TCP_CEP *cep,
                         T_TCP_SEQ ack, T_TCP_SEQ seq, uint_t rbfree, uint8_t flags);
extern void tcp_set_header (T_NET_BUF *nbuf, T_TCP_CEP *cep, uint_t thoff, uint_t optlen);
extern ER tcp_get_segment (T_NET_BUF **nbuf, T_TCP_CEP *cep,
                           uint_t optlen, uint_t len, uint_t maxlen, ATR nbatr, TMO tmout);
extern void tcp_init_cep (T_TCP_CEP *cep);
extern void tcp_notify (T_NET_BUF *input, int code);
extern T_TCP_TIME tcp_rexmt_val (T_TCP_CEP *cep);
extern void tcp_set_persist_timer (T_TCP_CEP *cep);
extern void tcp_cancel_timers (T_TCP_CEP *cep);
extern void tcp_alloc_auto_port (T_TCP_CEP *cep);
extern ER tcp_alloc_port (T_TCP_CEP *cep, uint16_t portno);
extern void tcp_move_twcep (T_TCP_CEP *cep);
extern ER tcp_lock_cep (ID cepid, T_TCP_CEP **p_cep, FN tfn);
extern void tcp_free_reassq (T_TCP_CEP *cep);
extern ER tcp_can_send_more (T_TCP_CEP *cep, FN fncd, TMO tmout);
extern ER tcp_can_recv_more (ER *error, T_TCP_CEP *cep, FN fncd, TMO tmout);
extern uint8_t tcp_move_ra2rw (T_TCP_CEP *cep, uint8_t flags);
extern uint8_t tcp_write_raque (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags);
extern ER tcp_wait_rwbuf (T_TCP_CEP *cep, TMO tmout);
extern T_TCP_CEP *tcp_user_closed (T_TCP_CEP *cep);

/*
 *  TCP �̿�ü���μ���������ɥХåե��Ѵؿ�
 */

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ξ�硢
 *  �ؿ�������˻��Ѥ��롣
 */

extern void tcp_free_rwbufq (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �̿�ü���μ���������ɥХåե��ξʥ��ԡ���ǽ�Ѵؿ�
 */

extern void tcp_free_rwbufq_cs (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf_cs (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf_cs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf_cs (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr_cs (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �̿�ü���μ���������ɥХåե��Ρ���۾ʥ��ԡ���ǽ�Ѵؿ�
 */

extern void tcp_free_rwbufq_ncs (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �̿�ü��������������ɥХåե��Ѵؿ�
 */

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ��ͭ���ξ�硢
 *  �ؿ�������˻��Ѥ��롣
 */

extern void tcp_free_swbufq (T_TCP_CEP *cep);
extern void tcp_drop_swbuf (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf (T_TCP_CEP *cep, TMO tmout);
extern T_NET_BUF *tcp_push_res_nbuf (T_NET_BUF *buf);
extern T_NET_BUF *tcp_pull_res_nbuf (ATR nbatr);
extern void tcp_alloc_swbuf (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full (T_TCP_CEP *cep);
extern void tcp_init_swbuf (T_TCP_CEP *cep);

/*
 *  TCP �̿�ü��������������ɥХåե��ξʥ��ԡ���ǽ�Ѵؿ�
 */

extern void tcp_free_swbufq_cs (T_TCP_CEP *cep);
extern void tcp_drop_swbuf_cs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf_cs (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf_cs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf_cs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr_cs (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf_cs (T_TCP_CEP *cep, TMO tmout);
extern void tcp_alloc_swbuf_cs (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full_cs (T_TCP_CEP *cep);

/*
 *  TCP �̿�ü��������������ɥХåե��Ρ���۾ʥ��ԡ���ǽ�Ѵؿ�
 */

extern void tcp_free_swbufq_ncs (T_TCP_CEP *cep);
extern void tcp_drop_swbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf_ncs (T_TCP_CEP *cep, TMO tmout);
extern T_NET_BUF *tcp_push_res_nbuf_ncs (T_NET_BUF *buf);
extern T_NET_BUF *tcp_pull_res_nbuf_ncs (ATR nbatr);
extern void tcp_alloc_swbuf_ncs (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full_ncs (T_TCP_CEP *cep);

/*
 *  tcp_find_cep -- �ݡ����ֹ椫�� TCP �̿�ü�������롣
 *
 *    ���: myaddr �ϡ�
 *          TINET-1.2 ����ͥåȥ���Х��ȥ�������
 *          TINET-1.1 �ޤǤϡ��ۥ��ȥХ��ȥ�����
 */
extern T_TCP_CEP *tcp_find_cep (T_IN_ADDR *dstaddr,  uint16_t dstport,
                                T_IN_ADDR *peeraddr, uint16_t peerport);

/*
 *  TCP �إå��Υȥ졼�����ϵ�ǽ�Ѵؿ�
 */
extern void tcp_output_trace (T_NET_BUF *output, T_TCP_CEP *cep);
extern void tcp_input_trace  (T_NET_BUF *input,  T_TCP_CEP *cep);

/* TCP ���ϥ����� */

extern void	tcp_output_task(intptr_t exinf);

#endif	/* of #ifndef _TCP_VAR_H_ */
