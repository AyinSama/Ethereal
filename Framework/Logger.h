#pragma once
#include "Pch.h"

// wingdi.h Line 118定义了这个宏
#undef ERROR

// 日志等级
enum class LogLevel : uint32_t {

	// 生产环境
	INFO = 0,
	ERROR,
	WARN,

	// 开发环境
	DEBUG
};

#ifdef _DEBUG
#define LOG(_Content, _FileName, _Rank) Logger::getInstance() << Message((_Content), (_FileName), (_Rank))
#define LOG_INFO(_Content, _FileName) LOG((_Content), (_FileName), LogLevel::INFO)
#define LOG_ERROR(_Content, _FileName) LOG((_Content), (_FileName), LogLevel::ERROR)
#define LOG_WARN(_Content, _FileName) LOG((_Content), (_FileName), LogLevel::WARN)
#define LOG_DEBUG(_Content, _FileName) LOG((_Content), (_FileName), LogLevel::DEBUG)
#define LOGF_INFO(_Format, _FileName, ...) Logger::getInstance() << Logger::format((_Format), (_FileName), LogLevel::INFO, __VA_ARGS__);
#define LOGF_ERROR(_Format, _FileName, ...) Logger::getInstance() << Logger::format((_Format), (_FileName), LogLevel::ERROR, __VA_ARGS__);
#define LOGF_WARN(_Format, _FileName, ...) Logger::getInstance() << Logger::format((_Format), (_FileName), LogLevel::WARN, __VA_ARGS__);
#define LOGF_DEBUG(_Format, _FileName, ...) Logger::getInstance() << Logger::format((_Format), (_FileName), LogLevel::DEBUG, __VA_ARGS__);
#define FlushLoggerMessageQueue() Logger::getInstance().flush()
#else
#define LOG(_Content, _FileName, _Rank)
#define LOG_INFO(_Content, _FileName)
#define LOG_ERROR(_Content, _FileName)
#define LOG_WARN(_Content, _FileName)
#define LOG_DEBUG(_Content, _FileName)
#define LOGF_INFO(_Format, _FileName, ...)
#define LOGF_ERROR(_Format, _FileName, ...)
#define LOGF_WARN(_Format, _FileName, ...)
#define LOGF_DEBUG(_Format, _FileName, ...)
#define FlushLoggerMessageQueue()
#endif

typedef std::wstring WString;
constexpr const wchar_t* LogLevelStrings[] = { L"INFO", L"ERROR", L"WARN", L"DEBUG" };

struct Message {

	WString content;

	Message(WString text, WString file, LogLevel rank) : content(text) {

		SYSTEMTIME sys;
		GetLocalTime(&sys);

		wchar_t buffer[256] = { 0 };
		RtlZeroMemory(buffer, 256 * 2);

		WString rankString = LogLevelStrings[static_cast<uint32_t>(rank)];
		wsprintfW(buffer, L"[%4d.%02d.%02d %02d:%02d:%02d][%ws][%ws] %ws\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, file.c_str(), rankString.c_str(), text.c_str());
		this->content = WString(buffer);
	}

	Message(WString text, LogLevel rank) : Message(text, L"UnknownFile", LogLevel::INFO) {}

};

typedef std::vector<Message> MessageQueue;

class Logger : public Singleton<Logger> {
	SingleObject(Logger)

public:
	static Message format(WString format, WString file, LogLevel rank, ...);

	Logger& operator<<(const wchar_t* message);
	Logger& operator<<(const WString& message);
	Logger& operator<<(const Message& message);
	void flush();

private:

	MessageQueue queue;

	Logger();
	~Logger() = default;

};
