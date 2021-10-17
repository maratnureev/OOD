#pragma once
#include <string>

using namespace std;

/* Параграф текста*/
class IParagraph
{
public:
	virtual string GetText()const = 0;
	virtual void SetText(const string& text) = 0;
	virtual ~IParagraph() = default;
};

