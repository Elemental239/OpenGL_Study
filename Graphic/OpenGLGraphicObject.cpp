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
	CControl::DrawSelf();

	if (!m_bInited)
	{
		m_bInited = true;

		// Open VAO, fill VBO & EBO with data, set attributes, close VAO
		glBindVertexArray(m_VAO);
			BindVBO();
			BindEBO();
			SetupVAOAttributes();
		glBindVertexArray(0);
		
		if (!m_spShaderProgram)
		{
			CreateShaderProgram();
		}
	}

	if (m_spShaderProgram)
	{
		m_spShaderProgram->Use();
	}
	else
	{
		LOGE("No shader program for COpenGLGraphicObject");
	}
}

COpenGLPoint COpenGLGraphicObject::TranslatePixelPoint(const CPoint& point) const
{
	CSize szWindowSize = CWindowManagerProvider::Instance().GetWindowManager()->GetActiveWindow()->GetSize();

	GLfloat xFloat = (2.0f * (point.GetX() + GetOrigin().GetX())) / szWindowSize.GetX() - 1;
	GLfloat yFloat = (2.0f * (point.GetY() + GetOrigin().GetY())) / szWindowSize.GetY() - 1;
	GLfloat zFloat = 1.0f * point.GetZ();

	return COpenGLPoint(xFloat, yFloat, zFloat);
}
