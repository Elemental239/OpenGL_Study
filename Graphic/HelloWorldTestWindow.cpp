// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/

#include "HelloWorldTestWindow.h"
#include "Logger.h"
#include <glut.h>
#include <functional>

#define GLEW_STATIC
#include "glfw-3.1.1\include\GLFW\glfw3.h"

CHelloWorldTestWindow::CHelloWorldTestWindow()
{
	MARKER("CHelloWorldTestWindow::CHelloWorldTestWindow()");
}

CHelloWorldTestWindow::~CHelloWorldTestWindow()
{
	MARKER("CHelloWorldTestWindow::~CHelloWorldTestWindow()");
}

void CHelloWorldTestWindow::Render()
{
	LOG("CHelloWorldTestWindow::Render()");
}

void CHelloWorldTestWindow::Draw()
{
	MARKER("CHelloWorldTestWindow::Draw()");
}
