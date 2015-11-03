#ifndef __Graphic_Dialog_H__
#define __Graphic_Dialog_H__

#include "GraphicObject.h"
#include <vector>
#include "WindowManager.h"

class CDialog : public CGraphicObject
{
public:
	CDialog();
	~CDialog();

	bool OnSystemEvent(const EventData& event);
};

#endif //__Graphic_Dialog_H__