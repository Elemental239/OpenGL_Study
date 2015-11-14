#ifndef __Graphic__Rectangle__H__
#define __Graphic__Rectangle__H__

#include "OpenGLGraphicObject.h"
#include <vector>

class CRectanglePrimitive : public COpenGLGraphicObject
{
public:
	CRectanglePrimitive(CPointWithColor p1, CPointWithColor p2, CPointWithColor p3, CPointWithColor p4, CPoint originPoint = CPoint());
	~CRectanglePrimitive();

	virtual void DrawSelf() override;
	virtual CPoint GetOrigin() override { return m_origin + static_cast<CPoint>(m_points[0]);}
	int GetHeight() { return m_points[2].GetY() - m_points[0].GetY(); }
	int GetWidth() { return m_points[2].GetX() - m_points[0].GetX(); }

protected:
	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private:
	std::vector<CPointWithColor> m_points;
};

class CRectangle : public CRectanglePrimitive
{
public:
	CRectangle(CPoint p1, CPoint p2, CColor cColor, CPoint originPoint = CPoint());
};

#endif //__Graphic__Rectangle__H__