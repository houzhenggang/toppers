/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: if_lpcmac.c,v 1.1 2011/01/16 16:08:03 roi Exp $
 */

/*
 * Copyright (c) 1995, David Greenman
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/i386/isa/if_ed.c,v 1.148.2.4 1999/09/25 13:08:18 nyan Exp $
 */

/*
 * Device driver for National Semiconductor DS8390/WD83C690 based ethernet
 *   adapters. By David Greenman, 29-April-1993
 *
 * Currently supports the Western Digital/SMC 8003 and 8013 series,
 *   the SMC Elite Ultra (8216), the 3Com 3c503, the NE1000 and NE2000,
 *   and a variety of similar clones.
 *
 */

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include <string.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/net_buf.h>

#include "if_lpcemac.h"

/*
 *  �ͥåȥ�����󥿥ե������˰�¸���륽�եȥ��������� 
 */

typedef struct t_emac_softc {
	UW		nic_addr;			/* NIC �Υ١������ɥ쥹	*/
	UH      phy_addr;			/* PHY ADDRESS�ֹ� */
	UB      phy_speed;
	UB      phy_duplex;
	UW      tx_error;			/* �������顼����߲�� */
	UW      rx_error;			/* �������顼����߲�� */
} T_EMAC_SOFTC;

/*
 *  �ͥåȥ�����󥿥ե������Υ��եȥ���������
 */

/* �ͥåȥ�����󥿥ե������˰�¸���륽�եȥ��������� */

static T_EMAC_SOFTC ed_softc = {
	TADR_EMC_BASE,				/* NIC �Υ١������ɥ쥹		*/
	PHY_ADDRNO,					/* PHY���ɥ쥹�ֹ� */
};

/* �ͥåȥ�����󥿥ե������˰�¸���ʤ����եȥ��������� */


T_IF_SOFTC if_softc = {
	{},					/* �ͥåȥ�����󥿥ե������Υ��ɥ쥹	*/
	0,					/* ���������ॢ����			*/
	&ed_softc,				/* �ǥ��Х�����¸�Υ��եȥ���������	*/
	SEM_IF_EMAC_SBUF_READY,			/* �������ޥե�			*/
	SEM_IF_EMAC_RBUF_READY,			/* �������ޥե�			*/

#ifdef SUPPORT_INET6

	IF_MADDR_INIT,				/* �ޥ�����㥹�ȥ��ɥ쥹�ꥹ��	*/

#endif	/* of #ifdef SUPPORT_INET6 */
};


static INT  init_PHY(T_EMAC_SOFTC *sc);
static void write_PHY(UH phyaddr, INT reg, INT data);
static INT  read_PHY(UH phyaddr, INT reg);

/*
 *  �����ѥǥ�������ץ��ν����
 */
static void
lpcemac_txdescriptor_init(void)
{
	UW  *tx_desc_addr, *tx_status_addr;
	INT i;

	/*
	 *  �����ѥǥ�������ץ��ΰ�ȥ�����������
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXDESCRIPTOR), TX_DESCRIPTOR_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXSTATUS), TX_STATUS_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXDESCRIPTORNUM), NUM_IF_EMAC_TXBUF-1);

	/*
	 *  �����ѥǥ�������ץ��ΰ�ν����
	 */
	for(i = 0 ; i < NUM_IF_EMAC_TXBUF ; i++){
		tx_desc_addr = (UW *)(TX_DESCRIPTOR_ADDR + i*sizeof(UW)*2);
		*tx_desc_addr = (UW)(EMAC_TX_BUFFER_ADDR + i*EMAC_BLOCK_SIZE);
		*(tx_desc_addr+1) = (UW)(EMAC_TX_DESC_INT | (EMAC_BLOCK_SIZE-1));
	}

	/*
	 *  �����ѥ��ơ������ΰ�ν����
	 */
	for(i = 0 ; i < NUM_IF_EMAC_TXBUF ; i++){
		tx_status_addr = (UW *)(TX_STATUS_ADDR + i*sizeof(UW));
		*tx_status_addr = (UW)0;
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX), 0);
}

/*
 *  �����ѥǥ�������ץ��ν����
 */
static void
lpcemac_rxdescriptor_init(void)
{
	UW  *rx_desc_addr, *rx_status_addr;
	INT i;

	/*
	 *  �����ѥǥ�������ץ��ΰ�ȥ�����������
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXDESCRIPTOR), RX_DESCRIPTOR_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXSTATUS), RX_STATUS_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXDESCRIPTORNUM), NUM_IF_EMAC_RXBUF-1);

	/*
	 *  �����ѥǥ�������ץ��ΰ�ν����
	 */
	for(i = 0 ; i < NUM_IF_EMAC_RXBUF ; i++){
		rx_desc_addr = (UW *)(RX_DESCRIPTOR_ADDR + i*sizeof(UW)*2 );
		*rx_desc_addr = (UW)(EMAC_RX_BUFFER_ADDR + i*EMAC_BLOCK_SIZE);
		*(rx_desc_addr+1) = (UW)(EMAC_RX_DESC_INT | (EMAC_BLOCK_SIZE-1));
	}

	/*
	 *  �����ѥ��ơ������ΰ�ν����
	 */
	for (i = 0 ; i < NUM_IF_EMAC_RXBUF ; i++){
		rx_status_addr = (UW *)(RX_STATUS_ADDR + i*sizeof(UW)*2);
		*rx_status_addr = (UW)0;
		*(rx_status_addr+1) = (UW)0;
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXCONSUMEINDEX), 0);	/* RX descriptor points to zero */
}

/*
 *  LPC23XX��EMAC��PHY�Υϡ��ɥ����������
 */
static int
lpcemac_phy_initailze(T_IF_SOFTC *ic)
{
	unsigned long mac2, supp, comd, ipgt, tmp;

	/*
	 *  EMAC�Υ��եȥ������ꥻ�å�
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), MAC_RESET);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), MAC_RXRESET | MAC_TXRESET | MAC_REGRESET);

	sil_dly_nse(800);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), 0x00000000);

	/*
	 *  EMAC���������ػ�����
	 */
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp &= ~(MAC_TXENABLE | MAC_RXENABLE);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1));
	tmp &= ~MAC_RECEIVEENABLE;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), tmp);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC2), 0x00000000);

	/*
	 *  Non Back-to-back Inter-Packet-Gap�˥ǥե���Ȥ�����
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_IPGR), 0x00000012);

	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_CLRT), 0x37<<8 + 0xF);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAXF), 0x0600);

	/*
	 *  PHY�ν����
	 */
	if(init_PHY(ic->sc) == FALSE){
		return FALSE;
	}

	/*
	 *  MAC���ɥ쥹������
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA0), (ic->ifaddr.lladdr[0]<<8)+ic->ifaddr.lladdr[1]);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA1), (ic->ifaddr.lladdr[2]<<8)+ic->ifaddr.lladdr[3]); 
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA2), (ic->ifaddr.lladdr[4]<<8)+ic->ifaddr.lladdr[5]);

	syslog_2(LOG_NOTICE, "Speed[%d] Duplex[%d}", (int)ic->sc->phy_speed, (int)ic->sc->phy_duplex);
	supp = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP));
	comd = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	if(ic->sc->phy_speed == SPEED_10){
		supp &= ~MAC_100MBPS;	/* 10M�Τߤ����� */
	}
	else{
		supp |= MAC_100MBPS;	/* 100M/10M������ */
	}
	if(ic->sc->phy_duplex == HALF_DUPLEX){	/* HALF DUPLEX�ξ�� */
		mac2  = MAC_PADCRCENABLEMODE | MAC_CRCENABLEMODE;
		comd |= MAC_PASSRUNTFRAME;
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
		ipgt  = 0x00000012;		/* Non Back-to-back HALF DUPLEX��Ŭ��GAP�� */
	}
	else{						/* FULL DUPLEX�ξ�� */
		mac2  = MAC_PADCRCENABLEMODE | MAC_CRCENABLEMODE | MAC_FULLDUPLEXMODE;
		comd |= MAC_FULLDUPLEX | MAC_PASSRUNTFRAME;
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
		ipgt  = 0x00000015;		/* Non Back-to-back FULL DUPLEX��Ŭ��GAP�� */
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC2), mac2);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP), supp);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), comd);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_IPGT), ipgt);

	/*
	 *  �ǥ�������ץ��ΰ�ν����
	 */
	lpcemac_txdescriptor_init();
	lpcemac_rxdescriptor_init();

	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1));
	tmp |= MAC_PASSALLRECEIVEFRAMES;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), tmp);

	/*
	 *  �����ѥե��륿��������
	 */
#ifdef ACCEPT_BROADCAST
	tmp = MAC_ACCEPTPERFECTEN | MAC_ACCEPTBROADCASTEN;	/* broadcast/perfect */
#else	/* ACCEPT_BROADCAST */
	tmp = MAC_ACCEPTPERFECTEN;	/* perfect match only */
#endif	/* ACCEPT_BROADCAST */

#ifdef MULTICAST_UNICAST
	tmp |= MAC_ACCEPTMULTICASTEN | MAC_ACCEPTUNICASTEN;
#endif	/* MULTICAST_UNICAST */

#ifdef ENABLE_HASH
	tmp |= MAC_ACCEPTMULTICASTHASHEN | MAC_ACCEPTUNICASEHASHEN;
#endif	/* ENABLE_HASH */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXFILTERCTRL), tmp);

	/*
	 *  EMAC�γ��������
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), 0xFFFF);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTENABLE), EMAC_INT_DEFAULT);
	return TRUE;
}

/*
 * ed_get_frame -- Ethernet �ե졼������Ϥ��롣
 */

static T_NET_BUF *
lpcemac_get_frame (T_EMAC_SOFTC *sc, UB *ring, UH len)
{
	T_NET_BUF	*input = NULL;
	UH		align;
	ER		error;


	/*
	 *  +-----------+--------+---------+---------+
	 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
	 *  +-----------+--------+---------+---------+
	 *        14        20        20        n
	 *   <----------------- len ---------------->
	 *              ^
	 *              net_buf �� 4 �����ƥåȶ����˥��饤�󤵤�Ƥ��롣
	 *
	 *  tcp_input �� udp_input �Ǥϡ������إå��� SDU �ǥ����å������
	 *  �׻����뤬��n �� 4 �����ƥåȶ����ˤʤ�褦�� SDU �θ��� 0 ��
	 *  �ѥåǥ��󥰤��롣����ʬ���θ���� net_buf ��������ʤ���Фʤ�ʤ���
	 */
	align = ((((len - sizeof(T_IF_HDR)) + 3) >> 2) << 2) + sizeof(T_IF_HDR);

	if ((error = tget_net_buf(&input, align, TMO_IF_ED_GET_NET_BUF)) == E_OK && input != NULL) {
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_PACKETS], 1);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_OCTETS],  len);
		memcpy(input->buf, ring, len);
	}
	else {
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_NO_BUFS], 1);
	}
	return input;
}


/*
 * lpcemac_reset -- emac �ͥåȥ�����󥿥ե�������ꥻ�åȤ��롣
 */

void
lpcemac_reset (T_IF_SOFTC *ic)
{
	int result;

	disint();
	result = lpcemac_phy_initailze(ic);
	enaint();
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RESETS], 1);
	syslog_2(LOG_NOTICE, "lpcemac_reset(%08x);(%d)", ic, result);
}

/*
 *  lpcemac_ed_softc -- �ͥåȥ�����󥿥ե������Υ��եȥ�����������֤���
 */

T_IF_SOFTC *
lpcemac_get_softc (void)
{
	return &if_softc;
}

/*
 * lpcemac_watchdog -- emac �ͥåȥ�����󥿥ե������Υ�å��ɥå������ॢ����
 */

void
lpcemac_watchdog (T_IF_SOFTC *ic)
{
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], 1);
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_TIMEOUTS], 1);
	lpcemac_reset(ic);
}

/*
 * lpcemac_probe -- emac �ͥåȥ�����󥿥ե������θ���
 */

void
lpcemac_probe (T_IF_SOFTC *ic)
{
	/* �������ͥå��ѤΥϡ��ɥ��������� */
	tinet_sys_initialize();
	/* MAC���ɥ쥹�μ��� */
	memcpy(ic->ifaddr.lladdr, lp23xx_macaddr, ETHER_ADDR_LEN);
}

/*
 * lpcemac_init -- emac �ͥåȥ�����󥿥ե������ν����
 */

void
lpcemac_init (T_IF_SOFTC *ic)
{
	T_EMAC_SOFTC  *sc = ic->sc;
	int result;
	unsigned long tmp;

	syslog_1(LOG_NOTICE, "start lpcemac_init(%08x)", ic);
	if(!(result = lpcemac_phy_initailze(ic))){
		syslog_1(LOG_ERROR, "lpcemac_phy_initailze result(%d)", result);
		slp_tsk();
	}
	/* MAC TX/RX enable */
	tmp = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp |= MAC_TXENABLE | MAC_RXENABLE;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1));
	tmp |= MAC_RECEIVEENABLE;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), tmp);
}

/*
 * lpcemac_read -- �ե졼����ɤ߹���
 */

T_NET_BUF *
lpcemac_read (T_IF_SOFTC *ic)
{
	T_EMAC_SOFTC	*sc = ic->sc;
	T_NET_BUF	*input = NULL;
	int		len;
	UB      *frame_ptr;
	UB		boundry;
	UB		curr;
	int RxProduceIndex, RxConsumeIndex;
	long *rx_desc_addr, *rx_status_addr;

	disint();
	RxProduceIndex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXPRODUCEINDEX));
	RxConsumeIndex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXCONSUMEINDEX));
	if(RxProduceIndex != RxConsumeIndex) {

		if(RxProduceIndex == NUM_IF_EMAC_RXBUF){
			RxProduceIndex = 0;
			sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXPRODUCEINDEX), 0);
		}
		rx_desc_addr = (long *)(RX_DESCRIPTOR_ADDR + RxConsumeIndex * 8);
		rx_status_addr = (long *)(RX_STATUS_ADDR + RxConsumeIndex * 8);
		frame_ptr    = (char *)*rx_desc_addr;
		len = (*rx_status_addr & DESC_SIZE_MASK) - 1;
		/* NIC ����γ����ߤ���Ĥ��롣*/
		enaint();

		if (len <= EMAC_BLOCK_SIZE) {
			input = lpcemac_get_frame(sc, frame_ptr, len);
			syslog_5(LOG_INFO, "ETH[RECV][%08x](%d) type[%04x] src[%08x] dst[%08x]", input->buf, input->len,
										(input->buf[12]<<8)|input->buf[13],
										(input->buf[26]<<24)|(input->buf[27]<<16)|(input->buf[28]<<8)|input->buf[29],
										(input->buf[30]<<24)|(input->buf[31]<<16)|(input->buf[32]<<8)|input->buf[33]);
		}
		else {
			/* �������顼�ȥꥻ�åȤ�Ͽ���롣*/
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
			lpcemac_reset(ic);
			return NULL;
		}

		/*
		 *  �����ǥ�������ץ��򹹿����롣
		 */
		disint();
		RxConsumeIndex++;
		if(RxConsumeIndex == NUM_IF_EMAC_RXBUF){
			RxConsumeIndex = 0;
		}
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXCONSUMEINDEX), RxConsumeIndex);
	}
	enaint();
	if (RxProduceIndex != RxConsumeIndex)
		sig_sem(ic->semid_rxb_ready);

	return input;
}

/*
 * lpcemac_start -- �����ե졼���Хåե���󥰤��롣
 */

void
lpcemac_start (T_IF_SOFTC *ic, T_NET_BUF *output)
{
	long *tx_desc_addr;
	int TxProduceIndex;
	int TxConsumeIndex;
	int i, templen;

	TxProduceIndex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX));
	TxConsumeIndex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXCONSUMEINDEX));
	syslog_2(LOG_DEBUG, "ETH[SEND P(%d) C(%d)", TxProduceIndex, TxConsumeIndex);

	if(TxProduceIndex == NUM_IF_EMAC_TXBUF){
		/*
		 * �����ѤΥǥ�������ץ��������ͤ�ã������硢������᤹
		 */
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX), 0);
	}

	disint();
	tx_desc_addr = (long *)(TX_DESCRIPTOR_ADDR + TxProduceIndex * 8);
	/*
	 *  �����ǡ����������Хåե��˥��ԡ�����
	 */
	memcpy((char *)(*tx_desc_addr), output->buf, output->len);
	syslog_5(LOG_INFO, "ETH[SEND][%08x](%d) type[%04x] src[%08x] dst[%08x]", output->buf, output->len,
										(output->buf[12]<<8)|output->buf[13],
										(output->buf[26]<<24)|(output->buf[27]<<16)|(output->buf[28]<<8)|output->buf[29],
										(output->buf[30]<<24)|(output->buf[31]<<16)|(output->buf[32]<<8)|output->buf[33]);
	/*
	 *  �����ǥ�������ץ������������Ԥ�
	 */
	*(tx_desc_addr+1) = (long)(EMAC_TX_DESC_INT | EMAC_TX_DESC_LAST | (output->len -1));
	TxProduceIndex++;		/* transmit now */
	if(TxProduceIndex == NUM_IF_EMAC_TXBUF ){
		TxProduceIndex = 0;
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX), TxProduceIndex);
	enaint();
}

/*
 *  NIC �����ߥϥ�ɥ�
 */

void
if_ether_handler (void)
{
	T_IF_SOFTC *ic = &if_softc;
	unsigned int IntStatus, rxproduceindex, rxconsumeindex;
	int         loopcount = 0;

	IntStatus = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTSTATUS));
	syslog_1(LOG_DEBUG, "if_ether_handler[%08x]", IntStatus);
	if((IntStatus & EMAC_INT_WOL) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_WOL);
		syslog_0(LOG_NOTICE, "occer EMAC_INT_WOL");
		return;
	}
	if((IntStatus & EMAC_INT_RXOVERRUN) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_RXOVERRUN);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
		syslog_0(LOG_DEBUG, "occer EMAC_INT_RXOVERRUN[%08x]");
		return;
	}

	if((IntStatus & EMAC_INT_RXERROR) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_RXERROR);
		/* �������顼��Ͽ���롣*/
		ic->sc->rx_error++;
		syslog_0(LOG_DEBUG, "occer EMAC_INT_RXERROR");
		return;
	}

	if((IntStatus & EMAC_INT_RXFINISHED) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_RXFINISHED);
		do{
			rxproduceindex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXPRODUCEINDEX));
			rxconsumeindex = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXCONSUMEINDEX));
			if(loopcount > 100)
				syslog_2(LOG_EMERG, "occer EMAC_INT_RXFINISHED MAC_RXPRODUCEINDEX[%08x] MAC_RXCONSUMEINDEX[%08x]", rxproduceindex, rxconsumeindex);
			if(rxconsumeindex == 0)
				rxconsumeindex = NUM_IF_EMAC_RXBUF-1;
			else
				rxconsumeindex--;
			loopcount++;
		}
		while(rxproduceindex != rxconsumeindex);
	}

	if((IntStatus & EMAC_INT_RXDONE) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_RXDONE);
		syslog_0(LOG_DEBUG, "occer EMAC_INT_RXDONE");
		if (isig_sem(ic->semid_rxb_ready) != E_OK){
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RXB_QOVRS], 1);
		}
	}

	if((IntStatus & EMAC_INT_TXUNDERRUN) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_TXUNDERRUN);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], 1);
		syslog_0(LOG_NOTICE, "occer EMAC_INT_TXUNDERRUN");
		return;
	}

	if((IntStatus & EMAC_INT_TXERROR) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_TXERROR);
		ic->sc->tx_error++;
		syslog_0(LOG_NOTICE, "occer EMAC_INT_TXERROR");
		return;
	}

	if((IntStatus & EMAC_INT_TXFINISHED) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_TXFINISHED);
		syslog_0(LOG_DEBUG, "occer EMAC_INT_TXFINISHED");
	}

	if((IntStatus & EMAC_INT_TXDONE) != 0){
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), EMAC_INT_TXDONE);
		if (isig_sem(ic->semid_txb_ready) != E_OK)
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_TXB_QOVRS], 1);
		syslog_0(LOG_DEBUG, "occer EMAC_INT_TXDONE");
	}
}


/*
 *  �������ͥå�PHY�ν����
 *  ����������硢�꥿�����ͤ�TRUE�ǡ�sc���speed,duplex�򥻥å�
 *  ���Ԥ�����硢FALSE���֤���
 */
static INT
init_PHY(T_EMAC_SOFTC *sc)
{
	int i;
	unsigned long tmp;

	/* MII�ѥ���ե�����졼��������� */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCFG), MAC_RESETMIIMGMT | MAC_HOSTCLOCKDIV20);
	sil_dly_nse(8000);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCFG), MAC_HOSTCLOCKDIV20);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCMD), MAC_MIICMD_WRITE);
#ifdef USE_RMII 
	/* RMII�ѥ���ե�����졼��������� */
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp |= MAC_RMII;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	/* 100base�⡼������ */ 
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP), MAC_100MBPS);
#else
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp &= ~MAC_RMII;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP), 0x00000000);
#endif

	sil_dly_nse(20000);

	write_PHY(sc->phy_addr, PHY_BMCR, BMCR_RESET);
	sil_dly_nse(4000);

	for(i = 0 ; ; i++){
		tmp = read_PHY(sc->phy_addr, PHY_BMCR);
		if((tmp & BMCR_RESET) == 0x0000){
			break;		/* �ꥻ�åȽ�λ */
		}
		if(i >= (PHY_TIMEOUT*2)){	/* �����ॢ���� */
			return FALSE;
		}
		sil_dly_nse(1000);
	}

	/* check PHY IDs to make sure the reset takes place and PHY
	is in its default state. See National PHY DP83848 Users Manual 
	for more details */
	tmp = read_PHY(sc->phy_addr, PHY_PHYIDR1);
	if((tmp & 0x2000) != 0x2000){
		return FALSE;
	}

	tmp = read_PHY(sc->phy_addr, PHY_PHYIDR2);
	if((tmp & 0x5C90) != 0x5C90){
		return FALSE;
	}

	/*
	 *  AUTO NEGOTIATION����
	 *  ¾������򤷤������Ϥ�������
	 */
	write_PHY(sc->phy_addr, PHY_BMCR, BMCR_AN | BMCR_RE_AN);

	for(i = 0 ; ; i++){
		tmp = read_PHY(sc->phy_addr, NSM_PHY_PHYSTS);
		if((tmp & 0x0011) == 0x0011){
			break;		/* ��󥯴�λ */
		}
		if(i >= PHY_TIMEOUT){	/* �����ॢ���� */
			return FALSE;
		}
		sil_dly_nse(1000);
	}

	/* ��󥯾���μ��������� */
	if(tmp & 0x04)
		sc->phy_duplex = FULL_DUPLEX;
	else
		sc->phy_duplex = HALF_DUPLEX;

	if(tmp & 0x02)
		sc->phy_speed = SPEED_10;
	else
		sc->phy_speed = SPEED_100;
	return TRUE;
}

/*
 *  PHY�쥸�����ؤΥǡ����񤭹���
 */
static void
write_PHY(UH phyaddr, INT reg, INT data)
{
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCMD), MAC_MIICMD_WRITE);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MADR), (phyaddr<<8) | reg);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MWTD), data);
	while(sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MIND)) != 0);
}

/*
 *  PHY�쥸��������Υǡ����ɤ߹���
 */
static INT
read_PHY(UH phyaddr, INT reg)
{
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCMD), MAC_MIICMD_READ);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MADR), (phyaddr<<8) | reg);
	while((sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MIND)) & (MAC_MII_NOTVALID|MAC_MII_BUSY)) != 0 );
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCMD), MAC_MIICMD_WRITE);
	return( sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MRDD)));
}


