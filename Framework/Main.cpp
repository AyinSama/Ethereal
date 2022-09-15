#include "Pch.h"
#include "EventManager.hpp"
#include "ReflectInjector.h"
#include "StandardMemoryManager.h"
#include "Logger.h"
#include "Util.h"
#include "Forwarder.hpp"

constexpr DWORD PROCESS_ID = 35760;

#pragma region Hook
typedef int (WINAPI* pfnMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
pfnMessageBoxA pMessageBoxA = nullptr;

int WINAPI MyMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
	pMessageBoxA(hWnd, "My MessageBox called.", lpCaption, uType);
	int ret = pMessageBoxA(hWnd, lpText, lpCaption, uType);
	return ret;
}
#pragma endregion

/// <summary>
/// 各个模块使用例子
/// </summary>
/// <returns>Dimples#1337</returns>
int main() {

#pragma region Logger
	/*
	// 使用LOG_XXX宏进行无格式化输出
	LOG_INFO("This is a info log.");
	LOG_DEBUG(L"This is a debug log.");
	LOG_WARN(L"这是一个警告日志");

	// 使用LOGF_XXX宏进行格式化输出
	LOGF_ERROR(L"This is a formatted error log. %d %.2f", 520, 13.14f);
	LOGF_DEBUG(L"这是一个格式化后的调试日志 %X %x", 0xABC, 0xABC);

	// 该函数会把当前消息队列中的所有消息进行输出
	FlushLoggerMessageQueue();

	Logger& logger = Logger::getInstance();

	std::wstring wText = Util::cvtWString("Ayin");
	std::string aText = Util::cvtString(L"Sama");

	// 不推荐直接使用重载运算符，这会使输出的文件名一直都是Logger.cpp，应使用提供好的LOG_XXX和LOGF_XXX等一系列宏
	logger << wText;
	logger << aText;
	logger << __FILE__;
	logger << __FUNCTION__;

	// 输出中文时请务必使用wchar_t*而不是char*
	logger << L"中文测试";
	FlushLoggerMessageQueue();
	*/
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

#ifdef _WIN64
	bool res = injector->inject(PROCESS_ID, L"G:\\CppProjs\\Tests\\Tests\\x64\\Debug\\TestDll.dll");
#else
	bool res = injector->inject(PROCESS_ID, L"G:\\CppProjs\\Tests\\Tests\\Debug\\TestDll.dll");
#endif
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
#ifdef _WIN64
	LOGF_INFO(L"[Ethereal MemoryManager] Allocate memory: %llX", L"Main.cpp", addr);
#else
	LOGF_INFO(L"[Ethereal MemoryManager] Allocate memory: %X", L"Main.cpp", addr);
#endif
	uintptr_t buffer = 5201314;
	memMgr->writeMemory(addr, &buffer, sizeof(buffer));
	LOGF_INFO(L"[Ethereal MemoryManager] Write result: %d", L"Main.cpp", buffer);

	memMgr->readMemory(addr, &buffer, sizeof(buffer));
	LOGF_INFO(L"[Ethereal MemoryManager] Read result: %d", L"Main.cpp", buffer);

	delete memMgr;
	*/
#pragma endregion

#pragma region Hook

	Forwarder<int>& forwarder = Forwarder<int>::getInstance();
	bool res = forwarder.create(0, &MessageBoxA, &MyMessageBoxA, reinterpret_cast<void**>(&pMessageBoxA));
	LOGF_INFO(L"Status: %d", res);

	forwarder.enable(0);
	LOGF_INFO(L"Status: %d", res);

	MessageBoxA(nullptr, "AyinSama", "Info", MB_ICONINFORMATION);

	forwarder.disable(0);
	LOGF_INFO(L"Status: %d", res);

	forwarder.destroy(0);
	LOGF_INFO(L"Status: %d", res);

#pragma endregion

	FlushLoggerMessageQueue();
	return 0;
}


