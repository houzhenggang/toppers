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
 *  @(#) $Id: ip_output.c,v 1.5 2009/12/24 05:47:21 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)output.c	8.3 (Berkeley) 1/21/94
 * $FreeBSD: src/sys/netinet/output.c,v 1.85.2.4 1999/08/29 16:29:49 peter Exp $
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>

#if defined(SUPPORT_IPSEC)
#include <netinet6/ipsec.h>
#endif

static uint16_t frag_id = 0;

/*
 *  IP output -- IP �ν��ϴؿ�
 *
 *    ���: �С������ȥإå�Ĺ�Ͼ���ؤ����ꤹ�롣
 */

ER
ip_output (T_NET_BUF *output, TMO tmout)
{
	T_IP4_HDR	*ip4h;
	ER		error = E_OK;
	T_IN4_ADDR	gw;

#ifdef SUPPORT_IPSEC
	T_SECPOLICY* sp;
	int ipsec_error;
        int policy;
#endif /* SUPPORT_IPSEC */

	NET_COUNT_MIB(ip_stats.ipOutRequests, 1);

#ifdef SUPPORT_IPSEC
        /* XXX: IPsec�ν����ϥѥ��å����Ҳ������˹Ԥ��� */

	/* SPD��������� */
	sp = ipsec4_getpolicybyaddr(output, IPSEC_DIR_OUTBOUND, &ipsec_error);
	if (sp==NULL) {
                error = ipsec_error;
                return error;
        }

        /* �ݥꥷ������å�����*/
#if 0
        switch (sp->policy) {

        case IPSEC_POLICY_BYPASS:
        case IPSEC_POLICY_NONE:
        case IPSEC_POLICY_TCP:
                goto skip_ipsec;

                break; /* NOTREACHED */

        case  IPSEC_POLICY_IPSEC:
                /* XXX: SH2�ǤϤ�����illegal Instruction��ȯ�����롣����ѥ���ΥХ�? */
                if (sp->req == NULL) {
                        /* ���򴹥ǡ������Ф���SA�μ������׵᤹�� */
                        goto bad;
                }
                break;

        default:
                /* �����ʥݥꥷ */
                goto bad;
                break;
        }
#else /* 0 */
        /* XXX: ����ѥ�����Զ�����Τ��� switch����ifʸ�ǽ�ľ���� */
        policy = sp->spinitb->policy;

        if (policy == IPSEC_POLICY_BYPASS ||
            policy == IPSEC_POLICY_NONE ||
            policy == IPSEC_POLICY_TCP)
                goto skip_ipsec;
        else if (policy == IPSEC_POLICY_IPSEC) {
                if (sp->req == NULL)
                        /* ���򴹥ǡ������Ф���SA�μ������׵᤹�� */
                        goto bad;
        } else
                goto bad;

#endif /* 0 */

		{
			T_IPSEC_OUTPUT_STATE state;

			state.m = output;
			/* XXX: ipsec4_output()��Ǥϡ�ip->{len,off}��ͥåȥ���Х��ȥ������Ȥ��� */
			error = ipsec4_output (&state, sp, 0 /* flags */ );
			output = state.m;

			if (error) {
				/* net_buf ��ipsec4_output�ˤ�äƴ��˲�������Ƥ��� */
				switch (error) {
				default:
					syslog (LOG_NOTICE, "ip_output:%d error", __LINE__);
				}
			}
		}

        /* ipsec4_output�˱ƶ���������ͤ򹹿����� */
        /* XXX: ɬ�פ�? */

skip_ipsec:
#endif /* SUPPORT_IPSEC */

#ifdef IP4_CFG_FRAGMENT

	ip4h = GET_IP4_HDR(output);

	gw = in4_rtalloc(ntohl(ip4h->dst));

	/*
	 *  �ǡ�������ॵ�������ͥåȥ���� MTU ��Ķ���Ƥ���С�
	 *  ʬ�䤷���������롣
	 */
	if (ntohs(ip4h->len) > IF_MTU) {
		T_NET_BUF	*frag;
		T_IP4_HDR	*fip4h;
		uint_t		off, hlen, len, flen, align;

		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_OUT], 1);
		NET_COUNT_MIB(ip_stats.ipFragCreates, 1);

		len  = ntohs(ip4h->len);
		off  = hlen = GET_IP4_HDR_SIZE(ip4h);
		while (off < len) {
			if (off + (IF_MTU - IP4_HDR_SIZE) < len)
				flen = IF_MTU - IP4_HDR_SIZE;
			else
				flen = len - off;

			/* �ǡ���Ĺ�� 4 �����ƥåȶ�����Ĵ�����롣	*/
			align = (flen + 3) >> 2 << 2;

			/* �ͥåȥ���Хåե���������롣*/
			if (tget_net_buf(&frag, align + IF_IP4_HDR_SIZE, TMO_IP4_FRAG_GET_NET_BUF) == E_OK) {

				/* �ե饰���Ȥ򥳥ԡ����롣*/
				memcpy(GET_IP4_SDU(frag), (uint8_t *)ip4h + off, flen);

				/* �إå������롣*/
				fip4h		= GET_IP4_HDR(frag);
				*fip4h		= *ip4h;
				fip4h->flg_off	= htons(IP4_MAKE_FLGOFF(off + flen == len ? 0 : IP4_MF,
						                       (off - hlen) >> 3));
				fip4h->len	= htons(flen + IP4_HDR_SIZE);
				fip4h->id	= htons(frag_id);
				fip4h->sum	= 0;
				fip4h->sum	= in_cksum(fip4h, GET_IP4_HDR_SIZE(fip4h));

				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(fip4h->len));
				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_OUT_FRAGS], 1);

				IF_SET_PROTO(frag, IF_PROTO_IP);
				if ((error = IF_OUTPUT(frag, &gw, NULL, tmout)) != E_OK) {
					syscall(rel_net_buf(output));
					NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
					NET_COUNT_MIB(ip_stats.ipFragFails, 1);
					return error;
					}
				}
			else {
				/* �����Ǥ��ʤ���С������򤢤����롣*/
				syscall(rel_net_buf(output));
				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
				NET_COUNT_MIB(ip_stats.ipFragFails, 1);
				return E_NOMEM;
				}

			off += IF_MTU - IP4_HDR_SIZE;
			}
		syscall(rel_net_buf(output));
		frag_id ++;
		NET_COUNT_MIB(ip_stats.ipFragOKs, 1);
		}
	else {

		/* �إå������롣*/
		ip4h->id  = htons(frag_id);
		frag_id ++;
		ip4h->sum = 0;
		ip4h->sum = in_cksum(ip4h, GET_IP4_HDR_SIZE(ip4h));

		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(ip4h->len));
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);

		IF_SET_PROTO(output, IF_PROTO_IP);
		if ((error = IF_OUTPUT(output, &gw, NULL, tmout)) != E_OK)
			NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
		}

#else	/* of #ifdef IP4_CFG_FRAGMENT */

	ip4h = GET_IP4_HDR(output);

	/* �ǡ�������ॵ�������ͥåȥ���� MTU ��Ķ���Ƥ���Х��顼 */
	if (ntohs(ip4h->len) > IF_MTU)
		return E_PAR;

	/* �إå������롣*/
	ip4h->id  = htons(frag_id);
	frag_id ++;
	ip4h->sum = 0;
	ip4h->sum = in_cksum(ip4h, (uint_t)GET_IP4_HDR_SIZE(ip4h));

	NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(ip4h->len));
	NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);

	gw = in4_rtalloc(ntohl(ip4h->dst));
	IF_SET_PROTO(output, IF_PROTO_IP);
	if ((error = IF_OUTPUT(output, &gw, NULL, tmout)) != E_OK)
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
		NET_COUNT_MIB(ip_stats.ipOutDiscards, 1);

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

#ifdef SUPPORT_IPSEC
	bad:
#endif /* SUPPORT_IPSEC */

	return error;
	}
