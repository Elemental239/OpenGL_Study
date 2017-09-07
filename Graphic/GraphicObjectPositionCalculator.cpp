#include "GraphicObjectPositionCalculator.h"
#include "Logger.h"

//////////////////////////////////
///IGraphicObjectPositionCalculator
IGraphicObjectPositionCalculator::IGraphicObjectPositionCalculator(CGraphicObject* pObj, CPoint containerOriginPoint, CSize containerSize) : 
	m_obj(pObj), 
	m_containerOriginPoint(containerOriginPoint),
	m_containerSize(containerSize)
{
}

//////////////////////////////////
///CGraphicObjectPositionCalculator
void CGraphicObjectPositionCalculator::Calculate()
{
	auto margins = m_obj->GetMargins();

	m_resultPoint = m_containerOriginPoint;
	m_resultSize = m_obj->GetSize();

	CalcAndSetNewChildAxisParam(EAxis::X, margins[0], margins[2], m_resultPoint, m_resultSize);
	CalcAndSetNewChildAxisParam(EAxis::Y, margins[3], margins[1], m_resultPoint, m_resultSize);
}

void CGraphicObjectPositionCalculator::CalcAndSetNewChildAxisParam(EAxis axis, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize)
{
	//Get all we want
	auto childAlignOptions = m_obj->GetAlignOptions();
	auto childSizeOptions = m_obj->GetSizeOptions();

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
			DoMoveToOppositeSide(axis, m_obj->GetSize(), resultPoint);
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_AFTER, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
		else if (GetFlag(childAlignOptions, enumValueToInt(axis == EAxis::X ? EAlignOption::CENTER_X : axis == EAxis::Y ? EAlignOption::CENTER_Y : EAlignOption::CENTER_Z)))
		{
			DoMoveToCenter(axis, m_obj->GetSize(), resultPoint);
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_CENTER, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
		else
		{
			DoUseMargins(axis, UseMarginsMode::AFFECT_POSITION_BEFORE, nMarginBefore, nMarginAfter, resultPoint, resultSize);
		}
	}
}

void CGraphicObjectPositionCalculator::DoStretch(EAxis axis, CPoint& resultPoint, CSize& resultSize)
{
	int newSize = m_containerSize.Get(axis);

	resultSize.Set(axis, newSize);
}

void CGraphicObjectPositionCalculator::DoMoveToOppositeSide(EAxis axis, const CSize childRect, CPoint& resultPoint)
{
	resultPoint.Set(axis, resultPoint.Get(axis) + m_containerSize.Get(axis) - childRect.Get(axis));
}

void CGraphicObjectPositionCalculator::DoMoveToCenter(EAxis axis, const CSize childRect, CPoint& resultPoint)
{
	int result = (m_containerSize.Get(axis) - childRect.Get(axis)) / 2;
	resultPoint.Set(axis, resultPoint.Get(axis) + result);
}

void CGraphicObjectPositionCalculator::DoUseMargins(EAxis axis, UseMarginsMode nMarginsUsageMode, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize)
{
	switch (nMarginsUsageMode)
	{
		case UseMarginsMode::NONE:  
			LOGW("CGraphicObjectPositionCalculator::DoUseMargins() no margins mode");
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
			LOGE("CGraphicObjectPositionCalculator::DoUseMargins() unknown margins mode");
			break;
	}
}
