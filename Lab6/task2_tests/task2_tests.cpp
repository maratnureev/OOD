#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../task2/libraries.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>

using namespace std;

SCENARIO("adapter constructor test")
{
	ostringstream out;
	app::CModernGraphicsRendererAdapter rendererAdapter(out);
	REQUIRE(out.str() == "<draw>\n");
}

SCENARIO("adapter destructor test")
{
	ostringstream out;
	{
		app::CModernGraphicsRendererAdapter rendererAdapter(out);
	}

	REQUIRE(out.str() == "<draw>\n</draw>\n");
}

SCENARIO("adapter moveTo test")
{
	ostringstream out;
	{
		app::CModernGraphicsRendererAdapter rendererAdapter(out);
		rendererAdapter.MoveTo(0, 0);
	}

	REQUIRE(out.str() == "<draw>\n</draw>\n");
}

SCENARIO("adapter lineTo test")
{
	ostringstream out;
	{
		app::CModernGraphicsRendererAdapter rendererAdapter(out);
		rendererAdapter.MoveTo(0, 0);
		rendererAdapter.LineTo(1, 1);
	}

	REQUIRE(out.str() == "<draw>\n<line fromX='0' fromY='0' toX='1' toY='1'/>\n</draw>\n");
}