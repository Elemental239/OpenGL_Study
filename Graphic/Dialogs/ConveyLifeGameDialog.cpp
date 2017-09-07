#include "ConveyLifeGameDialog.h"
#include "Logger.h"
#include "GraphicObjects/Rectangle.h"

CConveyLifeGameDialog::CConveyLifeGameDialog()
{
	MARKER("CConveyLifeGameDialog::CConveyLifeGameDialog()");
}

CConveyLifeGameDialog::~CConveyLifeGameDialog()
{
	MARKER("CConveyLifeGameDialog::~CConveyLifeGameDialog()");
}

void CConveyLifeGameDialog::CreateChildren()
{
	MARKER("CConveyLifeGameDialog::CreateChildren()");

	//TGraphicObjectRef spRectangle = new CRectangle(CSize(100, 0), CColor("6F8322"));
	//spRectangle->SetAlignOption(EAlignOption::CENTER_X);
	//spRectangle->SetSizeOption(ESizeOption::FILL_Y);
	//spRectangle->SetMargins(0, 10, 0, 40);
	//TControlRef spSimpleControl = new CControl(spRectangle);
	
	//AddChild(spSimpleControl);
}

void CConveyLifeGameDialog::OnLifetimeEvent(EDialogLifetimeEvent event)
{
	MARKER("CConveyLifeGameDialog::OnLifetimeEvent()");

	CDialog::OnLifetimeEvent(event);
}




