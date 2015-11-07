#include "StringImpl.h"
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr

CStringWide CString2CStringWide(const CString string)
{
	CStringWide wideString(string.begin(), string.end());
	return wideString;
}

const char* ToLog(const CString& input)
{
	const char* output = input.c_str();
	return output;
}

CString ToStr(int input)
{
	return std::to_string(input);
}

CString FormatString(const CString fmt_str, ...)
{
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy_s(&formatted[0], n, fmt_str.c_str()); // El239: was strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
		final_n = vsnprintf_s(&formatted[0], n, _TRUNCATE, fmt_str.c_str(), ap);	// El239: was final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return CString(formatted.get());
}
