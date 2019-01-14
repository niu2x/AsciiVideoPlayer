#ifndef REF_COUNT_H
#define REF_COUNT_H

class RefCount{
public:
	virtual ~RefCount() = 0;
	bool unref() = 0;
	void ref() = 0;
};


class SimpleRefCount: public RefCount{

public:
	SimpleRefCount();
	virtual ~SimpleRefCount();
	bool unref();
	void ref();

private:
	uint32_t counter;
};

#endif
