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
 *  @(#) $Id: netapp_var.h,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

#ifndef _NETAPP_VAR_H_
#define _NETAPP_VAR_H_

/*
 *  �ޥ������
 */

#if defined(SUPPORT_INET4)
#define T_IPEP		T_IPV4EP
#endif

#if defined(SUPPORT_INET6)
#define T_IPEP		T_IPV6EP
#endif

/*
 *  �ͥåȥ����ͳ���󥽡���������
 */

#ifdef USE_NET_CONS

/* ��͡��� */

#define syslog		net_syslog
#define serial_ctl_por	net_serial_ctl_por

/* �ؿ����ߥ�졼�����ޥ��� */

#define FLUSH_SND_BUFF()	flush_snd_buff()
#define WAI_NET_CONS_PRINTF()	syscall(wai_sem(SEM_NET_CONS_PRINTF))
#define SIG_NET_CONS_PRINTF()	sig_sem(SEM_NET_CONS_PRINTF)

#else	/* of #ifdef USE_NET_CONS */

/* �ؿ����ߥ�졼�����ޥ��� */

#define FLUSH_SND_BUFF()
#define WAI_NET_CONS_PRINTF()
#define SIG_NET_CONS_PRINTF()

#endif	/* of #ifdef USE_NET_CONS */

/*
 *  �ؿ�
 */

extern const char *in_strtfn (FN fncd);
extern const char *itron_strerror (ER ercd);
extern ER	net_syslog(uint_t prio, const char *format, ...) throw();
extern ER	net_serial_ctl_por(ID portid, uint_t ioctl) throw();
extern void	flush_snd_buff (void);
extern ER	discon_net_cons (void);
extern void	wup_net_cons (void);
extern ER	alloc_tcp_rep (ID *repid, ID tskid, T_TCP_CREP *crep);
extern ER	free_tcp_rep (ID repid, bool_t call_tcp_del_rep);
extern ER	alloc_tcp_cep (ID *cepid, ID tskid, T_TCP_CCEP *ccep);
extern ER	free_tcp_cep (ID cepid);
extern ER	alloc_udp_cep (ID *cepid, ID tskid, T_UDP_CCEP *ccep);
extern ER	free_udp_cep (ID cepid, bool_t call_udp_del_cep);

#if defined(SUPPORT_INET4)

#define TCP_CRE_REP(i,r)	tcp_cre_rep(i,r)
#define TCP_CRE_CEP(i,c)	tcp_cre_cep(i,c)
#define UDP_CRE_CEP(i,c)	udp_cre_cep(i,c)
#define TCP_ACP_CEP(c,r,d,t)	tcp_acp_cep(c,r,d,t)
#define TCP_CON_CEP(c,m,d,t)	tcp_con_cep(c,m,d,t)

#define UDP_SND_DAT(c,d,b,l,t)	udp_snd_dat(c,d,b,l,t)
#define UDP_RCV_DAT(c,d,b,l,t)	udp_rcv_dat(c,d,b,l,t)

#define IP2STR(s,a)		ip2str(s,a)

#define GET_IPADDR(a,l)		get_ipv4addr(a,l)
#define PING(a,t,l)		ping4(a,t,l)

extern void ping4 (T_IN4_ADDR *addr, uint_t tmo, uint_t len);
extern char *get_ipv4addr (T_IN4_ADDR *addr, char *line);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_CRE_REP(i,r)	tcp6_cre_rep(i,r)
#define TCP_CRE_CEP(i,c)	tcp6_cre_cep(i,c)
#define UDP_CRE_CEP(i,c)	udp6_cre_cep(i,c)
#define TCP_ACP_CEP(c,r,d,t)	tcp6_acp_cep(c,r,d,t)
#define TCP_CON_CEP(c,m,d,t)	tcp6_con_cep(c,m,d,t)

#define UDP_SND_DAT(c,d,b,l,t)	udp6_snd_dat(c,d,b,l,t)
#define UDP_RCV_DAT(c,d,b,l,t)	udp6_rcv_dat(c,d,b,l,t)

#define IP2STR(s,a)		ipv62str(s,a)

#define GET_IPADDR(a,l)		get_ipv6addr(a,l)
#define PING(a,t,l)		ping6(a,t,l)

extern void ping6 (T_IN6_ADDR *addr, uint_t tmo, uint_t len);
extern char *get_ipv6addr (T_IN6_ADDR *addr, char *line);

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #ifndef _NETAPP_VAR_H_ */
