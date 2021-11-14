#pragma once
#include "CShape.h"
#include "ICanvas.h"
#include <algorithm>
#include <vector>

class CTriangle : public CShape
{
public:
	CTriangle(const PointD& p1, const PointD& p2, const PointD& p3)
		: CShape()
	{
		double xCoords[] = { p1.x, p2.x, p3.x };
		double yCoords[] = { p1.y, p2.y, p3.y };
		double left = *min_element(xCoords, xCoords + 3);
		double right = *max_element(xCoords, xCoords + 3);
		double bottom = *min_element(yCoords, yCoords + 3);
		double top = *max_element(yCoords, yCoords + 3);
		RectD rect = {
			left,
			top,
			right - left,
			top - bottom,
		};
		SetFrame(rect);
	}

	void Draw(ICanvas& canvas)const override
	{
		auto outlineStyle = GetOutlineStyle();
		if (outlineStyle == nullptr)
			throw logic_error("invalid outline style for basic shape");

		canvas.SetLineColor(outlineStyle->GetColor());
		canvas.SetLineWidth(outlineStyle->GetStrokeSize());
		auto fillStyle = GetFillStyle();
		if (fillStyle == nullptr)
			throw logic_error("invalid line style for basic shape");
		canvas.BeginFill(fillStyle->GetColor());
		vector<PointD> points;
		points.push_back(m_p1);
		points.push_back(m_p2);
		points.push_back(m_p3);
		canvas.FillPolygon(points);
		canvas.DrawLine(m_p1, m_p2);
		canvas.DrawLine(m_p2, m_p3);
		canvas.DrawLine(m_p3, m_p1);
		canvas.EndFill();
	}

	void SetFrame(const RectD& rect) override
	{
		m_p1 = PointD{ rect.left, rect.top};
		m_p2 = PointD{ rect.left + rect.width, rect.top};
		m_p3 = PointD{ rect.left + rect.width / 2, rect.top - rect.height };
	}

private:
	PointD m_p1;
	PointD m_p2;
	PointD m_p3;
};

