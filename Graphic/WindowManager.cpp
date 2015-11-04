#include "WindowManager.h"
#include "Logger.h"
#include "Window.h"
#include "OpenGL.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

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

	CWindowManager::Instance().OnSystemEvent(data);
}

void opengl_GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	EventData data;
	data.m_nEventType = EVT_RESIZE;
	data.m_pTargetWindow = window;
	data.m_nNewWidth = width;
	data.m_nNewHeight = height;
	CWindowManager::Instance().OnSystemEvent(data);
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
	if (m_bInited)
		return;

	MARKER("CWindowManager::Init()");

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
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	glfwSetErrorCallback(opengl_GLFW_error_callback);
}

void CWindowManager::CreateFirstWindow(WindowConstructionParams& firstWindowParams)
{
	MARKER("CWindowManager::CreateFirstWindow()");

	AddWindow(CSharedPtr<IWindow>(new CWindow(firstWindowParams)));
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

void CWindowManager::OnSystemEvent(const EventData& event)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
	{
		if ((*iter)->IsMineOpenGLWindow(event.m_pTargetWindow))
		{
			(*iter)->OnSystemEvent(event);
			break;
		}
	}
}

void CWindowManager::AddWindow(CSharedPtr<IWindow> spWindow)
{
	m_windows.push_back(spWindow);
}

void CWindowManager::RemoveWindow(CSharedPtr<IWindow> spWindow)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
		if (*iter == spWindow)
		{
			m_windows.erase(iter);
			break;
		}
}
