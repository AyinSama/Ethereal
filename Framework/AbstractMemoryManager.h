#pragma once
#include "Pch.h"

/// <summary>
/// 管理某进程内存的类，提供一系列操作内存的API
/// 如需对接自己的驱动等可另起实现类，扩展该基类等
/// 我写的接口不保证对所有人都通用，人各有所需，按自己的需求来
/// </summary>
abstract_class AbstractMemoryManager {

public:

	AbstractMemoryManager(DWORD pid) : procId(pid) {
		procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	}

	/// <summary>
	/// 释放相关资源
	/// </summary>
	virtual ~AbstractMemoryManager() {
		CloseHandle(this->procHandle);
	}

	/// <summary>
	/// 拷贝address处size个字节的内存并保存到buffer中
	/// </summary>
	/// <returns>是否读取成功</returns>
	virtual bool readMemory(uintptr_t address, void* buffer, size_t size) = 0;

	/// <summary>
	/// 把data处的size个字节写入地址是address的那块内存
	/// </summary>
	/// <returns>是否写入成功</returns>
	virtual bool writeMemory(uintptr_t address, void* data, size_t size) = 0;

	/// <summary>
	/// 在目标进程内的address地址处分配一块size个字节的内存，如果address为0则随机地址分配，内存保护属性是protect，失败返回0
	/// </summary>
	/// <returns>分配的内存地址，失败时为0</returns>
	virtual uintptr_t allocateMemory(size_t size, DWORD protect = PAGE_READWRITE, uintptr_t address = 0) = 0;

	/// <summary>
	/// 检查MemoryManager是否正常加载了目标进程的各项所需数据
	/// </summary>
	/// <returns>是否加载成功</returns>
	bool isOpened() {
		return this->procHandle != nullptr;
	}

	/// <summary>
	/// 获取目标进程的PID
	/// </summary>
	/// <returns>目标进程的PID</returns>
	DWORD getProcessId() {
		return this->procId;
	}
	
	/// <summary>
	/// 获取目标进程的进程句柄
	/// </summary>
	/// <returns>目标进程的进程句柄</returns>
	HANDLE getProcessHandle() {
		return this->procHandle;
	}

protected:
	HANDLE procHandle = nullptr;	// 目标进程句柄
	DWORD procId = 0;				// 目标进程PID

};

