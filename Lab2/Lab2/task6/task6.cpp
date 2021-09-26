#include "WeatherData.h"

int main()
{
	CWeatherDataPro wdProOut("outside");
	CWeatherData wdIn("inside");

	CDisplay display;
	wdProOut.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wdProOut.RegisterObserver(statsDisplay);

	wdProOut.SetMeasurements(3, 0.7, 760, 3, 270);
	wdProOut.SetMeasurements(4, 0.8, 761, 3, 0);
	wdProOut.SetMeasurements(4, 0.8, 761, 3, 90);
	wdProOut.SetMeasurements(4, 0.8, 761, 0, 0);

	wdIn.SetMeasurements(1, 0.3, 766);
	wdIn.SetMeasurements(2, 0.8, 757);
	wdIn.SetMeasurements(4, 0.8, 764);
	wdIn.SetMeasurements(4, 0.8, 761);

	return 0;
}