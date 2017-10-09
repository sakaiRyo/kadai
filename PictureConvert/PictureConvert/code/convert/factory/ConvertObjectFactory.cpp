///////////////////////////////////////////////////////////
//@file ConvertObjectFactory.h
//@brief 変換オブジェクト生成クラスの宣言
//@author 酒井 崚
///////////////////////////////////////////////////////////

#include "./ConvertObjectFactory.h"
#include "../picture/PictureConverter.h"


ConvertObjectBase* ConvertObjectFactory::Create(convert::ConvertDirectryInfo info , const convert::ConvertType type)
{
	switch (type)
	{
		case convert::kConvertTypeJpegToPng:
		case convert::kConvertTypePngToJpg:
		return new PictureConvert(info, type);
		default:
		return nullptr;
	}
}

