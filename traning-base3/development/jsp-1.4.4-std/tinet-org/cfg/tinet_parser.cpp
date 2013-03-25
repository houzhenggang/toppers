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
//  @(#) $Id: tinet_parser.cpp,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#include <stdarg.h>

#include "base/parser.h"
#include "base/mpstrstream.h"

#include "tinet_defs.h"
#include "tinet_classes.h"

#include <sstream>
#include <set>
#include <map>
#include <iomanip>

// 名前空間の指定

using namespace std;

//
// CoreParser -- 構文解析のコンストラクタ
//

CoreParser::CoreParser (void)
{
	setBanner("--- TCP/IP Protocol Stack Configurator ver 1.4 (for JSP rel 1.4) ---");
	}

//
// CoreParser::parseOption -- 構文解析のオプション解析
//

void
CoreParser::parseOption (Directory& container)
{
	ParserComponent::parseOption(container);	// 親クラスのオプションの解析

	if (findOption("h", "help")) {
		cerr << Message (
			"  -obj, --dump-object=filename : Dump the object tree into file specified\n"
			"  -ao, --assign-order=order    : Specify the order of automatic ID assignment\n"
			"    You can use three terms below as ordering rule.\n"
			"      alphabetic (in alphabetic order)\n"
			"      fcfs       (in arrival order [as default])\n"
			"      reverse    (reverse the order)\n",

			"  -obj, --dump-object=ファイル名 : 指定したファイルにオブジェクト情報を出力します\n"
			"  -ao, --assign-order=順序       : 自動 ID 割当の割当順序を指定します\n"
			"    aphabetic (ABC 順), fcfs (宣言順 [ディフォルト]), reverse (逆順)\n"
			);
		}
	}

//
// CoreParser::assignID -- 構文解析のオブジェクト ID の割り当て
//

enum tagAssignmentOrder {
	UNKNOWN,
	ALPHABETIC,
	FCFS,
	REVERSE = 0x80,
	REVERSE_ALPHABETIC,
	REVERSE_FCFS,
	};

int
CoreParser::assignID (Directory& container, const char *category)
{
	set<int>		idpool;
	map<int, Directory *>	sorter;
	map<int, Directory *>::iterator	entry;
	Directory		*node = NULL;
	Directory		*scope;
	Directory		*work;
	tagAssignmentOrder	order;
	int			id;

	// とりあえず、宣言順
	order = FCFS;

	// 指定された静的 API がなければ終了
	node = container.findChild(OBJECT_TREE, category, NULL);
	if (node == NULL)
		return 0;

	// 割り当て集合を初期設定する。
	for (id = 1; id < (signed int)node->size() + 32; id ++)
		idpool.insert(id);

	// 割り当て候補を決定し、割り当て済み ID を削除する。
	id = 0;
	scope = node->getFirstChild();
	while (scope != NULL) {

		// ID に整数が指定されているとき
		if (*scope == Directory::INTEGER)
			idpool.erase(*scope);
		else {
			// ID の重複をチェックする。
			work = container.openChild("/", "identifier", scope->getKey().c_str(), NULL);
			if (*work == Directory::INTEGER)  {
				VerboseMessage("Assigning the same ID (%) since the name (%[%]) is duplicated\n",
				               "ID 番号 (%) を異種同名のオブジェクト (%[%]) に割り当てます。\n")
				               << work->toInteger() << scope->getKey().c_str() <<category;
				idpool.erase(*scope = work->toInteger());
				}
			else {
				// 割り当て順序に従って、割り当て候補に追加する。
				switch (order) {
				case ALPHABETIC:
					sorter[id ++] = scope;
					break;
				case REVERSE_ALPHABETIC:
					sorter[id --] = scope;
					break;
				case REVERSE_FCFS:
					sorter[- scope->openChild("#order")->toInteger()] = scope;
					break;
				case FCFS:
				default:
					sorter[scope->openChild("#order")->toInteger()] = scope;
					break;
					}
				}
			}
		scope = scope->getNext();
		}

	// ID を割り当てる。
	entry = sorter.begin();
	while (entry != sorter.end()) {
		scope = (*entry).second;
		if (*scope != Directory::INTEGER) {
			id = *(idpool.begin());
			idpool.erase(idpool.begin());
			work = container.openChild("/","identifier", scope->getKey().c_str(), NULL);
			*work  = id;
			*scope = id;
			}
		entry ++;
		}

	// 割り当て表出力
	if (node->size() != 0 && VerboseMessage::getVerbose()) {
		VerboseMessage("Object ID assignment list [%s]\n",
		               "オブジェクト ID 割付表 [%]\n") << category;

		sorter.clear();
		scope = node->getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger()] = scope;
			scope = scope->getNext();
			}

		entry = sorter.begin();
		while (entry != sorter.end()) {
			VerboseMessage("  % : %\n") << setw(3) << (*entry).first << (*entry).second->getKey().c_str();
			entry ++;
			}
		}

	// 不連続 ID の検出
	if ((signed)node->size() + 1 != *(idpool.begin()))
		ExceptionMessage("Discontinuous %s ID assignment occured",
		                 "不連続なオブジェクト ID (%)") << category << throwException;

	return node->size();
	}

//
// CoreParser::parse -- 構文解析
//

bool
CoreParser::parse (Parser& parser, Directory& container)
{
	Token	token;
	bool	errorOccured;

	try {
		errorOccured = false;

		// 静的 API の構文解析
		do {
			parser.getToken(token);
			if (token == Token::IDENTIFIER) {
				try {
					this->parseStaticAPI(parser, container, token);
					}
				catch (...) {
					errorOccured = true;
					}
				}
			} while (token != Token::EOS);

		if (errorOccured)
			ExceptionMessage(ExceptionMessage::FATAL,
			                "The configuration process was aborted due to occurence of parse error",
			                "構文解析に失敗したため処理を中断します").throwException();

		// オブジェクト ID を割り当てる。
		assignID(container, TCP_REP);
		assignID(container, TCP_CEP);
		assignID(container, UDP_CEP);
		assignID(container, TCP6_REP);
		assignID(container, TCP6_CEP);
		assignID(container, UDP6_CEP);
		assignID(container, IPSEC_SET_UP_SPD);
		assignID(container, IPSEC_SET_UP_SAD);

		return true;
		}

	catch (Exception& e) {
		throw e;
		}
	}

//
// SpecialtyFile::SpecialtyFile -- constructor
//

SpecialtyFile::SpecialtyFile (void) throw() : MultipartStream(), RuntimeObject(true)
{
	}

//
// getFileName -- ファイル名の生成
//

string getFileName (string category, string def_cat) throw(Exception)
{
	string result(def_cat);
	OptionParameter::OptionItem item = getOptionParameter()[category];

	if (item.isValid()) {
		if (item.countParameter() == 1)
			result = item[0];
		else
			ExceptionMessage("-% should have just ONE filename.",
			                 "-%オプションに指定できるファイルは 1 つのみ")
				<< category << throwException;
		}

	if (result.empty())
		ExceptionMessage("-% has illegal filename.",
		                 "-%オプションに渡されたファイル名は不正")
			<< category << throwException;

	return result;
	}

//
// createTinetCfg -- tinet_cfg.c ファイルの生成
//

TinetCfg*
createTinetCfg (void)
{
	TinetCfg*		cfg = NULL;
	TinetCfg::CreationEvent	event;

	cfg = TinetCfg::createInstance(getFileName("tinet_cfg", "tinet_cfg.c"));
	cfg->disableOutput();

	// オブジェクトの格納場所の設定
	cfg->createPart("header")
	    .createPart("include")
	    .createPart("define")
	    .createPart(TCP_REP)
	    .createPart(TCP_CEP)
	    .createPart(UDP_CEP)
	    .createPart(TCP6_REP)
	    .createPart(TCP6_CEP)
	    .createPart(UDP6_CEP)
	    .createPart(IPSEC_SET_UP_SPD)
	    .createPart(IPSEC_SET_UP_SAD);

	// ファイル生成イベントの実行
	event.file = cfg;
	Event<TinetCfg::CreationEvent>::raise(event);


	// エラーのチェック
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "内部エラー: tinet_cfg のハンドラがインスタンスを削除した") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetCfg)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "内部エラー: tinet_cfg のハンドラが不正なインスタンスを生成した") << throwException;

	return event.file;
	}

//
// createIPsecConfig -- ipsec_config.h ファイルの生成
//
IPsecConfig*
createIPsecConfig (void)
{
	IPsecConfig*		cfg = NULL;
	IPsecConfig::CreationEvent	event;

	cfg = IPsecConfig::createInstance(getFileName("ipsec_config", "ipsec_config.h"));
	cfg->disableOutput();

	// オブジェクトの格納場所の設定
	cfg->createPart("header")
	    .createPart("include")
	    .createPart("define")
	    .createPart(TCP_REP)
	    .createPart(TCP_CEP)
	    .createPart(UDP_CEP)
	    .createPart(TCP6_REP)
	    .createPart(TCP6_CEP)
	    .createPart(UDP6_CEP)
	    .createPart(IPSEC_SET_UP_SPD)
	    .createPart(IPSEC_SET_UP_SAD);

	// ファイル生成イベントの実行
	event.file = cfg;
	Event<IPsecConfig::CreationEvent>::raise(event);


	// エラーのチェック
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "内部エラー: ipsec_config のハンドラがインスタンスを削除した") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(IPsecConfig)) != event.file)
		ExceptionMessage("Internal error: ipsec_config event handler create the illegal instance.",
		                 "内部エラー: ipsec_config のハンドラが不正なインスタンスを生成した") << throwException;

	return event.file;
	}

//
// createTinetKern -- tinet_kern.cfg ファイルの生成
//

TinetKernCfg*
createTinetKernCfg (void)
{
	TinetKernCfg*			kern = NULL;
	TinetKernCfg::CreationEvent	event;

	kern = TinetKernCfg::createInstance(getFileName("tinet_kern_cfg", "tinet_kern.cfg"));
	kern->disableOutput();

	// オブジェクトの格納場所の設定
	kern->createPart("header")
	     .createPart(TCP_REP)
	     .createPart(TCP_CEP)
	     .createPart(UDP_CEP)
	     .createPart(TCP6_REP)
	     .createPart(TCP6_CEP)
	     .createPart(UDP6_CEP)
	     .createPart(IPSEC_SET_UP_SPD)
	     .createPart(IPSEC_SET_UP_SAD);

	// ファイル生成イベントの実行
	event.file = kern;
	Event<TinetKernCfg::CreationEvent>::raise(event);

	// エラーのチェック
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "内部エラー: tinet_cfg のハンドラがインスタンスを削除した") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetKernCfg)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "内部エラー: tinet_cfg のハンドラが不正なインスタンスを生成した") << throwException;

	return event.file;
	}

//
// createTinetID -- tinet_id.h ファイルの生成
//

TinetID*
createTinetID (void)
{
	TinetID*		id = NULL;
	TinetID::CreationEvent	event;

	id = TinetID::createInstance(getFileName("tinet_id", "tinet_id.h"));
	id->disableOutput();

	// オブジェクトの格納場所の設定
	id->createPart("header")
	   .createPart("body")
	   .createPart("footer");

	// ファイル生成イベントの実行
	event.file = id;
	Event<TinetID::CreationEvent>::raise(event);

	// エラーのチェック
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "内部エラー: tinet_cfg のハンドラがインスタンスを削除した") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetID)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "内部エラー: tinet_cfg のハンドラが不正なインスタンスを生成した") << throwException;

	// 多重インクルード回避用定義の設定
	id->movePart("header");
	(*id) << "#ifndef _TINET_ID_H_\n#define _TINET_ID_H_\n\n";

	id->movePart("footer");
	(*id) << "\n#endif\t/* of _TINET_ID_H_*/\n";

	return event.file;
	}

//
// ConfigurationFileGenerator::parseOption -- ファイル生成のオプション解析
//

void
ConfigurationFileGenerator::parseOption (Directory& parameter)
{
	string		name;

	if (findOption("h", "help")) {
		cerr << endl << Message (
			"TINET configuration file generator\n"
			"  -id,  --tinet_id      =filename : Specify the name of ID assignment file\n"
			"  -cfg, --tinet_cfg     =filename : Specify the name of TINET configuration file\n"
			"  -kern,--tinet_kern_cfg=filename : Specify the name of TINET kernel configuration file\n"
			"  -z,   --nonzero                 : Do not output __EMPTY_LABEL macro and related definitions\n",

			"TINET 構成ファイルの生成\n"
			"  -id,  --tinet_id      =ファイル名 : ID 割当ファイルの名前を指定します。\n"
			"  -cfg, --tinet_cfg     =ファイル名 : TINET 構成ファイルの名前を指定します。\n"
			"  -kern,--tinet_kern_cfg=ファイル名 : TINET カーネル構成ファイルの名前を指定します。\n"
			"  -z,   --nonzero                   : __EMPTY_LABEL マクロの使用を制限します。\n");
		return;
		}

	// ID 割当ファイル (tinet_id.h) の初期設定

	createTinetID();

	// TINET 構成ファイル (tinet_cfg.c) の初期設定

	createTinetCfg();

	// TINET カーネル構成ファイル (tinet_kern.cfg) の初期設定
	//
	//   受付口、通信端点内で使用するカーネルオブジェクトを出力する。
	//

	createTinetKernCfg();

	// IPsec 固有ファイル (ipsec_config.h) の初期設定

	if (findOption("-ipsec")) {
		createIPsecConfig();
	}

	activateComponent();
	}

//
// ConfigurationFileGenerator::onFatalExit -- 異常終了時の処理
//

void
ConfigurationFileGenerator::onFatalExit (Directory& container)
{
	// 例外により異常終了したときの処理、ファイルを生成しない。
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetCfg)))->disableOutput();
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetID)))->disableOutput();
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetKernCfg)))->disableOutput();
	}

//
// ConfigurationFileGenerator::outTinet_id_h -- ID 割当ファイル (tinet_id.h) を出力する。
//

void
ConfigurationFileGenerator::outTinet_id_h (Directory& container)
{
	TinetID*	out = NULL;
	Directory*	scope;

	out = dynamic_cast<TinetID *>(RuntimeObjectTable::getInstance(typeid(TinetID)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_id.h disappeared.",
		                 "内部エラー: tinet_id.h 用のファイルストリームが開けません") << throwException;
		return;
		}

	out->movePart("body");
	scope = Singleton<Directory>::getInstance()->findChild("/identifier")->getFirstChild();
	while (scope != NULL) {
		(*out) << "#define "
		       << scope->getKey() << "\t" << scope->toInteger() << "\n";
		scope = scope->getNext();
		}

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::outCfgTCP_CRE_REP --  TCP 受付口の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgTCP_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(TCP_REP);

		// TCP 受付口数を出力する。
		(*out) << "#define TNUM_TCP_REPID\t" << container.size() << "\n\n";

		// TCP 受付口の最大 ID を出力する。
		(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の TCP/IPv4 受付口を出力する。
		(*out) << "T_TCP4_REP tcp_rep[TNUM_TCP_REPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t0,\n";
				(*out) << "\t\t{ IPV4_ADDRANY, TCP_PORTANY },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_DYNAMIC,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"   << (*(*psorter).second)["repatr"].toString() << ",\n";
				(*out) << "\t\t{ " << (*(*psorter).second)["myipaddr"].toString() << ", "
				                   << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_VALID,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}

			(*out) << "\t\t},\n";
			psorter ++;
			count ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgTCP_CRE_CEP --  TCP 通信端点の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgTCP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(TCP_CEP);

		// TCP 通信端点数を出力する。
		(*out) << "#define TNUM_TCP_CEPID\t" << container.size() << "\n\n";

		// TCP 通信端点の最大 ID を出力する。
		(*out) << "const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の TCP/IPv4 通信端点を出力する。
		(*out) << "T_TCP4_CEP tcp_cep[TNUM_TCP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(t_tcp_callback)NULL,\n";
				(*out) << "\t\tTCP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"        << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["sbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["sbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["rbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["rbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(t_tcp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tTCP_CEP_FLG_VALID,\n";
				}

			// 実装依存の定義
			(*out) << "\t\tSEM_TCP_CEP_LOCK"	<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_EST"		<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_SND"		<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_RCV"		<< count ++	<< ",\n";

			(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgUDP_CRE_CEP --  UDP 通信端点の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgUDP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(UDP_CEP);

		// UDP 通信端点数を出力する。
		(*out) << "#define TNUM_UDP_CEPID\t" << container.size() << "\n\n";

		// UDP 通信端点の最大 ID を出力する。
		(*out) << "const ID tmax_udp_cepid = (TMIN_UDP_CEPID + TNUM_UDP_CEPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の UDP/IPv4 通信端点を出力する。
		(*out) << "T_UDP4_CEP udp_cep[TNUM_UDP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON UDP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t"     << "0,\n";
				(*out) << "\t\t{ "   << "IPV4_ADDRANY, "
				                     << "UDP_PORTANY },\n";
				(*out) << "\t\t(t_udp_callback)" << "NULL,\n";
				(*out) << "\t\tUDP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"     << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t{ "   << (*(*psorter).second)["myipaddr"].toString() << ", "
				                     << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "\t\t(t_udp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tUDP_CEP_FLG_VALID,\n";
				}

			// 実装依存の定義
			(*out) << "\t\tSEM_UDP_CEP_LOCK" << count    << ",\n";
			(*out) << "\t\tTA_NULL,\n";
			(*out) << "\t\tTA_NULL,\n";
			(*out) << "\t\tDTQ_UDP_RCVQ"     << count ++ << ",\n";

			(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgTCP6_CRE_REP --  TCP/IPv6 受付口の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgTCP6_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(TCP6_REP);

		// TCP/IPv6 受付口数を出力する。
		(*out) << "#define TNUM_TCP_REPID\t" << container.size() << "\n\n";

		// TCP/IPv6 受付口の最大 ID を出力する。
		(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の TCP/IPv6 受付口を出力する。
		(*out) << "T_TCP6_REP tcp_rep[TNUM_TCP_REPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t0,\n";
				(*out) << "\t\t{ IPV6_ADDRANY, TCP_PORTANY },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_DYNAMIC,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"   << (*(*psorter).second)["repatr"  ].toString() << ",\n";
				(*out) << "\t\t{ " << (*(*psorter).second)["myipaddr"].toString() << ", "
				                   << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_VALID,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}

			(*out) << "\t\t},\n";
			psorter ++;
			count ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgTCP6_CRE_CEP --  TCP/IPv6 通信端点の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgTCP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(TCP6_CEP);

		// TCP/IPv6 通信端点数を出力する。
		(*out) << "#define TNUM_TCP_CEPID\t" << container.size() << "\n\n";

		// TCP/IPv6 通信端点の最大 ID を出力する。
		(*out) << "const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の TCP/IPv6 通信端点を出力する。
		(*out) << "T_TCP6_CEP tcp_cep[TNUM_TCP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(t_tcp_callback)NULL,\n";
				(*out) << "\t\tTCP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"        << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["sbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["sbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["rbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["rbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(t_tcp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tTCP_CEP_FLG_VALID,\n";
				}

			// 実装依存の定義
			(*out) << "\t\tSEM_TCP_CEP_LOCK"	<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_EST"		<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_SND"		<< count	<< ",\n";
			(*out) << "\t\tFLG_TCP_CEP_RCV"		<< count ++	<< ",\n";

			(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgUDP6_CRE_CEP --  UDP/IPv6 通信端点の定義を出力する。
//

void
ConfigurationFileGenerator::outCfgUDP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(UDP6_CEP);

		// UDP/IPv6 通信端点数を出力する。
		(*out) << "#define TNUM_UDP_CEPID\t" << container.size() << "\n\n";

		// UDP/IPv6 通信端点の最大 ID を出力する。
		(*out) << "const ID tmax_udp_cepid = (TMIN_UDP_CEPID + TNUM_UDP_CEPID - 1);\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET 内部使用の UDP/IPv6 通信端点を出力する。
		(*out) << "T_UDP6_CEP udp_cep[TNUM_UDP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON UDP/IP API 標準の定義
			if ((*psorter).second->findChild("_reserved") != 0) {
				// 予約 ID の場合
				(*out) << "\t\t"     << "0,\n";
				(*out) << "\t\t{ "   << "IPV6_ADDRANY, "
				                     << "UDP_PORTANY },\n";
				(*out) << "\t\t(t_udp_callback)" << "NULL,\n";
				(*out) << "\t\tUDP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// 通常の定義の場合
				(*out) << "\t\t"     << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t{ "   << (*(*psorter).second)["myipaddr"].toString() << ", "
				                     << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "\t\t(t_udp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tUDP_CEP_FLG_VALID,\n";
				}

			// 実装依存の定義
			(*out) << "\t\tSEM_UDP_CEP_LOCK" << count    << ",\n";
			(*out) << "\t\tTA_NULL,\n";
			(*out) << "\t\tTA_NULL,\n";
			(*out) << "\t\tDTQ_UDP_RCVQ"     << count ++ << ",\n";

			(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgEMPTY_TCP_CRE_REP --  TCP 受付口の EMPTY 定義を出力する。
//

void
ConfigurationFileGenerator::outCfgEMPTY_TCP_CRE_REP (MultipartStream* out)
{
	// #ifdef を出力する。
	(*out) << "#ifdef TCP_CFG_PASSIVE_OPEN\n\n";

	// TCP 受付口数（0）を出力する。
	(*out) << "#define TNUM_TCP_REPID\t0\n\n";

	// TCP 受付口の最大 ID を出力する。
	(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

	// TCP 受付口構造体の空ラベルを出力する。
	(*out) << "#if defined(SUPPORT_INET4)\n";
	(*out) << "T_TCP4_REP tcp_rep[1];\n";
	(*out) << "#endif\n\n";
	(*out) << "#if defined(SUPPORT_INET6)\n";
	(*out) << "T_TCP6_REP tcp_rep[1];\n";
	(*out) << "#endif\n\n";

	// #endif を出力する。
	(*out) << "#endif\t/* of ifdef TCP_CFG_PASSIVE_OPEN */\n\n";
	}

//
// ConfigurationFileGenerator::outCfgIPSEC_VSET_SPD --  SPDの定義を出力する。
//

void
ConfigurationFileGenerator::outCfgIPSEC_VSET_SPD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;

		out->movePart(IPSEC_SET_UP_SPD);

		// SPのルール数を出力する。
	//	(*out) << "#define IPSEC_TNUM_SPD\t" << container.size() << "\n\n";

		// SPの最大 ID を出力する。
		(*out) << "const ID tmax_ipsec_spd = (IPSEC_TMIN_IPSEC_SPD + IPSEC_TNUM_SPD - 1);\n\n";

		// SPを格納する配列 を出力する。
		(*out) << "T_SECPOLICY * spd_rules[IPSEC_TNUM_SPD];\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// 各 SP のルールを出力する。
		(*out) << "const T_SECPOLICY_INITB spd_rules_initb[IPSEC_TNUM_SPD] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// 
			(*out) << "\t\t{  " << (*(*psorter).second)["dir"        ].toString() << ",\n";
			(*out) << "\t\t\t{" << (*(*psorter).second)["srcipaddr"  ].toString() << ", ";
			(*out) << "\t"      << (*(*psorter).second)["srcportno"  ].toString() << " },\n";
			(*out) << "\t\t\t{" << (*(*psorter).second)["dstipaddr"  ].toString() << ", ";
			(*out) << "\t"      << (*(*psorter).second)["dstportno"  ].toString() << " },\n";
			(*out) << "\t\t"    << (*(*psorter).second)["prefs"      ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["prefd"      ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["proto"      ].toString() << " },\n";
			(*out) << "\t\t"    << (*(*psorter).second)["policy"     ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["ipproto"    ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["level"      ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["id"         ].toString() << " },\n";

			// 実装依存の定義
		//	(*out) << "\t\tSEM_TCP_CEP_LOCK"       << count    << ",\n";
		//	(*out) << "\t\tSEM_TCP_CEP_SBUF_BUSY"  << count    << ",\n";
		//	(*out) << "\t\tSEM_TCP_CEP_RBUF_READY" << count    << ",\n";
		//	(*out) << "\t\tFLG_TCP_CEP"            << count ++ << ",\n";

		//	(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outCfgIPSEC_VSET_SAD --  SADの定義を出力する。
//

void
ConfigurationFileGenerator::outCfgIPSEC_VSET_SAD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count, len;
		unsigned int		index;
		map<int, Directory*>		sorter;
		map<int, Directory*>::iterator	psorter;
		std::string key, keyconv;
		std::stringstream bufstream;
		std::stringstream keystream;

		out->movePart(IPSEC_SET_UP_SAD);

		// SAのルール数を出力する。
	//	(*out) << "#define IPSEC_TNUM_SAD\t" << container.size() << "\n\n";

		// SAの最大 ID を出力する。
		(*out) << "const ID tmax_ipsec_sad = (IPSEC_TMIN_IPSEC_SAD + IPSEC_TNUM_SAD - 1);\n\n";

		// SAの一覧を示す配列を確保する。
		(*out) << "T_SECAS_HEAD *sad_list[IPSEC_TNUM_SAD];\n\n";

		// ID 順にソートする。
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {

			key = (*(*psorter).second)["key_enc"  ].toString();
			len = key.length()-4;
			keystream.str("");	//keystreamをクリア
			bufstream.str("");	//bufstereamをクリア
			bufstream << count;
			if (key[0]=='"' and key[1]=='0' and key[2]=='x') {
				if (!((key.length()-4) == 256/4 || (key.length()-4) == 192/4 || (key.length()-4) == 128/4)){
					std::cout << "Key Length is not 128/192/256-bit. ("<< (key.length()-4)*4 << "-bit)->" << key << "\n";
				}

				keystream << "static uint8_t Key" + bufstream.str() + "[] = {";
				for(index = 3; index < (key.length()/2*2)-1; index+=2){
					keystream << "0x" << key[index]  << key[index+1] <<",";
				}
				keystream << "0x0};\n" ;

				(*out) << keystream.str();
				bufstream.str("");	//bufstereamをクリア
				bufstream << len*4;
				(*(*psorter).second)["key_enc"  ] = bufstream.str();

			} else {
				if (!(key.length() == 256/8 || key.length() == 192/8 || key.length() == 128/8)){
					std::cout << "Key Length is not 128/192/256-bit. ("<< key.length()*8 << "-bit)->" << key << "\n";
				}
				keyconv = key;
				len = key.length();

				(*out) << "static uint8_t Key" << bufstream.str() << "[] = {\"" << key << "\"};\n";
				bufstream.str("");	//bufstereamをクリア
				bufstream << len*8;
				(*(*psorter).second)["key_enc"  ] = bufstream.str();
			}

			count ++;
			psorter ++;
			}
		(*out) << "\n";

		// 各 SA のルールを出力する。
		(*out) << "const T_SECAS_INITB sad_rules_initb[IPSEC_TNUM_SAD] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// 
			(*out) << "\t\t"    << (*(*psorter).second)["srcipaddr"  ].toString() << ", ";
			(*out) << "\t"      << (*(*psorter).second)["dstipaddr"  ].toString() << " ,\n";
			(*out) << "\t\t"    << (*(*psorter).second)["ipproto"    ].toString() << ",";
			(*out) << "\t"      << (*(*psorter).second)["spi"        ].toString() << ",";
			(*out) << "\t"      << (*(*psorter).second)["reqid"      ].toString() << ",\n";
			(*out) << "\t\t"    << (*(*psorter).second)["alg_enc"    ].toString() << ",";
			(*out) << "\t"      << "(uint8_t*) Key" << count  << ",";
			(*out) << "\t"      << (*(*psorter).second)["key_enc"    ].toString() << " },\n";

			count ++;
		//	(*out) << "\t\t},\n";
			psorter ++;
			}
		(*out) << "\t};\n\n";
		}
	}

//
// ConfigurationFileGenerator::outTinet_cfg_c -- TINET 構成ファイル (tinet_cfg.c) を出力する。
//

void
ConfigurationFileGenerator::outTinet_cfg_c (Directory& container)
{
	Directory*	scope;
	TinetCfg*	out = NULL;

	out = dynamic_cast<TinetCfg *>(RuntimeObjectTable::getInstance(typeid(TinetCfg)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_cfg.c disappeared.",
		                 "内部エラー: tinet_cfg.c 用のファイルストリームが開けません") << throwException;
		return;
		}

	// 標準のインクルードファイルを出力する。
	out->movePart("header");
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_cfg.c disappeared.",
		                 "内部エラー: tinet_cfg.c 用のファイルストリームが開けません") << throwException;
		return;
		}

	(*out) << "#ifdef TARGET_KERNEL_ASP\n";
	(*out) << "#include <kernel.h>\n";
	(*out) << "#include \"kernel_cfg.h\"\n";
	(*out) << "#endif\n";
	(*out) << "#ifdef TARGET_KERNEL_JSP\n";
	(*out) << "#include <s_services.h>\n";
	(*out) << "#include <t_services.h>\n";
	(*out) << "#include \"kernel_id.h\"\n";
	if (findOption("-ipsec")) {
		(*out) << "#include \"ipsec_config.h\"\n";
	}
	(*out) << "#endif\n";

	// TINET ID 定義ファイル名を出力する。
	(*out) << "#include \"";
	(*out) << dynamic_cast<TinetID *>(RuntimeObjectTable::getInstance(typeid(TinetID)))->getFilename();
	(*out) << "\"\n";

	//
	(*out) << "#include <tinet_defs.h>\n";
	(*out) << "#include <tinet_config.h>\n";
	(*out) << "#include <net/if.h>\n";
	(*out) << "#include <net/if_ppp.h>\n";
	(*out) << "#include <net/if_loop.h>\n";
	(*out) << "#include <net/ethernet.h>\n";
	(*out) << "#include <net/net_buf.h>\n";
	(*out) << "#include <netinet/in.h>\n";
	(*out) << "#include <netinet/in_itron.h>\n";
	(*out) << "#include <netinet/ip.h>\n";
	(*out) << "#include <netinet/ip6.h>\n";
	(*out) << "#include <netinet/tcp.h>\n";
	(*out) << "#include <netinet/tcp_timer.h>\n";
	(*out) << "#include <netinet/tcp_var.h>\n";
	(*out) << "#include <netinet/tcp_fsm.h>\n";
	(*out) << "#include <netinet/udp_var.h>\n";
	if (findOption("-ipsec")) {
		(*out) << "#include <netinet6/ipsec.h>\n";
		(*out) << "#include <netinet6/esp.h>\n";
	}
	(*out) << "\n";

	// ユーザ定義のインクルードファイルを出力する。
	out->movePart(INCLUDE_FILE);
	scope = container(OBJECT_TREE "/" INCLUDE_FILE)->getFirstChild();
	while (scope != NULL) {
		(*out) << "#include " << scope->toString() << "\n";
		scope = scope->getNext();
		}
	(*out) << "\n";

	if (container[OBJECT_TREE "/" TCP_REP].size() > 0)
		outCfgTCP_CRE_REP(out, container[OBJECT_TREE "/" TCP_REP]);	// TCP 受付口の定義を出力する。
	else if (container[OBJECT_TREE "/" TCP6_REP].size() > 0)
		outCfgTCP6_CRE_REP(out, container[OBJECT_TREE "/" TCP6_REP]);	// TCP/IPv6 受付口の定義を出力する。
	else
		outCfgEMPTY_TCP_CRE_REP(out);						// TCP/IP 受付口の EMPTY 定義を出力する。

	outCfgTCP_CRE_CEP(out, container[OBJECT_TREE "/" TCP_CEP]);	// TCP 通信端点の定義を出力する。
	outCfgTCP6_CRE_CEP(out, container[OBJECT_TREE "/" TCP6_CEP]);	// TCP/IPv6 通信端点の定義を出力する。

	outCfgUDP_CRE_CEP(out, container[OBJECT_TREE "/" UDP_CEP]);	// UDP 通信端点の定義を出力する。
	outCfgUDP6_CRE_CEP(out, container[OBJECT_TREE "/" UDP6_CEP]);	// UDP/IPv6 通信端点の定義を出力する。

	if (findOption("-ipsec")) {
		outCfgIPSEC_VSET_SPD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SPD]);	// SPDの定義を出力する。
		outCfgIPSEC_VSET_SAD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SAD]);	// SADの定義を出力する。
	}

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::outKernCfgTCP_CRE_REP --  TCP 受付口に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgTCP_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP_REP);

		// 各 TCP 受付口に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_REP_LOCK" << count ++ << ",{ TA_TPRI, 1, 1 });\n";
			scope = scope->getNext();
			}
		(*out) << "#endif\n\n";
		}
	}

//
// ConfigurationFileGenerator::outKernCfgTCP_CRE_CEP --  TCP 通信端点に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgTCP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP_CEP);

		// 各 TCP 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_CEP_LOCK"	<< count	<< ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_EST"	<< count	<< ",{ TA_TFIFO|TA_WSGL, TCP_CEP_EVT_CLOSED });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_SND"	<< count	<< ",{ TA_TFIFO|TA_WSGL, TCP_CEP_EVT_SWBUF_READY });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_RCV"	<< count ++	<< ",{ TA_TFIFO|TA_WSGL, 0 });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outKernCfgUDP_CRE_CEP --  UDP 通信端点に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgUDP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(UDP_CEP);

		// 各 UDP 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_UDP_CEP_LOCK" << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_DTQ(DTQ_UDP_RCVQ"     << count ++ << ",{ TA_TFIFO, NUM_DTQ_UDP_RCVQ, NULL });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outKernCfgTCP6_CRE_REP --  TCP/IPv6 受付口に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgTCP6_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP6_REP);

		// 各 TCP/IPv6 受付口に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_REP_LOCK" << count ++ << ",{ TA_TPRI, 1, 1 });\n";
			scope = scope->getNext();
			}
		(*out) << "#endif\n\n";
		}
	}

//
// ConfigurationFileGenerator::outKernCfgTCP6_CRE_CEP --  TCP/IPv6 通信端点に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgTCP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP6_CEP);

		// 各 TCP/IPv6 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_CEP_LOCK"	<< count	<< ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_EST"	<< count	<< ",{ TA_TFIFO|TA_WSGL, TCP_CEP_EVT_CLOSED });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_SND"	<< count	<< ",{ TA_TFIFO|TA_WSGL, TCP_CEP_EVT_SWBUF_READY });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP_RCV"	<< count ++	<< ",{ TA_TFIFO|TA_WSGL, 0 });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outKernCfgUDP6_CRE_CEP --  UDP/IPv6 通信端点に使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgUDP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(UDP6_CEP);

		// 各 UDP/IPv6 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_UDP_CEP_LOCK" << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_DTQ(DTQ_UDP_RCVQ"     << count ++ << ",{ TA_TFIFO, NUM_DTQ_UDP_RCVQ, NULL });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outIPsec_config_h -- TINET 構成ファイル (ipsec_config.h) を出力する。
//

void
ConfigurationFileGenerator::outIPsec_config_h (Directory& container)
{
	IPsecConfig*	out;

	out = dynamic_cast<IPsecConfig *>(RuntimeObjectTable::getInstance(typeid(IPsecConfig)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of ipsec_config.h disappeared.",
		                 "内部エラー: ipsec_config.h 用のファイルストリームが開けません") << throwException;
		return;
		}

	(*out) << "/* ipsec_config.h */\n";

	if (container[OBJECT_TREE "/" IPSEC_SET_UP_SPD].size() > 0) {

		// SPのルール数を出力する。
		(*out) << "#define IPSEC_TNUM_SPD\t" << container[OBJECT_TREE "/" IPSEC_SET_UP_SPD].size() << "\n";
		}

	if (container[OBJECT_TREE "/" IPSEC_SET_UP_SAD].size() > 0) {

		// SAのルール数を出力する。
		(*out) << "#define IPSEC_TNUM_SAD\t" << container[OBJECT_TREE "/" IPSEC_SET_UP_SAD].size() << "\n";
		}

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SPD --  SPDに使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SPD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(IPSEC_SET_UP_SPD);

		// 各 TCP 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_CEP_LOCK"       << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_SEM(SEM_TCP_CEP_SBUF_BUSY"  << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_SEM(SEM_TCP_CEP_RBUF_READY" << count    << ",{ TA_TPRI, 0, 1 });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP"            << count ++ << ",{ TA_TFIFO|TA_WSGL, CEP_EVT_CLOSED });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SAD --  SADに使用するカーネルオブジェクトを出力する。
//

void
ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SAD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(IPSEC_SET_UP_SAD);

		// 各 TCP 通信端点に使用するカーネルオブジェクトを出力する。
		count = 1;
		scope = container.getFirstChild();
		while (scope != NULL) {
			(*out) << "CRE_SEM(SEM_TCP_CEP_LOCK"       << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_SEM(SEM_TCP_CEP_SBUF_BUSY"  << count    << ",{ TA_TPRI, 1, 1 });\n";
			(*out) << "CRE_SEM(SEM_TCP_CEP_RBUF_READY" << count    << ",{ TA_TPRI, 0, 1 });\n";
			(*out) << "CRE_FLG(FLG_TCP_CEP"            << count ++ << ",{ TA_TFIFO|TA_WSGL, CEP_EVT_CLOSED });\n\n";
			scope = scope->getNext();
			}
		}
	}

//
// ConfigurationFileGenerator::outTinet_kern_cfg -- TINET カーネル構成ファイル (tinet_kern.cfg) を出力する。
//

void
ConfigurationFileGenerator::outTinet_kern_cfg (Directory& container)
{
	TinetKernCfg*	out;

	out = dynamic_cast<TinetKernCfg *>(RuntimeObjectTable::getInstance(typeid(TinetKernCfg)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_kern.cfg disappeared.",
		                 "内部エラー: tinet_kern.cfg 用のファイルストリームが開けません") << throwException;
		return;
		}

	outKernCfgTCP_CRE_REP(out, container[OBJECT_TREE "/" TCP_REP]);		// TCP 受付口に使用するカーネルオブジェクトを出力する。
	outKernCfgTCP_CRE_CEP(out, container[OBJECT_TREE "/" TCP_CEP]);		// TCP 通信端点に使用するカーネルオブジェクトを出力する。
	outKernCfgUDP_CRE_CEP(out, container[OBJECT_TREE "/" UDP_CEP]);		// UDP 通信端点に使用するカーネルオブジェクトを出力する。
	outKernCfgTCP6_CRE_REP(out, container[OBJECT_TREE "/" TCP6_REP]);	// TCP 受付口に使用するカーネルオブジェクトを出力する。
	outKernCfgTCP6_CRE_CEP(out, container[OBJECT_TREE "/" TCP6_CEP]);	// TCP 通信端点に使用するカーネルオブジェクトを出力する。
	outKernCfgUDP6_CRE_CEP(out, container[OBJECT_TREE "/" UDP6_CEP]);	// UDP 通信端点に使用するカーネルオブジェクトを出力する。
//	outKernCfgIPSEC_VSET_SPD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SPD]);		// SP生成に使用するカーネルオブジェクトを出力する。
//	outKernCfgIPSEC_VSET_SAD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SAD]);		// SA生成に使用するカーネルオブジェクトを出力する。

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::body -- ファイル生成の本体 
//

void
ConfigurationFileGenerator::body (Directory& container)
{
	outTinet_id_h(container);	// tinet_id.h     を出力する。
	outTinet_cfg_c(container);	// tinet_cfg.c    を出力する。
	outTinet_kern_cfg(container);	// tinet_kern.cfg を出力する。
	if (findOption("-ipsec")) {
		outIPsec_config_h(container);	// ipsec_config.h    を出力する。
	}
	}
