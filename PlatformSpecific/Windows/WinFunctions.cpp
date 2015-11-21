#include "WinFunctions.h"

#include "StringImpl.h"
#include "Logger.h"

static const int MAX_APP_PATH_LENGTH = 1024;

LPCWSTR CString2LPCWSTR(const CString string)
{
	return (LPCWSTR)CString2CStringWide(string).c_str();
}

CString LPCSTR2CString(LPCSTR string)
{
	if (string == NULL)
		return CString();

	return CString(string);
}

CString LPCWSTR2CString(LPCWSTR string)
{
	if (string == NULL)
		return CString();

	CStringWide wideString = CStringWide(string);
	return CStringWide2CString(wideString);
}

CString LPCTSTR2CString(LPCTSTR string)
{
	if (string == NULL)
		return CString();

	if (sizeof(TCHAR) == sizeof(wchar_t))
		return LPCWSTR2CString((LPCWSTR)string);
	else
		return LPCSTR2CString((LPCSTR)string);
}

CStringWide LPCSTR2CStringWide(LPCSTR string)
{
	if (string == NULL)
		return CStringWide();

	return CString2CStringWide(LPCSTR2CString(string));
}

CStringWide LPCWSTR2CStringWide(LPCWSTR string)
{
	if (string == NULL)
		return CStringWide();

	return CStringWide(string);
}

CStringWide LPCTSTR2CStringWide(LPCTSTR string)
{
	if (string == NULL)
		return CStringWide();

	if (sizeof(TCHAR) == sizeof(wchar_t))
		return LPCWSTR2CStringWide((LPCWSTR)string);
	else
		return LPCSTR2CStringWide((LPCSTR)string);
}

CString ConvertStringToPath(CString input)
{
	return CStringWide2CString(ConvertStringToPath(CString2CStringWide(input)));
}

CStringWide ConvertStringToPath(CStringWide input)
{
	if (input.length() < 1)
	{
		LOGE("ConvertStringToPath::empty input");
		return CStringWide();
	}

	//at first, convert all '/' with "\\"
	size_t nPos = input.find('/');
	while (nPos != std::string::npos)
	{
		input.replace(nPos, 1, L"\\");
		nPos = input.find('/', nPos + 1);
	}

	// Check starting slash presence, ending slash unpresence, length
	if (input[0] != '\\')
		input.insert(0, L"\\");

	int nIter = input.length() - 1;
	while (nIter >= 0 && input[nIter] == '\\')
	{
		input.erase(nIter, 1);
		nIter -= 1;
	}

	if (input.length() < 1)
	{
		LOGE("ConvertStringToPath::empty string");
		return L"";
	}

	//at second, surround all "<word> <word>" with \"
	nPos = input.find(L" ");
	while (nPos != std::string::npos)
	{
		int leftPos = input.rfind(L"\\", nPos);
		int rightPos = input.find(L"\\", nPos);

		if (leftPos == std::string::npos || rightPos == std::string::npos)
		{
			LOGE("Error searching spaces");
			return input;
		}

		if (input.substr(rightPos - 1, 1) != L"\"")
			input.insert(rightPos, L"\"");

		if (input.substr(leftPos + 1, 1) != L"\"")
			input.insert(leftPos + 1, L"\"");

		nPos = input.find(L" ", nPos + 2);
	}

	return input;
}

CStringWide GetAppFilePath()
{
	TCHAR path[MAX_APP_PATH_LENGTH];

    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
		// When passing NULL to GetModuleHandle, it returns handle of exe itself
		GetModuleFileName(hModule, (LPTSTR)path, (sizeof(path))); 

		return LPCTSTR2CStringWide(path);
    }
    else
    {
		LOGE("GetAppFilePath(): Error getting app filepath");
		return CStringWide();
    }
}
