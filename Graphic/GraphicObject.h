#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>
#include "GraphicGeneral.h"

class CGraphicObject;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

enum EAlignOption : int32_t
{
	NONE		= 0x00000000,
	LEFT		= 0x00000001,
	RIGHT		= 0x00000010,
	TOP			= 0x00000100,
	BOTTOM		= 0x00001000,
	CENTER_X	= 0x00010000,
	CENTER_Y	= 0x00100000
};

enum ESizeOption : int32_t
{
	NONE	= 0x00000000,
	FILL_X	= 0x00000001,
	FILL_Y	= 0x00000010
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

	void SetAlignOptions(int32_t option) { m_nAlignOption = option; }
	void SetAlign(EAlignOption option) { m_nAlignOption |= option; }
	int32_t GetAlignOptions() const { return m_nAlignOption; }

	void SetMargins(const std::vector<int> &margins) { m_margins = margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.
	void SetMargins(int left, int top, int right, int bottom);
	std::vector<int> GetMargins() const { return m_margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.

protected:
	std::vector<TGraphicObjectRef> m_children;
	CGraphicObject* m_pParent;
	CPoint m_origin;
	int32_t m_nAlignOption;	//Flags
	std::vector<int> m_margins;
	CSize m_rectSize;	// Size of containing rectangle

	///<summary> Get size of minimal containing rect</summary>
	CSize GetRectSize() const { return m_rectSize; }
	///<summary> Set size of minimal containing rect</summary>
	void SetRectSize(CSize size) { m_rectSize = size; }

	CPoint CalcChildOriginPoint(TGraphicObjectRef child);

};

#endif //__Graphic_GraphicObject_H__
