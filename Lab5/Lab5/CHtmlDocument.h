#pragma once
#include "IDocument.h"
#include <vector>
#include "History.h"

class CHtmlDocument : public IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	shared_ptr<IParagraph> InsertParagraph(const string& text,
		optional<size_t> position = nullopt);

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images 
	// под автоматически сгенерированным именем
	shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = nullopt);

	// Возвращает количество элементов в документе
	size_t GetItemsCount()const;

	// Доступ к элементам изображения
	CConstDocumentItem GetItem(size_t index)const;
	CDocumentItem GetItem(size_t index);

	// Удаляет элемент из документа
	void DeleteItem(size_t index);

	// Возвращает заголовок документа
	string GetTitle()const;
	// Изменяет заголовок документа
	void SetTitle(const string& title);

	// Сообщает о доступности операции Undo
	bool CanUndo()const;
	// Отменяет команду редактирования
	void Undo();

	// Сообщает о доступности операции Redo
	bool CanRedo()const;
	// Выполняет отмененную команду редактирования
	void Redo();

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images
	// пути к изображениям указываются относительно пути к сохраняемому HTML файлу
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

