#ifndef __Utility_File_H__
#define __Utility_File_H__

#include "IFile.h"

class CFile : public IFile
{
public:
	CFile(CString path, EFileMode mode);
	~CFile();

	virtual void Open() override;
	virtual void Close() override;
	virtual void Flush() override;
	virtual void Write(CString data) override;
	virtual CString ReadString() override;

	virtual bool IsExist() override;
};

#endif //__Utility_File_H__
