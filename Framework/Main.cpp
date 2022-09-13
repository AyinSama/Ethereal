// 主函数仅用于测试
#include "Pch.h"
#include "ReflectInjector.h"
#include "StandardMemoryManager.h"
#include "Logger.h"

constexpr DWORD PROCESS_ID = 18276;

int main() {
	
#pragma region Injector
	
	AbstractInjector* injector = new ReflectInjector();

	bool res = injector->inject(PROCESS_ID, L"G:\\CppProjs\\Tests\\Tests\\Debug\\TestDll.dll");
	if (res)
		LOG(L"Main.cpp", L"[Ethereal Injector] Inject success :)!", LogLevel::DEBUG);
	else
		LOG(L"Main.cpp", L"[Ethereal Injector] Inject failed :(.", LogLevel::ERROR);
	
	delete injector;
	
#pragma endregion

#pragma region MemoryManager
	/*
	AbstractMemoryManager* memMgr = new StandardMemoryManager(PROCESS_ID);

	uintptr_t addr = memMgr->allocateMemory(sizeof(uintptr_t));
	LOGGER << Logger::format(L"[Ethereal MemoryManager] Allocate memory: %X", L"Main.cpp", LogLevel::DEBUG, addr);

	uintptr_t buffer = 5201314;
	memMgr->writeMemory(addr, &buffer, sizeof(buffer));
	LOGGER << Logger::format(L"[Ethereal MemoryManager] Write result: %d", L"Main.cpp", LogLevel::DEBUG, buffer);

	memMgr->readMemory(addr, &buffer, sizeof(buffer));
	LOGGER << Logger::format(L"[Ethereal MemoryManager] Read result: %d", L"Main.cpp", LogLevel::DEBUG, buffer);

	delete memMgr;
	*/
#pragma endregion

	FlushLoggerMessageQueue();
	return 0;
}
