#pragma once
#include <string>
#include <memory>
#include "IImage.h"
#include "IParagraph.h"

using namespace std;

/*
	������������ ������� ���������
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: m_image(image)
		, m_paragraph(paragraph)
	{}
	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<const IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<const IParagraph> GetParagraph()const;

protected:
	shared_ptr<IImage> m_image;
	shared_ptr<IParagraph> m_paragraph;
};

/*
	������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(image, paragraph)
	{}
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	shared_ptr<IParagraph> GetParagraph();
};