#include "Catch\include\catch.hpp"
#include "Windows/WinFunctions.h"

TEST_CASE("ConvertStringToPath() test", "[Windows][String][Path]")
{
	SECTION("Nothing to do")
	{
		CString path = "\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(path == output);
	}

	SECTION("All is ok")
	{
		CString path = "\\\"my documents\"\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(path == output);
	}

	SECTION("Just change / to \\")
	{
		CString path = "/documents/input.txt";
		CString rightOutput = "\\documents\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("Just escape path with space")
	{
		CString path = "\\my documents\\input.txt";
		CString rightOutput = "\\\"my documents\"\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("escape space & change /")
	{
		CString path = "/my documents/kvaka_dom/input.txt";
		CString rightOutput = "\\\"my documents\"\\kvaka_dom\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("String with no start slash")
	{
		CString path = "input.txt";
		CString rightOutput = "\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}

	SECTION("Wrong arg: empty arg")
	{
		REQUIRE(ConvertStringToPath("") == CString(""));
	}

	SECTION("Wrong arg: / input")
	{
		REQUIRE(ConvertStringToPath("/") == CString(""));
		REQUIRE(ConvertStringToPath("\\") == CString(""));
	}

	SECTION("Arg with / at the end")
	{
		CString path = "/documents/input.txt/";
		CString rightOutput = "\\documents\\input.txt";
		CString output = ConvertStringToPath(path);

		REQUIRE(rightOutput == output);
	}
}
