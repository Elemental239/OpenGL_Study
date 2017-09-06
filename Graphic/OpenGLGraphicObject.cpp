#include "OpenGLGraphicObject.h"
#include "Logger.h"
#include "WindowManager.h"
#include "Window.h"

COpenGLGraphicObject::COpenGLGraphicObject()
{
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);
}

COpenGLGraphicObject::~COpenGLGraphicObject()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
}

void COpenGLGraphicObject::DrawSelf()
{
	__super::DrawSelf();

	if (!m_bInited)
	{
		m_bInited = true;

		// Open VAO, fill VBO & EBO with data, set attributes, close VAO
		glBindVertexArray(m_VAO);
			BindVBO();
			BindEBO();
			SetupVAOAttributes();
		glBindVertexArray(0);
		CreateShaderProgram();
	}

	if (m_shaderProgram)
	{
		m_shaderProgram->Use();
	}
}

COpenGLPoint COpenGLGraphicObject::TranslatePixelPoint(const CPoint& point) const
{
	CSize szWindowSize = CWindowManagerProvider::Instance().GetWindowManager()->GetActiveWindow()->GetSize();

	GLfloat xFloat = (2.0f * (point.GetX() + m_origin.GetX())) / szWindowSize.GetX() - 1;
	GLfloat yFloat = (2.0f * (point.GetY() + m_origin.GetY())) / szWindowSize.GetY() - 1;
	GLfloat zFloat = 1.0f * point.GetZ();

	return COpenGLPoint(xFloat, yFloat, zFloat);
}
