#ifndef REF_COUNT_H
#define REF_COUNT_H

#include "type.h"

class SimpleRefCount{
public:
	SimpleRefCount():counter(0){}
	virtual ~SimpleRefCount(){}
	inline bool unref(){
		return --counter == 0;
	}
	inline void ref(){
		counter ++;
	}
private:
	uint32_t counter;
};

#endif
