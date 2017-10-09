///////////////////////////////////////////////////////////
//@file ConvertObjectFactory.h
//@brief 変換オブジェクト生成クラスの宣言
//@author 酒井 崚
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
