#pragma once
#include "Pch.h"

// wingdi.h Line 118定义了这个宏
#undef ERROR

// 日志等级
enum class LogLevel : unsigned char {

	// 生产环境
	INFO = 0,
	ERROR,
	WARN,

	// 开发环境
	DEBUG
};

#ifndef _DEBUG
#define LOG(_FileName, _Content, _Rank) Logger::getInstance() << Message((_Content), (_FileName), (_Rank))
#define LOG_INFO(_FileName, _Content) LOG(_FileName, _Content, LogLevel::INFO)
#define LOG_ERROR(_FileName, _Content) LOG(_FileName, _Content, LogLevel::ERROR)
#define LOG_WARN(_FileName, _Content) LOG(_FileName, _Content, LogLevel::WARN)
#define LOG_DEBUG(_FileName, _Content) LOG(_FileName, _Content, LogLevel::DEBUG)
#define FlushLoggerMessageQueue() Logger::getInstance().flush()
#else
#define LOG(_FileName, _Content, _Rank)
#define LOG_INFO(_FileName, _Content)
#define LOG_ERROR(_FileName, _Content)
#define LOG_WARN(_FileName, _Content)
#define LOG_DEBUG(_FileName, _Content)
#define FlushLoggerMessageQueue()
#endif

typedef std::wstring WString;

struct Message {

	WString content;

	Message(WString text, WString file, LogLevel rank) : content(text) {

		SYSTEMTIME sys;
		GetLocalTime(&sys);

		wchar_t buffer[256] = { 0 };
		RtlZeroMemory(buffer, 256 * 2);

		WString rankString;
		if (rank == LogLevel::INFO)
			rankString = L"INFO";
		else if (rank == LogLevel::ERROR)
			rankString = L"ERROR";
		else if (rank == LogLevel::WARN)
			rankString = L"WARN";
		else if (rank == LogLevel::DEBUG)
			rankString = L"DEBUG";

		wsprintfW(buffer, L"[%4d.%02d.%02d %02d:%02d:%02d][%ws][%ws] %ws\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, file.c_str(), rankString.c_str(), text.c_str());
		this->content = WString(buffer);
	}

	Message(WString text, LogLevel rank) : Message(text, L"UnknownFile", LogLevel::INFO) {}

};

typedef std::vector<Message> MessageQueue;

class Logger {

public:

	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	void operator=(Logger&) = delete;

	static Logger& getInstance();
	static Message format(WString format, WString file, LogLevel rank, ...);

	Logger& operator<<(const wchar_t* message);
	Logger& operator<<(const WString message);
	Logger& operator<<(const Message message);
	void flush();

private:

	MessageQueue queue;

	Logger();
	~Logger() = default;

};
