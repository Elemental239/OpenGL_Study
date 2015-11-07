#ifndef __Graphic_OpenGLGraphicObject_H__
#define __Graphic_OpenGLGraphicObject_H__

#include "GraphicObject.h"
#include "SharedPtr.h"
#include "Shader.h"
#include "OpenGL.h"
#include "GraphicGeneral.h"

class COpenGLGraphicObject : public CGraphicObject
{
public:
	COpenGLGraphicObject(CPoint originPoint);
	~COpenGLGraphicObject();

	virtual void DrawSelf() override;

protected:
	CPoint m_origin;
	bool m_bInited;

	//OpenGL related
	TShaderProgramRef m_shaderProgram;
	GLuint m_VAO; // VertexArrayObject
	GLuint m_VBO; // VertexBufferObject
	GLuint m_EBO; // ElementsBufferObject
	//GLuint m_Texture;

	COpenGLPoint TranslatePixelPoint(const CPoint& point) const;
	virtual void CreateShaderProgram() = 0;
	virtual void BindVBO() = 0;
	virtual void BindEBO() = 0;
	virtual void SetupVAOAttributes() = 0;
};

#endif //__Graphic_OpenGLGraphicObject_H__
