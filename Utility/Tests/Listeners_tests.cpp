#include <Catch\include\catch.hpp>
#include "Listeners.h"
#include "SharedPtr.h"

class TestListener
{
public:
	TestListener() : m_nWork(0) {}

	void Work() { m_nWork = 5; }
	void WorkHard(int n) { m_nWork = n; }
	int GetWork() { return m_nWork; }

private:
	int m_nWork;
};

class AdditionalTestListener
{
public:
	AdditionalTestListener() : m_nWork(0) {}

	void AWork() { m_nWork = 5; }
	void AWorkHard(int n) { m_nWork = n; }
	int GetWork() { return m_nWork; }

private:
	int m_nWork;
};

class TestHolder
{
public:
	DECLARE_LISTENERS(TestListener);
	DECLARE_ADDITIONAL_LISTENERS(AdditionalTestListener);

	void Call() { CALL_LISTENERS(Work()); }
	void CallHard(int nWork) { CALL_LISTENERS(WorkHard(nWork)); }

	void ACall() { CALL_ADDITIONAL_LISTENERS(AdditionalTestListener, AWork()); }
	void ACallHard(int nWork) { CALL_ADDITIONAL_LISTENERS(AdditionalTestListener, AWorkHard(nWork)); }

	int GetListenersNumber() { return m__listeners.size(); }
};

TEST_CASE("One listener test", "[Utility][Listeners]")
{
	CSharedPtr<TestListener> spListener1 = new TestListener;
	TestHolder holder;
	holder.RegisterListener(spListener1);
	
	SECTION("Call one void")
	{
		holder.Call();
		REQUIRE(spListener1->GetWork() == 5);
	}

	SECTION("Call int function")
	{
		holder.CallHard(3);
		REQUIRE(spListener1->GetWork() == 3);
	}

	SECTION("Unregister")
	{
		holder.UnregisterListener(spListener1);
		holder.Call();
		REQUIRE(spListener1->GetWork() == 0);
	}

	SECTION("Double register")
	{
		holder.RegisterListener(spListener1);

		REQUIRE(holder.GetListenersNumber() == 1);
	}

	SECTION("Double unregister")
	{
		holder.UnregisterListener(spListener1);
		REQUIRE(holder.GetListenersNumber() == 0);
		REQUIRE_NOTHROW(holder.UnregisterListener(spListener1));
	}
}

TEST_CASE("Two listeners test", "[Utility][Listeners]")
{
	CSharedPtr<TestListener> spListener1 = new TestListener;
	CSharedPtr<TestListener> spListener2 = new TestListener;
	TestHolder holder;
	holder.RegisterListener(spListener1);
	holder.RegisterListener(spListener2);

	SECTION("Call 2 void")
	{
		holder.Call();
		REQUIRE(spListener1->GetWork() == 5);
		REQUIRE(spListener2->GetWork() == 5);
	}

	SECTION("call 2 int")
	{
		holder.CallHard(3);
		REQUIRE(spListener1->GetWork() == 3);
		REQUIRE(spListener2->GetWork() == 3);
	}

	SECTION("1 Unregister")
	{
		REQUIRE(holder.GetListenersNumber() == 2);
		holder.UnregisterListener(spListener1);
		holder.Call();
		REQUIRE(spListener1->GetWork() == 0);
		REQUIRE(spListener2->GetWork() == 5);
	}
}

TEST_CASE("Two listeners types test", "[Utility][Listeners]")
{
	TestHolder holder;
	
	CSharedPtr<TestListener> spListener = new TestListener;
	holder.RegisterListener(spListener);

	CSharedPtr<AdditionalTestListener> spListenerA = new AdditionalTestListener;
	holder.RegisterListener(spListenerA);

	SECTION("Call base listener - void function")
	{
		holder.Call();
		REQUIRE(spListener->GetWork() == 5);
		REQUIRE(spListenerA->GetWork() == 0);
	}

	SECTION("Call additional listener - void function")
	{
		holder.ACall();
		REQUIRE(spListener->GetWork() == 0);
		REQUIRE(spListenerA->GetWork() == 5);
	}

	SECTION("Call base listener - int function")
	{
		holder.CallHard(3);
		REQUIRE(spListener->GetWork() == 3);
		REQUIRE(spListenerA->GetWork() == 0);
	}

	SECTION("Call additional listener - int function")
	{
		holder.ACallHard(2);
		REQUIRE(spListener->GetWork() == 0);
		REQUIRE(spListenerA->GetWork() == 2);
	}
}
