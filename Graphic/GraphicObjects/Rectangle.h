#ifndef __Graphic__Rectangle__H__
#define __Graphic__Rectangle__H__

#include "OpenGLGraphicObject.h"
#include <vector>

class CRectanglePrimitive : public COpenGLGraphicObject //TODO: replace with CPolygon class, as soon as we will have it
{
public:
	///<summary>Base class for rectangle. Each corner has it's own color.</summary>
	CRectanglePrimitive(CSize size, CColor cColorLeftBottom, CColor cColorLeftTop, CColor cColorRightTop, CColor cColorRightBottom);

	virtual void DrawSelf() override;
	int GetHeight() { return GetRectSize().GetY(); }
	int GetWidth() { return GetRectSize().GetX(); }

protected:
	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private:
	std::vector<CColor> m_colors;
	std::vector<CPointWithColor> m_points;
};

class CRectangle : public CRectanglePrimitive
{
public:
	CRectangle(CSize size, CColor cColor) : CRectanglePrimitive(size, cColor, cColor, cColor, cColor) { }
};

#endif //__Graphic__Rectangle__H__