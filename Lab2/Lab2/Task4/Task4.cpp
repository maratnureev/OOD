#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "WeatherData.h"

SCENARIO("Delete during update test")
{
	CWeatherData wdIn("inside");
	CWeatherData wdOut("outside");
	CDisplay display;
	CStatsDisplay statsDisplay;

	wdIn.RegisterObserver(display);
	wdIn.RegisterObserver(statsDisplay);
	wdOut.RegisterObserver(display);
	wdOut.RegisterObserver(statsDisplay);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(10, 0.8, 761);
	wdIn.SetMeasurements(4, 0.8, 761);
	wdOut.SetMeasurements(-10, 0.8, 763);
	
	REQUIRE(statsDisplay.GetHumidity(wdIn.GetName()).maxValue == 0.8);
	REQUIRE(statsDisplay.GetPressure(wdIn.GetName()).maxValue == 761);
	REQUIRE(statsDisplay.GetTemperature(wdIn.GetName()).maxValue == 4);

	REQUIRE(statsDisplay.GetHumidity(wdOut.GetName()).maxValue == 0.8);
	REQUIRE(statsDisplay.GetPressure(wdOut.GetName()).maxValue == 763);
	REQUIRE(statsDisplay.GetTemperature(wdOut.GetName()).maxValue == 10);
}
