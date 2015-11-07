#include "GraphicGeneral.h"
#include "Logger.h"
#include "StringImpl.h"

/////////////////////////////////////////
///CColor
int CColor::GetPartInt(ColorPart part)
{
	switch (part)
	{
		case COLOR_PART_RED:
			return m_nRed;

		case COLOR_PART_GREEN:
			return m_nGreen;

		case COLOR_PART_BLUE:
			return m_nBlue;

		case COLOR_PART_ALPHA:
			return m_nAlpha;

		default:
			LOGE("Unknown color part %d in CColor::GetPartInt()", part);
			return -1;
	}
}

CString CColor::ToString() const
{
	return FormatString("#%02X%02X%02X:%02X", m_nRed, m_nGreen, m_nBlue, m_nAlpha);
}
