#include "Globals.h"
#include "Logger.h"
#include <memory>
#include "UtilityMacros.h"

#include "File.h"

#define NO_GUI

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

#if !defined(NO_GUI)
	m_spHelloWorldTestWindow = CSharedPtr<CHelloWorldTestWindow>(new CHelloWorldTestWindow);
	m_spHelloWorldTestWindow->Draw();
#endif

	CFile file(CString("input.txt"), EFileMode::FILE_MODE_OPEN);
	bool bExist = file.IsExist();
}
