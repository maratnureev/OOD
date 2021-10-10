#pragma once
#include <iostream>
#include "ICanvas.h"
#include "Common.h"

const int CANVAS_WIDTH = 1920;
const int CANVAS_HEIGHT = 1080;

class CCanvas : public ICanvas
{
public:
    CCanvas(std::ostream& out)
        : m_output(out)
    {
        m_output << "<svg "
            << "xmlns='http://www.w3.org/2000/svg' "
            << "width='" << CANVAS_WIDTH << "' height='" << CANVAS_HEIGHT << "' "
            << "viewPort='0 0 " << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "'>"
            << std::endl;
    };

    ~CCanvas()
    {
        m_output << "</svg>" << std::endl;
    };

	void SetColor(Color color);
	void DrawLine(Point from, Point to);
	void DrawElipse(Point center, double w, double h);
private:
    std::string GetColorName(Color color) const;

private:
	Color m_color = Color::BLACK;
    std::ostream& m_output;
};

