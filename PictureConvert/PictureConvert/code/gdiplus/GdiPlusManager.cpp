///////////////////////////////////////////////////////////
//@file GdiPlusManager.cpp
//@brief Gdi管理クラスの実装
//@author 酒井 崚
///////////////////////////////////////////////////////////

#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include <mutex>
#include "./GdiPlusManager.h"

using namespace Gdiplus;
namespace{

	std::mutex mtx;

}
GdiPlusManager::GdiPlusManager()
{
	//GDI+の初期化
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
}

GdiPlusManager::~GdiPlusManager()
{
	//GDI+の終了処理
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

void GdiPlusManager::ConvertPicture(const wchar_t srcPicPath[], const wchar_t dstPicPath[])
{
	mtx.lock();
	CLSID encoderClsid;

	//複数のパラメータを指定する場合はこちら
	EncoderParameters* encoderParameters = (EncoderParameters*)malloc(sizeof(EncoderParameters) + 4 * sizeof(EncoderParameter));
	ULONG colordepth;
	ULONG quality;
	ULONG transformation;
	Status stat;

	// ファイルを指定してオブジェクトを作成.
	Image* image = new Image(srcPicPath);


	//画像Bのフォーマット
	GUID guid;
	image->GetRawFormat(&guid);
	if (guid == ImageFormatUndefined) printf("Format : Undefined(0x%x)\n", guid);
	else if (guid == ImageFormatMemoryBMP) printf("Format : MemoryBMP(0x%x)\n", guid);
	else if (guid == ImageFormatBMP) printf("Format : BMP(0x%x)\n", guid);
	else if (guid == ImageFormatJPEG) printf("Format : JPEG(0x%x)\n", guid);
	else if (guid == ImageFormatPNG) printf("Format : PNG(0x%x)\n", guid);
	else if (guid == ImageFormatGIF) printf("Format : GIF(0x%x)\n", guid);
	else if (guid == ImageFormatTIFF) printf("Format : TIFF(0x%x)\n", guid);
	else printf("Format : Error(0x%x)\n", guid);

	//サイズ
	UINT width = image->GetWidth();
	UINT height = image->GetHeight();
	printf("Width : %u\n", width);
	printf("Height: %u\n", height);

	//解像度
	REAL res_hori = image->GetHorizontalResolution();
	REAL res_ver = image->GetVerticalResolution();
	printf("HorizontalResolution : %d\n", res_hori);
	printf("GetVerticalResolution: %d\n", res_ver);

	//ファイルタイプ
	ImageType type = image->GetType();
	switch (type) {
	case ImageTypeUnknown: printf("ImageType : ImageTypeUnknown(%d)\n", type); break;
	case ImageTypeBitmap: printf("ImageType : ImageTypeBitmap(%d)\n", type); break;
	case ImageTypeMetafile: printf("ImageType : ImageTypeMetafile(%d)\n", type); break;
	default: printf("ImageType : Error(%d)\n", type); break;
	}

	//カラーフォーマット
	PixelFormat pixelFormat = image->GetPixelFormat();
	switch (pixelFormat) {
	case PixelFormat8bppIndexed: printf("PixelFormat : 8bppIndexed(0x%x)\n", pixelFormat); break;
	case PixelFormat16bppRGB555: printf("PixelFormat : 16bppRGB555(0x%x)\n", pixelFormat); break;
	case PixelFormat16bppRGB565: printf("PixelFormat : 16bppRGB565(0x%x)\n", pixelFormat); break;
	case PixelFormat24bppRGB: printf("PixelFormat : 24bppRGB(0x%x)\n", pixelFormat); break;
	case PixelFormat32bppRGB: printf("PixelFormat : 32bppRGB(0x%x)\n", pixelFormat); break;
	case PixelFormat32bppARGB: printf("PixelFormat : 32bppARGB(0x%x)\n", pixelFormat); break;
	default: printf("PixelFormat : Othre(0x%x)\n", pixelFormat); break;
	}


	//保存するときのエンコーダをJPGに設定
	GetEncoderClsid(dstPicPath, &encoderClsid);


	//パラメータの数を指定
	encoderParameters->Count = 3;
	//色深度
	encoderParameters->Parameter[2].Guid = EncoderColorDepth;
	encoderParameters->Parameter[2].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[2].NumberOfValues = 1;
	colordepth = 24;
	encoderParameters->Parameter[2].Value = &colordepth;
	//クオリティの設定
	encoderParameters->Parameter[1].Guid = EncoderQuality;
	encoderParameters->Parameter[1].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[1].NumberOfValues = 1;
	quality = 80; //0～100
	encoderParameters->Parameter[1].Value = &quality;
	//回転の設定
	encoderParameters->Parameter[0].Guid = EncoderTransformation;
	encoderParameters->Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[0].NumberOfValues = 1;
	transformation = EncoderValueTransformRotate90;
	encoderParameters->Parameter[0].Value = &transformation;

	//各種処理をして保存
	stat = image->Save(dstPicPath, &encoderClsid, encoderParameters);

	//結果
	if (stat == Ok) {
		wprintf(L"成功\n");
	}
	else {
		wprintf(L"失敗(0x%x)\n", stat);
	}

	//オブジェクトの破棄
	delete image;
	mtx.unlock();
}

int GdiPlusManager::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0; // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1; // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1; // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; // Success
		}
	}

	free(pImageCodecInfo);
	return -1; // Failure
}

