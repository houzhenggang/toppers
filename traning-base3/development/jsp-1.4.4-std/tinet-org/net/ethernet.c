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
 *  @(#) $Id: ethernet.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/* 
 *  Ethernet ����������������
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <net/if_llc.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/if_ether.h>
#include <netinet6/if6_ether.h>
#include <netinet6/nd6.h>

#include <net/if_var.h>
#include <net/if6_var.h>

#ifdef SUPPORT_ETHER

/*
 *  �ѿ�
 */

#if defined(SUPPORT_INET4)

const uint8_t ether_broad_cast_addr[ETHER_ADDR_LEN] = {
	UINT_C(0xff), UINT_C(0xff), UINT_C(0xff),
	UINT_C(0xff), UINT_C(0xff), UINT_C(0xff)
	};

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  �ѿ�
 */

/* �ͥåȥ�����󥿥ե�������¤�� */

#if defined(SUPPORT_INET4)

static T_IFNET ether_ifnet = {
	NULL,			/* �ͥåȥ�����󥿥ե������Υ��եȥ���������	*/
	{
		IPV4_ADDR_LOCAL,	/* IPv4 ���ɥ쥹		*/
		IPV4_ADDR_LOCAL_MASK,	/* ���֥ͥåȥޥ���		*/
		},
	};

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

static T_IFNET ether_ifnet = {
	NULL,			/* �ͥåȥ�����󥿥ե������Υ��եȥ���������	*/
	{},			/* IPv6 ���ɥ쥹����				*/
	{},			/* �ޥ�����㥹�� IPv6 ���ɥ쥹			*/
	0,			/* �ե饰					*/
	};

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� ��������١��� (MIB)
 */

T_IF_STATS if_stats;

#endif	/* of #ifdef SUPPORT_MIB */

#ifdef ETHER_CFG_802_WARNING

/*
 *  �ؿ�
 */

static void ieee_802_input (T_NET_BUF *input);

/*
 *  ieee_802_input -- IEEE 802.3 ���Ͻ���
 */

static void
ieee_802_input (T_NET_BUF *input)
{
	T_8023MAC_HDR	*mhdr;
	T_8022SNAP_HDR	*shdr;

	mhdr = GET_8023MAC_HDR(input);
	shdr = GET_8022SNAP_HDR(input);
	syslog(LOG_WARNING, "[ETHER] unexp 802.3 from: %s, proto: 0x%04x.",
	                    mac2str(NULL, mhdr->shost), ntohs(*(uint16_t*)&shdr->type));
	}

#endif	/* of #ifdef ETHER_CFG_802_WARNING */

/*
 *  ether_get_ifnet -- �ͥåȥ�����󥿥ե�������¤�Τ��֤���
 */

T_IFNET *
ether_get_ifnet (void)
{
	return &ether_ifnet;
	}

#if defined(SUPPORT_INET6)

/*
 *  ether_in6_resolve_multicast -- �������ͥåȤΥޥ�����㥹�ȥ��ɥ쥹�ؤ��Ѵ�
 */

ER
ether_in6_resolve_multicast (T_ETHER_ADDR *ifaddr, T_IN6_ADDR *maddr)
{
	/* �ޥ�����㥹�ȥ��ɥ쥹�������å����롣*/
	if (!IN6_IS_ADDR_MULTICAST(maddr))
		return E_PAR;

	/* �������ͥåȤΥޥ�����㥹�ȥ��ɥ쥹�ؤ��Ѵ� */
	ether_map_ipv6_multicast(ifaddr, maddr);

	return E_OK;
	}

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  ether_raw_output -- Ethernet ���󥿥ե������ν��ϴؿ���MAC ���ɥ쥹���̵��
 */

ER
ether_raw_output (T_NET_BUF *output, TMO tmout)
{
	ER error = E_OK;

	/* Ethernet ���ϥ��塼���������롣*/
	if ((error = tsnd_dtq(DTQ_ETHER_OUTPUT, (intptr_t)output, tmout)) != E_OK) {
		NET_COUNT_ETHER(net_count_ether.out_err_packets, 1);
		NET_COUNT_MIB(if_stats.ifOutDiscards, 1);

		/* IF �ǥͥåȥ���Хåե��������ʤ��ե饰������å����롣*/
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		IF_ETHER_NIC_RESET(IF_ETHER_NIC_GET_SOFTC());
		}
	return error;
	}

/*
 *  ether_output -- Ethernet ���󥿥ե������ν��ϴؿ���MAC ���ɥ쥹���ͭ��
 */

ER
ether_output (T_NET_BUF *output, void *dst, T_IF_ADDR *gw, TMO tmout)
{
	T_IF_SOFTC	*ic;
	ER		error = E_OK;

	/* ������ MAC ���ɥ쥹�����ꤹ�롣*/
	ic = IF_ETHER_NIC_GET_SOFTC();
	memcpy(GET_ETHER_HDR(output)->shost, ic->ifaddr.lladdr, ETHER_ADDR_LEN);

	switch(ntohs(GET_ETHER_HDR(output)->type)) {

#if defined(SUPPORT_INET4)

	case ETHER_TYPE_IP:		/* IPv4	*/
		if (arp_resolve(&ic->ifaddr, output, *(uint32_t*)dst)) {	/* true �ʤ饢�ɥ쥹���� */
			error = ether_raw_output(output, tmout);
			}
		break;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

	case ETHER_TYPE_IPV6:		/* IPv6	*/
		error = nd6_storelladdr((T_ETHER_ADDR*)GET_ETHER_HDR(output)->dhost,
		                        (T_IN6_ADDR*)dst, gw);
		if (error == E_OK)
			error = ether_raw_output(output, tmout);

		/* IF �ǥͥåȥ���Хåե��������ʤ��ե饰������å����롣*/
		else if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		break;

#endif	/* of #if defined(SUPPORT_INET6) */

	default:
		NET_COUNT_MIB(if_stats.ifOutErrors, 1);

		/* IF �ǥͥåȥ���Хåե��������ʤ��ե饰������å����롣*/
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		error = E_PAR;
		break;
		}

	if (error != E_OK)
		NET_COUNT_ETHER(net_count_ether.out_err_packets, 1);
	return error;
	}

/*
 *  Ethernet ���ϥ�����
 */

void
ether_output_task(intptr_t exinf)
{
	T_IF_SOFTC	*ic;
	T_NET_BUF	*output;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[ETHER OUTPUT:%d] started.", tskid);

	ic = IF_ETHER_NIC_GET_SOFTC();

	while (true) {
		while (rcv_dtq(DTQ_ETHER_OUTPUT, (intptr_t*)&output) == E_OK) {
			NET_COUNT_ETHER(net_count_ether.out_octets,  output->len);
			NET_COUNT_MIB(if_stats.ifOutOctets, output->len + 8);
			NET_COUNT_ETHER(net_count_ether.out_packets, 1);

#ifdef SUPPORT_MIB
			if ((*(GET_ETHER_HDR(output)->dhost) & ETHER_MCAST_ADDR) == 0) {
				NET_COUNT_MIB(if_stats.ifOutUcastPkts, 1);
				}
			else {
				NET_COUNT_MIB(if_stats.ifOutNUcastPkts, 1);
				}
#endif	/* of #ifdef SUPPORT_MIB */

			syscall(wai_sem(ic->semid_txb_ready));

			IF_ETHER_NIC_START(ic, output);

#ifndef ETHER_NIC_CFG_RELEASE_NET_BUF

			if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
				syscall(rel_net_buf(output));
				}
			else {
				output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;

#ifdef SUPPORT_TCP
				sig_sem(SEM_TCP_POST_OUTPUT);
#endif	/* of #ifdef SUPPORT_TCP */
				}

#endif	/* of #ifndef ETHER_NIC_CFG_RELEASE_NET_BUF */

			}
		}
	}

/*
 *  Ethernet ���ϥ�����
 */

void
ether_input_task(intptr_t exinf)
{
	T_IF_SOFTC	*ic;
	T_NET_BUF	*input;
	T_ETHER_HDR	*eth;
	ID		tskid;
	uint16_t	proto;

	/* �ͥåȥ�����󥿥ե������������������롣*/
	ifinit();

	/* NIC ���������롣*/
	ic = IF_ETHER_NIC_GET_SOFTC();
	IF_ETHER_NIC_PROBE(ic);
	IF_ETHER_NIC_INIT(ic);

	/* Ethernet ���ϥ�������ư���� */
	syscall(act_tsk(ETHER_OUTPUT_TASK));

	/* �ͥåȥ�������ޥ�������ư���� */
	syscall(act_tsk(NET_TIMER_TASK));

	get_tid(&tskid);

	syslog(LOG_NOTICE, "[ETHER INPUT:%2d] started on MAC Addr: %s.",
	                   tskid, mac2str(NULL, ic->ifaddr.lladdr));

#if defined(SUPPORT_INET4)

	/* ARP ���������롣*/
	arp_init();

#endif	/* of #if defined(SUPPORT_INET4) */

	ether_ifnet.ic = ic;

	while (true) {
		syscall(wai_sem(ic->semid_rxb_ready));
		if ((input = IF_ETHER_NIC_READ(ic)) != NULL) {
			NET_COUNT_ETHER(net_count_ether.in_octets,  input->len);
			NET_COUNT_MIB(if_stats.ifInOctets, input->len + 8);
			NET_COUNT_ETHER(net_count_ether.in_packets, 1);
			eth = GET_ETHER_HDR(input);
			proto = ntohs(eth->type);

#ifdef SUPPORT_MIB
			if ((*eth->dhost & ETHER_MCAST_ADDR) == 0) {
				NET_COUNT_MIB(if_stats.ifInUcastPkts, 1);
				}
			else {
				NET_COUNT_MIB(if_stats.ifInNUcastPkts, 1);
				}
#endif	/* of #ifdef SUPPORT_MIB */

#if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL)

			if ((*eth->dhost & ETHER_MCAST_ADDR) && *eth->dhost != 0xff) {

#ifdef ETHER_CFG_MCAST_WARNING

				if (proto <= 1500)
					proto = ntohs(*(uint16_t*)&(GET_8022SNAP_HDR(input)->type));
				syslog(LOG_WARNING, "[ETHER] mcast addr  from: %s, to: %s, proto: 0x%04x.",
				                    mac2str(NULL, eth->shost), mac2str(NULL, eth->dhost), proto);

#endif	/* of #ifdef ETHER_CFG_MCAST_WARNING */

				NET_COUNT_ETHER(net_count_ether.in_err_packets, 1);
				NET_COUNT_MIB(if_stats.ifInErrors, 1);
				syscall(rel_net_buf(input));
				continue;
				}

#endif	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) */

			switch(proto) {

#if defined(SUPPORT_INET4)

			case ETHER_TYPE_IP:		/* IP	*/
				ip_input(input);
				break;

			case ETHER_TYPE_ARP:		/* ARP	*/
				arp_input(&ic->ifaddr, input);
				break;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

			case ETHER_TYPE_IPV6:		/* IPv6	*/
				ip6_input(input);
				break;

#endif	/* of #if defined(SUPPORT_INET6) */

			default:

#ifdef ETHER_CFG_UNEXP_WARNING

#ifdef ETHER_CFG_802_WARNING

				if (proto <= 1500)
					ieee_802_input(input);
				else
					syslog(LOG_NOTICE, "[ETHER] unexp proto from: %s, proto: 0x%04x.",
					                   mac2str(NULL, GET_ETHER_HDR(input)->shost), proto);

#else	/* of #ifdef ETHER_CFG_802_WARNING */

				syslog(LOG_INFO, "[ETHER] unexp proto from: %s, proto: 0x%04x.",
				                   mac2str(NULL, GET_ETHER_HDR(input)->shost), proto);

#endif	/* of #ifdef ETHER_CFG_802_WARNING */

#endif	/* of #ifdef ETHER_CFG_UNEXP_WARNING */

				NET_COUNT_ETHER(net_count_ether.in_err_packets, 1);
				NET_COUNT_MIB(if_stats.ifUnknownProtos, 1);
				syscall(rel_net_buf(input));
				break;
				}
			}
		}
	}

#endif /* of #ifdef SUPPORT_ETHER */
