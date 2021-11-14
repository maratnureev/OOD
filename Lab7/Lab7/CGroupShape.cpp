#include "CGroupShape.h"
#include <algorithm>

RectD CGroupShape::GetFrame()
{
	if (m_shapes.empty())
		throw logic_error("group is empty");
	std::vector<double> leftXCoords;
	std::vector<double> topYCoords;
	std::vector<double> rightXCoords;
	std::vector<double> bottomYCoords;
	for (auto shape : m_shapes)
	{
		leftXCoords.push_back(shape->GetFrame().left);
		topYCoords.push_back(shape->GetFrame().top);
		rightXCoords.push_back(shape->GetFrame().left + shape->GetFrame().width);
		bottomYCoords.push_back(shape->GetFrame().top - shape->GetFrame().height);
	}

	double left = *min_element(leftXCoords.begin(), leftXCoords.end());
	double right = *max_element(rightXCoords.begin(), rightXCoords.end());
	double bottom = *min_element(bottomYCoords.begin(), bottomYCoords.end());
	double top = *max_element(topYCoords.begin(), topYCoords.end());

	return RectD{ left, top, right - left, top - bottom };
}

void CGroupShape::SetFrame(const RectD& rect)
{
}

shared_ptr<CLineStyle> CGroupShape::GetOutlineStyle()
{
	if (m_shapes.empty())
		throw logic_error("group is empty");
	auto firstElemColor = m_shapes[0]->GetOutlineStyle()->GetColor();
	for (auto shape : m_shapes)
	{
		if (firstElemColor != shape->GetOutlineStyle()->GetColor())
			return nullptr;
	}
	return m_shapes[0]->GetOutlineStyle();
}

const shared_ptr<CLineStyle> CGroupShape::GetOutlineStyle() const
{
	return GetOutlineStyle();
}

shared_ptr<CFillStyle> CGroupShape::GetFillStyle()
{
	if (m_shapes.empty())
		throw logic_error("group is empty");
	auto firstElemColor = m_shapes[0]->GetFillStyle()->GetColor();
	for (auto shape : m_shapes)
	{
		if (firstElemColor != shape->GetFillStyle()->GetColor())
			return nullptr;
	}
	return m_shapes[0]->GetFillStyle();
}

const shared_ptr<CFillStyle> CGroupShape::GetFillStyle() const
{
	return GetFillStyle();
}

shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return GetGroup();
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (auto shape : m_shapes)
		shape->Draw(canvas);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position >= m_shapes.size())
		m_shapes.push_back(shape);
	else
	{
		auto it = m_shapes.begin();
		m_shapes.insert(it, position, shape);
	}
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index > m_shapes.size())
		throw logic_error("position is out of bounce");
	auto it = m_shapes.begin();
	m_shapes.erase(it + index);
}

std::shared_ptr<IGroupShape> CGroupShape::GetParent() const
{
	return m_parent;
}

void CGroupShape::SetParent(std::shared_ptr<IGroupShape> parent)
{
	m_parent = parent;
}

bool CGroupShape::IsParent(std::shared_ptr<IGroupShape> parent)
{
	auto currentNode = GetGroup();
	while (currentNode != nullptr)
	{
		if (currentNode == parent)
			return false;
		currentNode = currentNode->GetParent();
	}
	return true;
}