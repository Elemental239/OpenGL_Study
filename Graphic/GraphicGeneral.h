#ifndef __Graphic_GraphicGeneral_H__
#define __Graphic_GraphicGeneral_H__

#include "Object.h"

class CPoint : public CObject
{
public: 
	CPoint(int x, int y) : m_nX(x), m_nY(y) {}
	CPoint(const CPoint& other) : m_nX(other.GetX()), m_nY(other.GetY()) {}
	CPoint& operator=(const CPoint& other);

	int GetX() const { return m_nX; }
	int GetY() const { return m_nY; }

private:
	int m_nX;
	int m_nY;
};

typedef unsigned short CColorPart;
#define MAX_COLOR_PART_VALUE 0xFF

enum ColorPart
{
	COLOR_PART_RED,
	COLOR_PART_BLUE,
	COLOR_PART_GREEN,
	COLOR_PART_ALPHA
};

class CColor : public CObject
{
public:
	CColor() : m_nRed(MAX_COLOR_PART_VALUE), m_nGreen(MAX_COLOR_PART_VALUE), m_nBlue(MAX_COLOR_PART_VALUE), m_nAlpha(MAX_COLOR_PART_VALUE) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue, CColorPart alpha) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(alpha) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(MAX_COLOR_PART_VALUE) { }

	float GetPart(ColorPart part) { return (1.0f * GetPartInt(part)) / MAX_COLOR_PART_VALUE; }
	int GetPartInt(ColorPart part);

	CString ToString() const override;

private:
	CColorPart m_nRed;
	CColorPart m_nGreen;
	CColorPart m_nBlue;
	CColorPart m_nAlpha;
};

#endif //__Graphic_GraphicGeneral_H__
