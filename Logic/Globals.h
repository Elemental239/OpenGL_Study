#ifndef __GLOBALS_H__
#define __GLOBALS_H__

class Globals
{
public:
	static Globals& Instance() { static Globals globals; return globals; }

	void Init();

private:
	Globals();
	virtual ~Globals();
	Globals& operator=(Globals&) = delete;
	Globals(const Globals&) = delete;
};

#endif //__GLOBALS_H__