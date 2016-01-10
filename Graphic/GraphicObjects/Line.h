#ifndef __Graphic__Line__H__
#define __Graphic__Line__H__

#include "OpenGLGraphicObject.h"
#include <vector>

class CLine : public COpenGLGraphicObject
{
public:
	CLine(CPointWithColor pointStart, CPointWithColor cFinish, CPoint originPoint = CPoint());
	~CLine();

	virtual void DrawSelf() override;

protected:
	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private:
	CPointWithColor m_pointStart;
	CPointWithColor m_pointFinish;
};

#endif //__Graphic__Line__H__