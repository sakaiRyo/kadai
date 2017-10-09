///////////////////////////////////////////////////////////
//@file ConvertManager.h
//@brief コンバートオブジェクト管理クラス宣言
//@author 酒井 崚
///////////////////////////////////////////////////////////

#include <assert.h>
#include "./ConvertManager.h"
#include "../ConvertBase.h"
#include "../factory/ConvertObjectFactory.h"

///////////////////////////////////////////////////////////

ConvertManager::ConvertManager(const convert::ConvertType type, FileSerch fliseSerch)
: m_state(kStateInit)
, m_convertType(type)
{
	m_DirectoryInfo			= fliseSerch;
}

ConvertManager::~ConvertManager()
{
}

void ConvertManager::Update()
{
	switch (m_state)
	{
		case ConvertManager::kStateNone:
			break;
		case ConvertManager::kStateInit:
			_ConvertInitExecute();
			break;
		case ConvertManager::kStateExecute:
			_ConvertExecute();
			break;
		case ConvertManager::kStateTerm:
			_ConvertTerm();
			break;
		default:
			printf("ConvertManager::Update 未定義のステートが設定されています!!!!!!!! state = %d\n " , m_state);
			assert(false);
			break;
	}

}

bool ConvertManager::IsEnd()
{
	return ( m_state == kStateNone );
}


void ConvertManager::_ConvertInitExecute()
{
	ConvertObjectFactory factory;
	
	unsigned int num =m_DirectoryInfo.GetConvertDirectryNum();
	for (unsigned int i = 0; i < num; i++ )
	{
		ConvertObjectBase* object = factory.Create(m_DirectoryInfo.GetDirectryInfo(i), m_convertType);
		if (object)
		{
			object->CreateThread();
			m_ConvertObjectList.push_back(object);
		}
	}

	m_state = kStateExecute;
}

void ConvertManager::_ConvertExecute()
{
	std::list<ConvertObjectBase*>::iterator itr = m_ConvertObjectList.begin();
	std::list<ConvertObjectBase*>::iterator end = m_ConvertObjectList.end();
	bool isEnd = true;
	
	while (itr != end){
		isEnd &= (*itr)->ThreadEndCheck();
		itr++;
	}
	// 全オブジェクト処理が終了していたら
	if(isEnd){
		m_state = kStateTerm;
	}
}

void ConvertManager::_ConvertTerm()
{
	std::list<ConvertObjectBase*>::iterator itr = m_ConvertObjectList.begin();
	std::list<ConvertObjectBase*>::iterator end = m_ConvertObjectList.end();

	while (itr != end)
	{
		delete (*itr);
		itr++;
	}
	m_ConvertObjectList.clear();
	m_state = kStateNone;
}
