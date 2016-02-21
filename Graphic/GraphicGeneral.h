#ifndef __Graphic_GraphicGeneral_H__
#define __Graphic_GraphicGeneral_H__

#include "Object.h"
#include "OpenGL.h"
#include "Random.h"

struct CSize;

template<class T>
class CGenericPoint : public CObject
{
public:
	CGenericPoint() : m_nX(0), m_nY(0), m_nZ(0) {}
	CGenericPoint(T x, T y) : m_nX(x), m_nY(y), m_nZ(0) {}
	CGenericPoint(T x, T y, T z) : m_nX(x), m_nY(y), m_nZ(z) {}
	CGenericPoint(const CGenericPoint<T>& other) : m_nX(other.GetX()), m_nY(other.GetY()), m_nZ(other.GetZ()) {}
	CGenericPoint<T>& operator=(const CGenericPoint<T>& other);

	friend const CGenericPoint<T> operator+(const CGenericPoint<T>& left, const CGenericPoint<T>& right)
	{
		return CGenericPoint<T>(left.GetX() + right.GetX(), left.GetY() + right.GetY(), left.GetZ() + right.GetZ());
	}
	
	T GetX() const { return m_nX; }
	T GetY() const { return m_nY; }
	T GetZ() const { return m_nZ; }

	CString8 ToString() const override { return CString8("(") + m_nX + ", " + m_nY + ", " + m_nZ + ")"; }

protected:
	T m_nX;
	T m_nY;
	T m_nZ;
};

typedef CGenericPoint<int> CPoint;
typedef CGenericPoint<GLfloat> COpenGLPoint;

template<typename T>
struct CGenericSize : public CGenericPoint<T>
{
	CGenericSize() : CGenericPoint<T>() {}
	CGenericSize(T a, T b) : CGenericPoint<T>(a,b) {}
};

struct CSize : public CGenericSize<int>
{
	CSize() : CGenericSize<int>() {}
	CSize(int a,int b) : CGenericSize<int>(a,b) {}
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
	CColor() : m_nRed(0), m_nGreen(0), m_nBlue(0), m_nAlpha(MAX_COLOR_PART_VALUE) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue, CColorPart alpha) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(alpha) { }
	CColor(CColorPart red, CColorPart green, CColorPart blue) : m_nRed(red), m_nGreen(green), m_nBlue(blue), m_nAlpha(MAX_COLOR_PART_VALUE) { }
	CColor(CStringA strColor);

	float GetPart(ColorPart part) { return (1.0f * GetPartInt(part)) / MAX_COLOR_PART_VALUE; }
	int GetPartInt(ColorPart part);

	CString8 ToString() const override;

private:
	CColorPart m_nRed;
	CColorPart m_nGreen;
	CColorPart m_nBlue;
	CColorPart m_nAlpha;
};

class CRandomColor : public CColor
{
public: 
	CRandomColor() : CColor(Random::Instance().GetIntII(0, 0xFF), 
							Random::Instance().GetIntII(0, 0xFF), 
							Random::Instance().GetIntII(0, 0xFF), 
							MAX_COLOR_PART_VALUE) {}
};


template<class T>
class CGenericPointWithColor : public CPoint
{
public:
	CGenericPointWithColor() : CGenericPoint(), m_cColor() {}
	CGenericPointWithColor(T x, T y, CColor color) : CGenericPoint(x, y, 1), m_cColor(color) {}
	CGenericPointWithColor(T x, T y, T z, CColor color) : CGenericPoint(x, y, z), m_cColor(color) {}
	CGenericPointWithColor(CGenericPoint<T> p, CColor color) : CGenericPoint(p), m_cColor(color) {}
	CGenericPointWithColor(const CGenericPointWithColor& other) : CGenericPoint(other), m_cColor(other.GetColor()) {}
	CGenericPointWithColor& operator=(const CGenericPointWithColor& other);
	CGenericPointWithColor& operator=(const CGenericPoint& other);

	CColor GetColor() const { return m_cColor; }

private:
	CColor m_cColor;
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

template<class T>
CGenericPointWithColor<T>& CGenericPointWithColor<T>::operator=(const CGenericPoint& other)
{
	if (&other == this)
		return *this;

	m_nX = other.GetX();
	m_nY = other.GetY();
	m_nZ = other.GetZ();

	return *this;
}

typedef CGenericPointWithColor<int> CPointWithColor;
typedef CGenericPointWithColor<GLfloat> COpenGLPointWithColor;

#endif //__Graphic_GraphicGeneral_H__
