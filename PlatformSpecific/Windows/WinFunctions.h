#ifndef __Specific_WinFunctions_H__
#define __Specific_WinFunctions_H__

#include <windows.h>
#include "StringImpl.h"

LPCWSTR CString2LPCWSTR(const CString string);
CString ConvertStringToPath(CString input);

#endif //__Specific_WinFunctions_H__