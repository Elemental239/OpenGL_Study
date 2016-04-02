#include "Dialog.h"
#include "Logger.h"

CDialog::CDialog() : m_bChildrenInited(false)
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
	MARKER("CDialog::OnSystemEvent()");
	return false;
}

void CDialog::OnLifetimeEvent(EDialogLifetimeEvent event)
{
	MARKER("CDialog::OnLifetimeEvent()");
	return;
}
