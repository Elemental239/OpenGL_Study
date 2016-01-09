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
	CString8 m_strWindowLabel;
	int m_nWindowWidth;		// Pixels
	int m_nWindowHeight;	// Pixels
	CColor m_colorBase;

	CStringA ToString() const { return ToString8().ToString().c_str(); }
	CString8 ToString8() const { return "Window params: Label = " + m_strWindowLabel + ", size = " + m_nWindowWidth
		+ "x" + m_nWindowHeight + "; color = " + m_colorBase.ToString(); }

	bool m_bIsResizable;
};

class IWindow : public CObject
{
public:
	IWindow(const WindowConstructionParams& params);
	virtual ~IWindow() {}
	
	virtual bool OnSystemEvent(const EventData& event) = 0;

	void SetOpenGLDrawingContext();
	int GetWidth() { return m_params.m_nWindowWidth; }
	int GetHeight() { return m_params.m_nWindowHeight; }

	virtual bool IsClosed() const = 0;
	virtual void Close() = 0;
	virtual void Draw() = 0;

	void AddDialog(TDialogRef spDialog);
	void RemoveDialog(TDialogRef spDialog);

	friend class CWindowManager;

protected:
	GLFWwindow* m_window;
	WindowConstructionParams m_params;
	CStack<TDialogRef> m_dialogs;
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

private:
	bool m_bClosed;

	int GetHeight() { return m_params.m_nWindowHeight; }
	int GetWidth() { return m_params.m_nWindowWidth; }
};

#endif //__Graphic_Window_H__