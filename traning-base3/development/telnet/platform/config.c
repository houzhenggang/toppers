/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010-2011 by GJ Business Division RICOH COMPANY,LTD.
 *                   JAPAN
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
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: config.c,v 1.01 2011/12/10 17:55:29 roi Exp $
 */

#include <stdio.h> 
#include <string.h>
#include <limits.h>
#include <time.h>

#include "config.h"
#include <tinet_config.h>
#include <tinet_defs.h>
#include "ff.h"
#include "fcntl.h"
#include "dhcp.h"

#include "kernel_id.h"
#include "tinet_id.h"

static void  *mon_infile;
int   (*application)(INT mode);

extern FILE *_get_stdio(int no);
extern int   _set_stdio(int no);
extern void *monitor_infile(void *file);
extern INT  dispatcher(INT mode);

/*
 *  周期ハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
void cyclic_handler(VP_INT exinf)
{
	static unsigned int sw = 1;

	sil_wrw_mem((VP)(TADR_FIO_BASE+TOFF_FIO2_CLR), sw);		/* led on */
	sil_wrw_mem((VP)(TADR_FIO_BASE+TOFF_FIO2_SET), ~sw);	/* led off */
	sw <<= 1;
	if((sw & 0x00000100) != 0)
		sw = 1;
}

/*
 *  MACアドレスの設定
 */
void
macaddr_init(VP_INT exinf)
{
	static const UB macaddr[LPC_ETHER_ADDR_LEN] = {0x00, 0x12, 0xCB, 0x01, 0x88, 0xE3};
	memcpy(lp23xx_macaddr, macaddr, LPC_ETHER_ADDR_LEN);
}

/*
 *  FILEシステム用時間取得関数
 */
static int get_rtc_time(void)
{
	struct tm2 timedate;
	int    reqtime, ctime;

	rtc_get_time(&timedate);
	reqtime  = ((timedate.tm_year-10)<<25)+(timedate.tm_mon<<21)+(timedate.tm_mday<<16);
	reqtime += (timedate.tm_hour<<11)+(timedate.tm_min<<5)+(timedate.tm_sec/2);
	return reqtime;
}

/*
 *  STORAGE DEVICEの通知
 */
static void sdcard_notice(StorageDevice_t *psdev, BOOL sw)
{
	if(sw)
		syslog_1(LOG_NOTICE, "found sd-card %d sectors !", psdev->_sdev_maxsec);
	else
		syslog_0(LOG_NOTICE, "remove sd-card !");
}

/*
 *  TELNETアプリコールバック関数
 */
static void callback_telnet(INT mode)
{
	FILE *st;

	syslog_1(LOG_NOTICE, "callback telnet(%d) !", mode);
	switch(mode){
	case TCP_TELNET_IN:
		mon_infile = monitor_infile(stderr);
		st = _get_stdio(0);
		tcp_telnet_srv_set_file(st);
		st = _get_stdio(1);
		tcp_telnet_srv_set_file(st);
		st = _get_stdio(2);
		tcp_telnet_srv_set_file(st);
		break;
	case TCP_TELNET_OUT:
		_set_stdio(0);
		_set_stdio(1);
		_set_stdio(2);
		monitor_infile(mon_infile);
		break;
	default:
		break;
	}
}

/*
 *  メインタスク
 */
void main_task(VP_INT exinf)
{
/*	int  result; */
	StorageDevice_t *psdev;
	FATFS   *fs;
	struct tm2 timedate;
    T_IF_SOFTC  *ic;
	ER	error = E_OK;
	INT  ch = 0;

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));
	sta_cyc(CYCHDR1);

	/*
	 *  RTCがバッテリバックアップでないため、時刻の設定
	 */
	timedate.tm_sec = 0;
	timedate.tm_min = 0;
	timedate.tm_hour = 21;
	timedate.tm_mday = 3;
	timedate.tm_mon = 3;
	timedate.tm_year = 2012-1970;
	timedate.tm_isdst = 0;
	mktime((struct tm *)&timedate);
	rtc_set_time(&timedate);
	rtc_start(NULL);
	SDeviceHead._get_datetime = get_rtc_time;

	/*
	 *  SDカードファイルシステムとMCIの初期化
	 */
	_sd_init();
	psdev = SDMGetStorageDevice(0);
	fs = (FATFS *)psdev->_sdev_local[0];
	psdev->_sdev_notice = sdcard_notice;

	/*
	 *  設定時刻の再表示
	 */
	rtc_get_time(&timedate);
	syslog_3(LOG_NOTICE, "%04d/%02d/%02d", timedate.tm_year+1970, timedate.tm_mon, timedate.tm_mday);
	syslog_3(LOG_NOTICE, "  %02d:%02d:%02d", timedate.tm_hour, timedate.tm_min, timedate.tm_sec);
	chg_pri(TSK_SELF, DEFAULT_PRIORITY);

	/*
	 * 自分のMACアドレス読み込み
	 */
    ic = IF_ETHER_NIC_GET_SOFTC();
    error = dhcp_open(ic);
	if(error != E_OK){
		syslog(LOG_ERROR, "DHCP ERROR: %s !", itron_strerror(error));
		slp_tsk();
	}

	/*
	 *  SDカード検出待ち
	 */
	while((psdev->_sdev_attribute & SDEV_EMPLOY) == 0){
		SDMSence_task(0);
	}
	syslog_0(LOG_NOTICE, "start telnet !");
	tcp_telnet_srv_init(callback_telnet);
	while(ch != EOF){
		if(tcp_telnet_connect()){	/* connect */
			if(application != NULL)
				ch = application(0);
			else{
				putchar(ch = getchar());
				if(ch == CHAR_CR)
					putchar(CHAR_LF);
			}
		}
		else				/* disconnect */
			dly_tsk(100);
	}

	syslog(LOG_NOTICE, "Sample program ends.");
	kernel_exit();
}
