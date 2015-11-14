#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");

	TGraphicObjectRef spTopTriangle = new CTrianglePrimitive( 
		CPointWithColor(200,   0, 1, CColor("#227722")),
		CPointWithColor(800, 600, 1, CColor("#772222")),
		CPointWithColor(800,   0, 1, CColor("#222277"))
	);
	TGraphicObjectRef spCurrentTriangle = spTopTriangle;
	AddChild(spTopTriangle);

	for (int i = 1; i < 4; i++)
	{
		TGraphicObjectRef spTriangle = new CTrianglePrimitive( 
			CPointWithColor(200 + i * 100,   30 * i, 1, CRandomColor()),
			CPointWithColor(800 - 30 * i, 600 - i * 100, 1, CRandomColor()),
			CPointWithColor(800 - 30 * i,             30 * i, 1, CRandomColor())
		); 

		spCurrentTriangle->AddChild(spTriangle);
		spCurrentTriangle = spTriangle;
	}
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