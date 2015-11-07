#ifndef __Graphic_GraphicGeneral_H__
#define __Graphic_GraphicGeneral_H__

#include "Object.h"
#include "OpenGL.h"

template<class T>
class CGenericPoint : public CObject
{
public: 
	CGenericPoint(T x, T y) : m_nX(x), m_nY(y), m_nZ(0) {}
	CGenericPoint(const CGenericPoint<T>& other) : m_nX(other.GetX()), m_nY(other.GetY()), m_nZ(other.GetZ()) {}
	CGenericPoint<T>& operator=(const CGenericPoint<T>& other);

	T GetX() const { return m_nX; }
	T GetY() const { return m_nY; }
	T GetZ() const { return m_nZ; }

protected:
	T m_nX;
	T m_nY;
	T m_nZ;
};

/////////////////////////////////////////
///CGenericPoint
template<class T>
CGenericPoint<T>& CGenericPoint<T>::operator=(const CGenericPoint<T>& other)
{
	if (&other == this)
		return *this;

	m_nX = other.GetX();
	m_nY = other.GetY();
	m_nZ = other.GetZ();

	return *this;
}

typedef CGenericPoint<int> CPoint;
typedef CGenericPoint<GLfloat> COpenGLPoint;
typedef CGenericPoint<int> CSize;



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

template<class T>
class CGenericPointWithColor : public CPoint
{
public:
	CGenericPointWithColor(T x, T y, T z, CColor color) : CGenericPointWithColor(x, y, z), m_cColor(color) {}
	CGenericPointWithColor(const CGenericPointWithColor& other) : CPoint(other), m_cColor(other.GetColor()) {}
	CGenericPointWithColor& operator=(const CGenericPointWithColor& other);

	CColor GetColor() const { return m_cColor; }

private:
	CColor m_cColor;
};

/////////////////////////////////////////
///CGenericPointWithColor
template<class T>
CGenericPointWithColor<T>& CGenericPointWithColor<T>::operator=(const CGenericPointWithColor<T>& other)
{
	if (&other == this)
		return *this;

	m_nX = other.GetX();
	m_nY = other.GetY();
	m_nZ = other.GetZ();
	m_cColor = other.GetColor();

	return *this;
}

typedef CGenericPointWithColor<int> CPointWithColor;
typedef CGenericPointWithColor<GLfloat> COpenGLPointWithColor;

#endif //__Graphic_GraphicGeneral_H__
