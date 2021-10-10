#pragma once
#include <memory>
#include "Common.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawElipse(Point center, double w, double h) = 0;

	virtual ~ICanvas() = default;
};

typedef std::unique_ptr<ICanvas> ICanvasPtr;

