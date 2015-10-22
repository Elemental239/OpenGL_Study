#include "Logger.h"
#include "File.h"
#include "String.h"
#include <windows.h>

CFile::CFile(CString path, EFileMode mode): IFile(path, mode) 
{

}

CFile::~CFile()
{

}

void CFile::Open()
{
	MARKER("CFile::Open(%s)", m_strPath);

	
}

void CFile::Close()
{
	MARKER("CFile::Close(%s)", m_strPath);
}

void CFile::Flush()
{
	MARKER("CFile::Flush(%s)", m_strPath);
}

void CFile::Write(CString data)
{
	
}

CString CFile::ReadString()
{
	return "";
}

bool CFile::IsExist()
{
	MARKER("CFile::IsExist(%s)", m_strPath);

	//return GetFileAttributes(m_strPath.c_str());

	return false;
}
