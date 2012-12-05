/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2006 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2006-2011 by GJ Business Division RICOH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: $
 */

#ifndef _TINET_SYS_CONFIG_H_
#define _TINET_SYS_CONFIG_H_

/*
 *  �ǡ�������� (�ͥåȥ�����󥿥ե�����) �˴ؤ������
 */

/*
 *  NIC (EMAC �ߴ�) �˴ؤ������
 */
#define TMO_IF_ED_GET_NET_BUF	1	/* [ms]�������� net_buf ���������ॢ����	*/
					/* [s]�� ���������ॢ����			*/
#define TMO_IF_ED_XMIT		(2*IF_TIMER_HZ)

/*#define IF_ED_CFG_ACCEPT_ALL		 �ޥ�����㥹�ȡ����顼�ե졼����������Ȥ��ϥ����Ȥ򳰤���*/

/*
 *  �������ͥåȽ��ϻ��ˡ�NIC �� net_buf ����������˻��ꤹ�롣
 *
 *  ���: �ʲ��λ���ϡ�������Ǥ��ꡢif_ed �Ǥϡ�
 *        �������ʤ��Τǡ��ʲ��Υ����Ȥ򳰤��ƤϤʤ�ʤ���
 */

/*#define ETHER_NIC_CFG_RELEASE_NET_BUF*/

/*
 *  EMAC�˴ؤ������
 */

#define INHNO_ETHER		INTNO_ETHER		/* IRQ5 */

#define LPC_ETHER_ADDR_LEN	6			/* Ethernet (MAC) Address��Ĺ��	*/

/* MAC�ѤΥ���å������� */
#define PCONP_EMAC_CLOCK	0x40000000

/* EMAC MODULE ID	*/
#define PHILIPS_EMAC_MODULE_ID	((0x3902 << 16) | 0x2000)

/*
 *  PHY�˴ؤ������
 */
#define PHY_ADDRNO      1				/* PHY���ɥ쥹�ֹ� */
#define USE_RMII						/* PHY�Ȥ��̿���RMII����� */

#ifndef _MACRO_ONLY

#define ed_ena_inter(ipm)	chg_ipm(ipm)

/*
 *  �ǡ���
 */
extern UB lp23xx_macaddr[LPC_ETHER_ADDR_LEN];

/*
 *  �ؿ�
 */
void tinet_sys_initialize(void);


#endif	/* of #ifndef _MACRO_ONLY */

#endif /* _TINET_SYS_CONFIG_H_ */
