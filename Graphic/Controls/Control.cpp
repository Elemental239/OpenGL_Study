#include "Control.h"
#include "Logger.h"

///////////////////////////////////////////////////////
///IControl
IControl::IControl(TGraphicObjectRef representation)
{
	m_spVisualRepresentation = representation;
}

///////////////////////////////////////////////////////
///CControl
CControl::CControl(TGraphicObjectRef representation /* = new CGraphicObject()*/) : IControl(representation)
{
}

void CControl::SetVisualRepresentation(TGraphicObjectRef graphicObject)
{
	m_spVisualRepresentation = graphicObject;
}

void CControl::AddChild(TControlRef obj)
{
	MARKER("CControl::AddChildren()");

	if (!obj || !obj->GetVisualRepresentation())
		return;

	GetVisualRepresentation()->CalcAndSetNewChildParams(obj->GetVisualRepresentation());
	obj->SetParent(this);
	m_children.push_back(obj);
}

void CControl::RemoveChild(TControlRef obj)
{
	MARKER("CControl::RemoveChildren()");

	for (auto iter = m_children.end(); iter-- != m_children.begin(); )
	{
		if ((*iter) == obj)
			m_children.erase(iter);
	}

	obj->SetParent(nullptr);
}

void CControl::RemoveChildren()
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->SetParent(nullptr);
	}

	m_children.erase(m_children.begin(), m_children.end());
}

void CControl::Draw()
{
	GetVisualRepresentation()->DrawSelf();
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->Draw();
	}
}

bool CControl::OnSystemEvent(const EventData& event)
{
	return false;
}

bool CControl::OnSignal(const SignalData& signal)
{
	return false;
}

bool CControl::IsPointInsideMyBounds(const CPoint& point) const
{
	CPoint originPoint = GetVisualRepresentation()->GetOrigin();
	CPoint otherPoint = originPoint + GetVisualRepresentation()->GetRectSize();
	bool bXInside = point.GetX() >= originPoint.GetX() && point.GetX() <= otherPoint.GetX();  
	bool bYInside = point.GetY() >= originPoint.GetY() && point.GetY() <= otherPoint.GetY();
	bool bZInside = point.GetZ() >= originPoint.GetZ() && point.GetZ() <= otherPoint.GetZ();

	return (bXInside && bYInside && bZInside);
}
