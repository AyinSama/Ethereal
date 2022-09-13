#include "Pch.h"
#include "EventManager.hpp"
#include "ReflectInjector.h"
#include "StandardMemoryManager.h"
#include "Logger.h"

constexpr DWORD PROCESS_ID = 74824;

/// <summary>
/// ����ģ��ʹ������
/// </summary>
/// <returns>Dimples#1337</returns>
int main() {

#pragma region Logger

	// ʹ��LOG_XXX������޸�ʽ�����
	LOG_INFO(L"This is a info log.", L"Main.cpp");
	LOG_DEBUG(L"This is a debug log.", L"Main.cpp");
	LOG_ERROR(L"This is a error log.", L"Main.cpp");

	// ʹ��LOGF_XXX����и�ʽ�����
	LOGF_INFO(L"This is a formatted info log. %d %.2f", L"Main.cpp", 520, 13.14f);
	LOGF_DEBUG(L"This is a debug log. %X %x", L"Main.cpp", 0x114, 0x514);

	// �ú�����ѵ�ǰ��Ϣ�����е�������Ϣ�������
	FlushLoggerMessageQueue();

#pragma endregion

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

	// ��ĳ�����ĸ��¼�
	EventCallHandler handler;
	eMgr.reg<EventCall>(std::bind(&EventCallHandler::onCall, &handler, std::placeholders::_1));

	// ��ĳ���������¼�
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

#pragma region Memory
	/*
	AbstractMemoryManager* memMgr = new StandardMemoryManager(PROCESS_ID);

	uintptr_t addr = memMgr->allocateMemory(sizeof(uintptr_t));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Allocate memory: %X", L"Main.cpp", addr);

	uintptr_t buffer = 5201314;
	memMgr->writeMemory(addr, &buffer, sizeof(buffer));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Write result: %d", L"Main.cpp", buffer);

	memMgr->readMemory(addr, &buffer, sizeof(buffer));
	LOGF_DEBUG(L"[Ethereal MemoryManager] Read result: %d", L"Main.cpp", buffer);

	delete memMgr;
	*/
#pragma endregion

	FlushLoggerMessageQueue();
	return 0;
}


