#ifndef __Graphic_Window_H__
#define __Graphic_Window_H__

#include "Object.h"

struct GLFWwindow;

class CWindow : public CObject
{
public:
	CWindow();
	~CWindow();

private:
	GLFWwindow* m_window;
};

#endif //__Graphic_Window_H__