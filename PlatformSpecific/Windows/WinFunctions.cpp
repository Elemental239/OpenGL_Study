#include "WinFunctions.h"

#include "StringImpl.h"
#include "Logger.h"

LPCWSTR CString2LPCWSTR(const CString string)
{
	return (LPCWSTR)CString2CStringWide(string).c_str();
}


CString ConvertStringToPath(CString input)
{
	//at first, convert all '/' with "\\"
	size_t nPos = input.find("/");
	while (nPos != std::string::npos)
	{
		input.replace(nPos, 1, "\\");
		nPos = input.find("/", nPos + 1);
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

		input.insert(leftPos, "\"");
		input.insert(rightPos - 1, "\"");

		nPos = input.find(" ");
	}
}