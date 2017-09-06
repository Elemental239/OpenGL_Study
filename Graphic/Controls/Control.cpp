#include "Control.h"
#include "Logger.h"

///////////////////////////////////////////////////////
///IControl
IControl::IControl(TGraphicObjectRef representation)
{
	representation->SetOwner(this);
	m_visualPresentations.push_back(representation);
}

///////////////////////////////////////////////////////
///CControl
CControl::CControl(TGraphicObjectRef representation /* = new CGraphicObject()*/) : IControl(representation)
{
}

void CControl::SetVisualPresentation(TGraphicObjectRef graphicObject, int nOrdinal/* = 0*/)
{
	if (nOrdinal >= static_cast<int>(m_visualPresentations.size()))
	{
		m_visualPresentations.push_back(graphicObject);
		return;
	}

	m_visualPresentations[nOrdinal] = graphicObject;
}

TGraphicObjectRef CControl::GetVisualPresentation(int index) const
{
	if (index != 0 )
		return nullptr;

	 return m_visualPresentations[0];
}

void CControl::AdjustGraphicPresentations(CPoint origin, CSize size)
{
	for (auto iter = m_visualPresentations.begin(); iter != m_visualPresentations.end(); ++iter)
	{
		(*iter)->SetContainerParams(origin, size);
	}
}

void CControl::AddChild(TControlRef obj)
{
	MARKER("CControl::AddChildren()");

	if (!obj || !obj->GetVisualPresentation(0))
		return;

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
	GetVisualPresentation(0)->DrawSelf();
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		DrawChild(*iter);
	}
}

void CControl::DrawChild(TControlRef spControl)
{
	auto spCurrentVisualPresentation = GetCurrentVisualPresentation();

	for (int i = 0; i < spControl->GetVisualPresentationNumber(); i++)
	{
		spControl->AdjustGraphicPresentations(spCurrentVisualPresentation->GetOrigin(), spCurrentVisualPresentation->GetRectSize());
	}

	spControl->Draw();
}

bool CControl::OnSystemEvent(const EventData& event)
{
	if (event.m_nEventType == EVT_RESIZE)
	{
		LOG("Resize event");
		for (int i = 0; i < GetVisualPresentationNumber(); i++)
		{
			GetVisualPresentation(i)->Reinitialize();
		}
	}

	return false;
}

bool CControl::OnSignal(const SignalData& signal)
{
	return false;
}

bool CControl::IsPointInsideMyBounds(const CPoint& point) const
{
	CPoint originPoint = GetCurrentVisualPresentation()->GetOrigin();
	CPoint otherPoint = originPoint + GetCurrentVisualPresentation()->GetRectSize();
	bool bXInside = point.GetX() >= originPoint.GetX() && point.GetX() <= otherPoint.GetX();  
	bool bYInside = point.GetY() >= originPoint.GetY() && point.GetY() <= otherPoint.GetY();
	bool bZInside = point.GetZ() >= originPoint.GetZ() && point.GetZ() <= otherPoint.GetZ();

	return (bXInside && bYInside && bZInside);
}
