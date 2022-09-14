#include "Pch.h"

#ifndef _ABSTRACT_MODULE_H_
#define _ABSTRACT_MODULE_H_

/// <summary>
/// ����ģ��Ļ���
/// </summary>
abstract_class AbstractModule {
	
public:
	/// <summary>
	/// ��ȡ��ģ�������
	/// </summary>
	/// <returns>ģ�������</returns>
	std::string getName() const {
		return this->name;
	}

	/// <summary>
	/// ��ȡ��ģ��ı���
	/// </summary>
	/// <returns>ģ��ı���</returns>
	std::string getNickname() const {
		return this->nickname;
	}

	/// <summary>
	/// ��ȡ��ģ�������
	/// </summary>
	/// <returns>ģ�������</returns>
	std::string getDescription() const {
		return this->description;
	}

	/// <summary>
	/// �л���ǰģ��Ŀ���״̬
	/// </summary>
	/// <returns>�л����ģ�鿪��״̬</returns>
	bool toggle() {
		this->state = !this->state;
		return this->state;
	}

protected:

	/// <summary>
	/// ����
	/// </summary>
	std::string name;
	
	/// <summary>
	/// �����������÷�������
	/// </summary>
	std::string nickname;

	/// <summary>
	/// ����
	/// </summary>
	std::string description;

	/// <summary>
	/// ����״̬
	/// </summary>
	bool state;

};

#endif // _ABSTRACT_MODULE_H_
