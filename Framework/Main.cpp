// 主函数仅用于测试
#include "Pch.h"
#include "ReflectInjector.h"
#include "Logger.h"

constexpr DWORD PROCESS_ID = 74140;

int main() {
	
	AbstractInjector* injector = new ReflectInjector();
	bool res = injector->inject(PROCESS_ID, "G:\\Github\\Repos\\CSO2-Flux\\Release\\Flux.dll");
	// bool res = injector->inject(PROCESS_ID, "G:\\CppProjs\\Tests\\Tests\\Debug\\TestDll.dll");
	if (res)
		LOGGER << Message(L"[Ethereal Inject] Inject success :)!", L"Main.cpp", LogRank::DEBUG);
	else
		LOGGER << Message(L"[Ethereal Inject] Inject failed :(.", L"Main.cpp", LogRank::ERROR);

	delete injector;
	LOGGER.flush();
	return 0;
}
