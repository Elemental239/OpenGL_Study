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
	GLuint m_VAO;
	GLuint m_MedmVAO;

	void InitOpenGL();
	void CreateNewWindow(int nWidth, int nHeight, CString strTitle);
	void CreateShaderProgram();
	void CreateGLObjects();	

	void StartRenderCycle();
	void Render();


	void CreateMedmLogoObject();
};

#endif //__HelloWorldTestWindow_H__
