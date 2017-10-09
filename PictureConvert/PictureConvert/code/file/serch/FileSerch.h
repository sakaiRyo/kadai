///////////////////////////////////////////////////////////
//@file FileSerch.h
//@brief ファイル、ディレクトリ探索クラスの宣言
//@author 酒井 崚
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

	//! 探索する拡張子
	enum SerchExe
	{
		kSerchInvalid = -1,
		kSerchExeDirectory,	//!< ディレクトリ探索
		kSerchPng,			//!< png拡張子のデータ
		kSerchJpg,			//!< jpg拡張子のデータ
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

