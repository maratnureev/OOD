#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "WeatherData.h"

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(CWeatherData& wd)
		:m_wd(&wd)
	{}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::shared_ptr<CMockDisplay> thisShared(this);
		m_wd->RemoveObserver(thisShared);
	}

	CWeatherData* m_wd;
};

SCENARIO("Delete during update test")
{
	CWeatherData wd;
	auto mockDisplay = std::make_shared<CMockDisplay>(wd);
	wd.RegisterObserver(mockDisplay);
	auto display = std::make_shared<CDisplay>();
	wd.RegisterObserver(display);

	auto statsDisplay = std::make_shared<CStatsDisplay>();
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
}