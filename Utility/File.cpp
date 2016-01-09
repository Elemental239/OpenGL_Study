#include "Logger.h"
#include "File.h"
#include "String.h"
#include "Headers/WinFunctions.h"

//CreateDirectory("data\\", NULL); - winapi for creating directories



CFile::CFile(CString8 path, EFileMode mode): IFile(path, mode) 
{

}

CFile::~CFile()
{

}

void CFile::Open()
{
	MARKER("CFile::Open(%s)", m_strPath.ToCharPtr());

	m_stream.open(CString82CStringW(m_strPath), MODE_INPUT | MODE_OUTPUT | MODE_BINARY);
}

void CFile::Close()
{
	MARKER("CFile::Close(%s)", m_strPath.ToCharPtr());

	Flush();
	m_stream.close();
}

void CFile::Flush()
{
	MARKER("CFile::Flush(%s)", m_strPath.ToCharPtr());

	m_stream.flush();
}

void CFile::Write(CString8 data)
{
	//m_stream.write(data.c_str(), data.length());
}

CString8 CFile::ReadString()
{
	return CString8();
}

bool CFile::IsExist()
{
	MARKER("CFile::IsExist(%s)", m_strPath.ToCharPtr());

	m_stream.open(CString82CStringW(m_strPath), MODE_INPUT);
	bool bResult = m_stream.is_open();
	m_stream.close();

	return bResult;
}
