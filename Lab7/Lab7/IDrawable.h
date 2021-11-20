#pragma once
#include "ICanvas.h"

class IDrawable
{
public:
	// зачем?
	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~IDrawable() = default;
};
