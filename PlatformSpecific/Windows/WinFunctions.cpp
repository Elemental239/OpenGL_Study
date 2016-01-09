#include "..\Headers\WinFunctions.h"

#include "StringImpl.h"
#include "Logger.h"
#include <atlbase.h>

static const int MAX_APP_PATH_LENGTH = 1024;

CString8 ConvertStringToPath(CString8 input)
{
	if (input.Length() < 1)
	{
		LOGE("ConvertStringToPath::empty input");
		return CString8();
	}

	input.Trim();

	//at first, convert all '/' with "\\"
	input = input.Replace("/", "\\");

	// Check starting slash presence, ending slash unpresence, length
	if (input[0] != "\\")
		input = "\\" + input;

	int nIter = input.Length() - 1;
	while (nIter >= 0 && input[nIter] == "\\")
	{
		input = input.SubstringReplace(nIter, 1, "");
		nIter -= 1;
	}

	if (input.Length() < 1)
	{
		LOGE("ConvertStringToPath::empty string");
		return CString8();
	}

	//at second, surround all "<word> <word>" with \"
	long nPos = input.Search(" ");
	while (nPos >= 0)
	{
		long leftPos = input.Search("\\", nPos, UTF8::String::SearchDirectionFromRightToLeft);
		long rightPos = input.Search("\\", nPos);

		if (leftPos < 0 || rightPos < 0)
		{
			LOGE("Error searching spaces");
			return input;
		}

		if (input[rightPos - 1] != "\"")
			input = input.Insert(rightPos, "\"");

		if (input[leftPos + 1] != "\"")
			input = input.Insert(leftPos + 1, "\"");

		nPos = input.Search(" ", nPos + 2);
	}

	if (input[0] == "\\")
		input = input.Substring(1);

	return input;
}

CString8 GetAppFilePath()
{
	TCHAR path[MAX_APP_PATH_LENGTH];

	GetCurrentDirectory(sizeof(path), path);

	return LPCTSTR2CString8(path);

    // Will contain exe path
    //HMODULE hModule = GetModuleHandle(NULL);
    //if (hModule != NULL)
    //{
		// When passing NULL to GetModuleHandle, it returns handle of exe itself
	//	GetModuleFileName(hModule, (LPTSTR)path, (sizeof(path))); 

	//	return LPCTSTR2CString8(path);
    //}
    //else
    //{
	//	LOGE("GetAppFilePath(): Error getting app filepath");
	//	return CString8();
    //}
}

LPCWSTR CStringW2LPCWSTR(CStringW inputW)
{
	return inputW.c_str();
}

CStringA LPCTSTR2CStringA(LPCTSTR input)
{
	return CStringA(CT2A(input));
}

CStringW LPCTSTR2CStringW(LPCTSTR input)
{
	return CStringW(CT2W(input));
}

CString8 LPCTSTR2CString8(LPCTSTR input)
{
	CStringW tempW = LPCTSTR2CStringW(input);
	return CStringW2CString8(tempW); //LPCTSTR2CStringA(input);
}

CStringW LPCWSTR2CStringW(LPCWSTR inputW)
{
	return inputW;
}

CString8 CStringW2CString8(CStringW inputW)
{
	if (inputW.empty())
	{
		return CString8();
	}

	LPCWSTR input = inputW.c_str();
	int length = WideCharToMultiByte(CP_UTF8, 0, input, -1, 0, 0, NULL, NULL);

	CString8 str8(length, 1);
	
	WideCharToMultiByte(CP_UTF8, 0, input, -1, str8.ToCharPtr(), length, NULL, NULL);

	return str8;
}

CStringW CString82CStringW(CString8 input8)
{
	if (!input8.Length())
		return CStringW();

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, input8.ToConstCharPtr(), (int)input8.DataLength(), NULL, 0);

    CStringW wstrTo(size_needed, 0);

    MultiByteToWideChar(CP_UTF8, 0, input8.ToConstCharPtr(), (int)input8.DataLength(), &wstrTo[0], size_needed);

    return wstrTo;
}

CString8 CStringA2CString8(CStringA inputA)
{
	return inputA;
}
