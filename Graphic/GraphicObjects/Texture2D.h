#ifndef __Graphic_Texture2D_H__
#define __Graphic_Texture2D_H__

#include "OpenGLGraphicObject.h"
#include "StringImpl.h"

class CTexture2D : public COpenGLGraphicObject
{
public:
	CTexture2D(CString8 strTexturePath, CPoint originPoint = CPoint());

	virtual void DrawSelf() override;

protected:
	virtual void CreateShaderProgram() override;
	virtual void BindVBO() override;
	virtual void BindEBO() override;
	virtual void SetupVAOAttributes() override;

private: 
	CString8 m_strTexturePath;
};

#endif //__Graphic_Texture2D_H__