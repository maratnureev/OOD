#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <optional>
#include <filesystem>
#include "IImage.h"
#include "IParagraph.h"
#include "CDocumentItem.h"
#include "ICommand.h"

using namespace std;

typedef filesystem::path Path;
/*
	�������� ���������
*/
class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = nullopt) = 0;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	virtual shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = nullopt) = 0;

	// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount()const = 0;

	// ������ � ��������� �����������
	virtual CConstDocumentItem GetItem(size_t index)const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const string& title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const Path& path)const = 0;

	virtual void HandleCommand(unique_ptr<ICommand>&& command) = 0;

	virtual ~IDocument() = default;
};