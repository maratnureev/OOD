#include "HtmlEncoder.h"
#include <regex>

typedef regex_token_iterator<const char*> Iterator;

string EncodeStringIfHtmlCode(string const& symbolCode)
{
    if (symbolCode == "<")
        return "&lt;";
    if (symbolCode == ">")
        return "&gt;";
    if (symbolCode == "\"")
        return "&quot;";
    if (symbolCode == "'")
        return "&apos;";
    if (symbolCode == "&")
        return "&amp;";
    return symbolCode;
}

string HtmlEncode(string const& html)
{
    const char* tempHtml = html.c_str();
    vector<string>htmlParts;
    Iterator::regex_type rx("<|>|\"|&|'");
    Iterator next(tempHtml, tempHtml + html.length(), rx);
    Iterator end;

    string decodedString;
    next = Iterator(tempHtml, tempHtml + strlen(tempHtml), rx, { -1,0 });
    for (; next != end; ++next)
        decodedString += EncodeStringIfHtmlCode(next->str());

    return decodedString;
}