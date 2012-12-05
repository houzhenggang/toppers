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
//  @(#) $Id: tinet_staticapi.cpp,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#include "base/parser.h"

#include "tinet_defs.h"

#include <iostream>

// ̾�����֤λ���

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
		                 "�ե�����̾�� \"...\" �� <...> �η��Ǥʤ���Фʤ�ޤ���").throwException();

	node = container.openChild(OBJECT_TREE, INCLUDE_FILE, NULL);
	last = node;

	// ��ʣ������å����롣
	scope = node->getFirstChild();
	while (scope != 0) {
		if (token.compare(scope->toString()) == 0) {
			cerr << p.getStreamLocation() << ' ' 
			     << (Message("Include file % was already specified (ignored).",
			                 "���󥯥롼�ɥե����� %s ��ʣ������ꤵ��ޤ��� (̵�뤷�ޤ�)") << token.c_str()) << endl;
			return;
			}
		scope = scope->getNext();
		}

	node->addChild(new Directory(token));
	}

//
// TCP_CRE_REP -- TCP ���ո�������
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
// VRID_TCP_REP -- TCP ���ո� ID ��ͽ��
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
// TCP_CRE_CEP -- TCP �̿�ü��������
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
// VRID_TCP_CEP -- TCP �̿�ü�� ID ��ͽ��
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
// UDP_CRE_CEP -- UDP �̿�ü��������
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
// VRID_UDP_CEP -- UDP �̿�ü�� ID ��ͽ��
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
// TCP6_CRE_REP -- TCP/IPv6 ���ո�������
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
// VRID_TCP6_REP -- TCP/IPv6 ���ո� ID ��ͽ��
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
// TCP6_CRE_CEP -- TCP/IPv6 �̿�ü��������
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
// VRID_TCP6_CEP -- TCP/IPv6 �̿�ü�� ID ��ͽ��
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
// UDP6_CRE_CEP -- UDP/IPv6 �̿�ü��������
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
// VRID_UDP6_CEP -- UDP/IPv6 �̿�ü�� ID ��ͽ��
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
// IPSEC_VSET_SPD -- �������ƥ��ݥꥷ���Υ��å�
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
// IPSEC_VSET_SAD -- �������ƥ����������������Υ��å�
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
