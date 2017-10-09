///////////////////////////////////////////////////////////
//@file ConvertDef.h
//@brief Gdi管理クラスの宣言
//@author 酒井 崚
///////////////////////////////////////////////////////////

#ifndef CONVERT_DEF_H_
#define CONVERT_DEF_H_

#include <string>

namespace convert{

//! 変換タイプの列挙
enum ConvertType
{
	kConvertTypeInvalid = -1,	//!< 不正値
	kConvertTypePngToJpg,		//!< jpg→png
	kConvertTypeJpegToPng,		//!< png→jpg
	kConvertTypeNum,			//!< 列挙数
};

struct ConvertDirectryInfo
{
	std::wstring		srcDirectryPath;		//ディレクトリパス
	std::wstring		dstDirectryPath;		//ディレクトリパス

	bool IsValid()
	{
		return (!srcDirectryPath.empty() && !dstDirectryPath.empty());
	}
};

}

#endif //CONVERT_DEF_H_