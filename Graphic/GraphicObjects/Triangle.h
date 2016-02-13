#ifndef __Graphic__Triangle__H__
#define __Graphic__Triangle__H__

#include "OpenGLGraphicObject.h"
#include <vector>

class CTrianglePrimitive : public COpenGLGraphicObject
{
public:
	CTrianglePrimitive(CPointWithColor p1, CPointWithColor p2, CPointWithColor p3);
	~CTrianglePrimitive();

	virtual void DrawSelf() override;

protected:
	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private:
	std::vector<CPointWithColor> m_points;
};

class CTriangle : public CTrianglePrimitive
{
public:
	CTriangle(CPoint p1, CPoint p2, CPoint p3, CColor cColor) : 
		CTrianglePrimitive(CPointWithColor(p1, cColor),
						   CPointWithColor(p2, cColor),
						   CPointWithColor(p3, cColor))
	{ 
	}
};

#endif //__Graphic__Triangle__H__