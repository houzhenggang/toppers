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
//  @(#) $Id: tinet_classes.h,v 1.5 2009/12/24 05:39:31 abe Exp abe $
//

#ifndef _TINET_CLASSES_H_
#define _TINET_CLASSES_H_

//
// クラス定義
//

// パーザ中核

class CoreParser : public ParserComponent {

	private:

	protected:

		// 仮想関数

		virtual void parseOption (Directory& container);

		// 関数

		int assignID (Directory& container, const char *category);

	public:

		// コンストラクタ

		CoreParser (void);

		// 仮想関数

		virtual bool parse (Parser& parser, Directory& container);

	};

//  TINET 構成ファイル

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
				                 "内部エラー : オブジェクト生成時エラー [createInstance]") << throwException;
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

//  コンフィグレーションファイル生成

class ConfigurationFileGenerator : public Component {

	private:

		// 関数

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

		// 仮想関数

		virtual void parseOption (Directory& container);
		virtual void body        (Directory& container);
		virtual void onFatalExit (Directory& container);

	public:

		// コンストラクタ

		ConfigurationFileGenerator (void) : Component(CODEGENERATOR) {};

	};

#endif	/* of #ifndef _TINET_CLASSES_H_ */
