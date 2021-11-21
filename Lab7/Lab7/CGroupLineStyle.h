#pragma once
#include "IStyle.h"

class CGroupLineStyle : public IOutlineStyle
{
public:
	CGroupLineStyle(std::vector<std::shared_ptr<IShape>>& shapes, std::optional<RGBAColor> color, std::optional<double> strokeSize)
		:m_shapes(shapes)
		,m_color(color)
		,m_strokeSize(strokeSize)
	{}

	std::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetColor(color);
	}

	std::optional<double> GetStrokeSize() const override
	{
		return m_strokeSize;
	}

	void SetStrokeSize(double size) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetStrokeSize(size);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
	std::optional<RGBAColor> m_color;
	std::optional<double> m_strokeSize;
};