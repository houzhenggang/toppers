//
//  TINET (TCP/IP Protocol Stack)
// 
//  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
//                   Tomakomai National College of Technology, JAPAN
//  Copyright (C) 2008-2009 by Hokkaido Industrial Research Institute, JAPAN
//
//  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
//  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
//  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
//  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
//  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
//  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
//      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
//      ����������˴ޤޤ�Ƥ��뤳�ȡ�
//  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
//      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
//      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
//      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
//  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
//      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����ξ������������ȡ�
//    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
//        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
//  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
//      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
//
//  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
//  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
//  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
//  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
// 
//  @(#) $Id: tinet_defs.h,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#ifndef _TINET_DEFS_H_
#define _TINET_DEFS_H_

//
//  ���֥������ȥ���̾
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
