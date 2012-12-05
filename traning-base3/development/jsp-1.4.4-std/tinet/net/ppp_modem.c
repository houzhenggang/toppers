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
 *  @(#) $Id: ppp_modem.c,v 1.5 2009/12/24 05:42:40 abe Exp abe $
 */

/* 
 *  PPP ��ǥ�����
 */

#include <string.h>

#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_fsm.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_modem.h>
#include <net/ppp_lcp.h>

#ifdef SUPPORT_PPP

/*
 *  �����ѿ�
 */

uint8_t	modem_state = PPP_MODEM_DOWN;	/* ��ǥ�ξ���		*/

/*
 *  ��ǥ�����ʸ����
 */

#define MODEM_RCODE_OK		0
#define MODEM_RCODE_CONNECT	1
#define MODEM_RCODE_RING	2
#define MODEM_RCODE_NO_CARRIER	3
#define MODEM_RCODE_ERROR	4
#define MODEM_RCODE_NO_DIALTONE	5
#define MODEM_RCODE_BUSY	6
#define MODEM_RCODE_DELAYED	7

/*
 *  �ѿ�
 */

static uint8_t *modem_rcode[] = {
	"OK",
	"CONNECT",
	"RING",
	"NO CARRIER",
	"ERROR",
	"NO DIALTONE",
	"BUSY",
	"DELAYED"
	};

static int_t dial_retry;

/*
 *  �ؿ�
 */

static void do_dial (void);
static void modem_putstr (uint8_t *str);
static void modem_wait (uint8_t *line);
static void modem_putline (uint8_t *line);

/*
 *  modem_getline -- ��ǥ������
 */

T_NET_BUF *
modem_getline (T_NET_BUF *nbuf, uint16_t size)
{
	uint8_t *buf;

	buf = nbuf->buf;
	size --;			/* '\0' ��ʬ */
	while (size > 0 && (*buf = HDLC_raw_getoctet()) != '\r') {
		buf  ++;
		size --;
		}
	*buf = '\0';
	HDLC_raw_getoctet();		/* \n ���ɤ����Ф���*/
	nbuf->len = buf - nbuf->buf;
	return nbuf;
	}

/*
 *  ��ǥ�����
 *
 *	�����: ��ǥफ��Υꥶ��ȥ�����
 */

int_t
modem_cntl (T_NET_BUF *input)
{
	int_t	code;

	code = sizeof(modem_rcode) / sizeof(uint8_t*) - 1;
	while (strcmp(modem_rcode[code], input->buf) != 0) {
		if (code == 0)
			return modem_state;
		code --;
		}

	switch (modem_state) {

	case PPP_MODEM_UP:
		if (code == MODEM_RCODE_RING)
			modem_state = PPP_MODEM_RING;
		break;

	case PPP_MODEM_DIAL:
		if (code == MODEM_RCODE_CONNECT) {
			syslog(LOG_NOTICE, "[MODEM] up.");
			modem_state = PPP_MODEM_CONNECT;
			lcp_open(PPP_OPEN_ACTIVE);
			sig_sem(SEM_MODEM_READY);
			}
		else {
			syslog(LOG_NOTICE, "[MODEM] dial failed '%s'.", modem_rcode[code]);
			if (-- dial_retry == 0) {
				syslog(LOG_WARNING, "[MODEM] dial failed %d times.", MODEM_CFG_RETRY_CNT);
				modem_state = PPP_MODEM_UP;
				}
			else {
				syscall(dly_tsk(MODEM_CFG_RETRY_WAIT));
				do_dial();
				}
			}
		break;

	case PPP_MODEM_RING:
		if (code == MODEM_RCODE_CONNECT) {
			syslog(LOG_NOTICE, "[MODEM] up.");
			modem_state = PPP_MODEM_CONNECT;
			lcp_open(PPP_OPEN_PASSIVE);
			}
		else
			modem_state = PPP_MODEM_UP;
		break;

	default:
		if (code == MODEM_RCODE_NO_CARRIER) {
			if (lcp_fsm.state == PPP_FSM_OPENED)
				lcp_close();
			syslog(LOG_NOTICE, "[MODEM] down.");
			modem_state = PPP_MODEM_UP;
			}
		break;

		}

	return code;
	}

/*
 *  init_modem -- ��ǥ���������롣
 */

void
init_modem (void)
{
	modem_putline("AT");

#ifdef MODEM_CFG_INIT

	modem_putline(MODEM_CFG_INIT);

#endif	/* of #ifdef MODEM_CFG_INIT */

	modem_state = PPP_MODEM_UP;
	}

/*
 *  wait_modem -- ��³��λ�ޤ��Ԥġ�
 *
 *	�����: ��³�˼��Ԥ����� E_OBJ ���֤���
 */

ER
wait_modem (void)
{
	ER error = E_OK;

	if (modem_state == PPP_MODEM_UP) {
		dial();
		}

	if (modem_state != PPP_MODEM_CONNECT) {
		/* ��³��λ�ޤ��Ԥġ�*/
		wai_sem(SEM_MODEM_READY);
		if (modem_state != PPP_MODEM_CONNECT)
			error = E_OBJ;
		}

	return error;
	}

/*
 *  dial -- ������뤹�롣��ȥ饤����򥻥åȤ��롣
 */

void
dial (void)
{
	do_dial();
	dial_retry = MODEM_CFG_RETRY_CNT;
	modem_state = PPP_MODEM_DIAL;
	}

/*
 *  do_dial -- ������뤹�롣dial() �β������ؿ�
 */

static void
do_dial (void)
{
	syslog(LOG_NOTICE, "[MODEM] dial: %s.", MODEM_CFG_PHONE_NUMBER);
	modem_putstr(MODEM_CFG_DIAL);
	modem_putstr(MODEM_CFG_PHONE_NUMBER);
	modem_putstr("\r");
	}

/*
 *  modem_putstr -- ��ǥ�ʸ�������
 */

static void
modem_putstr (uint8_t *str)
{
	while (*str)
		HDLC_raw_putoctet(*str ++);
	}

/*
 *  modem_wait -- ��ǥफ��ʸ������Ԥ�
 */

static void
modem_wait (uint8_t *line)
{
	int_t ch, state, len = strlen(line);

	state = len;
	while (state != 0) {
		ch = HDLC_raw_getoctet();
		if (ch != line[len - state])
			state = len;
		if (ch == line[len - state])
			state --;
		}
	}

/*
 *  modem_putline -- ��ǥ�Խ���
 */

static void
modem_putline (uint8_t *line)
{
	modem_putstr(line);
	modem_putstr("\r");
	modem_wait("OK\r\n");
	}

#endif	/* fo #ifdef SUPPORT_PPP */
