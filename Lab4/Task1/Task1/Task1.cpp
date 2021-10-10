#include <iostream>
#include <fstream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CPictureDraft.h"
#include "CCanvas.h"
#include "CPainter.h"

int main()
{
    std::ofstream result("result.svg");
    IShapeFactoryPtr shapeFactory = std::make_unique<CShapeFactory>();

    CDesigner designer(std::move(shapeFactory));

    CPictureDraft draft = designer.CreateDraft(std::cin);

    CCanvas canvas(result);

    CPainter painter;

    painter.DrawPicture(draft, canvas);
}
