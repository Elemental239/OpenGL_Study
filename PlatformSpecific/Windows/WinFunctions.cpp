#include "WinFunctions.h"

#include "StringImpl.h"
#include "Logger.h"

LPCWSTR CString2LPCWSTR(const CString string)
{
	return (LPCWSTR)CString2CStringWide(string).c_str();
}


CString ConvertStringToPath(CString input)
{
	if (input.length() < 1)
	{
		LOGE("ConvertStringToPath::empty input");
		return "";
	}

	//at first, convert all '/' with "\\"
	size_t nPos = input.find('/');
	while (nPos != std::string::npos)
	{
		input.replace(nPos, 1, "\\");
		nPos = input.find('/', nPos + 1);
	}

	// Check starting slash presence, ending slash unpresence, length
	if (input[0] != '\\')
		input.insert(0, "\\");

	int nIter = input.length() - 1;
	while (nIter >= 0 && input[nIter] == '\\')
	{
		input.erase(nIter, 1);
		nIter -= 1;
	}

	if (input.length() < 1)
	{
		LOGE("ConvertStringToPath::empty string");
		return "";
	}

	//at second, surround all "<word> <word>" with \"
	nPos = input.find(" ");
	while (nPos != std::string::npos)
	{
		int leftPos = input.rfind("\\", nPos);
		int rightPos = input.find("\\", nPos);

		if (leftPos == std::string::npos || rightPos == std::string::npos)
		{
			LOGE("Error searching spaces");
			return input;
		}

		if (input.substr(rightPos - 1, 1) != "\"")
			input.insert(rightPos, "\"");

		if (input.substr(leftPos + 1, 1) != "\"")
			input.insert(leftPos + 1, "\"");

		nPos = input.find(" ", nPos + 2);
	}

	return input;
}