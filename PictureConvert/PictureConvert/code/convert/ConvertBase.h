///////////////////////////////////////////////////////////
//@file ConvertObjectBase.h
//@brief ïœä∑äÓíÍÉNÉâÉXêÈåæ
//@author éà‰ õ√
///////////////////////////////////////////////////////////

#ifndef CONVERT_OBJECT_BASE_H
#define CONVERT_OBJECT_BASE_H

#include <thread>
#include "../file/serch/FileSerch.h"
#include "./ConvertDef.h"

class FileSerch;

class ConvertObjectBase
{
public:
	ConvertObjectBase( convert::ConvertDirectryInfo info , const convert::ConvertType type );
	virtual ~ConvertObjectBase();

	virtual void Convert() = 0;
	virtual void CreateThread() = 0;
	virtual void ThreadJoin();

	bool ThreadEndCheck();
	void SetThreadExec(bool enable) { m_execThread = enable; }
	bool IsThreadExec() {return m_execThread;}
protected:

	convert::ConvertDirectryInfo	m_dirInfo;
	FileSerch*						m_fileSerch;
	convert::ConvertType			m_type;

	std::thread*					m_thread;
	bool							m_execThread;

};

#endif //CONVERT_OBJECT_BASE_H
