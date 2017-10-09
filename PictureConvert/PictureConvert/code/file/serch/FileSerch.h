///////////////////////////////////////////////////////////
//@file FileSerch.h
//@brief �t�@�C���A�f�B���N�g���T���N���X�̐錾
//@author ���� ��
///////////////////////////////////////////////////////////

#ifndef FILE_SERCH_MANAGER_H_
#define FILE_SERCH_MANAGER_H_

#include <vector>
#include <string>
#include <Windows.h>
#include <winnt.h>
#include "../../convert/ConvertDef.h"

class FileSerch
{
public:

	//! �T������g���q
	enum SerchExe
	{
		kSerchInvalid = -1,
		kSerchExeDirectory,	//!< �f�B���N�g���T��
		kSerchPng,			//!< png�g���q�̃f�[�^
		kSerchJpg,			//!< jpg�g���q�̃f�[�^
		kSerchNum,
	};

	FileSerch();
	~FileSerch();

	bool DirectoryAnalyze( const char dstPath[] , const char srcPath[] , const SerchExe serchExe);
	bool DirectoryAnalyze16( const wchar_t dstPath[], const wchar_t srcPath[], const SerchExe serchExe);
	const size_t GetConvertDirectryNum() { return m_info.size(); };
	convert::ConvertDirectryInfo GetDirectryInfo(unsigned int index);

private:

	bool			_Analize(HANDLE hFind, WIN32_FIND_DATA win32fd, const wchar_t dstPath[], const wchar_t srcPath[], const SerchExe serchExe);
	void			_SetConvertDirectoryInfo(std::wstring& out, const wchar_t path[], const wchar_t fileName[]);

	bool			_SetDirectoryPath16( wchar_t dst[], size_t dstBuffSize, const char src[], size_t srcBuffSize, const wchar_t addSerchFile[] = nullptr );

	const wchar_t*	_GetSerchExeString(const SerchExe serchExe);
	const size_t	_GetSerchExeStringSize(const SerchExe serchExe);
	const bool		_IsValidSerchExe(const SerchExe serchExe);



	std::vector<convert::ConvertDirectryInfo>	m_info;
};

#endif //#ifndef FILE_SERCH_MANAGER_H_

