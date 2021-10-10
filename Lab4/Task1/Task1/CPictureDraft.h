#pragma once
#include "CShape.h"
#include <vector>

class CPictureDraft
{
public:
	int GetShapeCount() const;
	const std::unique_ptr<CShape>& GetShape(int index) const;
	void AddShape(std::unique_ptr<CShape>&& shape);

private:
	std::vector<std::unique_ptr<CShape>> m_shapes;
};

