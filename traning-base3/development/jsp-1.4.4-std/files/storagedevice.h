/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010      by GJ Designing Center RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: storagedevice.h,v 1.2 2010/07/09 18:39:56 roi Exp $
 */

#ifndef _STORAGEDEVICE_H_
#define _STORAGEDEVICE_H_

#include <s_services.h>
#include <t_services.h>
#ifndef _MACRO_ONLY
#include <fcntl.h>
#endif

/*
 * This file includes the definitions for open and fcntl
 * described by POSIX for <fcntl.h>; it also includes
 * related kernel definitions.
 */
#ifndef _MACRO_ONLY
#include <sys/types.h>
#endif

/*
 *  ���ȥ졼���ǥХ����δ�������
 */
#ifndef NUM_STORAGEDEVICE
#define	NUM_STORAGEDEVICE   4		/* �ǥե���ȤΥ��ȥ졼���ǥХ����� */
#endif
#define MINIMUM_DEVNO       0
#define MAXIMUM_DEVNO       9
#ifndef DEFAULT_DEVNO
#define DEAFULT_DEVNO       MINIMUM_DEVNO
#endif

#define SDEV_ACTIVE         (1<<15)	/* �����ƥ��֤ʥǥХ��� */
#define SDEV_INSERTCHK      (1<<14)	/* �������ӽФ����ꤢ�� */
#define SDEV_CHKREMOVE      (1<<13)	/* �ӽи������� */
#define SDEV_EMPLOY         (1<<8)	/* ���Ѳ�ǽ */
#define SDEV_DEVERROR       (1<<7)	/* DEVICE ERROR */
#define SDEV_DEVNOTUSE      (1<<0)	/* DEVICE �����Բ� */
#define SDEV_NOTUSE         255


/* File attribute bits for directory entry */

#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define	AM_VOL	0x08	/* Volume label */
#define AM_LFN	0x0F	/* LFN entry */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */
#define AM_MASK	0x3F	/* Mask of defined bits */

/*
 *  chmod value
 */
#define FF_READ     0x0000444
#define FF_WRITE    0x0000222
#define FF_EXEC     0x0000111

#ifndef _MACRO_ONLY

struct dirent2
{
/* NOTE: This is OUR VERSION of this structure. It contains all the fields currently used by IPS code.
	If you add fields here, you will also have to modify vcwrapnt.c::*dir() to fill those fields! */
	unsigned long  d_fsize;
	unsigned short d_date;
	unsigned short d_time;
	unsigned short d_reclen;
	unsigned char  d_type;
	unsigned char  d_dummy;
	char           d_name[256];		/* FIXME: use NAME_MAX? */
};

/*
 * file system statistics
 */
struct statfs2 {
  long           f_type;		/* type of file system (unused; zero) */
  long           f_bsize;		/* fundamental file system block size */
  long           f_blocks;		/* total data blocks in file system */
  long           f_bfree;		/* free blocks in fs */
  long           f_bavail;		/* free blocks avail to non-superuser */
};

/*
 *  �ǥХ����ɥ饤�С��Ѵؿ��ơ��֥����
 */
typedef struct StorageDeviceFunc {
	int (*_sdevf_sense)(void *psdev, BOOL on);
	int (*_sdevf_diskinit)();
	int (*_sdevf_diskstatus)();
	int (*_sdevf_diskread)();
	int (*_sdevf_diskwrite)();
	int (*_sdevf_diskioctl)();
} StorageDeviceFunc_t;

/*
 *  POSIX�ե����륤�󥿡��ե������Ѵؿ��ơ��֥����
 */
typedef struct StorageDeviceFileFunc {
	void  *(*_sdevff_opendir)(const char *name);
	int   (*_sdevff_closedir)(void *dir);
	int   (*_sdevff_readdir)(void *dir, void *dirent2);
	int   (*_sdevff_mkdir)(const char *name);
	int   (*_sdevff_rmdir)(const char *name);
	int   (*_sdevff_unlink)(const char *name);
	int   (*_sdevff_rename)(const char *oname, const char *nname);
	int   (*_sdevff_chmod)(const char *name, int mode);
	int   (*_sdevff_stat)(const char *name, struct stat *buf);
	int   (*_sdevff_statfs)(const char *name, void *status);
	int   (*_sdevff_open)(const char *name, int flags);
	int   (*_sdevff_close)(int fd);
 	int   (*_sdevff_fstat)(int fd, struct stat *buf);
	off_t (*_sdevff_lseek)(int fd, off_t offset, int whence);
	long  (*_sdevff_read)(int fd, void *buf, long count);
	long  (*_sdevff_write)(int fd, const void *buf, long count);
	void  *(*_sdevff_mmap)(void *start, size_t length, int prot, int flags, int fd, off_t offset);
} StorageDeviceFileFunc_t;

/*
 *  ���ȥ졼���ǥХ��������
 */
typedef struct StorageDevice {
    UH    _sdev_attribute;
	UB    _sdev_devno;
	UB    _sdev_port;
    UW    _sdev_maxsec;
    UW    _sdev_secsize;
    void  (*_sdev_notice)(void *psdev, BOOL sw);
    void  *_sdev_local[4];
	StorageDeviceFunc_t     *pdevf;
	StorageDeviceFileFunc_t *pdevff;
} StorageDevice_t;

/*
 *  ���ȥ졼���ǥХ����إå��������
 */
typedef struct StorageDeviceHead {
	H   _num_activedev;
    B   _sdev_active;
	B   _default_device;
	UW  (*_get_datetime)(void);
    StorageDevice_t *_psd;
} StorageDeviceHead_t;

/*
 *  SDM���������
 */
extern StorageDeviceHead_t SDeviceHead;

/*
 *  �ƥ����ӥ��Υץ�ȥ��������
 */
extern void  sdev_init(VP_INT exinf);
extern void  sdev_terminate(void);
extern ER    SDMSetupDevice(H devno, StorageDevice_t **ppsdev);
extern ER_ID SDMGetDeviceNo(const char **ppathname);
extern StorageDevice_t *SDMGetStorageDevice(int devno);
extern ER    SDMEmploy(StorageDevice_t *psdev, BOOL sw);
extern void  SDMSence_task(VP_INT exinf);

extern void stdfile_init(VP_INT exinf);

#endif /* _MACRO_ONLY */
#endif /* _STORAGEDEVICE_H_ */
/*  end of file  */
