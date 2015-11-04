#ifndef __Graphic_Dialog_H__
#define __Graphic_Dialog_H__

#include "GraphicObject.h"
#include <vector>
#include "WindowManager.h"

class IDialog : public CGraphicObject
{
public:
	virtual bool OnSystemEvent(const EventData& event) = 0;
};

class CDialog : public IDialog
{
public:
	CDialog();
	~CDialog();

	virtual bool OnSystemEvent(const EventData& event) override;
};

#endif //__Graphic_Dialog_H__