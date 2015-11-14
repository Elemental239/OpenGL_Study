#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>

class CGraphicObject;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

class CGraphicObject : public CObject
{
public:
	CGraphicObject();
	~CGraphicObject();

	virtual void Draw();
	virtual void DrawSelf() {}

	void AddChild(TGraphicObjectRef obj);
	void RemoveChild(TGraphicObjectRef obj);
	void RemoveChildren() { m_children.erase(m_children.begin(), m_children.end()); }

protected:
	std::vector<TGraphicObjectRef> m_children;
};

#endif //__Graphic_GraphicObject_H__
