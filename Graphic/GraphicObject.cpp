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
	m_margins.clear();
	m_margins.push_back(left);
	m_margins.push_back(top);
	m_margins.push_back(right);
	m_margins.push_back(bottom);
}

void CGraphicObject::CalcAndSetNewChildParams(TGraphicObjectRef spChild) const
{
	if (!spChild)
		return;

	//Prepare result variables
	CPoint resultPoint = GetOrigin();
	CSize resultSize = spChild->GetRectSize();

	auto childMargins = spChild->GetMargins();

	CalcAndSetNewChildAxisParam(EAxis::X, spChild, childMargins[0], childMargins[2], resultPoint, resultSize);
	CalcAndSetNewChildAxisParam(EAxis::Y, spChild, childMargins[3], childMargins[1], resultPoint, resultSize);

	spChild->SetRectSize(resultSize);
	spChild->SetOrigin(resultPoint); // TODO: test me!
}

void CGraphicObject::CalcAndSetNewChildAxisParam(EAxis axis, TGraphicObjectRef spChild, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize) const
{
	//Get all we want
	auto childAlignOptions = spChild->GetAlignOptions();
	auto childSizeOptions = spChild->GetSizeOptions();

	//Local variables
	bool bStretched = GetFlag(childSizeOptions, enumValueToInt(axis == EAxis::X ? ESizeOption::FILL_X : axis == EAxis::Y ? ESizeOption::FILL_Y : ESizeOption::FILL_Z));

	//Process X-axis
	if (bStretched)
	{
		DoStretch(axis, resultPoint, resultSize);
		DoUseMargins(axis, UseMarginsMode::AFFECT_SIZE, nMarginBefore, nMarginAfter, resultPoint, resultSize);
	}
	else
	{
		if (GetFlag(childAlignOptions, enumValueToInt(axis == EAxis::X ? EAlignOption::RIGHT : axis == EAxis::Y ? EAlignOption::TOP : EAlignOption::FRONT)))	// don't check LEFT, BOTTOM, BACK cause it is the same as default
		{
			DoMoveToOppositeSide(EAxis::X, spChild->GetRectSize(), resultPoint);
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_AFTER, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
		else if (GetFlag(childAlignOptions, enumValueToInt(axis == EAxis::X ? EAlignOption::CENTER_X : axis == EAxis::Y ? EAlignOption::CENTER_Y : EAlignOption::CENTER_Z)))
		{
			DoMoveToCenter(axis, spChild->GetRectSize(), resultPoint);
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_CENTER, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
		else
		{
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_BEFORE, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
	}
}

void CGraphicObject::DoStretch(EAxis axis, CPoint& resultPoint, CSize& resultSize) const
{
	int newSize = GetRectSize().Get(axis);

	resultSize.Set(axis, newSize);
}

void CGraphicObject::DoMoveToOppositeSide(EAxis axis, const CSize childRect, CPoint& resultPoint) const
{
	resultPoint.Set(axis, resultPoint.Get(axis) + GetRectSize().Get(axis) - childRect.Get(axis));
}

void CGraphicObject::DoMoveToCenter(EAxis axis, const CSize childRect, CPoint& resultPoint) const
{
	int result = (GetRectSize().Get(axis) - childRect.Get(axis)) / 2;
	resultPoint.Set(axis, resultPoint.Get(axis) + result);
}

void CGraphicObject::DoUseMargins(EAxis axis, UseMarginsMode nMarginsUsageMode, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize) const
{
	switch (nMarginsUsageMode)
	{
		case UseMarginsMode::NONE:  
			LOGW("CGraphicObject::DoUseMargins() no margins mode");
			break;

		case UseMarginsMode::AFFECT_SIZE:
			resultPoint.Set(axis, resultPoint.Get(axis) + nMarginBefore);
			resultSize.Set(axis, resultSize.Get(axis) - nMarginAfter - nMarginBefore);
			break;

		case UseMarginsMode::AFFECT_POSITION_BEFORE:
			resultPoint.Set(axis, resultPoint.Get(axis) + nMarginBefore);
			break;

		case UseMarginsMode::AFFECT_POSITION_AFTER:
			resultPoint.Set(axis, resultPoint.Get(axis) - nMarginAfter);
			break;

		case UseMarginsMode::AFFECT_POSITION_CENTER:
			resultPoint.Set(axis, resultPoint.Get(axis) - nMarginAfter + nMarginBefore);
			break;

		default:
			LOGE("CGraphicObject::DoUseMargins() unknown margins mode");
			break;
	}
}
