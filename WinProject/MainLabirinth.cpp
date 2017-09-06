#include <windows.h>
#include "Logger.h"
#include "CommonGame.h"

//void main(void)
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	LOG("WinMain");	
	
	CCommonGame game;

	game.Init();
	game.Start();

	return 0;
}

