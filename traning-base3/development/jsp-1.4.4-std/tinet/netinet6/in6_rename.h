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
 *  @(#) $Id: in6_rename.h,v 1.5 2009/12/24 05:48:16 abe Exp abe $
 */

#ifndef _IN6_RENAME_H_
#define _IN6_RENAME_H_

/*
 *  TCP/IPv6 �ץ�ȥ��륹���å�����̾�Υ�͡���
 */

/* netinet6/in6.c */

#define in6_addr_loopback	_tinet_in6_addr_loopback
#define in6_ifainit		_tinet_in6_ifainit
#define in6_addr2ifaix		_tinet_in6_addr2ifaix
#define in6_addr2maix		_tinet_in6_addr2maix
#define in6_update_ifa		_tinet_in6_update_ifa
#define in6ifa_ifpwithix	_tinet_in6ifa_ifpwithix
#define in6ifa_ifpwithrtrix	_tinet_in6ifa_ifpwithrtrix
#define in6_ifawithifp		_tinet_in6_ifawithifp
#define in6_if_up		_tinet_in6_if_up
#define in6_rtalloc		_tinet_in6_rtalloc
#define in6_are_prefix_equal	_tinet_in6_are_prefix_equal
#define in6_addr_linklocal_allrouters	\
				_tinet_in6_addr_linklocal_allrouters
#define in6_addr_linklocal_allnodes	\
				_tinet_in6_addr_linklocal_allnodes
#define in6_ifaddr_timer	_tinet_in6_ifaddr_timer

/* netinet6/in6_ifattach.c */

#define in6_ifattach		_tinet_in6_ifattach

/* netinet6/in6_subr.c */

#define in6_lookup_multi	_tinet_in6_lookup_multi
#define get_ip6_hdr_size	_tinet_get_ip6_hdr_size
#define in6_lookup_ifaddr	_tinet_in6_lookup_ifaddr
#define in6_get_datagram	_tinet_in6_get_datagram
#define in6_cksum		_tinet_in6_cksum
#define in6_is_dstaddr_accept	_tinet_in6_is_dstaddr_accept
#define in6_plen2pmask		_tinet_in6_plen2pmask
#define in6_init		_tinet_in6_init
#define in6_rtredirect		_tinet_in6_rtredirect
#define in6_gateway_lookup	_tinet_in6_gateway_lookup
#define in6_set_header		_tinet_in6_set_header
#define in6_hostcache_getmtu	_tinet_in6_hostcache_getmtu
#define in6_hostcache_update	_tinet_in6_hostcache_update

/* netinet6/if6_ether.c */

#define ether_map_ipv6_multicast	\
				_tinet_ether_map_ipv6_multicast

/* netinet6/ip6_input.c */

#define ip6_input		_tinet_ip6_input
#define ip6_lasthdr		_tinet_ip6_lasthdr
#define ip6_unknown_opt		_tinet_ip6_unknown_opt
#define ip6_init		_tinet_ip6_init
#define ip6_nexthdr		_tinet_ip6_nexthdr
#define ip6_remove_exthdrs	_tinet_ip6_remove_exthdrs
#define ip6_get_prev_hdr	_tinet_ip6_get_prev_hdr

/* netinet6/ip6_output.c */

#define ip6_output		_tinet_ip6_output
#define linkmtu			_tinet_linkmtu

/* netinet6/dest6.c */

#define dest6_input		_tinet_dest6_input

/* netinet6/rout6.c */

#define route6_input		_tinet_route6_input

/* netinet6/frag6.c */

#define frag6_input		_tinet_frag6_input
#define frag6_timer		_tinet_frag6_timer
#define ip6_get_frag_queue	_tinet_ip6_get_frag_queue

/* netinet6/ah_input.c */

#define ah6_input		_tinet_ah6_input

/* netinet6/esp_input.c */

#define esp6_input		_tinet_esp6_input

/* netinet6/icmp6.c */

#define icmp6_input		_tinet_icmp6_input
#define icmp6_error		_tinet_icmp6_error
#define icmp6_echo_reply	_tinet_icmp6_echo_reply

/* netinet6/nd6.c */

#define nd6_ifattach		_tinet_nd6_ifattach
#define nd6_is_addr_neighbor	_tinet_nd6_is_addr_neighbor
#define nd6_cache_lladdr	_tinet_nd6_cache_lladdr
#define nd6_output_hold		_tinet_nd6_output_hold
#define nd6_init		_tinet_nd6_init
#define nd6_output		_tinet_nd6_output
#define nd6_options		_tinet_nd6_options
#define nd6_storelladdr		_tinet_nd6_storelladdr
#define nd6_lookup		_tinet_nd6_lookup
#define nd6_get_drl		_tinet_nd6_get_drl
#define nd6_get_cache		_tinet_nd6_get_cache
#define nd6_timer		_tinet_nd6_timer

/* netinet6/nd6_nbr.c */

#define nd6_dad_start		_tinet_nd6_dad_start
#define nd6_ns_input		_tinet_nd6_ns_input
#define nd6_na_input		_tinet_nd6_na_input
#define nd6_ns_output		_tinet_nd6_ns_output
#define nd6_na_output		_tinet_nd6_na_output

/* netinet6/nd6_rtr.c */

#define nd6_router_lookup	_tinet_nd6_router_lookup
#define nd6_defrtrlist_timer	_tinet_nd6_defrtrlist_timer
#define nd6_prelist_timer	_tinet_nd6_prelist_timer
#define nd6_ra_input		_tinet_nd6_ra_input
#define nd6_rtrsol_ctl		_tinet_nd6_rtrsol_ctl
#define ip6_defhlim		_tinet_ip6_defhlim
#define nd6_reachable_time	_tinet_nd6_reachable_time
#define nd6_base_reachable_time	_tinet_nd6_base_reachable_time
#define nd6_recalc_reachtm_interval	\
				_tinet_nd6_recalc_reachtm_interval
#define nd6_retrans_time	_tinet_nd6_retrans_time
#define nd6_defrtrlist_lookup	_tinet_nd6_defrtrlist_lookup
#define nd6_prefix_onlink	_tinet_nd6_prefix_onlink
#define nd6_prefix_offlink	_tinet_nd6_prefix_offlink
#define nd6_get_prl		_tinet_nd6_get_prl
#define nd6_get_drl		_tinet_nd6_get_drl
#define nd6_defrtrlist_del	_tinet_nd6_defrtrlist_del

/* netinet6/scope6.c */

#define in6_addrscope		_tinet_in6_addrscope

#endif	/* of #ifndef _IN6_RENAME_H_ */
