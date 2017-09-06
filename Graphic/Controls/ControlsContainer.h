#pragma once
#include "Control.h"

class CControlsContainer
{
public:
	void AddChild(TControlRef obj);
	void RemoveChild(TControlRef obj);
	void RemoveChildren();

protected:
	std::vector<TControlRef> m_children;
};
