#pragma once
#include "Pch.h"

typedef struct _ForwardData {
	bool state;
	void* pfnTarget;
	void* pfnDetour;
	void** ppfnOrigin;
}ForwardData, *PForwardData;

template <class _CookieType>
/// <summary>
/// ����Minhook���ٷ�װ��ģ��
/// Cookie��������ǽ���ں���ע��ע���ص����Ǹ�Cookie
/// ���ڱ�ʶÿһ���Ѵ����Ĺ���
/// Cookie������ȷ�������˾Ͳ�Ҫ��
/// </summary>
/// <typeparam name="_CookieType">Ψһ��ʶ������������</typeparam>
class Forwarder : public Singleton<Forwarder<_CookieType>> {

public:
	Forwarder() {
		MH_Initialize();
	}

	~Forwarder() {
		MH_Uninitialize();
	}

	/// <summary>
	/// ����һ������
	/// </summary>
	/// <returns>�Ƿ񴴽��ɹ�</returns>
	bool create(_CookieType cookie, void* pfnTarget, void* pfnDetour, void** ppfnOrigin) {
		ForwardData data{ 0 };
		data.state = false;
		data.pfnTarget = pfnTarget;
		data.pfnDetour = pfnDetour;
		data.ppfnOrigin = ppfnOrigin;
		this->forwarderChain.insert(std::pair<_CookieType, ForwardData>(cookie, data));
		return MH_CreateHook(data.pfnTarget, data.pfnDetour, data.ppfnOrigin) == MH_OK;
	}
	
	/// <summary>
	/// ����һ������
	/// </summary>
	/// <returns>�Ƿ������ɹ�</returns>
	bool enable(_CookieType cookie) {
		for (std::pair<const _CookieType, ForwardData>& data : this->forwarderChain) {
			if (data.first == cookie) {
				bool res = MH_EnableHook(data.second.pfnTarget) == MH_OK;
				if (res) {
					data.second.state = true;
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}

	/// <summary>
	/// �ر�һ������
	/// </summary>
	/// <returns>�Ƿ�رճɹ�</returns>
	bool disable(_CookieType cookie) {
		for (std::pair<const _CookieType, ForwardData>& data : this->forwarderChain) {
			if (data.first == cookie) {
				bool res = MH_DisableHook(data.second.pfnTarget) == MH_OK;
				if (res) {
					data.second.state = false;
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}

	/// <summary>
	/// ����һ���Ѵ����Ĺ��ӣ�����ù��Ӵ��������е�״̬����ȹرոù���
	/// </summary>
	void destroy(_CookieType cookie) {
		typename std::unordered_map<_CookieType, ForwardData>::iterator iter = this->forwarderChain.begin();
		while (iter != this->forwarderChain.end()) {
			if (iter->first == cookie) {
				if (iter->second.state)
					MH_DisableHook(iter->second.pfnTarget);
				this->forwarderChain.erase(iter++);
			}
			else {
				++iter;
			}
		}
	}

private:
	std::unordered_map<_CookieType, ForwardData> forwarderChain;

};

