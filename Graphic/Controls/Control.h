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

	virtual void SetVisualRepresentation(TGraphicObjectRef graphicObject) = 0;
	virtual TGraphicObjectRef GetVisualRepresentation() const = 0;

	virtual void SetParent(IControl* spParent) = 0;
	virtual void AddChild(TControlRef obj) = 0;
	virtual void RemoveChild(TControlRef obj) = 0;
	virtual void RemoveChildren() = 0;

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual bool OnSignal(const SignalData& signal) = 0;
	virtual void Draw() = 0;

protected:
	TGraphicObjectRef m_spVisualRepresentation;
};

class CControl : public IControl
{
public:
	CControl(TGraphicObjectRef representation = new CGraphicObject());
	virtual ~CControl() {}

	virtual void Draw() override;
	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool OnSignal(const SignalData& signal) override;

	virtual void SetVisualRepresentation(TGraphicObjectRef graphicObject) override;
	virtual TGraphicObjectRef GetVisualRepresentation() const override { return m_spVisualRepresentation; }

	virtual void SetParent(IControl* spParent) override { m_pParent = spParent; }
	virtual void AddChild(TControlRef obj) override;
	virtual void RemoveChild(TControlRef obj) override;
	virtual void RemoveChildren() override;

protected:
	std::vector<TControlRef> m_children;
	IControl* m_pParent;

	bool IsPointInsideMyBounds(const CPoint& point) const;
};

#endif //__Controls_Control_H__
