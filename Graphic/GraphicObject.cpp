#include "GraphicObject.h"
#include "Logger.h"

CGraphicObject::CGraphicObject() : 
	m_pParent(nullptr), 
	m_origin(CPoint()), 
	m_nAlignOptionX(EAlignOption::NONE),
	m_nAlignOptionY(EAlignOption::NONE),
	m_rectSize(CSize())
{
	m_margins.assign(4, 0);	// Fill with zero margins
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

	obj->SetOrigin(CalcChildOriginPoint(obj));
	obj->SetParent(this);
	m_children.push_back(obj);
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

void CGraphicObject::SetMargins(int left, int top, int right, int bottom)
{
	m_margins.push_back(left);
	m_margins.push_back(top);
	m_margins.push_back(right);
	m_margins.push_back(bottom);
}

CPoint CGraphicObject::CalcChildOriginPoint(TGraphicObjectRef child)
{
	return child->GetOrigin();
}
