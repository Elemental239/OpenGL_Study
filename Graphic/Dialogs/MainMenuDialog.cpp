#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");
}

CMainMenuDialog::~CMainMenuDialog()
{
	MARKER("CMainMenuDialog::~CMainMenuDialog()");
}

void CMainMenuDialog::CreateChildren()
{
	MARKER("CMainMenuDialog::CreateChildren()");

	TGraphicObjectRef spRectangle = new CRectanglePrimitive(CSize(200, 200), CRandomColor(), CRandomColor(), CRandomColor(), CRandomColor());
	spRectangle->SetMargins(20, 40, 20, 40);
	spRectangle->SetAlignOption(EAlignOption::CENTER_Y);
	spRectangle->SetSizeOption(ESizeOption::FILL_X);

	AddChild(spRectangle);
}

bool CMainMenuDialog::OnSystemEvent(const EventData& event)
{
	MARKER("CMainMenuDialog::OnSystemEvent()");

	if (event.m_nEventType == EVT_CURSOR_POSITION)
	{
		LOG("cursor position = %s", event.m_cursorPosition.ToString());
	}

	return __super::OnSystemEvent(event);
}

void CMainMenuDialog::DrawSelf()
{
	//MARKER("CMainMenuDialog::DrawSelf()");
}
