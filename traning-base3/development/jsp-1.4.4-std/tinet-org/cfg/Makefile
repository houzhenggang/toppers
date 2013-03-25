#
#   TINET (TCP/IP Protocol Stack)
#  
#   Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
#                    Tomakomai National College of Technology, JAPAN
# 
#   �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
#   �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
#   �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
#   ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
#   ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
#   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
#       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
#       ����������˴ޤޤ�Ƥ��뤳�ȡ�
#   (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#       �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
#       �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
#       ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
#   (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#       �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����ξ������������ȡ�
#     (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
#         �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
#   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
#       ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
# 
#   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
#   ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
#   �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
#   ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
#  
#   @(#) $Id: Makefile,v 1.5 2009/12/24 05:39:31 abe Exp abe $
# 

#
#  ���ޥ��̾������ѥ��륪�ץ��������
#
CC       = g++
CFLAGS   = -O2 -Wall
INCLUDE  = -I. -I$(JSPCFGDIR)

#
#  ���֥������ȥե�����̾���إå��ե�����̾�����
#

COMMONOBJS= manager.o directorymap.o except.o \
            garbage.o component.o message.o singleton.o \
            parser.o mpstrstream.o event.o collection.o option.o

CFGOBJS   = tinet_parser.o tinet_staticapi.o \
            tinet_instanciate.o

JSPCFGDIR = ../../cfg

##############################################################################

all: tinet_cfg

clean:
	rm -f *.o

parser.o:	$(JSPCFGDIR)/base/parser.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/parser.cpp

manager.o:	$(JSPCFGDIR)/base/manager.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/manager.cpp

directorymap.o:	$(JSPCFGDIR)/base/directorymap.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/directorymap.cpp

except.o:	$(JSPCFGDIR)/base/except.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/except.cpp

garbage.o:	$(JSPCFGDIR)/base/garbage.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/garbage.cpp

component.o:	$(JSPCFGDIR)/base/component.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/component.cpp

message.o:	$(JSPCFGDIR)/base/message.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/message.cpp

singleton.o:	$(JSPCFGDIR)/base/singleton.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/singleton.cpp

mpstrstream.o:	$(JSPCFGDIR)/base/mpstrstream.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/mpstrstream.cpp

event.o:	$(JSPCFGDIR)/base/event.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/event.cpp

collection.o:	$(JSPCFGDIR)/base/collection.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/collection.cpp

option.o:	$(JSPCFGDIR)/base/option.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(JSPCFGDIR)/base/option.cpp

tinet_parser.o:	tinet_parser.cpp tinet_defs.h tinet_classes.h
	$(CC) $(CFLAGS) $(INCLUDE) -c tinet_parser.cpp

tinet_staticapi.o:	tinet_staticapi.cpp tinet_defs.h
	$(CC) $(CFLAGS) $(INCLUDE) -c tinet_staticapi.cpp

tinet_instanciate.o:	tinet_instanciate.cpp tinet_defs.h tinet_classes.h
	$(CC) $(CFLAGS) $(INCLUDE) -c tinet_instanciate.cpp

tinet_cfg: $(CFGOBJS) $(COMMONOBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o tinet_cfg $(CFGOBJS) $(COMMONOBJS)