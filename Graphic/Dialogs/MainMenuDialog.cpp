#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"
#include "Controls/Button.h"
#include "../Resources/Commands.h"
#include "../Resources/ColorsResources.h"

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

	TGraphicObjectRef spRectanglePressed = new CRectangle(CSize(200, 100), COLOR_GREEN);
	spRectanglePressed->SetMargins(20, 20, 20, 20);
	spRectanglePressed->SetAlignOption(EAlignOption::CENTER_Y);
	spRectanglePressed->SetAlignOption(EAlignOption::CENTER_X);

	TControlRef childControl = new CButton(CMD_OPEN_LIFE_GAME_WINDOW, spRectangle, spRectanglePressed);
	AddChild(childControl);
}

bool CMainMenuDialog::OnSystemEvent(const EventData& event)
{
	return __super::OnSystemEvent(event);
}

bool CMainMenuDialog::OnSignal(const SignalData& signal)
{
	MARKER("CMainMenuDialog::OnSignal()");

	if (signal.m_nCommand == CMD_OPEN_LIFE_GAME_WINDOW)
	{
		LOG("Open ConveyGameDialog");


		return true;
	}

	return __super::OnSignal(signal);
}
