#ifndef __Controls_Control_H__
#define __Controls_Control_H__

#include "Object.h"
#include "GraphicObject.h"
#include "SharedPtr.h"
#include "WindowEvents.h"
#include "ControlsContainer.h"

class IControl;
typedef CSharedPtr<IControl> TControlRef;

class IControl : public CObject, public CControlsContainer
{
public:
	//virtual void AdjustGraphicPresentations(CPoint origin, CSize size) = 0;

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual bool OnSignal(const SignalData& signal) = 0;
	virtual void Draw() = 0;

	///<summary> Origin is the bottom-left point of the object.</summary>
	void SetOrigin(CPoint point) { m_origin = point; }
	///<summary> Origin is the bottom-left point of the object.</summary>
	CPoint GetOrigin() const { return m_origin; }

	virtual void SetSize(CSize size) const { m_size = size; }
	virtual CSize GetSize() const { return m_size; }

private:
	CPoint m_origin;
	CSize m_size;
};

class CControl : public IControl
{
public:
	CControl();

	virtual void Draw() override;
	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool OnSignal(const SignalData& signal) override;
	
	//virtual void AdjustGraphicPresentations(CPoint origin, CSize size) override;
		
	virtual void SetParent(IControlsContainer* spParent) override { m_pParent = spParent; }

	//virtual CSize GetSize() override { return GetCurrentVisualPresentation()->GetRectSize(); }
	//virtual CPoint GetOrigin() override { return GetCurrentVisualPresentation()->GetOrigin(); }

protected:
	IControlsContainer* m_pParent;

	virtual void DrawSelf() = 0;
	bool IsPointInsideMyBounds(const CPoint& point) const;

private:
	void DrawChild(TControlRef spControl);
};

#endif //__Controls_Control_H__
