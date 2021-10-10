#pragma once
#include "CShape.h"
#include "Common.h"
#include <stdexcept>

class CEllipse : public CShape
{
public:
	CEllipse(Color color, Point center, double horizontalRadius, double verticalRadius)
		: m_center(center)
		, m_horizontalRadius(horizontalRadius)
		, m_verticalRadius(verticalRadius)
		, CShape(color)
	{
		if (center.x < 0 || center.y < 0 || horizontalRadius < 0 || verticalRadius < 0)
			throw std::invalid_argument("Invalid polygon vertex amount");
	}

	void Draw(ICanvas& canvas) const override;
	Point GetCenter() const;
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;

private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};

