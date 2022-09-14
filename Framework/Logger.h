#pragma once
#include "Pch.h"
#include "Util.h"

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
#define LOG(_Content, _Level) Logger::getInstance() << Message((_Content), TEXT(__FILE__), (_Level))
#define LOG_INFO(_Content) LOG((_Content), LogLevel::INFO)
#define LOG_ERROR(_Content) LOG((_Content), LogLevel::ERROR)
#define LOG_WARN(_Content) LOG((_Content), LogLevel::WARN)
#define LOG_DEBUG(_Content) LOG((_Content), LogLevel::DEBUG)
#define LOGF_INFO(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::INFO, __VA_ARGS__);
#define LOGF_ERROR(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::ERROR, __VA_ARGS__);
#define LOGF_WARN(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::WARN, __VA_ARGS__);
#define LOGF_DEBUG(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::DEBUG, __VA_ARGS__);
#define FlushLoggerMessageQueue() Logger::getInstance().flush()
#else
#define LOG(_Content, _Level) Logger::getInstance() << Message((_Content), TEXT(__FILE__), (_Level))
#define LOG_INFO(_Content) LOG((_Content), LogLevel::INFO)
#define LOG_ERROR(_Content) LOG((_Content), LogLevel::ERROR)
#define LOG_WARN(_Content) LOG((_Content), LogLevel::WARN)
#define LOG_DEBUG(_Content)
#define LOGF_INFO(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::INFO, __VA_ARGS__);
#define LOGF_ERROR(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::ERROR, __VA_ARGS__);
#define LOGF_WARN(_Format, ...) Logger::getInstance() << Logger::format((_Format), TEXT(__FILE__), LogLevel::WARN, __VA_ARGS__);
#define LOGF_DEBUG(_Format, ...)
#define FlushLoggerMessageQueue() Logger::getInstance().flush()
#endif

typedef std::wstring WString;
constexpr const wchar_t* LogLevelStrings[] = { L"INFO", L"ERROR", L"WARN", L"DEBUG" };

struct Message {

	WString content;

	Message(WString text, WString file, LogLevel rank) {
		SYSTEMTIME sys;
		GetLocalTime(&sys);

		wchar_t buffer[256] = { 0 };
		RtlZeroMemory(buffer, 256 * 2);

		WString rankString = LogLevelStrings[static_cast<uint32_t>(rank)];
		wsprintfW(buffer, L"[%4d.%02d.%02d %02d:%02d:%02d][%ws][%ws] %ws\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, file.c_str(), rankString.c_str(), text.c_str());
		this->content = WString(buffer);
	}

	Message(const std::string& text, WString file, LogLevel rank) {
		SYSTEMTIME sys;
		GetLocalTime(&sys);

		wchar_t buffer[256] = { 0 };
		RtlZeroMemory(buffer, 256);

		WString wText = Util::cvtWString(text);
		WString rankString = LogLevelStrings[static_cast<uint32_t>(rank)];
		wsprintfW(buffer, L"[%4d.%02d.%02d %02d:%02d:%02d][%ws][%ws] %ws\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, file.c_str(), rankString.c_str(), wText.c_str());
		this->content = WString(buffer);
	}

};

typedef std::vector<Message> MessageQueue;

class Logger : public Singleton<Logger> {
	SingleObject(Logger)

public:
	static Message format(WString format, WString file, LogLevel rank, ...);

	Logger& operator<<(const char* message);
	Logger& operator<<(const wchar_t* message);
	Logger& operator<<(const std::string& message);
	Logger& operator<<(const WString& message);
	Logger& operator<<(const Message& message);
	void flush();

private:

	MessageQueue queue;

	Logger();
	~Logger() = default;

};
