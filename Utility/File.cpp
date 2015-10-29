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
	MARKER("CFile::Open(%s)", ToLog(m_strPath));

	m_stream.open(m_strPath, MODE_INPUT | MODE_OUTPUT | MODE_BINARY);
}

void CFile::Close()
{
	MARKER("CFile::Close(%s)", ToLog(m_strPath));

	Flush();
	m_stream.close();
}

void CFile::Flush()
{
	MARKER("CFile::Flush(%s)", ToLog(m_strPath));

	m_stream.flush();
}

void CFile::Write(CString data)
{
	m_stream.write(data.c_str(), data.length());
}

CString CFile::ReadString()
{
	return "";
}

bool CFile::IsExist()
{
	MARKER("CFile::IsExist(%s)", ToLog(m_strPath));

	m_stream.open(m_strPath, MODE_INPUT);
	bool bResult = m_stream.is_open();
	m_stream.close();

	return bResult;
}
