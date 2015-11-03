#include "StringImpl.h"

CStringWide CString2CStringWide(const CString string)
{
	CStringWide wideString(string.begin(), string.end());
	return wideString;
}

const char* ToLog(CString input)
{
	return input.c_str();
}

CString ToStr(int input)
{
	return std::to_string(input);
}
