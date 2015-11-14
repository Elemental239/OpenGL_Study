#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>
#include "GraphicGeneral.h"

class CGraphicObject;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

class CGraphicObject : public CObject
{
public:
	CGraphicObject();
	~CGraphicObject();

	virtual void Draw();
	virtual void DrawSelf() {}
	virtual CPoint GetOrigin() { return CPoint(); }

	void SetParent(CGraphicObject* spParent) { m_pParent = spParent; }
	void AddChild(TGraphicObjectRef obj);
	void RemoveChild(TGraphicObjectRef obj);
	void RemoveChildren() { m_children.erase(m_children.begin(), m_children.end()); }

protected:
	std::vector<TGraphicObjectRef> m_children;
	CGraphicObject* m_pParent;
};

#endif //__Graphic_GraphicObject_H__
