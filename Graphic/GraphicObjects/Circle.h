#ifndef __Graphic__Circle__H__
#define __Graphic__Circle__H__

#include "OpenGLGraphicObject.h"
#include <vector>
#include <GraphicObjects/Line.h>

class CCircle : public COpenGLGraphicObject
{
public:
	static const int CIRCLE_APPROX_LINES_NUMBER = 500;

	CCircle(int nRadius, CColor cColor);

	virtual void DrawSelf() override;

protected:
	std::vector<CPoint> m_CirclePoints;
	
	void InitPoints();

	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private:
	//CPoint m_center;
	int m_nRadius;
	CColor m_cColor;
};

class CFilledCircle : public CCircle
{
public:
	CFilledCircle(int nRadius, CColor cColor) : CCircle(nRadius, cColor) { }

	virtual void DrawSelf() override;
};

#endif //__Graphic__Circle__H__