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
	IFile(CString path, EFileMode mode): m_mode(mode) { m_strPath = ConvertStringToPath(path); }
	~IFile() { }

	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Flush() = 0;
	virtual void Write(CString data) = 0;
	virtual CString ReadString() = 0;

	virtual bool IsExist() = 0;

protected:
	CString m_strPath;
	EFileMode m_mode;
};

#endif //__Utility_IFile_H__
