#include "Logger.h"
#include "Catch\include\catch.hpp"
#include <iostream>

class LoggerTest : public Logger
{
public:
	LoggerTest() : m_pLastLog(NULL) { }
	~LoggerTest() { if (m_pLastLog) delete[] m_pLastLog; }

	virtual void WriteString(char* buffer) override;
	char* GetLastLog() { return m_pLastLog; }

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

	SECTION("Fail test")
	{
		REQUIRE(1 != 1);
	}
}

