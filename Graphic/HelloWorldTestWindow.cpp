// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/

#include "HelloWorldTestWindow.h"
#include "Logger.h"
#include <glut.h>
#include <functional>

GLenum g_OpenGLError;

#define OPENGL_CALL(expression) { expression; \
    if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
      LOG_ERROR("OpenGL expression \"" #expression "\" error 0x%X", (unsigned)g_OpenGLError); }

#define OPENGL_CHECK_FOR_ERRORS if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) LOGE("OpenGL error 0x%X\n", (unsigned)g_OpenGLError);

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
