#include "Catch/include/catch.hpp"
#include "Headers/WinFunctions.h"
#include "File.h"
#include "Logger.h"
#include "Globals.h"

TEST_CASE("File test", "[Utility][File]")
{
	SECTION("Checks")
	{
		CFile file("Labirinth.exe", FILE_MODE_OPEN);
		LOG("%d", file.IsExist());

		file.SetPath("Labirinth.exe");
		LOG("%d", file.IsExist());
		file.SetPath(CGlobals::Instance().GetAppFilePath() + "\\Labirinth.exe");
		LOG("%d", file.IsExist());
	}

	SECTION("Check file existance - true")
	{
		CFile file("Labirinth.exe", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == true);
	}

	SECTION("Check file existance - false")
	{
		CFile file("nothing.bat", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == false);
	}
}
