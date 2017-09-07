#include "GraphicObject.h"
#include "Logger.h"
#include "GraphicObjectPositionCalculator.h"

CGraphicObject::CGraphicObject() : 
	m_nAlignOption(enumValueToInt(EAlignOption::NONE)),
	m_nSizeOption(enumValueToInt(ESizeOption::NONE)),
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

void CGraphicObject::AdjustPositionAndSize()
{
	auto pParent = GetParent();

	if (!pParent)
		return;

	CPoint parentOrigin = pParent->GetOrigin();
	CSize parentSize = pParent->GetSize();

	CGraphicObjectPositionCalculator calculator(this, parentOrigin, parentSize);
	calculator.Calculate();
	
	SetSize(calculator.GetResultSize());
	SetOrigin(calculator.GetResultOriginPoint()); // TODO: test me!
}

