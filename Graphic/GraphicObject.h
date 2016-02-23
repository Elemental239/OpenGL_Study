#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>
#include "GraphicGeneral.h"
#include "InlineFunctions.h"

class CGraphicObject;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

enum class EAlignOption : int64_t
{
	NONE		= 0x0000000000000000,
	LEFT		= 0x0000000000000001,
	RIGHT		= 0x0000000000000010,
	TOP			= 0x0000000000000100,
	BOTTOM		= 0x0000000000001000,
	CENTER_X	= 0x0000000000010000,
	CENTER_Y	= 0x0000000000100000
};

enum class ESizeOption : int32_t
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

	void SetAlignOptions(int64_t option) { m_nAlignOption = option; }
	void SetAlignOption(EAlignOption option) { m_nAlignOption = (m_nAlignOption | enumValueToInt(option)); }
	int64_t GetAlignOptions() const { return m_nAlignOption; }

	void SetSizeOptions(int32_t options) { m_nSizeOption = options; }
	void SetSizeOption(ESizeOption option) { m_nSizeOption = (m_nSizeOption | enumValueToInt(option)); }
	int32_t GetSizeOptions() const { return m_nSizeOption; }

	void SetMargins(const std::vector<int> &margins) { m_margins = margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.
	void SetMargins(int left, int top, int right, int bottom);
	std::vector<int> GetMargins() const { return m_margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.

protected:
	std::vector<TGraphicObjectRef> m_children;
	CGraphicObject* m_pParent;
	CPoint m_origin;
	int64_t m_nAlignOption;	//Flags
	int32_t m_nSizeOption;	//Flags
	std::vector<int> m_margins;
	CSize m_rectSize;	// Size of containing rectangle

	///<summary> Get size of minimal containing rect</summary>
	CSize GetRectSize() const { return m_rectSize; }
	///<summary> Set size of minimal containing rect</summary>
	void SetRectSize(CSize size) { m_rectSize = size; }

	CPoint CalcChildOriginPoint(TGraphicObjectRef child);

};

#endif //__Graphic_GraphicObject_H__
