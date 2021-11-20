#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(const PointD& leftTop, double width, double height)
		: CShape()
	{
		RectD rect = {
			leftTop.x,
			leftTop.y,
			width,
			height,
		};
		SetFrame(rect);
	}

	void Draw(ICanvas& canvas)const final
	{
		auto outlineStyle = GetOutlineStyle();
		if (outlineStyle == nullptr)
			throw std::logic_error("invalid outline style for basic shape");

		canvas.SetLineColor(outlineStyle->GetColor());
		canvas.SetLineWidth(outlineStyle->GetStrokeSize());
		auto fillStyle = GetFillStyle();
		if (fillStyle == nullptr)
			throw std::logic_error("invalid line style for basic shape");
		canvas.BeginFill(fillStyle->GetColor());
		canvas.DrawEllipse(m_leftTop.x, m_leftTop.y, m_width, m_height);
		canvas.EndFill();
	}


	void SetFrame(const RectD& rect) override
	{
		m_leftTop.x = rect.left;
		m_leftTop.y = rect.top;
		m_width = rect.width;
		m_height = rect.height;
		m_frame = rect;
	}

private:
	PointD m_leftTop;
	double m_width = 0;
	double m_height = 0;
};

