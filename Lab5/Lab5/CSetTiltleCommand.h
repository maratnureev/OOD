#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CSetTitleCommand : public CAbstractCommand
{
public:
	CSetTitleCommand(IDocument& document, const string& title)
		: m_document(document)
		, m_newTitle(title)
	{
	}

protected:

	void DoExecute() override
	{
		m_oldTitle = m_document.GetTitle();
		m_document.SetTitle(m_newTitle);
	}

	void DoUnexecute() override
	{
		m_document.SetTitle(m_oldTitle);
	}

private:
	IDocument& m_document;
	string m_newTitle;
	string m_oldTitle;
};