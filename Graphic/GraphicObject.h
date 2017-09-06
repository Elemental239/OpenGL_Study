#ifndef __Graphic_GraphicObject_H__
#define __Graphic_GraphicObject_H__

#include "Object.h"
#include "SharedPtr.h"
#include <vector>
#include "GraphicGeneral.h"
#include "InlineFunctions.h"
#include "Controls/Control.h"

class CGraphicObject;
class IControl;
typedef CSharedPtr<CGraphicObject> TGraphicObjectRef;

enum class EAlignOption : int64_t
{
	NONE		= 0x0000000000000000,
	LEFT		= 0x0000000000000001, // The same as NONE for X
	RIGHT		= 0x0000000000000010,
	TOP			= 0x0000000000000100,
	BOTTOM		= 0x0000000000001000, // The same as NONE for Y
	FRONT		= 0x0000000000010000,
	BACK		= 0x0000000000100000,
	CENTER_X	= 0x0000000001000000,
	CENTER_Y	= 0x0000000010000000,
	CENTER_Z	= 0x0000000100000000,
};

enum class ESizeOption : int32_t
{
	NONE	= 0x00000000,
	FILL_X	= 0x00000001,
	FILL_Y	= 0x00000010,
	FILL_Z	= 0x00000100,
};

class CGraphicObject : public CControl
{
public:
	CGraphicObject();

	//void AdjustSizeAndPosition();
	//void SetContainerParams(CPoint origin, CSize size) { m_containerOrigin = origin; m_containerSize = size; }
	//void Reinitialize() { m_bInited = false; };
	
	void SetAlignOptions(int64_t option) { m_nAlignOption = option; }
	void SetAlignOption(EAlignOption option) { m_nAlignOption = (m_nAlignOption | enumValueToInt(option)); }
	int64_t GetAlignOptions() const { return m_nAlignOption; }

	void SetSizeOptions(int32_t options) { m_nSizeOption = options; }
	void SetSizeOption(ESizeOption option) { m_nSizeOption = (m_nSizeOption | enumValueToInt(option)); }
	int32_t GetSizeOptions() const { return m_nSizeOption; }

	void SetMargins(const std::vector<int> &margins) { m_margins = margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.
	void SetMargins(int left, int top, int right, int bottom);

	///<summary>Left, top, right, bottom</summary>
	std::vector<int> GetMargins() const { return m_margins; } //TODO: OPTIMISE: array copy with reserve/std::copy/etc.

protected:
	bool m_bInited;
	int64_t m_nAlignOption;	//Flags
	int32_t m_nSizeOption;	//Flags
	std::vector<int> m_margins;
	//CPoint m_containerOrigin;
	//CSize m_containerSize;

	//virtual void PrepareInitiation() { AdjustSizeAndPosition(); }
};

#endif //__Graphic_GraphicObject_H__
