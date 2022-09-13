#include "Pch.h"
#include "EventManager.hpp"
#include "ReflectInjector.h"
#include "StandardMemoryManager.h"
#include "Logger.h"

constexpr DWORD PROCESS_ID = 74824;

/// <summary>
/// 各个模块使用例子
/// </summary>
/// <returns>Dimples#1337</returns>
int main() {

#pragma region EventSystem
	/*
	class EventCall : public Event<EventCall> {
	public:
		EventCall(int param) : param(param) {}
		int getParam() const { return this->param; }
	private:
		int param;
	};

	class EventCallHandler {
	public:
		void onCall(const EventCall& e) { printf_s("Event called. Param: %d\n", e.getParam()); }
	};

	EventManager& eMgr = EventManager::getInstance();

	// 在某处订阅改事件
	EventCallHandler handler;
	eMgr.reg<EventCall>(std::bind(&EventCallHandler::onCall, &handler, std::placeholders::_1));

	// 在某处触发该事件
	EventCall pack(520);
	eMgr.call<EventCall>(pack);
	*/
#pragma endregion

#pragma region Injector
	/*
	AbstractInjector* injector = new ReflectInjector();

	bool res = injector->inject(PROCESS_ID, L"G:\\CppProjs\\Tests\\Tests\\Debug\\TestDll.dll");
	if (res)
		LOG(L"Main.cpp", L"[Ethereal Injector] Inject success :)!", LogLevel::DEBUG);
	else
		LOG(L"Main.cpp", L"[Ethereal Injector] Inject failed :(.", LogLevel::ERROR);
	
	delete injector;
	*/
#pragma endregion

#pragma region MemoryManager
	
	AbstractMemoryManager* memMgr = new StandardMemoryManager(PROCESS_ID);

	uintptr_t addr = memMgr->allocateMemory(sizeof(uintptr_t));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Allocate memory: %X", L"Main.cpp", addr);

	uintptr_t buffer = 5201314;
	memMgr->writeMemory(addr, &buffer, sizeof(buffer));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Write result: %d", L"Main.cpp", buffer);

	memMgr->readMemory(addr, &buffer, sizeof(buffer));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Read result: %d", L"Main.cpp", buffer);

	delete memMgr;
	
#pragma endregion

	FlushLoggerMessageQueue();
	return 0;
}


