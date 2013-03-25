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
 *  @(#) $Id: if_lpcemac.h,v 1.1 2011/01/16 16:05:03 roi Exp $
 */

/*
 * Copyright (C) 1993, David Greenman. This software may be used, modified,
 *   copied, distributed, and sold, in both source and binary form provided
 *   that the above copyright and these terms are retained. Under no
 *   circumstances is the author responsible for the proper functioning
 *   of this software, nor does the author assume any responsibility
 *   for damages incurred with its use.
 */

#ifndef _IF_LPCEMAC_H_
#define _IF_LPCEMAC_H_

/*
 *  受信データモードの設定
 */
/* #define ENABLE_HASH */
/* #define ACCEPT_BROADCAST	*/
#define MULTICAST_UNICAST


/*
 *  送受信バッファ数の設定
 */
#define NUM_IF_EMAC_TXBUF	0x0005	/* 送信バッファ数			*/
#define NUM_IF_EMAC_RXBUF	0x0005	/* 受信バッファ数			*/

/*
 *  送受信バッファ領域の設定
 */
#define EMAC_RAM_ADDR		0x7FE00000
#define EMAC_RAM_SIZE		0x00004000
#define EMAC_BLOCK_SIZE		0x600

#define TX_DESCRIPTOR_SIZE	(NUM_IF_EMAC_TXBUF * 8)
#define RX_DESCRIPTOR_SIZE	(NUM_IF_EMAC_RXBUF * 8)
#define TX_STATUS_SIZE		(NUM_IF_EMAC_TXBUF * 4)
#define RX_STATUS_SIZE		(NUM_IF_EMAC_RXBUF * 8)
#define TOTAL_DESCRIPTOR_SIZE	(TX_DESCRIPTOR_SIZE + RX_DESCRIPTOR_SIZE + TX_STATUS_SIZE + RX_STATUS_SIZE)
#define EMAC_DESCRIPTOR_ADDR	(EMAC_RAM_ADDR + EMAC_RAM_SIZE - TOTAL_DESCRIPTOR_SIZE) 

#define TX_DESCRIPTOR_ADDR	EMAC_DESCRIPTOR_ADDR
#define TX_STATUS_ADDR		(EMAC_DESCRIPTOR_ADDR + TX_DESCRIPTOR_SIZE)
#define RX_DESCRIPTOR_ADDR	(TX_STATUS_ADDR + TX_STATUS_SIZE)
#define RX_STATUS_ADDR		(RX_DESCRIPTOR_ADDR + RX_DESCRIPTOR_SIZE)

#define EMAC_TX_BUFFER_ADDR	EMAC_RAM_ADDR
#define EMAC_RX_BUFFER_ADDR	(EMAC_RAM_ADDR + EMAC_BLOCK_SIZE * NUM_IF_EMAC_TXBUF)

/* EMAC interrupt controller related definition */
#define EMAC_INT_RXOVERRUN	(1<<0)
#define EMAC_INT_RXERROR    (1<<1)
#define EMAC_INT_RXFINISHED (1<<2)
#define EMAC_INT_RXDONE     (1<<3)
#define EMAC_INT_TXUNDERRUN (1<<4)
#define EMAC_INT_TXERROR    (1<<5)
#define EMAC_INT_TXFINISHED (1<<6)
#define EMAC_INT_TXDONE     (1<<7)
#define EMAC_INT_SOFTINT    (1<<12)
#define EMAC_INT_WOL        (1<<13)
#define EMAC_INT_DEFAULT    (EMAC_INT_RXOVERRUN | EMAC_INT_RXERROR | EMAC_INT_RXFINISHED | EMAC_INT_RXDONE \
							| EMAC_INT_TXUNDERRUN | EMAC_INT_TXERROR | EMAC_INT_TXFINISHED | EMAC_INT_TXDONE)

/* MAC Configuration Register 1 */
#define MAC_RECEIVEENABLE           (1<<0)		/* set this allow receive frames to be receivd. */
#define MAC_PASSALLRECEIVEFRAMES    (1<<1)		/* When set 1, the MAC will pass all frames regardless of type. */
#define MAC_RESETTX                 (1<<8)		/* Setting this bit will put the Transmit Function logic in reset */
#define MAC_RESETMCSTX              (1<<9)		/* Setting this bit resets the MAC Control Bublayer/ Transmit logic */
#define MAC_RESETRX                 (1<<10)		/* Setting this bit will put the Receive Function logic in reset */
#define MAC_RESETMCSRX              (1<<11)		/* Setting this bit resets the MAC Control Sublayer/Receive logic. */
#define MAC_SIMLATIONRESET          (1<<14)		/* Setting this bit will case a reset to the random number gnerator widthin the Transmit Function */
#define MAC_SOFTRESET               (1<<15)		/* Setting this bit will put all modiles within the MAC in reset except the Host interface */
#define MAC_RESET                   (MAC_SOFTRESET | MAC_SIMLATIONRESET | MAC_RESETMCSRX | MAC_RESETRX | MAC_RESETMCSTX | MAC_RESETTX)

/* MAC Configuration Register 2 */
#define MAC_FULLDUPLEXMODE          (1<<0)		/* When enabled, the MAC operates in Full-Duplex mode */
#define MAC_CRCENABLEMODE           (1<<4)		/* Set this bit to append a CRC to every frame whwther padding was required or not */
#define MAC_PADCRCENABLEMODE        (1<<5)		/* Set this bit to have the MAC pad all short frames */

/* PHY Support Register */
#define MAC_100MBPS                 (1<<8)		/* When set, 100Mbps. clear, 10Mbps */

/* MII Mgmt Configuration Register */
#define MAC_HOSTCLOCKDIV4           (0<<2)		/* Host Clock divided by 4 */
#define MAC_HOSTCLOCKDIV6           (2<<2)		/* Host Clock divided by 6 */
#define MAC_HOSTCLOCKDIV8           (3<<2)		/* Host Clock divided by 8 */
#define MAC_HOSTCLOCKDIV10          (4<<2)		/* Host Clock divided by 10 */
#define MAC_HOSTCLOCKDIV14          (5<<2)		/* Host Clock divided by 14 */
#define MAC_HOSTCLOCKDIV20          (6<<2)		/* Host Clock divided by 20 */
#define MAC_HOSTCLOCKDIV28          (7<<2)		/* Host Clock divided by 28 */
#define MAC_RESETMIIMGMT            (1<<15)		/* Reset the MII Managment hardware */

/* MII Mgmt Command Register */
#define MAC_MIICMD_WRITE            (0<<0)
#define MAC_MIICMD_READ             (1<<0)
#define MAC_MIICMD_SCAN             (1<<1)

/* MII Mgmt Indicators Register */
#define MAC_MII_BUSY                (1<<0)		/* if 1, indicates MII Mgmt is currently performing an MII Mgmt Read or Write cycle */
#define MAC_MII_SCANNING            (1<<1)		/* if 1, indicates a scan operation is in progress */
#define MAC_MII_NOTVALID            (1<<2)		/* if 1, indicates MII Mgmt Read cycle has not completed and Read Data is not yet vaild */
#define MAC_MII_LINKFAIL            (1<<3)		/* if 1, indicates that an MII Mgnt link fail has occurred */

/* Command Register */
#define MAC_RXENABLE                (1<<0)		/* Enable receive */
#define MAC_TXENABLE                (1<<1)		/* Enable transmit */
#define MAC_REGRESET                (1<<3)		/* When set to 1, all datapaths and the host registers are reset */
#define MAC_TXRESET                 (1<<4)		/* When set to 1, the transmit datapath is reset */
#define MAC_RXRESET                 (1<<5)		/* When set to 1, the receive datapath is reset */
#define MAC_PASSRUNTFRAME           (1<<6)		/* When set to 1, passes runt frames smaller than 64 bytes to memory unless they have a CRC error */
#define MAC_RMII                    (1<<9)		/* When set to 1, RMII mode is selected */
#define MAC_FULLDUPLEX              (1<<10)		/* When set to 1, indicattes full duplex operation */

/* Receive Filter Control Register */
#define MAC_ACCEPTUNICASTEN         (1<<0)		/* When set to 1, all unicast frames are accepted */
#define MAC_ACCEPTBROADCASTEN       (1<<1)		/* When set to 1, all broadcase frames are accepted */
#define MAC_ACCEPTMULTICASTEN       (1<<2)		/* When set to 1, all multicast frames are accepted */
#define MAC_ACCEPTUNICASEHASHEN     (1<<3)		/* When set to 1, all unicast frames that pass the inpertfect hash filter are accepted */
#define MAC_ACCEPTMULTICASTHASHEN   (1<<4)		/* When set to 1, multicast frames that pass the inperfect hash filter are accepted */
#define MAC_ACCEPTPERFECTEN         (1<<5)		/* When set to 1, the frame with a destination address indentical the station address are accepted */

/* EMAC Descriptor TX and RX Control fields */
#define EMAC_TX_DESC_INT		0x80000000
#define EMAC_TX_DESC_LAST		0x40000000
#define EMAC_TX_DESC_CRC		0x20000000
#define EMAC_TX_DESC_PAD		0x10000000
#define EMAC_TX_DESC_HUGE		0x08000000
#define EMAC_TX_DESC_OVERRIDE	0x04000000

#define EMAC_RX_DESC_INT		0x80000000

/* EMAC Descriptor status related definition */
#define TX_DESC_STATUS_ERR		0x80000000
#define TX_DESC_STATUS_NODESC	0x40000000
#define TX_DESC_STATUS_UNDERRUN	0x20000000
#define TX_DESC_STATUS_LCOL		0x10000000
#define TX_DESC_STATUS_ECOL		0x08000000
#define TX_DESC_STATUS_EDEFER	0x04000000
#define TX_DESC_STATUS_DEFER	0x02000000
#define TX_DESC_STATUS_COLCNT	0x01E00000	/* four bits, it's a mask, not exact count */

#define RX_DESC_STATUS_ERR		0x80000000
#define RX_DESC_STATUS_LAST		0x40000000
#define RX_DESC_STATUS_NODESC	0x20000000
#define RX_DESC_STATUS_OVERRUN	0x10000000
#define RX_DESC_STATUS_ALGNERR	0x08000000
#define RX_DESC_STATUS_RNGERR	0x04000000
#define RX_DESC_STATUS_LENERR	0x02000000
#define RX_DESC_STATUS_SYMERR	0x01000000
#define RX_DESC_STATUS_CRCERR	0x00800000
#define RX_DESC_STATUS_BCAST	0x00400000
#define RX_DESC_STATUS_MCAST	0x00200000
#define RX_DESC_STATUS_FAILFLT	0x00100000
#define RX_DESC_STATUS_VLAN		0x00080000
#define RX_DESC_STATUS_CTLFRAM	0x00040000

#define DESC_SIZE_MASK			0x000007FF	/* 11 bits for both TX and RX */

/*
 *  PHYの設定
 */
#define PHY_TIMEOUT         5000000			/* μsec */

/*
 *  Standard PHYレジスタ番号
 */
#define PHY_BMCR		0x0000
#define PHY_BMSR		0x0001
#define PHY_PHYIDR1		0x0002
#define PHY_PHYIDR2		0x0003
#define PHY_ANAR		0x0004
#define PHY_ANLPAR		0x0005
#define PHY_ANLPARNP	0x0005
#define PHY_ANER		0x0006
#define PHY_ANNPTR		0x0007

/*
 *  BMCR設定値
 */
#define BMCR_RESET			0x8000
#define BMCR_LOOPBACK		0x4000
#define BMCR_SPEED_100		0x2000
#define BMCR_AN				0x1000
#define BMCR_POWERDOWN		0x0800
#define BMCR_ISOLATE		0x0400
#define BMCR_RE_AN			0x0200
#define BMCR_DUPLEX			0x0100

/*
 *  BMSR設定値
 */
#define BMSR_100BE_T4		0x8000
#define BMSR_100TX_FULL		0x4000
#define BMSR_100TX_HALF		0x2000
#define BMSR_10BE_FULL		0x1000
#define BMSR_10BE_HALF		0x0800
#define BMSR_AUTO_DONE		0x0020
#define BMSR_REMOTE_FAULT	0x0010
#define BMSR_NO_AUTO		0x0008
#define BMSR_LINK_ESTABLISHED	0x0004

/*
 *  拡張PHYレジスタ番号
 */
#define NSM_PHY_PHYSTS		0x0010
#define NSM_PHY_MICR		0x0011
#define NSM_PHY_MISR		0x0012
#define NSM_PHY_RESERVED1	0x0013
#define NSM_PHY_FCSCR		0x0014
#define NSM_PHY_RECR		0x0015
#define NSM_PHY_PCSR		0x0016
#define NSM_PHY_RBR			0x0017
#define NSM_PHY_LEDCR		0x0018
#define NSM_PHY_PHYCR		0x0019
#define NSM_PHY_10BTSCR		0x001A
#define NSM_PHY_CDCTRL1		0x001B
#define NSM_PHY_RESERVED2	0x001C
#define NSM_PHY_EDCR		0x001D

/*
 *  リンク情報
 */
#define SPEED_100			1
#define SPEED_10			0
#define FULL_DUPLEX			1
#define HALF_DUPLEX			0

/*
 *  NIC の選択マクロ
 */

#define IF_ETHER_NIC_GET_SOFTC()	lpcemac_get_softc()
#define IF_ETHER_NIC_WATCHDOG(i)	lpcemac_watchdog(i)
#define IF_ETHER_NIC_PROBE(i)		lpcemac_probe(i)
#define IF_ETHER_NIC_INIT(i)		lpcemac_init(i)
#define IF_ETHER_NIC_READ(i)		lpcemac_read(i)
#define IF_ETHER_NIC_RESET(i)		lpcemac_reset(i)
#define IF_ETHER_NIC_START(i,o)		lpcemac_start(i,o)

#define T_IF_ETHER_NIC_SOFTC		struct t_emac_softc

/* IPv6 関係 */

#define IF_ETHER_NIC_IN6_IFID(i,a)	get_mac6_ifid(i,a)	/* インタフェース識別子の設定		*/
#define IF_ETHER_NIC_ADDMULTI(s)	lpcemac_addmulti(s)	/* マルチキャストアドレスの登録		*/

#ifndef _MACRO_ONLY

/*
 *  前方参照
 */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  関数
 */
extern void if_ether_handler(void);

extern void lpcemac_reset(T_IF_SOFTC *ic);
extern T_IF_SOFTC *lpcemac_get_softc(void);
extern void lpcemac_watchdog(T_IF_SOFTC *ic);
extern void lpcemac_probe(T_IF_SOFTC *ic);
extern void lpcemac_init(T_IF_SOFTC *ic);
extern T_NET_BUF *lpcemac_read(T_IF_SOFTC *ic);
extern void lpcemac_start(T_IF_SOFTC *ic, T_NET_BUF *output);
extern ER lpcemac_addmulti(T_IF_SOFTC *ic);

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _IF_LPCEMAC_H_ */
