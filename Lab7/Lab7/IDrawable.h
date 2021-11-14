#pragma once
#include "ICanvas.h"

using namespace std;

class IDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~IDrawable() = default;
};
