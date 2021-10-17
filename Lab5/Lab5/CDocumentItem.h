#pragma once
#include <string>
#include <memory>
#include "IImage.h"
#include "IParagraph.h"

using namespace std;

/*
	Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: m_image(image)
		, m_paragraph(paragraph)
	{}
	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	shared_ptr<const IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<const IParagraph> GetParagraph()const;

protected:
	shared_ptr<IImage> m_image;
	shared_ptr<IParagraph> m_paragraph;
};

/*
	Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(image, paragraph)
	{}
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	shared_ptr<IParagraph> GetParagraph();
};