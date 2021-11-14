#pragma once
#include "CommonTypes.h"
#include <optional>

using namespace std;

class CFillStyle
{
public:
	RGBAColor GetColor()const
	{
		return m_color;
	}

	void SetColor(RGBAColor color)
	{
		m_color = color;
	}

private:
	RGBAColor m_color = 0;
};