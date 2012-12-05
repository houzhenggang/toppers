/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
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
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: nserv.c,v 1.0 2003/06/20 08:00:41 abe Exp abe $
 */


#include "config.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/ethernet.h>
#include <net/net.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>


#include "tinet_id.h"
#include "dhcp.h"

const UB magic_cookie[4]       = {0x63, 0x82, 0x53, 0x63};
const UB message_and_length[2] = {0x35, 0x01};
const UB client_identifier[3]  = {0x3d, 0x07, 0x01};

static UB          udp_rbuf[600];
static DHCP_PACKET *dhcp_packet;
static DHCP        Dhcp;


void dhcp_discover(DHCP *dhcp)
{
    T_IPV4EP   p_dstaddr;
    ER         ercd;
    
    memset((VP)dhcp_packet, 0, sizeof(DHCP_PACKET));

    /* DHCP�ѥ��å����� */
    dhcp_packet->opecode        = 0x01;            /* OP������ */
    dhcp_packet->hard_addr      = 0x01;            /* �ϡ��ɥ����������ɥ쥹 */
    dhcp_packet->hard_addr_len  = 0x06;            /* �ϡ��ɥ����������ɥ쥹Ĺ */
    dhcp_packet->hop_count      = 0x00;            /* �ۥåס�������� */
    dhcp_packet->transaction_id = htonl(TRANSACTION_ID);
    dhcp_packet->second         = htons(0x0000);   /* �в���� */
    dhcp_packet->dummy          = htons(0x0000);   /* �ե饰 */
    /* dhcp_packet->client_ip[4]; */               /* ���饤����ȡ����ɥ쥹 */
    /* dhcp_packet->user_ip[4]; */                 /* �桼��IP���ɥ쥹 */
    /* dhcp_packet->server_ip[4]; */               /* ������IP���ɥ쥹 */
    /* dhcp_packet->gateway_ip[4]; */              /* �����ȥ�����IP���ɥ쥹 */
    memcpy((VP)dhcp_packet->client_hard_addr, (const VP)dhcp->macaddr, 6);
                                                   /* ���饤�����MAC���ɥ쥹 */
    /* dhcp_packet->server_host_name[64]; */
    /* dhcp_packet->file_name[128]; */

    /* DHCP���ץ���� */
    memcpy((VP)dhcp_packet->options.magic_cookie, (const VP)magic_cookie, 4);
                                                         /* Magic Cookie */
    memcpy((VP)dhcp_packet->options.message_type1, (const VP)message_and_length, 2);
                                                         /* DHCP Message */
    dhcp_packet->options.message_type2 = DHCP_DISCOVER;  /* DHCP Discover */
    memcpy((VP)dhcp_packet->options.client_id1, (const VP)client_identifier, 3);
                                                         /* Client Identifier, Ethernet */
    memcpy((VP)dhcp_packet->options.client_mac, (const VP)dhcp->macaddr, 6);
                                                         /* Client MAC Address */
    dhcp_packet->options.dummy[0]      = 0xff;           /* End Option */

    p_dstaddr.ipaddr = BROADCAST_ADDR;
    p_dstaddr.portno = BROADCAST_PORT;
    ercd = udp_snd_dat(UDP_CLIENT_CEPID, &p_dstaddr, (VP)&dhcp_packet->opecode,
             sizeof(DHCP_PACKET), TIMEOUT);
    syslog(LOG_NOTICE, "[dhcp_discover] ercd = %d", ercd);
}


ER dhcp_offer(DHCP *dhcp)
{
    ER         ercd;
    T_IPV4EP   p_dstaddr;
	T_IN4_ADDR tipaddr;
    static UB  ipaddr[sizeof("000.000.000.000") + 1];

    p_dstaddr.ipaddr = BROADCAST_ADDR;
    p_dstaddr.portno = BROADCAST_PORT;

    ercd = udp_rcv_dat(UDP_CLIENT_CEPID, &p_dstaddr, (VP)&udp_rbuf, sizeof(DHCP_PACKET), TIMEOUT);
                                                                 /* �����ॢ���Ȥ�2�ä���� */
    syslog(LOG_NOTICE, "[dhcp_offer] ercd = %d", ercd);
    if(ercd > 0){
        if((dhcp_packet->transaction_id == htonl(TRANSACTION_ID)) &&
          (dhcp_packet->options.message_type1[0] == 0x35) &&     /* DHCP Message */
          (dhcp_packet->options.message_type1[1] == 0x01) &&     /* Option Data Length */
          (dhcp_packet->options.message_type2 == DHCP_OFFER)) {  /* DHCP Offer */
            memcpy((VP)dhcp->ipaddr, (const VP)dhcp_packet->user_ip, 4);
			tipaddr = htonl(*((UW *)dhcp->ipaddr));				/* for endian */
            ip2str(ipaddr, (const T_IN4_ADDR *)&tipaddr);
            syslog(LOG_NOTICE, "[dhcp_offer] ip_addr = %s", ipaddr);
        }
    }

    return ercd;
}


void dhcp_request(DHCP *dhcp)
{
    const UB request_ip[] = {0x32,0x04};
    ER       ercd;
    T_IPV4EP p_dstaddr;

    memset((VP)dhcp_packet, 0, sizeof(DHCP_PACKET));

    dhcp_packet->opecode        = 0x01;            /* OP������ */
    dhcp_packet->hard_addr      = 0x01;            /* �ϡ��ɥ����������ɥ쥹 */
    dhcp_packet->hard_addr_len  = 0x06;            /* �ϡ��ɥ����������ɥ쥹Ĺ */
    dhcp_packet->hop_count      = 0x00;            /* �ۥåס�������� */
    dhcp_packet->transaction_id = htonl(TRANSACTION_ID);
    dhcp_packet->second         = htons(0x0000);   /* �в���� */
    dhcp_packet->dummy          = htons(0x0000);   /* �ե饰 */
    /* dhcp_packet->client_ip[4]; */               /* ���饤����ȡ����ɥ쥹 */
    memcpy((VP)dhcp_packet->user_ip, (const VP)dhcp->ipaddr, 4);  /* �桼��IP���ɥ쥹 */
    /* dhcp_packet->server_ip[4]; */               /* ������IP���ɥ쥹 */
    /* dhcp_packet->gateway_ip[4]; */              /* �����ȥ�����IP���ɥ쥹 */
    memcpy((VP)dhcp_packet->client_hard_addr, (const VP)dhcp->macaddr, 6);
                                                   /* ���饤�����MAC���ɥ쥹 */
    /* dhcp_packet->server_host_name[64]; */
    /* dhcp_packet->file_name[128]; */

    memcpy((VP)dhcp_packet->options.magic_cookie, (const VP)magic_cookie, 4);
                                                          /* Magic Cookie */
    memcpy((VP)dhcp_packet->options.message_type1, (const VP)message_and_length, 2);
                                                          /* DHCP Message */
    dhcp_packet->options.message_type2 = DHCP_REQUEST;    /* DHCP Request */
    memcpy((VP)dhcp_packet->options.client_id1, (const VP)client_identifier, 3);
                                                          /* Client Identifier, Ethernet */
    memcpy((VP)dhcp_packet->options.client_mac, (const VP)dhcp->macaddr, 6);
    memset((VP)dhcp_packet->options.dummy, 0, sizeof(dhcp_packet->options.dummy));
    memcpy((VP)dhcp_packet->options.dummy, (const VP)request_ip, 2);
    memcpy((VP)&dhcp_packet->options.dummy[2], (const VP)dhcp->ipaddr, 4);
    dhcp_packet->options.dummy[6] = 0xff;

    p_dstaddr.ipaddr = BROADCAST_ADDR;
    p_dstaddr.portno = BROADCAST_PORT;
    ercd = udp_snd_dat(UDP_CLIENT_CEPID, &p_dstaddr, (VP)&dhcp_packet->opecode,
               sizeof(DHCP_PACKET), TIMEOUT);
    syslog(LOG_NOTICE, "[dhcp_request] ercd = %d", ercd);
}


ER dhcp_ack(DHCP *dhcp)
{
    UB       *option;
    ER       ercd;
    T_IPV4EP p_dstaddr;

    p_dstaddr.ipaddr = BROADCAST_ADDR;
    p_dstaddr.portno = BROADCAST_PORT;

    ercd = udp_rcv_dat(UDP_CLIENT_CEPID, &p_dstaddr, (VP)&udp_rbuf, sizeof(DHCP_PACKET), TIMEOUT);
                                                            /* �����ॢ���Ȥ�2�ä���� */
    syslog(LOG_NOTICE, "[dhcp_ack] ercd = %d", ercd);
    if(ercd > 0){
        if((dhcp_packet->transaction_id != htonl(TRANSACTION_ID)) ||
           (dhcp_packet->options.message_type1[0] != 0x35) ||
           (dhcp_packet->options.message_type1[1] != 0x01) ||
           (dhcp_packet->options.message_type2 != DHCP_PACK)) return E_SYS;
      
    }

    option = (UB *)&dhcp_packet->options.message_type1;
    while(*option != 0xff){ /* End */
        switch(*option){
            case 0:         /* Pad */
                while(*option == 0) option++;
            case 1:         /* Subnet Mask */
                memcpy(dhcp->maskaddr, option + 2, 4);
                break;
            case 3:         /* Router */
                memcpy(dhcp->gwaddr, option + 2, 4);
                break;
            case 6:         /* Domain Server */
                memcpy(dhcp->dnsaddr, option + 2, 4);
                break;
            case 15:        /* Domain Name */
                memcpy(dhcp->domain, option + 2, *(option+1));
                dhcp->domain[*(option+1)] = '\0';
                break;
            case 54:        /* DHCP Server Id */
                memcpy(dhcp->dhcpsrvaddr, option + 2, 4);
                break;
            default:
                break;
        }
        option += *(option+1) + 2;
    }

    return ercd;
}


UW str2ip(UB *ip_addr)
{
  UW tmp = 0;
  
  tmp = ((UW)(*ip_addr) << 24) & 0xff000000; ip_addr++;
  tmp += ((UW)(*ip_addr) << 16) & 0x00ff0000; ip_addr++;
  tmp += ((UW)(*ip_addr) << 8) & 0x0000ff00; ip_addr++;
  tmp += (UW)(*ip_addr) & 0x000000ff;
  
  return tmp;
}


/* ����Ϥ�����ư��ʤ� */
ER dhcp_release(DHCP *dhcp)
{

    T_IPV4EP p_dstaddr;
    ER       ercd;

    memset((VP)dhcp_packet, 0, sizeof(DHCP_PACKET));

    dhcp_packet->opecode        = 0x01;
    dhcp_packet->hard_addr      = 0x01;
    dhcp_packet->hard_addr_len  = 0x06;
    dhcp_packet->hop_count      = 0x00;
    dhcp_packet->transaction_id = htonl(TRANSACTION_ID);
    dhcp_packet->second         = htons(0x0000);
    dhcp_packet->dummy          = htons(0x0000);
    /* dhcp_packet->client_ip[4]; */
    /* dhcp_packet->user_ip[4]; */
    /* dhcp_packet->server_ip[4]; */
    /* dhcp_packet->gateway_ip[4]; */
    memcpy((VP)dhcp_packet->client_hard_addr, (const VP)dhcp->macaddr, 6);
    /* dhcp_packet->server_host_name[64]; */
    /* dhcp_packet->file_name[128]; */

    memcpy((VP)dhcp_packet->options.magic_cookie, (const VP)magic_cookie, 4);
                                                    /* Magic Cookie */
    memcpy((VP)dhcp_packet->options.message_type1, (const VP)message_and_length, 2);
                                                    /* DHCP Message */
    dhcp_packet->options.message_type2 = DHCP_RELEASE;
    memcpy((VP)dhcp_packet->options.client_id1, (const VP)client_identifier, 3);
                                                    /* Client Identifier, Ethernet */
    memcpy((VP)dhcp_packet->options.client_mac, (const VP)dhcp->macaddr, 6);
    dhcp_packet->options.dummy[0]      = 0xff;

    p_dstaddr.ipaddr = str2ip(dhcp->dhcpsrvaddr);
    p_dstaddr.portno = BROADCAST_PORT;
    ercd = udp_snd_dat(UDP_CLIENT_CEPID, &p_dstaddr, (VP)&dhcp_packet->opecode,
             sizeof(DHCP_PACKET), TMO_NBLK);

    return ercd;
}


void dhcp_close(void)
{

    dhcp_release(&Dhcp);

}


ER get_dhcp_addr(DHCP *dhcp)
{
    dhcp_discover(dhcp);
    if(dhcp_offer(dhcp) < 0){
        syslog(LOG_NOTICE, "DHCP Offer error");
        return E_SYS;
    }
    dhcp_request(dhcp);
    if(dhcp_ack(dhcp) < 0){
        syslog(LOG_NOTICE, "DHCP Ack error");
        return E_SYS;
    }
    return E_OK;
}


ER dhcp_open(T_IF_SOFTC  *ic)
{

    static UB   shost_addr[sizeof("00:00:00:00:00:00") + 1];
    ER          ercd;

    /* DHCP�ˤ��IP���ɥ쥹���� */
    memcpy(Dhcp.macaddr, ic->ifaddr.lladdr, ETHER_ADDR_LEN);
    mac2str(shost_addr, Dhcp.macaddr);
    syslog(LOG_NOTICE, "[get_dhcp_addr] started on MAC Addr: %s.", shost_addr);

    dhcp_packet = (DHCP_PACKET *)udp_rbuf;

    ercd = get_dhcp_addr(&Dhcp);
    if(ercd == E_OK) {
        /* ���󥿥ե�������IPv4���ɥ쥹�����ꤹ�� */
        in4_add_ifaddr((T_IN4_ADDR)str2ip(Dhcp.ipaddr), (T_IN4_ADDR)str2ip(Dhcp.maskaddr));
    }

    return ercd;
}
