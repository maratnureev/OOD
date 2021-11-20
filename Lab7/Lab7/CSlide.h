#pragma once
#include <vector>
#include "IShape.h"
#include "IDrawable.h"

class CSlide : public IDrawable
{
public:
	CSlide(double width, double height)
		: m_width(width)
		, m_height(height)
	{};

	size_t GetShapesCount()const;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max());
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const;
	void RemoveShapeAtIndex(size_t index);
	void Draw(ICanvas& canvas) const override;

	double GetWidth()const;
	double GetHeight()const;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	double m_width = 0;
	double m_height = 0;
};

