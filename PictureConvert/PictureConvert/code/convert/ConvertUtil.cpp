///////////////////////////////////////////////////////////
//@file ConvertUtil.h
//@brief �R���o�[�g����̃��[�e�B���e�B����
//@author ���� ��
///////////////////////////////////////////////////////////

#include "./ConvertUtil.h"

namespace convert {
namespace util {

	bool IsConvartTypeValid(ConvertType type)
	{
		return (type > kConvertTypeInvalid && type < kConvertTypeNum);
	}

}
}
