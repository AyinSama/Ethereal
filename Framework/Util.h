#pragma once
#include "Pch.h"

/// <summary>
/// ����ȫ���ԵĹ����ຯ�������Է��������棬��ֹ�����ռ���Ⱦ
/// </summary>
namespace Util {

	/// <summary>
	/// ��std::stringת��Ϊstd::wstring
	/// ע����ĳЩ����ǰ���ܲ�������
	/// </summary>
	/// <param name="text">��ת���ı�</param>
	/// <returns>ת������ı�</returns>
	std::wstring cvtWString(const std::string& text);

	/// <summary>
	/// ��std::wstringת��Ϊstd::string
	/// ע����ĳЩ����ǰ���ܲ�������
	/// </summary>
	/// <param name="text">��ת���ı�</param>
	/// <returns>ת������ı�</returns>
	std::string cvtString(const std::wstring& text);

}


