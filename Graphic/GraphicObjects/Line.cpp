#include "Line.h"
#include "InlineFunctions.h"

static const int DATA_ROW_LENGTH = 6; // 3 for pos and 3 for color

CLine::CLine(CPointWithColor pointStart, CPointWithColor pointFinish) :
	COpenGLGraphicObject(),
	m_pointStart(pointStart),
	m_pointFinish(pointFinish)
{
	SetSize(CSize(ABS(pointStart.GetX() - pointFinish.GetX()), ABS(pointStart.GetY() - pointFinish.GetY())));
}

CLine::~CLine() {}


void CLine::DrawSelf()
{
	__super::DrawSelf();

	glBindVertexArray(m_VAO);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CLine::CreateShaderProgram()
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

	m_spShaderProgram = new CShaderProgram(CVertexShader(vertexShaderSource), CFragmentShader(fragmentShaderSource));
}

void CLine::BindVBO()
{
	GLfloat vertices[2 * DATA_ROW_LENGTH];

	COpenGLPoint glPoint = TranslatePixelPoint(m_pointStart);
	vertices[0 * DATA_ROW_LENGTH + 0] = glPoint.GetX();
	vertices[0 * DATA_ROW_LENGTH + 1] = glPoint.GetY();
	vertices[0 * DATA_ROW_LENGTH + 2] = glPoint.GetZ();
	vertices[0 * DATA_ROW_LENGTH + 3] = m_pointStart.GetColor().GetPart(COLOR_PART_RED);
	vertices[0 * DATA_ROW_LENGTH + 4] = m_pointStart.GetColor().GetPart(COLOR_PART_GREEN);
	vertices[0 * DATA_ROW_LENGTH + 5] = m_pointStart.GetColor().GetPart(COLOR_PART_BLUE);

	glPoint = TranslatePixelPoint(m_pointFinish);
	vertices[1 * DATA_ROW_LENGTH + 0] = glPoint.GetX();
	vertices[1 * DATA_ROW_LENGTH + 1] = glPoint.GetY();
	vertices[1 * DATA_ROW_LENGTH + 2] = glPoint.GetZ();
	vertices[1 * DATA_ROW_LENGTH + 3] = m_pointFinish.GetColor().GetPart(COLOR_PART_RED);
	vertices[1 * DATA_ROW_LENGTH + 4] = m_pointFinish.GetColor().GetPart(COLOR_PART_GREEN);
	vertices[1 * DATA_ROW_LENGTH + 5] = m_pointFinish.GetColor().GetPart(COLOR_PART_BLUE);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void CLine::BindEBO()
{
	GLuint indices[] = { 0, 1 };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CLine::SetupVAOAttributes()
{
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}
