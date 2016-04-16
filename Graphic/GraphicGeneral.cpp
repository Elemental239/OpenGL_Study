#include "GraphicGeneral.h"
#include "Logger.h"
#include "StringImpl.h"

CGenericPoint<int> FloatPointToIntPoint(CGenericPoint<double> point)
{
	return CGenericPoint<int>(
		static_cast<int>(point.GetX()),
		static_cast<int>(point.GetY()),
		static_cast<int>(point.GetZ())
		);
}

/////////////////////////////////////////
///CColor
CColor::CColor(CStringA strColor)
{
	if (strColor[0] == '#')
		strColor = strColor.substr(1, strColor.length() - 1);

	if (strColor.length() != 6 && strColor.length() != 8)
	{
		LOGE("Can't parse color string %s in constructor", LST(strColor));
		m_nRed = 0;
		m_nGreen = 0;
		m_nBlue = 0;
		m_nAlpha = MAX_COLOR_PART_VALUE;
		return;
	}

	CStringA substr = strColor.substr(0, 2);
	m_nRed = std::stoi(substr, 0, 16);
	
	substr = strColor.substr(2, 2);
	m_nGreen = std::stoi(substr, 0, 16);
	
	substr = strColor.substr(4, 2);
	m_nBlue = std::stoi(substr, 0, 16);

	if (strColor.length() == 6)
	{
		m_nAlpha = MAX_COLOR_PART_VALUE;
	}
	else
	{
		substr = strColor.substr(6, 2);
		m_nAlpha = std::stoi(substr, 0, 16);
	}
}

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

CString8 CColor::ToString() const
{
	return FormatString("#%02X%02X%02X%02X", m_nRed, m_nGreen, m_nBlue, m_nAlpha);
}
