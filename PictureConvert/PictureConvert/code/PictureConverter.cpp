#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "./file/serch/FileSerch.h"
#include "./convert/manager/ConvertManager.h"


int main(int argc, char *argv[])
{
	// ���Ȃ��Ƃ����s�t�@�C���̋N������ �ȊO�Ɉ���������
	if (argc < 4)
	{
		printf( "��2�����ȍ~�̎w�肪�s���Ă��Ȃ��悤�ł�\n" );
		printf("��2�����ɂ͕ϊ���̃f�[�^�̏o�͐�f�B���N�g�����w��\n");
		printf("��3�����ɂ͕ϊ����̃f�[�^�̃f�B���N�g�����w��\n");
		printf("��4�����ɂ͕ϊ��̕��@���w�� 0:png��jpg 1:jpg��png\n");
		printf("�����L�[�������ƏI�����܂�\n");
		//�ꎞ��~
		getchar();
		return -1;
	}
	
	printf("�ϊ��o�͐�w��f�B���N�g�� : %s\n" , argv[1]);
	printf("�ϊ����w��f�B���N�g�� : %s\n", argv[2]);
	printf("�ϊ����[�h : %s\n", argv[3]);


	FileSerch fliseSerch;
	//�J�����g�f�B���N�g���ȉ��̃f�B���N�g����f�[�^�̑��݊m�F�Ƃ����Ƀf�B���N�g�����ǂꂾ�����邩���
	if(fliseSerch.DirectoryAnalyze(argv[1], argv[2], FileSerch::kSerchExeDirectory) == false)
	{
		printf("�w�肳�ꂽ�ϊ����f�B���N�g���ɂ͉����f�[�^�������悤�ł��B\n");
		//�ꎞ��~
		getchar();
		return -1;
	}
	convert::ConvertType type =	static_cast<convert::ConvertType>(atoi(argv[3]));
	ConvertManager*		convertMan	= new ConvertManager( type , fliseSerch );

	while(convertMan->IsEnd() == false)
	{
		convertMan->Update();
	}

	//�ꎞ��~
	printf("�S�ϊ��I�����܂����B�����L�[����͂���ƏI�����܂�\n");
	getchar();

    return 0;
}

