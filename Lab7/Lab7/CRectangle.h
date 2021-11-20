#pragma once
#include "CShape.h"
#include <stdexcept>
#include <vector>

class CRectangle : public CShape
{
public:
	CRectangle(const PointD& leftTop, double width, double height)
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
		std::vector<PointD> points;
		points.push_back(PointD{ m_leftTop.x, m_leftTop.y });
		points.push_back(PointD{ m_leftTop.x + m_width, m_leftTop.y });
		points.push_back(PointD{ m_leftTop.x + m_width, m_leftTop.y + m_height });
		points.push_back(PointD{ m_leftTop.x, m_leftTop.y + m_height });
		canvas.FillPolygon(points);
		canvas.DrawLine(m_leftTop, PointD{ m_leftTop.x + m_width, m_leftTop.y});
		canvas.DrawLine(PointD{ m_leftTop.x + m_width, m_leftTop.y }, PointD{ m_leftTop.x + m_width, m_leftTop.y + m_height });
		canvas.DrawLine(PointD{ m_leftTop.x + m_width, m_leftTop.y + m_height }, PointD{ m_leftTop.x, m_leftTop.y + m_height });
		canvas.DrawLine(PointD{ m_leftTop.x, m_leftTop.y + m_height }, m_leftTop);
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

