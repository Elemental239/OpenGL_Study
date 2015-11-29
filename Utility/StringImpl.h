#ifndef __Utility_String_H__
#define __Utility_String_H__

#include <string>
#include <locale>
#include <vector>

typedef std::string CString;						//UTF-8
typedef std::vector<unsigned short> CStringWide;	//UTF-16

extern std::locale russianLocalization;
extern std::locale englishUSALocalization;

//CStringWide CString2CStringWide(const CString string, const std::locale& loc = std::locale::classic());
//CString CStringWide2CString(const CStringWide string, const std::locale& loc = std::locale::classic());

bool CString2CStringWide(const CString input, CStringWide& output);
bool CStringWide2CString(const CStringWide input, CString& output);
CString FormatString(const CString fmt_str, ...);

CString ToStr(int input);

#endif //__Utility_String_H__