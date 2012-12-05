/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: mci.h,v 1.1 2011/02/13 21:18:56 roi Exp $
 */

#ifndef _MCI_H_
#define _MCI_H_


#define INHNO_MMC           INTNO_MMC

#define CMD_SHORTRESP       (1<<6)	/* short response */
#define CMD_LONGRESP        (1<<7)	/* long response */
#define CMD_SLONGRESP       (CMD_SHORTRESP|CMD_LONGRESP)
#define CMD_TIMEOUT         (1<<8)	/* timeout request bit */
#define CMD_SETLAST         (1<<10)
#define CMD_MASK            0xFFFF
#define CMD_IGNOREIRES      (1<<16)
#define CMD_INDEX           0x003F

/*
 *  SD/MMC �R�}���h���X�g
 */
#define MCI_CMD0			(0x0000)								/* GO_IDLE_STATE(MMC) or RESET(SD) */
#define MCI_CMD1			(0x0001|CMD_SHORTRESP|CMD_IGNOREIRES)	/* SEND_OP_COND(MMC) or CMD1(SD) */
#define MCI_CMD2			(0x0002|CMD_SLONGRESP|CMD_IGNOREIRES)	/* ALL SEND_CID */
#define MCI_CMD3			(0x0003|CMD_SHORTRESP)					/* SET_RELATE_ADDR */
#define MCI_CMD6			(0x0006|CMD_SHORTRESP)
#define MCI_CMD7			(0x0007|CMD_SHORTRESP)					/* SELECT/DESELECT_CARD */
#define MCI_CMD9			(0x0009|CMD_SLONGRESP|CMD_IGNOREIRES)	/* SEND_CSD */
#define MCI_CMD12			(0x000C|CMD_SHORTRESP)					/* Stop either READ or WRITE operation */
#define MCI_CMD13			(0x000D|CMD_SHORTRESP)					/* SEND_STATUS */
#define MCI_CMD16			(0x0010|CMD_SHORTRESP)					/* SET_BLOCK_LEN */
#define MCI_CMD17			(0x0011|CMD_SHORTRESP)					/* READ_SINGLE_BLOCK */
#define MCI_CMD24			(0x0018|CMD_SHORTRESP)					/* WRITE_BLOCK */
#define MCI_ACMD41			(0x0029|CMD_SHORTRESP|CMD_IGNOREIRES)	/* ACMD41 for SD card */		
#define MCI_CMD55			(0x0037|CMD_SHORTRESP)					/* APP_CMD, the following will a ACMD */

#define RES_CMD1            (MCI_CMD1 & CMD_INDEX)
#define RES_CMD12           (MCI_CMD12 & CMD_INDEX)
#define RES_ACMD41          (MCI_ACMD41 & CMD_INDEX)

#define OCR_INDEX			0x00FF8000

#define CARD_STATUS_ACMD_ENABLE		(1<<5)
#define CARD_STATUS_RDY_DATA		(1<<8)
#define CARD_STATUS_CURRENT_STATE	(0x0F<<9)
#define CARD_STATUS_ERASE_RESET		(1<<13)

#define SLOW_RATE			1
#define NORMAL_RATE			2

#define SD_1_BIT 			0
#define SD_4_BIT			1

#define MMC_CARD			1
#define SD_CARD				2

#define MCI_NOTEND          0
#define MCI_END             1
#define MCI_ERREND          2

/* Error code on the command response. */
#define INVALID_RESPONSE	0xFFFFFFFF

#define SDMODE_PROTECT      (1<<0)
#define SDMODE_WRITE        (1<<7)

#ifndef _MACRO_ONLY

/*
 *  MCI-I/O�|�[�g�̋��L�Ǘ��̈�
 */
typedef struct mci_port_common_block {
	UINT    base;
	UINT    status;
	UINT    mask;
	UINT    cardRCA;
	UINT    cardType;
	UB      retryCount;
	UB      endFlag;
	UH      mode;
}MCIPCMB;

/*
 *  MCI-I/O�|�[�g�Ǘ��u���b�N�̒�`
 */
typedef struct mci_port_control_block	MCIPCB;

extern void  mci_init(VP_INT exinf);
extern void  dma_init(VP_INT exinf);
extern void  mci_isr0(void);
extern void  dma_isr0(void);

#endif	/* _MACRO_ONLY */

#if defined(LPC2388)
#include "lpc23xx_mci.h"
#else
#error "not support mci board."
#endif

#endif /* end _MCI_H_ */
