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
 *  @(#) $Id: sample1n.c,v 1.5 2009/12/24 05:40:11 abe Exp abe $
 */

/* 
 *  �ͥåȥ��������ץ�ץ����(1)������
 */

#include <stdarg.h>

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include "sample1n.h"

/*
 *  �ޥ������
 */

/*  ��͡���β��  */

#undef syslog
#undef serial_rea_dat
#undef serial_ctl_por

#define EOF		(-1)

/*  TELNET ���ץ���� */

#define TELNET_OPT_SE		(240)
#define TELNET_OPT_NOP		(241)
#define TELNET_OPT_DM		(242)
#define TELNET_OPT_BRK		(243)
#define TELNET_OPT_IP		(244)
#define TELNET_OPT_AO		(245)
#define TELNET_OPT_AYT		(246)
#define TELNET_OPT_EC		(247)
#define TELNET_OPT_EL		(248)
#define TELNET_OPT_GA		(249)
#define TELNET_OPT_SB		(250)
#define TELNET_OPT_WILL		(251)
#define TELNET_OPT_WONT		(252)
#define TELNET_OPT_DO		(253)
#define TELNET_OPT_DONT		(254)
#define TELNET_OPT_IAC		(255)

/*
 *  �ѿ�
 */

/*  TCP ������������ɥХåե�  */

UB tcp_swbuf[TCP_SWBUF_SIZE];
UB tcp_rwbuf[TCP_RWBUF_SIZE];

BOOL		connected	= FALSE;	/* ���ͥ������ξ���	*/
BOOL		wait_accept	= FALSE;	/* ��³�׵��Ԥ���	*/

#ifdef SUPPORT_INET4

T_IPV4EP	dst;

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

T_IPV6EP	dst;

#endif	/* of #ifdef SUPPORT_INET6 */

UB		*snd_buff	= NULL;
UB		*rcv_buff	= NULL;
UINT		snd_off		= 0;
UINT		rcv_off		= 0;
ER_UINT		snd_len		= 0;
ER_UINT		rcv_len		= 0;
UINT		net_ioctl	= IOCTL_NULL;
UB		addr[sizeof("0123:4567:89ab:cdef:0123:4567:89ab:cdef")];

/*
 *  �ͥåȥ���ؤ�����
 */

#ifdef SUPPORT_INET4

#define TCP_ACP_CEP(c,r,d,t)	tcp_acp_cep(c,r,d,t)
#define IP2STR(s,a)		ip2str(s,a)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

#define TCP_ACP_CEP(c,r,d,t)	tcp6_acp_cep(c,r,d,t)
#define IP2STR(s,a)		ipv62str(s,a)

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_tcp (ID cepid, FN fncd, VP p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		IP2STR(addr, &dst.ipaddr);
		syslog(LOG_NOTICE, "connected:    %s.%d", addr, dst.portno);
		if (*(ER*)p_parblk == E_OK)
			connected = TRUE;
		snd_len = snd_off = rcv_len = rcv_off = 0;
		wait_accept = FALSE;
		break;

	case TFN_TCP_CLS_CEP:
	case TFN_TCP_RCV_BUF:
	case TFN_TCP_GET_BUF:
	case TFN_TCP_RCV_DAT:
	case TFN_TCP_SND_DAT:
	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

/*
 *  ���ͥ�����������
 */

ER
disconnecting (void)
{
	ER	error = E_OK;

	if (connected) {
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off > 0)
			tcp_snd_buf(TCP_CEPID, snd_off);
		tcp_sht_cep(TCP_CEPID);
		tcp_cls_cep(TCP_CEPID, TMO_FEVR);
		connected = FALSE;
		syscall(sig_sem(SEM_NET_SEND));
		IP2STR(addr, &dst.ipaddr);
		syslog(LOG_NOTICE, "disconnected: %s.%d", addr, dst.portno);
		}
	return error;
	}

/*
 *  �����Хåե��Υե�å���
 */

void
flush_snd_buff (ID cepid)
{
	if (connected) {
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off > 0) {
			tcp_snd_buf(cepid, snd_off);
			snd_len = snd_off = 0;
			}
		syscall(sig_sem(SEM_NET_SEND));
		}
	return;
	}

/*
 *  ʸ������
 */

void
put_char (ID cepid, char ch)
{
	if (connected) {
		if (ch == '\n' && (net_ioctl & IOCTL_CRLF) != 0)
			put_char(cepid, '\r');
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off >= snd_len) {
			if (tcp_snd_buf(cepid, snd_off) != E_OK) {
				syscall(sig_sem(SEM_NET_SEND));
				return;
				}
			snd_off = 0;
			if ((snd_len = tcp_get_buf(cepid, (VP*)&snd_buff, TMO_FEVR)) <= 0) {
				syscall(sig_sem(SEM_NET_SEND));
				return;
				}
			}
		snd_buff[snd_off ++] = ch;
		syscall(sig_sem(SEM_NET_SEND));
		}
	}

/*
 *  ʸ���������Ѵ��ʤ���
 */

int
get_char_raw (ID cepid)
{
	if (connected) {
		if (rcv_off >= rcv_len) {
			rcv_off = 0;
			if (tcp_rel_buf(TCP_CEPID, rcv_len) != E_OK) {
				disconnecting();
				return EOF;
				}
			if ((rcv_len = tcp_rcv_buf(TCP_CEPID, (VP*)&rcv_buff, TMO_FEVR)) == 0) {
				disconnecting();
				return EOF;
				}
			else if (rcv_len < 0) {
				disconnecting();
				return EOF;
				}
			}
		return rcv_buff[rcv_off ++];
		}
	else
		return EOF;
	}

/*
 *  ʸ��������TELNET ���ץ����򥹥��åס�
 */

int
get_char (ID cepid)
{
	int	ch, req;

	while ((ch = get_char_raw(cepid)) == TELNET_OPT_IAC || ch == '\0') {
		if (ch != '\0') {
			switch (ch = get_char_raw(cepid)) {
			case TELNET_OPT_WILL:
			case TELNET_OPT_WONT:
			case TELNET_OPT_DO:
			case TELNET_OPT_DONT:
				req = get_char_raw(cepid);
				break;
			case TELNET_OPT_SB:
				while ((ch = get_char_raw(cepid)) != EOF && ch != TELNET_OPT_IAC) {
					if ((ch = get_char_raw(cepid)) == EOF || ch == TELNET_OPT_SE)
						break;
					}
				break;
			default:
				break;
				}
			}
		}
	return ch;
	}

/*
 *  ���ꥢ��ݡ��Ȥ�����ɽФ�
 */

ER_UINT
net_serial_rea_dat (ID portid, char *buf, UINT len)
{
	T_SERIAL_RPOR	rpor;
	UINT		off;
	int		ch;

	if (!wait_accept && !connected) {
		wait_accept = TRUE;
		if (TCP_ACP_CEP(TCP_CEPID, TCP_REPID, &dst, TMO_NBLK) != E_WBLK)
			return 0;
		}

	while (TRUE) {
		if (connected) {
			off = 0;
			while (off < len && (ch = get_char(TCP_CEPID)) != EOF) {
				*(buf + off ++) = ch;
				if ((net_ioctl & IOCTL_ECHO) != 0) {
					put_char(TCP_CEPID, ch);
					flush_snd_buff(TCP_CEPID);
					}
				}
			return off;
			}
		else if (serial_ref_por(portid, &rpor) == E_OK && rpor.reacnt > 0) {
			return serial_rea_dat(portid, buf, len);
			}
		dly_tsk(500);
		}
	return off;
	}

/*
 *  ���ꥢ��ݡ��Ȥ�����
 */

ER
net_serial_ctl_por (ID portid, UINT ioctl)
{
	net_ioctl = ioctl;
	return serial_ctl_por(portid, ioctl);
	}

/*
 *  ��äȤ�Ĺ�������� (LONGEST) �����ʤ������� (ULONGEST)
 */

#ifdef LONGLONG_TYPE

typedef LONGLONG_TYPE		LONGEST;
typedef unsigned LONGLONG_TYPE	ULONGEST;

#else	/* of #ifdef LONGLONG_TYPE */

#ifdef LONG_TYPE

typedef LONG_TYPE		LONGEST;
typedef unsigned LONG_TYPE	ULONGEST;

#else	/* of #ifdef LONG_TYPE */

typedef int			LONGEST;
typedef unsigned int		ULONGEST;

#endif	/* of #ifdef LONG_TYPE */

#endif	/* of #ifdef LONGLONG_TYPE */

/*
 *  ���Υ��ߥ�졼�����
 */

/*  �����Ѵ��Τ�����Ѵ�ɽ  */

static const char radhex[] = "0123456789abcdef";
static const char radHEX[] = "0123456789ABCDEF";

/*
 *  put_num -- printf �ο����Ѵ�
 */

int
put_num(ID cepid, ULONGEST val, int radix, const char *radchar, int width, BOOL minus, char padchar)
{
	char	digits[24];
	int	ix, pad, pchars;
	BOOL	left;

	if (width < 0) {
		width = -width;
		left = TRUE;
		}
	else
		left = FALSE;

	ix = 0;
	do {
		digits[ix ++] = radchar[val % radix];
		val /= radix;
		} while (val != 0);

	if (minus)
		digits[ix ++] = '-';

	if (width > ix)
		pchars = width;
	else
		pchars = ix;

	pad = ix;
	if (!left)	/* ���ͤ� */
		for ( ; pad < width; pad ++)
			put_char(cepid, padchar);

	while (ix -- > 0)
		put_char(cepid, digits[ix]);

	if (left)	/* ���ͤ� */
		for ( ; pad < width; pad ++)
			put_char(cepid, padchar);

	return pchars;
	}

#ifdef SUPPORT_INET4

/*
 *  put_ipv4addr -- IPv4 ���ɥ쥹����
 */

static int
put_ipv4addr (ID cepid, ULONGEST *addr, int width)
{
	int len = 3;	/* 3 �� '.' ��ʸ���� */

#if SIL_ENDIAN == SIL_ENDIAN_BIG

	len += put_num(cepid, (*addr >> 24) & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 16) & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >>  8) & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid,  *addr        & 0xff, 10, radhex, 0, FALSE, ' '); 

#else	/* of #if SIL_ENDIAN == SIL_ENDIAN_BIG */

	len += put_num(cepid,  *addr        & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >>  8) & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 16) & 0xff, 10, radhex, 0, FALSE, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 24) & 0xff, 10, radhex, 0, FALSE, ' '); 

#endif	/* of #if SIL_ENDIAN == SIL_ENDIAN_BIG */

	for ( ; len < width; len ++)
		put_char(cepid, ' ');

	return len;
	}

#define PUT_IPADDR(p,a,w)	put_ipv4addr(p,a,w)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

/*
 *  ipv6addr -- IPv6 ���ɥ쥹����
 */

static int
put_ipv6addr (ID cepid, const T_IN6_ADDR *addr, int width)
{
	int	len = 0, ix;
	BOOL	omit = FALSE, zero = FALSE;

	if (addr == NULL) {
		put_char(cepid, '0');
		put_char(cepid, ':');
		put_char(cepid, ':');
		put_char(cepid, '0');
		len = 4;
		}
	else {
		for (ix = 0; ix < sizeof(T_IN6_ADDR) / 2; ix ++) {
			if (omit) {
				len += put_num(cepid, addr->s6_addr16[ix], 16, radhex, 0, FALSE, ' '); 
				if (ix < 7) {
					put_char(cepid, ':');
					len ++;
					}
				}
			else if (ix > 0 && ix < 7 && addr->s6_addr16[ix] == 0)
				zero = TRUE;
			else {
				if (zero) {
					omit = TRUE;
					put_char(cepid, ':');
					len ++;
					}
				len += put_num(cepid, addr->s6_addr16[ix], 16, radhex, 0, FALSE, ' '); 
				if (ix < 7) {
					put_char(cepid, ':');
					len ++;
					}
				}
			}

		for ( ; len < width; len ++)
			put_char(cepid, ' ');
		}
	return len;
	}

#define PUT_IPADDR(p,a,w)	put_ipv6addr(p,a,w)

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  put_macaddr -- MAC ���ɥ쥹����
 */

static int
put_macaddr (ID cepid, char *mac, int width)
{
	int oct, len;

	for (oct = 5; oct -- > 0; ) {
		put_num(cepid, *mac ++, 16, radhex, 2, FALSE, '0'); 
		put_char(cepid, ':');
		}
	put_num(cepid, *mac, 16, radhex, 2, FALSE, '0'); 

	for (len = 17; len < width; len ++)
		put_char(cepid, ' ');

	return len;
	}

/*
 *  ��������Ф�����Υޥ���
 */

#ifdef LONGLONG_TYPE

#ifdef LONG_TYPE

#define GET_ARG(ap,lf)	((lf > 1) ? va_arg(ap, LONGLONG_TYPE)	\
			 (lf      ? va_arg(ap, LONG_TYPE)	\
			          : va_arg(ap, int)))

#else	/* of #ifdef LONG_TYPE */

#define GET_ARG(ap,lf)	((lf > 1) ? va_arg(ap, LONGLONG_TYPE)	\
			          : va_arg(ap, int))

#endif	/* of #ifdef LONG_TYPE */

#else	/* of #ifdef LONGLONG_TYPE */

#ifdef LONG_TYPE

#define GET_ARG(ap,lf)	 (lf      ? va_arg(ap, LONG_TYPE)	\
			          : va_arg(ap, int))

#else	/* of #ifdef LONG_TYPE */

#define GET_ARG(ap,lf)	(va_arg(ap, int))

#endif	/* of #ifdef LONG_TYPE */

#endif	/* of #ifdef LONGLONG_TYPE */

/*
 *  ������
 */

ER
net_syslog (UINT prio, const char *format, ...)
{
	LONGEST	val;
	SYSLOG	log;
	va_list	ap;
	char	padchar, *str;
	int	ch, width, longflag, left, i, c;

	if (connected) {
		syscall(wai_sem(SEM_TCP_SYSLOG));
		va_start(ap, format);
		while ((ch = *format ++) != '\0') {
			if (ch != '%') {		/* �񼰻���ʳ� */
				put_char(TCP_CEPID, (char)ch);
				continue;
				}

			width = longflag = 0;
			padchar = ' ';

			if (ch == '-') {		/* ���ͤ� */
				format ++;
				left = -1;
				}
			else
				left = 1;

			if ((ch = *format ++) == '0') {	/* ��̷�� 0 */
				padchar = '0';
				ch = *format ++;
				}

			while ('0' <= ch && ch <= '9') {	/* ������ */
				width = width * 10 + ch - '0';
				ch = *format ++;
				}

			while (ch == 'l') {		/* long (long) �λ��� */
				longflag ++;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				val = GET_ARG(ap, longflag);
				if (val >= 0)
					put_num(TCP_CEPID,  val, 10, radhex, width * left, FALSE, padchar);
				else
					put_num(TCP_CEPID, -val, 10, radhex, width * left, TRUE, padchar);
				break;

			case 'u':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 10, radhex, width * left, FALSE, padchar);
				break;

			case 'x':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 16, radhex, width * left, FALSE, padchar);
				break;

			case 'X':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 16, radHEX, width * left, FALSE, padchar);
				break;

			case 'c':
				ch = va_arg(ap, int);
				put_char(TCP_CEPID, (char)ch);
				break;

			case 's':
				str = va_arg(ap, char*);
				while ((ch = *str ++) != '\0') {
					put_char(TCP_CEPID, (char)ch);
					width --;
					}
				while (width -- > 0)
					put_char(TCP_CEPID, ' ');
				break;

			case 'I':

#ifdef SUPPORT_INET4

				val = GET_ARG(ap, longflag);
				put_ipv4addr(TCP_CEPID, (ULONGEST *)val, width);

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

				str = va_arg(ap, char*);
				put_ipv6addr(TCP_CEPID, (T_IN6_ADDR *)str, width);

#endif	/* of #ifdef SUPPORT_INET6 */

				break;

			case 'M':
				str = va_arg(ap, char*);
				put_macaddr(TCP_CEPID, str, width);
				break;

			case '%':
				put_char(TCP_CEPID, '%');
				break;

			case '0':
				format --;
				break;

			default:
				break;
				}

			}
		va_end(ap);
		put_char(TCP_CEPID, '\n');
		flush_snd_buff(TCP_CEPID);
		syscall(sig_sem(SEM_TCP_SYSLOG));
		return E_OK;
		}
	else {
		log.logtype = LOG_TYPE_COMMENT;
		log.loginfo[0] = (VP_INT) format;
		i = 1;
		va_start(ap, format);

		while ((c = *format++) != '\0' && i < TMAX_LOGINFO) {
			if (c != '%') {
				continue;
				}

			c = *format++;
			while ('0' <= c && c <= '9') {
				c = *format++;
				}
			switch (c) {
			case 'd':
				log.loginfo[i++] = (VP_INT) va_arg(ap, int);
				break;
			case 'u':
			case 'x':
			case 'X':
				log.loginfo[i++] = (VP_INT) va_arg(ap, unsigned int);
				break;
			case 'p':
				log.loginfo[i++] = (VP_INT) va_arg(ap, void *);
				break;
			case 'c':
				log.loginfo[i++] = (VP_INT) va_arg(ap, int);
				break;
			case 's':
				log.loginfo[i++] = (VP_INT) va_arg(ap, const char *);
				break;
			case '\0':
				format--;
				break;
			default:
				break;
				}
			}
		va_end(ap);
		return(vwri_log(prio, &log));
		}
	}
