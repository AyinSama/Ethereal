#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#define Instance(_ClassName) Singleton<_ClassName>().getInstance()
#define SingleObject(_ClassName) friend class Singleton<_ClassName>;

template <class Clazz>
class Singleton {

public:
	static Clazz& getInstance();

private:
	static Clazz* instance;

};

template <class Clazz>
Clazz* Singleton<Clazz>::instance = nullptr;

template <class Clazz>
Clazz& Singleton<Clazz>::getInstance() {
	if (instance == nullptr)
		instance = new Clazz();
	return *instance;
}

#endif // _SINGLETON_H_
