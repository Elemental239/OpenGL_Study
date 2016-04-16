#include "Button.h"
#include "Logger.h"

CButton::CButton(int nCommand, TGraphicObjectRef representation/* = new CGraphicObject()*/, TGraphicObjectRef pressedRepresentation/* = nullptr()*/) :
	CControl(representation), m_nCommand(nCommand), m_state(BUTTON_STATE::NONE)
{
	m_spPressedRepresentation = pressedRepresentation != nullptr ? pressedRepresentation : representation;
}

void CButton::EmitOnPressedSignal()
{
	SignalData signal;
	signal.m_nCommand = m_nCommand;

	if (m_pParent)
	{
		m_pParent->OnSignal(signal);
	}
}

bool CButton::OnSystemEvent(const EventData& event)
{
	switch (event.m_nEventType)
	{
		case EVT_CURSOR_POSITION:
		{
			if (ProcessCursorPositionEvent(event))
			{
				return true;
			}
			break;
		}
	
		case EVT_MOUSE:
		{
			if (ProcessMouseButtonEvent(event))
			{
				if (m_state == BUTTON_STATE::RELEASED)
					EmitOnPressedSignal();

				return true;
			}

			break;
		}

		default:
			break;
	};
	
	return __super::OnSystemEvent(event);
}

bool CButton::ProcessCursorPositionEvent(const EventData& event)
{
	if (IsPointInsideMyBounds(FloatPointToIntPoint(event.m_cursorPosition)))
	{
		m_state = BUTTON_STATE::IN_FOCUS;

		CPoint origin = GetVisualRepresentation()->GetOrigin();
		CPoint point = origin + GetVisualRepresentation()->GetRectSize();
		LOG("cursor position = %s, my position = %s - %s", event.m_cursorPosition.ToString().ToCharPtr(), 
			origin.ToString().ToCharPtr(), point.ToString().ToCharPtr());

		return true;
	}
	else
	{
		m_state = BUTTON_STATE::RELEASED;
	}

	return false;
}

bool CButton::ProcessMouseButtonEvent(const EventData& event)
{
	if (m_state != BUTTON_STATE::IN_FOCUS)
		return false;

	if (event.m_nMouseEventType == MOUSE_EVENT_TYPE::PRESS)
	{
		LOG("Button pressed");
		m_state = BUTTON_STATE::PRESSED;
	}
	else if (event.m_nMouseEventType == MOUSE_EVENT_TYPE::RELEASE)
	{
		LOG("Button released");
		m_state = BUTTON_STATE::RELEASED;
	}

	return true;
}
