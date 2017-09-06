#include "GraphicObject.h"
#include "Logger.h"
#include "GraphicObjectPositionCalculator.h"

CGraphicObject::CGraphicObject() : 
	m_nAlignOption(enumValueToInt(EAlignOption::NONE)),
	m_nSizeOption(enumValueToInt(ESizeOption::NONE)),
	//m_containerOrigin(CPoint()),
	//m_containerSize(CSize()),
	m_bInited(false)
{
	m_margins.assign(4, 0);	// Fill with zero margins
}

void CGraphicObject::SetMargins(int left, int top, int right, int bottom)
{
	m_margins.clear();
	m_margins.push_back(left);
	m_margins.push_back(top);
	m_margins.push_back(right);
	m_margins.push_back(bottom);
}

//void CGraphicObject::AdjustSizeAndPosition()
//{
//	CGraphicObjectPositionCalculator calculator(this, m_containerOrigin, m_containerSize);
//	calculator.Calculate();
//
//	SetRectSize(calculator.GetResultSize());
//	SetOrigin(calculator.GetResultOriginPoint()); // TODO: test me!
//}
