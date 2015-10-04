#ifndef __SharedPtr_H__
#define __SharedPtr_H__

#include <memory>
#include <Object.h>

template<typename T>
class CSharedPtr : public CObject
{
public:
	CSharedPtr() : sp_obj(NULL) {}
	CSharedPtr(T*);
	CSharedPtr& operator=(const CSharedPtr<T>&);
	CSharedPtr(const CSharedPtr<T>&);
	~CSharedPtr();

	operator T*() { return sp_obj.get(); }

	std::shared_ptr<T>& operator->() { return sp_obj; }
	template<typename Type> friend bool operator==(const CSharedPtr<Type>& left, const CSharedPtr<Type>& right);

	int GetCount() { return sp_obj.use_count(); }
	std::shared_ptr<T>& GetPointer() { return sp_obj; }

private:
	std::shared_ptr<T> sp_obj;
};

template<typename T>
CSharedPtr<T>::CSharedPtr(T* obj) : sp_obj(obj)
{
}

template<typename T>
CSharedPtr<T>& CSharedPtr<T>::operator=(const CSharedPtr<T>& other)
{
	sp_obj = other.sp_obj;
	return *this;
}

template<typename T>
CSharedPtr<T>::CSharedPtr(const CSharedPtr<T>& other)
{
	sp_obj = other.sp_obj;
}

template<typename T>
CSharedPtr<T>::~CSharedPtr()
{
	sp_obj = nullptr;
}

template<typename T>
bool operator==(const CSharedPtr<T>& left, const CSharedPtr<T>& right) {
	return left.sp_obj == right.sp_obj;
}

#endif //__SharedPtr_H__
