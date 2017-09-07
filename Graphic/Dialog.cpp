#include "Dialog.h"
#include "Logger.h"
#include "GraphicObjects/Rectangle.h"
#include "SharedPtr.h"

void IDialog::AddChild(CSharedPtr<CGraphicObject>& obj)
{
	CControlsContainer::AddChild(obj.static_cast_to<IControl>());	// cause every GraphicObject is a control
}

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

		CreateChildren();
	}
}

void CDialog::Draw()
{
	for (size_t i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Draw();
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
			if (ProcessResizeEvent(event))
			{
				//Do nothing
			}
			break;
		}

		default: 
			break;
	} //switch (event.m_nEventType)

	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if ((*iter)->OnSystemEvent(event))
			return true;
	}

	return false;
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

bool CDialog::ProcessResizeEvent(const EventData& event)
{
	//for (int i = 0; i < GetVisualPresentationNumber(); i++)
	//{
	//	auto spVisualPresentation = GetVisualPresentation(i).static_cast_to<CRectangle>();
	//	CSize newSize = CSize(event.m_nNewWidth, event.m_nNewHeight);
	//	spVisualPresentation->SetSize(newSize);
	//}

	return false; // Pass event to all children cause whole UI should change size
}

void CDialog::ActionOnButtonEvent(const EventData& event)
{
	//Empty
}

void CDialog::ActionOnMouseEvent(const EventData& event)
{
	//Empty
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
