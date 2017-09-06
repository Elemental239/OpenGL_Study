#include "WindowManager.h"
#include "Logger.h"
#include "OpenGL.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"
#include "MainWindow.h"
#include "Window.h"

///////////////////////////////////////////////////
///Various OpenGL global callbacks
void opengl_GLFW_error_callback(int error, const char* description)
{
    //fputs(description, stderr);
	LOGE("OpenGL error %d with description %s", error, description);
}

void opengl_GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	EventData data;
	data.m_nEventType = EVT_BUTTON;
	data.m_pTargetWindow = window;
	data.m_nKeyboardKey = key;
	data.m_nAction = action;
	data.m_nScancode = scancode;
	data.m_nMode = mode;

	CWindowManagerProvider::Instance().GetWindowManager()->OnSystemEvent(data);
}

void opengl_GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	EventData data;
	data.m_nEventType = EVT_RESIZE;
	data.m_pTargetWindow = window;
	data.m_nNewWidth = width;
	data.m_nNewHeight = height;

	CWindowManagerProvider::Instance().GetWindowManager()->OnSystemEvent(data);
}

void opengl_GLFW_mouse_callback(GLFWwindow* window, int nButton, int nEvent, int nAdditionalFlags)
{
	EventData data;
	data.m_nEventType = EVT_MOUSE;
	data.m_pTargetWindow = window;
	data.m_nMouseEventType = nEvent == GLFW_PRESS ? MOUSE_EVENT_TYPE::PRESS : MOUSE_EVENT_TYPE::RELEASE;
	data.m_nMouseEventModeFlags = nAdditionalFlags;
	data.m_nMouseEventButton = static_cast<MOUSE_EVENT_BUTTON>(nButton); //El239: enum is the same as GLFW

	CWindowManagerProvider::Instance().GetWindowManager()->OnSystemEvent(data);
}

void opengl_GLFW_cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	EventData data;
	data.m_nEventType = EVT_CURSOR_POSITION;
	data.m_pTargetWindow = window;
	data.m_cursorPosition = CGenericPoint<double>(xPos, yPos);

	CWindowManagerProvider::Instance().GetWindowManager()->OnSystemEvent(data);
}

///////////////////////////////////////////////////
///CWindowManagerProvider
CWindowManagerProvider::CWindowManagerProvider()
{
	MARKER("CWindowManagerProvider::CWindowManagerProvider()");
}

CWindowManagerProvider::~CWindowManagerProvider()
{
	MARKER("CWindowManagerProvider::~CWindowManagerProvider()");
}

CSharedPtr<IWindowManager> CWindowManagerProvider::GetWindowManager() //TODO: mutex this
{
	if (!m_spWindowManager)
		m_spWindowManager = new CWindowManager();

	return m_spWindowManager;
}

///////////////////////////////////////////////////
///CWindowManager
CWindowManager::CWindowManager() : m_bInited(false)
{
	MARKER("CWindowManager::CWindowManager()");
}

CWindowManager::~CWindowManager()
{
	MARKER("CWindowManager::~CWindowManager()");
}

void CWindowManager::Init(WindowConstructionParams& firstWindowParams)
{
	MARKER("CWindowManager::Init()");

	if (m_bInited)
	{
		LOGE("CWindowManager::Init(): double initialization attempt");
		return;
	}

	InitOpenGLWindowLibrary();
	CreateFirstWindow(firstWindowParams);
	InitOpenGLDriverLibrary();

	m_bInited = true;
}

void CWindowManager::InitOpenGLWindowLibrary()
{
	MARKER("CWindowManager::InitOpenGLWindowLibrary()");

	//Init GLFW
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	glfwSetErrorCallback(opengl_GLFW_error_callback);
}

void CWindowManager::CreateFirstWindow(WindowConstructionParams& firstWindowParams)
{
	MARKER("CWindowManager::CreateFirstWindow()");

	TWindowRef spWindow = new CMainWindow(firstWindowParams);
	AddWindow(spWindow);
	SetActiveWindow(spWindow);
}

void CWindowManager::InitOpenGLDriverLibrary()
{
	MARKER("CWindowManager::InitOpenGLDriverLibrary()");

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		LOGE("Failed to initialize GLEW");
	}
}

void CWindowManager::StartMainLoop()
{
	MARKER("CWindowManager::StartRenderLoop()");

	if (!m_bInited)
	{
		LOGE("Attempt to start main loop without initialization");
		return;
	}

	while (m_windows.size() > 0)
	{
		glfwPollEvents();

		for (int i = m_windows.size() - 1; i >= 0; i--)
		{
			if (m_windows[i]->IsClosed())
			{
				m_windows.erase(m_windows.begin() + i);
			}
			else
			{
				m_windows[i]->Draw();
			}
		}
	}

	glfwTerminate();
}

void CWindowManager::OnSystemEvent(const EventData& event)
{
	if (IsEventForAllWindows(event))
	{
		SendEventForAllWindows(event);
	}
	else
	{
		SendEventForTargetWindow(event);
	}
}

void CWindowManager::SendEventForAllWindows(const EventData& event)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
	{
		ProcessWindowEvent(*iter, event);
		break;
	}
}

void CWindowManager::SendEventForTargetWindow(const EventData& event)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
	{
		if ((*iter)->m_window == event.m_pTargetWindow)
		{
			ProcessWindowEvent(*iter, event);
			break;
		}
	}
}

void CWindowManager::ProcessWindowEvent(CSharedPtr<IWindow> spWindow, const EventData& event)
{
	EventData evt = event;

	switch (event.m_nEventType)
	{
		case EVT_CURSOR_POSITION:
			evt.m_cursorPosition.SetY(static_cast<double>(spWindow->GetHeight()) - event.m_cursorPosition.GetY());
			break;

		case EVT_RESIZE:
			LOG("Event params: new width = %d, height = %d", event.m_nNewWidth, event.m_nNewHeight);
			spWindow->m_params.m_nWindowWidth = event.m_nNewWidth;
			spWindow->m_params.m_nWindowHeight = event.m_nNewHeight;
			break;

		default:
			break;
	} //switch (event.m_nEventType)

	if (IsEventForAllDialogs(event))
	{
		spWindow->BroadcastEventToAllDialogs(event);
	}
	else
	{
		spWindow->OnSystemEvent(evt);
	}
}

bool CWindowManager::IsEventForAllDialogs(const EventData& event) const
{
	return event.m_nEventType == EVT_BUTTON && event.m_nKeyboardKey == GLFW_KEY_ESCAPE && event.m_nAction == GLFW_RELEASE;
}

bool CWindowManager::IsEventForAllWindows(const EventData& event) const
{
	return false;
}

void CWindowManager::AddWindow(CSharedPtr<IWindow> spWindow)
{
	if (m_windows.size() > 0)
	{
		LOGE("Attempts to add second window are restricted until multiwindow mode will be enabled");
		return; // See the note at the top of .h file
	}

	m_windows.push_back(spWindow);
}

void CWindowManager::RemoveWindow(CSharedPtr<IWindow> spWindow)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
	{
		if (*iter == spWindow)
		{
			m_windows.erase(iter);
			break;
		}
	}
}

void CWindowManager::AddDialog(IWindow* pWindow, CSharedPtr<IDialog> spDialog)
{
	MARKER("CWindowManager::AddDialog()");

	pWindow->AddDialog(spDialog);
}
