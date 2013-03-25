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
 *  @(#) $Id: netapp.h,v 1.5 2009/12/24 05:44:56 abe Exp abe $
 */

#ifndef _NETAPP_H_
#define _NETAPP_H_

/*
 *  IPv4 �� IPv6 ���ڴ����ޥ���
 */

#if defined(SUPPORT_INET4)
#define PUT_IPADDR(p,a,w)	put_ipv4addr(p,a,w)
#endif

#if defined(SUPPORT_INET6)
#define PUT_IPADDR(p,a,w)	put_ipv6addr(p,a,w)
#endif

/*
 *  ���󥽡�����Ѥ��륷�ꥢ��ݡ����ֹ�
 */

#ifndef CONSOLE_PORTID

#define	CONSOLE_PORTID		LOGTASK_PORTID

#endif	/* of #ifndef CONSOLE_PORTID */

/*
 *  �����Ѵ��Τ�����Ѵ�ɽ
 */

extern const char radhex[];
extern const char radHEX[];

/*
 *  �ؿ�
 */

extern char *skip_blanks (char *line);
extern int_t cons_getline (ID portid, char *line, int_t size);
extern char *get_int (int_t *val, char *line);
extern char *get_xuint (uint_t *val, char *line);
extern void cons_putchar (ID portid, char ch);
extern int_t cons_getchar (ID portid);
extern int_t cons_putnumber (ID portid, ulong_t val, int_t radix,
                           const char *radchar, int_t width,
                           bool_t minus, char padchar);
extern void cons_printf (ID portid, const char *fmt, ...);
extern int_t put_macaddr (ID portid, uint8_t *mac, int_t width);

#if defined(SUPPORT_INET4)
extern int_t put_ipv4addr (ID portid, T_IN4_ADDR *addr, int_t width);
#endif

#if defined(SUPPORT_INET6)
extern int_t put_ipv6addr (ID portid, const T_IN6_ADDR *addr, int_t width);
#endif

#endif	/* of #ifndef _NETAPP_H_ */
