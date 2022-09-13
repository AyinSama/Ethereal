#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#define Instance(_ClassName) Singleton<_ClassName>().getInstance()
#define SingleObject(_ClassName) friend class Singleton<_ClassName>;

/// <summary>
/// 单例模板基类，这里不删除拷贝构造是个人代码习惯
/// </summary>
/// <typeparam name="Clazz">派生类</typeparam>
template <class Clazz>
class Singleton {

public:
	static Clazz& getInstance() {
		static Clazz* instance = new Clazz;
		return *instance;
	}

	virtual ~Singleton() = default;
	Singleton& operator=(const Singleton&) = delete;
};

#endif // _SINGLETON_H_
