#include "Window.h"
#include "Logger.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

/////////////////////////////////////////////
///IWindow
void IWindow::SetOpenGLDrawingContext()
{
	glfwMakeContextCurrent(m_window);
}

/////////////////////////////////////////////
///CWindow
CWindow::CWindow(const WindowConstructionParams& params)
{
	MARKER("CWindow::CWindow()");
	LOG("%s", ToLog(params.ToString()));

	m_window = glfwCreateWindow(params.WindowWidth, params.WindowHeight, params.strWindowLabel.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		LOGE("Failed to create GLFW window");
		return;
	}
	SetOpenGLDrawingContext();
}

CWindow::~CWindow()
{
	MARKER("CWindow::~CWindow()");
}

bool CWindow::OnSystemEvent(const EventData& event)
{
	return false;
}
