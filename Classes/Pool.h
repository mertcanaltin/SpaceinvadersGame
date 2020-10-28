#ifndef __SPRITE_POOL_H_
#define __SPRITE_POOL_H_

#include <list>
// list havuzu  yok edilen gemiler ve iade nesnesi oluşturmak için
template <class T> class Pool
{
public:
	Pool() { }

public:
    //geri al
	void returnObject(T* obj) {
		_pool.push_back(obj);
	}
	//havuzdan nesne al
	T* getOne() {
		if (_pool.empty()) {
			return new T;
		}
		T* first = _pool.front();
		_pool.pop_front();
		return first;
	}
//yok et
	void destroy() {
		typename std::list<T*>::iterator it;
		for (it = _pool.begin(); it != _pool.end(); ++it) {
			delete *it;
		}
	}

protected:
	std::list<T*> _pool;
};

#endif
