#ifndef __CGlobals_H__
#define __CGlobals_H__

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
};

#define GLOBALS CGlobals::Instance()

#endif //__CGlobals_H__