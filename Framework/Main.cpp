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
/// ����ģ��ʹ������
/// </summary>
/// <returns>Dimples#1337</returns>
int main() {

#pragma region Logger
	/*
	// ʹ��LOG_XXX������޸�ʽ�����
	LOG_INFO("This is a info log.");
	LOG_DEBUG(L"This is a debug log.");
	LOG_WARN(L"����һ��������־");

	// ʹ��LOGF_XXX����и�ʽ�����
	LOGF_ERROR(L"This is a formatted error log. %d %.2f", 520, 13.14f);
	LOGF_DEBUG(L"����һ����ʽ����ĵ�����־ %X %x", 0xABC, 0xABC);

	// �ú�����ѵ�ǰ��Ϣ�����е�������Ϣ�������
	FlushLoggerMessageQueue();

	Logger& logger = Logger::getInstance();

	std::wstring wText = Util::cvtWString("Ayin");
	std::string aText = Util::cvtString(L"Sama");

	// ���Ƽ�ֱ��ʹ����������������ʹ������ļ���һֱ����Logger.cpp��Ӧʹ���ṩ�õ�LOG_XXX��LOGF_XXX��һϵ�к�
	logger << wText;
	logger << aText;
	logger << __FILE__;
	logger << __FUNCTION__;

	// �������ʱ�����ʹ��wchar_t*������char*
	logger << L"���Ĳ���";
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


