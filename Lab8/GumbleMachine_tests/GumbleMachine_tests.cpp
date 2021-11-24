#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "../Lab8/GumBallMachineWithState.h"
#include "../Lab8/NaiveGumBallMachine.h"

using namespace std;

SCENARIO("test gumble machine creation state with 0 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(0, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Machine is sold out\n");
}

SCENARIO("test gumble machine creation state with 5 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 1 quarter and turn")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.InsertQuarter();
	m.TurnCrank();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 4 gumballs\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine eject Quarter")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.EjectQuarter();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"Quarter returned\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 4 gumballs\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine eject without coin")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.EjectQuarter();
	REQUIRE(out.str() == "You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 5")
{
	ostringstream out;
	with_state::CGumballMachine m(3, out);
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"Oops, out of gumballs\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Machine is sold out\n");
}

SCENARIO("test state gumble machine insert coin when out of gumballs")
{
	ostringstream out;
	with_state::CGumballMachine m(1, out);
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"Oops, out of gumballs\n"
		"You can't insert a quarter, the machine is sold out\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Machine is sold out\n");
}

SCENARIO("test state gumble machine turn without a coin")
{
	ostringstream out;
	with_state::CGumballMachine m(1, out);
	m.TurnCrank();
	REQUIRE(out.str() == "You turned but there's no quarter\n"
		"You need to pay first\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 1 gumball\n"
		"Machine is waiting for quarter\n");
}