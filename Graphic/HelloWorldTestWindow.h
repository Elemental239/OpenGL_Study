#ifndef __HelloWorldTestWindow_H__
#define __HelloWorldTestWindow_H__

#include "Object.h"
#include "StringImpl.h"

#define GLEW_STATIC
#include "glew-1.13.0/include/GL/glew.h"
struct GLFWwindow;

class CHelloWorldTestWindow : public CObject
{
public:
	CHelloWorldTestWindow();
	~CHelloWorldTestWindow();

	void Draw();

private:
	GLFWwindow* m_window;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;
	GLuint m_VAO;
	GLuint m_MedmVAO;

	void InitOpenGL();
	void CreateNewWindow(int nWidth, int nHeight, CString strTitle);
	void CreateVertexShader();
	void CreateFragmentShader();
	void CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	void CreateGLObjects();	

	void StartRenderCycle();
	void Render();


	void CreateMedmLogoObject();
};

#endif //__HelloWorldTestWindow_H__
