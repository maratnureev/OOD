#include "CShape.h"

using namespace std;

RectD CShape::GetFrame() const
{
	return m_frame;
}

shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const shared_ptr<IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

shared_ptr<IFillStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

const shared_ptr<IFillStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

std::shared_ptr<IGroupShape> CShape::GetParent() const
{
	return m_parent;
}

void CShape::SetParent(std::shared_ptr<IGroupShape> parent)
{
	m_parent = parent;
}
