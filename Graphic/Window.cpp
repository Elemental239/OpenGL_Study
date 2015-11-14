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


void IWindow::AddDialog(TDialogRef spDialog)
{
	m_dialogs.push(spDialog);
}

void IWindow::RemoveDialog(TDialogRef spDialog)
{
	if (m_dialogs.size() > 0)
	{
		for (int i = 0; i < m_dialogs.size(); i++)
		{
			if (m_dialogs[i] == spDialog)
				m_dialogs[i]->Close();
		}
	}
}

/////////////////////////////////////////////
///CWindow
CWindow::CWindow(const WindowConstructionParams& params) : IWindow(params), m_bClosed(false)
{
	MARKER("CWindow::CWindow()");
	LOG("%s", ToLog(params.ToString()));

	glfwWindowHint(GLFW_RESIZABLE, params.m_bIsResizable ? GL_TRUE : GL_FALSE);
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
	for (int i = m_dialogs.size() - 1; i >= 0; i--)
	{
		if (m_dialogs[i]->OnSystemEvent(event))
			return true;
	}

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

	// Remove all closed all dialogs
	while (m_dialogs.size() > 0 && m_dialogs.top()->IsClosed())
	{
		LOG("Delete top dialog cause it was closed");
		m_dialogs.pop();
	}

	if (m_dialogs.size() > 0)
	{
		m_dialogs.top()->Draw();
	}
	else
	{
		LOG("Close window cause of no dialogs in it");
		Close();
	}

	glfwSwapBuffers(m_window);
}
