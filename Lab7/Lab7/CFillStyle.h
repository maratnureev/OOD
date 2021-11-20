#pragma once
#include "CommonTypes.h"
#include <optional>
#include "IStyle.h"

class CFillStyle : public IFillStyle
{
public:
	RGBAColor GetColor()const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

private:
	RGBAColor m_color = 0;
};