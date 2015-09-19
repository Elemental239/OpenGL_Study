#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>
#include "UtilityMacros.h"

enum LOG_CATEGORY
{
	LOG_CATEGORY_VERBOSE,
	LOG_CATEGORY_INFO,
	LOG_CATEGORY_WARNING,
	LOG_CATEGORY_ERROR
};

#define LOG(...) BASE_LOGGER(LOG_CATEGORY_VERBOSE, __VA_ARGS__)
#define LOGI(...) BASE_LOGGER(LOG_CATEGORY_INFO, __VA_ARGS__)
#define LOGW(...) BASE_LOGGER(LOG_CATEGORY_WARNING, __VA_ARGS__)
#define LOGE(...) BASE_LOGGER(LOG_CATEGORY_ERROR, __VA_ARGS__)

#define MARKER(...) BASE_MARKER(__VA_ARGS__)
#define MARKERI(...) BASE_MARKER(__VA_ARGS__)
#define MARKERW(...) BASE_MARKER(__VA_ARGS__)
#define MARKERE(...) BASE_MARKER(__VA_ARGS__)

#define BASE_LOGGER(...) log_instance.Write(__VA_ARGS__)
#define BASE_MARKER(...) Marker CONCAT(m,LINE)(__VA_ARGS__)

#define MAX_LOG_STRING_LENGTH 256

class Logger
{
public:
	Logger() {}
	virtual ~Logger() {}

	void Write(LOG_CATEGORY category, const char* log, ...);

protected:
	void WriteVA(LOG_CATEGORY category, int indent, const char* log, va_list args);
	virtual void AddBeginning(char* buffer, LOG_CATEGORY category, int indent);
	virtual void AddEnding(char* buffer, LOG_CATEGORY category, int indent);
	void ConstructLogString(char* buffer, LOG_CATEGORY category, int indent, const char* log, va_list args);
	virtual void WriteString(char* buffer);
};

class Marker : public Logger
{
public:
	Marker(const char* log, ...);
	~Marker();

private:
	char buffer[MAX_LOG_STRING_LENGTH];

	virtual void AddBeginning(char* buffer, LOG_CATEGORY category, int indent) override;
	virtual void AddEnding(char* buffer, LOG_CATEGORY category, int indent) override;
};

extern Logger log_instance;
#endif //__LOGGER_H__
