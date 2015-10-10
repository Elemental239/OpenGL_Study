#include "Logger.h"
#include "Catch\include\catch.hpp"
#include <iostream>

class LoggerTest : public Logger
{
public:
	LoggerTest() : m_pLastLog(NULL) { }
	~LoggerTest() { if (m_pLastLog) delete[] m_pLastLog; }

	char* GetLastLog() { return m_pLastLog; }

protected:
	virtual void WriteString(char* buffer) override;

private:
	char* m_pLastLog;
};

void LoggerTest::WriteString(char* buffer)
{
	m_pLastLog = new char[strlen(buffer) + 1];
	memcpy(m_pLastLog, buffer, strlen(buffer) + 1);
}

TEST_CASE("Catch test", "[Catch]")
{
	SECTION("Ok test")
	{
		REQUIRE(1 == 1);
	}
}

TEST_CASE_METHOD(LoggerTest, "Log system test", "[Utility][Logger]")
{
	SECTION("Basic text")
	{
		char* hello = "Hello!";
		Write(LOG_CATEGORY_VERBOSE, "Hello!");
		REQUIRE(memcmp(GetLastLog(), hello, strlen(hello)) == 0);
	}

	SECTION("Text with numbers")
	{
		char* hello1 = "Hello1";
		Write(LOG_CATEGORY_VERBOSE, "Hello%d", 1);
		REQUIRE(memcmp(GetLastLog(), hello1, strlen(hello1)) == 0);
	}

	SECTION("Text with modifiers")
	{
		char* testString = "Hello1_2_World!";
		Write(LOG_CATEGORY_VERBOSE, "Hello%d_%d_%s!", 1, 2, "World!");
		REQUIRE(memcmp(GetLastLog(), testString, strlen(testString)) == 0);
	}

	SECTION("Text with category")
	{
		char* testString = "[E]Hello!";
		Write(LOG_CATEGORY_ERROR, "Hello!");
		REQUIRE(memcmp(GetLastLog(), testString, strlen(testString)) == 0);
	}
	
	SECTION("Text with category and modifiers")
	{
		char* testString = "[E]Hello!";
		Write(LOG_CATEGORY_ERROR, "Hello%c", '!');
		REQUIRE(memcmp(GetLastLog(), testString, strlen(testString)) == 0);
	}
}
