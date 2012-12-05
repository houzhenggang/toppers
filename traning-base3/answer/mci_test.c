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
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
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
 *  �ѥ��ץ��ޥ���ֹ�
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
 *  �ѥ��ץ��ޥ�ɥơ��֥�
 */
static const struct SUBCOMMAND_TABLE const mon_pipe[] = {
	{"READ",	PIPE_READ    },	/* 1�֥�å�READ */
	{"WRITE",	PIPE_WRITE   },	/* 1�֥�å�WRITE */
	{"EXIT",	PIPE_EXIT    },	/* ��λ */
	{"HELP",	PIPE_HELP    }
};

/*
 *  PIPE���ޥ�ɤΥǥ����ѥå�
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
	case PIPE_READ:	/* SECTOR READ���� */
		sscanf((char *)&command[point], "%d", &arg1);
		actcount = 1;
		sector = arg1;
		actaddr = act_buffer;
		break;
	case PIPE_WRITE:/* SECTOR WRITE���� */
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
 *  �ᥤ�󥿥���
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
   *  MCI�ǥХ����ν�����������ץ󡢥����ɤγ�ǧ
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
   *  READ/WRITE�μ¹�
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


