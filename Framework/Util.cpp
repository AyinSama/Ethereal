#include "Pch.h"
#include "Util.h"

namespace Util {
	
	std::wstring cvtWString(const std::string& text) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(text);
	}

	std::string cvtString(const std::wstring& text) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(text);
	}

}
