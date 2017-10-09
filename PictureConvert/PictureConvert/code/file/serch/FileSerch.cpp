///////////////////////////////////////////////////////////
//@file FileSerch.h
//@brief ファイル、ディレクトリ探索クラスの実装
//@author 酒井 崚
///////////////////////////////////////////////////////////

#include <sys/stat.h>
#include <stdexcept>
#include <vector>
#include <assert.h>
#include <locale.h>

#include "./FileSerch.h"

namespace {
	const int kBuffSize = 512;

	const wchar_t* kSerchExeStringTbl[]
	{
		L"/*.*",
		L"/*.jpg",
		L"/*.png",
	};

	static_assert(sizeof(kSerchExeStringTbl) / sizeof(kSerchExeStringTbl[0]) == FileSerch::kSerchNum , "sizeof(kSerchExeStringTbl) / sizeof(kSerchExeStringTbl[0]) != SerchExe::kSerchNum\n");
}

FileSerch::FileSerch()
{

}

FileSerch::~FileSerch()
{

}

bool FileSerch::DirectoryAnalyze( const char dstPath[] , const char srcPath[], const SerchExe serchExe)
{
	WIN32_FIND_DATA win32fd;

	wchar_t srcFilePath[kBuffSize];
	wchar_t dstFilePath[kBuffSize];
	
	_SetDirectoryPath16( srcFilePath , kBuffSize , srcPath , kBuffSize, _GetSerchExeString(serchExe) );
	HANDLE hFind = FindFirstFile(srcFilePath, &win32fd );

	_SetDirectoryPath16(srcFilePath, kBuffSize, srcPath, kBuffSize);
	_SetDirectoryPath16(dstFilePath, kBuffSize, dstPath, kBuffSize);

	//if (hFind == INVALID_HANDLE_VALUE) {
	//	printf("変換元データのディレクトリにディレクトリもデータもありません！！！！！！！！！！！！！！\n");
	//	return false;
	//}
	//else {
	//	do {
	//		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
	//			if(wcsstr(win32fd.cFileName , L"." ) == nullptr)
	//			{
	//				wprintf(L"directory %s\n", win32fd.cFileName);
	//				convert::ConvertDirectryInfo info;
	//				info.srcDirectryPath = srcFilePath;
	//				info.srcDirectryPath += L"/";
	//				info.srcDirectryPath += win32fd.cFileName;
	//				wprintf(L"directory %s\n", info.srcDirectryPath.c_str());
	//			}
	//		}
	//		else{
	//			file_names.push_back(win32fd.cFileName);
	//			wprintf(L"data %s\n", file_names.back().c_str());
	//		}
	//	} while (FindNextFile(hFind, &win32fd));

	//	FindClose(hFind);
	//}

	return _Analize(hFind, win32fd, dstFilePath ,srcFilePath , serchExe);
}

bool FileSerch::DirectoryAnalyze16(const wchar_t dstPath[], const wchar_t srcPath[], const SerchExe serchExe)
{
	WIN32_FIND_DATA win32fd;
	wchar_t srcFilePath[kBuffSize];
	swprintf(srcFilePath, kBuffSize - 1, L"%ls%ls", srcPath, _GetSerchExeString(serchExe));

	HANDLE hFind = FindFirstFile(srcFilePath, &win32fd);

	return _Analize(hFind, win32fd, dstPath, srcPath, serchExe);
}

convert::ConvertDirectryInfo FileSerch::GetDirectryInfo( unsigned int index )
{
	if (index < m_info.size())
	{
		return m_info.at(index);
	}
	printf("指定されたindexがm_infoのサイズより大きいです\n");
	assert(false);
	convert::ConvertDirectryInfo info;
	return info;
}


bool FileSerch::_Analize(HANDLE hFind, WIN32_FIND_DATA win32fd, const wchar_t dstPath[], const wchar_t srcPath[], const SerchExe serchExe)
{
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("変換元データのディレクトリにディレクトリもデータもありません！！！！！！！！！！！！！！\n");
		return false;
	}
	else {
		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (wcsstr(win32fd.cFileName, L".") == nullptr)
				{
					convert::ConvertDirectryInfo info;
					//入力ディレクトリ指定
					_SetConvertDirectoryInfo(info.srcDirectryPath, srcPath, win32fd.cFileName);
					//出力ディレクトリ指定
					_SetConvertDirectoryInfo(info.dstDirectryPath, dstPath, win32fd.cFileName);
					m_info.push_back(info);
				}
			}
			else {
				convert::ConvertDirectryInfo info;
				//入力ディレクトリ指定
				_SetConvertDirectoryInfo(info.srcDirectryPath, srcPath, win32fd.cFileName);
				//出力ディレクトリ指定
				_SetConvertDirectoryInfo(info.dstDirectryPath, dstPath, win32fd.cFileName);
				m_info.push_back(info);
				//wprintf(L"data %s\n", file_names.back().c_str());
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}

	return true;

}

void FileSerch::_SetConvertDirectoryInfo(std::wstring& out, const wchar_t path[], const wchar_t fileName[])
{
	wprintf(L"directory %s\n", fileName);
	convert::ConvertDirectryInfo info;
	out = path;
	out += L"/";
	out += fileName;
	wprintf(L"directory %s\n", out.c_str());
}

bool FileSerch::_SetDirectoryPath16(wchar_t dst[], size_t dstBuffSize, const char src[], size_t srcBuffSize, const wchar_t addSerchFile[])
{
	//参照チェック

	// 処理前にバッファクリア
	memset(dst, 0 , dstBuffSize);
	size_t setSize = 0;
	
	int errorNo = static_cast<int>(mbstowcs_s(&setSize, dst, dstBuffSize, src, srcBuffSize));
	if(errorNo > 0)
	{
		//エラー
		return false;
	}

	// 検索ファイルの名前、拡張子設定が指定されていたらそれも追加で設定
	if (addSerchFile)
	{
		swprintf(dst, dstBuffSize - 1 , L"%ls%ls" , dst, addSerchFile);
	}

	return true;
}

const wchar_t*	FileSerch::_GetSerchExeString(const SerchExe serchExe)
{
	if (_IsValidSerchExe(serchExe) == false) {
		printf("FileSerch::_GetSerchExeString SerchExeの指定がおかしいです。 %d", serchExe);
		return nullptr;
	}
	return kSerchExeStringTbl[serchExe];
}

const size_t	FileSerch::_GetSerchExeStringSize(const SerchExe serchExe)
{
	if (_IsValidSerchExe(serchExe) == false){
		printf("FileSerch::_GetSerchExeStringSize SerchExeの指定がおかしいです。 %d", serchExe);
		return 0;
	}
	return lstrlenW(kSerchExeStringTbl[serchExe]);
}

const bool FileSerch::_IsValidSerchExe(const SerchExe serchExe)
{
	return ( serchExe > kSerchInvalid && serchExe < kSerchNum );
}

