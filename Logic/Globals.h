#ifndef __GLOBALS_H__
#define __GLOBALS_H__

class Globals
{
public:
	virtual ~Globals();
	static Globals& Instance() { static Globals globals; return globals; }

	void Init();

private:
	Globals();
	Globals& operator=(const Globals&);
	Globals(const Globals&);
};

#define GLOBALS Globals::Instance()

#endif //__GLOBALS_H__