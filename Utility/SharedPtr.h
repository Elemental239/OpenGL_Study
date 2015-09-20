#ifndef __SharedPtr_H__
#define __SharedPtr_H__

#include <memory>

template<typename T>
class CSharedPtr
{
public:
	CSharedPtr() : sp_obj(NULL) {}
	CSharedPtr(T*);
	CSharedPtr& operator=(const CSharedPtr<T>&);
	CSharedPtr(const CSharedPtr<T>&);
	~CSharedPtr();

	int GetCount() { return sp_obj.use_count(); }

	std::shared_ptr sp_obj;
};

template<typename T>
CSharedPtr<T>::CSharedPtr(T* obj)
{
	sp_obj = make_shared<T>(obj);
}

template<typename T>
CSharedPtr<T>& CSharedPtr<T>::operator=(const CSharedPtr<T>& other)
{
	sp_obj = other.sp_obj;
}

template<typename T>
CSharedPtr<T>::CSharedPtr(const CSharedPtr<T>& other)
{
	sp_obj = other.sp_obj;
}

template<typename T>
CSharedPtr<T>::~CSharedPtr()
{
	sp_obj = NULL;
}


#endif //__SharedPtr_H__