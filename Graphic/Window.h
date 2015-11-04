#ifndef __Graphic_Window_H__
#define __Graphic_Window_H__

#include "Object.h"
#include <stack>
#include "WindowManager.h"
#include "StringImpl.h"

struct GLFWwindow;

struct WindowConstructionParams
{
	CString m_strWindowLabel;
	int m_nWindowWidth;		// Pixels
	int m_nWindowHeight;	// Pixels

	CString ToString() const { return "Window params: Label = " + m_strWindowLabel + ", size = " + ToStr(m_nWindowWidth) + "x" + ToStr(m_nWindowHeight); }
};

class IWindow : public CObject
{
public:
	IWindow(const WindowConstructionParams& params);
	
	virtual bool OnSystemEvent(const EventData& event) = 0;

	bool IsMineOpenGLWindow(GLFWwindow* window) const { return window == m_window; }
	void SetOpenGLDrawingContext();
	int GetHeight() { return m_params.m_nWindowHeight; }
	int GetWidth() { return m_params.m_nWindowWidth; }

protected:
	GLFWwindow* m_window;
	WindowConstructionParams m_params;
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