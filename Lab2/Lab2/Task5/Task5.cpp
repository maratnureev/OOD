#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 3, 270);
	wd.SetMeasurements(4, 0.8, 761, 3, 0);
	wd.SetMeasurements(4, 0.8, 761, 3, 90);
	
	return 0;
}