#ifndef __Utility_Stack_H__
#define __Utility_Stack_H__

#include <vector>

template <class T>
class CStack
{
public:
	void pop() { if (m_container.size() > 0) m_container.pop_back(); }
	void push(const T& obj) { m_container.push_back(obj); }
	T& top() { return m_container[m_container.size() - 1]; }
	int size() { return m_container.size(); }
	T& operator[](int index) { return m_container[index]; }

private:
	std::vector<T> m_container;
};

#endif //__Utility_Stack_H__