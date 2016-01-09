#ifndef __Specific_WinFunctions_H__
#define __Specific_WinFunctions_H__

#include <windows.h>
#include "StringImpl.h"

CString8 ConvertStringToPath(CString8 input);

CString8 GetAppFilePath();

CStringA LPCTSTR2CStringA(LPCTSTR input);
CStringW LPCTSTR2CStringW(LPCTSTR input);
CString8 LPCTSTR2CString8(LPCTSTR input);

LPCWSTR CStringW2LPCWSTR(CStringW inputW); 
CStringW LPCWSTR2CStringW(LPCWSTR inputW); 

CString8 CStringW2CString8(CStringW inputW);
CStringW CString82CStringW(CString8 input8);

CString8 CStringA2CString8(CStringA inputA);

#endif //__Specific_WinFunctions_H__