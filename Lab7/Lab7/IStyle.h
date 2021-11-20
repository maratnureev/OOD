#pragma once
#include "CommonTypes.h"

class IFillStyle
{
public:
	virtual RGBAColor GetColor()const = 0;
	virtual  void SetColor(RGBAColor color) = 0;

	~IFillStyle() = default;
};

class IOutlineStyle
{
public:
	//Исправить optional RGBAColor 
	virtual RGBAColor GetColor()const = 0;
	virtual  void SetColor(RGBAColor color) = 0;
	virtual  double GetStrokeSize() const = 0;
	virtual void SetStrokeSize(double size) = 0;

	~IOutlineStyle() = default;
};