#ifndef __Graphic_StartMenuDialog__
#define __Graphic_StartMenuDialog__

#include "Dialog.h"
#include "OpenGL.h"
#include "glfw-3.1.1/include/GLFW/glfw3.h"

class CMainMenuDialog : public CDialog
{
public:
	CMainMenuDialog();
	~CMainMenuDialog();

	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool OnSignal(const SignalData& signal) override;

	virtual void CreateChildren() override;
};

#endif //__Graphic_StartMenuDialog__