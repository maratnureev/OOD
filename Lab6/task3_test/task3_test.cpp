#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../task3/libraries.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>

using namespace std;

SCENARIO("adapter constructor test")
{
	ostringstream out;
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	app::CModernGraphicsRendererAdapter rendererAdapter(renderer);
	REQUIRE(out.str() == "<draw>\n");
}

SCENARIO("adapter destructor test")
{
	ostringstream out;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(out);
		app::CModernGraphicsRendererAdapter rendererAdapter(renderer);
	}

	REQUIRE(out.str() == "<draw>\n</draw>\n");
}

SCENARIO("adapter moveTo test")
{
	ostringstream out;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(out);
		app::CModernGraphicsRendererAdapter rendererAdapter(renderer);
		rendererAdapter.MoveTo(0, 0);
	}

	REQUIRE(out.str() == "<draw>\n</draw>\n");
}

SCENARIO("adapter lineTo test")
{
	ostringstream out;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(out);
		app::CModernGraphicsRendererAdapter rendererAdapter(renderer);
		rendererAdapter.MoveTo(0, 0);
		rendererAdapter.LineTo(1, 1);
	}

	REQUIRE(out.str() == "<draw>\n<line fromX='0' fromY='0' toX='1' toY='1'>\n<color r='0' g='0' b='0' a='1'/>\n</line>\n</draw>\n");
}

SCENARIO("adapter setColor test")
{
	ostringstream out;
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(out);
		app::CModernGraphicsRendererAdapter rendererAdapter(renderer);
		rendererAdapter.MoveTo(0, 0);
		rendererAdapter.SetColor(999999);
		rendererAdapter.LineTo(1, 1);
	}

	REQUIRE(out.str() == "<draw>\n<line fromX='0' fromY='0' toX='1' toY='1'>\n<color r='0.0588235' g='0.258824' b='0.247059' a='1'/>\n</line>\n</draw>\n");
}