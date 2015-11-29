#include "StringImpl.h"
#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include "utf8_cpp/source/utf8.h"
#include <vector>

std::locale russianLocalization("Russian");
std::locale englishUSALocalization("en-US");

//CStringWide CString2CStringWide(const CString string, const std::locale& loc)
//{
//	if (string.empty())
//		return std::wstring();
//
//	typedef std::string::traits_type::state_type state_type;
//	typedef std::codecvt<wchar_t, char, state_type> CVT;
//	const CVT& cvt = std::use_facet<CVT>(loc);
//	std::wstring wide(string.size(), '\0');
//	state_type state = state_type();
//	const char* from_beg = &string[0];
//	const char* from_end = from_beg + string.size();
//	const char* from_nxt;
//	wchar_t* to_beg = &wide[0];
//	wchar_t* to_end = to_beg + wide.size();
//	wchar_t* to_nxt;
//	std::wstring::size_type sz = 0;
//	std::codecvt_base::result r;
//	do
//	{
//		r = cvt.in(state, from_beg, from_end, from_nxt,
//							to_beg,   to_end,   to_nxt);
//		switch (r)
//		{
//		case std::codecvt_base::error:
//			throw std::runtime_error("error converting string to wstring");
//		case std::codecvt_base::partial:
//			sz += to_nxt - to_beg;
//			wide.resize(2*wide.size());
//			to_beg = &wide[sz];
//			to_end = &wide[0] + wide.size();
//			break;
//		case std::codecvt_base::noconv:
//			wide.resize(sz + (from_end-from_beg));
//			std::memcpy(&wide[sz], from_beg, (std::size_t)(from_end-from_beg));
//			r = std::codecvt_base::ok;
//			break;
//		case std::codecvt_base::ok:
//			sz += to_nxt - to_beg;
//			wide.resize(sz);
//			break;
//		}
//	} while (r != std::codecvt_base::ok);
//
//	return wide;
//
//	//CStringWide wideString(string.begin(), string.end());
//	//return wideString;
//}
//
//CString CStringWide2CString(const CStringWide string, const std::locale& loc)
//{
//	if (string.empty())
//		return std::string();
//
//	typedef std::wstring::traits_type::state_type state_type;
//	typedef std::codecvt<wchar_t, char, state_type> CVT;
//
//	const CVT& cvt = std::use_facet<CVT>(loc);
//	std::string narrow(cvt.max_length()*string.size(), '\0');
//	state_type state = state_type();
//
//	const wchar_t* from_beg = &string[0];
//	const wchar_t* from_end = from_beg + string.size();
//	const wchar_t* from_nxt;
//	char* to_beg = &narrow[0];
//	char* to_end = to_beg + narrow.size();
//	char* to_nxt;
//
//	std::string::size_type sz = 0;
//	std::codecvt_base::result r;
//	do
//	{
//		r = cvt.out(state, from_beg, from_end, from_nxt,
//							to_beg,   to_end,   to_nxt);
//		switch (r)
//		{
//		case std::codecvt_base::error:
//			throw std::runtime_error("error converting wstring to string");
//
//		case std::codecvt_base::partial:
//			sz += to_nxt - to_beg;
//			narrow.resize(2*narrow.size());
//			to_beg = &narrow[sz];
//			to_end = &narrow[0] + narrow.size();
//			break;
//
//		case std::codecvt_base::noconv:
//			narrow.resize(sz + (from_end-from_beg)*sizeof(wchar_t));
//			std::memcpy(&narrow[sz], from_beg,(from_end-from_beg)*sizeof(wchar_t));
//			r = std::codecvt_base::ok;
//			break;
//
//		case std::codecvt_base::ok:
//			sz += to_nxt - to_beg;
//			narrow.resize(sz);
//			break;
//		}
//	} while (r != std::codecvt_base::ok);
//
//	return narrow;
//	//CString oneByteString(string.begin(), string.end());
//	//return oneByteString;
//}


bool CString2CStringWide(const CString input, CStringWide& output)
{
	output.clear();
	utf8::utf8to16(input.begin(), input.end(), back_inserter(output));
}

bool CStringWide2CString(const CStringWide input, CString& output)
{
	output.clear();
	utf8::utf16to8(input.begin(), input.end(), back_inserter(output));
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
