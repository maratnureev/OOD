#include <cstdint>
#include "CommonTypes.h"
#include "CSlide.h"
#include "CCanvas.h"
#include <fstream>
#include <iostream>
#include "CEllipse.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CGroupShape.h"

using namespace std;

int main()
{
    CSlide slide(1000, 800);
    ofstream out("result.svg");
    CCanvas canvas(out);
    canvas.BeginDraw();
    shared_ptr<IShape> ground = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    ground->GetFillStyle()->SetColor(0x524E2A);
    shared_ptr<IShape> house = make_shared<CRectangle>(PointD{ 100, 400 }, 300, 200);
    house->GetFillStyle()->SetColor(0x793119);
    shared_ptr<IShape> window = make_shared<CRectangle>(PointD{ 200, 470 }, 100, 100);
    window->GetFillStyle()->SetColor(0x46F5F4);
    shared_ptr<IShape> roof = make_shared<CTriangle>(PointD{ 80, 400 }, PointD{ 420, 400 }, PointD{ 300, 200 });
    roof->GetFillStyle()->SetColor(0x11AA4E);
    shared_ptr<IShape> lake = make_shared<CEllipse>(PointD{ 700, 700 }, 120, 65);
    lake->GetFillStyle()->SetColor(0x46F5F4);
    shared_ptr<IShape> sun = make_shared<CEllipse>(PointD{ 800, 150 }, 100, 100);
    sun->GetFillStyle()->SetColor(0xE7EF32);
    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(ground);
    shapes.push_back(house);
    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);

    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);
    //picture->GetFillStyle()->SetColor(0x00FFff);
    //picture->GetOutlineStyle()->SetColor(0x0000ff);
    //picture->GetOutlineStyle()->SetStrokeSize(9);

    slide.InsertShape(picture);
    RectD frame = picture->GetFrame();
    picture->SetFrame(RectD{ 0, 700, 800, 300 });
    slide.Draw(canvas);
    canvas.EndDraw();
}