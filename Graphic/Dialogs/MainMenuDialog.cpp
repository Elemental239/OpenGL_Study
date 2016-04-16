#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"
#include "Controls/Button.h"
#include "../Resources/Commands.h"

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

	TGraphicObjectRef spRectangle = new CRectanglePrimitive(CSize(200, 100), CRandomColor(), CRandomColor(), CRandomColor(), CRandomColor());
	spRectangle->SetMargins(20, 20, 20, 20);
	spRectangle->SetAlignOption(EAlignOption::CENTER_Y);
	spRectangle->SetAlignOption(EAlignOption::CENTER_X);

	TControlRef childControl = new CButton(CMD_OPEN_LIFE_GAME_WINDOW, spRectangle);
	AddChild(childControl);
}

bool CMainMenuDialog::OnSystemEvent(const EventData& event)
{
	if (event.m_nEventType == EVT_CURSOR_POSITION)
	{
		LOG("cursor position = %s", event.m_cursorPosition.ToString());
	}

	return __super::OnSystemEvent(event);
}

bool CMainMenuDialog::OnSignal(const SignalData& signal)
{
	MARKER("CMainMenuDialog::OnSignal()");

	if (signal.m_nCommand == CMD_OPEN_LIFE_GAME_WINDOW)
	{
		LOG("HOORAY!");
		return true;
	}

	return __super::OnSignal(signal);
}
