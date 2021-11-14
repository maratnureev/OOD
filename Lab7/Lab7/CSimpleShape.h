#pragma once
#include "IShape.h"
#include <functional>

typedef std::function<void(ICanvas& canvas, const IShape& shape)> DrawingStrategy;

class CSimpleShape : public IShape
{
public:
	CSimpleShape(const DrawingStrategy& drawingStrategy)
	{
		(void)&drawingStrategy;
	}
};

