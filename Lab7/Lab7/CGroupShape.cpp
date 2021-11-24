#include "CGroupShape.h"
#include "ICanvas.h"
#include <algorithm>

using namespace std;

RectD CGroupShape::GetFrame() const
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
	if (m_shapes.empty())
		return;
	auto oldFrame = GetFrame();
	auto widthRatio = rect.width / oldFrame.width;
	auto heightRation = rect.height / oldFrame.height;
	auto leftOffset = oldFrame.left - rect.left;
	auto topOffset = oldFrame.top - rect.top;
	for (auto shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		auto newFrame = RectD{ widthRatio*(shapeFrame.left + leftOffset), heightRation * (shapeFrame.top + topOffset), shapeFrame.width * widthRatio, shapeFrame.height * heightRation };
		shape->SetFrame(newFrame);
	}
}

shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()
{
	if (m_shapes.empty())
		throw logic_error("group is empty");
	auto firstElemColor = m_shapes[0]->GetOutlineStyle()->GetColor();
	auto firstElemWidth = m_shapes[0]->GetOutlineStyle()->GetStrokeSize();
	bool isColorEqual = true;
	bool isLineSizeEqual = true;
	for (auto shape : m_shapes)
	{
		if (firstElemColor != shape->GetOutlineStyle()->GetColor())
			isColorEqual = false;
		if (firstElemWidth != shape->GetOutlineStyle()->GetStrokeSize())
			isLineSizeEqual = false;
	}
	// проверять при получении цвета цвета фигур.
	shared_ptr<IOutlineStyle>lineStyle = make_shared<CGroupLineStyle>(m_shapes, isColorEqual ? firstElemColor : nullopt, isLineSizeEqual ? firstElemWidth : nullopt);
	m_groupLineStyle = lineStyle;
	return m_groupLineStyle;
}

const shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle() const
{
	return GetOutlineStyle();
}

shared_ptr<IFillStyle> CGroupShape::GetFillStyle()
{
	if (m_shapes.empty())
		throw logic_error("group is empty");
	auto firstElemColor = m_shapes[0]->GetFillStyle()->GetColor();
	bool isColorEqual = true;
	for (auto shape : m_shapes)
	{
		if (firstElemColor != shape->GetFillStyle()->GetColor())
		{
			isColorEqual = false;
			break;
		}
	}
	shared_ptr<IFillStyle>fillStyle = make_shared<CGroupFillStyle>(m_shapes, isColorEqual ? firstElemColor : nullopt);
	m_groupFillStyle = fillStyle;
	return m_groupFillStyle;
}

const shared_ptr<IFillStyle> CGroupShape::GetFillStyle() const
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
	auto it = m_shapes.begin();
	m_shapes.at(index)->SetParent(nullptr);
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

bool CGroupShape::IsParent(std::shared_ptr<IShape> parent)
{
	auto currentNode = GetGroup();
	while (currentNode != nullptr)
	{
		if (currentNode == parent)
			return true;
		currentNode = currentNode->GetParent();
	}
	return false;
}