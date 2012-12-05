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
//  @(#) $Id: tinet_staticapi.cpp,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#include "base/parser.h"

#include "tinet_defs.h"

#include <iostream>

// 名前空間の指定

using namespace std;

//
// include API
//

DECLARE_API (INCLUDE, "INCLUDE")
{
	Token		token;
	Directory*	node;
	Directory*	scope;

	last = NULL;
	p.getToken(token, Token::STRINGLITERAL);
	token.chopLiteral();

	if ((token[0] != '\"' || token[token.size() - 1] != '\"') &&
	    (token[0] != '<'  || token[token.size() - 1] != '>' ))
		ExceptionMessage("An include filename must be enclosed with \"...\" or <...>",
		                 "ファイル名は \"...\" か <...> の形でなければなりません").throwException();

	node = container.openChild(OBJECT_TREE, INCLUDE_FILE, NULL);
	last = node;

	// 重複をチェックする。
	scope = node->getFirstChild();
	while (scope != 0) {
		if (token.compare(scope->toString()) == 0) {
			cerr << p.getStreamLocation() << ' ' 
			     << (Message("Include file % was already specified (ignored).",
			                 "インクルードファイル %s が複数回指定されました (無視します)") << token.c_str()) << endl;
			return;
			}
		scope = scope->getNext();
		}

	node->addChild(new Directory(token));
	}

//
// TCP_CRE_REP -- TCP 受付口の生成
//

DECLARE_API (TCP_CRE_REP, "TCP_CRE_REP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP_REP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "repatr");
	p.getToken(",", "{", NULL);
	parseParameters(p, node, "myipaddr,myportno");
	p.getToken("}", "}", NULL);
	}

//
// VRID_TCP_REP -- TCP 受付口 ID の予約
//

DECLARE_API (VRID_TCP_REP, "VRID_TCP_REP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP_REP);
	(*node)["position"] = p.getStreamLocation();
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, TCP_REP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// TCP_CRE_CEP -- TCP 通信端点の生成
//

DECLARE_API (TCP_CRE_CEP, "TCP_CRE_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP_CEP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "cepatr,sbuf,sbufsz,rbuf,rbufsz,callback");
	p.getToken("}");
	}

//
// VRID_TCP_CEP -- TCP 通信端点 ID の予約
//

DECLARE_API (VRID_TCP_CEP, "VRID_TCP_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP_CEP);
	(*node)["position"] = p.getStreamLocation();
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, TCP_CEP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// UDP_CRE_CEP -- UDP 通信端点の生成
//

DECLARE_API (UDP_CRE_CEP, "UDP_CRE_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, UDP_CEP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "cepatr");
	p.getToken(",", "{", NULL);
	parseParameters(p, node, "myipaddr,myportno");
	p.getToken("}", ",", NULL);
	parseParameters(p, node, "callback");
	p.getToken("}", NULL);
	}

//
// VRID_UDP_CEP -- UDP 通信端点 ID の予約
//

DECLARE_API (VRID_UDP_CEP, "VRID_UDP_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, UDP_CEP);
	(*node)["position"] = p.getStreamLocation();
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, UDP_CEP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// TCP6_CRE_REP -- TCP/IPv6 受付口の生成
//

DECLARE_API (TCP6_CRE_REP, "TCP6_CRE_REP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP6_REP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "repatr");
	p.getToken(",", "{", NULL);
	parseParameters(p, node, "myipaddr,myportno");
	p.getToken("}", "}", NULL);
	}

//
// VRID_TCP6_REP -- TCP/IPv6 受付口 ID の予約
//

DECLARE_API (VRID_TCP6_REP, "VRID_TCP6_REP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP6_REP);
	(*node)["position"] = p.getStreamLocation();
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, TCP6_REP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// TCP6_CRE_CEP -- TCP/IPv6 通信端点の生成
//

DECLARE_API (TCP6_CRE_CEP, "TCP6_CRE_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP6_CEP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "cepatr,sbuf,sbufsz,rbuf,rbufsz,callback");
	p.getToken("}");
	}

//
// VRID_TCP6_CEP -- TCP/IPv6 通信端点 ID の予約
//

DECLARE_API (VRID_TCP6_CEP, "VRID_TCP6_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, TCP6_CEP);
	(*node)["position"] = p.getStreamLocation();
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, TCP6_CEP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// UDP6_CRE_CEP -- UDP/IPv6 通信端点の生成
//

DECLARE_API (UDP6_CRE_CEP, "UDP6_CRE_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, UDP6_CEP);
	(*node)["position"] = p.getStreamLocation();

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "cepatr");
	p.getToken(",", "{", NULL);
	parseParameters(p, node, "myipaddr,myportno");
	p.getToken("}", ",", NULL);
	parseParameters(p, node, "callback");
	p.getToken("}", NULL);
	}

//
// VRID_UDP6_CEP -- UDP/IPv6 通信端点 ID の予約
//

DECLARE_API (VRID_UDP6_CEP, "VRID_UDP6_CEP")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, UDP6_CEP);
	(*node)["_reserved"] = 1;

	node = allocate(container[RESERVED_ID], token, UDP6_CEP);
	(*node)["position"] = p.getStreamLocation();
	}

//
// IPSEC_VSET_SPD -- セキュリティポリシーのセット
//

DECLARE_API (IPSEC_VSET_SPD, "IPSEC_VSET_SPD")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, IPSEC_SET_UP_SPD);
	(*node)["position"] = p.getStreamLocation();

//	p.getToken(",", "{", NULL);
//	parseParameters(p, node, "dir,srcipaddr,srcportno,dstipaddr,dstportno,policy");
//	p.getToken("}");

	p.getToken(",", "{", "{", NULL);
	parseParameters(p, node, "dir");
	p.getToken(",", "{", NULL);
	parseParameters(p, node, "srcipaddr,srcportno");
	p.getToken("}", ",", "{", NULL);
	parseParameters(p, node, "dstipaddr,dstportno");
	p.getToken("}", ",", NULL);
	parseParameters(p, node, "prefs,prefd,proto");
	p.getToken("}", ",", NULL);
	parseParameters(p, node, "policy,ipproto,level,id");
	p.getToken("}", NULL);

	}

//
// IPSEC_VSET_SAD -- セキュリティアソシエーションのセット
//

DECLARE_API (IPSEC_VSET_SAD, "IPSEC_VSET_SAD")
{
	Token		token;
	Directory*	node;

	p.getToken(token);
	node = allocate(container[OBJECT_TREE], token, IPSEC_SET_UP_SAD);
	(*node)["position"] = p.getStreamLocation();

//	p.getToken(",", "{", NULL);
//	parseParameters(p, node, "dir,srcipaddr,srcportno,dstipaddr,dstportno,policy");
//	p.getToken("}");

	p.getToken(",", "{", NULL);
	parseParameters(p, node, "srcipaddr,dstipaddr");
	p.getToken(",", NULL);
	parseParameters(p, node, "ipproto,spi,reqid,alg_enc");
	p.getToken(",", NULL);
	parseParameters(p, node, "key_enc");
	p.getToken("}", NULL);

	}
