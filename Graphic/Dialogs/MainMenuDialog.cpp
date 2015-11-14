#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");

	AddChild(new CTrianglePrimitive( CPointWithColor(100, 100, 1, CColor("#227722")),
									 CPointWithColor(200, 200, 1, CColor("#227722")),
									 CPointWithColor(300, 100, 1, CColor("#227722"))
								    )
	);
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
	MARKER("CMainMenuDialog::DrawSelf()");
}