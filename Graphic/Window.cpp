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
CWindow::CWindow(const WindowConstructionParams& params) : IWindow(params), m_bClosed(false)
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

void CWindow::Close()
{
	MARKER("CWindow::Close()");

	m_bClosed = true;
	//glfwSetWindowShouldClose(m_window, true);
}

void CWindow::Draw()
{
	glClearColor(m_params.m_colorBase.GetPart(COLOR_PART_RED), 
				 m_params.m_colorBase.GetPart(COLOR_PART_GREEN), 
				 m_params.m_colorBase.GetPart(COLOR_PART_BLUE), 
				 m_params.m_colorBase.GetPart(COLOR_PART_ALPHA));
	glClear(GL_COLOR_BUFFER_BIT);

	if (m_dialogs.size() > 0)
		m_dialogs.top()->Draw();

	glfwSwapBuffers(m_window);
}

void AddDialog(CSharedPtr<IDialog> spDialog);
void RemoveDialog(CSharedPtr<IDialog> spDialog);
