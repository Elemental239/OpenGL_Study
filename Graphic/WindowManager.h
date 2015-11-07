#ifndef __Graphic_WindowManager_H__
#define __Graphic_WindowManager_H__

//* Now WindowManager can't create more than 1 window at once
//* To enable multiple windows, one has to manually build GLEW
//* with GLEW_MX flag. 
//* For more information, google GLEW MX
//*
//*

#include "Object.h"
#include <vector>
#include "Singleton.h"
#include "SharedPtr.h"

class IWindow;
struct GLFWwindow;
struct WindowConstructionParams;

enum EVENT_TYPE
{
	EVT_MOUSE,
	EVT_RESIZE,
	EVT_BUTTON
};

enum MOUSE_EVENT_TYPE
{
	EVT_MOUSE_DOWN,
	EVT_MOUSE_UP
};

struct EventData
{
	EVENT_TYPE m_nEventType;
	GLFWwindow* m_pTargetWindow;

	union {
		struct //EVT_MOUSE
		{
			MOUSE_EVENT_TYPE m_nMouseEventType;
		};

		struct //EVT_BUTTON
		{
			int m_nKeyboardKey;
			int m_nScancode;
			int m_nAction;
			int m_nMode;
		};

		struct //EVT_RESIZE
		{
			int m_nNewHeight;
			int m_nNewWidth;
		};
	};
};

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