#include "Globals.h"
#include "Logger.h"
#include <memory>
#include "UtilityMacros.h"
#include "WindowManager.h"
#include "Window.h"
#include "ApplicationInfo.h"

#include "File.h"

#define NO_GUI
#define EXPERIMENTAL_GUI

CGlobals::CGlobals()
{
	MARKER("CGlobals::CGlobals()");

	Init();
}

CGlobals::~CGlobals()
{
	MARKER("CGlobals::~CGlobals()");
}

void CGlobals::Init()
{
	MARKER("CGlobals::Init()");

	m_strAppFilepath = ::GetAppFilePath();
}

void CGlobals::InitGUI()
{
	MARKER("CGlobals::InitGUI()");
}
