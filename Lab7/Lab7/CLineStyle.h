#pragma once
#include "CommonTypes.h"
#include <optional>
#include "IStyle.h"

class CLineStyle : public IOutlineStyle
{
public:
	std::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

	std::optional<double> GetStrokeSize() const override
	{
		return m_strokeSize;
	}

	void SetStrokeSize(double size) override
	{
		m_strokeSize = size;
	}

private:
	RGBAColor m_color = 0;
	double m_strokeSize = 0;
};