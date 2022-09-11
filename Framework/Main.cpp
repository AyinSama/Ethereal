// 主函数仅用于测试
#include "Pch.h"
#include "ReflectInjector.h"

constexpr DWORD PROCESS_ID = 12784;

int main() {
	
	AbstractInjector* injector = new ReflectInjector();
	bool res = injector->inject(PROCESS_ID, "G:\\Github\\Repos\\CSO2-Flux\\Release\\Flux.dll");
	// bool res = injector->inject(PROCESS_ID, "G:\\CppProjs\\Tests\\Tests\\Debug\\TestDll.dll");
	if (res)
		printf("[Ethereal Inject] Inject success :)!");
	else
		printf("[Ethereal Inject] Inject failed :(.");

	delete injector;
	return 0;
}
