#ifndef __Graphic_ConveyLifeGameDialog_H__
#define __Graphic_ConveyLifeGameDialog_H__

#include "Dialog.h"
#include "ColorsResources.h"

class CConveyLifeGameDialog : public CDialog
{
public:
	CConveyLifeGameDialog();
	virtual ~CConveyLifeGameDialog();

	virtual void CreateChildren() override;

	virtual void OnLifetimeEvent(EDialogLifetimeEvent event) override;

	virtual CColor GetBackgroundColor() override { return COLOR_BLACK; }

private:

};

#endif //__Graphic_ConveyLifeGameDialog_H__
