#include "Pch.h"
#include "Logger.h"

Logger::Logger() {

}

// 格式化生成Message
Message Logger::format(const WString& format, WString file, LogLevel level, ...) {
	
	wchar_t* buffer = new wchar_t[BUFFER_COUNT];
	RtlZeroMemory(buffer, BUFFER_COUNT * 2);

	va_list args;
	va_start(args, level);
	vswprintf_s(buffer, BUFFER_COUNT, format.c_str(), args);
	va_end(args);

	Message msg(buffer, file, level);
	delete[] buffer;

	return msg;
}

Message Logger::format(const std::string& format, WString file, LogLevel level, ...) {
	
	char* buffer = new char[BUFFER_COUNT];
	RtlZeroMemory(buffer, BUFFER_COUNT);

	va_list args;
	va_start(args, level);
	vsprintf_s(buffer, BUFFER_COUNT, format.c_str(), args);
	va_end(args);

	Message msg(buffer, file, level);
	delete[] buffer;

	return msg;
}


Logger& Logger::operator<<(const char* message) {
	this->queue.push_back(Message(std::string(message), TEXT(__FILE__), LogLevel::INFO));
	return *this;
}

Logger& Logger::operator<<(const wchar_t* message) {
	this->queue.push_back(Message(WString(message), TEXT(__FILE__), LogLevel::INFO));
	return *this;
}

Logger& Logger::operator<<(const std::string& message) {
	this->queue.push_back(Message(message, TEXT(__FILE__), LogLevel::INFO));
	return *this;
}

Logger& Logger::operator<<(const WString& message) {
	this->queue.push_back(Message(message, TEXT(__FILE__), LogLevel::INFO));
	return *this;
}

Logger& Logger::operator<<(const Message& message) {
	this->queue.push_back(message);
	return *this;
}

void Logger::flush() {
	if (this->queue.empty()) return;
	setlocale(LC_CTYPE, "");
	for (const Message& msg : this->queue) {
		wprintf(msg.content.c_str());
	}
	setlocale(LC_CTYPE, "C");
	this->queue.clear();
}

