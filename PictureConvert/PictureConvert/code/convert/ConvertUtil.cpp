///////////////////////////////////////////////////////////
//@file ConvertUtil.h
//@brief コンバート周りのユーティリティ実装
//@author 酒井 崚
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
