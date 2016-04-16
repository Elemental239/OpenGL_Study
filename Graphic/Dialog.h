#ifndef __Graphic_Dialog_H__
#define __Graphic_Dialog_H__

#include "Controls/Control.h"
#include <vector>
#include "WindowManager.h"
#include "SharedPtr.h"

enum EDialogLifetimeEvent
{
	DIALOG_LIFETIME_EVENT_BEFORE_SHOW,
	DIALOG_LIFETIME_EVENT_AFTER_SHOW,
	DIALOG_LIFETIME_EVENT_BEFORE_HIDE,
	DIALOG_LIFETIME_EVENT_AFTER_HIDE
};

class IDialog : public CControl
{
public:
	IDialog(): m_bClosed(false) {}

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual void OnLifetimeEvent(EDialogLifetimeEvent event) = 0;

	bool IsClosed() const { return m_bClosed; }
	void Close() { m_bClosed = true; }

	virtual void InitChildren() = 0;

	friend IWindow; // Window sets size to dialog, but I don't want to have public method for this

private:
	bool m_bClosed;
};
typedef CSharedPtr<IDialog> TDialogRef;

class CDialog : public IDialog
{
public:
	CDialog();
	~CDialog();

	virtual bool OnSystemEvent(const EventData& event) override;
	virtual void OnLifetimeEvent(EDialogLifetimeEvent event) override;

	virtual void InitChildren() override;

private:
	bool m_bChildrenInited;

	virtual void CreateChildren() = 0;

	bool ProcessButtonEvent(const EventData& event);
	bool ProcessMouseEvent(const EventData& event);

	void ActionOnButtonEvent(const EventData& event);
	void ActionOnMouseEvent(const EventData& event);
};

#endif //__Graphic_Dialog_H__