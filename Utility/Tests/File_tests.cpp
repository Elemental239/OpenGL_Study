#include "Catch/include/catch.hpp"
#include "Headers/WinFunctions.h"
#include "File.h"
#include "Logger.h"
#include "Globals.h"

#include <fstream>

TEST_CASE("File test", "[Utility][File]")
{
	SECTION("Check file existance - true")
	{
		CFile file("TEXT.txt", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == true);
	}

	SECTION("Check file existance - false")
	{
		CFile file("nothing.nothing", FILE_MODE_OPEN);
		REQUIRE(file.IsExist() == false);
	}
}
