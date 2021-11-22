#pragma once
#include "CommonTypes.h"
#include <optional>
#include <vector>
#include "IStyle.h"

class CGroupFillStyle : public IFillStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>>& shapes, std::optional<RGBAColor> color)
		:m_shapes(shapes)
		,m_color(color)
	{}

	std::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
		for (auto shape : m_shapes)
			shape->GetFillStyle()->SetColor(color);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
	std::optional<RGBAColor> m_color;
};