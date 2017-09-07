#include "CommonGame.h"
#include "Logger.h"
#include "Globals.h"
#include "ApplicationInfo.h"
#include "Dialogs/MainMenuDialog.h"
#include "Window.h"

CCommonGame::CCommonGame()
{
	MARKER("CCommonGame::CCommonGame()");
}

void CCommonGame::Init()
{
	MARKER("CCommonGame::Init()");
	GLOBALS.Init();
	CreateMainWindow();
}

void CCommonGame::Start()
{
	MARKER("CCommonGame::Start()");
	WINDOW_MANAGER->StartMainLoop();
}

void CCommonGame::CreateMainWindow()
{
	WindowConstructionParams firstWindowParams;
	firstWindowParams.m_nWindowWidth = 1200;
	firstWindowParams.m_nWindowHeight = 800;
	firstWindowParams.m_strWindowLabel = MAIN_WINDOW_LABEL;
	firstWindowParams.m_colorBase = CColor(0xFF, 0xFF, 0xFF);
	firstWindowParams.m_bIsResizable = true;
	firstWindowParams.m_bUseAntialiasing = false;

	WINDOW_MANAGER->Init(firstWindowParams);

	CSharedPtr<IDialog> spDialog = new CMainMenuDialog;
	WINDOW_MANAGER->AddDialogToActiveWindow(spDialog);
}
