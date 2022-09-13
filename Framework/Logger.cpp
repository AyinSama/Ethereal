#include "Pch.h"
#include "Logger.h"

Logger::Logger() {

}

// 格式化生成Message
Message Logger::format(WString format, WString file, LogLevel rank, ...) {
	
	wchar_t* buffer = new wchar_t[1024];
	RtlZeroMemory(buffer, 1024 * 2);

	va_list args;
	va_start(args, rank);
	vswprintf(buffer, format.c_str(), args);
	va_end(args);

	Message msg(buffer, file, rank);
	delete[] buffer;

	return msg;
}

// 直接打INFO Log
Logger& Logger::operator<<(const wchar_t* message) {
	this->queue.push_back(Message(message, LogLevel::INFO));
	return *this;
}

// 直接打INFO Log
Logger& Logger::operator<<(const WString message) {
	this->queue.push_back(Message(message, LogLevel::INFO));
	return *this;
}

Logger& Logger::operator<<(const Message message) {
	this->queue.push_back(message);
	return *this;
}

void Logger::flush() {
	if (this->queue.empty()) return;
	for (const Message& msg : this->queue) {
		wprintf(msg.content.c_str());
	}
	this->queue.clear();
}

