///////////////////////////////////////////////////////////
//@file ConvertObjectFactory.h
//@brief �ϊ��I�u�W�F�N�g�����N���X�̐錾
//@author ���� ��
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

