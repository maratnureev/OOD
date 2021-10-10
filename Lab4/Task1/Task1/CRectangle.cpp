#include "CRectangle.h"
#include "ICanvas.h"

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}
