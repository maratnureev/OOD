#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape()
		: m_frame(RectD{0,0,0,0})
	{}

	RectD GetFrame() override;

	shared_ptr<CLineStyle> GetOutlineStyle() override;
	const shared_ptr<CLineStyle> GetOutlineStyle()const override;

	shared_ptr<CFillStyle> GetFillStyle() override;
	const shared_ptr<CFillStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::shared_ptr<IGroupShape> GetParent() const override;
	void SetParent(shared_ptr<IGroupShape> parent) override;

private:
	std::shared_ptr<CLineStyle> m_outlineStyle = std::make_shared<CLineStyle>();
	std::shared_ptr<CFillStyle> m_fillStyle = std::make_shared<CFillStyle>();
	RectD m_frame;
	shared_ptr<IGroupShape> m_parent;
};

