///////////////////////////////////////////////////////////
//@file ConvertObjectBase.h
//@brief �ϊ����N���X�錾
//@author ���� ��
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
		printf("�s���ȃ^�C�v�ݒ肪����Ă��܂�!!!!!!!!!!! %d", type);
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

