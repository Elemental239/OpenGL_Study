#ifndef __Graphic_Dialog_H__
#define __Graphic_Dialog_H__

#include "GraphicObject.h"
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

class IDialog : public CGraphicObject
{
public:
	IDialog() : m_bClosed(false) {}

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual void OnLifetimeEvent(EDialogLifetimeEvent event) = 0;

	bool IsClosed() { return m_bClosed; }
	void Close() { m_bClosed = true; }
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
};

#endif //__Graphic_Dialog_H__