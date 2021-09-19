#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "WeatherData.h"

SCENARIO("test priority")
{
	CWeatherData wd;

	CDisplay display;
	CDisplay display2;
	wd.RegisterObserver(display2, 2);
	wd.RegisterObserver(display, 3);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760);
}

SCENARIO("test 2 displays with same priority")
{
	CWeatherData wd;

	CDisplay display;
	CDisplay display2;
	wd.RegisterObserver(display2, 2);
	wd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 3);

	wd.SetMeasurements(3, 0.7, 760);
}