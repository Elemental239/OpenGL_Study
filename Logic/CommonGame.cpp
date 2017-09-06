#include "CommonGame.h"
#include "Logger.h"
#include "Globals.h"

CCommonGame::CCommonGame()
{
	MARKER("CCommonGame::CCommonGame()");
}

void CCommonGame::Init()
{
	MARKER("CCommonGame::Init()");
	GLOBALS.Init();
}

void CCommonGame::Start()
{
	MARKER("CCommonGame::Start()");
	GLOBALS.InitGUI();
}
