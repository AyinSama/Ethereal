#include "Pch.h"
#include "StandardMemoryManager.h"

bool StandardMemoryManager::readMemory(uintptr_t address, void* buffer, size_t size) {
	SIZE_T dwRead = 0;
	return ReadProcessMemory(this->procHandle, reinterpret_cast<void*>(address), buffer, size, &dwRead) && dwRead == size;
}

bool StandardMemoryManager::writeMemory(uintptr_t address, void* data, size_t size) {
	SIZE_T dwWritten = 0;
	return WriteProcessMemory(this->procHandle, reinterpret_cast<void*>(address), data, size, &dwWritten) && size == dwWritten;
}

uintptr_t StandardMemoryManager::allocateMemory(size_t size, DWORD protect, uintptr_t address) {
	void* target = VirtualAllocEx(this->procHandle, address == 0 ? nullptr : reinterpret_cast<void*>(address), size, MEM_COMMIT | MEM_RESERVE, protect);
	return target == nullptr ? 0 : reinterpret_cast<uintptr_t>(target);
}
