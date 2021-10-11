#include "CRegularPolygon.h"

void CRegularPolygon::Draw(ICanvas& canvas) const
{
    canvas.SetColor(m_color);
    double centerAngle = 2 * 3.14 / m_vertexCount;

    bool isFirst = true;
    Point lastPoint;
    Point firstPoint;

    for (int i = 0; i < m_vertexCount; i++)
    {
        Point point;
        point.x = m_center.x + m_radius * sin(centerAngle * i);
        point.y = m_center.y + m_radius * cos(centerAngle * i);

        if (!isFirst)
            canvas.DrawLine(lastPoint, point);
        else
            firstPoint = point;
        isFirst = false;
        lastPoint = point;
    }
    canvas.DrawLine(lastPoint, firstPoint);
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

int CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}
