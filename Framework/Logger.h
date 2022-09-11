#pragma once
#include "Pch.h"

// wingdi.h Line 118定义了这个宏
#undef ERROR
enum class LogRank : unsigned char {

	// 生产环境
	INFO = 0,
	ERROR,
	WARN,

	// 开发环境
	DEBUG
};

#define LOGGER Logger::getInstance()

#ifdef _DEBUG
#define LOG(_FileName, _Content, _Rank) LOGGER << Message((_Content), (_FileName), LogRank::_Rank)
#define LOG_INFO(_FileName, _Content) LOG(_FileName, _Content, INFO)
#define LOG_ERROR(_FileName, _Content) LOG(_FileName, _Content, ERROR)
#define LOG_WARN(_FileName, _Content) LOG(_FileName, _Content, WARN)
#define LOG_DEBUG(_FileName, _Content) LOG(_FileName, _Content, DEBUG)
#else
#define LOG(_FileName, _Content, _Rank)
#define LOG_INFO(_FileName, _Content)
#define LOG_ERROR(_FileName, _Content)
#define LOG_WARN(_FileName, _Content)
#define LOG_DEBUG(_FileName, _Content)
#endif

typedef std::wstring WString;

struct Message {

	WString content;

	Message(WString text, WString file, LogRank rank) : content(text) {

		SYSTEMTIME sys;
		GetLocalTime(&sys);

		wchar_t buffer[256] = { 0 };
		RtlZeroMemory(buffer, 256 * 2);

		WString rankString;
		if (rank == LogRank::INFO)
			rankString = L"INFO";
		else if (rank == LogRank::ERROR)
			rankString = L"ERROR";
		else if (rank == LogRank::WARN)
			rankString = L"WARN";
		else if (rank == LogRank::DEBUG)
			rankString = L"DEBUG";

		wsprintfW(buffer, L"[%4d.%02d.%02d %02d:%02d:%02d][%ws][%ws] %ws\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, file.c_str(), rankString.c_str(), text.c_str());
		this->content = WString(buffer);
	}

	Message(WString text, LogRank rank) : Message(text, L"UnknownFile", LogRank::INFO) {}

};

typedef std::vector<Message> MessageQueue;

class Logger {

public:

	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	void operator=(Logger&) = delete;

	static Logger& getInstance();
	static Message format(WString format, WString file, LogRank rank, ...);

	Logger& operator<<(const wchar_t* message);
	Logger& operator<<(const WString message);
	Logger& operator<<(const Message message);
	void flush();

private:

	MessageQueue queue;

	Logger();
	~Logger() = default;

};
