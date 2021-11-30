#include "CSlide.h"

using namespace std;

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (shape == nullptr)
		throw logic_error("Invalid shape");
	if (position >= m_shapes.size())
		m_shapes.push_back(shape);
	else
	{
		auto it = m_shapes.begin();
		m_shapes.insert(it, position, shape);
	}
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index > m_shapes.size())
		throw logic_error("position is out of bounce");
	auto it = m_shapes.begin();
	m_shapes.erase(it + index);
}

void CSlide::Draw(ICanvas& canvas) const
{
	for (auto& shape : m_shapes)
		shape->Draw(canvas);
}