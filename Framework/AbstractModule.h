#include "Pch.h"

#ifndef _ABSTRACT_MODULE_H_
#define _ABSTRACT_MODULE_H_

/// <summary>
/// 所有模块的基类
/// </summary>
abstract_class AbstractModule {
	
public:
	/// <summary>
	/// 获取该模块的名称
	/// </summary>
	/// <returns>模块的名称</returns>
	std::string getName() const {
		return this->name;
	}

	/// <summary>
	/// 获取该模块的别名
	/// </summary>
	/// <returns>模块的别名</returns>
	std::string getNickname() const {
		return this->nickname;
	}

	/// <summary>
	/// 获取该模块的描述
	/// </summary>
	/// <returns>模块的描述</returns>
	std::string getDescription() const {
		return this->description;
	}

	/// <summary>
	/// 切换当前模块的开关状态
	/// </summary>
	/// <returns>切换后的模块开关状态</returns>
	bool toggle() {
		this->state = !this->state;
		return this->state;
	}

protected:

	/// <summary>
	/// 名称
	/// </summary>
	std::string name;
	
	/// <summary>
	/// 别名，具体用法看个人
	/// </summary>
	std::string nickname;

	/// <summary>
	/// 描述
	/// </summary>
	std::string description;

	/// <summary>
	/// 开启状态
	/// </summary>
	bool state;

};

#endif // _ABSTRACT_MODULE_H_
