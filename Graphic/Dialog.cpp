#include "Dialog.h"
#include "Logger.h"

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

bool CDialog::OnSystemEvent(const EventData& event)
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if ((*iter)->OnSystemEvent(event))
			return true;
	}

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

		default: 
			break;
	} //switch (event.m_nEventType)

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
