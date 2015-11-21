#ifndef __Utility_IFile_H__
#define __Utility_IFile_H__

#include "Object.h"
#include "StringImpl.h"
#include "Windows/WinFunctions.h"

enum EFileMode
{
	FILE_MODE_OPEN,
	FILE_MODE_CREATE_OPEN,
	FILE_MODE_APPEND,
	FILE_MODE_READ_ONLY,
	FILE_MODE_WRITE_ONLY
};

class IFile : public CObject
{
public:
	IFile(CStringWide path, EFileMode mode): m_mode(mode) { m_strPath = ConvertStringToPath(path); }
	~IFile() { }

	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Flush() = 0;
	virtual void Write(CStringWide data) = 0;
	virtual CStringWide ReadString() = 0;

	virtual bool IsExist() = 0;

	void SetPath(CStringWide path) { m_strPath = path; }

protected:
	CStringWide m_strPath;
	EFileMode m_mode;
};

#endif //__Utility_IFile_H__
