#ifndef SINGLETON_H
#define	SINGLETON_H
#include <cstddef>
#include "iostream"

template<class T>
class TSingleton {
protected:
	static T *pSingleton;

public:
	virtual ~TSingleton() { }

	static T* GetInstance() {
		if (!pSingleton) {
			pSingleton = new T;
		}
		return (pSingleton);
	}

	static void DeleteInstance() {
		if (pSingleton) {
			delete (pSingleton);
			pSingleton = NULL;
		}
	}
};

template<class T>
T* TSingleton<T>::pSingleton = nullptr;

#endif