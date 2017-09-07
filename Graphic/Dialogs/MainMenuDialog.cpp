#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"
#include "Controls/Button.h"
#include "Commands.h"
#include "ColorsResources.h"
#include "ConveyLifeGameDialog.h"
#include "Random.h"

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

	RemoveChildren();

	for (int i = 0; i < 2; i++)
	{
		auto size = CSize(RANDOM.GetIntII(1, 1200), RANDOM.GetIntII(1, 800));
		auto leftMargin = RANDOM.GetIntII(0, 1200 - size.GetX());
		auto bottomMargin = RANDOM.GetIntII(0, 800 - size.GetY());

		TGraphicObjectRef spRectangle = std::make_shared<CRandomColorRectangle>(size);
		spRectangle->SetMargins(leftMargin, 0, 0, bottomMargin);
		spRectangle->SetAlignOption(EAlignOption::BOTTOM);
		spRectangle->SetAlignOption(EAlignOption::LEFT);
		AddChild(spRectangle);
	}

	//TGraphicObjectRef spRectangle = std::make_shared<CRandomColorRectangle>(CSize(400, 400));
	//spRectangle->SetMargins(20, 0, 0, 0);
	//spRectangle->SetAlignOption(EAlignOption::CENTER_Y);
	//spRectangle->SetAlignOption(EAlignOption::LEFT);
	//AddChild(spRectangle);

	//TGraphicObjectRef spRectangle2 = std::make_shared<CRandomColorRectangle>(CSize(250, 300));
	//spRectangle2->SetMargins(100, 0, 0, 10);
	////spRectangle->SetMargins(20, 20, 20, 20);
	////spRectangle->SetAlignOption(EAlignOption::CENTER_Y);
	////spRectangle->SetAlignOption(EAlignOption::CENTER_X);
	//spRectangle->AddChild(spRectangle2);
}

bool CMainMenuDialog::OnSystemEvent(const EventData& event)
{
	if (event.m_nEventType == EVT_BUTTON && event.m_nKeyboardKey == GLFW_KEY_ENTER && event.m_nAction == GLFW_RELEASE)
	{
		CreateChildren();

		return true;
	}

	return __super::OnSystemEvent(event);
}

bool CMainMenuDialog::OnSignal(const SignalData& signal)
{
	MARKER("CMainMenuDialog::OnSignal()");

	if (signal.m_nCommand == CMD_OPEN_LIFE_GAME_WINDOW)
	{
		LOG("Open ConveyGameDialog");
		//CSharedPtr<IDialog> spDialog = CSharedPtr<IDialog>(new CConveyLifeGameDialog());
		//WINDOW_MANAGER->AddDialog(GetContainingWindow(), spDialog);

		return true;
	}

	return CDialog::OnSignal(signal);
}
