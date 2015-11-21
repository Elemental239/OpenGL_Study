#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch\include\catch.hpp"
#include "Catch\include\reporters\catch_reporter_console.hpp"
//#include <Catch\include\reporters\catch_reporter_teamcity.hpp>
//#include <Catch\include\reporters\catch_reporter_compact.hpp>
//#include <Catch\include\reporters\catch_reporter_junit.hpp>

int static FailFunc()
{
	return 0;
}

TEST_CASE("Catch test", "[Catch]")
{
	int i = 1;
	SECTION("Ok test")
	{
		REQUIRE(i == 1);
	}

	SECTION("Fail test")
	{
		REQUIRE(i == FailFunc());
	}

	SECTION("Fail2")
	{
		int a = i - 1;
		REQUIRE_FALSE(a == FailFunc());
	}
}
