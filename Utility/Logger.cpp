#include "Logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

Logger log_instance;

#define CATEGORY_MARKER_SIZE 3
#define MAX_INDENT_SIZE 10
#define MAX_PURE_LOG_SIZE ((MAX_LOG_STRING_LENGTH) - (CATEGORY_MARKER_SIZE) - (MAX_INDENT_SIZE))

const char LogCategories[4] = { 'V', 'I', 'W', 'E' };
int nCurrentIndent = 0;

void Logger::Write(LOG_CATEGORY category, const char* log, ...)
{
	va_list args;
	va_start(args, log);
	WriteVA(category, nCurrentIndent, log, args);
	va_end(args);
}

void Logger::WriteVA(LOG_CATEGORY category, int indent, const char* log, va_list args)
{
	char buffer[MAX_LOG_STRING_LENGTH];
	ConstructLogString(buffer, category, indent, log, args);
	WriteString(buffer);
}

void Logger::ConstructLogString(char* buffer, LOG_CATEGORY category, int indent, const char* log, va_list args)
{
	char logString[MAX_PURE_LOG_SIZE];

	//_snprintf_s(logString, MAX_PURE_LOG_SIZE, _TRUNCATE, log, args);	// El239: doesn't work with "%f, %s"
	vsprintf(logString, log, args);

	AddBeginning(buffer, category, indent);
	memcpy(buffer + CATEGORY_MARKER_SIZE + indent, logString, MAX_PURE_LOG_SIZE);
	AddEnding(buffer, category, indent);
}

void Logger::AddBeginning(char* buffer, LOG_CATEGORY category, int indent)
{
	if (indent > MAX_INDENT_SIZE)
		indent = MAX_INDENT_SIZE;

	for (int i = 0; i < indent; i++)
	{
		if (i < indent - 1)
			buffer[i] = '|';
		else
			buffer[i] = ' ';
	}

	if (indent > 0)
		buffer[0] = '.';

	buffer[indent] = '[';
	buffer[indent + 1] = LogCategories[category];
	buffer[indent + 2] = ']';
}

void Logger::AddEnding(char* buffer, LOG_CATEGORY category, int indent)
{
	buffer[MAX_LOG_STRING_LENGTH - 1] = '0';

	if (category == LOG_CATEGORY_VERBOSE)
		memmove(buffer + indent, buffer + indent + 3, strlen(buffer) - indent - 3 + 1);
}

void Logger::WriteString(char* buffer)
{
	//fprintf(stdout, buffer);
	//fprintf(stdout, "\n");

	WCHAR wide_buffer[MAX_LOG_STRING_LENGTH];
	MultiByteToWideChar(0, 0, buffer, MAX_LOG_STRING_LENGTH, wide_buffer, MAX_LOG_STRING_LENGTH);
	OutputDebugString(wide_buffer);
	OutputDebugString(L"\n");
}

Marker::Marker(const char* log, ...)
{
	va_list args;
	va_start(args, log);
	
	ConstructLogString(buffer, LOG_CATEGORY_VERBOSE, nCurrentIndent, log, args);
	WriteString(buffer);

	va_end(args);
	nCurrentIndent++;
}

Marker::~Marker()
{
	for (size_t i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '>')
		{
			buffer[i] = '<';
			buffer[i + 1] = '<';
			break;
		}
	}
	
	WriteString(buffer);
	nCurrentIndent--;
}

void Marker::AddBeginning(char* buffer, LOG_CATEGORY category, int indent)
{
	__super::AddBeginning(buffer, category, indent);

	buffer[indent] = '>';
	buffer[indent + 1] = '>';
	buffer[indent + 2] = '[';
}

void Marker::AddEnding(char* buffer, LOG_CATEGORY category, int indent)
{
	int stringLength = strlen(buffer);

	if (stringLength < MAX_LOG_STRING_LENGTH - 1)
	{
		buffer[stringLength] = ']';
		buffer[stringLength + 1] = 0;
	}
	else
	{
		buffer[stringLength - 1] = ']';
		buffer[stringLength] = 0;
	}
}
