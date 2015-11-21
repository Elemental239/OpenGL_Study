#include "Catch\include\catch.hpp"
#include "Windows/WinFunctions.h"
#include "File.h"
#include "Logger.h"
#include "Globals.h"

TEST_CASE("File test", "[Utility][File]")
{
	SECTION("Checks")
	{
		CFile file(L"Labirinth.exe", FILE_MODE_OPEN);
		LOG("%d", file.IsExist());

		file.SetPath(L"Labirinth.exe");
		LOG("%d", file.IsExist());
		file.SetPath(CGlobals::Instance().GetAppFilePath() + L"Labirinth.exe");
		LOG("%d", file.IsExist());
	}

	SECTION("Check file existance - true")
	{
		CFile file(L"Labirinth.exe", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == true);
	}

	SECTION("Check file existance - false")
	{
		CFile file(L"nothing.bat", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == false);
	}
}
