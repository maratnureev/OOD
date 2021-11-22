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

void AssertShapeValid(shared_ptr<IShape>& figure, RectD rect, RGBAColor fillColor, RGBAColor lineColor, double lineWidth)
{
    REQUIRE(figure->GetFillStyle()->GetColor() == fillColor);
    REQUIRE(figure->GetOutlineStyle()->GetColor() == lineColor);
    REQUIRE(figure->GetOutlineStyle()->GetStrokeSize() == lineWidth);
    REQUIRE(abs(figure->GetFrame().height - rect.height) < 0.0001);
    REQUIRE(abs(figure->GetFrame().width - rect.width) < 0.0001);
    REQUIRE(abs(figure->GetFrame().left - rect.left) < 0.0001);
    REQUIRE(abs(figure->GetFrame().top - rect.top) < 0.0001);
}

SCENARIO("Test empty group")
{
    shared_ptr<CSlide> picture = make_shared<CSlide>(1920, 1080);
    ostringstream strm;
    CCanvas canvas(strm);
    canvas.BeginDraw();
    picture->Draw(canvas);
    canvas.EndDraw();
    picture->Draw(canvas);
    REQUIRE(strm.str() == "<svg xmlns='http://www.w3.org/2000/svg' width='1920' height='1080' viewPort='0 0 1920 1080'>\n</svg>\n");
}

SCENARIO("Test full group creation")
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

    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(ground);
    shapes.push_back(house);

    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);
    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);

    AssertShapeValid(ground, RectD{ 0, 600, 1200, 500 }, 0x524E2A, 0x000000, 0);
    AssertShapeValid(house, RectD{ 100, 400, 300, 200 }, 0x793119, 0x000000, 0);
    AssertShapeValid(lake, RectD{ 700, 700, 120, 65 }, 0x46F5F4, 0x000000, 0);
    AssertShapeValid(roof, RectD{ 80, 400, 340, 200 }, 0x11AA4E, 0x000000, 0);
    AssertShapeValid(sun, RectD{ 800, 150, 100, 100 }, 0xE7EF32, 0x000000, 0);
    AssertShapeValid(window, RectD{ 200, 470, 100, 100 }, 0x46F5F4, 0x000000, 0);
}

SCENARIO("Test group resize")
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

    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(ground);
    shapes.push_back(house);

    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);
    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);

    RectD frame = picture->GetFrame();
    picture->SetFrame(RectD{ 0, 700, 800, 300 });

    AssertShapeValid(ground, RectD{ 0, 400, 800, 333.33333 }, 0x524E2A, 0x000000, 0);
    AssertShapeValid(house, RectD{ 66.66665, 266.66665, 200, 133.33333 }, 0x793119, 0x000000, 0);
    AssertShapeValid(lake, RectD{ 466.66666, 466.66666, 80, 43.33333 }, 0x46F5F4, 0x000000, 0);
    AssertShapeValid(roof, RectD{ 53.33333, 266.66666, 226.66666, 133.33333 }, 0x11AA4E, 0x000000, 0);
    AssertShapeValid(sun, RectD{ 533.33333, 100, 66.66666, 66.66666 }, 0xE7EF32, 0x000000, 0);
    AssertShapeValid(window, RectD{ 133.33333, 313.33333, 66.66666, 66.66666 }, 0x46F5F4, 0x000000, 0);
}

SCENARIO("Test group change color")
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

    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(ground);
    shapes.push_back(house);

    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);
    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);

    picture->GetFillStyle()->SetColor(0x00FFff);
    picture->GetOutlineStyle()->SetColor(0x0000ff);
    picture->GetOutlineStyle()->SetStrokeSize(9);

    AssertShapeValid(ground, RectD{ 0, 600, 1200, 500 }, 0x00FFff, 0x0000ff, 9);
    AssertShapeValid(house, RectD{ 100, 400, 300, 200 }, 0x00FFff, 0x0000ff, 9);
    AssertShapeValid(lake, RectD{ 700, 700, 120, 65 }, 0x00FFff, 0x0000ff, 9);
    AssertShapeValid(roof, RectD{ 80, 400, 340, 200 }, 0x00FFff, 0x0000ff, 9);
    AssertShapeValid(sun, RectD{ 800, 150, 100, 100 }, 0x00FFff, 0x0000ff, 9);
    AssertShapeValid(window, RectD{ 200, 470, 100, 100 }, 0x00FFff, 0x0000ff, 9);
}

SCENARIO("Test GetColor with different colors in group")
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

    std::vector<std::shared_ptr<IShape>> shapes;
    shapes.push_back(ground);
    shapes.push_back(house);

    shared_ptr<IGroupShape> picture = make_shared<CGroupShape>(shapes);
    picture->InsertShape(window);
    picture->InsertShape(roof);
    picture->InsertShape(lake);
    picture->InsertShape(sun);

    REQUIRE(picture->GetFillStyle()->GetColor() == nullopt);
    REQUIRE(picture->GetOutlineStyle()->GetColor() == 0x000000);
    REQUIRE(picture->GetOutlineStyle()->GetStrokeSize() == 0);
}

SCENARIO("test recursive insertion")
{
    shared_ptr<IShape> figure1 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    shared_ptr<IShape> figure2 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    shared_ptr<IShape> figure3 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    shared_ptr<IShape> figure4 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    shared_ptr<IShape> figure5 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    shared_ptr<IShape> figure6 = make_shared<CRectangle>(PointD{ 0, 600 }, 1200, 500);
    std::vector<std::shared_ptr<IShape>> shapes1;
    shapes1.push_back(figure1);
    shapes1.push_back(figure2);
    shared_ptr<IGroupShape> group1 = make_shared<CGroupShape>(shapes1);
    std::vector<std::shared_ptr<IShape>> shapes2;
    shapes2.push_back(figure3);
    shapes2.push_back(figure4);
    shared_ptr<IGroupShape> group2 = make_shared<CGroupShape>(shapes2);
    std::vector<std::shared_ptr<IShape>> shapes3;
    shapes3.push_back(figure5);
    shapes3.push_back(figure6);
    shared_ptr<IGroupShape> group3 = make_shared<CGroupShape>(shapes3);
    REQUIRE_NOTHROW(group1->InsertShape(group2));
    REQUIRE_NOTHROW(group2->InsertShape(group3));
    REQUIRE_THROWS(group3->InsertShape(group1));
}