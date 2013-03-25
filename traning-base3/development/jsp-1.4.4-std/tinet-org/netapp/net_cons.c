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
 *  @(#) $Id: net_cons.c,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

/* 
 *  �ͥåȥ����ͳ���󥽡���������
 */

#include <stdarg.h>
#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <syssvc/serial.h>
#include <syssvc/logtask.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/net_cons.h>

#ifdef USE_NET_CONS

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

uint8_t net_cons_swbuf[NET_CONS_SWBUF_SIZE];
uint8_t net_cons_rwbuf[NET_CONS_RWBUF_SIZE];

bool_t	connected	= false;	/* ���ͥ������ξ���	*/
bool_t	wait_accept	= false;	/* ��³�׵��Ԥ���	*/

#if defined(SUPPORT_INET4)

T_IPV4EP	dst;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

T_IPV6EP	dst;

#endif	/* of #if defined(SUPPORT_INET6) */

uint8_t		*snd_buff	= NULL;
uint8_t		*rcv_buff	= NULL;
uint_t		snd_off		= 0;
uint_t		rcv_off		= 0;
uint_t		net_ioctl	= IOCTL_NULL;
ER_UINT		snd_len		= 0;
ER_UINT		rcv_len		= 0;

/*
 *  �Υ�֥�å��󥰥�����Υ�����Хå��ؿ�
 */

ER
callback_nblk_net_cons (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;
	SYSTIM	now;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		get_tim(&now);
		if (*(ER*)p_parblk == E_OK) {
			syslog(LOG_NOTICE, "[NCS:%02u CBN] connected:  %6lu, from: %s.%u",
			                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
			connected = true;
			}
		else
			syslog(LOG_NOTICE, "[NCS:%02d CBN] error: %s", itron_strerror(*(ER*)p_parblk));
		snd_len = snd_off = rcv_len = rcv_off = 0;
		wait_accept = false;
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
 *  �����Хåե��Υե�å���
 */

void
flush_snd_buff (void)
{
	ER_UINT	error;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off > 0) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK && error != E_CLS)
				syslog(LOG_NOTICE, "[NCS:%02d SND] flush send error: %s",
				                   NET_CONS_CEPID, itron_strerror(error));
			snd_len = snd_off = 0;
			}
		syscall(sig_sem(SEM_NET_CONS_SEND));
		}
	return;
	}

/*
 *  ʸ������
 */

void
cons_putchar (ID portid, char ch)
{
	ER_UINT	error;

	if (connected) {
		if (ch == '\n' && (net_ioctl & IOCTL_CRLF) != 0)
			cons_putchar(portid, '\r');
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off >= snd_len) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK) {
				if (error != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d SND] send buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(error));
				syscall(sig_sem(SEM_NET_CONS_SEND));
				return;
				}
			snd_off = 0;
			if ((snd_len = tcp_get_buf(NET_CONS_CEPID, (void*)&snd_buff, TMO_FEVR)) <= 0) {
				if (snd_len != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d SND] get buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(snd_len));
				syscall(sig_sem(SEM_NET_CONS_SEND));
				return;
				}
			}
		snd_buff[snd_off ++] = ch;
		syscall(sig_sem(SEM_NET_CONS_SEND));
		}
	else
		serial_wri_dat(portid, &ch, sizeof(ch));
	}

/*
 *  ʸ���������Ѵ��ʤ���
 */

static int_t
cons_getchar_raw (void)
{
	ER	error = E_OK;

	if (connected) {
		if (rcv_off >= rcv_len) {
			rcv_off = 0;
			if ((error = tcp_rel_buf(NET_CONS_CEPID, rcv_len)) != E_OK) {
				if (error != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d RCV] release buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(error));
				discon_net_cons();
				return EOF;
				}
			if ((rcv_len = tcp_rcv_buf(NET_CONS_CEPID, (void*)&rcv_buff, TMO_FEVR)) == 0) {
				discon_net_cons();
				return EOF;
				}
			else if (rcv_len < 0) {
				if (rcv_len != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d RCV] recieve buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(rcv_len));
				discon_net_cons();
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

int_t
cons_getchar (ID portid)
{
	T_SERIAL_RPOR	rpor;
	int_t		ch, req;
	char		uch;
	ER		error;

	if (!wait_accept && !connected) {
		wait_accept = true;
		error = TCP_ACP_CEP(NET_CONS_CEPID, NET_CONS_REPID, &dst, TMO_NBLK);
#if 0
		syslog(LOG_NOTICE, "[NCS:%02d ACP] status: %s",NET_CONS_CEPID, itron_strerror(error));
#endif
		if (error != E_WBLK)
			return EOF;
		}

	while (true) {
		if (connected) {
			while ((ch = cons_getchar_raw()) == TELNET_OPT_IAC || ch == '\0') {
				if (ch != '\0') {
					switch (ch = cons_getchar_raw()) {
					case TELNET_OPT_WILL:
					case TELNET_OPT_WONT:
					case TELNET_OPT_DO:
					case TELNET_OPT_DONT:
						req = cons_getchar_raw();
						break;
					case TELNET_OPT_SB:
						while ((ch = cons_getchar_raw()) != EOF && ch != TELNET_OPT_IAC) {
							if ((ch = cons_getchar_raw()) == EOF || ch == TELNET_OPT_SE)
								break;
							}
						break;
					default:
						break;
						}
					}
				}
			if (ch != '\n') {
				if ((net_ioctl & IOCTL_ECHO) != 0 && ch != EOF) {
					cons_putchar(portid, ch);
					flush_snd_buff();
					}
				return ch;
				}
			}

		else if (serial_ref_por(portid, &rpor) == E_OK && rpor.reacnt > 0) {
			if (serial_rea_dat(portid, &uch, sizeof(uch)) > 0)
				return uch;
			else
				return EOF;
			}
		dly_tsk(100);
		}
	return EOF;
	}

/*
 *  ���ͥ�����������
 */

ER
discon_net_cons (void)
{
	ER	error = E_OK;
	SYSTIM	now;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off > 0) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK && error != E_CLS)
				syslog(LOG_NOTICE, "[NCS:%02d SND] send buff error: %s",
				                   NET_CONS_CEPID, itron_strerror(error));
			}
		if ((error = tcp_sht_cep(NET_CONS_CEPID)) != E_OK)
			syslog(LOG_NOTICE, "[NCS:%02d SHT] shutdown error: %s",
			                   NET_CONS_CEPID, itron_strerror(error));
		if ((error = tcp_cls_cep(NET_CONS_CEPID, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[NCS:%02d CLS] close error: %s",
			                   NET_CONS_CEPID, itron_strerror(error));
		connected = false;
		syscall(sig_sem(SEM_NET_CONS_SEND));
		get_tim(&now);
		syslog(LOG_NOTICE, "[NCS:%02u SND] disconnected:%5lu, from: %s.%u",
		                   NET_CONS_CEPID, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
		}
	return error;
	}

/*
 *  ���ꥢ��ݡ��Ȥ�����
 */

ER
net_serial_ctl_por (ID portid, uint_t ioctl)
{
	net_ioctl = ioctl;
	return serial_ctl_por(portid, ioctl);
	}

/*
 *  ������
 */

ER
net_syslog (uint_t prio, const char *format, ...)
{
#if defined(SUPPORT_INET4)
	T_IN4_ADDR	*addr;
#endif	/* of #if defined(SUPPORT_INET4) */

	ulong_t		val;
	SYSLOG		log;
	va_list		ap;
	char		padchar, *str;
	int_t		ch, width, left, i;
	bool_t		longflag;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_PRINTF));
		va_start(ap, format);
		while ((ch = *format ++) != '\0') {
			if (ch != '%') {		/* �񼰻���ʳ� */
				cons_putchar(CONSOLE_PORTID, (char)ch);
				continue;
				}

			width = 0;
			longflag = false;
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
				longflag = true;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				val = longflag ? (ulong_t)va_arg(ap, long_t)
				               : (ulong_t)va_arg(ap, int_t);
				if ((long_t)val >= 0)
					cons_putnumber(CONSOLE_PORTID,  val, 10, radhex, width * left, false, padchar);
				else
					cons_putnumber(CONSOLE_PORTID, -val, 10, radhex, width * left, true, padchar);
				break;

			case 'u':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 10, radhex, width * left, false, padchar);
				break;

			case 'x':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 16, radhex, width * left, false, padchar);
				break;

			case 'X':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 16, radHEX, width * left, false, padchar);
				break;

			case 'c':
				ch = va_arg(ap, int_t);
				cons_putchar(CONSOLE_PORTID, (char)ch);
				break;

			case 's':
				str = va_arg(ap, char*);
				while ((ch = *str ++) != '\0') {
					cons_putchar(CONSOLE_PORTID, (char)ch);
					width --;
					}
				while (width -- > 0)
					cons_putchar(CONSOLE_PORTID, ' ');
				break;

			case 'I':

#if defined(SUPPORT_INET4)

				addr = va_arg(ap, T_IN4_ADDR*);
				put_ipv4addr(CONSOLE_PORTID, addr, width);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

				str = va_arg(ap, char*);
				put_ipv6addr(CONSOLE_PORTID, (T_IN6_ADDR *)str, width);

#endif	/* of #if defined(SUPPORT_INET6) */

				break;

			case 'M':
				str = va_arg(ap, char*);
				put_macaddr(CONSOLE_PORTID, str, width);
				break;

			case '%':
				cons_putchar(CONSOLE_PORTID, '%');
				break;

			case '0':
				format --;
				break;

			default:
				break;
				}

			}
		va_end(ap);
		cons_putchar(CONSOLE_PORTID, '\n');
		flush_snd_buff();
		syscall(sig_sem(SEM_NET_CONS_PRINTF));
		return E_OK;
		}
	else {
		log.logtype = LOG_TYPE_COMMENT;
		log.loginfo[0] = (intptr_t)format;
		i = 1;
		va_start(ap, format);

		while ((ch = *format++) != '\0' && i < TMAX_LOGINFO) {
			if (ch != '%') {
				continue;
				}

			longflag = false;

			ch = *format++;
			while ('0' <= ch && ch <= '9') {
				ch = *format++;
				}

			while (ch == 'l') {		/* long (long) �λ��� */
				longflag = true;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				log.loginfo[i++] = longflag
					? (intptr_t)va_arg(ap, long_t) 
					: (intptr_t)va_arg(ap, int_t);
				break;
			case 'u':
			case 'x':
			case 'X':
				log.loginfo[i++] = longflag
					? (intptr_t)va_arg(ap, ulong_t)
					: (intptr_t)va_arg(ap, uint_t);
				break;
			case 'p':
				log.loginfo[i++] = (intptr_t)va_arg(ap, void *);
				break;
			case 'c':
				log.loginfo[i++] = (intptr_t)va_arg(ap, int_t);
				break;
			case 's':
				log.loginfo[i++] = (intptr_t)va_arg(ap, const char *);
				break;
			case '\0':
				format--;
				break;
			default:
				break;
				}
			}
		va_end(ap);

#ifdef TARGET_KERNEL_ASP

		return(syslog_wri_log(prio, &log));

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

		return(vwri_log(prio, &log));

#endif	/* of #ifdef TARGET_KERNEL_JSP */

		}
	}

#endif	/* of #ifdef USE_NET_CONS */
