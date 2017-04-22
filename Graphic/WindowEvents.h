#ifndef __Graphic__WindowEvents_H__
#define __Graphic__WindowEvents_H__

#include "GraphicGeneral.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

enum EVENT_TYPE
{
	EVT_MOUSE,
	EVT_CURSOR_POSITION,
	EVT_RESIZE,
	EVT_BUTTON
};

enum class MOUSE_EVENT_BUTTON
{
	LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
	CENTER_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
	RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
	BUTTON_4 = GLFW_MOUSE_BUTTON_4,
	BUTTON_5 = GLFW_MOUSE_BUTTON_5,
	BUTTON_6 = GLFW_MOUSE_BUTTON_6,
	BUTTON_7 = GLFW_MOUSE_BUTTON_7,
	BUTTON_8 = GLFW_MOUSE_BUTTON_8
};

enum class MOUSE_EVENT_TYPE
{
	PRESS,
	RELEASE
};

struct EventData
{
	EVENT_TYPE m_nEventType;
	GLFWwindow* m_pTargetWindow;

	struct //EVT_MOUSE
	{
		MOUSE_EVENT_TYPE m_nMouseEventType;
		MOUSE_EVENT_BUTTON m_nMouseEventButton;
		int m_nMouseEventModeFlags;
	};

	struct // CURSOR_POSITION
	{
		CGenericPoint<double> m_cursorPosition;
	};

	struct //EVT_BUTTON
	{
		int m_nKeyboardKey;
		int m_nScancode;
		int m_nAction;
		int m_nMode;
	};

	struct //EVT_RESIZE
	{
		int m_nNewHeight;
		int m_nNewWidth;
	};
};

struct SignalData
{
	int m_nCommand;
};

#endif //__Graphic__WindowEvents_H__
