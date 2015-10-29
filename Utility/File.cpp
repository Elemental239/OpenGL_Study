#include "Logger.h"
#include "File.h"
#include "String.h"
#include "Windows/WinFunctions.h"

//CreateDirectory("data\\", NULL); - winapi for creating directories

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

	m_stream.open(m_strPath, std::fstream::in);
	bool bResult = m_stream.is_open();
	m_stream.close();

	return bResult;
}
