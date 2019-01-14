#ifndef REF_H
#define REF_H

#include "RefCount.h"
#include "log.h"

class Reference{
public:
	virtual ~Reference() {};
	void ref();
	void unref();
	Reference(){}
private:
	Reference(const Reference &);
	Reference &operator=(const Reference &);
	SimpleRefCount refCount;
};

template<class T>
class Ref{
public:
	T * operator->(){return ptr;}
	const T * operator->() const {return ptr;}
	Ref();
	Ref(T *);
	~Ref();
	Ref(const Ref &);
	Ref& operator=(const Ref &);
	bool operator==(const Ref &other) {return ptr == other.ptr;}
	operator T *(){return ptr;}
private:
	T * ptr;
};

#include "Ref.inl"

#endif