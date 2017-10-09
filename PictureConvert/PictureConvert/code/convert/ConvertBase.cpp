///////////////////////////////////////////////////////////
//@file ConvertObjectBase.h
//@brief 変換基底クラス宣言
//@author 酒井 崚
///////////////////////////////////////////////////////////

#include <assert.h>
#include <thread>
#include "./ConvertBase.h"
#include "./ConvertUtil.h"


ConvertObjectBase::ConvertObjectBase( convert::ConvertDirectryInfo info , const convert::ConvertType type )
: m_fileSerch(nullptr)
, m_type(type)
, m_execThread(false)
{
	if (info.IsValid() == false)
	{
		printf("ConvertDirectryInfo is Invalid Setting !!!!!!!!!!!!!!!!!\n");
		assert(false);
	}

	m_dirInfo = info;

	m_fileSerch = new FileSerch();

	if (convert::util::IsConvartTypeValid(m_type) == false)
	{
		printf("不正なタイプ設定がされています!!!!!!!!!!! %d", type);
		assert(false);
	}
}

ConvertObjectBase::~ConvertObjectBase()
{
	if (m_thread)
	{
		ThreadJoin();
		delete m_thread;
	}

	if(m_fileSerch)
	{
		delete m_fileSerch;
	}
}

bool ConvertObjectBase::ThreadEndCheck()
{
	if (IsThreadExec() == false)
	{
		ThreadJoin();
		return true;
	}

	return false;
}

void ConvertObjectBase::ThreadJoin()
{
	if (m_thread->joinable())
	{
		m_thread->join();
	}
}

