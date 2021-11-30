#pragma once
#include "IGroupShape.h"
#include <stdexcept>
#include <vector>
#include "CGroupStyle.h"
#include "CGroupLineStyle.h"

class CGroupShape : public IGroupShape, public std::enable_shared_from_this<CGroupShape>
{
public:
	CGroupShape(std::vector<std::shared_ptr<IShape>> shapes)
		:m_shapes(std::move(shapes))
	{
		if (shapes.size() < 2)
			throw std::logic_error("Cannot create group less then from 2 elements");
	}

	static std::shared_ptr<CGroupShape> Create(std::vector<std::shared_ptr<IShape>> shapes)
	{
		auto shape = std::make_shared<CGroupShape>(std::move(shapes));
		// TODO: adopt chidren
		return shape;
	}

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	std::shared_ptr<const IOutlineStyle> GetOutlineStyle()const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	std::shared_ptr<const IFillStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;
	void RemoveShapeAtIndex(size_t index) override;

	std::weak_ptr<IGroupShape> GetParent() const;
	void SetParent(std::weak_ptr<IGroupShape> parent);

	bool IsParent(std::weak_ptr<IShape> parent);
	
private:
	std::shared_ptr<IFillStyle> m_groupFillStyle = nullptr;
	std::shared_ptr<IOutlineStyle> m_groupLineStyle = nullptr;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::weak_ptr<IGroupShape> m_parent;
};

