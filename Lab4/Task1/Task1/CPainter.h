#pragma once
#include "CPictureDraft.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft const& draft, ICanvas& canvas);
};

