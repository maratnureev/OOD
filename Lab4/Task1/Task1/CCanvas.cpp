#include "CCanvas.h"
#include "Common.h"
#include <iostream>

void CCanvas::SetColor(Color color)
{
    m_color = color;
}

void CCanvas::DrawLine(Point from, Point to)
{
    m_output
        << "<line "
        << "x1 = '" << from.x << "' y1 = '" << from.y
        << "' x2 = '" << to.x << "' y2 = '" << to.y << "' "
        << "stroke = '" << GetColorName(m_color) << "' stroke-width = '5'/>"
        << std::endl;
}

void CCanvas::DrawElipse(Point center, double w, double h)
{
    m_output
        << "<ellipse "
        << "rx='" << w << "' ry='" << h << "' "
        << "cx='" << center.x << "' cy='" << center.y << "' "
        << "stroke='" << GetColorName(m_color) << "' stroke-width='5' "
        << "fill='transparent' />"
        << std::endl;
}

std::string CCanvas::GetColorName(Color color) const
{
    switch (color)
    {
    case Color::GREEN:
        return "green";
    case Color::BLUE:
        return "blue";
    case Color::RED:
        return "red";
    case Color::YELLOW:
        return "yellow";
    case Color::PINK:
        return "pink";
    case Color::BLACK:
        return "black";
    }
    throw std::invalid_argument("Invalid color");
}

