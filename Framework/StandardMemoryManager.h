#pragma once
#include "Pch.h"
#include "AbstractMemoryManager.h"

/// <summary>
/// �������MemoryManager��ʹ��Win32 APIʵ��
/// </summary>
class StandardMemoryManager : public AbstractMemoryManager {

public:

	StandardMemoryManager(DWORD pid) : AbstractMemoryManager(pid) {}

	bool readMemory(uintptr_t address, void* buffer, size_t size) override;
	bool writeMemory(uintptr_t address, void* data, size_t size) override;
	uintptr_t allocateMemory(size_t size, DWORD protect = PAGE_READWRITE, uintptr_t address = 0) override;

};

