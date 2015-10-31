#ifndef __Utility_Singleton_H__
#define __Utility_Singleton_H__

#define SINGLETON(Type, constructor) \
	public:				\
		static Type& Instance() { static Type m_singleton; return m_singleton; } \
		virtual ~Type(); \
	private: \
		constructor; \
		Type& operator=(const Type&); \
		Type(const Type&); \
	public:

#endif __Utility_Singleton_H__