#pragma once
#include "Pch.h"

/// <summary>
/// ����ע��ʵ�ֵĳ������
/// </summary>
abstract_class AbstractInjector {
	
public:
	virtual bool inject(DWORD pid, const std::string& szModulePath) = 0;
	virtual bool inject(DWORD pid, const std::wstring& szModulePath) = 0;

};
