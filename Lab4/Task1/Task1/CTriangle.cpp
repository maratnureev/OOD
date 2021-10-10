#include "CTriangle.h"

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_firstVertex, m_secondVertex);
	canvas.DrawLine(m_secondVertex, m_thirdVertex);
	canvas.DrawLine(m_thirdVertex, m_firstVertex);
}

Point CTriangle::GetFirstVertex() const
{
	return m_firstVertex;
}

Point CTriangle::GetSecondVertex() const
{
	return m_secondVertex;
}

Point CTriangle::GetThirdVertex() const
{
	return m_thirdVertex;
}
