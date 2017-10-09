///////////////////////////////////////////////////////////
//@file ConvertManager.h
//@brief コンバートオブジェクト管理クラス宣言
//@author 酒井 崚
///////////////////////////////////////////////////////////

#ifndef CONVERT_MANAGER_H_
#define CONVERT_MANAGER_H_

#include <list>
#include "../ConvertDef.h"
#include "../../file/serch/FileSerch.h"

class ConvertObjectBase;
class ConvertObjectFactory;

class ConvertManager
{
public:
	ConvertManager( const convert::ConvertType type, FileSerch fliseSerch);
	~ConvertManager();

	void Update();

	bool IsEnd();
private:

	void _ConvertInitExecute();
	void _ConvertExecute();
	void _ConvertTerm();

	//! 変換処理更新ステート
	enum State {
		kStateNone = 0,
		kStateInit,
		kStateExecute,
		kStateTerm,
	};
	State								m_state;
	convert::ConvertType				m_convertType;
	std::list<ConvertObjectBase*>		m_ConvertObjectList;	//!< 変換オブジェクト管理用リスト
	FileSerch							m_DirectoryInfo;
};

#endif //#ifndef FILE_SERCH_MANAGER_H_
