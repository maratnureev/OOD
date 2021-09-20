#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "WeatherData.h"

class CMockDisplay : public IObserver<SWeatherInfo>
{
public:
	CMockDisplay(std::string name, std::vector<std::string> &callStack)
		: m_name(name)
		, m_callStack(&callStack)
	{}

public:

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_callStack->push_back(m_name);
	}

	std::string m_name;
	std::vector<std::string>* m_callStack;
};

SCENARIO("test priority")
{
	CWeatherData wd;

	std::vector<std::string> callStack;
	CMockDisplay display("test1", callStack);
	CMockDisplay display2("test2", callStack);
	CMockDisplay display3("test3", callStack);
	wd.RegisterObserver(display2, 0);
	wd.RegisterObserver(display3, 2);
	wd.RegisterObserver(display, 3);

	wd.SetMeasurements(3, 0.7, 760);

	REQUIRE(callStack[0] == "test1");
	REQUIRE(callStack[1] == "test3");
	REQUIRE(callStack[2] == "test2");
}
