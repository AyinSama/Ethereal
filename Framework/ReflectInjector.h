#pragma once
#include "AbstractInjector.h"

#define PAGE_SIZE 0x1000
#define RELOC_FLAG32(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_HIGHLOW)
#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef _WIN64
#define RELOC_FLAG RELOC_FLAG64
#define COMPILE_ARCHITECTURE IMAGE_FILE_MACHINE_AMD64
#else
#define RELOC_FLAG RELOC_FLAG32
#define COMPILE_ARCHITECTURE IMAGE_FILE_MACHINE_I386
#endif

typedef HMODULE(WINAPI *pfnLoadLibraryA)(const char* lpLibFilename);
typedef FARPROC(WINAPI *pfnGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
typedef BOOL(WINAPI *pfnDllEntry)(HMODULE hModule, DWORD dwReason, LPVOID pReserved);

// Shellcode�����ṹ
typedef struct _ReflectContext {

	BYTE* payload;
	pfnLoadLibraryA fnLoadLibraryA;
	pfnGetProcAddress fnGetProcAddress;

} ReflectContext, *PReflectContext;

/// <summary>
/// ����ע�룬�ڴ�ע�룬�Լ�����ɶ��ɶ�������ֶ�װ��PE
/// ע�⣺����δ֪ԭ��ʹ�ø�ע�뷽����ʱ������Ҫ����Release����Ȼ���ܻᵼ��ע��ʧ��
/// </summary>
class ReflectInjector : public AbstractInjector {

public:
	bool inject(DWORD pid, const std::string& szModulePath) override;
	bool inject(DWORD pid, const std::wstring& szModulePath) override;

private:
	bool doInject(DWORD pid, void* pModuleBinary);

};
