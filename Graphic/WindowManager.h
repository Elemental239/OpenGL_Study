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
class IDialog;
struct GLFWwindow;
struct WindowConstructionParams;

class IWindowManager : public CObject
{
public:
	virtual void Init(WindowConstructionParams& firstWindowParams) = 0;

	virtual void StartMainLoop() = 0;
	virtual void OnSystemEvent(const EventData& event) = 0;

	virtual void AddWindow(CSharedPtr<IWindow> spWindow) = 0;
	virtual void RemoveWindow(CSharedPtr<IWindow> spWindow) = 0;

	virtual void AddDialog(IWindow* pWindow, CSharedPtr<IDialog> spDialog) = 0;
	virtual void AddDialogToActiveWindow(CSharedPtr<IDialog> spDialog) { AddDialog(GetActiveWindow(), spDialog); }

	virtual CSharedPtr<IWindow> GetActiveWindow() = 0;
};

class IWindowManagerProvider : public CObject
{
public:
	virtual CSharedPtr<IWindowManager> GetWindowManager() = 0;
};

class CWindowManagerProvider : public IWindowManagerProvider
{
	SINGLETON(CWindowManagerProvider, CWindowManagerProvider());

	virtual CSharedPtr<IWindowManager> GetWindowManager() override;

private:
	CSharedPtr<IWindowManager> m_spWindowManager;
};

class CWindowManager : public IWindowManager
{
public:
	CWindowManager();
	~CWindowManager();

	virtual void Init(WindowConstructionParams& firstWindowParams) override;
	virtual void StartMainLoop() override;

	virtual void OnSystemEvent(const EventData& event) override;

	virtual void AddWindow(CSharedPtr<IWindow> spWindow) override;
	virtual void RemoveWindow(CSharedPtr<IWindow> spWindow) override;

	virtual void AddDialog(IWindow* pWindow, CSharedPtr<IDialog> spDialog) override;

	void SetActiveWindow(CSharedPtr<IWindow> spWindow) { m_activeWindow = spWindow; }
	virtual CSharedPtr<IWindow> GetActiveWindow() override { return m_activeWindow; }

private:
	std::vector<CSharedPtr<IWindow> > m_windows;
	CSharedPtr<IWindow> m_activeWindow;
	bool m_bInited;

	void InitOpenGLWindowLibrary(); //GLFW
	void CreateFirstWindow(WindowConstructionParams& firstWindowParams);
	void InitOpenGLDriverLibrary(); //GLEW

	void ProcessWindowEvent(CSharedPtr<IWindow> spWindow, const EventData& event);
	bool IsEventForAllDialogs(const EventData& event) const;
	bool IsEventForAllWindows(const EventData& event) const;

	void SendEventForAllWindows(const EventData& event);
	void SendEventForTargetWindow(const EventData& event);
};

#define WINDOW_MANAGER CWindowManagerProvider::Instance().GetWindowManager()

#endif //__Graphic_WindowManager_H__
