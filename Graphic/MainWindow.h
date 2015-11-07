#ifndef __Graphic_MainWindow_H__
#define __Graphic_MainWindow_H__

#include "Object.h"
#include "Window.h"

class CMainWindow : public CWindow
{
public:
	CMainWindow(const WindowConstructionParams& params);
	~CMainWindow();

//	virtual bool OnSystemEvent(const EventData& event) override;
};

#endif //__Graphic_MainWindow_H__
