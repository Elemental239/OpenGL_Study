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

	TGraphicObjectRef spRectangle = new CRectangle(CSize(200, 200), CColor("6F8322"));
	TControlRef spSimpleControl = new CControl(spRectangle);
	AddChild(spSimpleControl);
}
