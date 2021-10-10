#include "CPictureDraft.h"
#include "CDesigner.h"
#include <iostream>
#include <string>

CPictureDraft CDesigner::CreateDraft(std::istream& strm)
{
    std::string line;
    CPictureDraft draft;
    while (std::getline(strm, line))
    {
        try
        {
            auto shape = m_shapeFactory->CreateShape(line);
            draft.AddShape(std::move(shape));
        }
        catch (std::invalid_argument)
        {
            continue;
        }
    }

    return draft;
}
