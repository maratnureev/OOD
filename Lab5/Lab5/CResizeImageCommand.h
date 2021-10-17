#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(IDocument& document, size_t position, int width, int height)
		: m_document(document)
		, m_position(position)
		, m_newWidth(width)
		, m_newHeight(height)
	{
	}

protected:

	void DoExecute() override
	{
		auto item = m_document.GetItem(*m_position).GetImage();
		if (item == nullptr)
			throw invalid_argument("Position is out of bounce");
		m_oldWidth = item->GetWidth();
		m_oldHeight = item->GetHeight();
		item->Resize(m_newWidth, m_newHeight);
	}

	void DoUnexecute() override
	{
		auto item = m_document.GetItem(*m_position).GetImage();
		if (item == nullptr)
			throw invalid_argument("Position is out of bounce");
		item->Resize(m_oldWidth, m_oldHeight);
	}

private:
	IDocument& m_document;
	optional<size_t> m_position;
	int m_newWidth;
	int m_newHeight;
	int m_oldWidth;
	int m_oldHeight;
};

