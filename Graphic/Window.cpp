#include "Window.h"
#include "Logger.h"

CWindow::CWindow()
{
	MARKER("CWindow::CWindow()");
}

CWindow::~CWindow()
{
	MARKER("CWindow::~CWindow()");
}

bool CWindow::OnSystemEvent(const EventData& event)
{
	return false;
}
