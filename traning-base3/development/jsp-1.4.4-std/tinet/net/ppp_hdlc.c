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
 *  @(#) $Id: ppp_hdlc.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/*
 *	     PPP High Level Link Control (HDLC) Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan, Inc.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/hdlc.c,v 1.46 1999/12/20 20:29:42 brian Exp $
 *
 *	TODO:
 */

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_modem.h>

#ifdef SUPPORT_PPP

/*
 *  RFC1171 (PPP) �� HDLC �������
 */

/*
 *  �ѿ�
 */

uint32_t remote_ACCM	= DEF_REMOTE_ACCM;

/*
 *  �ؿ�
 */

static ER HDLC_putoctet (uint8_t octet);
static ER HDLC_getoctet (uint8_t *octet);

/*
 *  genfcstab.c �ˤ��������� FCS �Υ�å����å�ɽ
 *  RFC1171 ����
 */

static uint16_t fcstab[256] = {
	UINT_C(0x0000), UINT_C(0x1189), UINT_C(0x2312), UINT_C(0x329b),
	UINT_C(0x4624), UINT_C(0x57ad), UINT_C(0x6536), UINT_C(0x74bf),
	UINT_C(0x8c48), UINT_C(0x9dc1), UINT_C(0xaf5a), UINT_C(0xbed3),
	UINT_C(0xca6c), UINT_C(0xdbe5), UINT_C(0xe97e), UINT_C(0xf8f7),
	UINT_C(0x1081), UINT_C(0x0108), UINT_C(0x3393), UINT_C(0x221a),
	UINT_C(0x56a5), UINT_C(0x472c), UINT_C(0x75b7), UINT_C(0x643e),
	UINT_C(0x9cc9), UINT_C(0x8d40), UINT_C(0xbfdb), UINT_C(0xae52),
	UINT_C(0xdaed), UINT_C(0xcb64), UINT_C(0xf9ff), UINT_C(0xe876),
	UINT_C(0x2102), UINT_C(0x308b), UINT_C(0x0210), UINT_C(0x1399),
	UINT_C(0x6726), UINT_C(0x76af), UINT_C(0x4434), UINT_C(0x55bd),
	UINT_C(0xad4a), UINT_C(0xbcc3), UINT_C(0x8e58), UINT_C(0x9fd1),
	UINT_C(0xeb6e), UINT_C(0xfae7), UINT_C(0xc87c), UINT_C(0xd9f5),
	UINT_C(0x3183), UINT_C(0x200a), UINT_C(0x1291), UINT_C(0x0318),
	UINT_C(0x77a7), UINT_C(0x662e), UINT_C(0x54b5), UINT_C(0x453c),
	UINT_C(0xbdcb), UINT_C(0xac42), UINT_C(0x9ed9), UINT_C(0x8f50),
	UINT_C(0xfbef), UINT_C(0xea66), UINT_C(0xd8fd), UINT_C(0xc974),
	UINT_C(0x4204), UINT_C(0x538d), UINT_C(0x6116), UINT_C(0x709f),
	UINT_C(0x0420), UINT_C(0x15a9), UINT_C(0x2732), UINT_C(0x36bb),
	UINT_C(0xce4c), UINT_C(0xdfc5), UINT_C(0xed5e), UINT_C(0xfcd7),
	UINT_C(0x8868), UINT_C(0x99e1), UINT_C(0xab7a), UINT_C(0xbaf3),
	UINT_C(0x5285), UINT_C(0x430c), UINT_C(0x7197), UINT_C(0x601e),
	UINT_C(0x14a1), UINT_C(0x0528), UINT_C(0x37b3), UINT_C(0x263a),
	UINT_C(0xdecd), UINT_C(0xcf44), UINT_C(0xfddf), UINT_C(0xec56),
	UINT_C(0x98e9), UINT_C(0x8960), UINT_C(0xbbfb), UINT_C(0xaa72),
	UINT_C(0x6306), UINT_C(0x728f), UINT_C(0x4014), UINT_C(0x519d),
	UINT_C(0x2522), UINT_C(0x34ab), UINT_C(0x0630), UINT_C(0x17b9),
	UINT_C(0xef4e), UINT_C(0xfec7), UINT_C(0xcc5c), UINT_C(0xddd5),
	UINT_C(0xa96a), UINT_C(0xb8e3), UINT_C(0x8a78), UINT_C(0x9bf1),
	UINT_C(0x7387), UINT_C(0x620e), UINT_C(0x5095), UINT_C(0x411c),
	UINT_C(0x35a3), UINT_C(0x242a), UINT_C(0x16b1), UINT_C(0x0738),
	UINT_C(0xffcf), UINT_C(0xee46), UINT_C(0xdcdd), UINT_C(0xcd54),
	UINT_C(0xb9eb), UINT_C(0xa862), UINT_C(0x9af9), UINT_C(0x8b70),
	UINT_C(0x8408), UINT_C(0x9581), UINT_C(0xa71a), UINT_C(0xb693),
	UINT_C(0xc22c), UINT_C(0xd3a5), UINT_C(0xe13e), UINT_C(0xf0b7),
	UINT_C(0x0840), UINT_C(0x19c9), UINT_C(0x2b52), UINT_C(0x3adb),
	UINT_C(0x4e64), UINT_C(0x5fed), UINT_C(0x6d76), UINT_C(0x7cff),
	UINT_C(0x9489), UINT_C(0x8500), UINT_C(0xb79b), UINT_C(0xa612),
	UINT_C(0xd2ad), UINT_C(0xc324), UINT_C(0xf1bf), UINT_C(0xe036),
	UINT_C(0x18c1), UINT_C(0x0948), UINT_C(0x3bd3), UINT_C(0x2a5a),
	UINT_C(0x5ee5), UINT_C(0x4f6c), UINT_C(0x7df7), UINT_C(0x6c7e),
	UINT_C(0xa50a), UINT_C(0xb483), UINT_C(0x8618), UINT_C(0x9791),
	UINT_C(0xe32e), UINT_C(0xf2a7), UINT_C(0xc03c), UINT_C(0xd1b5),
	UINT_C(0x2942), UINT_C(0x38cb), UINT_C(0x0a50), UINT_C(0x1bd9),
	UINT_C(0x6f66), UINT_C(0x7eef), UINT_C(0x4c74), UINT_C(0x5dfd),
	UINT_C(0xb58b), UINT_C(0xa402), UINT_C(0x9699), UINT_C(0x8710),
	UINT_C(0xf3af), UINT_C(0xe226), UINT_C(0xd0bd), UINT_C(0xc134),
	UINT_C(0x39c3), UINT_C(0x284a), UINT_C(0x1ad1), UINT_C(0x0b58),
	UINT_C(0x7fe7), UINT_C(0x6e6e), UINT_C(0x5cf5), UINT_C(0x4d7c),
	UINT_C(0xc60c), UINT_C(0xd785), UINT_C(0xe51e), UINT_C(0xf497),
	UINT_C(0x8028), UINT_C(0x91a1), UINT_C(0xa33a), UINT_C(0xb2b3),
	UINT_C(0x4a44), UINT_C(0x5bcd), UINT_C(0x6956), UINT_C(0x78df),
	UINT_C(0x0c60), UINT_C(0x1de9), UINT_C(0x2f72), UINT_C(0x3efb),
	UINT_C(0xd68d), UINT_C(0xc704), UINT_C(0xf59f), UINT_C(0xe416),
	UINT_C(0x90a9), UINT_C(0x8120), UINT_C(0xb3bb), UINT_C(0xa232),
	UINT_C(0x5ac5), UINT_C(0x4b4c), UINT_C(0x79d7), UINT_C(0x685e),
	UINT_C(0x1ce1), UINT_C(0x0d68), UINT_C(0x3ff3), UINT_C(0x2e7a),
	UINT_C(0xe70e), UINT_C(0xf687), UINT_C(0xc41c), UINT_C(0xd595),
	UINT_C(0xa12a), UINT_C(0xb0a3), UINT_C(0x8238), UINT_C(0x93b1),
	UINT_C(0x6b46), UINT_C(0x7acf), UINT_C(0x4854), UINT_C(0x59dd),
	UINT_C(0x2d62), UINT_C(0x3ceb), UINT_C(0x0e70), UINT_C(0x1ff9),
	UINT_C(0xf78f), UINT_C(0xe606), UINT_C(0xd49d), UINT_C(0xc514),
	UINT_C(0xb1ab), UINT_C(0xa022), UINT_C(0x92b9), UINT_C(0x8330),
	UINT_C(0x7bc7), UINT_C(0x6a4e), UINT_C(0x58d5), UINT_C(0x495c),
	UINT_C(0x3de3), UINT_C(0x2c6a), UINT_C(0x1ef1), UINT_C(0x0f78),
	};

/*
 *  ����饤��ؿ�
 */

Inline uint16_t Next_FCS (uint16_t FCS, uint8_t Octet) {
	return (FCS >> 8) ^ fcstab[(FCS ^ Octet) & 0xff];
	};

/*
 *  HDLC_putoctet -- HDLC �����ƥåȽ���
 */

static
ER HDLC_putoctet (uint8_t octet)
{
	static uint8_t escape[2] = { HDLC_CNTL_ESC };

	ER error;

	NET_COUNT_PPP_HDLC(net_count_hdlc.out_octets, 1);

	if ((octet < 0x20 && ((1 << octet) & lcp_remote_ack_cfg.ACCM)) ||
	    octet == HDLC_CNTL_ESC || octet == HDLC_FLAG_SEQ) {
		escape[1] = octet ^ HDLC_ESC_MASK;
		error = serial_wri_dat(HDLC_PORTID, escape, sizeof(escape));
		}
	else
		error = serial_wri_dat(HDLC_PORTID, &octet, sizeof(octet));

	return error > 0 ? E_OK : error;
	}

/*
 *  HDLC_wirte -- HDLC ����
 */

ER HDLC_write (T_NET_BUF *nbuf)
{
	static char flag_seq_ac[4] = {
		HDLC_FLAG_SEQ,
		HDLC_ADDR_ALL,
		HDLC_CNTL_ESC,
		HDLC_CNTL_UI ^ HDLC_ESC_MASK,
		};

#ifdef LCP_CFG_ACCOMP

	static char flag_seq = HDLC_FLAG_SEQ;

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	ER		error;
	uint32_t	fcs;
	uint16_t	len;
	uint8_t 	*buf;

	NET_COUNT_PPP_HDLC(net_count_hdlc.out_packets, 1);

#ifdef LCP_CFG_ACCOMP

	if (lcp_local_ack_cfg.options & LCP_CFG_ACCOMP) {
		NET_COUNT_PPP_HDLC(net_count_hdlc.out_octets, sizeof(flag_seq));
		/* �ե졼�೫�ϥե饰�������� ����������    */
		if ((error = serial_wri_dat(HDLC_PORTID, &flag_seq, sizeof(flag_seq))) < 0) {
			goto err_ret;
			}
		fcs = HDLC_INIT_FCS;
		}
	else {

		NET_COUNT_PPP_HDLC(net_count_hdlc.out_octets, sizeof(flag_seq_ac));
		/* �ե졼�೫�ϥե饰�������󥹡�Address �� Control ����������    */
		if ((error = serial_wri_dat(HDLC_PORTID, flag_seq_ac, sizeof(flag_seq_ac))) < 0) {
			goto err_ret;
			}
		/* Address �� Control �� FCS �η׻��� HDLC_INIT_FCS_AC �˴ޤ�Ƥ��� */
		fcs = HDLC_INIT_FCS_AC;
		}

#else	/* of #ifdef LCP_CFG_ACCOMP */

	NET_COUNT_PPP_HDLC(net_count_hdlc.out_octets, sizeof(flag_seq_ac));
	/* �ե졼�೫�ϥե饰�������󥹡�Address �� Control ����������    */
	if ((error = serial_wri_dat(HDLC_PORTID, flag_seq_ac, sizeof(flag_seq_ac))) < 0) {
		goto err_ret;
		}
	/* Address �� Control �� FCS �η׻��� HDLC_INIT_FCS_AC �˴ޤ�Ƥ��� */
	fcs = HDLC_INIT_FCS_AC;

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	buf = nbuf->buf;
	len = nbuf->len;

#ifdef LCP_CFG_PCOMP

	if ((lcp_local_ack_cfg.options & LCP_CFG_ACCOMP) && *buf == 0 && *(buf + 1) < 0xff) {
		buf ++;
		len --;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

	/* �ǡ������������� */
	while (len -- > 0) {

		if ((error = HDLC_putoctet(*buf)) != E_OK)
			goto err_ret;
		fcs = Next_FCS(fcs, *buf);
		buf ++;
		}

	/* FCS ���������� */
	fcs = ~fcs;
	if ((error = HDLC_putoctet(fcs & 0xff)) != E_OK)
		goto err_ret;
	if ((error = HDLC_putoctet(fcs >> 8)) != E_OK)
		goto err_ret;

	/* �ե졼�ཪλ�ե饰�������󥹤��������� */
	if ((error = serial_wri_dat(HDLC_PORTID, &flag_seq_ac[0], sizeof(char))) < 0)
		goto err_ret;

	return E_OK;

err_ret:
	NET_COUNT_PPP_HDLC(net_count_hdlc.out_err_packets, 1);
	return error;
	}

/*
 *  HDLC_getoctet -- HDLC �����ƥå�����
 *
 *	����ͤ� true �ʤ�ե饰��������
 */

static
ER_BOOL HDLC_getoctet (uint8_t *octet)
{
	ER error;

	/* 1�����ƥå����Ϥ��� */
	if ((error = serial_rea_dat(HDLC_PORTID, octet, sizeof(uint8_t))) <= 0) {
		return error;
		}

	/* ���Ϥ��������ƥåȤ��ե饰�������󥹤ʤ� true ���֤� */
	if (*octet == HDLC_FLAG_SEQ)
		return true;

	/* ���Ϥ��������ƥåȤ����������פʤ顢�⤦�������ƥå����Ϥ��ޥ����������� */
	if (*octet == HDLC_CNTL_ESC) {
		if ((error = serial_rea_dat(HDLC_PORTID, octet, sizeof(uint8_t))) <= 0)
			return error;
		*octet ^= HDLC_ESC_MASK;
		}

	NET_COUNT_PPP_HDLC(net_count_hdlc.in_octets, 1);
	return E_OK;
	}

/*
 *  HDLC_read -- HDLC ����
 *
 *	HDLC �ե졼������Ϥ��롣
 */

ER HDLC_read (T_NET_BUF *nbuf, uint16_t size)
{
	ER		error;
	uint32_t	fcs = 0;
	uint16_t	olen = 0;
	uint8_t		*buf, octet;

	buf = nbuf->buf;

	/* �ե졼�೫�ϥե饰�������󥹤ޤ����Ϥ��ɤ����Ф� */
	while ((error = HDLC_getoctet(&octet)) != true) {

		if (error != E_OK)
			goto err_ret;

#ifdef PPP_CFG_MODEM

		else if (octet == '\n') {
			/* ��ǥ������ƤӽФ���*/
			modem_cntl(modem_getline(nbuf, size));
			/* ���١����δؿ���λ���롣*/
			nbuf->len = 0;
			return E_OK;
			}

#endif/* of #ifdef PPP_CFG_MODEM */

		}

	/* �ե졼�೫�ϥե饰�������󥹤δ֤����Ϥ��ɤ����Ф� */
	while (1) {
		if ((error = HDLC_getoctet(&octet)) == E_OK)
			break;
		else if (error != true)
			goto err_ret;
		}

	NET_COUNT_PPP_HDLC(net_count_hdlc.in_packets, 1);

	/* ���Ϥ��������ƥåȤ� Address: All-Stations �� */
	if (octet == HDLC_ADDR_ALL) {

		/* ���� Control: UI */
		if ((error = HDLC_getoctet(&octet)) != E_OK || octet != HDLC_CNTL_UI) {
			error = E_SYS;
			goto err_ret;
			}
		if ((error = HDLC_getoctet(&octet)) != E_OK)
			goto err_ret;
		/* Address �� Control �� FCS �η׻��� HDLC_INIT_FCS_AC �˴ޤ�Ƥ��� */
		fcs = HDLC_INIT_FCS_AC;
		}

#ifdef LCP_CFG_ACCOMP

	else if (lcp_remote_ack_cfg.options & LCP_CFG_ACCOMP) {
		fcs = HDLC_INIT_FCS;
		}

#endif/* of #ifdef LCP_CFG_ACCOMP */

	else {
		error = E_SYS;
		goto err_ret;
		}

	nbuf->len = 0;

#ifdef LCP_CFG_PCOMP

	if ((lcp_remote_ack_cfg.options & LCP_CFG_PCOMP) && (octet & 0x01) != 0) {
		*buf ++ = 0x00;
		size  --;
		nbuf->len ++;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

	fcs = Next_FCS(fcs, octet);
	*buf ++ = octet;
	size  --;
	nbuf->len ++;

	/* SUD + FCS �����Ϥ��� */
	while ((error = HDLC_getoctet(&octet)) == E_OK) {
		fcs = Next_FCS(fcs, octet);
		if (size > 0) {
			*buf ++ = octet;
			size  --;
			}
		else
			olen ++;
		nbuf->len ++;
		}

	if (error == true) {
		if (size > 0)
			nbuf->len -= 2;
		else if (olen <= 2)
			nbuf->len -= olen;
		else {
			error = E_BOVR;
			goto err_ret;
			}
		}
	else
		goto err_ret;

	/* FCS ������å����� */
	if (fcs != HDLC_GOOD_FCS) {
		error = E_SYS;
		goto err_ret;
		}

	return E_OK;

err_ret:
	NET_COUNT_PPP_HDLC(net_count_hdlc.in_err_packets, 1);
	return error;
	}

/*
 *  HDLC_dummy_read -- HDLC ���� (���ɤ�)
 *
 *	HDLC �ե졼�����ɤߤ��롣
 */

void
HDLC_dummy_read (void)
{
	uint8_t	octet;
	ER	error;

	/* �ե졼�೫�ϥե饰�������󥹤ޤ����Ϥ��ɤ����Ф� */
	while ((error = HDLC_getoctet(&octet)) != true) {
		if (error != E_OK)
			return;
		}

	/* �ե졼�೫�ϥե饰�������󥹤δ֤����Ϥ��ɤ����Ф� */
	while (octet == HDLC_FLAG_SEQ)
		if (HDLC_getoctet(&octet) != E_OK)
			return;

	/* ���Ϥ��������ƥåȤ� Address: All-Stations �� */
	if (octet == HDLC_ADDR_ALL) {

		/* ���� Control: UI */
		if (HDLC_getoctet(&octet) != E_OK || octet != HDLC_CNTL_UI)
			return;
		if (HDLC_getoctet(&octet) != E_OK)
			return;
		}

#ifdef LCP_CFG_ACCOMP

	else if (lcp_remote_ack_cfg.options & LCP_CFG_ACCOMP)
		;

#endif/* of #ifdef LCP_CFG_ACCOMP */

	else
		return;

	while (HDLC_getoctet(&octet) == E_OK)
		;
	}

#ifdef PPP_CFG_MODEM

/*
 *  HDLC_raw_getoctet -- HDLC �����ƥå� (Raw) ����
 */

int HDLC_raw_getoctet (void)
{
	uint8_t ch;

	/* 1�����ƥå����Ϥ��� */
	if (serial_rea_dat(HDLC_PORTID, &ch, sizeof(ch)) <= 0)
		return '\0';

	NET_COUNT_PPP_HDLC(net_count_hdlc.in_octets, 1);
	return ch;
	}

/*
 *  HDLC_raw_putoctet -- HDLC �����ƥå� (Raw) ����
 */

void HDLC_raw_putoctet (uint8_t ch)
{
	NET_COUNT_PPP_HDLC(net_count_hdlc.out_octets, 1);
	/* 1�����ƥåȽ��Ϥ��� */
	serial_wri_dat(HDLC_PORTID, &ch, sizeof(ch));
	}

#endif	/* of #ifdef PPP_CFG_MODEM */

#endif	/* fo #ifdef SUPPORT_PPP */
