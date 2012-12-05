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
 *  @(#) $Id: net_buf.h,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

#ifndef _NET_BUF_H_
#define _NET_BUF_H_

/*
 *  �ͥåȥ���Хåե�
 *
 *    4 �����ƥåȤǥ��饤�󤹤�ɬ�פΤ���ץ��å����θ���ơ�
 *    IF �إå��������� 4 �����ƥåȶ����Ǥʤ��ξ�硢
 *    IP �إå��ʹߤ� 4 �����ƥåȶ�����Ĵ�����롣
 */

#ifndef CPU_NET_ALIGN
#error "CPU_NET_ALIGN expected."
#endif

/*
 *  �ƥ�ץ졼��
 */

struct t_net_buf {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[4];	/* �Хåե�����		*/
	};

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */
/*
 *  64 �����ƥå�
 */

typedef struct t_net_buf_64 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[64]; /* �Хåե�����	*/
	} T_NET_BUF_64;

/*
 *  128 �����ƥå�
 */

typedef struct t_net_buf_128 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[128]; /* �Хåե�����	*/
	} T_NET_BUF_128;

/*
 *  256 �����ƥå�
 */

typedef struct t_net_buf_256 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[256]; /* �Хåե�����	*/
	} T_NET_BUF_256;

/*
 *  512 �����ƥå�
 */

typedef struct t_net_buf_512 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[512];/* �Хåե�����	*/
	} T_NET_BUF_512;

/*
 *  1024 �����ƥå�
 */

typedef struct t_net_buf_1024 {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[1024]; /* �Хåե�����	*/
	} T_NET_BUF_1024;

/*
 *  �ͥåȥ�����󥿥ե������κ��� PDU ������
 */

typedef struct t_net_buf_if_pdu {
	uint16_t	len;	/* �ǡ�����Ĺ��		*/
	uint8_t		idix;	/* mpfid �Υ���ǥå���	*/
	uint8_t		flags;	/* �ե饰		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_PDU_SIZE];
				/* �Хåե�����		*/
#if defined(IF_PDU_HDR_PADDING)
	uint8_t		padding[IF_PDU_HDR_PADDING];
#endif				/* �إå���;ʬ		*/
	} T_NET_BUF_IF_PDU;

/*
 *  �ͥåȥ���Хåե�ɽ
 */

typedef struct t_net_buf_entry {

	uint16_t	index;
	uint_t		size;

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

	ulong_t		prepares;
	ulong_t		requests;
	ulong_t		allocs;
	ulong_t		errors;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

	} T_NET_BUF_ENTRY;

/*
 *  �ͥåȥ���Хåե����ե饰	
 */

/*
 *  �ͥåȥ�����󥿥ե��������ϸ�˥ͥåȥ���Хåե��������ʤ���
 *  ���: ���ϸ�ˤ��Υե饰�ϥ��ꥢ����롣
 */
#define NB_FLG_NOREL_IFOUT	UINT_C(0x80)

/*
 *  ESP �ѥե饰
 */
#define NB_FLG_DECRYPED		UINT_C(0x40)

/*
 *  �ͥåȥ���Хåե�����°��
 */

/* õ��°�� */

#define NBA_SEARCH_ASCENT	UINT_C(0x1000)	/* �礭�ʥ�������������õ�����롣	*/
#define NBA_SEARCH_DESCENT	UINT_C(0x2000)	/* �����ʥ�������������õ�����롣	*/
#define NBA_RESERVE_TCP		UINT_C(0x4000)	/* TCP �Ѥ˥ͥåȥ���Хåե���ͽ�󤹤롣*/
#define NBA_ID_MASK		UINT_C(0x0fff)	/* �̿�ü�� ID ���Ϥ����Υޥ�����	*/

/*
 *  �ؿ����ߥ�졼�����ޥ���
 */

#define get_net_buf(b,l)	tget_net_buf((b),(l),TMO_FEVR)

/*
 *  �ؿ�
 */

extern ER tget_net_buf_ex (T_NET_BUF **blk, uint_t minlen, uint_t maxlen, ATR nbatr, TMO tmout);
extern ER tget_net_buf (T_NET_BUF **blk, uint_t len, TMO tmout);
extern ER rel_net_buf (T_NET_BUF *blk);
extern ER rus_net_buf (T_NET_BUF *blk);
extern ER_UINT net_buf_siz (T_NET_BUF *blk);
extern uint_t net_buf_max_siz (void);
extern const T_NET_BUF_ENTRY *nbuf_get_tbl (void);
extern uint_t nbuf_get_tbl_size (void);

#endif	/* of #ifndef _NET_BUF_H_ */
