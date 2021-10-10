#pragma once
#include <stdexcept>
#include "CShape.h"
#include "Common.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point leftTop, Point rightBottom)
		: m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
		, CShape(color)
	{
		if (leftTop.x < 0 || leftTop.y < 0 || rightBottom.x < 0 || rightBottom.y < 0)
			throw std::invalid_argument("Invalid params");
	}

	void Draw(ICanvas& canvas) const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};