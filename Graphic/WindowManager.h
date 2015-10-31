#ifndef __Graphic_WindowManager_H__
#define __Graphic_WindowManager_H__

#include "Object.h"
#include <vector>
#include "Singleton.h"
#include "SharedPtr.h"

class CWindow;
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

	void OnSystemEvent(const EventData& event);

	void AddWindow(CSharedPtr<CWindow> spWindow);
	void RemoveWindow(CSharedPtr<CWindow> spWindow);

private:
	std::vector<CSharedPtr<CWindow> > m_windows; 
};

#endif //__Graphic_WindowManager_H__