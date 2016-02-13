#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");

	TGraphicObjectRef spRectangle = new CRectanglePrimitive(CSize(400, 400), CRandomColor(), CRandomColor(), CRandomColor(), CRandomColor());
	spRectangle->SetOrigin(CPoint(10, 10));
	
	TGraphicObjectRef spTriangle = new CTrianglePrimitive(
		CPointWithColor(100, 100, CRandomColor()),
		CPointWithColor(300, 100, CRandomColor()),
		CPointWithColor(200, 200, CRandomColor())
	);
	spTriangle->SetOrigin(CPoint(30, 30));

	TGraphicObjectRef spFilledCircle = new CFilledCircle(50, CRandomColor());
	spFilledCircle->SetOrigin(CPoint(70, 50));

	AddChild(spRectangle);
	AddChild(spTriangle);
	AddChild(spFilledCircle);
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