///////////////////////////////////////////////////////////
//@file ConvertObjectFactory.h
//@brief �ϊ��I�u�W�F�N�g�����N���X�̐錾
//@author ���� ��
///////////////////////////////////////////////////////////

#ifndef CONVERT_OBJECT_FACTORY_H
#define CONVERT_OBJECT_FACTORY_H

#include "../ConvertDef.h"

class ConvertObjectBase;

class ConvertObjectFactory
{
public:
	ConvertObjectBase* Create( convert::ConvertDirectryInfo info , const convert::ConvertType type);

};


#endif //CONVERT_OBJECT_FACTORY_H
