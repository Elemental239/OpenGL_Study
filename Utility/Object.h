#ifndef __Utility_OBJECT_H__
#define __Utility_OBJECT_H__

#include "StringImpl.h"

class CObject
{
public:
	CObject() {}
	virtual ~CObject() {}

	virtual CString8 ToString() const { return "CObject"; }
};

#endif //__Utility_OBJECT_H__
