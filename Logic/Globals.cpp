#include "Globals.h"
#include "Logger.h"
#include <memory>
#include "UtilityMacros.h"
#include "HelloWorldTestWindow.h"
#include "WindowManager.h"
#include "Window.h"
#include "ApplicationInfo.h"

#include "File.h"

#define NO_GUI
#define EXPERIMENTAL_GUI

CGlobals::CGlobals()
{
	MARKER("CGlobals::CGlobals()");
}

CGlobals::~CGlobals()
{
	MARKER("CGlobals::~CGlobals()");
}

void CGlobals::Init()
{
	MARKER("CGlobals::Init()");

#if !defined(NO_GUI)
	m_spHelloWorldTestWindow = CSharedPtr<CHelloWorldTestWindow>(new CHelloWorldTestWindow);
	m_spHelloWorldTestWindow->Draw();
#endif

#if defined(EXPERIMENTAL_GUI)
	WindowConstructionParams firstWindowParams;
	firstWindowParams.m_nWindowWidth = 800;
	firstWindowParams.m_nWindowHeight = 600;
	firstWindowParams.m_strWindowLabel = MAIN_WINDOW_LABEL;

	CWindowManager::Instance().Init(firstWindowParams);

#endif

	//CFile file(CString("input.txt"), EFileMode::FILE_MODE_OPEN);
	//bool bExist = file.IsExist();
}
