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
 *  @(#) $Id: net_rename.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

#ifndef _NET_RENAME_H_
#define _NET_RENAME_H_

/*
 *  ���ѥͥåȥ�����󥿥ե���������̾�Υ�͡���
 */

/* net/ethernet.c */

#define ether_broad_cast_addr	_tinet_ether_broad_cast_addr
#define ether_ipv4_addr_local	_tinet_ether_ipv4_addr_local
#define ether_ipv4_addr_local_mask	\
				_tinet_ether_ipv4_addr_local_mask

#define	ether_raw_output	_tinet_ether_raw_output
#define ether_output		_tinet_ether_output
#define ether_in6_ifaddr	_tinet_ether_in6_ifaddr
#define ether_in6_ifaddr_list	_tinet_ether_in6_ifaddr_list
#define ether_in6_resolve_multicast	\
				_tinet_ether_in6_resolve_multicast
#define ether_input_task	_tinet_ether_input_task
#define ether_get_ifnet		_tinet_ether_get_ifnet
#define ether_output_task	_tinet_ether_output_task

/* net/if.c */

#ifdef SUPPORT_ETHER

#define ifinit			_tinet_ifinit
#define if_addmulti		_tinet_if_addmulti

#endif	/* of #ifdef SUPPORT_ETHER */

/* net/net_buf.c */

#define tget_net_buf_ex		_tinet_tget_net_buf_ex
#define tget_net_buf		_tinet_tget_net_buf
#define rel_net_buf		_tinet_rel_net_buf
#define rus_net_buf		_tinet_rus_net_buf
#define net_buf_siz		_tinet_net_buf_siz
#define net_buf_max_siz		_tinet_net_buf_max_siz
#define nbuf_get_tbl		_tinet_nbuf_get_tbl
#define nbuf_get_tbl_size	_tinet_nbuf_get_tbl_size

/* net/net_subr.c */

#define convert_hexdigit	_tinet_convert_hexdigit
#define net_rand		_tinet_net_rand
#define net_srand		_tinet_net_srand
#define rev_memcpy_word		_tinet_rev_memcpy_word
#define rev_memcmp_word		_tinet_rev_memcmp_word

/* net/net_timer.c */

#define timeout			_tinet_timeout
#define untimeout		_tinet_untimeout
#define busy_callout		_tinet_busy_callout
#define max_busy		_tinet_max_busy

/* route_cfg.c */

#define routing_tbl		_tinet_routing_tbl

#ifdef SUPPORT_PPP

/* net/ppp.c */

#define ppp_output		_tinet_ppp_output
#define ppp_cp_output		_tinet_ppp_cp_output
#define ppp_phase		_tinet_ppp_phase
#define protocols		_tinet_protocols

/* net/ppp_hdlc.c */

#define HDLC_dummy_read		_tinet_HDLC_dummy_read
#define HDLC_read		_tinet_HDLC_read
#define HDLC_write		_tinet_HDLC_write
#define remote_ACCM		_tinet_remote_ACCM

/* net/ppp_lcp.c */

#define lcp_close		_tinet_lcp_close
#define lcp_open		_tinet_lcp_open
#define lcp_lowerdown		_tinet_lcp_lowerdown
#define lcp_sprotrej		_tinet_lcp_sprotrej
#define lcp_lowerup		_tinet_lcp_lowerup
#define lcp_finished		_tinet_lcp_finished
#define lcp_down		_tinet_lcp_down
#define lcp_callbacks		_tinet_lcp_callbacks
#define lcp_fsm			_tinet_lcp_fsm
#define lcp_protent		_tinet_lcp_protent
#define lcp_local_ack_cfg	_tinet_lcp_local_ack_cfg
#define lcp_remote_ack_cfg	_tinet_lcp_remote_ack_cfg

/* net/ppp_fsm.c */

#define fsm_init		_tinet_fsm_init
#define fsm_open		_tinet_fsm_open
#define fsm_input		_tinet_fsm_input
#define fsm_protreject		_tinet_fsm_protreject
#define fsm_lowerdown		_tinet_fsm_lowerdown
#define fsm_close		_tinet_fsm_close
#define fsm_lowerup		_tinet_fsm_lowerup
#define ppp_open_mode		_tinet_ppp_open_mode

/* net/ppp_auth.c */

#define auth_reset		_tinet_auth_reset
#define link_terminated		_tinet_link_terminated
#define link_established	_tinet_link_established
#define link_required		_tinet_link_required
#define network_phase		_tinet_network_phase
#define link_down		_tinet_link_down

/* net/ppp_ipcp.c */

#define wait_ipcp		_tinet_wait_ipcp
#define ppp_get_ifnet		_tinet_ppp_get_ifnet
#define ipcp_protent		_tinet_ipcp_protent
#define ipcp_callbacks		_tinet_ipcp_callbacks
#define ipcp_fsm		_tinet_ipcp_fsm
#define ipcp_remote_ack_cfg	_tinet_ipcp_remote_ack_cfg
#define ipcp_local_ack_cfg	_tinet_ipcp_local_ack_cfg

/* net/ppp_upap.c */

#define upap_auth_client	_tinet_upap_auth_client
#define upap_auth_server	_tinet_upap_auth_server
#define pap_protent		_tinet_pap_protent

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #ifndef _NET_RENAME_H_ */
