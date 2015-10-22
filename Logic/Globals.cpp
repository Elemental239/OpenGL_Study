#include "Globals.h"
#include "Logger.h"
#include <memory>
#include "UtilityMacros.h"

CGlobals::CGlobals()
{
	MARKER("CGlobals::CGlobals()");
}

CGlobals::~CGlobals()
{
	MARKER("CGlobals::~CGlobals()");
}

void CGlobals::Init()
{
	MARKER("CGlobals::Init()");

	m_spHelloWorldTestWindow = CSharedPtr<CHelloWorldTestWindow>(new CHelloWorldTestWindow);
	//m_spHelloWorldTestWindow->Draw();
}
