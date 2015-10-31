#ifndef __HelloWorldTestWindow_H__
#define __HelloWorldTestWindow_H__

#include "Object.h"
#include "StringImpl.h"
#include "OpenGL.h"
#include "Shader.h"

struct GLFWwindow;

class CHelloWorldTestWindow : public CObject
{
public:
	CHelloWorldTestWindow();
	~CHelloWorldTestWindow();

	void Draw();

private:
	GLFWwindow* m_window;
	CShaderProgram m_shaderProgram;
	CShaderProgram m_shaderProgramWithTexture;
	GLuint m_VAO;
	GLuint m_MedmVAO;
	GLuint m_MedmVAOConstantBlue;
	GLuint m_MedmVAO18Vertex;
	GLuint m_texture;

	void InitOpenGL();
	void CreateNewWindow(GLFWwindow*& targetWindow, int nWidth, int nHeight, CString strTitle);
	void CreateShaderProgram();
	void CreateGLObjects();	

	void StartRenderCycle();
	void Render();

	void CreateMedmLogoObject(float fHorizontalShift, float fVerticalShift, GLuint& VAO);
	void CreateMedmLogo18Vertex(float fHorizontalShift, float fVerticalShift, GLuint& VAO);

	float IntColorPart2Float(int nColor);
};

#endif //__HelloWorldTestWindow_H__
