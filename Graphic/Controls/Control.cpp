#include "Control.h"
#include "Logger.h"

IControl::IControl() : m_pParent(nullptr)
{
}

void IControl::AddChild(CSharedPtr<IControl>& obj)
{
	if (!obj)
		return;

	obj->SetParent(this);
	m_children.push_back(obj);
}

void IControl::RemoveChild(CSharedPtr<IControl> obj)
{
	for (auto iter = m_children.end(); iter-- != m_children.begin(); )
	{
		if ((*iter) == obj)
			m_children.erase(iter);
	}

	obj->SetParent(nullptr);
}

void IControl::RemoveChildren()
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->SetParent(nullptr);
	}

	m_children.erase(m_children.begin(), m_children.end());
}

///////////////////////////////////////////////////////
///CControl
CControl::CControl()
{
}

void CControl::Draw()
{
	DrawSelf();

	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		DrawChild(*iter);
	}
}

void CControl::DrawChild(TControlRef spControl)
{
	spControl->AdjustPositionAndSize();
	spControl->Draw();
}

bool CControl::OnSystemEvent(const EventData& event)
{
	if (event.m_nEventType == EVT_RESIZE)
	{
		LOG("Resize event");
		//for (int i = 0; i < GetVisualPresentationNumber(); i++)
		//{
		//	GetVisualPresentation(i)->Reinitialize();
		//}
	}

	return false;
}

bool CControl::OnSignal(const SignalData& signal)
{
	return false;
}

bool CControl::IsPointInsideMyBounds(const CPoint& point) const
{
	CPoint originPoint = GetOrigin();
	CPoint otherPoint = originPoint + GetSize();
	bool bXInside = point.GetX() >= originPoint.GetX() && point.GetX() <= otherPoint.GetX();  
	bool bYInside = point.GetY() >= originPoint.GetY() && point.GetY() <= otherPoint.GetY();
	bool bZInside = point.GetZ() >= originPoint.GetZ() && point.GetZ() <= otherPoint.GetZ();

	return (bXInside && bYInside && bZInside);
}
