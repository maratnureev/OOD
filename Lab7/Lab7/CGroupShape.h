#pragma once
#include "IGroupShape.h"
#include <stdexcept>
#include <vector>
#include "CGroupStyle.h"
#include "CGroupLineStyle.h"

class CGroupShape : public IGroupShape, public std::enable_shared_from_this<CGroupShape>
{
public:
	RectD GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	const std::shared_ptr<IFillStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;
	void RemoveShapeAtIndex(size_t index) override;

	std::shared_ptr<IGroupShape> GetParent() const;
	void SetParent(std::shared_ptr<IGroupShape> parent);

	bool IsParent(std::shared_ptr<IShape> parent);
	
private:
	std::shared_ptr<IFillStyle> m_groupFillStyle = nullptr;
	std::shared_ptr<IOutlineStyle> m_groupLineStyle = nullptr;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IGroupShape> m_parent = nullptr; //weak_ptr... 
};

