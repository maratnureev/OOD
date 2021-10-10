#include "CEllipse.h"
#include "ICanvas.h"

void CEllipse::Draw(ICanvas& canvas) const
{
    canvas.SetColor(m_color);
    canvas.DrawElipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point CEllipse::GetCenter() const
{
    return m_center;
}

double CEllipse::GetHorizontalRadius() const
{
    return m_horizontalRadius;
}

double CEllipse::GetVerticalRadius() const
{
    return m_verticalRadius;
}
