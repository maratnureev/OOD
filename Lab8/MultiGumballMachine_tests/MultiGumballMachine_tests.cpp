#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "../MultiGumballMachine/GumBallMachineWithState.h"
#include "../MultiGumballMachine/NaiveGumBallMachine.h"

using namespace std;

SCENARIO("test gumble machine creation state with 0 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(0, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test gumble machine creation state with 5 coins")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
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
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine turn without coin and eject")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.EjectQuarter();
	REQUIRE(out.str() == "You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 4 quarter and eject without coin")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 1 gumball\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine insert 5")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
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
		"Bank: 0 quarters\n"
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
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test state gumble machine refill from empty state")
{
	ostringstream out;
	with_state::CGumballMachine m(0, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}


SCENARIO("test state gumble machine refill from no quarter state")
{
	ostringstream out;
	with_state::CGumballMachine m(1, out);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 1 gumball\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test state gumble machine refill from has quarter state")
{
	ostringstream out;
	with_state::CGumballMachine m(1, out);
	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 1 gumball\n"
		"Bank: 1 quarter\n"
		"Machine is waiting for turn of crank\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 1 quarter\n"
		"Machine is waiting for turn of crank\n");
}

SCENARIO("test state gumble machine refill from full state")
{
	ostringstream out;
	with_state::CGumballMachine m(1, out);
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 1 gumball\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
}


SCENARIO("test state gumble machine insert 5 coins and get gumballs")
{
	ostringstream out;
	with_state::CGumballMachine m(5, out);
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 5 gumballs\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.TurnCrank();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 4 gumballs\n"
		"Bank: 4 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.TurnCrank();
	m.TurnCrank();
	m.TurnCrank();
	m.TurnCrank();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016 (with state)\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test gumble machine creation naive with 0 coins")
{
	ostringstream out;
	naive::CGumballMachine m(0, out);

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test gumble machine creation naive with 5 coins")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test naive gumble machine insert 1 quarter and turn")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	m.InsertQuarter();
	m.TurnCrank();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 4 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test naive gumble machine turn without coin and eject")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	m.EjectQuarter();
	REQUIRE(out.str() == "You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test naive gumble machine insert 4 quarter and eject without coin")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You haven't inserted a quarter\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 1 gumball\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test naive gumble machine insert 5")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
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
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"Oops, out of gumballs\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test naive gumble machine insert coin when out of gumballs")
{
	ostringstream out;
	naive::CGumballMachine m(1, out);

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	REQUIRE(out.str() == "You inserted a quarter\n"
		"You turned...\n"
		"A gumball comes rolling out the slot...\n"
		"Oops, out of gumballs\n"
		"You can't insert a quarter, the machine is sold out\n");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}

SCENARIO("test naive gumble machine refill from empty state")
{
	ostringstream out;
	naive::CGumballMachine m(0, out);

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 5 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}


SCENARIO("test naive gumble machine refill from no quarter state")
{
	ostringstream out;
	naive::CGumballMachine m(1, out);

	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 1 gumball\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 6 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is waiting for quarter\n");
}

SCENARIO("test naive gumble machine refill from has quarter state")
{
	ostringstream out;
	naive::CGumballMachine m(1, out);

	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 1 gumball\n"
		"Bank: 1 quarter\n"
		"Machine is waiting for turn of crank\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 6 gumballs\n"
		"Bank: 1 quarter\n"
		"Machine is waiting for turn of crank\n");
}

SCENARIO("test naive gumble machine refill from full state")
{
	ostringstream out;
	naive::CGumballMachine m(1, out);

	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 1 gumball\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.Refill(5);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 6 gumballs\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
}


SCENARIO("test naive gumble machine insert 5 coins and get gumballs")
{
	ostringstream out;
	naive::CGumballMachine m(5, out);

	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	m.InsertQuarter();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 5 gumballs\n"
		"Bank: 5 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.TurnCrank();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 4 gumballs\n"
		"Bank: 4 quarters\n"
		"Machine is waiting for turn of crank\n");
	m.TurnCrank();
	m.TurnCrank();
	m.TurnCrank();
	m.TurnCrank();
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
		"C++-enabled Standing Gumball Model #2016\n"
		"Inventory: 0 gumballs\n"
		"Bank: 0 quarters\n"
		"Machine is sold out\n");
}