///////////////////////////////////////////////////////////
//@file GdiPlusManager.cpp
//@brief Gdi�Ǘ��N���X�̎���
//@author ���� ��
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
	//GDI+�̏�����
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
}

GdiPlusManager::~GdiPlusManager()
{
	//GDI+�̏I������
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

void GdiPlusManager::ConvertPicture(const wchar_t srcPicPath[], const wchar_t dstPicPath[])
{
	mtx.lock();
	CLSID encoderClsid;

	//�����̃p�����[�^���w�肷��ꍇ�͂�����
	EncoderParameters* encoderParameters = (EncoderParameters*)malloc(sizeof(EncoderParameters) + 4 * sizeof(EncoderParameter));
	ULONG colordepth;
	ULONG quality;
	ULONG transformation;
	Status stat;

	// �t�@�C�����w�肵�ăI�u�W�F�N�g���쐬.
	Image* image = new Image(srcPicPath);


	//�摜B�̃t�H�[�}�b�g
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

	//�T�C�Y
	UINT width = image->GetWidth();
	UINT height = image->GetHeight();
	printf("Width : %u\n", width);
	printf("Height: %u\n", height);

	//�𑜓x
	REAL res_hori = image->GetHorizontalResolution();
	REAL res_ver = image->GetVerticalResolution();
	printf("HorizontalResolution : %d\n", res_hori);
	printf("GetVerticalResolution: %d\n", res_ver);

	//�t�@�C���^�C�v
	ImageType type = image->GetType();
	switch (type) {
	case ImageTypeUnknown: printf("ImageType : ImageTypeUnknown(%d)\n", type); break;
	case ImageTypeBitmap: printf("ImageType : ImageTypeBitmap(%d)\n", type); break;
	case ImageTypeMetafile: printf("ImageType : ImageTypeMetafile(%d)\n", type); break;
	default: printf("ImageType : Error(%d)\n", type); break;
	}

	//�J���[�t�H�[�}�b�g
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


	//�ۑ�����Ƃ��̃G���R�[�_��JPG�ɐݒ�
	GetEncoderClsid(dstPicPath, &encoderClsid);


	//�p�����[�^�̐����w��
	encoderParameters->Count = 3;
	//�F�[�x
	encoderParameters->Parameter[2].Guid = EncoderColorDepth;
	encoderParameters->Parameter[2].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[2].NumberOfValues = 1;
	colordepth = 24;
	encoderParameters->Parameter[2].Value = &colordepth;
	//�N�I���e�B�̐ݒ�
	encoderParameters->Parameter[1].Guid = EncoderQuality;
	encoderParameters->Parameter[1].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[1].NumberOfValues = 1;
	quality = 80; //0�`100
	encoderParameters->Parameter[1].Value = &quality;
	//��]�̐ݒ�
	encoderParameters->Parameter[0].Guid = EncoderTransformation;
	encoderParameters->Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters->Parameter[0].NumberOfValues = 1;
	transformation = EncoderValueTransformRotate90;
	encoderParameters->Parameter[0].Value = &transformation;

	//�e�폈�������ĕۑ�
	stat = image->Save(dstPicPath, &encoderClsid, encoderParameters);

	//����
	if (stat == Ok) {
		wprintf(L"����\n");
	}
	else {
		wprintf(L"���s(0x%x)\n", stat);
	}

	//�I�u�W�F�N�g�̔j��
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

