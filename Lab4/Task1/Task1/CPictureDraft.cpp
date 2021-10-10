#include "CPictureDraft.h"

int CPictureDraft::GetShapeCount() const
{
    return m_shapes.size();
}

const std::unique_ptr<CShape>& CPictureDraft::GetShape(int index) const
{
    return m_shapes.at(index);
}

void CPictureDraft::AddShape(std::unique_ptr<CShape>&& shape)
{
    m_shapes.push_back(std::move(shape));
}
