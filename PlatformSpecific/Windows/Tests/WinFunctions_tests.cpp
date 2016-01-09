#include "Catch/include/catch.hpp"
#include "Headers/WinFunctions.h"

TEST_CASE("ConvertStringToPath() test", "[Windows][String][Path]")
{
	SECTION("Nothing to do")
	{
		CStringA path = "\\input.txt";
		CString8 output = ConvertStringToPath(CStringA2CString8(path));

		REQUIRE(path == output);
	}

	SECTION("All is ok")
	{
		CStringA path = "\\\"my documents\"\\input.txt";
		CString8 output = ConvertStringToPath(CStringA2CString8(path));

		REQUIRE(path == output);
	}

	SECTION("Just change / to \\")
	{
		CStringA path = "/documents/input.txt";
		CStringA rightOutput = "\\documents\\input.txt";
		CString8 output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("Just escape path with space")
	{
		CStringA path = "\\my documents\\input.txt";
		CStringA rightOutput = "\\\"my documents\"\\input.txt";
		CString8 output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("escape space & change /")
	{
		CStringA path = "/my documents/kvaka_dom/input.txt";
		CStringA rightOutput = "\\\"my documents\"\\kvaka_dom\\input.txt";
		CString8 output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("String with no start slash")
	{
		CStringA path = "input.txt";
		CStringA rightOutput = "\\input.txt";
		CString8 output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("Wrong arg: empty arg")
	{
		REQUIRE(ConvertStringToPath("") == CStringA(""));
	}

	SECTION("Wrong arg: / input")
	{
		REQUIRE(ConvertStringToPath("/") == CStringA(""));
		REQUIRE(ConvertStringToPath("\\") == CStringA(""));
	}

	SECTION("Arg with / at the end")
	{
		CStringA path = "/documents/input.txt/";
		CStringA rightOutput = "\\documents\\input.txt";
		CString8 output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}
}
