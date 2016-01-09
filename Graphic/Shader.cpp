#include "Shader.h"
#include "Logger.h"

///////////////////////////////////////////
///CShader
CShader::CShader(CStringA source) : m_strSource(source), m_nShaderType(0)
{
	MARKER("CShader::CShader()");
}

void CShader::DeleteShader()
{
	glDeleteShader(m_shader);
	m_shader = 0;
}

void CShader::Compile()
{ 
	CompileShader();
	CheckErrors();
}

void CShader::CompileShader()
{
	MARKER("CVertexShader::CompileShader()");

	if (m_strSource.empty())
		return;

	m_shader = glCreateShader(m_nShaderType);

	const GLchar* source = static_cast<const GLchar*>(m_strSource.c_str());
	glShaderSource(m_shader, 1, &source, NULL);
	glCompileShader(m_shader);
}

void CShader::CheckErrors()
{
	GLint bSuccess;
	GLchar infoLog[512];
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &bSuccess);

	if(!bSuccess)
	{
		glGetShaderInfoLog(m_shader, sizeof(infoLog), NULL, infoLog);
		LOGE("SHADER type = %s COMPILATION_FAILED:\n %s", ShaderType2String(m_nShaderType), infoLog);
	}
}

CStringA CShader::ShaderType2String(int nShaderType)
{
	if (nShaderType == GL_VERTEX_SHADER)
		return "VERTEX_SHADER";
	else if (nShaderType == GL_FRAGMENT_SHADER)
		return "FRAGMENT_SHADER";
	else
		return "Unknown type " + nShaderType;
}

///////////////////////////////////////////
///CShaderProgram
CShaderProgram::CShaderProgram(CVertexShader VertexShader, CFragmentShader FragmentShader)
{
	if (!VertexShader.IsValid() || !FragmentShader.IsValid())
		return;

	m_program = glCreateProgram();
	glAttachShader(m_program, VertexShader.GetShader());
	glAttachShader(m_program, FragmentShader.GetShader());
	glLinkProgram(m_program);
	
	GLint bSuccess;
	GLchar infoLog[512];
	glGetProgramiv(m_program, GL_LINK_STATUS, &bSuccess);

	if(!bSuccess)
	{
		glGetProgramInfoLog(m_program, sizeof(infoLog), NULL, infoLog);
		LOGE("SHADER PROGRAM COMPILATION FAILED:\n %s", infoLog);
	}

	VertexShader.DeleteShader();
	FragmentShader.DeleteShader();
}

bool CShaderProgram::SetUniform(CStringA name, int value)
{
	//NB! Don't forget to create different SetUniform's for other inputs
	GLint location = glGetUniformLocation(m_program, name.c_str());

	if (location == -1)
	{
		LOGE("CShaderProgram::SetUniform1i() can't find uniform %s", LST(name));
		return false;
	}

	glUniform1i(location, value);
	return true;
}

bool CShaderProgram::SetUniform(CStringA name, float value)
{
	//NB! Don't forget to create different SetUniform's for other inputs
	GLint location = glGetUniformLocation(m_program, name.c_str());

	if (location == -1)
	{
		LOGE("CShaderProgram::SetUniform1f() can't find uniform %s", LST(name));
		return false;
	}

	glUniform1f(location, value);
	return true;
}
