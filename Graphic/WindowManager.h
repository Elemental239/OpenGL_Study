#ifndef __Graphic_WindowManager_H__
#define __Graphic_WindowManager_H__

//* Now WindowManager can't create more than 1 window at once
//* To enable multiple windows, one has to manually build GLEW
//* with GLEW_MX flag. 
//* For more information, google GLEW MX
//*

#include "Object.h"
#include <vector>
#include "Singleton.h"
#include "SharedPtr.h"
#include "WindowEvents.h"

class IWindow;
struct GLFWwindow;
struct WindowConstructionParams;

class CWindowManager : public CObject
{
public:
	SINGLETON(CWindowManager, CWindowManager())

	void Init(WindowConstructionParams& firstWindowParams);
	void StartMainLoop();

	void OnSystemEvent(const EventData& event);

	void AddWindow(CSharedPtr<IWindow> spWindow);
	void RemoveWindow(CSharedPtr<IWindow> spWindow);

	void SetActiveWindow(CSharedPtr<IWindow> spWindow) { m_activeWindow = spWindow; }
	CSharedPtr<IWindow> GetActiveWindow() { return m_activeWindow; }

private:
	std::vector<CSharedPtr<IWindow> > m_windows;
	CSharedPtr<IWindow> m_activeWindow;
	bool m_bInited;

	void InitOpenGLWindowLibrary(); //GLFW
	void CreateFirstWindow(WindowConstructionParams& firstWindowParams);
	void InitOpenGLDriverLibrary(); //GLEW
};

#endif //__Graphic_WindowManager_H__
