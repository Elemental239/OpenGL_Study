#include "Circle.h"
#include <GraphicGeneral.h>
#include "Logger.h"

#define _USE_MATH_DEFINES
#include <math.h>

static const int DATA_ROW_LENGTH = 6; // 3 for pos and 3 for color

///////////////////////////////////////////////////////////////////////////////
///CCircle
CCircle::CCircle(int nRadius, CColor cColor) : 
	COpenGLGraphicObject(),
	m_nRadius(nRadius),
	m_cColor(cColor)
{
	MARKER("CCircle::CCircle()");

	m_rectSize = CSize(2 * m_nRadius, 2 * m_nRadius);
}


void CCircle::InitPoints()
{
	if (!m_bInited)
	{
		CPoint pointCenter = CPoint(m_nRadius, m_nRadius) + GetOrigin();
		for (int i = 0; i < CIRCLE_APPROX_LINES_NUMBER; i++)
		{
			CPoint point = pointCenter + CPoint(static_cast<int>(sin(i * 2 * M_PI / CIRCLE_APPROX_LINES_NUMBER) * m_nRadius), 
										        static_cast<int>(cos(i * 2 * M_PI / CIRCLE_APPROX_LINES_NUMBER) * m_nRadius));

			m_CirclePoints.push_back(point);
		}
	}
}

void CCircle::DrawSelf()
{
	InitPoints();

	__super::DrawSelf();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_LINE_LOOP, 0, m_CirclePoints.size());	// Use glDrawArrays cause we have no EBO here
	glBindVertexArray(0);
}

void CCircle::CreateShaderProgram()
{
	MARKER("CCircle::CreateShaderProgram()");

	CStringA vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 colour;\n"
		"\n"
		"out vec3 vertexColour;"
		"\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"vertexColour = colour;\n"
		"}";

	CStringA fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 vertexColour;"
		"out vec4 color;\n"
		"void main()\n"
		"{"
			"color = vec4(vertexColour, 1.0f);\n"
		"}";

	m_shaderProgram = new CShaderProgram(CVertexShader(vertexShaderSource), CFragmentShader(fragmentShaderSource));
}

void CCircle::BindVBO()
{
	GLfloat* vertices = new GLfloat[m_CirclePoints.size() * DATA_ROW_LENGTH];

	for (decltype(m_CirclePoints.size()) i = 0; i < m_CirclePoints.size(); i++)
	{
		// Positions
		COpenGLPoint glPoint = TranslatePixelPoint(m_CirclePoints[i]);
		vertices[i * DATA_ROW_LENGTH + 0] = glPoint.GetX();
		vertices[i * DATA_ROW_LENGTH + 1] = glPoint.GetY();
		vertices[i * DATA_ROW_LENGTH + 2] = glPoint.GetZ();

		// Color
		vertices[i * DATA_ROW_LENGTH + 3] = m_cColor.GetPart(COLOR_PART_RED);
		vertices[i * DATA_ROW_LENGTH + 4] = m_cColor.GetPart(COLOR_PART_GREEN);
		vertices[i * DATA_ROW_LENGTH + 5] = m_cColor.GetPart(COLOR_PART_BLUE);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_CirclePoints.size() * DATA_ROW_LENGTH * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	delete[] vertices;
}

void CCircle::BindEBO()
{
	//GLuint* indices = new GLuint[m_CirclePoints.size() * 2];

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CCircle::SetupVAOAttributes()
{
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

///////////////////////////////////////////////////////////////////////////////
///CFilledCircle
void CFilledCircle::DrawSelf()
{
	InitPoints();

	COpenGLGraphicObject::DrawSelf();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_CirclePoints.size());	// Use glDrawArrays cause we have no EBO here
	glBindVertexArray(0);
}
