#ifndef __Graphic_OpenGLGraphicObject_H__
#define __Graphic_OpenGLGraphicObject_H__

#include "GraphicObject.h"
#include "SharedPtr.h"
#include "Shader.h"

class COpenGLGraphicObject : public CGraphicObject
{
public:
	COpenGLGraphicObject();
	~COpenGLGraphicObject();

private:
	CSharedPtr<CShaderProgram> m_shaderProgram;
};

#endif //__Graphic_OpenGLGraphicObject_H__
