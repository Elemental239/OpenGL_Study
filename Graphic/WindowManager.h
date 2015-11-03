#ifndef __Graphic_WindowManager_H__
#define __Graphic_WindowManager_H__

#include "Object.h"
#include <vector>
#include "Singleton.h"
#include "SharedPtr.h"

class IWindow;
struct GLFWwindow;

enum EVENT_TYPE
{
	EVT_MOUSE,
	EVT_RESIZE
};

enum MOUSE_EVENT_TYPE
{
	EVT_MOUSE_DOWN,
	EVT_MOUSE_UP
};

struct EventData
{
	EVENT_TYPE m_type;
	GLFWwindow* m_pTargetWindow;

	union {
		MOUSE_EVENT_TYPE m_nMouseEventType;
	};
};

class CWindowManager : public CObject
{
public:
	SINGLETON(CWindowManager, CWindowManager())

	void Init();

	void OnSystemEvent(const EventData& event);

	void AddWindow(CSharedPtr<IWindow> spWindow);
	void RemoveWindow(CSharedPtr<IWindow> spWindow);

private:
	std::vector<CSharedPtr<IWindow> > m_windows;
	bool m_bInited;

	void InitOpenGLWindowLibrary(); //GLFW
	void CreateFirstWindow();
	void InitOpenGLDriverLibrary(); //GLEW
};

#endif //__Graphic_WindowManager_H__