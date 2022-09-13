#pragma once
#include "Pch.h"

/// <summary>
/// ����ĳ�����ڴ���࣬�ṩһϵ�в����ڴ��API
/// ����Խ��Լ��������ȿ�����ʵ���࣬��չ�û����
/// ��д�Ľӿڲ���֤�������˶�ͨ�ã��˸������裬���Լ���������
/// </summary>
abstract_class AbstractMemoryManager {

public:

	AbstractMemoryManager(DWORD pid) : procId(pid) {
		procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	}

	/// <summary>
	/// �ͷ������Դ
	/// </summary>
	virtual ~AbstractMemoryManager() {
		CloseHandle(this->procHandle);
	}

	/// <summary>
	/// ����address��size���ֽڵ��ڴ沢���浽buffer��
	/// </summary>
	/// <returns>�Ƿ��ȡ�ɹ�</returns>
	virtual bool readMemory(uintptr_t address, void* buffer, size_t size) = 0;

	/// <summary>
	/// ��data����size���ֽ�д���ַ��address���ǿ��ڴ�
	/// </summary>
	/// <returns>�Ƿ�д��ɹ�</returns>
	virtual bool writeMemory(uintptr_t address, void* data, size_t size) = 0;

	/// <summary>
	/// ��Ŀ������ڵ�address��ַ������һ��size���ֽڵ��ڴ棬���addressΪ0�������ַ���䣬�ڴ汣��������protect��ʧ�ܷ���0
	/// </summary>
	/// <returns>������ڴ��ַ��ʧ��ʱΪ0</returns>
	virtual uintptr_t allocateMemory(size_t size, DWORD protect = PAGE_READWRITE, uintptr_t address = 0) = 0;

	/// <summary>
	/// ���MemoryManager�Ƿ�����������Ŀ����̵ĸ�����������
	/// </summary>
	/// <returns>�Ƿ���سɹ�</returns>
	bool isOpened() {
		return this->procHandle != nullptr;
	}

	/// <summary>
	/// ��ȡĿ����̵�PID
	/// </summary>
	/// <returns>Ŀ����̵�PID</returns>
	DWORD getProcessId() {
		return this->procId;
	}
	
	/// <summary>
	/// ��ȡĿ����̵Ľ��̾��
	/// </summary>
	/// <returns>Ŀ����̵Ľ��̾��</returns>
	HANDLE getProcessHandle() {
		return this->procHandle;
	}

protected:
	HANDLE procHandle = nullptr;	// Ŀ����̾��
	DWORD procId = 0;				// Ŀ�����PID

};

