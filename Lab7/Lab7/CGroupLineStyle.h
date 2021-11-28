#pragma once
#include "IStyle.h"

class CGroupLineStyle : public IOutlineStyle
{
public:
	CGroupLineStyle(std::vector<std::shared_ptr<IShape>>& shapes)
		:m_shapes(shapes)
	{}

	std::optional<RGBAColor> GetColor()const override
	{
		auto firstElemColor = m_shapes[0]->GetOutlineStyle()->GetColor();
		bool isLineSizeEqual = true;
		for (auto shape : m_shapes)
		{
			if (firstElemColor != shape->GetOutlineStyle()->GetColor())
				isLineSizeEqual = false;
		}
		return firstElemColor;
	}

	void SetColor(RGBAColor color) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetColor(color);
	}

	std::optional<double> GetStrokeSize() const override
	{
		auto firstElemWidth = m_shapes[0]->GetOutlineStyle()->GetStrokeSize();
		bool isLineSizeEqual = true;
		for (auto shape : m_shapes)
		{
			if (firstElemWidth != shape->GetOutlineStyle()->GetStrokeSize())
				isLineSizeEqual = false;
		}
		return firstElemWidth;
	}

	void SetStrokeSize(double size) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetStrokeSize(size);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};