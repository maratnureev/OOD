#pragma once
#include <stdexcept>
#include "CShape.h"
#include "Common.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point firstVertex, Point secondVertex, Point thirdVertex)
		: m_firstVertex(firstVertex)
		, m_secondVertex(secondVertex)
		, m_thirdVertex(thirdVertex)
		, CShape(color)
	{
		if (firstVertex.x < 0 || firstVertex.y < 0 || secondVertex.x < 0 || secondVertex.y < 0 || thirdVertex.x < 0 || thirdVertex.y < 0)
			throw std::invalid_argument("Invalid params");
	}

	void Draw(ICanvas& canvas) const override;
	Point GetFirstVertex() const;
	Point GetSecondVertex() const;
	Point GetThirdVertex() const;

private:
	Point m_firstVertex;
	Point m_secondVertex;
	Point m_thirdVertex;
};

