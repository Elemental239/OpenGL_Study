#include "Globals.h"
#include <Catch\include\catch.hpp>
#include <iostream>

class GlobalsTest : public Globals
{
};

TEST_CASE("Globals test", "[Globals][Logic]")
{
	SECTION("NoThrow Creation")
	{
		CHECK_NOTHROW(GlobalsTest::Instance());
	}

	SECTION("NoThrow Creation")
	{
		CHECK_NOTHROW(GlobalsTest::Instance().Init());

	}
}
