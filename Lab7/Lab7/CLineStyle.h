#pragma once
#include "CommonTypes.h"
#include <optional>

using namespace std;

class CLineStyle
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

	double GetStrokeSize() const
	{
		return m_strokeSize;
	}

	void SetStrokeSize(double size)
	{
		m_strokeSize = size;
	}

private:
	RGBAColor m_color = 0;
	double m_strokeSize = 2;
};