//
//  TINET (TCP/IP Protocol Stack)
// 
//  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
//                   Tomakomai National College of Technology, JAPAN
//  Copyright (C) 2008-2009 by Hokkaido Industrial Research Institute, JAPAN
//
//  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
//  によって公表されている GNU General Public License の Version 2 に記
//  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
//  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
//  利用と呼ぶ）することを無償で許諾する．
//  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
//      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
//      スコード中に含まれていること．
//  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
//      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
//      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
//      の無保証規定を掲載すること．
//  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
//      用できない形で再配布する場合には，次の条件を満たすこと．
//    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
//        作権表示，この利用条件および下記の無保証規定を掲載すること．
//  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
//      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
//
//  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
//  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
//  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
//  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
// 
//  @(#) $Id: tinet_defs.h,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#ifndef _TINET_DEFS_H_
#define _TINET_DEFS_H_

//
//  オブジェクトキー名
//

#define OBJECT_TREE		"object"
#define RESERVED_ID		"reserved_id"

#define INCLUDE_FILE		"include"
#define TCP_REP			"tcp_rep"
#define TCP_CEP			"tcp_cep"
#define UDP_CEP			"udp_cep"
#define TCP6_REP		"tcp6_rep"
#define TCP6_CEP		"tcp6_cep"
#define UDP6_CEP		"udp6_cep"

#define IPSEC_SET_UP_SPD	"ipsec_set_up_spd"
#define IPSEC_SET_UP_SAD	"ipsec_set_up_sad"

#define TINET_ID		"/file/tinet_id"
#define TINET_CFG		"/file/tinet_cfg"
#define TINET_KERN_CFG		"/file/tinet_kern_cfg"

#define PREFIX			"/prefix"

#endif	/* of #ifndef _TINET_DEFS_H_ */
