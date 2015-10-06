#ifndef __GraphicObject_H__
#define __GraphicObject_H__

#include <Object.h>
#include <SharedPtr.h>
#include <list>

//http://grafika.me/lessons - OpenGL tutorials

class CGraphicObject : public CObject
{
public:
	typedef CSharedPtr<CGraphicObject> CGraphicObjectRef;

	CGraphicObject();
	~CGraphicObject();

	virtual void Draw() = 0;

	void AddChildren(CGraphicObjectRef obj);
	void RemoveChildren(CGraphicObjectRef obj);
	void RemoveAllChildren() { m_children.erase(m_children.begin(), m_children.end()); }

private:
	std::list<CGraphicObjectRef> m_children;   
};

#endif //__GraphicObject_H__