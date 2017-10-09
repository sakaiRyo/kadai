///////////////////////////////////////////////////////////
//@file GdiPlusManager.h
//@brief Gdiä«óùÉNÉâÉXÇÃêÈåæ
//@author éà‰ õ√
///////////////////////////////////////////////////////////

#ifndef GDI_PLUS_MANAGER_H_
#define GDI_PLUS_MANAGER_H_

#include <shlobj.h>
#include <gdiplus.h>
#include <Gdiplusinit.h>
#include "../convert/ConvertDef.h"

class GdiPlusManager
{
public:
	GdiPlusManager();
	~GdiPlusManager();

	void ConvertPicture(const wchar_t srcPicPath[] , const  wchar_t dstPicPath[]);

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

private:
	ULONG_PTR						m_gdiplusToken;
	Gdiplus::GdiplusStartupInput	m_gdiplusStartupInput;
};

#endif //#ifndef GDI_PLUS_MANAGER_H_
