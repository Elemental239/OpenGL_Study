#include "GraphicObject.h"
#include "Logger.h"

CGraphicObject::CGraphicObject() : m_pParent(nullptr)
{
}

CGraphicObject::~CGraphicObject()
{
}

void CGraphicObject::Draw()
{
	DrawSelf();
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->Draw();
	}
}

void CGraphicObject::AddChild(TGraphicObjectRef obj)
{
	MARKER("CGraphicObject::AddChildren()");

	m_children.push_back(obj);
	obj->SetParent(this);
}

void CGraphicObject::RemoveChild(TGraphicObjectRef obj)
{
	MARKER("CGraphicObject::RemoveChildren()");

	for (auto iter = m_children.end(); iter-- != m_children.begin(); )
	{
		if ((*iter) == obj)
			m_children.erase(iter);
	}

	obj->SetParent(nullptr);
}
