#include "Catch\include\catch.hpp"
#include "SharedPtr.h"

class TestClass
{
public:
	TestClass(int n) : m_nField(n) {}
	int GetField() { return m_nField; }

private:
	int m_nField;
};

TEST_CASE("SharedPtr test", "[Utility][CSharedPtr]")
{
	CSharedPtr<TestClass> spInt(new TestClass(10));
	
	SECTION("Access SharedPtr")
	{
		REQUIRE(spInt->GetField() == 10);
	}

	SECTION("Access raw pointer")
	{
		REQUIRE_FALSE(spInt.GetPointer() == nullptr);
		REQUIRE(spInt.GetPointer()->GetField() == 10);
	}

	SECTION("Proper count number")
	{
		REQUIRE(spInt.GetCount() == 1);
		{
			CSharedPtr<TestClass> spOther = spInt;
			REQUIRE(spInt.GetCount() == 2);
		}
		REQUIRE(spInt.GetCount() == 1);
	}

	SECTION("Cast to raw pointer")
	{
		TestClass* pInt;
		{
			CSharedPtr<TestClass> spInt2(new TestClass(12));
			pInt = spInt2;

			REQUIRE(pInt->GetField() == 12);
		}

		REQUIRE_FALSE(pInt->GetField() == 12);
	}

	SECTION("Operator ==")
	{
		CSharedPtr<TestClass> spIntSame = spInt;
		CSharedPtr<TestClass> spIntDifferent = new TestClass(10);

		REQUIRE(spInt == spIntSame);
		REQUIRE_FALSE(spInt == spIntDifferent);
	}
}