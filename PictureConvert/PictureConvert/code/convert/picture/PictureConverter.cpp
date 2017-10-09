///////////////////////////////////////////////////////////
//@file PictureConvert.h
//@brief �摜�ϊ��N���X�錾
//@author ���� ��
///////////////////////////////////////////////////////////

#include <assert.h>
#include "./PictureConverter.h"
#include "../ConvertUtil.h"
#include "../../gdiplus/GdiPlusManager.h"

namespace
{
	GdiPlusManager	gdiPlus;
}

void threadFunc(ConvertObjectBase* obj)
{
	obj->Convert();
}

PictureConvert::PictureConvert(convert::ConvertDirectryInfo info , const convert::ConvertType type)
:ConvertObjectBase(info , type)
,m_SerchExe(FileSerch::kSerchInvalid)
{
	switch( m_type)
	{
		case convert::kConvertTypePngToJpg:
			m_SerchExe = FileSerch::kSerchPng;
		break;
		case convert::kConvertTypeJpegToPng:
			m_SerchExe = FileSerch::kSerchJpg;
		break;
		default:
			printf("�s���ȃ^�C�v�ݒ肪����Ă��܂�!!!!!!!!!!! %d", m_type);
		break;
	}
}

PictureConvert::~PictureConvert()
{

}


void PictureConvert::Convert()
{
	m_fileSerch->DirectoryAnalyze16( m_dirInfo.dstDirectryPath.c_str() , m_dirInfo.srcDirectryPath.c_str(), m_SerchExe);
	unsigned int dataNum = m_fileSerch->GetConvertDirectryNum();
	for ( unsigned int i = 0; i < dataNum; i++)
	{
		printf("�R���o�[�g�J�n %d\n", i);
		convert::ConvertDirectryInfo info = m_fileSerch->GetDirectryInfo(i);
		gdiPlus.ConvertPicture(info.srcDirectryPath.c_str(), info.dstDirectryPath.c_str());
	}

	SetThreadExec(false);
}

void PictureConvert::CreateThread()
{
	SetThreadExec(true);
	m_thread = new std::thread(&threadFunc, this);
}
