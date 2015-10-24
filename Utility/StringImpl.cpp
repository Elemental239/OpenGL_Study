#include "StringImpl.h"

CStringWide CString2CStringWide(const CString string)
{
	CStringWide wideString(string.begin(), string.end());
	return wideString;
}

LPCWSTR CString2LPCWSTR(const CString string)
{
	return (LPCWSTR)CString2CStringWide(string).c_str();
}
