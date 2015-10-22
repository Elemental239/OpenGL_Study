#ifndef __Utility_String_H__
#define __Utility_String_H__

#include <string>
#include <windows.h>

#define CString std::string
#define CStringWide std::wstring

CStringWide CString2CStringWide(const CString string)
{
	CStringWide wideString(string.begin(), string.end());
	return wideString;
}

LPCWSTR CString2LPCWSTR(const CString string)
{
	return (LPCWSTR)CString2CStringWide(string).c_str();
}

#endif //__Utility_String_H__