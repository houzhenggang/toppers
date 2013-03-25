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
//  @(#) $Id: tinet_classes.h,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#ifndef _TINET_CLASSES_H_
#define _TINET_CLASSES_H_

//
// ���饹���
//

// �ѡ������

class CoreParser : public ParserComponent {

	private:

	protected:

		// ���۴ؿ�

		virtual void parseOption (Directory& container);

		// �ؿ�

		int assignID (Directory& container, const char *category);

	public:

		// ���󥹥ȥ饯��

		CoreParser (void);

		// ���۴ؿ�

		virtual bool parse (Parser& parser, Directory& container);

	};

//  TINET �����ե�����

class SpecialtyFile : public MultipartStream, public RuntimeObject {

	protected:

		SpecialtyFile (void) throw();

		template<class T>
		static T* createInstance (std::string filename) throw(Exception)
		{
			T* old;
			T* result = 0;

			old = dynamic_cast<T*>(RuntimeObjectTable::getInstance(typeid(T)));
			if (old != 0)
				delete old;

			result = new(nothrow) T;
			if (result == 0)
				ExceptionMessage("Internal error : Object creation failure [createInstance]",
				                 "�������顼 : ���֥����������������顼 [createInstance]") << throwException;
			try {
				result->setFilename(filename);
				}
			catch (...) {
				if (result != 0)
					delete result;
				throw;
				}
			return result;
			};
	};

//  tinet_cfg.c

class TinetCfg : public SpecialtyFile {

	public:

		struct CreationEvent {
			class TinetCfg* file;
			};

		static inline TinetCfg* createInstance (std::string filename) throw(Exception) {
			return SpecialtyFile::createInstance<TinetCfg>(filename);
			};

	};

//  tinet_id.h

class TinetID : public SpecialtyFile {

	public:

		struct CreationEvent {
			class TinetID* file;
			};

		static inline TinetID* createInstance (std::string filename) throw(Exception) {
			return SpecialtyFile::createInstance<TinetID>(filename);
			};

	};

//  ipsec_config.h

class IPsecConfig : public SpecialtyFile {

	public:

		struct CreationEvent {
			class IPsecConfig* file;
			};

		static inline IPsecConfig* createInstance (std::string filename) throw(Exception) {
			return SpecialtyFile::createInstance<IPsecConfig>(filename);
			};

	};

//  tinet_kern.cfg

class TinetKernCfg : public SpecialtyFile {

	public:

		struct CreationEvent {
			class TinetKernCfg* file;
			};

		static inline TinetKernCfg* createInstance (std::string filename) throw(Exception) {
			return SpecialtyFile::createInstance<TinetKernCfg>(filename);
			};

	};

//  ����ե����졼�����ե���������

class ConfigurationFileGenerator : public Component {

	private:

		// �ؿ�

		void outTinet_id_h     (Directory& container);
		void outTinet_cfg_c    (Directory& container);
		void outTinet_kern_cfg (Directory& container);
		void outIPsec_config_h (Directory& container);

		void outCfgTCP_CRE_REP (MultipartStream* out, Directory& container);
		void outCfgTCP_CRE_CEP (MultipartStream* out, Directory& container);
		void outCfgUDP_CRE_CEP (MultipartStream* out, Directory& container);

		void outCfgEMPTY_TCP_CRE_REP (MultipartStream* out);

		void outCfgTCP6_CRE_REP (MultipartStream* out, Directory& container);
		void outCfgTCP6_CRE_CEP (MultipartStream* out, Directory& container);
		void outCfgUDP6_CRE_CEP (MultipartStream* out, Directory& container);

		void outKernCfgTCP_CRE_REP (MultipartStream* out, Directory& container);
		void outKernCfgTCP_CRE_CEP (MultipartStream* out, Directory& container);
		void outKernCfgUDP_CRE_CEP (MultipartStream* out, Directory& container);

		void outKernCfgTCP6_CRE_REP (MultipartStream* out, Directory& container);
		void outKernCfgTCP6_CRE_CEP (MultipartStream* out, Directory& container);
		void outKernCfgUDP6_CRE_CEP (MultipartStream* out, Directory& container);

		void outCfgIPSEC_VSET_SPD (MultipartStream* out, Directory& container);
		void outKernCfgIPSEC_VSET_SPD (MultipartStream* out, Directory& container);
		void outCfgIPSEC_VSET_SAD (MultipartStream* out, Directory& container);
		void outKernCfgIPSEC_VSET_SAD (MultipartStream* out, Directory& container);

	protected:

		// ���۴ؿ�

		virtual void parseOption (Directory& container);
		virtual void body        (Directory& container);
		virtual void onFatalExit (Directory& container);

	public:

		// ���󥹥ȥ饯��

		ConfigurationFileGenerator (void) : Component(CODEGENERATOR) {};

	};

#endif	/* of #ifndef _TINET_CLASSES_H_ */
