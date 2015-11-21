#ifndef __Specific_WinFunctions_H__
#define __Specific_WinFunctions_H__

#include <windows.h>
#include "StringImpl.h"

LPCWSTR CString2LPCWSTR(const CString string);
CString LPCSTR2CString(LPCSTR string);
CString LPCWSTR2CString(LPCWSTR string);
CString LPCTSTR2CString(LPCTSTR string);

CStringWide LPCSTR2CStringWide(LPCSTR string);
CStringWide LPCWSTR2CStringWide(LPCWSTR string);
CStringWide LPCTSTR2CStringWide(LPCTSTR string);


CString ConvertStringToPath(CString input);
CStringWide ConvertStringToPath(CStringWide input);
CStringWide GetAppFilePath();

#endif //__Specific_WinFunctions_H__