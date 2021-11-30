#pragma once
#include "IStyle.h"
#include <functional>

class IOutlineStyleEnumerator
{
public:
	virtual void EnumerateOutlineStyles(const std::function<bool(IOutlineStyle& style)>& callback) const = 0;
};


class CGroupLineStyle : public IOutlineStyle
{
public:
	CGroupLineStyle(std::vector<std::shared_ptr<IShape>>& shapes)
		:m_shapes(shapes)
	{}

	std::optional<RGBAColor> GetColor()const override
	{
		auto firstElemColor = m_shapes[0]->GetOutlineStyle()->GetColor();
		for (auto& shape : m_shapes)
		{
			if (firstElemColor != shape->GetOutlineStyle()->GetColor())
				return std::nullopt;
		}
		return firstElemColor;
	}

	void SetColor(RGBAColor color) override
	{
		for (auto& shape : m_shapes)
			shape->GetOutlineStyle()->SetColor(color);
	}

	std::optional<double> GetStrokeSize() const override
	{
		auto firstElemWidth = m_shapes[0]->GetOutlineStyle()->GetStrokeSize();
		for (auto& shape : m_shapes)
		{
			if (firstElemWidth != shape->GetOutlineStyle()->GetStrokeSize())
				return std::nullopt;
		}
		return firstElemWidth;
	}

	void SetStrokeSize(double size) override
	{
		for (auto& shape : m_shapes)
			shape->GetOutlineStyle()->SetStrokeSize(size);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};