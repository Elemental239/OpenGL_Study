#ifndef __SHADER_H__
#define __SHADER_H__

#include "Object.h"
#include "OpenGL.h"
#include "StringImpl.h"
#include "SharedPtr.h"

class CShader : public CObject
{
public:
	CShader(CStringA source);
	
	void Compile();

	GLuint GetShader() { return m_shader; }
	void DeleteShader();
	//GLuint SetShader(GLuint nID) { m_shader = nID; }

	bool IsValid() { return m_shader != 0; }

protected:
	GLuint m_shader;
	CStringA m_strSource;
	int m_nShaderType; 

private:
	void CompileShader();
	void CheckErrors();

	CStringA ShaderType2String(int nShaderType);
};

class CVertexShader : public CShader
{
public:
	CVertexShader(CStringA source) : CShader(source) { m_nShaderType = GL_VERTEX_SHADER; Compile(); }
};

class CFragmentShader : public CShader
{
public:
	CFragmentShader(CStringA source) : CShader(source) { m_nShaderType = GL_FRAGMENT_SHADER; Compile(); }
};

class CShaderProgram : public CObject
{
public:
	CShaderProgram() : m_program(0) { }
	CShaderProgram(CVertexShader VertexShader, CFragmentShader FragmentShader);

	void Use() { glUseProgram(m_program); }
	bool SetUniform(CStringA name, int value);
	bool SetUniform(CStringA name, float value);

private:
	GLuint m_program;
};
typedef CSharedPtr<CShaderProgram> TShaderProgramRef;

#endif __SHADER_H__