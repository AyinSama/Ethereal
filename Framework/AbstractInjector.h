#pragma once
#include "Pch.h"

///
abstract_class AbstractInjector {
	
public:
	virtual bool inject(DWORD pid, const std::string& szModulePath) = 0;

};
