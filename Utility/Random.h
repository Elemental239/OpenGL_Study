#ifndef __Utility_Random_H__
#define __Utility_Random_H__

#include "Singleton.h"
#include "Object.h"
#include <random>

class Random : public CObject
{
// Note: functions naming ::= Get<type><LeftBound include><RightBound include>, where <bound include> ::= I|E (include/exclude)
public:
	SINGLETON(Random, Random());

	///<summary>return random int in [nLowBound, nHighBound)</summary>
	int GetIntIE(int nLowBound, int nHighBound);
	///<summary>return random int in [nLowBound, nHighBound]</summary>
	int GetIntII(int nLowBound, int nHighBound); 
	///<summary>return random float in [nLowBound, nHighBound)</summary>
	float GetFloatIE(float nLowBound, float nHighBound);

private:
	std::mt19937 m_generator;
};

#endif //__Utility_Random_H__
