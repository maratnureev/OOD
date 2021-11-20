#pragma once
#include "IStyle.h"

class CGroupLineStyle : public IOutlineStyle
{
public:
	CGroupLineStyle(std::vector<std::shared_ptr<IShape>>& shapes)
		:m_shapes(shapes)
	{}

	RGBAColor GetColor()const override
	{
		return m_shapes[0]->GetOutlineStyle()->GetColor();
	}

	void SetColor(RGBAColor color) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetColor(color);
	}

	double GetStrokeSize() const override
	{
		return m_shapes[0]->GetOutlineStyle()->GetColor();
	}

	void SetStrokeSize(double size) override
	{
		for (auto shape : m_shapes)
			shape->GetOutlineStyle()->SetStrokeSize(size);
	}

private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;

};