#pragma once
#include <stdint.h>
#include <iostream>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

template <typename T>
struct Point {
	T x = 0;
	T y = 0;
};

typedef Point<double> PointD;
typedef Rect<double> RectD;
typedef uint32_t RGBAColor;