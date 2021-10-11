#pragma once
#include <iostream>
#include "CPictureDraft.h"

class IDesigner
{
public:
	virtual CPictureDraft CreateDraft(std::istream& strm) = 0;

	virtual ~IDesigner() = default;
};

typedef std::unique_ptr<IDesigner> IDesignerPtr;
