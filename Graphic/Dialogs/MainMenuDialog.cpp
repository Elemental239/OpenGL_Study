#include "MainMenuDialog.h"
#include "Logger.h"
#include "GraphicObjects/Triangle.h"
#include "GraphicObjects/Rectangle.h"
#include "GraphicObjects/Line.h"
#include "GraphicObjects/Circle.h"

CMainMenuDialog::CMainMenuDialog()
{
	MARKER("CMainMenuDialog::CMainMenuDialog()");

	//TGraphicObjectRef spTopRectangle = new CRectanglePrimitive( 
	//	CPointWithColor(  0,   0, 1, CRandomColor()),
	//	CPointWithColor(  0, 600, 1, CRandomColor()),
	//	CPointWithColor(800, 600, 1, CRandomColor()),
	//	CPointWithColor(800,   0, 1, CRandomColor())
	//);
	//TGraphicObjectRef spCurrentRectangle = spTopRectangle;
	//AddChild(spTopRectangle);

	//for (int i = 1; i < 4; i++)
	//{
	//	TGraphicObjectRef spRectangle = new CRectangle( 
	//		CPoint(50, 50, 1),
	//		CPoint(spCurrentRectangle.static_cast_to<CRectanglePrimitive>()->GetWidth() - 50,
	//		       spCurrentRectangle.static_cast_to<CRectanglePrimitive>()->GetHeight() - 50, 1),
	//		CRandomColor(),
	//		spCurrentRectangle->GetOrigin()
	//	);

	//	spCurrentRectangle->AddChild(spRectangle);
	//	spCurrentRectangle = spRectangle;
	//};

	//AddChild(new CLine(CPointWithColor( 700, 100, 1, CRandomColor()), CPointWithColor( 100, 500, 1, CRandomColor())));
	//AddChild(new CLine(CPointWithColor( 100, 100, 1, CRandomColor()), CPointWithColor( 700, 500, 1, CRandomColor())));

	for (int i = 0; i < 7; i++)
	{
		AddChild(new CCircle(CPoint( 100 + i * 50, 100 + i * 50, 1), 50 - 5 * i, CRandomColor()));
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