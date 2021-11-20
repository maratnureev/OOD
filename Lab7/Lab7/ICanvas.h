#pragma once
#include "CommonTypes.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetLineWidth(double width) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void DrawLine(PointD from, PointD to) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;
	virtual void FillPolygon(std::vector<PointD> points) = 0;

	virtual ~ICanvas() = default;
};