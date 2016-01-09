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

	void ChangeTextureMixValue(float delta) { m_fTexturesMixValue += delta; if (m_fTexturesMixValue < 0.0f) m_fTexturesMixValue = 0.0f; if (m_fTexturesMixValue > 1.0f) m_fTexturesMixValue = 1.0f; }

private:
	GLFWwindow* m_window;
	CShaderProgram m_shaderProgram;
	CShaderProgram m_shaderProgramWithTexture;
	GLuint m_VAO;
	GLuint m_MedmVAO;
	GLuint m_MedmVAOConstantBlue;
	GLuint m_MedmVAO18Vertex;
	GLuint m_texture;
	GLuint m_texture2;
	float m_fTexturesMixValue;

	void InitOpenGL();
	void CreateNewWindow(GLFWwindow*& targetWindow, int nWidth, int nHeight, CStringA strTitle);
	void CreateShaderProgram();
	void CreateGLObjects();	

	void StartRenderCycle();
	void Render();

	void CreateMedmLogoObject(float fHorizontalShift, float fVerticalShift, GLuint& VAO);
	void CreateMedmLogo18Vertex(float fHorizontalShift, float fVerticalShift, GLuint& VAO);

	float IntColorPart2Float(int nColor);
};

#endif //__HelloWorldTestWindow_H__
