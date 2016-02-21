#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>
#include "GraphicGeneral.h"

class CGraphicObject;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

enum EAlignOption : int
{
	NONE,
	LEFT,
	RIGHT,
	CENTER,
	TOP,
	BOTTOM
};

class CGraphicObject : public CObject
{
public:
	CGraphicObject();
	virtual ~CGraphicObject();

	virtual void Draw();
	virtual void DrawSelf() {}
	
	void SetParent(CGraphicObject* spParent) { m_pParent = spParent; }
	void AddChild(TGraphicObjectRef obj);
	void RemoveChild(TGraphicObjectRef obj);
	void RemoveChildren() { m_children.erase(m_children.begin(), m_children.end()); }

	///<summary> Origin is the bottom-left point of the object.</summary>
	void SetOrigin(CPoint point) { m_origin = point; }
	///<summary> Origin is the bottom-left point of the object.</summary>
	CPoint GetOrigin() const { return m_origin; }

	void SetAlignX(EAlignOption option) { m_nAlignOptionX = option; }
	EAlignOption GetAlignX() const { return m_nAlignOptionX; }
	void SetAlignY(EAlignOption option) { m_nAlignOptionY = option; }
	EAlignOption GetAlignY() const { return m_nAlignOptionY; }

	void SetMargins(const std::vector<int> &margins) { m_margins = margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.
	void SetMargins(int left, int top, int right, int bottom);
	std::vector<int> GetMargins() const { return m_margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.

protected:
	std::vector<TGraphicObjectRef> m_children;
	CGraphicObject* m_pParent;
	CPoint m_origin;
	EAlignOption m_nAlignOptionX;
	EAlignOption m_nAlignOptionY;
	std::vector<int> m_margins;
	CSize m_rectSize;	// Size of containing rectangle

	///<summary> Get size of minimal containing rect</summary>
	CSize GetRectSize() const { return m_rectSize; }
	///<summary> Set size of minimal containing rect</summary>
	void SetRectSize(CSize size) { m_rectSize = size; }

	CPoint CalcChildOriginPoint(TGraphicObjectRef child);

};

#endif //__Graphic_GraphicObject_H__
