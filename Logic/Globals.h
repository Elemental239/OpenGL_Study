#ifndef __Logic_CGlobals_H__
#define __Logic_CGlobals_H__

#include <memory>
#include "MainWindow.h"
#include "SharedPtr.h"
#include "Object.h"

class CHelloWorldTestWindow;

class CGlobals : public CObject
{
public:
	virtual ~CGlobals();
	static CGlobals& Instance() { static CGlobals globals; return globals; }

	void Init();

	CSharedPtr<CHelloWorldTestWindow> m_spHelloWorldTestWindow;

private:
	CGlobals();
	CGlobals& operator=(const CGlobals&);
	CGlobals(const CGlobals&);

	CSharedPtr<CMainWindow> m_spMainWindow;
};

#define GLOBALS CGlobals::Instance()

#endif //__Logic_CGlobals_H__