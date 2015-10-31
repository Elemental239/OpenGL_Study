#ifndef __Graphic_Window_H__
#define __Graphic_Window_H__

#include "Object.h"
#include <stack>
#include "WindowManager.h"

struct GLFWwindow;

class CWindow : public CObject
{
public:
	CWindow();
	~CWindow();

	bool IsMineOpenGLWindow(GLFWwindow* window) { return window == m_window; }
	bool OnSystemEvent(const EventData& event);

private:
	GLFWwindow* m_window;
	//std::stack<> m_dialogs; 
};

#endif //__Graphic_Window_H__