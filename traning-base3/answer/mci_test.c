/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: mci_test.c,v 1.0 2011/06/12 08:55:29 roi Exp $
 */
#include <t_services.h>
#include <board_config.h>
#include <stdio.h>
#include "kernel_id.h"
#include "monitor.h"
#include "mci_test.h"
#include "mcicmd.h"

//#define TEST_WRITE

/*
 *  パイプコマンド番号
 */
#define PIPE_READ        0
#define PIPE_WRITE       1
#define PIPE_EXIT        2
#define PIPE_HELP        3

static B act_buffer[BLOCK_LENGTH];
static B test_buffer[BLOCK_LENGTH];
static INT actcount = 0;
static B   *actaddr = act_buffer;
static INT reqcmd =  PIPE_READ;
static INT sector;

/*
 *  パイプコマンドテーブル
 */
static const struct SUBCOMMAND_TABLE const mon_pipe[] = {
	{"READ",	PIPE_READ    },	/* 1ブロックREAD */
	{"WRITE",	PIPE_WRITE   },	/* 1ブロックWRITE */
	{"EXIT",	PIPE_EXIT    },	/* 終了 */
	{"HELP",	PIPE_HELP    }
};

/*
 *  PIPEコマンドのディスパッチ
 */
INT pipe_command(B *command)
{
	int   point=0;
	char  cmd=1;
	int   no, count, arg1;
	char  reg;
	count = sizeof(mon_pipe) / sizeof(struct SUBCOMMAND_TABLE);
	if(command[point]){
		for(no = 0 ; no < count ; no++){
			if(compare_word(mon_pipe[no].subcommand, command, 0)){
				skip_word(command, &point);
				cmd = mon_pipe[no].type;
				break;
			}
		}
	}
	reqcmd = cmd;
	arg1 = 0;
	switch(cmd){
	case PIPE_READ:	/* SECTOR READ制御 */
		sscanf((char *)&command[point], "%d", &arg1);
		actcount = 1;
		sector = arg1;
		actaddr = act_buffer;
		break;
	case PIPE_WRITE:/* SECTOR WRITE制御 */
		sscanf((char *)&command[point], "%d %x", &arg1);
		actcount = 1;
		sector = arg1;
		actaddr = act_buffer;
		break;
	case PIPE_EXIT:
		actcount = 1;
		break;
	default:
		printf("  READ  (sector #) (address)\n");
		printf("  WRITE (sector #) (address)\n");
		break;
	}
	return 0;
}


/*
 *  メインタスク
 */
void main_task(VP_INT exinf)
{
	ER_UINT	ercd;
	MCIPCB *pmci;
	int i, j;
	UINT MCI_CardType;
	UW maxsec;
	char tbuf[4];

	vmsk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog(LOG_NOTICE, "Sample program starts (exinf = %d).", (INT) exinf);

	syscall(serial_ctl_por(TASK_PORTID,
			(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

  /*
   *  MCIデバイスの初期化、オープン、カードの確認
   */
	memset(act_buffer, 0, BLOCK_LENGTH);

	pmci = mci_ini_por();
	if(pmci == NULL){
		syslog_0(LOG_NOTICE, "mci_ini_por ERROR !!");
		slp_tsk();		/* fatal error */
	}
	MCI_CardType = mci_opn_por(pmci);
	syslog_2(LOG_NOTICE, "Open [%08x][%d] !", pmci, MCI_CardType);
	if(MCI_CardType <= 0){
		syslog_0(LOG_NOTICE, "mci_opn_por ERROR !!");
		slp_tsk();		/* fatal error */
	}

	if(MciCheckCID(pmci) != E_OK){
		syslog_0(LOG_NOTICE, "## MCI_Check_CID ERROR ##");
		slp_tsk ();		/* fatal error */
	}

	if(MciSetAddress(pmci) != E_OK){
		syslog_0(LOG_NOTICE, "## MCI_Set_Address ERROR ##");
		slp_tsk ();		/* fatal error */
	}

	if(MciSendCSD(pmci, &maxsec) != E_OK){
		syslog_0(LOG_NOTICE, "## MCI_Send_CSD ERROR ##");
		slp_tsk ();		/* fatal error */
	}

	if(MciSelectCard(pmci) != E_OK){
		syslog_0(LOG_NOTICE, "## MCI_Select_Card ERROR ##");
		slp_tsk ();		/* fatal error */
	}

	syslog_1(LOG_NOTICE, "## MCI_CardType[%d] ##", MCI_CardType);
	if(MCI_CardType == SD_CARD){
		mci_set_clock(pmci, NORMAL_RATE );
		if (MciSDBusWidth(pmci, SD_4_BIT) != E_OK){
			syslog_0(LOG_NOTICE, "mci_set_clock ERROR !!");
			slp_tsk();		/* fatal error */
		}
	}

	if (MciSetBlockLen(pmci, BLOCK_LENGTH) != E_OK){
		syslog_0(LOG_NOTICE, "## MCI_Set_BlockLen ERROR ##");
		slp_tsk ();		/* fatal error */
	}
	syslog_0(LOG_NOTICE, "ready MCI !");

  /*
   *  READ/WRITEの実行
   */
	while(reqcmd != PIPE_EXIT){
		while(actcount == 0){
			dly_tsk(100);
		}
		if(reqcmd == PIPE_READ){
			printf("\nread sector [%d][%08x]\n", sector, actaddr);
#ifndef SAMLE_PROGRAM
			if(mci_rea_blk(pmci, actaddr, sector) != E_OK){
				syslog_0(LOG_NOTICE, "mci_rea_blk ERROR !!");
				ext_tsk();		/* fatal error */
			}
			if(mci_wai_trn(pmci, 5000) != E_OK){
				syslog_0(LOG_NOTICE, "mci_wai_trn ERROR !");
				ext_tsk();
			}
#endif
			for(i = 0; i < BLOCK_LENGTH; i += 16){
				if((i % 16) == 0){
					printf("\n%04x ", i);
				}
				for(j = 0 ; j < 16 ; j++)
					printf("%02x ", (UB)actaddr[i+j]);
				printf("  ");
				for(j = 0 ; j < 16 ; j++){
					if(actaddr[i+j] < ' ')
						printf(".");
					else{
						tbuf[0] = actaddr[i+j];
						tbuf[1] = 0;
						printf("%s", tbuf);
					}
				}
			}
			printf("\n");
		}
		else if(reqcmd == PIPE_WRITE){
			printf("\nwrite sector [%d][%08x]\n", sector, actaddr);
			for(i = 0; i < (BLOCK_LENGTH); i++){
				if((i % 16) == 0){
					printf("\n%04x ", i);
				}
				printf("%02x ", (UB)actaddr[i]);
			}
			printf("\n");
#ifdef TEST_WRITE
			if(mci_wri_blk(pmci, actaddr, sector) != E_OK){
				syslog_0(LOG_NOTICE, "mci_wri_blk ERROR !!");
				ext_tsk();		/* fatal error */
			}
			if(mci_wai_trn(pmci, 5000) != E_OK){
				syslog_0(LOG_NOTICE, "mci_wai_trn ERROR !");
				ext_tsk();
			}
			if(mci_rea_blk(pmci, test_buffer, sector) != E_OK){
				syslog_0(LOG_NOTICE, "mci_rea_blk ERROR !!");
				ext_tsk();		/* fatal error */
			}
			if(mci_wai_trn(pmci, 5000) != E_OK){
				syslog_0(LOG_NOTICE, "mci_wai_trn ERROR !");
				ext_tsk();
			}
			for(i = 0; i < (BLOCK_LENGTH); i++){
				if(test_buffer[i] != actaddr[i]){
					syslog_0(LOG_NOTICE, "compare error !");
					ext_tsk();
				}
			}
#endif	/* ROI DEBUG */
		}
		actcount = 0;
	}
	syslog(LOG_NOTICE, "Sample program ends.");
}


