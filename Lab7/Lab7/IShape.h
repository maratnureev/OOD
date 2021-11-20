#pragma once
#include "IDrawable.h"
#include "IStyle.h"
#include <optional>
#include <memory>

class IGroupShape;

class IShape : public IDrawable
{
public:
	// const method
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() = 0;
	virtual const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const = 0;

	virtual std::shared_ptr<IFillStyle> GetFillStyle() = 0;
	virtual const std::shared_ptr<IFillStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual std::shared_ptr<IGroupShape> GetParent() const = 0;
	virtual void SetParent(std::shared_ptr<IGroupShape> parent) = 0;

	virtual ~IShape() = default;
};