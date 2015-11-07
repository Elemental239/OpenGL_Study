#include "Dialog.h"
#include "Logger.h"

CDialog::CDialog()
{
	MARKER("CDialog::CDialog()");
}

CDialog::~CDialog()
{
	MARKER("CDialog::~CDialog()");
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
