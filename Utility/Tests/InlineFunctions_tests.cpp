#include "Catch\include\catch.hpp"
#include "InlineFunctions.h"

TEST_CASE("Utility GetFlagWithPosition()", "[Utility][Various functions]")
{
	SECTION("Get first position set flag")
	{
		int flags = 1;
		REQUIRE(GetFlagWithPosition(flags, 0));
	}

	SECTION("Get first position not setted flag")
	{
		int flags = 2;
		REQUIRE_FALSE(GetFlagWithPosition(flags, 0));
	}

	SECTION("Get 5th position setted flag")
	{
		int flags = (1 << 4) + 2 + 1; // 00010011
		REQUIRE(GetFlagWithPosition(flags, 4));
	}

	SECTION("Get 5th position not-setted flag")
	{
		int flags = (1 << 5) + 2 + 1; // 00100011
		REQUIRE_FALSE(GetFlagWithPosition(flags, 4));
	}

	SECTION("Attempt to get 9th flag")
	{
		int flags = (1 << 5) + 2 + 1; // 00100011
		REQUIRE_FALSE(GetFlagWithPosition(flags, 8));
	}
}

TEST_CASE("Utility GetFlag()", "[Utility][Various functions]")
{
	SECTION("Get first position set flag")
	{
		int flags = 1;
		REQUIRE(GetFlag(flags, 0x01));
	}

	SECTION("Get first position not setted flag")
	{
		int flags = 2;
		REQUIRE_FALSE(GetFlag(flags, 0x01));
	}

	SECTION("Get 4th position setted flag")
	{
		int flags = (1 << 4) + 2 + 1; // 00010011
		REQUIRE(GetFlag(flags, (1 << 4)));
	}

	SECTION("Get 4th position not-setted flag")
	{
		int flags = (1 << 5) + 2 + 1; // 00100011
		REQUIRE_FALSE(GetFlag(flags, (1 << 4)));
	}

	SECTION("Attempt to get 9th flag")
	{
		int flags = (1 << 5) + 2 + 1; // 00100011
		REQUIRE_FALSE(GetFlag(flags, (1 << 9)));
	}
}

TEST_CASE("Utility enumValueToInt()", "[Utility][Various functions]")
{
	SECTION("Old style enum")
	{
		enum TestOldStyleEnum
		{
			OLD_STYLE_NONE = 0,
			OLD_STYLE_SINGLE = 1,
		};

		REQUIRE(enumValueToInt(OLD_STYLE_SINGLE) == 1);
	}

	SECTION("enum class")
	{
		enum class TestEnumClass : int
		{
			NONE = 0,
			SINGLE = 1,
			MANY = 2
		};

		REQUIRE(enumValueToInt(TestEnumClass::MANY) == 2);
	}
}
