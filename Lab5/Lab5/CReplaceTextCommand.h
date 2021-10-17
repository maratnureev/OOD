#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(IDocument& document, optional<size_t> position, const string& text)
		: m_document(document)
		, m_newText(text)
		, m_position(position)
	{
	}

protected:

	void DoExecute() override
	{
		auto item = m_document.GetItem(*m_position).GetParagraph();
		if (item == nullptr)
			throw invalid_argument("Position is out of bounce");
		m_oldText = item->GetText();
		item->SetText(m_newText);
	}

	void DoUnexecute() override
	{
		auto item = m_document.GetItem(*m_position).GetParagraph();
		if (item == nullptr)
			throw invalid_argument("Position is out of bounce");
		item->SetText(m_oldText);
	}

private:
	IDocument& m_document;
	string m_newText;
	string m_oldText;
	optional<size_t> m_position;
};
