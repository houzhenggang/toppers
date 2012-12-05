#
#   TINET (TCP/IP Protocol Stack)
#  
#   Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
#                    Tomakomai National College of Technology, JAPAN
# 
#   上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
#   によって公表されている GNU General Public License の Version 2 に記
#   述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
#   を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
#   利用と呼ぶ）することを無償で許諾する．
#   (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#       権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#       スコード中に含まれていること．
#   (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#       用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#       者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#       の無保証規定を掲載すること．
#   (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#       用できない形で再配布する場合には，次の条件を満たすこと．
#     (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#         作権表示，この利用条件および下記の無保証規定を掲載すること．
#   (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#       害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
# 
#   本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#   よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
#   含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
#   接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
#  
#   @(#) $Id: Makefile,v 1.5 2009/12/24 05:39:31 abe Exp abe $
# 

#
#  コマンド名，コンパイルオプションの定義
#
CC       = g++
CFLAGS   = -O2 -Wall
INCLUDE  = -I. -I$(JSPCFGDIR)

#
#  オブジェクトファイル名，ヘッダファイル名の定義
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
