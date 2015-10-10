#ifndef __GraphicGeneral_H__
#define __GraphicGeneral_H__

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

#endif //__GraphicGeneral_H__
