#pragma once
#include "CommonTypes.h"
#include <optional>

class IFillStyle
{
public:
	virtual std::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	~IFillStyle() = default;
};

class IOutlineStyle
{
public:
	virtual std::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;
	virtual std::optional<double> GetStrokeSize() const = 0;
	virtual void SetStrokeSize(double size) = 0;

	~IOutlineStyle() = default;
};