#ifndef __Graphic_GraphicObjectPositionCalculator_H__
#define __Graphic_GraphicObjectPositionCalculator_H__

#include "GraphicGeneral.h"
#include "GraphicObject.h"

class IGraphicObjectPositionCalculator
{
public:
	IGraphicObjectPositionCalculator(CGraphicObject* pObj, CPoint containerOriginPoint, CSize containerSize);

	virtual void Calculate() = 0;

	CPoint GetResultOriginPoint() const { return m_resultPoint; };
	CSize GetResultSize() const { return m_resultSize; };

protected:
	enum class UseMarginsMode
	{
		NONE,
		AFFECT_SIZE,			// for stretched object modify size and position
		AFFECT_POSITION_BEFORE,	// Use left or bottom
		AFFECT_POSITION_AFTER,	// Use right or top
		AFFECT_POSITION_CENTER	// for centered objects
	};

	CGraphicObject* m_obj;
	CPoint m_containerOriginPoint;
	CSize m_containerSize;

	CPoint m_resultPoint;
	CSize m_resultSize;
};

class CGraphicObjectPositionCalculator : public IGraphicObjectPositionCalculator
{
public:
	CGraphicObjectPositionCalculator(CGraphicObject* pObj, CPoint containerOriginPoint, CSize containerSize) : IGraphicObjectPositionCalculator(pObj, containerOriginPoint, containerSize) {}

	virtual void Calculate() override;

private:
	// Help functions for CalcAndSetNewChildParams
	void CalcAndSetNewChildAxisParam(EAxis axis, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize);
	void DoStretch(EAxis axis, CPoint& resultPoint, CSize& resultSize);
	void DoMoveToOppositeSide(EAxis axis, const CSize childRect, CPoint& resultPoint); // Right or Top
	void DoMoveToCenter(EAxis axis, const CSize childRect, CPoint& resultPoint);
	void DoUseMargins(EAxis axis, UseMarginsMode nMarginsUsageMode, const int nMarginBefore, const int nMarginAfter, CPoint& resultPoint, CSize& resultSize);
};

#endif //__Graphic_GraphicObjectPositionCalculator_H__
