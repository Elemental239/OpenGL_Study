#ifndef __Graphic_OpenGLGraphicObject_H__
#define __Graphic_OpenGLGraphicObject_H__

// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window  - now it is the main course
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/
//
// GLFW documentation: http://www.glfw.org/docs/latest/window.html

#include "GraphicObject.h"
#include "SharedPtr.h"
#include "Shader.h"
#include "OpenGL.h"
#include "GraphicGeneral.h"

class COpenGLGraphicObject : public CGraphicObject
{
public:
	COpenGLGraphicObject();
	virtual ~COpenGLGraphicObject();

	virtual void DrawSelf() override;

protected:
	bool m_bInited;

	//OpenGL related
	TShaderProgramRef m_shaderProgram;
	GLuint m_VAO; // VertexArrayObject
	GLuint m_VBO; // VertexBufferObject
	GLuint m_EBO; // ElementsBufferObject
	//GLuint m_Texture; // Not used for now

	COpenGLPoint TranslatePixelPoint(const CPoint& point) const;
	virtual void CreateShaderProgram() = 0;
	virtual void BindVBO() = 0;
	virtual void BindEBO() = 0;
	virtual void SetupVAOAttributes() = 0;
};

#endif //__Graphic_OpenGLGraphicObject_H__
