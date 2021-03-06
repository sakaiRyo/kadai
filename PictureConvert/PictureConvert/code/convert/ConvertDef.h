///////////////////////////////////////////////////////////
//@file ConvertDef.h
//@brief GdiÇNXÌé¾
//@author ðä Ã
///////////////////////////////////////////////////////////

#ifndef CONVERT_DEF_H_
#define CONVERT_DEF_H_

#include <string>

namespace convert{

//! Ï·^CvÌñ
enum ConvertType
{
	kConvertTypeInvalid = -1,	//!< s³l
	kConvertTypePngToJpg,		//!< jpg¨png
	kConvertTypeJpegToPng,		//!< png¨jpg
	kConvertTypeNum,			//!< ñ
};

struct ConvertDirectryInfo
{
	std::wstring		srcDirectryPath;		//fBNgpX
	std::wstring		dstDirectryPath;		//fBNgpX

	bool IsValid()
	{
		return (!srcDirectryPath.empty() && !dstDirectryPath.empty());
	}
};

}

#endif //CONVERT_DEF_H_