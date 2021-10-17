#pragma once
#include "IDocument.h"
#include <vector>
#include "History.h"

class CHtmlDocument : public IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = nullopt);

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = nullopt);

	// ���������� ���������� ��������� � ���������
	size_t GetItemsCount()const;

	// ������ � ��������� �����������
	CConstDocumentItem GetItem(size_t index)const;
	CDocumentItem GetItem(size_t index);

	// ������� ������� �� ���������
	void DeleteItem(size_t index);

	// ���������� ��������� ���������
	string GetTitle()const;
	// �������� ��������� ���������
	void SetTitle(const string& title);

	// �������� � ����������� �������� Undo
	bool CanUndo()const;
	// �������� ������� ��������������
	void Undo();

	// �������� � ����������� �������� Redo
	bool CanRedo()const;
	// ��������� ���������� ������� ��������������
	void Redo();

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	void Save(const Path& path)const;

	void HandleCommand(unique_ptr<ICommand>&& command);

private:
	void AssertPositionValid(size_t position) const;

	CHistory m_history;
	vector<CDocumentItem> m_items;
	string m_title;
	Path m_path;
	int m_imageCounter = 0;
};

