#ifndef __HelloWorldTestWindow_H__
#define __HelloWorldTestWindow_H__

#include "Object.h"

class CHelloWorldTestWindow : public CObject
{
public:
	CHelloWorldTestWindow();
	~CHelloWorldTestWindow();

	void Draw();

private:
	bool LoadResources() { return true; }
	static void Idle() { }
	static void Render();
};

#endif //__HelloWorldTestWindow_H__
