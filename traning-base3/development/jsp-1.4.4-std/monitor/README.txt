
        �� TOPPERS/JSP�����ͥ� �桼�����ޥ˥奢�� ��
      ��monitor��netDevice��������newlibɸ�������Ϥ��б���

        ��Release 1.4.3 �б����ǽ�����: 11-27-2010��

------------------------------------------------------------------------
 TOPPERS/JSP Kernel
     Toyohashi Open Platform for Embedded Real-Time Systems/
     Just Standard Profile Kernel

 Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
                             Toyohashi Univ. of Technology, JAPAN
 Copyright (C) 2003-2004 by Takagi Nobuhisa
 Copyright (C) 2003-2010 by Ryosuke Takeuchi
                     GJ Business Division RICOH COMPANY,LTD. JAPAN

 �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
     ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
     ����������˴ޤޤ�Ƥ��뤳�ȡ�
 (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
     �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
     ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
     �ȡ�
   (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
       �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
   (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
       ��𤹤뤳�ȡ�
 (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
     ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�

 �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
------------------------------------------------------------------------
/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

����monitor�ˤĤ���

���ݣ�������
�ܥ�˥��ϡ�TOPPERS�ץ������ȶ���ףǤμ��������Ѥ˺������줿�ץ����
�Ǥ���TOPPERS/JSP1.4.1��ǥ������Ȥ��Ƽ¹Ԥ��ޤ����¹Գ�ǧ�ϰʲ��Σ��Ĥ�
�Ķ��Ķ��Ǽ¹Գ�ǧ��ԤäƤ��ޤ���
����m16c(OAKS16-mini��OAKS16)   ��ͥ����ƥ��Υ���TM
����h8(AKIH8-3048,AKIH8-3069F)  PizzaFactory2+GNU(h8300-hms)
                                cygwin+GNU(h8300-hms)
����sh2(hsb7616it)              cygwin+GNU(sh-hitachi-elf)

���ݣ������󥽡���λ���
��������˥��Υ��󥽡�����̾�ϥ��ꥢ��ǥХ������оݤȤ��Ƥ��ޤ���
MONTSK(��������˥��Υ�����)�ε�ư�ΰ������Ϥ����exinf���ͤ��˥���
�̿����ϥǥХ����Ȥ��Ƥ��ޤ���â����netDevice�Υ����ФȤ��Ƶ�ư������
���󥽡����Windows���netTerm�Ȥʤ�ޤ���

���ݣ�������ѥ��륹���å�
��������˥��Υӥ�ɤǼ¹Ե�ǽ����ꤹ�륳��ѥ��륹���å��ˤĤ����������ޤ���

����MONITOR_PORTID
��˥��Υǥե���ȥݡ��Ȥϥ��ꥢ�륳�󥽡����CONSOLE_PORTID�ˤǤ�����
��˥��ε�ư���󥽡�����ѹ���������硢����ѥ��륹���å���
-DMONITOR_PORTID=n����ꤹ����ѹ�����ǽ�Ǥ������ΤȤ�������ݡ��ȤΥ����ץ��
��˥��ε�ư���˹Ԥ��ޤ���(Ver1.1.0��NEED_OPEN�Υ����å��Ϻ�����ޤ�)

����SUPPORT_PIPE
���Υ����å����������ȡ����դ��Υ��ޥ�ɤ��ĥ���ޤ���
���դ����ޥ�ɤ���1���ޥ��"PIPE"�ǵ�ư���ޤ���
���դ����ޥ�ɤ�Ϣ��ؿ���pipe_command(B *command);�����ꤷ�Ƥ���������

����SUPPORT_ETHER
TINET�Υ��ޥ�ɥ����ӥ��ڤ�netDevice�Υ��ޥ�ɳ�ĥ��Ԥ��ޤ���
���Υ��ޥ�ɤ���1���ޥ��"NET"�ǵ�ư���ޤ���

����START_TASKID
netDEvice����³������ư�¹Ԥ��륿�����ֹ����ꤷ�ޤ���
-DSTART_TASKID=1
�Τ褦�˻��ꤹ��ȡ�netDevice����³�塢����Υץ���ब��ưŪ�˼¹Ԥ��ޤ���

����NEED_MONITOR
���Υ���ѥ��륹���å�����ꤹ��ȡ���˥��ε�ư����need_monitor()�ؿ���Ƥ�
�Ф��ޤ������δؿ�������ͤ�FALSE�ξ�硢��˥���������λ���ޤ���

����MONITOR_DELAY
���Υ���ѥ��륹���å������ꤵ�줿��硢��˥��ε�ư�������󥽡���ν��Ϥ�
MONITOR_DELAY(ms)�Ԥ���Ԥä���ǹԤ��ޤ���

���ݣ���TOPPERS/JSP�μ�����ĥ�ˤĤ���
��������˥��ΰʲ��ε�ǽ��¸����뤿���TOPPERS/JSP�μ�����¸config��
�����Ĥ��β�¤��ɬ�פǤ���

����_kernel_break_wait��������ɲ�(ɬ��)
JSP�����ͥ�Υ����ӥ�������Ǥ��Ԥ����֤�Ƚ��Τ���ˡ�_kernel_break_wait
��٥�򥵡��ӥ���������Ԥ��ץ������֤��������ɬ�פ�����ޤ���
�����ӥ���������Ԥ��ץ������֤��̾�ƣãУդ�cpu_support.S�β��줫��
���֤ˤ���ޤ���

����iana_tsk�Υ�󥯥ݥ���Ȥ������ɬ�ܤǤϤʤ���
��������˥��Ǥϳƥ������μ¹������dispatch�Υ������ڤ��ؤ�����iana_tsk
�ؿ���ƤӽФ����ȤǾ��������ԤäƤ��ޤ������Τ���iana_tsk�θƤӽФ���
��ꡢ�����å��󥰻��֤��礭���㲼���ޤ�����������"log task"���ޥ�ɤˤ��
����������ϥꥢ�륿���ॷ���ƥ�θ��ڤˤ�ͭ�Ѥʼ��ʤǤ���
�̾�ϥ���ѥ��륹���å�MON�ˤ�ꡢ��곰����ǽ�Ȥ���ɬ�פΤʤ�����
��곰���ơ����Ѥ��Ƥ���������
dispatch�ؿ����̾�ƣãУդ�cpu_support.S��ˤ���ޤ���

���ݣ�����������˥��Υޥ˥奢��
����display���ޥ��
display byte [<start address> [<end address>]]
        <start address>����<end address>�ޤǤΥ���ޤ��ϥݡ����ΰ��
        ���Х���ñ�̤�ɽ�����롣<end address>���ά��������128�Х��Ȥ�
        ɽ����Ԥ���<start adress>���ά�������ϡ�����ɽ����Ԥä�����
        ���ɥ쥹����ɽ����Ԥ���

display half [<start address> [<end address>]]
        <start address>����<end address>�ޤǤΥ���ޤ��ϥݡ����ΰ��
        ���Х���ñ�̤�ɽ�����롣<end address>���ά��������128�Х��Ȥ�
        ɽ����Ԥ���<start adress>���ά�������ϡ�����ɽ����Ԥä�����
        ���ɥ쥹����ɽ����Ԥ���

display word [<start address> [<end address>]]
        <start address>����<end address>�ޤǤΥ���ޤ��ϥݡ����ΰ��
        ���Х���ñ�̤�ɽ�����롣<end address>���ά��������128�Х��Ȥ�
        ɽ����Ԥ���<start adress>���ά�������ϡ�����ɽ����Ԥä�����
        ���ɥ쥹����ɽ����Ԥ���

display task
        ��Ͽ���줿�����������Ƥ�ɽ�����롣ɽ�����Ƥϰʲ����̤ꡣ
        cur     	�����ȥ�������*����˥���������mon��ɽ�����롣
        id          ������ID��ɽ�����롣
        pri         ����ͤΥ�����ͥ����
        state       �������ξ���
        pc          RUN���ְʳ��ʤ顢���ߤΥץ���५������
        stack       ���ߤΥ����å����ɥ쥹
        inistack    ����ͥ����å�����Ƭ���ɥ쥹
        inisize     ����ͥ����å��ΥХ��ȥ�����

diaplay register
        �����ȥ��������Ԥ����֤Ȥʤä���硢�Ԥ����֤Υ쥸���������Ƥ�
        ɽ�����롣�����ӥ�����������Ԥ��Ǥϥ쥸��������¸��Ԥ�ʤ��١�
        �쥸������ɽ���ϹԤ�ʤ����쥸���������Ƥ�CPU�ˤ�äưۤʤ롣

����set���ޥ��
set byte [<start address>]
        <start address>�����Ƥ򣱥Х���ɽ���������Ԥ��Ȥʤ롣�����ʿ����ϸ�
        <RETURN>�ˤƥХ����ͤ����Ϥ����<start address>���ͤ����߸塢
        <start address>�����Ƥ��ɽ����<start address>+1�����Ƥ������Ԥ��Ȥʤ�
        .<RETURN>�ˤ�set���ޥ�ɤ�λ���ץ��ץ�ɽ������롣<start address>
        ���ά������硢�Ǹ�˽��������Υ��ɥ쥹�ν���ߤ�Ԥ���

set half [<start address>]
        <start address>�����Ƥ򣲥Х���ɽ���������Ԥ��Ȥʤ롣�����ʿ����ϸ�
        <RETURN>�ˤƥХ����ͤ����Ϥ����<start address>���ͤ����߸塢
        <start address>�����Ƥ��ɽ����<start address>+2�����Ƥ������Ԥ��Ȥʤ�
        .<RETURN>�ˤ�set���ޥ�ɤ�λ���ץ��ץ�ɽ������롣<start address>
        ���ά������硢�Ǹ�˽��������Υ��ɥ쥹�ν���ߤ�Ԥ���

set ward [<start address>]
        <start address>�����Ƥ򣲥Х���ɽ���������Ԥ��Ȥʤ롣�����ʿ����ϸ�
        <RETURN>�ˤƥХ����ͤ����Ϥ����<start address>���ͤ����߸塢
        <start address>�����Ƥ��ɽ����<start address>+2�����Ƥ������Ԥ��Ȥʤ�
        .<RETURN>�ˤ�set���ޥ�ɤ�λ���ץ��ץ�ɽ������롣<start address>
        ���ά������硢�Ǹ�˽��������Υ��ɥ쥹�ν���ߤ�Ԥ���

set command [<mode>]
        ���ޥ�ɥ⡼�ɤ����ꤹ�롣�⡼�ɤϣ�(1���ޥ��)����(2���ޥ��)�⡼�ɤ�
        �ǥե���Ȥϣ����ޥ�ɥ⡼��(�㡧display��byte�Σ��ĤΥ��ޥ�ɤ�
        ���ޥ�������Ԥ�)�Ǥ��롣�����ޥ�ɤϣ����ޥ�ɤ���Ƭ��1ʸ�����Ȥ߹�
        �碌�����ĤΥ��ޥ�ɤǥ��ޥ�������Ԥ���(�㡧display byte�Ǥ�db)
        <mode>���ά����ȸ��ߤΥ��ޥ�ɥ⡼�ɤ�ɽ����Ԥ���
        �����ޥ�ɥ⡼�ɤǤ⡢���ޥ�ɤκǽ��1ʸ�������ϤǼ¹Բ�ǽ�Ǥ��롣
        (�㡧display byte�Ǥ� d b)

set serial [<portid>]
        ��������˥����������б��Υ��ꥢ��Υݡ����ֹ��<porid>���ѹ�����
        <portid>���ά����ȸ��ߤΥݡ����ֹ��ɽ�����롣

set task [<task id>]
        <task id>�ǻ��ꤷ���������˥����ȥ��������ѹ����롣
        <task id>���ά����ȥ�˥��������򥫥��ȥ����������ꤹ�롣

����task���ޥ��
task activate
        �����ȥ�������act_tsk(<�����ȥ�����ID>)�����ӥ��������ȯ�Ԥ��롣

task terminate
        �����ȥ�������ter_tsk(<�����ȥ�����ID>)�����ӥ��������ȯ�Ԥ��롣

task suspend
        �����ȥ�������sus_tsk(<�����ȥ�����ID>)�����ӥ��������ȯ�Ԥ��롣

task resume
        �����ȥ�������rsm_tsk(<�����ȥ�����ID>)�����ӥ��������ȯ�Ԥ��롣

task priority [pir]
        �����ȥ�������chg_tsk(<�����ȥ�����ID>, <pri>)�����ӥ��������
        ȯ�Ԥ��롣

����log���ޥ��
log mode [<logmask> [<lowmask>]]
        syslog��ɽ���⡼�ɤ��ѹ����롣<logmask>��<lowmask>���ά�������
        ���ߤ�<logmask>��<lowmask>��ɽ�����롣�����ͤΥޥ������б���
        �ʲ����̤�Ǥ��롣
        <�ޥ���>   <������>
        LOG_EMERG     0     ����åȥ�������ͤ��륨�顼:lowmask default
        LOG_ALERT     1
        LOG_CRIT      2
        LOG_ERROR     3     �����ƥ२�顼
        LOG_WARNING   4     �ٹ��å�����
        LOG_NOTICE    5                                 :logmask default
        LOG_INFO      6
        LOG_DEBUG     7     �ǥХå��ѥ�å�����
        logmask default��lowmask default���Ÿ�RTOS��ư��Υǥե������

log task [<cycle time>]
        <cycle time>ms�����˳ƥ�����������������Υ������μ¹Ի��֤�ɽ�����롣
        <cycle time>���ά������硢�����log taskɽ������γƥ�������
        �¹Ի��֤�ɽ�����롣

log port [<no> <logno> [<portaddress>]]
        �ݡ��ȥ�˥���ǽ�����ꡣ<portaddress>�����ꤷ�����<portaddress>��
        ������������뤿�Ӥ�<logno>�ˤƥ��������ǡ�����syslog�ˤƥ�ɽ��
        ���롣
         <no> <logno> <portaddress>������ˤ�<portaddress>��<no>��logmask��
         <logno>�ˤƥݡ��ȥ�˥��������Ԥ���â����<logno>��1�ʾ�7�ޤǤ��͡�
         <no> <0>������ˤƥݡ��ȥ�˥��β����Ԥ���
         �������ά����ȡ��ݡ��ȥ�˥�����Ͽ���֤�ɽ����Ԥ���

����volume���ޥ��
TINET��ͭ���Ǥ��ꡢSUPPORT_VOLUME����ѥ��륹���å���ͭ���ξ��Τ߻��Ѳ�ǽ��
���ޥ�ɤǤ��롣
volume format <drive>
         <drive>���Ф��ƥե����ޥåȤ�Ԥ���

volume dir  [<path>]
         <path>�Υǥ��쥯�ȥ��ɽ�����롣<path>���ά������硢�ǥե����
         derive�Υǥ��쥯�ȥ��ɽ�����롣

volume mkdir <path>
         <path>�ǻ��ꤷ���ǥ��쥯�ȥ��������롣

volume rmdir <path>
         <path>�ǻ��ꤷ���ǥ��쥯�ȥ�������롣

volume erase <path>
         <path>�ǻ��ꤷ���ե�����������롣

����pipe���ޥ��
SUPPORT_PIPE����ѥ��륹���å���ͭ���ǡ���ĥ���ޥ�ɤ��Ѱդ���Ƥ�����Τ�
ͭ���ʥ��ޥ�ɤǤ��ꡢ���ޥ�ɻ��ͤϳ�ĥ���줿�桼�����ꥳ�ޥ�ɤλ��ͤ�
������������ɥ��ޥ�ɤ��桼�����ꥳ�ޥ�ɤȤʤ롣

����help���ޥ��
��˥����ޥ�ɤΥإ�׾����ɽ�����롣

������˥��������Ϥ˴ؤ���
��˥��Υǡ��������ߤϡ�(FILE*)mon_infile���Ф���ǡ��������ߤ�Ԥ�
��˥��Υǡ��������ϡ�ɸ�������Ϥν��ϥե�����(stdout)���Ф��ƹԤ���


����ɸ�������Ϥ��б�

���ݣ�������
ɸ�������Ϥ�newlib�Ǥȴʰ��Ǥ�����Ǥ��ޤ���
newlib�Ǥϴʰ��Ǥ���١�H8�Υ�������32KB�ۤ��礭���ʤ�ޤ���
�����˱����ơ����򤷤Ƥ���������
newlib�Ǥ�h8�δĶ��Τ߼¹Գ�ǧ��ԤäƤ��ޤ���¾�δĶ��Ǥ�
�¹Գ�ǧ��ԤäƤ��ޤ���


���ݣ����ʰ���ɸ��������
monitor�ǥ쥯�ȥꥣ��ΰʲ��Υե��������Ѥ��ޤ�
��stdio.h������newlib���stdio.h��ͥ�褷�ƻ��Ȥ����
  printf.c����(printfʸ)
  sprintf.c   (sprintfʸ)
���ݡ��Ȥ��Ƥ���ɸ�������ϴؿ���stdio.h�򻲾Ȥ��Ƥ�������
�ޤ���printf�ؿ���sprintf�ؿ���libc.a��ͥ�褷�ƥ�󥯤����褦��
�饤�֥�ꥣ������ˡ�printf.o��sprintf.o�������褦�ˤ��Ƥ���������
�ޤ���OAKS16�Ѥγ�ȯ�Ķ�TM�ǻ��Ѥ������stdio.h������MTOOL��
stdio.h����Ѥ���褦�ˤ��Ƥ���������

���ݣ���newlib��ɸ��������
monitor�ǥ쥯�ȥꥣ���stdio.h��stddev.c��printf.c��sprintf.c�򻲾Ȥ��ʤ�
�褦�ˡ������Υե�����������Ƥ���������
�ޤ���monitor/Makefile.config�椫��stddev.o��printf.o��sprintf.o��ӥ�ɻ�
�˥�󥯤��ʤ��褦�˺�����Ƥ���������
newlib���ɸ�������Ϥϡ�putchar��putc�Τ褦�ʰ�ʸ�����ϴؿ���\n(����)�����ɤ�
�ʤ���ɽ����Ԥ��ޤ��󡣤ޤ���printf��puts�Τ褦��ʸ������ϴؿ���\n�����ɤ�
�դ����ƽ��Ϥ���ޤ���
putchar��putc���б���Ԥ��ˤϡ�������Ȥ��ƥХåե��Τʤ������Ԥ���
���Ǥ��ޤ������ζ���Ǥ�newlibrc.c���¤������������˥��ν��������
setbuf(stdio, 0);�ؿ��ˤơ����ϥХåե��ʤ��λ����ԤäƤ��ޤ���
��������˥�����Ѥ��ʤ����ϡ�setbuf�������ʬ�ǹԤäƤ���������
printf��puts�Τ褦��ʸ����ν��ϴؿ��˴ؤ��Ƥϡ�newlib���puts.c��
�������뤳�Ȥˤ�ꡢ�������򤹤뤳�Ȥ�����ޤ���
�ܺ٤ϣ���newlib�β�¤�򻲾Ȥ��Ƥ���������

�饤�֥�ꥣ�Υӥ�ɼ��ϰʲ����̤�Ǥ���
/home/roi/gnu��newlib�����ե�����򥳥ԡ���
gnu>tar zxvf newlib-1.11.0.tar.gz
gnu>mkdir /usr/local/h8300-hms
gnu>mkdir newlib-objdir
gnu>cd newlib-objdir
gnu>export TARGET_CFLAGS=-DREENTRANT_SYSCALLS_PROVIDED
gnu>/home/roi/gnu/newlib-1.11.0/configure --target=h8300-hms --prefix=/usr/local/h8300-hms
gnu>make
gnu>make install

���ץꥱ�������Υӥ�ɻ���ɸ���������Ѥμ������Ȥ��Ʋ�¤����
systask/newlibrt.c���󥯤���ɬ�פ�����ޤ���


���ݣ���newlib�β�¤(newlib-1.11.0/newlib/libc/stdio/)
puts.c�ν�����
/*
 * Write the given string to stdout, appending a newline.
 */

int
_DEFUN (_puts_r, (ptr, s),
	struct _reent *ptr _AND
	_CONST char * s)
{
  size_t c = strlen (s);
  struct __suio uio;
  struct __siov iov[2];

  iov[0].iov_base = s;
  iov[0].iov_len = c;
#if 0	/* TOPPERS.JSP */
  iov[1].iov_base = "\n";
#else	/* TOPPERS.JSP */
  iov[1].iov_base = "\0";
#endif	/* TOPPERS.JSP */
  iov[1].iov_len = 1;
  uio.uio_resid = c + 1;
  uio.uio_iov = &iov[0];
  uio.uio_iovcnt = 2;

  _REENT_SMALL_CHECK_INIT(_stdout_r (ptr));
  return (__sfvwrite (_stdout_r (ptr), &uio) ? EOF : '\n');
}


�ޤ���ɸ���������ѤΥ���٥�ؿ���systask/newlibrt.c�˵��ܤ��Ƥ���ޤ���
��¸��newlibrt.c��newlib�Ѥ�C����饤�֥�ꥣ��C++����饤�֥�ꥣ��
������ץ���ब���ä���˵��Ҥ��Ƥ���ޤ����Τǰʲ��Σ��ĤΥ�������
ʬ���ޤ�����newlib��ɸ�������Ϥ���Ѥ�����Ͽ�����newlibrt.c��
�ץ����Υӥ�ɻ��˥�󥯤���褦�ˤ��Ƥ���������
��������newlibrt.c��C�����Ѥ�newlib�饤�֥�ꥣ��TOPPERS�Ȥ�I/F��
��cpplibrt.c��C++�����Ѥδؿ��Ƚ�����ץ����

