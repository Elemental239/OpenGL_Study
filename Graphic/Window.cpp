#include "Window.h"
#include "Logger.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

void opengl_GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void opengl_GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height);

/////////////////////////////////////////////
///IWindow
IWindow::IWindow(const WindowConstructionParams& params) : m_params(params)
{
}

void IWindow::SetOpenGLDrawingContext()
{
	glfwMakeContextCurrent(m_window);
}

/////////////////////////////////////////////
///CWindow
CWindow::CWindow(const WindowConstructionParams& params) : IWindow(params)
{
	MARKER("CWindow::CWindow()");
	LOG("%s", ToLog(params.ToString()));

	m_window = glfwCreateWindow(params.m_nWindowWidth, params.m_nWindowHeight, params.m_strWindowLabel.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		LOGE("Failed to create GLFW window");
		return;
	}
	SetOpenGLDrawingContext();
	glViewport(0, 0, GetWidth(), GetHeight());

	//Set window-specific callback
	glfwSetKeyCallback(m_window, opengl_GLFW_key_callback);
	glfwSetFramebufferSizeCallback(m_window, opengl_GLFW_framebuffer_size_callback);
}

CWindow::~CWindow()
{
	MARKER("CWindow::~CWindow()");
}

bool CWindow::OnSystemEvent(const EventData& event)
{
	return false;
}
