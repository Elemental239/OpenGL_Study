#include "GraphicObject.h"
#include "Logger.h"

CGraphicObject::CGraphicObject() : 
	m_pParent(nullptr), 
	m_origin(CPoint()), 
	m_nAlignOption(enumValueToInt(EAlignOption::NONE)),
	m_nSizeOption(enumValueToInt(ESizeOption::NONE)),
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

	if (!obj)
		return;

	CalcAndSetNewChildParams(obj);
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

void CGraphicObject::CalcAndSetNewChildParams(TGraphicObjectRef spChild) const //TODO: implement the function
{
	if (!spChild)
		return;

	//Get all we want
	auto childMargins = spChild->GetMargins();
	auto childAlignOptions = spChild->GetAlignOptions();
	auto childSizeOptions = spChild->GetSizeOptions();

	//Prepare result variables
	CPoint resultPoint = GetOrigin();
	CSize resultSize = spChild->GetRectSize();

	//Local variables
	bool bNeedToCorrectOriginX = false;
	bool bNeedToCorrectOriginY = false;
	bool bStretchedByX = GetFlag(childSizeOptions, enumValueToInt(ESizeOption::FILL_X));
	bool bStretchedByY = GetFlag(childSizeOptions, enumValueToInt(ESizeOption::FILL_Y));

	//Process X-axis
	if (bStretchedByX)
	{
		DoStretch(EAxis::X, childMargins[0], childMargins[2], resultPoint, resultSize);
	}

	if (GetFlag(childAlignOptions, enumValueToInt(EAlignOption::RIGHT)) && !bStretchedByX)	// don't check LEFT cause it is the same as default
	{
		DoMoveToOppositeSide(EAxis::X, childMargins[0], childMargins[2], spChild->GetRectSize(), resultPoint);
	}

	if (GetFlag(childAlignOptions, enumValueToInt(EAlignOption::CENTER_X)) && !bStretchedByX)
	{
		DoMoveToCenter(EAxis::X, childMargins[0], childMargins[2], spChild->GetRectSize(), resultPoint);
	}

	//Process Y-axis
	if (bStretchedByY)
	{
		DoStretch(EAxis::Y, childMargins[3], childMargins[1], resultPoint, resultSize);
	}

	if (GetFlag(childAlignOptions, enumValueToInt(EAlignOption::TOP)) && !bStretchedByY)	// don't check BOTTOM cause it is the same as default
	{
		DoMoveToOppositeSide(EAxis::Y, childMargins[3], childMargins[1], spChild->GetRectSize(), resultPoint);
	}

	if (GetFlag(childAlignOptions, enumValueToInt(EAlignOption::CENTER_Y)) && !bStretchedByY)
	{
		DoMoveToCenter(EAxis::Y, childMargins[3], childMargins[1], spChild->GetRectSize(), resultPoint);
	}

	spChild->SetRectSize(resultSize);
	spChild->SetOrigin(resultPoint) // TODO: test me!
}

void CGraphicObject::DoStretch(EAxis axis, int childMarginBefore, int childMarginAfter, CPoint& resultPoint, CSize& resultSize) const
{
	int newSize = GetRectSize().Get(axis) - childMarginBefore - childMarginAfter;

	resultSize.Set(axis, newSize);
	resultPoint.Set(axis, resultPoint.Get(axis) + childMarginBefore);
}

void CGraphicObject::DoMoveToOppositeSide(EAxis axis, int childMarginBefore, int childMarginAfter, const CSize childRect, CPoint& resultPoint) const
{
	resultPoint.Set(axis, resultPoint.Get(axis) + GetRectSize().Get(axis) - childRect.Get(axis) - childMarginAfter);
}

void CGraphicObject::DoMoveToCenter(EAxis axis, int childMarginBefore, int childMarginAfter, const CSize childRect, CPoint& resultPoint) const
{
	int clearLength =  GetRectSize().Get(axis) - childMarginBefore - childMarginAfter;
	int result = (clearLength - childRect.Get(axis)) / 2;
	resultPoint.Set(axis, resultPoint.Get(axis) + result);
}
