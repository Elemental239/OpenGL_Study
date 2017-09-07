#pragma once
#include "SharedPtr.h"

class IControl;

class CControlsContainer
{
public:
	void AddChild(CSharedPtr<IControl> obj);
	void RemoveChild(CSharedPtr<IControl> obj);
	void RemoveChildren();

protected:
	std::vector<CSharedPtr<IControl> > m_children;
};
