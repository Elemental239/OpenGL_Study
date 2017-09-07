#include "ControlsContainer.h"
#include "Control.h"

void CControlsContainer::AddChild(CSharedPtr<IControl>& obj)
{
	if (!obj)
		return;

	obj->SetParent(this);
	m_children.push_back(obj);
}

void CControlsContainer::RemoveChild(CSharedPtr<IControl> obj)
{
	for (auto iter = m_children.end(); iter-- != m_children.begin(); )
	{
		if ((*iter) == obj)
			m_children.erase(iter);
	}

	obj->SetParent(nullptr);
}

void CControlsContainer::RemoveChildren()
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		(*iter)->SetParent(nullptr);
	}

	m_children.erase(m_children.begin(), m_children.end());
}