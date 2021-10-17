#include "CDocumentItem.h"

shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}

shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
