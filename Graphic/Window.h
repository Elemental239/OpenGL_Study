#ifndef __Graphic_Window_H__
#define __Graphic_Window_H__

#include "Object.h"
#include <stack>
#include "WindowManager.h"
#include "StringImpl.h"

struct GLFWwindow;

struct WindowConstructionParams
{
	CString strWindowLabel;
	int WindowWidth;	// Pixels
	int WindowHeight;	// Pixels

	CString ToString() const { return "Window params: Label = " + strWindowLabel + ", size = " + ToStr(WindowWidth) + "x" + ToStr(WindowHeight); }
};

class IWindow : public CObject
{
public:
	virtual bool OnSystemEvent(const EventData& event) = 0;

	bool IsMineOpenGLWindow(GLFWwindow* window) { return window == m_window; }
	void SetOpenGLDrawingContext();

protected:
	GLFWwindow* m_window;
};

class CWindow : public IWindow
{
public:
	CWindow(const WindowConstructionParams& params);
	~CWindow();

	virtual bool OnSystemEvent(const EventData& event) override;

private:
	//std::stack<> m_dialogs; 
};

#endif //__Graphic_Window_H__