#include "CPainter.h"

void CPainter::DrawPicture(CPictureDraft const& draft, ICanvas& canvas)
{
	for (int i = 0; i < draft.GetShapeCount(); i++)
	{
		draft.GetShape(i)->Draw(canvas);
	}
}
