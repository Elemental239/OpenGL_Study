#ifndef __Utility_String_H__
#define __Utility_String_H__

#include <string>
#include <locale>

typedef std::string CString;
typedef std::wstring CStringWide;

extern std::locale russianLocalization;
extern std::locale englishUSALocalization;

CStringWide CString2CStringWide(const CString string, const std::locale& loc = std::locale::classic());
CString CStringWide2CString(const CStringWide string, const std::locale& loc = std::locale::classic());
CString FormatString(const CString fmt_str, ...);

CString ToStr(int input);

#endif //__Utility_String_H__