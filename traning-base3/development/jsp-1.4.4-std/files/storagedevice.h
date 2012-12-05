/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2010      by GJ Designing Center RICOH COMPANY,LTD. JAPAN
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
 *  ストレージデバイスの基本設定
 */
#ifndef NUM_STORAGEDEVICE
#define	NUM_STORAGEDEVICE   4		/* デフォルトのストレージデバイス数 */
#endif
#define MINIMUM_DEVNO       0
#define MAXIMUM_DEVNO       9
#ifndef DEFAULT_DEVNO
#define DEAFULT_DEVNO       MINIMUM_DEVNO
#endif

#define SDEV_ACTIVE         (1<<15)	/* アクティブなデバイス */
#define SDEV_INSERTCHK      (1<<14)	/* 挿入・排出の設定あり */
#define SDEV_CHKREMOVE      (1<<13)	/* 排出検査する */
#define SDEV_EMPLOY         (1<<8)	/* 使用可能 */
#define SDEV_DEVERROR       (1<<7)	/* DEVICE ERROR */
#define SDEV_DEVNOTUSE      (1<<0)	/* DEVICE 使用不可 */
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
 *  デバイスドライバー用関数テーブル定義
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
 *  POSIXファイルインターフェイス用関数テーブル定義
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
 *  ストレージデバイス型定義
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
 *  ストレージデバイスヘッダー型定義
 */
typedef struct StorageDeviceHead {
	H   _num_activedev;
    B   _sdev_active;
	B   _default_device;
	UW  (*_get_datetime)(void);
    StorageDevice_t *_psd;
} StorageDeviceHead_t;

/*
 *  SDMの全体定義
 */
extern StorageDeviceHead_t SDeviceHead;

/*
 *  各サービスのプロトタイプ宣言
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
