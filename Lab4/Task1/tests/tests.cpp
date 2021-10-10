#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task1/CEllipse.h"
#include "../Task1/CRectangle.h"
#include "../Task1/CRegularPolygon.h"
#include "../Task1/CTriangle.h"
#include "../Task1/CShapeFactory.h"
#include "../Task1/CDesigner.h"
#include "../Task1/CPainter.h"
#include "../Task1/CPictureDraft.h"
#include "../Task1/CCanvas.h"
#include "../Task1/Common.h"

using namespace std;

void CheckEllipse(CEllipse& ellipse, Color color, Point center, double horizontalR, double verticalRadius)
{
	REQUIRE(ellipse.GetHorizontalRadius() == horizontalR);
	REQUIRE(ellipse.GetVerticalRadius() == verticalRadius);

	REQUIRE(ellipse.GetCenter().x == center.x);
	REQUIRE(ellipse.GetCenter().y == center.y);

	REQUIRE(ellipse.GetColor() == color);
}

void CheckRectangle(CRectangle& rect, Color color, Point leftTop, Point bottomRight)
{
	REQUIRE(rect.GetLeftTop().x == leftTop.x);
	REQUIRE(rect.GetLeftTop().y == leftTop.y);

	REQUIRE(rect.GetRightBottom().x == bottomRight.x);
	REQUIRE(rect.GetRightBottom().y == bottomRight.y);

	REQUIRE(rect.GetColor() == color);
}

void CheckTriangle(CTriangle& triangle, Color color, Point v1, Point v2, Point v3)
{
	REQUIRE(triangle.GetFirstVertex().x == v1.x);
	REQUIRE(triangle.GetFirstVertex().y == v1.y);

	REQUIRE(triangle.GetSecondVertex().x == v2.x);
	REQUIRE(triangle.GetSecondVertex().y == v2.y);

	REQUIRE(triangle.GetThirdVertex().x == v3.x);
	REQUIRE(triangle.GetThirdVertex().y == v3.y);

	REQUIRE(triangle.GetColor() == color);
}

void CheckPolygon(CRegularPolygon& polygon, Color color, Point center, double radius, int vertCount)
{
	REQUIRE(polygon.GetVertexCount() == vertCount);

	REQUIRE(polygon.GetCenter().x == center.x);
	REQUIRE(polygon.GetCenter().y == center.y);

	REQUIRE(polygon.GetRadius() == radius);

	REQUIRE(polygon.GetColor() == color);
}

void PrintToCanvas(ostream& out, CPictureDraft& draft)
{
	CCanvas canvas(out);
	CPainter painter;
	painter.DrawPicture(draft, canvas);
}


SCENARIO("test Shapes")
{
	CEllipse ellipse(
		Color::BLUE,
		{ 100, 200 },
		150,
		200
	);
	CheckEllipse(
		ellipse,
		Color::BLUE,
		{ 100 , 200 },
		150,
		200
	);


	CTriangle triangle(
		Color::BLUE,
		{ 100, 100 },
		{ 200, 200 },
		{ 500, 500 }
	);
	CheckTriangle(
		triangle,
		Color::BLUE,
		{ 100, 100 },
		{ 200, 200 },
		{ 500, 500 }
	);


	CRectangle rect(
		Color::PINK,
		{ 100, 100 },
		{ 500, 500 }
	);
	CheckRectangle(
		rect,
		Color::PINK,
		{ 100, 100 },
		{ 500, 500 }
	);


	CRegularPolygon regular(
		Color::GREEN,
		{ 300, 300 },
		50,
		5
	);
	CheckPolygon(
		regular,
		Color::GREEN,
		{ 300, 300 },
		50,
		5
	);
}

SCENARIO("Designer and PictuREDraft tests And when Painter And Canvas")
{
	IShapeFactoryPtr shapeFactory = std::make_unique<CShapeFactory>();
	CDesigner designer(move(shapeFactory));

	string input = "rectangle red 100 100 500 500\n"
		"triangle blue 100 100 300 300 500 500\n"
		"ellipse yellow 100 100 50 80\n"
		"circle black 100 100 15 15\n"
		"polygon black 100 100 50 6\n"
		"polygon black 6 15 105\n"
		"polygon black 100 100 60 2\n";
	istringstream in(input);

	CPictureDraft draft = designer.CreateDraft(in);

	REQUIRE(draft.GetShapeCount() == 4);
	CRectangle* rect = dynamic_cast<CRectangle*>(draft.GetShape(0).get());
	REQUIRE(rect != nullptr);
	CheckRectangle(
		*rect,
		Color::RED,
		{ 100, 100 },
		{ 500, 500 }
	);
	CTriangle* triangle = dynamic_cast<CTriangle*>(draft.GetShape(1).get());
	REQUIRE(triangle != nullptr);
	CheckTriangle(
		*triangle,
		Color::BLUE,
		{ 100, 100 },
		{ 300, 300 },
		{ 500, 500 }
	);
	CEllipse* ellipse = dynamic_cast<CEllipse*>(draft.GetShape(2).get());
	REQUIRE(ellipse != nullptr);
	CheckEllipse(
		*ellipse,
		Color::YELLOW,
		{ 100, 100 },
		50,
		80
	);
	CRegularPolygon* polygon = dynamic_cast<CRegularPolygon*>(draft.GetShape(3).get());
	REQUIRE(polygon != nullptr);
	CheckPolygon(
		*polygon,
		Color::BLACK,
		{ 100, 100 },
		50,
		6
	);

	string result = "<svg xmlns='http://www.w3.org/2000/svg' width='1920' height='1080' viewPort='0 0 1920 1080'>\n"
		"<line x1 = '100' y1 = '100' x2 = '500' y2 = '100' stroke = 'red' stroke-width = '5'/>\n"
		"<line x1 = '500' y1 = '100' x2 = '500' y2 = '500' stroke = 'red' stroke-width = '5'/>\n"
		"<line x1 = '500' y1 = '500' x2 = '100' y2 = '500' stroke = 'red' stroke-width = '5'/>\n"
		"<line x1 = '100' y1 = '500' x2 = '100' y2 = '100' stroke = 'red' stroke-width = '5'/>\n"
		"<line x1 = '100' y1 = '100' x2 = '300' y2 = '300' stroke = 'blue' stroke-width = '5'/>\n"
		"<line x1 = '300' y1 = '300' x2 = '500' y2 = '500' stroke = 'blue' stroke-width = '5'/>\n"
		"<line x1 = '500' y1 = '500' x2 = '100' y2 = '100' stroke = 'blue' stroke-width = '5'/>\n"
		"<ellipse rx='50' ry='80' cx='100' cy='100' stroke='yellow' stroke-width='5' fill='transparent' />\n"
		"<line x1 = '100' y1 = '150' x2 = '143.288' y2 = '125.023' stroke = 'black' stroke-width = '5'/>\n"
		"<line x1 = '143.288' y1 = '125.023' x2 = '143.328' y2 = '75.046' stroke = 'black' stroke-width = '5'/>\n"
		"<line x1 = '143.328' y1 = '75.046' x2 = '100.08' y2 = '50.0001' stroke = 'black' stroke-width = '5'/>\n"
		"<line x1 = '100.08' y1 = '50.0001' x2 = '56.7519' y2 = '74.9081' stroke = 'black' stroke-width = '5'/>\n"
		"<line x1 = '56.7519' y1 = '74.9081' x2 = '56.6325' y2 = '124.885' stroke = 'black' stroke-width = '5'/>\n"
		"<line x1 = '56.6325' y1 = '124.885' x2 = '100' y2 = '150' stroke = 'black' stroke-width = '5'/>\n"
		"</svg>\n";
	string out;
	ostringstream outStrm(out);
	PrintToCanvas(outStrm, draft);

	REQUIRE(outStrm.str() == result);
}