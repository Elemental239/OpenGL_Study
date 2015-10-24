#ifndef __SHADER_H__
#define __SHADER_H__

#include "Object.h"
#include "OpenGL.h"
#include "StringImpl.h"

class CShader : public CObject
{
public:
	CShader(CString source);
	
	void Compile();

	GLuint GetShader() { return m_shader; }
	void DeleteShader();
	//GLuint SetShader(GLuint nID) { m_shader = nID; }

	bool IsValid() { return m_shader != 0; }

protected:
	GLuint m_shader;
	CString m_strSource;
	int m_nShaderType; 

private:
	void CompileShader();
	void CheckErrors();

	CString ShaderType2String(int nShaderType);
};

class CVertexShader : public CShader
{
public:
	CVertexShader(CString source) : CShader(source) { m_nShaderType = GL_VERTEX_SHADER; }
};

class CFragmentShader : public CShader
{
public:
	CFragmentShader(CString source) : CShader(source) { m_nShaderType = GL_FRAGMENT_SHADER; }
};

class CShaderProgram : public CObject
{
public:
	CShaderProgram(CVertexShader VertexShader, CFragmentShader FragmentShader);
	void Use() { glUseProgram(m_program); }

private:
	GLuint m_program;
};

#endif __SHADER_H__