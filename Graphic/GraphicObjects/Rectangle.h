#ifndef __Graphic__Rectangle__H__
#define __Graphic__Rectangle__H__

#include "OpenGLGraphicObject.h"
#include <vector>
#include "Logger.h"

class CRectanglePrimitive : public COpenGLGraphicObject //TODO: replace with CPolygon class, as soon as we will have it
{
public:
	///<summary>Base class for rectangle. Each corner has it's own color.</summary>
	CRectanglePrimitive(CSize size, CColor cColorLeftBottom, CColor cColorLeftTop, CColor cColorRightTop, CColor cColorRightBottom);
	virtual ~CRectanglePrimitive()
	{
		MARKER("CRectanglePrimitive::~CRectanglePrimitive()");
	}

	virtual void DrawSelf() override;
	int GetHeight() { return GetSize().GetY(); }
	int GetWidth() { return GetSize().GetX(); }

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

class CRandomColorRectangle : public CRectanglePrimitive
{
public:
	CRandomColorRectangle(CSize size) : CRectanglePrimitive(size, CRandomColor(), CRandomColor(), CRandomColor(), CRandomColor()) { }
};

#endif //__Graphic__Rectangle__H__