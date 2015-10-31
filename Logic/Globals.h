#ifndef __Logic_CGlobals_H__
#define __Logic_CGlobals_H__

#include <memory>
#include "MainWindow.h"
#include "SharedPtr.h"
#include "Object.h"
#include "Singleton.h"

class CHelloWorldTestWindow;

class CGlobals : public CObject
{
public:
	SINGLETON(CGlobals, CGlobals());

	void Init();

	CSharedPtr<CHelloWorldTestWindow> m_spHelloWorldTestWindow;

private:
	CSharedPtr<CMainWindow> m_spMainWindow;
};

#define GLOBALS CGlobals::Instance()

#endif //__Logic_CGlobals_H__