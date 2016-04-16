#ifndef __Controls_Button_H__
#define __Controls_Button_H__

#include "Control.h"

class CButton : public CControl
{
public:
	CButton(int nCommand, TGraphicObjectRef representation = new CGraphicObject(), TGraphicObjectRef pressedRepresentation = nullptr);
	virtual ~CButton() {}

	virtual bool OnSystemEvent(const EventData& event) override;

private:
	enum class BUTTON_STATE
	{
		NONE,
		IN_FOCUS,
		PRESSED,
		RELEASED
	};

	BUTTON_STATE m_state;
	TGraphicObjectRef m_spPressedRepresentation;
	int m_nCommand;

	bool ProcessCursorPositionEvent(const EventData& event);
	bool ProcessMouseButtonEvent(const EventData& event);

	void EmitOnPressedSignal();
};

#endif //__Controls_Button_H__
