///////////////////////////////////////////////////////////
//@file PictureConvert.h
//@brief ‰æ‘œ•ÏŠ·ƒNƒ‰ƒXéŒ¾
//@author ğˆä ›Ã
///////////////////////////////////////////////////////////

#ifndef PICTURE_CONVERT_H
#define PICTURE_CONVERT_H

#include "../ConvertBase.h"

class PictureConvert : public ConvertObjectBase
{
public:
	PictureConvert( convert::ConvertDirectryInfo info , const convert::ConvertType type );
	virtual ~PictureConvert();

	virtual void Convert();
	virtual void CreateThread();

private:
	
	FileSerch::SerchExe			m_SerchExe;
};

#endif //PICTURE_CONVERT_H
