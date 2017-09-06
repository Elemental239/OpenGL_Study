#include "Window.h"
#include "Logger.h"
#include "GraphicObjects/Rectangle.h"
#include "../Resources/ColorsResources.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

void opengl_GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void opengl_GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void opengl_GLFW_mouse_callback(GLFWwindow* window, int nButton, int nEvent, int nAdditionalFlags);
void opengl_GLFW_cursor_position_callback(GLFWwindow* window, double xPos, double yPos);

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
	spDialog->OnLifetimeEvent(DIALOG_LIFETIME_EVENT_BEFORE_SHOW);

	CSize windowSize = CSize(GetWidth(), GetHeight());
	TGraphicObjectRef spDialogGraphicRepresentation = new CRectangle(windowSize, spDialog->GetBackgroundColor());
	spDialogGraphicRepresentation->SetContainerParams(CPoint(), windowSize);
	spDialog->SetVisualPresentation(spDialogGraphicRepresentation);
	spDialog->InitChildren();
	spDialog->SetContainingWindow(this);
	m_dialogs.push(spDialog);

	spDialog->OnLifetimeEvent(DIALOG_LIFETIME_EVENT_AFTER_SHOW);
}

void IWindow::RemoveDialog(TDialogRef spDialog)
{
	spDialog->OnLifetimeEvent(DIALOG_LIFETIME_EVENT_BEFORE_HIDE);

	if (m_dialogs.size() > 0)
	{
		for (int i = 0; i < m_dialogs.size(); i++)
		{
			if (m_dialogs[i] == spDialog)
				m_dialogs[i]->Close();
		}
	}

	spDialog->OnLifetimeEvent(DIALOG_LIFETIME_EVENT_AFTER_HIDE);
}

void IWindow::BroadcastEventToAllDialogs(const EventData& event)
{
	for (int i = 0; i < m_dialogs.size(); i++)
	{
		m_dialogs[i]->OnSystemEvent(event);
	}
}

/////////////////////////////////////////////
///CWindow
CWindow::CWindow(const WindowConstructionParams& params) : IWindow(params), m_bClosed(false)
{
	MARKER("CWindow::CWindow()");
	LOG("%s", params.ToString8());

	//if (params.m_bUseAntialiasing)
	//	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, params.m_bIsResizable ? GL_TRUE : GL_FALSE);
	m_window = glfwCreateWindow(params.m_nWindowWidth, params.m_nWindowHeight, params.m_strWindowLabel.ToString().c_str(), nullptr, nullptr);

	if (m_window == nullptr)
	{
		LOGE("Failed to create GLFW window");
		return;
	}

	SetOpenGLDrawingContext();
	glViewport(0, 0, GetWidth(), GetHeight());

	//if (params.m_bUseAntialiasing)
	//{
	//	glEnable(GL_MULTISAMPLE);

	//	glEnable(GL_LINE_SMOOTH);
	//	glEnable(GL_BLEND);
	//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); //or GL_FASTEST, or GL_DONT_CARE
	//	//glEnable(GL_POINT_SMOOTH);
	//	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//	//glEnable(GL_POLYGON_SMOOTH);
	//	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // - for lines
	//	//glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE); // - for polygons
	//}

	//Set window-specific callback
	glfwSetKeyCallback(m_window, opengl_GLFW_key_callback);
	glfwSetFramebufferSizeCallback(m_window, opengl_GLFW_framebuffer_size_callback);
	glfwSetMouseButtonCallback(m_window, opengl_GLFW_mouse_callback);
	glfwSetCursorPosCallback(m_window, opengl_GLFW_cursor_position_callback);
}

CWindow::~CWindow()
{
	MARKER("CWindow::~CWindow()");
}

bool CWindow::OnSystemEvent(const EventData& event)
{
	if (m_dialogs[m_dialogs.size() - 1]->OnSystemEvent(event))
			return true;

	return false;
}

void CWindow::Close()
{
	MARKER("CWindow::Close()");

	m_bClosed = true;
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
