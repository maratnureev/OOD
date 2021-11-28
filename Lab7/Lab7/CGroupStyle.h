#pragma once
#include "CommonTypes.h"
#include <optional>
#include <vector>
#include "IStyle.h"

class CGroupFillStyle : public IFillStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>>& shapes)
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
			shape->GetFillStyle()->SetColor(color);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};