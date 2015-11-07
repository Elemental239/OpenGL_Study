#include "MainWindow.h"
#include "Logger.h"
#include "Dialogs/MainMenuDialog.h"

CMainWindow::CMainWindow(const WindowConstructionParams& params) : CWindow(params)
{
	MARKER("CMainWindow::CMainWindow()");

	CSharedPtr<IDialog> spDialog = new CMainMenuDialog; 
	AddDialog(spDialog);
}

CMainWindow::~CMainWindow()
{
	MARKER("CMainWindow::~CMainWindow()");
}

//bool CMainWindow::OnSystemEvent(const EventData& event)
//{
//	MARKER("CMainWindow::OnSystemEvent()");
//
//
//
//	return __super::OnSystemEvent(event);
//}
