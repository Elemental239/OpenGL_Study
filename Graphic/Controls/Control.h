#ifndef __Controls_Control_H__
#define __Controls_Control_H__

#include "Object.h"
#include "GraphicObject.h"
#include "SharedPtr.h"
#include "WindowEvents.h"

class IControl;
typedef CSharedPtr<IControl> TControlRef;

/*
Control -> Function part: event's handling & child/parent links
		-> Visual part - graphic object 

*/
class IControl : public CObject
{
public:
	IControl(TGraphicObjectRef representation);
	virtual ~IControl() {}

	virtual CSize GetSize() = 0;
	virtual CPoint GetOrigin() = 0;
	virtual void SetVisualPresentation(TGraphicObjectRef graphicObject, int nOrdinal = 0) = 0;
	virtual int GetVisualPresentationNumber() const = 0;
	virtual TGraphicObjectRef GetVisualPresentation(int index) const = 0;
	virtual void AdjustGraphicPresentations(CPoint origin, CSize size) = 0;

	virtual void SetParent(IControl* spParent) = 0;
	virtual void AddChild(TControlRef obj) = 0;
	virtual void RemoveChild(TControlRef obj) = 0;
	virtual void RemoveChildren() = 0;

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual bool OnSignal(const SignalData& signal) = 0;
	virtual void Draw() = 0;

protected:
	std::vector<TGraphicObjectRef> m_visualPresentations;
};

class CControl : public IControl
{
public:
	CControl(TGraphicObjectRef representation = new CGraphicObject());
	virtual ~CControl() {}

	virtual void Draw() override;
	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool OnSignal(const SignalData& signal) override;
	
	virtual void SetVisualPresentation(TGraphicObjectRef graphicObject, int nOrdinal = 0) override;
	virtual int GetVisualPresentationNumber() const override { return 1; }
	virtual TGraphicObjectRef GetVisualPresentation(int index) const override;
	virtual void AdjustGraphicPresentations(CPoint origin, CSize size) override;
		
	virtual void SetParent(IControl* spParent) override { m_pParent = spParent; }
	virtual void AddChild(TControlRef obj) override;
	virtual void RemoveChild(TControlRef obj) override;
	virtual void RemoveChildren() override;

	virtual CSize GetSize() override { return GetCurrentVisualPresentation()->GetRectSize(); }
	virtual CPoint GetOrigin() override { return GetCurrentVisualPresentation()->GetOrigin(); }

protected:
	std::vector<TControlRef> m_children;
	IControl* m_pParent;

	bool IsPointInsideMyBounds(const CPoint& point) const;
	virtual TGraphicObjectRef GetCurrentVisualPresentation() const { return m_visualPresentations[0]; }

private:
	void DrawChild(TControlRef spControl);
};

#endif //__Controls_Control_H__
