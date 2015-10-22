#include "Logger.h"
#include "File.h"
#include "String.h"

CFile::CFile(CString path, EFileMode mode): IFile(path, mode) 
{

}

CFile::~CFile()
{

}

void CFile::Open()
{
}

void CFile::Close()
{
}

void CFile::Flush()
{
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
	return false;
}
