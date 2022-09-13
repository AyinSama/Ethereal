#pragma once
#include "Pch.h"

/// <summary>
/// 所有注入实现的抽象基类
/// </summary>
abstract_class AbstractInjector {
	
public:
	virtual bool inject(DWORD pid, const std::string& szModulePath) = 0;
	virtual bool inject(DWORD pid, const std::wstring& szModulePath) = 0;

};
