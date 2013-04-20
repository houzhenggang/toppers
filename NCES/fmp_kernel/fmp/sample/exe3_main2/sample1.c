/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
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
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: sample1.c 64 2009-01-13 16:37:04Z ertl-honda $
 */

/* 
 *  サンプルプログラム(1)の本体
 *
 *  FMPカーネルの基本的な動作を確認するためのサンプルプログラム．
 *
 *  プログラムの概要:
 *
 *  ユーザインタフェースを受け持つメインタスク（タスクID: MAIN_TASK，優
 *  先度: MAIN_PRIORITY）と，3つの並列実行されるタスク（タスクID:
 *  TASK1〜TASK3，初期優先度: MID_PRIORITY）で構成される．また，起動周
 *  期が2秒の周期ハンドラ（周期ハンドラID: CYCHDR1）を用いる．
 *
 *  並列実行されるタスクは，task_loop回空ループを実行する度に，タスクが
 *  実行中であることをあらわすメッセージを表示する．
 *
 *  周期ハンドラは，三つの優先度（HIGH_PRIORITY，MID_PRIORITY，
 *  LOW_PRIORITY）のレディキューを回転させる．プログラムの起動直後は，
 *  周期ハンドラは停止状態になっている．
 *
 *  メインタスクは，シリアルI/Oポートからの文字入力を行い（文字入力を
 *  待っている間は，並列実行されるタスクが実行されている），入力された
 *  文字に対応した処理を実行する．入力された文字と処理の関係は次の通り．
 *  Control-Cまたは'Q'が入力されると，プログラムを終了する．
 *
 *  '1' : 対象タスクをTASK1に切り換える（初期設定）．
 *  '2' : 対象タスクをTASK2に切り換える．
 *  '3' : 対象タスクをTASK3に切り換える．
 *  '4' : クラス1に所属するタスクを指定する．
 *        対象周期ハンドラをCYCHDR1に切り替える．
 *        対象アラームハンドラをALMHDR1に切り替える．
 *  '5' : クラス2に所属するタスクを指定する．
 *        対象周期ハンドラをCYCHDR2に切り替える．
 *        対象アラームハンドラをALMHDR2に切り替える．
 *  '6' : クラス3に所属するタスクを指定する．
 *        対象周期ハンドラをCYCHDR3に切り替える．
 *        対象アラームハンドラをALMHDR3に切り替える．
 *  '7' : クラス4に所属するタスクを指定する．
 *        対象周期ハンドラをCYCHDR4に切り替える．
 *        対象アラームハンドラをALMHDR4に切り替える．
 *  '8' : プロセッサ1を指定する．
 *  '9' : プロセッサ2を指定する．
 *  '0' : プロセッサ3を指定する．
 *  '-' : プロセッサ4を指定する．
 *  'a' : 対象タスクをact_tskにより起動する．
 *  'A' : 対象タスクに対する起動要求をcan_actによりキャンセルする．
 *  'e' : 対象タスクにext_tskを呼び出させ，終了させる．
 *  't' : 対象タスクをter_tskにより強制終了する．
 *  '>' : 対象タスクの優先度をHIGH_PRIORITYにする．
 *  '=' : 対象タスクの優先度をMID_PRIORITYにする．
 *  '<' : 対象タスクの優先度をLOW_PRIORITYにする．
 *  'G' : 対象タスクの優先度をget_priで読み出す．
 *  's' : 対象タスクにslp_tskを呼び出させ，起床待ちにさせる．
 *  'S' : 対象タスクにtslp_tsk(10秒)を呼び出させ，起床待ちにさせる．
 *  'w' : 対象タスクをwup_tskにより起床する．
 *  'W' : 対象タスクに対する起床要求をcan_wupによりキャンセルする．
 *  'l' : 対象タスクをrel_waiにより強制的に待ち解除にする．
 *  'u' : 対象タスクをsus_tskにより強制待ち状態にする．
 *  'm' : 対象タスクの強制待ち状態をrsm_tskにより解除する．
 *  'd' : 対象タスクにdly_tsk(10秒)を呼び出させ，時間経過待ちにさせる．
 *  'x' : 対象タスクに例外パターン0x0001の例外処理を要求する．
 *  'X' : 対象タスクに例外パターン0x0002の例外処理を要求する．
 *  'y' : 対象タスクにdis_texを呼び出させ，タスク例外を禁止する．
 *  'Y' : 対象タスクにena_texを呼び出させ，タスク例外を許可する．
 *  'r' : 3つの優先度（HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY）のレ
 *        ディキューを回転させる．
 *  'c' : 周期ハンドラを動作開始させる．
 *  'C' : 周期ハンドラを動作停止させる．
 *  'I' : 周期ハンドラの割付けプロセッサを変更する． 
 *  'b' : アラームハンドラを5秒後に起動するよう動作開始させる．
 *  'B' : アラームハンドラを動作停止させる．
 *  'E' : アラームハンドラの割付けプロセッサを変更する．   
 *  'z' : 対象タスクにCPU例外を発生させる（タスクを終了させる）．
 *  'Z' : 対象タスクにCPUロック状態でCPU例外を発生させる（プログラムを
 *        終了する）．
 *  'i' : 対象タスクをmig_tskにより割付けプロセッサを変更する． 
 *  'g' : 対象タスクにmig_tskを呼び出させ，割付けプロセッサを変更する． 
 *  'f' : 対象タスクをmact_tskにより起動する．  
 *  'p' : 対象タスクにget_pidを呼び出させ，プロセッサ番号を表示させる．
 *  'V' : get_utmで性能評価用システム時刻を2回読む．
 *  'v' : 発行したシステムコールを表示する（デフォルト）．
 *  'q' : 発行したシステムコールを表示しない．
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

/*
 *  サービスコールのエラーのログ出力
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

/*
 *  タスクIDのテーブル
 */
uint_t const sample_tskid[6] = {
    TASK1,TASK2,TASK3,TASK4,TASK5,TASK6,
};

/*
 *  周期ハンドラIDのテーブル
 */
uint_t const sample_cycid[TNUM_PRCID] = {
    CYCHDR1,
    CYCHDR2,
};

/*
 *  アラームIDのテーブル
 */
uint_t const sample_almid[TNUM_PRCID] = {
    ALMHDR1,
    ALMHDR2,
};

/*
 *  シリアルポート番号のテーブル
 */
uint_t const serial_port[TNUM_PRCID] = {
    TASK_PORTID_PRC1,
    TASK_PORTID_PRC2,
};

/*
 *  並行実行されるタスクへのメッセージ領域
 */
char_t	message[6];


/*
 *  ループ回数
 */
ulong_t	task_loop;		/* タスク内でのループ回数 */

/*
 *  並行実行されるタスク
 */
void task(intptr_t exinf)
{
	volatile ulong_t	i;
	int_t		n = 0;
	int_t		tskno = (int_t) (exinf);
	const char	*graph[] = { "|", "  +", "    *", "||", "  ++", "    **" };
	char_t		c;
	  
	while (1) {
		syslog(LOG_NOTICE, "task%d is running (%03d).   %s",
			   tskno, ++n, graph[tskno-1]);
		for (i = 0; i < task_loop; i++);
		c = message[tskno-1];
		message[tskno-1] = 0;
		switch (c) {
		case 'e':
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			SVC_PERROR(ext_tsk());
			assert(0);
		case 's':
			syslog(LOG_INFO, "#%d#slp_tsk()", tskno);
			SVC_PERROR(slp_tsk());
			break;
		case 'S':
			syslog(LOG_INFO, "#%d#tslp_tsk(10000)", tskno);
			SVC_PERROR(tslp_tsk(10000));
			break;
		case 'd':
			syslog(LOG_INFO, "#%d#dly_tsk(10000)", tskno);
			SVC_PERROR(dly_tsk(10000));
			break;
		default:
			break;
		}
	}
}

/*
 *  周期ハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
void cyclic_handler(intptr_t exinf)
{
	ID		prcid = exinf;

	syslog(LOG_NOTICE, "cyclic_handler %d start!", exinf);
	SVC_PERROR(imrot_rdq(HIGH_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(MID_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(LOW_PRIORITY, prcid));
}

/*
 *  アラームハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
void alarm_handler(intptr_t exinf)
{
	ID		prcid = exinf;

	syslog(LOG_NOTICE, "alarm_handler %d start!", exinf);
	SVC_PERROR(imrot_rdq(HIGH_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(MID_PRIORITY, prcid));
	SVC_PERROR(imrot_rdq(LOW_PRIORITY, prcid));
}

/*
 *  メインタスク
 */
void main_task(intptr_t exinf)
{
	char_t	c;
	ER_UINT	ercd;
	PRI		tskpri;
	ID		prcid = exinf;
	ID		tskid = sample_tskid[(exinf - 1) * 3 ];
	int_t	        tskno = (exinf-1) * 3 + 1;
	ID		cycid = sample_cycid[(int_t)exinf-1];
	ID		almid = sample_almid[(int_t)exinf-1];
	bool_t  update_select = true;
//	uint_t  tme_select    = exinf;
	uint_t  prc_select    = exinf;
	uint32_t server_req;

#ifndef TASK_LOOP
	volatile ulong_t	i;
	SYSTIM	stime1, stime2;
#endif /* TASK_LOOP */
#ifdef G_SYSLOG
	uint_t e;
#endif /* G_SYSLOG */

	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (int_t) exinf);

	/*
	 *  シリアルポートの初期化
	 *
	 *  システムログタスクと同じシリアルポートを使う場合など，シリアル
	 *  ポートがオープン済みの場合にはここでE_OBJエラーになるが，支障は
	 *  ない．
	 */
	ercd = serial_opn_por(((int_t)serial_port[exinf-1]));
	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
									itron_strerror(ercd), SERCD(ercd));
	}
	SVC_PERROR(serial_ctl_por(serial_port[exinf-1],
							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*
	 *  ループ回数の設定
	 *
	 *  TASK_LOOPがマクロ定義されている場合，測定せずに，TASK_LOOPに定
	 *  義された値を，タスク内でのループ回数とする．
	 *
	 *  MEASURE_TWICEがマクロ定義されている場合，1回目の測定結果を捨て
	 *  て，2回目の測定結果を使う．1回目の測定は長めの時間が出るため．
	 */
#ifdef TASK_LOOP
	task_loop = TASK_LOOP;
#else /* TASK_LOOP */

#ifdef MEASURE_TWICE
	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
#endif /* MEASURE_TWICE */

	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
	task_loop = LOOP_REF * 400UL / (stime2 - stime1);
#endif /* TASK_LOOP */

	/*
	 *  タスクの起動
	 */
	SVC_PERROR(act_tsk(tskid));

	/*
 	 *  メインループ
	 */
	do {
		if (update_select) {
			prcid = prc_select;
			cycid = sample_cycid[prcid-1];
			almid = sample_almid[prcid-1];
			update_select = false;
			syslog(LOG_INFO, "select tskno 0x%x", tskno);
			syslog(LOG_INFO, "select cycid %d", cycid);
			syslog(LOG_INFO, "select almid %d", almid);
			syslog(LOG_INFO, "select processor %d", prcid);
		}
		
		SVC_PERROR(serial_rea_dat(serial_port[exinf-1], &c, 1));
		
		switch (c) {
		case 'e':
		case 's':
		case 'S':
		case 'd':
			message[tskno - 1] = c;
			break;
		case '1':
			tskno = 1;
                        tskid = TASK1;
			update_select = true;
			break;
		case '2':
			tskno = 2;
                        tskid = TASK2;
			update_select = true;
			break;
		case '3':
			tskno = 3;
                        tskid = TASK3;
			update_select = true;
			break;
		case '4':
			tskno = 4;
                        tskid = TASK4;
			update_select = true;
			break;
		case '5':
			tskno = 5;
                        tskid = TASK5;
			update_select = true;
			break;
		case '6':
			tskno = 6;
                        tskid = TASK6;
			update_select = true;
			break;
		case 'a':
			syslog(LOG_INFO, "#act_tsk(0x%x)", tskno);
			SVC_PERROR(act_tsk(tskid));
			break;
		case 'A':
			syslog(LOG_INFO, "#can_act(0x%x)", tskno);
			SVC_PERROR(ercd = can_act(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_act(0x%x) returns %d", tskno, ercd);
			}
			break;
		case '>':
			syslog(LOG_INFO, "#chg_pri(0x%x, HIGH_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, HIGH_PRIORITY));
			break;
		case '=':
			syslog(LOG_INFO, "#chg_pri(0x%x, MID_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, MID_PRIORITY));
			break;
		case '<':
			syslog(LOG_INFO, "#chg_pri(0x%x, LOW_PRIORITY)", tskno);
			SVC_PERROR(chg_pri(tskid, LOW_PRIORITY));
			break;
		case 'G':
			syslog(LOG_INFO, "#get_pri(0x%x, &tskpri)", tskno);
			SVC_PERROR(ercd = get_pri(tskid, &tskpri));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "priority of task 0x%x is %d", tskno, tskpri);
			}
			break;
		case 'w':
			syslog(LOG_INFO, "#wup_tsk(0x%x)", tskno);
			SVC_PERROR(wup_tsk(tskid));
			break;
		case 'W':
			syslog(LOG_INFO, "#can_wup(0x%x)", tskno);
			SVC_PERROR(ercd = can_wup(tskid));
			if (ercd >= 0) {
				syslog(LOG_NOTICE, "can_wup(0x%x) returns %d", tskno, ercd);
			}
			break;
		case 'c':
			syslog(LOG_INFO, "#sta_cyc(%d)", cycid);
			SVC_PERROR(sta_cyc(cycid));
			break;
		case 'C':
			syslog(LOG_INFO, "#stp_cyc(%d)", cycid);
			SVC_PERROR(stp_cyc(cycid));
			break;
		case 'b':
			syslog(LOG_INFO, "#sta_alm(%d, %d)", almid, ALM_TIME);
			SVC_PERROR(sta_alm(almid, ALM_TIME));
			break;
		case 'B':
			syslog(LOG_INFO, "#stp_alm(%d)", almid);
			SVC_PERROR(stp_alm(almid));
			break;
		default:
			break;
		}
	} while (c != '\003' && c != 'Q');

	syslog(LOG_NOTICE, "Sample program ends.");
	SVC_PERROR(ext_ker());
	assert(0);
}
