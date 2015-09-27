#ifndef __LISTENERS_H__
#define __LISTENERS_H__

#include <map>

#define DECLARE_LISTENERS_EX(type, prefix)												\
	private:																	\
		typedef type TListener##prefix;													\
		std::map<type*, int> m_##prefix##_listeners;							\
	public:																		\
		void RegisterListener(type* pNew) { m_##prefix##_listeners.insert(std::pair<type*, int>(pNew, 1)); }	\
		void UnregisterListener(type* pOld) { m_##prefix##_listeners.erase(pOld); }		
	

#define DECLARE_LISTENERS(type) DECLARE_LISTENERS_EX(type,)
#define DECLARE_ADDITIONAL_LISTENERS(type) DECLARE_LISTENERS_EX(type, type)

#define CALL_LISTENERS_EX(op, type)		\
	{									\
		for (auto it = m_##type##_listeners.begin(); it != m_##type##_listeners.end(); ++it) \
		{								\
			if (it->first != nullptr)	\
				((TListener##type*)(it->first))->op;			\
		}								\
	}

#define CALL_LISTENERS(op) CALL_LISTENERS_EX(op,)
#define CALL_ADDITIONAL_LISTENERS(type, op) CALL_LISTENERS_EX(op, type)


#endif //__LISTENERS_H__
