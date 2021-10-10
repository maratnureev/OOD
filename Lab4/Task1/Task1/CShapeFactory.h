#pragma once
#include <string>
#include "CShape.h"
#include "IShapeFactory.h"
#include <memory>

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(std::string const& description);
	
private:
	std::unique_ptr<CShape> CreateRectangle(std::istream& strm, Color color) const;
	std::unique_ptr<CShape> CreateTriangle(std::istream& strm, Color color) const;
	std::unique_ptr<CShape> CreateEllipse(std::istream& strm, Color color) const;
	std::unique_ptr<CShape> CreateRegularPolygon(std::istream& strm, Color color) const;
	Color GetColorByName(std::string const& color) const;
};

