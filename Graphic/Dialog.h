#ifndef __Graphic_Dialog_H__
#define __Graphic_Dialog_H__

#include <vector>
#include "WindowManager.h"
#include "SharedPtr.h"
#include "ColorsResources.h"
#include "Controls/ControlsContainer.h"

enum EDialogLifetimeEvent
{
	DIALOG_LIFETIME_EVENT_BEFORE_SHOW,
	DIALOG_LIFETIME_EVENT_AFTER_SHOW,
	DIALOG_LIFETIME_EVENT_BEFORE_HIDE,
	DIALOG_LIFETIME_EVENT_AFTER_HIDE
};

class IDialog : public CObject, public CControlsContainer
{
	friend class IWindow;
public:
	IDialog(): m_bClosed(false) {}

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual void OnLifetimeEvent(EDialogLifetimeEvent event) = 0;

	virtual void InitChildren() = 0;

	bool IsClosed() const { return m_bClosed; }
	void Close() { m_bClosed = true; }

	virtual CColor GetBackgroundColor() { return COLOR_WHITE; }

protected:
	IWindow* GetContainingWindow() { return m_pWindow; }
	
private:
	bool m_bClosed;
	IWindow* m_pWindow;

	void SetContainingWindow(IWindow* pWindow) { m_pWindow = pWindow; }
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
	bool ProcessResizeEvent(const EventData& event);

	void ActionOnButtonEvent(const EventData& event);
	void ActionOnMouseEvent(const EventData& event);
};

#endif //__Graphic_Dialog_H__