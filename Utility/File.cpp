#include "Logger.h"
#include "File.h"
#include "String.h"
#include "Windows/WinFunctions.h"

//CreateDirectory("data\\", NULL); - winapi for creating directories



CFile::CFile(CStringWide path, EFileMode mode): IFile(path, mode) 
{

}

CFile::~CFile()
{

}

void CFile::Open()
{
	MARKER("CFile::Open(%s)", LSTW(m_strPath));

	m_stream.open(m_strPath, MODE_INPUT | MODE_OUTPUT | MODE_BINARY);
}

void CFile::Close()
{
	MARKER("CFile::Close(%s)", LSTW(m_strPath));

	Flush();
	m_stream.close();
}

void CFile::Flush()
{
	MARKER("CFile::Flush(%s)", LSTW(m_strPath));

	m_stream.flush();
}

void CFile::Write(CStringWide data)
{
	//m_stream.write(data.c_str(), data.length());
}

CStringWide CFile::ReadString()
{
	return CStringWide();
}

bool CFile::IsExist()
{
	MARKER("CFile::IsExist(%s)", LSTW(m_strPath));

	m_stream.open(m_strPath, MODE_INPUT);
	bool bResult = m_stream.is_open();
	m_stream.close();

	return bResult;
}
