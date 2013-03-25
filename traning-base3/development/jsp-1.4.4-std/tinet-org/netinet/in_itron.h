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
 *  @(#) $Id: in_itron.h,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */
 
#ifndef _IN_ITRON_H_
#define _IN_ITRON_H_

/*
 *  API ��ǽ�����ݥ�����
 */

/* TCP �ط� */

#define TFN_TCP_CRE_REP		(-0x201)
#define TFN_TCP_DEL_REP		(-0x202)
#define TFN_TCP_CRE_CEP		(-0x203)
#define TFN_TCP_DEL_CEP		(-0x204)
#define TFN_TCP_ACP_CEP		(-0x205)
#define TFN_TCP_CON_CEP		(-0x206)
#define TFN_TCP_SHT_CEP		(-0x207)
#define TFN_TCP_CLS_CEP		(-0x208)
#define TFN_TCP_SND_DAT		(-0x209)
#define TFN_TCP_RCV_DAT		(-0x20a)
#define TFN_TCP_GET_BUF		(-0x20b)
#define TFN_TCP_SND_BUF		(-0x20c)
#define TFN_TCP_RCV_BUF		(-0x20d)
#define TFN_TCP_REL_BUF		(-0x20e)
#define TFN_TCP_SND_OOB		(-0x20f)
#define TFN_TCP_RCV_OOB		(-0x210)
#define TFN_TCP_CAN_CEP		(-0x211)
#define TFN_TCP_SET_OPT		(-0x212)
#define TFN_TCP_GET_OPT		(-0x213)
#define TFN_TCP_ALL		(0)

#define TEV_TCP_RCV_OOB		(-0x201)

/* UDP �ط� */

#define TFN_UDP_CRE_CEP		(-0x221)
#define TFN_UDP_DEL_CEP		(-0x222)
#define TFN_UDP_SND_DAT		(-0x223)
#define TFN_UDP_RCV_DAT		(-0x224)
#define TFN_UDP_CAN_CEP		(-0x225)
#define TFN_UDP_SET_OPT		(-0x226)
#define TFN_UDP_GET_OPT		(-0x227)
#define TFN_UDP_ALL		(0)

#define TEV_UDP_RCV_DAT		(-0x221)

/* ���� */

#define NADR			((void*)(-1))	/* ̵�����ɥ쥹 */
#define IS_PTR_DEFINED(a)	((void*)(a)!=NADR&&(void*)(a)!=NULL)
#define TCP_REP_NONE		UINT_C(0)
#define TCP_CEP_NONE		UINT_C(0)
#define UDP_CEP_NONE		UINT_C(0)

/*
 *  �ؿ�
 */

/* TCP �ط� */

/* ��ɸ�ൡǽ�� */

extern ER	tcp_acp_cep (ID cepid, ID repid, T_IPV4EP *p_dstaddr, TMO tmout);
extern ER	tcp_con_cep (ID cepid, T_IPV4EP *p_myaddr, T_IPV4EP *p_dstaddr, TMO tmout);
extern ER	tcp_sht_cep (ID cepid);
extern ER	tcp_cls_cep (ID cepid, TMO tmout);
extern ER_UINT	tcp_snd_dat (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_rcv_dat (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_get_buf (ID cepid, void **p_buf, TMO tmout);
extern ER	tcp_snd_buf (ID cepid, int_t len);
extern ER_UINT	tcp_rcv_buf (ID cepid, void **p_buf, TMO tmout);
extern ER	tcp_rel_buf (ID cepid, int_t len);
extern ER	tcp_can_cep (ID cepid, FN fncd);

extern ER	tcp6_acp_cep (ID cepid, ID repid, T_IPV6EP *p_dstaddr, TMO tmout);
extern ER	tcp6_con_cep (ID cepid, T_IPV6EP *p_myaddr, T_IPV6EP *p_dstaddr, TMO tmout);

/* �ڳ�ĥ��ǽ�� */

extern ER	tcp_del_rep (ID cepid);
extern ER	tcp_cre_cep (ID cepid, T_TCP_CCEP *pk_crep);
extern ER	tcp_del_cep (ID cepid);
extern ER_UINT	tcp_snd_oob (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_rcv_oob (ID cepid, void *data, int_t len);
extern ER	tcp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	tcp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	tcp_cre_rep (ID repid, T_TCP_CREP *pk_crep);

extern ER	tcp6_cre_rep (ID repid, T_TCP6_CREP *pk_crep);

/* UDP �ط� */

/* ��ɸ�ൡǽ�� */

extern ER_UINT	udp_snd_dat (ID cepid, T_IPV4EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER_UINT	udp_rcv_dat (ID cepid, T_IPV4EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER	udp_can_cep (ID cepid, FN fncd);

extern ER_UINT	udp6_snd_dat (ID cepid, T_IPV6EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER_UINT	udp6_rcv_dat (ID cepid, T_IPV6EP *p_dstaddr, void *data, int_t len, TMO tmout);

/* �ڳ�ĥ��ǽ�� */

extern ER	udp_del_cep (ID cepid);
extern ER	udp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	udp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	udp_cre_cep (ID cepid, T_UDP_CCEP *pk_ccep);

extern ER	udp6_cre_cep (ID cepid, T_UDP6_CCEP *pk_ccep);

#endif	/* of #ifndef _IN_ITRON_H_ */
