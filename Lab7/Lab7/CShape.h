#pragma once
#include "IShape.h"
#include "CLineStyle.h"
#include "CFillStyle.h"

class CShape : public IShape
{
public:
	CShape()
		:m_frame(RectD{ 0, 0, 0, 0 })
	{}

	RectD GetFrame() override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	const std::shared_ptr<IFillStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::shared_ptr<IGroupShape> GetParent() const override;
	void SetParent(std::shared_ptr<IGroupShape> parent) override;

protected:
	RectD m_frame;

private:
	std::shared_ptr<IOutlineStyle> m_outlineStyle = std::make_shared<CLineStyle>();
	std::shared_ptr<IFillStyle> m_fillStyle = std::make_shared<CFillStyle>();
	std::shared_ptr<IGroupShape> m_parent;
};

