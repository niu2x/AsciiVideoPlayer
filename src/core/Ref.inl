void Reference::ref()
{
	refCount.ref();
}

void Reference::unref()
{
	if(refCount.unref()){
		delete this;
	}
}

template<class T>
Ref<T>::Ref()
:ptr(nullptr)
{

}

template<class T>
Ref<T>::Ref(T *p)
:ptr(p)
{	
	if(ptr != nullptr)
		ptr->ref();
}

template<class T>
Ref<T>::Ref(const Ref &other)
:Ref()
{
	*this = other;
}

template<class T>
Ref<T>& Ref<T>::operator=(const Ref<T> &other)
{
	if(this != &other){
		if(this->ptr != other.ptr){
			if(this->ptr != nullptr){
				this->ptr->unref();
			}
			this->ptr = other.ptr;
			if(this->ptr != nullptr){
				this->ptr->ref();
			}
		}
	}
	return *this;
}

#include <stdio.h>

template<class T>
Ref<T>::~Ref()
{	
	if(ptr != nullptr)
	{
		ptr->unref();
	}
	ptr = nullptr;
}