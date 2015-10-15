// Possible OpenGL tutorials: http://www.learnopengl.com/#!Getting-started/Creating-a-window  - now it is the main course
//							  https://open.gl/
// OpenGL main site links:    https://www.opengl.org/sdk/docs/tutorials/

#include "HelloWorldTestWindow.h"
#include "Logger.h"
#include <functional>

#define GLEW_STATIC
#include "glew-1.13.0/Source/GL/glew.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

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

	//Init GLFW
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create window
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		LOGE("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOGE("Failed to initialize GLEW");
		return;
	}

	//Set ViewPort
	glViewport(0, 0, 800, 600);  

	//Start event loop
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// End of all
	glfwTerminate();
}
