#include "MainMenuDialog.h"
#include "Logger.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");

	//AddChild();
}

CMainMenuDialog::~CMainMenuDialog()
{
	MARKER("CMainMenuDialog::~CMainMenuDialog()");
}

bool CMainMenuDialog::OnSystemEvent(const EventData& event)
{
	MARKER("CMainMenuDialog::OnSystemEvent()");

	if (event.m_nEventType == EVT_BUTTON)
	{
		if (event.m_nKeyboardKey == GLFW_KEY_ESCAPE && event.m_nAction == GLFW_PRESS)
		{
			Close();
		}

		return true;
	}

	return __super::OnSystemEvent(event);
}

void CMainMenuDialog::DrawSelf()
{

}