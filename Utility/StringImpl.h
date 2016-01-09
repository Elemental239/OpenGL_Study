#ifndef __Utility_String_H__
#define __Utility_String_H__

#include "UTF8Strings/String.h"
#include <string>

typedef UTF8::String CString8;

typedef std::string CStringA;
typedef std::wstring CStringW;

#ifdef UNICODE
	typedef CStringW CString;
#else
	typedef CStringA CString;
#endif

CStringA FormatString(const CStringA fmt_str, ...);
//
//CStringA ToStrA(int input);
//CStringA ToStrA(CStringW input);
//
//CStringW ToStrW(int input);
//CStringW ToStrA(CStringA input);

#endif //__Utility_String_H__