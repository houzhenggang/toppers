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

// ̾�����֤λ���

using namespace std;

//
// CoreParser -- ��ʸ���ϤΥ��󥹥ȥ饯��
//

CoreParser::CoreParser (void)
{
	setBanner("--- TCP/IP Protocol Stack Configurator ver 1.4 (for JSP rel 1.4) ---");
	}

//
// CoreParser::parseOption -- ��ʸ���ϤΥ��ץ�������
//

void
CoreParser::parseOption (Directory& container)
{
	ParserComponent::parseOption(container);	// �ƥ��饹�Υ��ץ����β���

	if (findOption("h", "help")) {
		cerr << Message (
			"  -obj, --dump-object=filename : Dump the object tree into file specified\n"
			"  -ao, --assign-order=order    : Specify the order of automatic ID assignment\n"
			"    You can use three terms below as ordering rule.\n"
			"      alphabetic (in alphabetic order)\n"
			"      fcfs       (in arrival order [as default])\n"
			"      reverse    (reverse the order)\n",

			"  -obj, --dump-object=�ե�����̾ : ���ꤷ���ե�����˥��֥������Ⱦ������Ϥ��ޤ�\n"
			"  -ao, --assign-order=���       : ��ư ID �����γ����������ꤷ�ޤ�\n"
			"    aphabetic (ABC ��), fcfs (����� [�ǥ��ե����]), reverse (�ս�)\n"
			);
		}
	}

//
// CoreParser::assignID -- ��ʸ���ϤΥ��֥������� ID �γ������
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

	// �Ȥꤢ�����������
	order = FCFS;

	// ���ꤵ�줿��Ū API ���ʤ���н�λ
	node = container.findChild(OBJECT_TREE, category, NULL);
	if (node == NULL)
		return 0;

	// ������ƽ���������ꤹ�롣
	for (id = 1; id < (signed int)node->size() + 32; id ++)
		idpool.insert(id);

	// ������Ƹ������ꤷ��������ƺѤ� ID �������롣
	id = 0;
	scope = node->getFirstChild();
	while (scope != NULL) {

		// ID �����������ꤵ��Ƥ���Ȥ�
		if (*scope == Directory::INTEGER)
			idpool.erase(*scope);
		else {
			// ID �ν�ʣ������å����롣
			work = container.openChild("/", "identifier", scope->getKey().c_str(), NULL);
			if (*work == Directory::INTEGER)  {
				VerboseMessage("Assigning the same ID (%) since the name (%[%]) is duplicated\n",
				               "ID �ֹ� (%) ��ۼ�Ʊ̾�Υ��֥������� (%[%]) �˳�����Ƥޤ���\n")
				               << work->toInteger() << scope->getKey().c_str() <<category;
				idpool.erase(*scope = work->toInteger());
				}
			else {
				// ������ƽ���˽��äơ�������Ƹ�����ɲä��롣
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

	// ID �������Ƥ롣
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

	// �������ɽ����
	if (node->size() != 0 && VerboseMessage::getVerbose()) {
		VerboseMessage("Object ID assignment list [%s]\n",
		               "���֥������� ID ����ɽ [%]\n") << category;

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

	// ��Ϣ³ ID �θ���
	if ((signed)node->size() + 1 != *(idpool.begin()))
		ExceptionMessage("Discontinuous %s ID assignment occured",
		                 "��Ϣ³�ʥ��֥������� ID (%)") << category << throwException;

	return node->size();
	}

//
// CoreParser::parse -- ��ʸ����
//

bool
CoreParser::parse (Parser& parser, Directory& container)
{
	Token	token;
	bool	errorOccured;

	try {
		errorOccured = false;

		// ��Ū API �ι�ʸ����
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
			                "��ʸ���Ϥ˼��Ԥ���������������Ǥ��ޤ�").throwException();

		// ���֥������� ID �������Ƥ롣
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
// getFileName -- �ե�����̾������
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
			                 "-%���ץ����˻���Ǥ���ե������ 1 �ĤΤ�")
				<< category << throwException;
		}

	if (result.empty())
		ExceptionMessage("-% has illegal filename.",
		                 "-%���ץ������Ϥ��줿�ե�����̾������")
			<< category << throwException;

	return result;
	}

//
// createTinetCfg -- tinet_cfg.c �ե����������
//

TinetCfg*
createTinetCfg (void)
{
	TinetCfg*		cfg = NULL;
	TinetCfg::CreationEvent	event;

	cfg = TinetCfg::createInstance(getFileName("tinet_cfg", "tinet_cfg.c"));
	cfg->disableOutput();

	// ���֥������Ȥγ�Ǽ��������
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

	// �ե������������٥�Ȥμ¹�
	event.file = cfg;
	Event<TinetCfg::CreationEvent>::raise(event);


	// ���顼�Υ����å�
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetCfg)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

	return event.file;
	}

//
// createIPsecConfig -- ipsec_config.h �ե����������
//
IPsecConfig*
createIPsecConfig (void)
{
	IPsecConfig*		cfg = NULL;
	IPsecConfig::CreationEvent	event;

	cfg = IPsecConfig::createInstance(getFileName("ipsec_config", "ipsec_config.h"));
	cfg->disableOutput();

	// ���֥������Ȥγ�Ǽ��������
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

	// �ե������������٥�Ȥμ¹�
	event.file = cfg;
	Event<IPsecConfig::CreationEvent>::raise(event);


	// ���顼�Υ����å�
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "�������顼: ipsec_config �Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(IPsecConfig)) != event.file)
		ExceptionMessage("Internal error: ipsec_config event handler create the illegal instance.",
		                 "�������顼: ipsec_config �Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

	return event.file;
	}

//
// createTinetKern -- tinet_kern.cfg �ե����������
//

TinetKernCfg*
createTinetKernCfg (void)
{
	TinetKernCfg*			kern = NULL;
	TinetKernCfg::CreationEvent	event;

	kern = TinetKernCfg::createInstance(getFileName("tinet_kern_cfg", "tinet_kern.cfg"));
	kern->disableOutput();

	// ���֥������Ȥγ�Ǽ��������
	kern->createPart("header")
	     .createPart(TCP_REP)
	     .createPart(TCP_CEP)
	     .createPart(UDP_CEP)
	     .createPart(TCP6_REP)
	     .createPart(TCP6_CEP)
	     .createPart(UDP6_CEP)
	     .createPart(IPSEC_SET_UP_SPD)
	     .createPart(IPSEC_SET_UP_SAD);

	// �ե������������٥�Ȥμ¹�
	event.file = kern;
	Event<TinetKernCfg::CreationEvent>::raise(event);

	// ���顼�Υ����å�
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetKernCfg)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

	return event.file;
	}

//
// createTinetID -- tinet_id.h �ե����������
//

TinetID*
createTinetID (void)
{
	TinetID*		id = NULL;
	TinetID::CreationEvent	event;

	id = TinetID::createInstance(getFileName("tinet_id", "tinet_id.h"));
	id->disableOutput();

	// ���֥������Ȥγ�Ǽ��������
	id->createPart("header")
	   .createPart("body")
	   .createPart("footer");

	// �ե������������٥�Ȥμ¹�
	event.file = id;
	Event<TinetID::CreationEvent>::raise(event);

	// ���顼�Υ����å�
	if (event.file == 0)
		ExceptionMessage("Internal error: tinet_cfg event handler eliminates the instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;

	if (RuntimeObjectTable::getInstance(typeid(TinetID)) != event.file)
		ExceptionMessage("Internal error: tinet_cfg event handler create the illegal instance.",
		                 "�������顼: tinet_cfg �Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

	// ¿�ť��󥯥롼�ɲ��������������
	id->movePart("header");
	(*id) << "#ifndef _TINET_ID_H_\n#define _TINET_ID_H_\n\n";

	id->movePart("footer");
	(*id) << "\n#endif\t/* of _TINET_ID_H_*/\n";

	return event.file;
	}

//
// ConfigurationFileGenerator::parseOption -- �ե����������Υ��ץ�������
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

			"TINET �����ե����������\n"
			"  -id,  --tinet_id      =�ե�����̾ : ID �����ե������̾������ꤷ�ޤ���\n"
			"  -cfg, --tinet_cfg     =�ե�����̾ : TINET �����ե������̾������ꤷ�ޤ���\n"
			"  -kern,--tinet_kern_cfg=�ե�����̾ : TINET �����ͥ빽���ե������̾������ꤷ�ޤ���\n"
			"  -z,   --nonzero                   : __EMPTY_LABEL �ޥ���λ��Ѥ����¤��ޤ���\n");
		return;
		}

	// ID �����ե����� (tinet_id.h) �ν������

	createTinetID();

	// TINET �����ե����� (tinet_cfg.c) �ν������

	createTinetCfg();

	// TINET �����ͥ빽���ե����� (tinet_kern.cfg) �ν������
	//
	//   ���ո����̿�ü����ǻ��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	//

	createTinetKernCfg();

	// IPsec ��ͭ�ե����� (ipsec_config.h) �ν������

	if (findOption("-ipsec")) {
		createIPsecConfig();
	}

	activateComponent();
	}

//
// ConfigurationFileGenerator::onFatalExit -- �۾ｪλ���ν���
//

void
ConfigurationFileGenerator::onFatalExit (Directory& container)
{
	// �㳰�ˤ��۾ｪλ�����Ȥ��ν������ե�������������ʤ���
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetCfg)))->disableOutput();
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetID)))->disableOutput();
	dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(TinetKernCfg)))->disableOutput();
	}

//
// ConfigurationFileGenerator::outTinet_id_h -- ID �����ե����� (tinet_id.h) ����Ϥ��롣
//

void
ConfigurationFileGenerator::outTinet_id_h (Directory& container)
{
	TinetID*	out = NULL;
	Directory*	scope;

	out = dynamic_cast<TinetID *>(RuntimeObjectTable::getInstance(typeid(TinetID)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_id.h disappeared.",
		                 "�������顼: tinet_id.h �ѤΥե����륹�ȥ꡼�ब�����ޤ���") << throwException;
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
// ConfigurationFileGenerator::outCfgTCP_CRE_REP --  TCP ���ո����������Ϥ��롣
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

		// TCP ���ո�������Ϥ��롣
		(*out) << "#define TNUM_TCP_REPID\t" << container.size() << "\n\n";

		// TCP ���ո��κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� TCP/IPv4 ���ո�����Ϥ��롣
		(*out) << "T_TCP4_REP tcp_rep[TNUM_TCP_REPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t0,\n";
				(*out) << "\t\t{ IPV4_ADDRANY, TCP_PORTANY },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_DYNAMIC,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}
			else {
				// �̾������ξ��
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
// ConfigurationFileGenerator::outCfgTCP_CRE_CEP --  TCP �̿�ü�����������Ϥ��롣
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

		// TCP �̿�ü��������Ϥ��롣
		(*out) << "#define TNUM_TCP_CEPID\t" << container.size() << "\n\n";

		// TCP �̿�ü���κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� TCP/IPv4 �̿�ü������Ϥ��롣
		(*out) << "T_TCP4_CEP tcp_cep[TNUM_TCP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(t_tcp_callback)NULL,\n";
				(*out) << "\t\tTCP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// �̾������ξ��
				(*out) << "\t\t"        << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["sbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["sbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["rbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["rbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(t_tcp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tTCP_CEP_FLG_VALID,\n";
				}

			// ������¸�����
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
// ConfigurationFileGenerator::outCfgUDP_CRE_CEP --  UDP �̿�ü�����������Ϥ��롣
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

		// UDP �̿�ü��������Ϥ��롣
		(*out) << "#define TNUM_UDP_CEPID\t" << container.size() << "\n\n";

		// UDP �̿�ü���κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_udp_cepid = (TMIN_UDP_CEPID + TNUM_UDP_CEPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� UDP/IPv4 �̿�ü������Ϥ��롣
		(*out) << "T_UDP4_CEP udp_cep[TNUM_UDP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON UDP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t"     << "0,\n";
				(*out) << "\t\t{ "   << "IPV4_ADDRANY, "
				                     << "UDP_PORTANY },\n";
				(*out) << "\t\t(t_udp_callback)" << "NULL,\n";
				(*out) << "\t\tUDP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// �̾������ξ��
				(*out) << "\t\t"     << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t{ "   << (*(*psorter).second)["myipaddr"].toString() << ", "
				                     << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "\t\t(t_udp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tUDP_CEP_FLG_VALID,\n";
				}

			// ������¸�����
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
// ConfigurationFileGenerator::outCfgTCP6_CRE_REP --  TCP/IPv6 ���ո����������Ϥ��롣
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

		// TCP/IPv6 ���ո�������Ϥ��롣
		(*out) << "#define TNUM_TCP_REPID\t" << container.size() << "\n\n";

		// TCP/IPv6 ���ո��κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� TCP/IPv6 ���ո�����Ϥ��롣
		(*out) << "T_TCP6_REP tcp_rep[TNUM_TCP_REPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t0,\n";
				(*out) << "\t\t{ IPV6_ADDRANY, TCP_PORTANY },\n";
				(*out) << "#if defined(TCP_CFG_EXTENTIONS)\n";
				(*out) << "\t\tTCP_REP_FLG_DYNAMIC,\n";
				(*out) << "\t\tSEM_TCP_REP_LOCK" << count << ",\n";
				(*out) << "#endif\n";
				}
			else {
				// �̾������ξ��
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
// ConfigurationFileGenerator::outCfgTCP6_CRE_CEP --  TCP/IPv6 �̿�ü�����������Ϥ��롣
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

		// TCP/IPv6 �̿�ü��������Ϥ��롣
		(*out) << "#define TNUM_TCP_CEPID\t" << container.size() << "\n\n";

		// TCP/IPv6 �̿�ü���κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� TCP/IPv6 �̿�ü������Ϥ��롣
		(*out) << "T_TCP6_CEP tcp_cep[TNUM_TCP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON TCP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(void*)NULL,\n";
				(*out) << "\t\t0,\n";
				(*out) << "\t\t(t_tcp_callback)NULL,\n";
				(*out) << "\t\tTCP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// �̾������ξ��
				(*out) << "\t\t"        << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["sbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["sbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(void*)" << (*(*psorter).second)["rbuf"    ].toString() << ",\n";
				(*out) << "\t\t"        << (*(*psorter).second)["rbufsz"  ].toString() << ",\n";
				(*out) << "\t\t(t_tcp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tTCP_CEP_FLG_VALID,\n";
				}

			// ������¸�����
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
// ConfigurationFileGenerator::outCfgUDP6_CRE_CEP --  UDP/IPv6 �̿�ü�����������Ϥ��롣
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

		// UDP/IPv6 �̿�ü��������Ϥ��롣
		(*out) << "#define TNUM_UDP_CEPID\t" << container.size() << "\n\n";

		// UDP/IPv6 �̿�ü���κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_udp_cepid = (TMIN_UDP_CEPID + TNUM_UDP_CEPID - 1);\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// TINET �������Ѥ� UDP/IPv6 �̿�ü������Ϥ��롣
		(*out) << "T_UDP6_CEP udp_cep[TNUM_UDP_CEPID] = {\n";
		count = 1;
		psorter = sorter.begin();
		while (psorter != sorter.end()) {
			(*out) << "\t{\n";

			// ITRON UDP/IP API ɸ������
			if ((*psorter).second->findChild("_reserved") != 0) {
				// ͽ�� ID �ξ��
				(*out) << "\t\t"     << "0,\n";
				(*out) << "\t\t{ "   << "IPV6_ADDRANY, "
				                     << "UDP_PORTANY },\n";
				(*out) << "\t\t(t_udp_callback)" << "NULL,\n";
				(*out) << "\t\tUDP_CEP_FLG_DYNAMIC,\n";
				}
			else {
				// �̾������ξ��
				(*out) << "\t\t"     << (*(*psorter).second)["cepatr"  ].toString() << ",\n";
				(*out) << "\t\t{ "   << (*(*psorter).second)["myipaddr"].toString() << ", "
				                     << (*(*psorter).second)["myportno"].toString() << " },\n";
				(*out) << "\t\t(t_udp_callback)" << (*(*psorter).second)["callback"].toString() << ",\n";
				(*out) << "\t\tUDP_CEP_FLG_VALID,\n";
				}

			// ������¸�����
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
// ConfigurationFileGenerator::outCfgEMPTY_TCP_CRE_REP --  TCP ���ո��� EMPTY �������Ϥ��롣
//

void
ConfigurationFileGenerator::outCfgEMPTY_TCP_CRE_REP (MultipartStream* out)
{
	// #ifdef ����Ϥ��롣
	(*out) << "#ifdef TCP_CFG_PASSIVE_OPEN\n\n";

	// TCP ���ո�����0�ˤ���Ϥ��롣
	(*out) << "#define TNUM_TCP_REPID\t0\n\n";

	// TCP ���ո��κ��� ID ����Ϥ��롣
	(*out) << "const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);\n\n";

	// TCP ���ո���¤�Τζ���٥����Ϥ��롣
	(*out) << "#if defined(SUPPORT_INET4)\n";
	(*out) << "T_TCP4_REP tcp_rep[1];\n";
	(*out) << "#endif\n\n";
	(*out) << "#if defined(SUPPORT_INET6)\n";
	(*out) << "T_TCP6_REP tcp_rep[1];\n";
	(*out) << "#endif\n\n";

	// #endif ����Ϥ��롣
	(*out) << "#endif\t/* of ifdef TCP_CFG_PASSIVE_OPEN */\n\n";
	}

//
// ConfigurationFileGenerator::outCfgIPSEC_VSET_SPD --  SPD���������Ϥ��롣
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

		// SP�Υ롼�������Ϥ��롣
	//	(*out) << "#define IPSEC_TNUM_SPD\t" << container.size() << "\n\n";

		// SP�κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_ipsec_spd = (IPSEC_TMIN_IPSEC_SPD + IPSEC_TNUM_SPD - 1);\n\n";

		// SP���Ǽ�������� ����Ϥ��롣
		(*out) << "T_SECPOLICY * spd_rules[IPSEC_TNUM_SPD];\n\n";

		// ID ��˥����Ȥ��롣
		count = 0;
		scope = container.getFirstChild();
		while (scope != NULL) {
			sorter[scope->toInteger(count ++)] = scope;
			scope = scope->getNext();
			}

		// �� SP �Υ롼�����Ϥ��롣
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

			// ������¸�����
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
// ConfigurationFileGenerator::outCfgIPSEC_VSET_SAD --  SAD���������Ϥ��롣
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

		// SA�Υ롼�������Ϥ��롣
	//	(*out) << "#define IPSEC_TNUM_SAD\t" << container.size() << "\n\n";

		// SA�κ��� ID ����Ϥ��롣
		(*out) << "const ID tmax_ipsec_sad = (IPSEC_TMIN_IPSEC_SAD + IPSEC_TNUM_SAD - 1);\n\n";

		// SA�ΰ����򼨤��������ݤ��롣
		(*out) << "T_SECAS_HEAD *sad_list[IPSEC_TNUM_SAD];\n\n";

		// ID ��˥����Ȥ��롣
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
			keystream.str("");	//keystream�򥯥ꥢ
			bufstream.str("");	//bufsteream�򥯥ꥢ
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
				bufstream.str("");	//bufsteream�򥯥ꥢ
				bufstream << len*4;
				(*(*psorter).second)["key_enc"  ] = bufstream.str();

			} else {
				if (!(key.length() == 256/8 || key.length() == 192/8 || key.length() == 128/8)){
					std::cout << "Key Length is not 128/192/256-bit. ("<< key.length()*8 << "-bit)->" << key << "\n";
				}
				keyconv = key;
				len = key.length();

				(*out) << "static uint8_t Key" << bufstream.str() << "[] = {\"" << key << "\"};\n";
				bufstream.str("");	//bufsteream�򥯥ꥢ
				bufstream << len*8;
				(*(*psorter).second)["key_enc"  ] = bufstream.str();
			}

			count ++;
			psorter ++;
			}
		(*out) << "\n";

		// �� SA �Υ롼�����Ϥ��롣
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
// ConfigurationFileGenerator::outTinet_cfg_c -- TINET �����ե����� (tinet_cfg.c) ����Ϥ��롣
//

void
ConfigurationFileGenerator::outTinet_cfg_c (Directory& container)
{
	Directory*	scope;
	TinetCfg*	out = NULL;

	out = dynamic_cast<TinetCfg *>(RuntimeObjectTable::getInstance(typeid(TinetCfg)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_cfg.c disappeared.",
		                 "�������顼: tinet_cfg.c �ѤΥե����륹�ȥ꡼�ब�����ޤ���") << throwException;
		return;
		}

	// ɸ��Υ��󥯥롼�ɥե��������Ϥ��롣
	out->movePart("header");
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_cfg.c disappeared.",
		                 "�������顼: tinet_cfg.c �ѤΥե����륹�ȥ꡼�ब�����ޤ���") << throwException;
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

	// TINET ID ����ե�����̾����Ϥ��롣
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

	// �桼������Υ��󥯥롼�ɥե��������Ϥ��롣
	out->movePart(INCLUDE_FILE);
	scope = container(OBJECT_TREE "/" INCLUDE_FILE)->getFirstChild();
	while (scope != NULL) {
		(*out) << "#include " << scope->toString() << "\n";
		scope = scope->getNext();
		}
	(*out) << "\n";

	if (container[OBJECT_TREE "/" TCP_REP].size() > 0)
		outCfgTCP_CRE_REP(out, container[OBJECT_TREE "/" TCP_REP]);	// TCP ���ո����������Ϥ��롣
	else if (container[OBJECT_TREE "/" TCP6_REP].size() > 0)
		outCfgTCP6_CRE_REP(out, container[OBJECT_TREE "/" TCP6_REP]);	// TCP/IPv6 ���ո����������Ϥ��롣
	else
		outCfgEMPTY_TCP_CRE_REP(out);						// TCP/IP ���ո��� EMPTY �������Ϥ��롣

	outCfgTCP_CRE_CEP(out, container[OBJECT_TREE "/" TCP_CEP]);	// TCP �̿�ü�����������Ϥ��롣
	outCfgTCP6_CRE_CEP(out, container[OBJECT_TREE "/" TCP6_CEP]);	// TCP/IPv6 �̿�ü�����������Ϥ��롣

	outCfgUDP_CRE_CEP(out, container[OBJECT_TREE "/" UDP_CEP]);	// UDP �̿�ü�����������Ϥ��롣
	outCfgUDP6_CRE_CEP(out, container[OBJECT_TREE "/" UDP6_CEP]);	// UDP/IPv6 �̿�ü�����������Ϥ��롣

	if (findOption("-ipsec")) {
		outCfgIPSEC_VSET_SPD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SPD]);	// SPD���������Ϥ��롣
		outCfgIPSEC_VSET_SAD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SAD]);	// SAD���������Ϥ��롣
	}

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::outKernCfgTCP_CRE_REP --  TCP ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgTCP_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP_REP);

		// �� TCP ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgTCP_CRE_CEP --  TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgTCP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP_CEP);

		// �� TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgUDP_CRE_CEP --  UDP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgUDP_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(UDP_CEP);

		// �� UDP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgTCP6_CRE_REP --  TCP/IPv6 ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgTCP6_CRE_REP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP6_REP);

		// �� TCP/IPv6 ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgTCP6_CRE_CEP --  TCP/IPv6 �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgTCP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(TCP6_CEP);

		// �� TCP/IPv6 �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgUDP6_CRE_CEP --  UDP/IPv6 �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgUDP6_CRE_CEP (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(UDP6_CEP);

		// �� UDP/IPv6 �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outIPsec_config_h -- TINET �����ե����� (ipsec_config.h) ����Ϥ��롣
//

void
ConfigurationFileGenerator::outIPsec_config_h (Directory& container)
{
	IPsecConfig*	out;

	out = dynamic_cast<IPsecConfig *>(RuntimeObjectTable::getInstance(typeid(IPsecConfig)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of ipsec_config.h disappeared.",
		                 "�������顼: ipsec_config.h �ѤΥե����륹�ȥ꡼�ब�����ޤ���") << throwException;
		return;
		}

	(*out) << "/* ipsec_config.h */\n";

	if (container[OBJECT_TREE "/" IPSEC_SET_UP_SPD].size() > 0) {

		// SP�Υ롼�������Ϥ��롣
		(*out) << "#define IPSEC_TNUM_SPD\t" << container[OBJECT_TREE "/" IPSEC_SET_UP_SPD].size() << "\n";
		}

	if (container[OBJECT_TREE "/" IPSEC_SET_UP_SAD].size() > 0) {

		// SA�Υ롼�������Ϥ��롣
		(*out) << "#define IPSEC_TNUM_SAD\t" << container[OBJECT_TREE "/" IPSEC_SET_UP_SAD].size() << "\n";
		}

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SPD --  SPD�˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SPD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(IPSEC_SET_UP_SPD);

		// �� TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SAD --  SAD�˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//

void
ConfigurationFileGenerator::outKernCfgIPSEC_VSET_SAD (MultipartStream* out, Directory& container)
{
	if (container.size() > 0) {
		Directory*	scope;
		int		count;

		out->movePart(IPSEC_SET_UP_SAD);

		// �� TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
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
// ConfigurationFileGenerator::outTinet_kern_cfg -- TINET �����ͥ빽���ե����� (tinet_kern.cfg) ����Ϥ��롣
//

void
ConfigurationFileGenerator::outTinet_kern_cfg (Directory& container)
{
	TinetKernCfg*	out;

	out = dynamic_cast<TinetKernCfg *>(RuntimeObjectTable::getInstance(typeid(TinetKernCfg)));
	if (out == 0) {
		ExceptionMessage("Internal error: The stream buffer of tinet_kern.cfg disappeared.",
		                 "�������顼: tinet_kern.cfg �ѤΥե����륹�ȥ꡼�ब�����ޤ���") << throwException;
		return;
		}

	outKernCfgTCP_CRE_REP(out, container[OBJECT_TREE "/" TCP_REP]);		// TCP ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	outKernCfgTCP_CRE_CEP(out, container[OBJECT_TREE "/" TCP_CEP]);		// TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	outKernCfgUDP_CRE_CEP(out, container[OBJECT_TREE "/" UDP_CEP]);		// UDP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	outKernCfgTCP6_CRE_REP(out, container[OBJECT_TREE "/" TCP6_REP]);	// TCP ���ո��˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	outKernCfgTCP6_CRE_CEP(out, container[OBJECT_TREE "/" TCP6_CEP]);	// TCP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
	outKernCfgUDP6_CRE_CEP(out, container[OBJECT_TREE "/" UDP6_CEP]);	// UDP �̿�ü���˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//	outKernCfgIPSEC_VSET_SPD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SPD]);		// SP�����˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣
//	outKernCfgIPSEC_VSET_SAD(out, container[OBJECT_TREE "/" IPSEC_SET_UP_SAD]);		// SA�����˻��Ѥ��륫���ͥ륪�֥������Ȥ���Ϥ��롣

	out->enableOutput();
	}

//
// ConfigurationFileGenerator::body -- �ե��������������� 
//

void
ConfigurationFileGenerator::body (Directory& container)
{
	outTinet_id_h(container);	// tinet_id.h     ����Ϥ��롣
	outTinet_cfg_c(container);	// tinet_cfg.c    ����Ϥ��롣
	outTinet_kern_cfg(container);	// tinet_kern.cfg ����Ϥ��롣
	if (findOption("-ipsec")) {
		outIPsec_config_h(container);	// ipsec_config.h    ����Ϥ��롣
	}
	}
