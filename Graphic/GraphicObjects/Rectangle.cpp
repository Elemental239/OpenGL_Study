#include "Rectangle.h"

static const int DATA_ROW_LENGTH = 6; // 3 for pos and 3 for color

////////////////////////////////////////
///CRectanglePrimitive
CRectanglePrimitive::CRectanglePrimitive(CSize size, CColor cColorLeftBottom, CColor cColorLeftTop, CColor cColorRightTop, CColor cColorRightBottom) : 
	COpenGLGraphicObject(),
	m_size(size)
{
	m_colors.push_back(cColorLeftBottom);
	m_colors.push_back(cColorLeftTop);
	m_colors.push_back(cColorRightTop);
	m_colors.push_back(cColorRightBottom);

	m_rectSize = m_size;
}

void CRectanglePrimitive::DrawSelf()
{
	if (!m_bInited)
	{
		m_points.push_back(CPointWithColor(GetOrigin(), m_colors[0]));
		m_points.push_back(CPointWithColor(GetOrigin() + CPoint(0, m_size.GetY()), m_colors[1]));
		m_points.push_back(CPointWithColor(GetOrigin() + CPoint(m_size.GetX(), m_size.GetY()), m_colors[2]));
		m_points.push_back(CPointWithColor(GetOrigin() + CPoint(m_size.GetX(), 0), m_colors[3]));
	}

	__super::DrawSelf();

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_points.size() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CRectanglePrimitive::CreateShaderProgram()
{
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

void CRectanglePrimitive::BindVBO()
{
	GLfloat vertices[4 * DATA_ROW_LENGTH];

	for (decltype(m_points.size()) i = 0; i < m_points.size(); i++)
	{
		// Positions
		COpenGLPoint glPoint = TranslatePixelPoint(m_points[i]);
		vertices[i * DATA_ROW_LENGTH + 0] = glPoint.GetX();
		vertices[i * DATA_ROW_LENGTH + 1] = glPoint.GetY();
		vertices[i * DATA_ROW_LENGTH + 2] = glPoint.GetZ();

		// Color
		vertices[i * DATA_ROW_LENGTH + 3] = m_points[i].GetColor().GetPart(COLOR_PART_RED);
		vertices[i * DATA_ROW_LENGTH + 4] = m_points[i].GetColor().GetPart(COLOR_PART_GREEN);
		vertices[i * DATA_ROW_LENGTH + 5] = m_points[i].GetColor().GetPart(COLOR_PART_BLUE);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void CRectanglePrimitive::BindEBO()
{
	GLuint indices[] = { 0, 1, 2,
						 0, 2, 3};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CRectanglePrimitive::SetupVAOAttributes()
{
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}
