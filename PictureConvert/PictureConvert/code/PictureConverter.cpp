#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "./file/serch/FileSerch.h"
#include "./convert/manager/ConvertManager.h"


int main(int argc, char *argv[])
{
	// 少なくとも実行ファイルの起動命令 以外に引数がある
	if (argc < 4)
	{
		printf( "第2引数以降の指定が行われていないようです\n" );
		printf("第2引数には変換後のデータの出力先ディレクトリを指定\n");
		printf("第3引数には変換元のデータのディレクトリを指定\n");
		printf("第4引数には変換の方法を指定 0:png→jpg 1:jpg→png\n");
		printf("何かキーを押すと終了します\n");
		//一時停止
		getchar();
		return -1;
	}
	
	printf("変換出力先指定ディレクトリ : %s\n" , argv[1]);
	printf("変換元指定ディレクトリ : %s\n", argv[2]);
	printf("変換モード : %s\n", argv[3]);


	FileSerch fliseSerch;
	//カレントディレクトリ以下のディレクトリやデータの存在確認といかにディレクトリがどれだけあるか解析
	if(fliseSerch.DirectoryAnalyze(argv[1], argv[2], FileSerch::kSerchExeDirectory) == false)
	{
		printf("指定された変換元ディレクトリには何もデータが無いようです。\n");
		//一時停止
		getchar();
		return -1;
	}
	convert::ConvertType type =	static_cast<convert::ConvertType>(atoi(argv[3]));
	ConvertManager*		convertMan	= new ConvertManager( type , fliseSerch );

	while(convertMan->IsEnd() == false)
	{
		convertMan->Update();
	}

	//一時停止
	printf("全変換終了しました。何かキーを入力すると終了します\n");
	getchar();

    return 0;
}

