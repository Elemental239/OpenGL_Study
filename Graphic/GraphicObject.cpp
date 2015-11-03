#include "GraphicObject.h"
#include "Logger.h"

CGraphicObject::CGraphicObject()
{
	MARKER("CGraphicObject::CGraphicObject()");
}

CGraphicObject::~CGraphicObject()
{
	MARKER("CGraphicObject::~CGraphicObject()");
}

void CGraphicObject::AddChildren(CGraphicObjectRef obj)
{
	MARKER("CGraphicObject::AddChildren()");

	m_children.push_back(obj);
}

void CGraphicObject::RemoveChildren(CGraphicObjectRef obj)
{
	MARKER("CGraphicObject::RemoveChildren()");

	for (auto iter = m_children.end(); iter-- != m_children.begin(); )
	{
		if ((*iter) == obj)
			m_children.erase(iter);
	}
}
