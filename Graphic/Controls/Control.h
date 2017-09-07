#ifndef __Controls_Control_H__
#define __Controls_Control_H__

#include "Object.h"
#include "SharedPtr.h"
#include "WindowEvents.h"

class IControl;
typedef CSharedPtr<IControl> TControlRef;

class IControl : public CObject
{
public:
	IControl();

	virtual void AdjustPositionAndSize() = 0;

	virtual bool OnSystemEvent(const EventData& event) = 0;
	virtual bool OnSignal(const SignalData& signal) = 0;
	virtual void Draw() = 0;

	///<summary> Origin is the bottom-left point of the object.</summary>
	virtual void SetOrigin(CPoint point) { m_origin = point; }
	///<summary> Origin is the bottom-left point of the object.</summary>
	CPoint GetOrigin() const { return m_origin; }
	virtual void SetSize(CSize size) { m_size = size; }
	virtual CSize GetSize() const { return m_size; }
	void SetParent(IControl* spParent) { m_pParent = spParent; }

	void AddChild(CSharedPtr<IControl>& obj);
	void RemoveChild(CSharedPtr<IControl> obj);
	void RemoveChildren();

protected:
	std::vector<CSharedPtr<IControl> > m_children;
	IControl* GetParent() { return m_pParent; }

private:
	CPoint m_origin;
	CSize m_size;
	IControl* m_pParent;
};

class CControl : public IControl
{
public:
	CControl();

	virtual void Draw() override;
	virtual bool OnSystemEvent(const EventData& event) override;
	virtual bool OnSignal(const SignalData& signal) override;
	
	
protected:
	virtual void DrawSelf() {}
	bool IsPointInsideMyBounds(const CPoint& point) const;

private:
	void DrawChild(TControlRef spControl);
};

#endif //__Controls_Control_H__
