#include "Globals.h"
#include <Catch\include\catch.hpp>
#include <iostream>

class CGlobalsTest : public CGlobals
{
};

TEST_CASE("Globals test", "[Globals][Logic]")
{
	SECTION("NoThrow Creation")
	{
		CHECK_NOTHROW(CGlobalsTest::Instance());
	}

	SECTION("NoThrow Creation")
	{
		CHECK_NOTHROW(CGlobalsTest::Instance().Init());
	}
}
