#pragma once
#include <stdexcept>
#include "CShape.h"
#include "Common.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, Point center, double radius, int vertexCount)
		: m_center(center)
		, m_radius(radius)
		, m_vertexCount(vertexCount)
		, CShape(color)
	{
		if (vertexCount < 3 || center.x < 0 || center.y < 0 || vertexCount < 0 || radius < 0)
			throw std::invalid_argument("Invalid polygon vertex amount");
	}

	void Draw(ICanvas& canvas) const override;
	Point GetCenter() const;
	double GetRadius() const;
	int GetVertexCount() const;

private:
	Point m_center;
	double m_radius;
	int m_vertexCount;
};

