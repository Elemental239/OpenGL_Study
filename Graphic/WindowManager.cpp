#include "WindowManager.h"
#include "Logger.h"
#include "Window.h"
#include "OpenGL.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

void opengl_GLFW_error_callback(int error, const char* description)
{
    //fputs(description, stderr);
	LOGE("OpenGL error %d with description %s", error, description);
}

CWindowManager::CWindowManager() : m_bInited(false)
{
	MARKER("CWindowManager::CWindowManager()");
}

CWindowManager::~CWindowManager()
{
	MARKER("CWindowManager::~CWindowManager()");
}

void CWindowManager::Init()
{
	if (m_bInited)
		return;

	MARKER("CWindowManager::Init()");

	InitOpenGLWindowLibrary();
	CreateFirstWindow();
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

void CWindowManager::CreateFirstWindow()
{
	MARKER("CWindowManager::CreateFirstWindow()");
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
