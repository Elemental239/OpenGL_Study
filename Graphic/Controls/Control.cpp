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

TGraphicObjectRef CControl::GetVisualRepresentation(int index) const
{
	if (index != 0 )
		return nullptr;

	 return m_spVisualRepresentation;
}

void CControl::AddChild(TControlRef obj)
{
	MARKER("CControl::AddChildren()");

	if (!obj || !obj->GetVisualRepresentation(0))
		return;

	for (int i = 0; i < obj->GetVisualRepresentationNumber(); i++)
	{
		GetVisualRepresentation(0)->CalcAndSetNewChildParams(obj->GetVisualRepresentation(i));
	}

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
	GetVisualRepresentation(0)->DrawSelf();
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
	CPoint originPoint = GetVisualRepresentation(0)->GetOrigin();
	CPoint otherPoint = originPoint + GetVisualRepresentation(0)->GetRectSize();
	bool bXInside = point.GetX() >= originPoint.GetX() && point.GetX() <= otherPoint.GetX();  
	bool bYInside = point.GetY() >= originPoint.GetY() && point.GetY() <= otherPoint.GetY();
	bool bZInside = point.GetZ() >= originPoint.GetZ() && point.GetZ() <= otherPoint.GetZ();

	return (bXInside && bYInside && bZInside);
}
