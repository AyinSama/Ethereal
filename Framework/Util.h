#pragma once
#include "Pch.h"

/// <summary>
/// 所有全局性的工具类函数都可以放在这里面，防止命名空间污染
/// </summary>
namespace Util {

	/// <summary>
	/// 把std::string转换为std::wstring
	/// 注：在某些编码前可能不起作用
	/// </summary>
	/// <param name="text">被转换文本</param>
	/// <returns>转换后的文本</returns>
	std::wstring cvtWString(const std::string& text);

	/// <summary>
	/// 把std::wstring转换为std::string
	/// 注：在某些编码前可能不起作用
	/// </summary>
	/// <param name="text">被转换文本</param>
	/// <returns>转换后的文本</returns>
	std::string cvtString(const std::wstring& text);

}


