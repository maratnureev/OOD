#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(const string& text)
		:m_text(text)
	{}
	string GetText()const;
	void SetText(const string& text);
private:
	string m_text;
};