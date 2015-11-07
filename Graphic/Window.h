#ifndef __Graphic_Window_H__
#define __Graphic_Window_H__

#include "Object.h"
#include "Stack.h"
#include "WindowManager.h"
#include "StringImpl.h"
#include "Dialog.h"
#include "GraphicGeneral.h"

struct GLFWwindow;

struct WindowConstructionParams
{
	CString m_strWindowLabel;
	int m_nWindowWidth;		// Pixels
	int m_nWindowHeight;	// Pixels
	CColor m_colorBase;

	CString ToString() const { return "Window params: Label = " + m_strWindowLabel + ", size = " + ToStr(m_nWindowWidth) 
		+ "x" + ToStr(m_nWindowHeight) + "; color = " + m_colorBase.ToString(); }
};

class IWindow : public CObject
{
public:
	IWindow(const WindowConstructionParams& params);
	~IWindow() {}
	
	virtual bool OnSystemEvent(const EventData& event) = 0;

	void SetOpenGLDrawingContext();
	int GetWidth() { return m_params.m_nWindowWidth; }
	int GetHeight() { return m_params.m_nWindowHeight; }

	virtual bool IsClosed() const = 0;
	virtual void Close() = 0;
	virtual void Draw() = 0;

	friend class CWindowManager;

protected:
	GLFWwindow* m_window;
	WindowConstructionParams m_params;
	
};
typedef CSharedPtr<IWindow> TWindowRef;

class CWindow : public IWindow
{
public:
	CWindow(const WindowConstructionParams& params);
	~CWindow();

	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool IsClosed() const override { return m_bClosed; }
	virtual void Close() override;
	virtual void Draw() override;

	void AddDialog(TDialogRef spDialog);
	void RemoveDialog(TDialogRef spDialog);

private:
	bool m_bClosed;
	CStack<TDialogRef> m_dialogs;

	int GetHeight() { return m_params.m_nWindowHeight; }
	int GetWidth() { return m_params.m_nWindowWidth; }
};

#endif //__Graphic_Window_H__