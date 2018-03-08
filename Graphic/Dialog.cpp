#include "Dialog.h"
#include "Logger.h"
#include "GraphicObjects/Rectangle.h"
#include "SharedPtr.h"
#include "Window.h"

CDialog::CDialog(): m_bChildrenInited(false)
{
	MARKER("CDialog::CDialog()");
}

CDialog::~CDialog()
{
	MARKER("CDialog::~CDialog()");
}

void CDialog::InitChildren()
{
	if (!m_bChildrenInited)
	{
		m_bChildrenInited = true;

		CreateBackgroundImage();
		CreateChildren();
	}
}

void CDialog::AddChild(CSharedPtr<CGraphicObject>& obj) // Dialog itself contains only one background rect
{
	if (m_children.size())
	{
		m_children[0]->AddChild(obj.static_cast_to<IControl>());
	}
	else
	{
		CGraphicObject::AddChild(obj);
	}
}

bool CDialog::OnSystemEvent(const EventData& event)
{
	switch (event.m_nEventType)
	{
		case EVT_BUTTON:
		{
			if (ProcessButtonEvent(event))
			{
				ActionOnButtonEvent(event);
				return true;
			}
			break;
		}

		case EVT_MOUSE:
		{
			if (ProcessMouseEvent(event))
			{
				ActionOnMouseEvent(event);
				return true;
			}
			break;
		}

		case EVT_RESIZE:
		{
			SetSize(CSize(event.m_nNewWidth, event.m_nNewHeight));
			break;
		}

		default: 
			break;
	} //switch (event.m_nEventType)

	//for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	//{
	//	if ((*iter)->OnSystemEvent(event))
	//		return true;
	//}

	return CGraphicObject::OnSystemEvent(event);
}

bool CDialog::ProcessButtonEvent(const EventData& event)
{
	if (event.m_nKeyboardKey == GLFW_KEY_ESCAPE && event.m_nAction == GLFW_RELEASE)
	{
		Close();
		return false; // If ESC was pressed, return false to move event deeper => close all dialogs
	}

	return false;
}

bool CDialog::ProcessMouseEvent(const EventData& event)
{
	return false;
}

void CDialog::ActionOnButtonEvent(const EventData& event)
{
	//Empty
}

void CDialog::ActionOnMouseEvent(const EventData& event)
{
	//Empty
}

void CDialog::CreateBackgroundImage()
{
	TGraphicObjectRef spRectangle = std::make_shared<CRectangle>(GetContainingWindow()->GetSize(), COLOR_WHITE);
	spRectangle->SetOrigin(CPoint(0, 0));
	AddChild(spRectangle);
}

void CDialog::OnLifetimeEvent(EDialogLifetimeEvent event)
{
	MARKER("CDialog::OnLifetimeEvent()");
	return;
}

bool CDialog::OnSignal(const SignalData & signal)
{
	return false;
}
