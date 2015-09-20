#ifndef __CGlobals_H__
#define __CGlobals_H__

#include <memory>
#include <MainWindow.h>
#include <SharedPtr.h>

class CGlobals
{
public:
	virtual ~CGlobals();
	static CGlobals& Instance() { static CGlobals globals; return globals; }

	void Init();

private:
	CGlobals();
	CGlobals& operator=(const CGlobals&);
	CGlobals(const CGlobals&);

	CSharedPtr<CMainWindow> m_spMainWindow;
};

#define GLOBALS CGlobals::Instance()

#endif //__CGlobals_H__