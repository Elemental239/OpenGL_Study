#ifndef __Utility_String_H__
#define __Utility_String_H__

#include <string>

typedef std::string CString;
typedef std::wstring CStringWide;

CStringWide CString2CStringWide(const CString string);

#endif //__Utility_String_H__