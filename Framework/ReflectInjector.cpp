#include "Pch.h"
#include "ReflectInjector.h"

void __stdcall ___loader___(ReflectContext* context) {
	
	// 解析PE头
	IMAGE_DOS_HEADER* pDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(context->payload);
	IMAGE_NT_HEADERS* pNtHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(context->payload + pDosHeader->e_lfanew);
	IMAGE_SECTION_HEADER* pFirstSection = IMAGE_FIRST_SECTION(pNtHeader);
	pfnDllEntry DllMain = reinterpret_cast<pfnDllEntry>(context->payload + pNtHeader->OptionalHeader.AddressOfEntryPoint);

	// 处理重定向项
	BYTE* baseDelta = context->payload - pNtHeader->OptionalHeader.ImageBase;
	if (baseDelta) {
		if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) {
			auto* pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(context->payload + pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
			while (pRelocData->VirtualAddress) {
				UINT AmountOfEntries = (pRelocData->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
				WORD* pRelativeInfo = reinterpret_cast<WORD*>(pRelocData + 1);

				for (UINT i = 0; i != AmountOfEntries; ++i, ++pRelativeInfo) {
					if (RELOC_FLAG(*pRelativeInfo)) {
						UINT_PTR* pPatch = reinterpret_cast<UINT_PTR*>(context->payload + pRelocData->VirtualAddress + ((*pRelativeInfo) & 0xFFF));
						*pPatch += reinterpret_cast<UINT_PTR>(baseDelta);
					}
				}
				pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(reinterpret_cast<BYTE*>(pRelocData) + pRelocData->SizeOfBlock);
			}
		}
	}

	// 处理导入表
	if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {
		auto* pImportDescr = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(context->payload + pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
		while (pImportDescr->Name) {
			char* szMod = reinterpret_cast<char*>(context->payload + pImportDescr->Name);
			HINSTANCE hDll = context->fnLoadLibraryA(szMod);

			ULONG_PTR* pThunkRef = reinterpret_cast<ULONG_PTR*>(context->payload + pImportDescr->OriginalFirstThunk);
			ULONG_PTR* pFuncRef = reinterpret_cast<ULONG_PTR*>(context->payload + pImportDescr->FirstThunk);

			if (!pThunkRef)
				pThunkRef = pFuncRef;

			for (; *pThunkRef; ++pThunkRef, ++pFuncRef) {
				if (IMAGE_SNAP_BY_ORDINAL(*pThunkRef)) {
					*pFuncRef = (ULONG_PTR)context->fnGetProcAddress(hDll, reinterpret_cast<char*>(*pThunkRef & 0xFFFF));
				}
				else {
					auto* pImport = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(context->payload + (*pThunkRef));
					*pFuncRef = (ULONG_PTR)context->fnGetProcAddress(hDll, pImport->Name);
				}
			}
			++pImportDescr;
		}
	}

	// 处理TLS
	if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size) {
		auto* pTLS = reinterpret_cast<IMAGE_TLS_DIRECTORY*>(context->payload + pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		auto* pCallback = reinterpret_cast<PIMAGE_TLS_CALLBACK*>(pTLS->AddressOfCallBacks);
		for (; pCallback && *pCallback; ++pCallback)
			(*pCallback)(context->payload, DLL_PROCESS_ATTACH, nullptr);
	}

	// 手动调用DllMain
	DllMain(reinterpret_cast<HMODULE>(context->payload), DLL_PROCESS_ATTACH, nullptr);
}

bool ReflectInjector::inject(DWORD pid, const std::string& szModulePath) {

	// 把DLL读入内存
	std::ifstream modFile(szModulePath, std::ios::binary | std::ios::ate);
	size_t fileSize = modFile.tellg();
	BYTE* modBinary = new BYTE[fileSize];
	modFile.seekg(0, std::ios::beg);
	modFile.read(reinterpret_cast<char*>(modBinary), fileSize);
	modFile.close();

	// PE头
	IMAGE_DOS_HEADER* pDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(modBinary);
	IMAGE_NT_HEADERS* pNtHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(modBinary + pDosHeader->e_lfanew);
	IMAGE_SECTION_HEADER* pFirstSection = IMAGE_FIRST_SECTION(pNtHeader);

	//判断是否为PE文件
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE || pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
		printf("[Ethereal Inject] Invalid pe file.");
		delete[] modBinary;
		return false;
	}

	// 判断运行平台
	if (pNtHeader->FileHeader.Machine != COMPILE_ARCHITECTURE) {
		printf("[Ethereal Inject] Invalid architecture.");
		delete[] modBinary;
		return false;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (!hProcess) {
		printf("[Ethereal Inject] OpenProcess failed.");
		return false;
	}

	// 目标进程空间地址
	BYTE* payload = reinterpret_cast<BYTE*>(VirtualAllocEx(hProcess, nullptr, pNtHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
	BYTE* pShellcode = reinterpret_cast<BYTE*>(VirtualAllocEx(hProcess, nullptr, PAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
	BYTE* pShellcodeParam = reinterpret_cast<BYTE*>(VirtualAllocEx(hProcess, nullptr, sizeof(ReflectContext), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
	if (!payload || !pShellcode || !pShellcodeParam) {
		printf("[Ethereal Inject] Memory allocation error.");
		return false;
	}

	// 写入PE头，节区头
	WriteProcessMemory(hProcess, payload, modBinary, pNtHeader->OptionalHeader.SizeOfHeaders, nullptr);
	for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++, pFirstSection++) {
		WriteProcessMemory(hProcess, payload + pFirstSection->VirtualAddress, modBinary + pFirstSection->PointerToRawData, pFirstSection->SizeOfRawData, nullptr);
	}

	// 打包参数
	ReflectContext context{};
	context.payload = payload;
	context.fnLoadLibraryA = LoadLibraryA;
	context.fnGetProcAddress = GetProcAddress;

	// 写入Shellcode及其参数
	WriteProcessMemory(hProcess, pShellcode, ___loader___, PAGE_SIZE, nullptr);
	WriteProcessMemory(hProcess, pShellcodeParam, &context, sizeof(ReflectContext), nullptr);

	// 调用Shellcode
	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pShellcode), pShellcodeParam, 0, nullptr);

	delete[] modBinary;
	return hThread ? CloseHandle(hThread) : false;
}
