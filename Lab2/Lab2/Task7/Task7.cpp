#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, EventType::TEMPERATURE_CHANGED);
	wd.RegisterObserver(display, EventType::PRESSURE_CHANGED);
	wd.SetTemperature(-5);
	wd.SetPressure(765);

	return 0;
}