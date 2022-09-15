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
/// 基于Minhook库再封装的模块
/// Cookie这个概念是借鉴内核里注册注册表回调的那个Cookie
/// 用于标识每一个已创建的钩子
/// Cookie的类型确定下来了就不要改
/// </summary>
/// <typeparam name="_CookieType">唯一标识符的数据类型</typeparam>
class Forwarder : public Singleton<Forwarder<_CookieType>> {

public:
	Forwarder() {
		MH_Initialize();
	}

	~Forwarder() {
		MH_Uninitialize();
	}

	/// <summary>
	/// 创建一个钩子
	/// </summary>
	/// <returns>是否创建成功</returns>
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
	/// 启动一个钩子
	/// </summary>
	/// <returns>是否启动成功</returns>
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
	/// 关闭一个钩子
	/// </summary>
	/// <returns>是否关闭成功</returns>
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
	/// 销毁一个已创建的钩子，如果该钩子处于启动中的状态则会先关闭该钩子
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

