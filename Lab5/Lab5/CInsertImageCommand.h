#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(IDocument& document, const Path& path, int width, int height, optional<size_t> position = nullopt)
		: m_document(document)
		, m_path(path)
		, m_width(width)
		, m_height(height)
		, m_position(position)
	{}

protected:

	void DoExecute() override
	{
		try
		{
			m_document.InsertImage(m_path, m_width, m_height, m_position);
		}
		// лоавить исключение копирования
		catch (exception e)
		{
			throw invalid_argument("File does not exists: " + m_path.string());
		}
	}

	void DoUnexecute() override
	{
		auto position = m_position == nullopt ? m_document.GetItemsCount() - 1 : *m_position;
		m_image = m_document.GetItem(position).GetImage();
		m_document.DeleteItem(position);
	}
	
	void Destroy() override
	{	
		filesystem::remove(m_image->GetPath());
	}

private:
	IDocument& m_document;
	Path m_path;
	int m_width;
	int m_height;
	shared_ptr<IImage> m_image;
	optional<size_t> m_position = nullopt;
};

