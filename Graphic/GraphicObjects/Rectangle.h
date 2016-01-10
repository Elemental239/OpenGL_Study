#ifndef __Graphic__Rectangle__H__
#define __Graphic__Rectangle__H__

#include "OpenGLGraphicObject.h"
#include <vector>

class CRectanglePrimitive : public COpenGLGraphicObject //TODO: replace with CPolygon class, as soon as we will have it
{
public:
	/**
	 * Base class for rectangle. To be correct, it can present any 4point figure, but let's think about rectangle
	 * Set points counterclockwise, starting from left-bottom point
	 */
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
	///<summary> Construct rectangle with left-bottom and right-top points</summary>
	CRectangle(CPoint p1, CPoint p2, CColor cColor, CPoint originPoint = CPoint());
	
	///<summary> Construct rectangle with left-bottom point, width and height</summary>
	CRectangle(CPoint p1, int width, int height, CColor cColor, CPoint originPoint = CPoint());
	
	///<summary> Construct rectangle with left-bottom point and size</summary>
	CRectangle(CPoint p1, CSize size, CColor cColor, CPoint originPoint = CPoint());
};

#endif //__Graphic__Rectangle__H__