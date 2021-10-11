#pragma once
class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(std::string const& description) = 0;
	
	virtual ~IShapeFactory() = default;
};

typedef std::unique_ptr<IShapeFactory> IShapeFactoryPtr;
