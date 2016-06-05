#include "GraphicObject.h"
#include "Logger.h"
#include "GraphicObjectPositionCalculator.h"

CGraphicObject::CGraphicObject() : 
	m_origin(CPoint()), 
	m_nAlignOption(enumValueToInt(EAlignOption::NONE)),
	m_nSizeOption(enumValueToInt(ESizeOption::NONE)),
	m_rectSize(CSize()),
	m_containerOrigin(CPoint()),
	m_containerSize(CSize())
{
	m_margins.assign(4, 0);	// Fill with zero margins
}

CGraphicObject::~CGraphicObject()
{
}

void CGraphicObject::SetMargins(int left, int top, int right, int bottom)
{
	m_margins.clear();
	m_margins.push_back(left);
	m_margins.push_back(top);
	m_margins.push_back(right);
	m_margins.push_back(bottom);
}

void CGraphicObject::DrawSelf()
{

}

void CGraphicObject::AdjustSizeAndPosition()
{
	//Prepare result variables
	CPoint resultPoint = GetOrigin();
	CSize resultSize = GetRectSize();
	auto margins = GetMargins();

	CGraphicObjectPositionCalculator calculator(this, m_containerOrigin, m_containerSize);
	calculator.Calculate(); //TODO: TEST that copy constructor wasn't called

	//CalcAndSetNewChildAxisParam(EAxis::X, spChild, childMargins[0], childMargins[2], resultPoint, resultSize);
	//CalcAndSetNewChildAxisParam(EAxis::Y, spChild, childMargins[3], childMargins[1], resultPoint, resultSize);

	SetRectSize(calculator.GetResultSize());
	SetOrigin(calculator.GetResultOriginPoint()); // TODO: test me!
}
