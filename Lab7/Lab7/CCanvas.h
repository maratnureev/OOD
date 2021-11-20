#pragma once
#include "ICanvas.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>

const int CANVAS_WIDTH = 1920;
const int CANVAS_HEIGHT = 1080;

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream& strm)
		: m_out(strm)
		, m_fillColor(0)
		, m_lineColor(0)
	{
	}

	~CCanvas()
	{
		if (m_drawing)
		{
			EndDraw();
		}
	}

	void SetLineWidth(double width) override
	{
		m_lineWidth = width;
	}

	void SetLineColor(RGBAColor color = 0) override
	{
		m_lineColor = color;
	}

	void BeginFill(RGBAColor color = 0) override
	{
		if (m_filling)
		{
			throw std::logic_error("Filling has already begun");
		}
		m_filling = true;
		m_fillColor = color;
	}

	void EndFill() override 
	{
		if (!m_filling)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_filling = false;
	}

	void BeginDraw() override
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<svg "
			<< "xmlns='http://www.w3.org/2000/svg' "
			<< "width='" << CANVAS_WIDTH << "' height='" << CANVAS_HEIGHT << "' "
			<< "viewPort='0 0 " << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "'>"
			<< std::endl;
		m_drawing = true;
	}
	
	void DrawLine(PointD from, PointD to) override
	{
		m_out << "<line "
			<< "x1 = '" << from.x << "' y1 = '" << from.y
			<< "' x2 = '" << to.x << "' y2 = '" << to.y << "' "
			<< "stroke = '" << ConvertRgbaToString(m_lineColor) << "' stroke-width = '" << m_lineWidth << "'/>"
			<< std::endl;
	}

	void EndDraw() override
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</svg>" << std::endl;
		m_drawing = false;
	}

	void DrawEllipse(double left, double top, double width, double height) override
	{
		m_out << "<ellipse "
			<< "rx='" << width << "' ry='" << height << "' "
			<< "cx='" << left+width / 2 << "' cy='" << top + height << "' "
			<< "stroke='" << ConvertRgbaToString(m_lineColor) << "' stroke-width='" << m_lineWidth << "' "
			<< "fill='" << ConvertRgbaToString(m_fillColor) << "' />"
			<< std::endl;
	}

	void FillPolygon(std::vector<PointD> points) override
	{
		if (points.size() == 0)
		{
			throw std::logic_error("FillPolygon with zero vertexes");
		}

		std::string vertexesString;
		std::for_each(points.begin(), points.end(), [&vertexesString](PointD point) {
			vertexesString += std::to_string(point.x) + "," + std::to_string(point.y) + " ";
			});
		vertexesString.pop_back();

		m_out
			<< "<polygon "
			<< "points = '" << vertexesString << "' "
			<< "fill = '" << ConvertRgbaToString(m_fillColor) << "'/>" << std::endl;
	}

private:
	std::ostream& m_out;
	double m_lineWidth = 0;
	bool m_drawing = false;
	bool m_filling = false;
	RGBAColor m_fillColor;
	RGBAColor m_lineColor;
	double m_startX = 0;
	double m_startY = 0;

	std::string ConvertRgbaToString(RGBAColor color)
	{
		int red = (color >> 16) & 0xff;
		int green = (color >> 8) & 0xff;
		int blue = color & 0xff;
		return  "rgb(" + std::to_string(red) + "," + std::to_string(green) + "," + std::to_string(blue) + ")";
	}
};

