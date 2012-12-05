/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 *
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次の条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
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
 *  ネットワークインタフェースに依存するソフトウェア情報 
 */

typedef struct t_emac_softc {
	UW		nic_addr;			/* NIC のベースアドレス	*/
	UH      phy_addr;			/* PHY ADDRESS番号 */
	UB      phy_speed;
	UB      phy_duplex;
	UW      tx_error;			/* 送信エラー割込み回数 */
	UW      rx_error;			/* 受信エラー割込み回数 */
} T_EMAC_SOFTC;

/*
 *  ネットワークインタフェースのソフトウェア情報
 */

/* ネットワークインタフェースに依存するソフトウェア情報 */

static T_EMAC_SOFTC ed_softc = {
	TADR_EMC_BASE,				/* NIC のベースアドレス		*/
	PHY_ADDRNO,					/* PHYアドレス番号 */
};

/* ネットワークインタフェースに依存しないソフトウェア情報 */


T_IF_SOFTC if_softc = {
	{},					/* ネットワークインタフェースのアドレス	*/
	0,					/* 送信タイムアウト			*/
	&ed_softc,				/* ディバイス依存のソフトウェア情報	*/
	SEM_IF_EMAC_SBUF_READY,			/* 送信セマフォ			*/
	SEM_IF_EMAC_RBUF_READY,			/* 受信セマフォ			*/

#ifdef SUPPORT_INET6

	IF_MADDR_INIT,				/* マルチキャストアドレスリスト	*/

#endif	/* of #ifdef SUPPORT_INET6 */
};


static INT  init_PHY(T_EMAC_SOFTC *sc);
static void write_PHY(UH phyaddr, INT reg, INT data);
static INT  read_PHY(UH phyaddr, INT reg);

/*
 *  送信用ディスクリプタの初期化
 */
static void
lpcemac_txdescriptor_init(void)
{
	UW  *tx_desc_addr, *tx_status_addr;
	INT i;

	/*
	 *  送信用ディスクリプタ領域とサイズの設定
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXDESCRIPTOR), TX_DESCRIPTOR_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXSTATUS), TX_STATUS_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXDESCRIPTORNUM), NUM_IF_EMAC_TXBUF-1);

	/*
	 *  送信用ディスクリプタ領域の初期化
	 */
	for(i = 0 ; i < NUM_IF_EMAC_TXBUF ; i++){
		tx_desc_addr = (UW *)(TX_DESCRIPTOR_ADDR + i*sizeof(UW)*2);
		*tx_desc_addr = (UW)(EMAC_TX_BUFFER_ADDR + i*EMAC_BLOCK_SIZE);
		*(tx_desc_addr+1) = (UW)(EMAC_TX_DESC_INT | (EMAC_BLOCK_SIZE-1));
	}

	/*
	 *  送信用ステータス領域の初期化
	 */
	for(i = 0 ; i < NUM_IF_EMAC_TXBUF ; i++){
		tx_status_addr = (UW *)(TX_STATUS_ADDR + i*sizeof(UW));
		*tx_status_addr = (UW)0;
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX), 0);
}

/*
 *  受信用ディスクリプタの初期化
 */
static void
lpcemac_rxdescriptor_init(void)
{
	UW  *rx_desc_addr, *rx_status_addr;
	INT i;

	/*
	 *  受信用ディスクリプタ領域とサイズの設定
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXDESCRIPTOR), RX_DESCRIPTOR_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXSTATUS), RX_STATUS_ADDR);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXDESCRIPTORNUM), NUM_IF_EMAC_RXBUF-1);

	/*
	 *  受信用ディスクリプタ領域の初期化
	 */
	for(i = 0 ; i < NUM_IF_EMAC_RXBUF ; i++){
		rx_desc_addr = (UW *)(RX_DESCRIPTOR_ADDR + i*sizeof(UW)*2 );
		*rx_desc_addr = (UW)(EMAC_RX_BUFFER_ADDR + i*EMAC_BLOCK_SIZE);
		*(rx_desc_addr+1) = (UW)(EMAC_RX_DESC_INT | (EMAC_BLOCK_SIZE-1));
	}

	/*
	 *  受信用ステータス領域の初期化
	 */
	for (i = 0 ; i < NUM_IF_EMAC_RXBUF ; i++){
		rx_status_addr = (UW *)(RX_STATUS_ADDR + i*sizeof(UW)*2);
		*rx_status_addr = (UW)0;
		*(rx_status_addr+1) = (UW)0;
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_RXCONSUMEINDEX), 0);	/* RX descriptor points to zero */
}

/*
 *  LPC23XX用EMACとPHYのハードウェア初期化
 */
static int
lpcemac_phy_initailze(T_IF_SOFTC *ic)
{
	unsigned long mac2, supp, comd, ipgt, tmp;

	/*
	 *  EMACのソフトウェアリセット
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), MAC_RESET);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), MAC_RXRESET | MAC_TXRESET | MAC_REGRESET);

	sil_dly_nse(800);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), 0x00000000);

	/*
	 *  EMACの送受信禁止設定
	 */
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp &= ~(MAC_TXENABLE | MAC_RXENABLE);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1));
	tmp &= ~MAC_RECEIVEENABLE;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), tmp);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC2), 0x00000000);

	/*
	 *  Non Back-to-back Inter-Packet-Gapにデフォルトを設定
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_IPGR), 0x00000012);

	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_CLRT), 0x37<<8 + 0xF);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAXF), 0x0600);

	/*
	 *  PHYの初期化
	 */
	if(init_PHY(ic->sc) == FALSE){
		return FALSE;
	}

	/*
	 *  MACアドレスの設定
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA0), (ic->ifaddr.lladdr[0]<<8)+ic->ifaddr.lladdr[1]);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA1), (ic->ifaddr.lladdr[2]<<8)+ic->ifaddr.lladdr[3]); 
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SA2), (ic->ifaddr.lladdr[4]<<8)+ic->ifaddr.lladdr[5]);

	syslog_2(LOG_NOTICE, "Speed[%d] Duplex[%d}", (int)ic->sc->phy_speed, (int)ic->sc->phy_duplex);
	supp = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP));
	comd = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	if(ic->sc->phy_speed == SPEED_10){
		supp &= ~MAC_100MBPS;	/* 10Mのみの設定 */
	}
	else{
		supp |= MAC_100MBPS;	/* 100M/10Mの設定 */
	}
	if(ic->sc->phy_duplex == HALF_DUPLEX){	/* HALF DUPLEXの場合 */
		mac2  = MAC_PADCRCENABLEMODE | MAC_CRCENABLEMODE;
		comd |= MAC_PASSRUNTFRAME;
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
		ipgt  = 0x00000012;		/* Non Back-to-back HALF DUPLEXの適正GAP値 */
	}
	else{						/* FULL DUPLEXの場合 */
		mac2  = MAC_PADCRCENABLEMODE | MAC_CRCENABLEMODE | MAC_FULLDUPLEXMODE;
		comd |= MAC_FULLDUPLEX | MAC_PASSRUNTFRAME;
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
		ipgt  = 0x00000015;		/* Non Back-to-back FULL DUPLEXの適正GAP値 */
	}
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC2), mac2);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_SUPP), supp);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), comd);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_IPGT), ipgt);

	/*
	 *  ディスクリプタ領域の初期化
	 */
	lpcemac_txdescriptor_init();
	lpcemac_rxdescriptor_init();

	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1));
	tmp |= MAC_PASSALLRECEIVEFRAMES;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MAC1), tmp);

	/*
	 *  受信用フィルターの設定
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
	 *  EMACの割込み設定
	 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTCLEAR), 0xFFFF);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_INTENABLE), EMAC_INT_DEFAULT);
	return TRUE;
}

/*
 * ed_get_frame -- Ethernet フレームを入力する。
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
	 *              net_buf で 4 オクテット境界にアラインされている。
	 *
	 *  tcp_input と udp_input では、擬似ヘッダと SDU でチェックサムを
	 *  計算するが、n が 4 オクテット境界になるように SDU の後ろに 0 を
	 *  パッディングする。その分を考慮して net_buf を獲得しなければならない。
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
 * lpcemac_reset -- emac ネットワークインタフェースをリセットする。
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
 *  lpcemac_ed_softc -- ネットワークインタフェースのソフトウェア情報を返す。
 */

T_IF_SOFTC *
lpcemac_get_softc (void)
{
	return &if_softc;
}

/*
 * lpcemac_watchdog -- emac ネットワークインタフェースのワッチドッグタイムアウト
 */

void
lpcemac_watchdog (T_IF_SOFTC *ic)
{
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], 1);
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_TIMEOUTS], 1);
	lpcemac_reset(ic);
}

/*
 * lpcemac_probe -- emac ネットワークインタフェースの検出
 */

void
lpcemac_probe (T_IF_SOFTC *ic)
{
	/* イーサネット用のハードウェア設定 */
	tinet_sys_initialize();
	/* MACアドレスの取得 */
	memcpy(ic->ifaddr.lladdr, lp23xx_macaddr, ETHER_ADDR_LEN);
}

/*
 * lpcemac_init -- emac ネットワークインタフェースの初期化
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
 * lpcemac_read -- フレームの読み込み
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
		/* NIC からの割り込みを許可する。*/
		enaint();

		if (len <= EMAC_BLOCK_SIZE) {
			input = lpcemac_get_frame(sc, frame_ptr, len);
			syslog_5(LOG_INFO, "ETH[RECV][%08x](%d) type[%04x] src[%08x] dst[%08x]", input->buf, input->len,
										(input->buf[12]<<8)|input->buf[13],
										(input->buf[26]<<24)|(input->buf[27]<<16)|(input->buf[28]<<8)|input->buf[29],
										(input->buf[30]<<24)|(input->buf[31]<<16)|(input->buf[32]<<8)|input->buf[33]);
		}
		else {
			/* 受信エラーとリセットを記録する。*/
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
			lpcemac_reset(ic);
			return NULL;
		}

		/*
		 *  受信ディスクリプタを更新する。
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
 * lpcemac_start -- 送信フレームをバッファリングする。
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
		 * 送信用のディスクリプタが最大値に達した場合、ゼロに戻す
		 */
		sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_TXPRODUCEINDEX), 0);
	}

	disint();
	tx_desc_addr = (long *)(TX_DESCRIPTOR_ADDR + TxProduceIndex * 8);
	/*
	 *  送信データを送信バッファにコピーする
	 */
	memcpy((char *)(*tx_desc_addr), output->buf, output->len);
	syslog_5(LOG_INFO, "ETH[SEND][%08x](%d) type[%04x] src[%08x] dst[%08x]", output->buf, output->len,
										(output->buf[12]<<8)|output->buf[13],
										(output->buf[26]<<24)|(output->buf[27]<<16)|(output->buf[28]<<8)|output->buf[29],
										(output->buf[30]<<24)|(output->buf[31]<<16)|(output->buf[32]<<8)|output->buf[33]);
	/*
	 *  送信ディスクリプタの送信設定を行う
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
 *  NIC 割り込みハンドラ
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
		/* 受信エラーを記録する。*/
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
 *  イーサネットPHYの初期化
 *  成功した場合、リターン値はTRUEで、sc中のspeed,duplexをセット
 *  失敗した場合、FALSEを返す。
 */
static INT
init_PHY(T_EMAC_SOFTC *sc)
{
	int i;
	unsigned long tmp;

	/* MII用コンフィギュレーション設定 */
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCFG), MAC_RESETMIIMGMT | MAC_HOSTCLOCKDIV20);
	sil_dly_nse(8000);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCFG), MAC_HOSTCLOCKDIV20);
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_MCMD), MAC_MIICMD_WRITE);
#ifdef USE_RMII 
	/* RMII用コンフィギュレーション設定 */
	tmp  = sil_rew_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND));
	tmp |= MAC_RMII;
	sil_wrw_mem((VP)(TADR_MAC_BASE+TOFF_MAC_COMMAND), tmp);
	/* 100baseモード設定 */ 
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
			break;		/* リセット終了 */
		}
		if(i >= (PHY_TIMEOUT*2)){	/* タイムアウト */
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
	 *  AUTO NEGOTIATION設定
	 *  他の設定をしたい場合はここを修正
	 */
	write_PHY(sc->phy_addr, PHY_BMCR, BMCR_AN | BMCR_RE_AN);

	for(i = 0 ; ; i++){
		tmp = read_PHY(sc->phy_addr, NSM_PHY_PHYSTS);
		if((tmp & 0x0011) == 0x0011){
			break;		/* リンク完了 */
		}
		if(i >= PHY_TIMEOUT){	/* タイムアウト */
			return FALSE;
		}
		sil_dly_nse(1000);
	}

	/* リンク情報の取得と設定 */
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
 *  PHYレジスタへのデータ書き込み
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
 *  PHYレジスタからのデータ読み込み
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


