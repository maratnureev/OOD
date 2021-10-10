#pragma once
class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(std::string const& description) = 0;
};

typedef std::unique_ptr<IShapeFactory> IShapeFactoryPtr;
