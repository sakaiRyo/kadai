///////////////////////////////////////////////////////////
//@file ConvertDef.h
//@brief Gdi�Ǘ��N���X�̐錾
//@author ���� ��
///////////////////////////////////////////////////////////

#ifndef CONVERT_DEF_H_
#define CONVERT_DEF_H_

#include <string>

namespace convert{

//! �ϊ��^�C�v�̗�
enum ConvertType
{
	kConvertTypeInvalid = -1,	//!< �s���l
	kConvertTypePngToJpg,		//!< jpg��png
	kConvertTypeJpegToPng,		//!< png��jpg
	kConvertTypeNum,			//!< �񋓐�
};

struct ConvertDirectryInfo
{
	std::wstring		srcDirectryPath;		//�f�B���N�g���p�X
	std::wstring		dstDirectryPath;		//�f�B���N�g���p�X

	bool IsValid()
	{
		return (!srcDirectryPath.empty() && !dstDirectryPath.empty());
	}
};

}

#endif //CONVERT_DEF_H_