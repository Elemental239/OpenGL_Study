#include "Triangle.h"

CTrianglePrimitive::CTrianglePrimitive(CPoint originPoint, CPointWithColor p1, CPointWithColor p2, CPointWithColor p3) : 
	COpenGLGraphicObject(originPoint)
{
	m_points.push_back(p1);
	m_points.push_back(p2);
	m_points.push_back(p3);
}

CTrianglePrimitive::~CTrianglePrimitive() {}

void CTrianglePrimitive::DrawSelf()
{
	__super::DrawSelf();

	m_shaderProgram->Use();
}

void CTrianglePrimitive::CreateShaderProgram()
{
	CString vertexShaderSource =
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

	CString fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 vertexColour;"
		"out vec4 color;\n"
		"void main()\n"
		"{"
			"color = vec4(vertexColour, 1.0f);\n"
		"}";

	m_shaderProgram = new CShaderProgram(CVertexShader(vertexShaderSource), CFragmentShader(fragmentShaderSource));
}

void CTrianglePrimitive::BindVBO()
{


	GLfloat vertices[] = {
		// Positions          // Colors
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void CTrianglePrimitive::BindEBO()
{

}

void CTrianglePrimitive::SetupVAOAttributes()
{

}
