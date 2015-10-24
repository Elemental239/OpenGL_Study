#ifndef __Graphic_GraphicGeneral_H__
#define __Graphic_GraphicGeneral_H__

#include "Object.h"

class CPoint : public CObject
{
public: 
	CPoint(int x, int y) : m_nX(x), m_nY(y) {}
	void CPoint(const CPoint& other) = default;
	void operator=(const CPoint& other) = default;

	int GetX() { return m_nX; }
	int GetY() { return m_nY; }

private:
	int m_nX;
	int m_nY;
}

typedef unsigned short CColorPart;

class CColor : public CObject
{
public:
	CColor() : m_nRed(0xFF), m_nGreen(0xFF), m_nBlue(0xFF), m_nAlpha(0xFF) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue, CColorPart alpha) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(alpha) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(0xFF) { }

private:
	CColorPart m_nRed;
	CColorPart m_nGreen;
	CColorPart m_nBlue;
	CColorPart m_nAlpha;
};

#endif //__Graphic_GraphicGeneral_H__
