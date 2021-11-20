#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <iostream>
#include "../Lab7/CommonTypes.h"
#include "../Lab7/CSlide.h"
#include "../Lab7/CCanvas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Lab7/CEllipse.h"
#include "../Lab7/CTriangle.h"
#include "../Lab7/CRectangle.h"
#include "../Lab7/CGroupShape.h"

using namespace std;

SCENARIO("Test empty group")
{
    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>();
    ostringstream strm;
    CCanvas canvas(strm);
    canvas.BeginDraw();
    picture->Draw(canvas);
    canvas.EndDraw();
    REQUIRE_THROWS(picture->Draw(canvas));
    REQUIRE(strm.str() == "<svg xmlns='http://www.w3.org/2000/svg' width='1920' height='1080' viewPort='0 0 1920 1080'>\n</svg>\n");
}

SCENARIO("Test full group")
{
    ostringstream strm;
    CCanvas canvas(strm);
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

    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>();
    picture->InsertShape(ground);
    picture->InsertShape(house);
    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);

    picture->GetOutlineStyle()->SetColor(0x000000);
    picture->GetOutlineStyle()->SetStrokeSize(9);
    REQUIRE(ground->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(ground->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(house->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(house->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(lake->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(lake->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(ground->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(ground->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(ground->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(ground->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(ground->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(ground->GetOutlineStyle()->GetStrokeSize() == 9);
    REQUIRE(ground->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(ground->GetOutlineStyle()->GetStrokeSize() == 9);

}