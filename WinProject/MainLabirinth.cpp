#include <windows.h>
#include "Logger.h"
#include "Globals.h"

//void main(void)
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	LOG("WinMain");	
	
	GLOBALS.Init();
	GLOBALS.InitGUI();

	return 0;
}

