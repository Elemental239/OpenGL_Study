#include "Control.h"
#include "Logger.h"

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
	//spControl->AdjustGraphicPresentations(spCurrentVisualPresentation->GetOrigin(), spCurrentVisualPresentation->GetRectSize());

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
