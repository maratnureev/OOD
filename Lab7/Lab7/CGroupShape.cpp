#include "CGroupShape.h"
#include "ICanvas.h"
#include <algorithm>

using namespace std;

RectD CGroupShape::GetFrame() const
{
	std::vector<double> leftXCoords;
	std::vector<double> topYCoords;
	std::vector<double> rightXCoords;
	std::vector<double> bottomYCoords;
	for (auto& shape : m_shapes)
	{
		leftXCoords.push_back(shape->GetFrame().left);
		topYCoords.push_back(shape->GetFrame().top);
		rightXCoords.push_back(shape->GetFrame().left + shape->GetFrame().width);
		bottomYCoords.push_back(shape->GetFrame().top + shape->GetFrame().height);
	}

	double left = *min_element(leftXCoords.begin(), leftXCoords.end());
	double right = *max_element(rightXCoords.begin(), rightXCoords.end());
	double bottom = *min_element(bottomYCoords.begin(), bottomYCoords.end());
	double top = *max_element(topYCoords.begin(), topYCoords.end());

	return RectD{ left, top, right - left, top - bottom };
}

void CGroupShape::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();
	auto widthRatio = rect.width / oldFrame.width;
	auto heightRation = rect.height / oldFrame.height;
	auto leftOffset = oldFrame.left - rect.left;
	auto topOffset = oldFrame.top - rect.top;
	for (auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		auto newFrame = RectD{ widthRatio*(shapeFrame.left + leftOffset), heightRation * (shapeFrame.top + topOffset), shapeFrame.width * widthRatio, shapeFrame.height * heightRation };
		shape->SetFrame(newFrame);
	}
}

shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()
{
	shared_ptr<IOutlineStyle>lineStyle = make_shared<CGroupLineStyle>(m_shapes);
	m_groupLineStyle = lineStyle;
	return m_groupLineStyle;
}

shared_ptr<const IOutlineStyle> CGroupShape::GetOutlineStyle() const
{
	return GetOutlineStyle();
}

shared_ptr<IFillStyle> CGroupShape::GetFillStyle()
{
	shared_ptr<IFillStyle>fillStyle = make_shared<CGroupFillStyle>(m_shapes);
	m_groupFillStyle = fillStyle;
	return m_groupFillStyle;
}

shared_ptr<const IFillStyle> CGroupShape::GetFillStyle() const
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
	for (auto& shape : m_shapes)
		shape->Draw(canvas);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (shape == nullptr)
		throw logic_error("Invalid shape");
	if (IsParent(shape))
		throw logic_error("Cannot recursive insert");
	if (position >= m_shapes.size())
		m_shapes.push_back(shape);
	else
	{
		auto it = m_shapes.begin();
		m_shapes.insert(it, position, shape);
	}
	shape->SetParent(GetGroup());
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index) const
{
	return m_shapes.at(index);
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index > m_shapes.size())
		throw logic_error("position is out of bounce");
	if (m_shapes.size() == 1)
		throw logic_error("can not remove last group element");
	auto it = m_shapes.begin();
	m_shapes.erase(it + index);
}

std::weak_ptr<IGroupShape> CGroupShape::GetParent() const
{
	return m_parent;
}

void CGroupShape::SetParent(std::weak_ptr<IGroupShape> parent)
{
	m_parent = std::move(parent);
}

bool CGroupShape::IsParent(std::weak_ptr<IShape> parent)
{
	auto currentNode = GetGroup();
	while (currentNode != nullptr)
	{
		if (currentNode == parent.lock())
			return true;
		currentNode = currentNode->GetParent().lock();
	}
	return false;
}