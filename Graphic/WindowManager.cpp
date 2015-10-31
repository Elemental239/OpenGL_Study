#include "WindowManager.h"
#include "Logger.h"
#include "Window.h"

CWindowManager::CWindowManager()
{
	MARKER("CWindowManager::CWindowManager()");
}

CWindowManager::~CWindowManager()
{
	MARKER("CWindowManager::~CWindowManager()");
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

void CWindowManager::AddWindow(CSharedPtr<CWindow> spWindow)
{
	m_windows.push_back(spWindow);
}

void CWindowManager::RemoveWindow(CSharedPtr<CWindow> spWindow)
{
	for (auto iter = m_windows.begin(); iter != m_windows.end(); iter++)
		if (*iter == spWindow)
		{
			m_windows.erase(iter);
			break;
		}
}
