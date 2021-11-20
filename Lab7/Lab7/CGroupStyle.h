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

	RGBAColor GetColor()const override
	{
		return m_shapes[0]->GetFillStyle()->GetColor();
	}

	void SetColor(RGBAColor color) override
	{
		for (auto shape : m_shapes)
			shape->GetFillStyle()->SetColor(color);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};