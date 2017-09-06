#include "Button.h"
#include "Logger.h"

CButton::CButton(int nCommand, TGraphicObjectRef representation/* = new CGraphicObject()*/, TGraphicObjectRef pressedRepresentation/* = nullptr()*/) :
	CControl(representation), m_nCommand(nCommand), m_state(BUTTON_STATE::NONE)
{
	auto spPressedRepresentation = pressedRepresentation != nullptr ? pressedRepresentation : representation;
	m_visualPresentations.push_back(spPressedRepresentation);
}

TGraphicObjectRef CButton::GetVisualPresentation(int index) const
{
	if (index < 0 || index > 1)
		return nullptr;

	return m_visualPresentations[index];
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

void CButton::Draw()
{
	TGraphicObjectRef currentRepresentation = m_state == BUTTON_STATE::PRESSED ? m_visualPresentations[1] : m_visualPresentations[0];
	currentRepresentation->DrawSelf();
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->Draw();
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
		if (m_state != BUTTON_STATE::PRESSED)
		{
			m_state = BUTTON_STATE::IN_FOCUS;
		}

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
	if (m_state != BUTTON_STATE::IN_FOCUS && m_state != BUTTON_STATE::PRESSED)
		return false;

	if (event.m_nMouseEventType == MOUSE_EVENT_TYPE::PRESS)
	{
		m_state = BUTTON_STATE::PRESSED;
	}
	else if (event.m_nMouseEventType == MOUSE_EVENT_TYPE::RELEASE)
	{
		if (m_state != BUTTON_STATE::PRESSED)
		{
			return true;
		}

		m_state = BUTTON_STATE::RELEASED;
	}

	return true;
}
