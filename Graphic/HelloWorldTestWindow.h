#ifndef __HelloWorldTestWindow_H__
#define __HelloWorldTestWindow_H__

#include "Object.h"

class CHelloWorldTestWindow : public CObject
{
public:
	CHelloWorldTestWindow();
	~CHelloWorldTestWindow();

	void Draw();

private:
	void InitOpenGL();
	void CreateWindow(int nWidth, int nHeight);
	void PrepareGLObjects();
	void CreateVertexShader();
	void CreateFragmentShader();
	void CreateShaderProgram();
	

	static void Render();
	void StartRenderCycle();
	


};

#endif //__HelloWorldTestWindow_H__
