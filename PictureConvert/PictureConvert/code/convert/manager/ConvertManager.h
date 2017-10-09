///////////////////////////////////////////////////////////
//@file ConvertManager.h
//@brief �R���o�[�g�I�u�W�F�N�g�Ǘ��N���X�錾
//@author ���� ��
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

	//! �ϊ������X�V�X�e�[�g
	enum State {
		kStateNone = 0,
		kStateInit,
		kStateExecute,
		kStateTerm,
	};
	State								m_state;
	convert::ConvertType				m_convertType;
	std::list<ConvertObjectBase*>		m_ConvertObjectList;	//!< �ϊ��I�u�W�F�N�g�Ǘ��p���X�g
	FileSerch							m_DirectoryInfo;
};

#endif //#ifndef FILE_SERCH_MANAGER_H_
